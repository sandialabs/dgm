#ifndef DGM_COVARIANCE_MATRIX_HPP
#define DGM_COVARIANCE_MATRIX_HPP

/** \file CovarianceMatrix.hpp
 *  \brief Introduce objective weightings from Response JSON
 *  \author Greg von Winckel
 */

#include "json/json.h"

// DTK includes
#include "DTK_Types.hpp"

// DGM includes
#include "Domain.hpp"
#include "vField.hpp"
#include "Types.hpp"     // Defines dArray

// system includes
#include <map>
#include <string>

namespace DGM {

/*  For simplicity, we begin with diagonal nonnegative covariance matrices
 *  of the form W(t) = a*exp(b*t) which are used to modify the objective 
 *  integrand and the adjoint forcing term (dMatrix Obs::obj)  via 
 *  Response::multiply_by_weights. The coefficients are set based on
 *  the names of the fields present in the supplied vField and in the JSON.
 *  If  field appears in the vField, but not in JSON, its weights are set 
 *  to default values, while the converse throws an exception. 
 *
 *  The JSON block should have one of the following forms:
 *
 *  "Covariance Matrix" : {
 *    "Weighting Type" : "Exponential",
 *    "Field Components" : {
 *      "Field Component Name 1" : {
 *        "Mantissa" : 1.0,
 *        "Exponent" : 0.0    
 *      }
 *    },
 *    . . . 
 *  }
 *
 *  or
 *
 * "Covariance Matrix" : {
 *    "Weighting Type" : "Linear",
 *    "Field Components" : {
 *      "Field Component Name 1" : {
 *        "Constant Coefficient" : 1.e-5,
 *        "Linear Cocefficient"  : 1.0    
 *      }
 *    },
 *    . . . 
 *  }

 *
 *  Note that the above coefficients are the default values that give
 *  uniform weighting.
 */
struct CovarianceMatrix {
  using size_type  = typename vField::size_type;
  using Map = std::map<std::string,size_type>;

  virtual ~CovarianceMatrix() {}

  virtual void initialize( Map& fieldNames, Json::Value& json ) = 0;
  virtual void set_weights( const Domain* const domain, dArray& weights ) = 0;

}; // CovarianceMatrix

class CovarianceMatrix_Linear : public CovarianceMatrix {
public:
  CovarianceMatrix_Linear( CovarianceMatrix::size_type numFields ) : 
    c0(numFields,1.0), c1(numFields,0.0) {}
 
  void initialize( CovarianceMatrix::Map& fieldNames, Json::Value& json );
  void set_weights( const Domain* const domain, dArray& weights );

private:
  std::vector<Scalar> c0; // Constant Coefficient
  std::vector<Scalar> c1; // Linear Coefficient

}; // CovarianceMatrix_Linear

class CovarianceMatrix_Exponential : public CovarianceMatrix {
public:
  CovarianceMatrix_Exponential( CovarianceMatrix::size_type numFields ):
    mantissae(numFields, 1.0), exponents(numFields, 0.0) {}

  void initialize(  CovarianceMatrix::Map& fieldNames, Json::Value& json );
  void set_weights( const Domain* const domain, dArray& weights );

private:
  std::vector<Scalar> mantissae;
  std::vector<Scalar> exponents;

}; // CovarianceMatrix_Exponential

inline void CovarianceMatrix_Linear::initialize( 
  CovarianceMatrix::Map& fieldNames, Json::Value& json ) {
  for( Json::ValueIterator itr = json.begin(); itr != json.end(); ++itr ) {
    std::string entry = itr.key().asString();
    Ordinal k    = static_cast<Ordinal>( fieldNames[entry] );
    c0[k] = static_cast<Scalar>(
      json.get("Constant Coefficient",1.0).asDouble());        
    c1[k] = static_cast<Scalar>(
      json.get("Linear Coefficient",0.0).asDouble());
  }
}

inline void CovarianceMatrix_Exponential::initialize( 
  CovarianceMatrix::Map& fieldNames, Json::Value& json ) {
  for( Json::ValueIterator itr = json.begin(); itr != json.end(); ++itr ) {
    std::string entry = itr.key().asString();
    Ordinal k    = static_cast<Ordinal>( fieldNames[entry] );
    mantissae[k] = static_cast<Scalar>(json.get("Mantissa",1.0).asDouble());
    exponents[k] = static_cast<Scalar>(json.get("Exponent",0.0).asDouble());
  }
}

// SSC:  This is not generally correct as it assumes t0 = 0 and constant dt
inline void CovarianceMatrix_Linear::set_weights( const Domain* const domain, 
                                                  dArray& weights ) {
  Scalar dt = domain->get_dt();
  for( Ordinal p=0; p<weights.dim1(); ++p ) {                 
    for( Ordinal istep=0; istep<weights.dim2(); ++istep ) {
      for( Ordinal nc=0; nc<weights.dim3(); ++nc ) {
        weights[p][istep][nc] = c0[nc] + c1[nc]*istep*dt;
      }
    }
  } 
} 

// SSC:  This is not generally correct as it assumes t0 = 0 and constant dt
inline void CovarianceMatrix_Exponential::set_weights( 
  const Domain* const domain, dArray& weights ) {
  Scalar dt = domain->get_dt();
  for( Ordinal p=0; p<weights.dim1(); ++p ) {                 
    for( Ordinal istep=0; istep<weights.dim2(); ++istep ) {
      for( Ordinal nc=0; nc<weights.dim3(); ++nc ) {
        weights[p][istep][nc] = mantissae[nc]*std::exp(exponents[nc]*istep*dt);
      }
    }
  } 
} 

inline Shared<CovarianceMatrix>::Ptr
make_CovarianceMatrix( const vField& F, Json::Value& json, 
                       const DGM::Comm::Ptr comm ) {
  Shared<CovarianceMatrix>::Ptr cm;
  CovarianceMatrix::Map fieldNames;

  comm->cout() << "Making Covariance Matrix..." << endl;
  comm->cout() << "  Field " << F.get_name() << " has components: {";
  for( vField::size_type i=0; i<F.size(); ++i ) {
    fieldNames[F[i]->name] = i;
    comm->cout() << F[i]->name;
    if (i==F.size()-1)
      comm->cout() << "}" << endl;
    else
      comm->cout() << ",";
  }

  // Look for a subblock of "Response" called "Covariance Matrix"
  if( json.isMember("Covariance Matrix") ) {
 
    Json::Value& covmat = json["Covariance Matrix"];

    if( covmat.isMember("Field Components") ) {

       Json::Value& fieldComp = covmat["Field Components"];

       // Iterate over entries - check if in list of field names
       for( Json::ValueIterator itr = fieldComp.begin(); 
            itr != fieldComp.end(); ++itr ) {

         std::string entry = itr.key().asString();

         Json::Value &fc = *itr;

         if( fieldNames.find(entry) == fieldNames.end() ) { // Not Found
           throw DGM::exception("Covariance Matrix entry: " + entry + " is not "
           "the name of a Field component in the vField " + F.get_name());
         } 

         if( fc.isMember("Weighting Type") ) {
           std::string weightType = 
             fc.get("Weighting Type", "Exponential").asString();
   
           if( weightType == "Exponential" ) {
             cm.reset( new DGM::CovarianceMatrix_Exponential( F.size() ) );
           }
           else if( weightType == "Linear" ) {
             cm.reset( new DGM::CovarianceMatrix_Linear( F.size() ) );
           }
           // When we implement evaluation of symbolic expressions
           // they will go here
           // else if ( weightType == "Symbolic" ) 
           else {
             throw DGM::exception("Unhandled Weighting Type: " + weightType);
           }
           cm->initialize( fieldNames, fc );
         }
         else {
           throw DGM::exception("Weighting type of the covariance matrix "
                                "has not been specified."); 
         }
       } // end loop over field component entries
    } // If "Field Components" block exists
    else {  // No field components listed
      throw DGM::exception("Covariance Matrix block present in root.obj "
                           "Response, however, no FieldComponents block "
                           "was found within");
    }
  } // end if json.isMember("Covariance Matrix");
  return cm;  
}

} // namespace DGM

#endif // COVARIANCE_MATRIX_HPP

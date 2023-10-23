#ifndef DGM_BC_HPP
#define DGM_BC_HPP

/** \file BC.hpp
    \brief Boundary Condition (BC) declaration
    \author Scott Collis

    This module defines the general BC's interface that all derived
    physics modules use.  It also implements two specific BC instances that
    are useful for a wide range of physics.  These are:

    StateBC:  This sets a constant state on the boundary sides which means
              that a Dirichlet-type condition is set weakly through the
              numerical fluxes.

    FuncBC:   This is similar to StateBC, but uses a DGM::Parser to set
              a boundary condition that is can be function of spatial
              coordinates.
*/

// Documentation for local defines
#ifdef DGM_DOXYGEN
/// Define this at compile time to use a hash map for BCs
#define DGM_BC_USE_HASH_MAP
/// Specifies that we are using the Intel C++ compiler
#define ICC
#endif

// system includes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef DGM_BC_USE_HASH_MAP
#ifdef ICC
#include <hash_map>
#else  // !ICC
#include <hash_map.h>
namespace std {
  /// A hash function is needed (SGI provides one but GCC does not)
  template<> struct hash<string> {
    /// Operator interface for hashing
    size_t operator()(const string &str) const {
      unsigned long h = 0;
      const string::value_type* s = str.data();
      for (size_t len = str.length(); len > 0; --len, ++s)
        h = 5*h + (unsigned long)(*s);
      return size_t(h);
    }
  };
}
#endif  // ICC
#else   // !DGM_BC_USE_HASH_MAP
#include <map>
#endif  // DGM_BC_USE_HASH_MAP

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "vField.hpp"
#include "Side.hpp"

namespace DGM {

// forward declarations
class Bndry;
class Ctrl;

/// Boundary condition virtual base class
class BC : public DTK::BC<vField,dVector,Scalar,Ordinal> {

 public:

  typedef DGM::Size GlobalSize;     ///< global size type
  typedef DGM::Ordinal LocalSize;   ///< local size type

  std::string type;  ///< type of boundary condition

  typedef DGM::Shared<BC>::Ptr Ptr;         ///< smart pointer
  typedef const DGM::Shared<BC>::Ptr cPtr;  ///< const smart pointer

#ifdef DGM_BC_USE_HASH_MAP
  struct eqstr {
    bool operator()(const std::string &s1, const std::string &s2) const {
      return s1 == s2;
    }
  };
  typedef hash_map<std::string,BCPtr,hash<std::string>,BC::eqstr> db_type;
#else
  typedef std::map<std::string,Ptr> db_type;         ///< BC database
  typedef std::map<const std::string,cPtr> cdb_type; ///< const BC database
#endif
  typedef db_type::iterator db_itr;          ///< iterator into the database
  typedef db_type::const_iterator db_citr;   ///< c. iterator into the database

  /// constructor
  BC(const std::string t) : type(t) {}

  /// destructor
  virtual ~BC() {}

  /// \name BC Interface
  //@{
  /// apply the boundary condition at a specific time
  virtual void apply(const Scalar t, const vField &) {
    DGM_UNDEFINED;
  }
  /// apply a flux-type boundary condition
  virtual void apply_flux(const Scalar t, const vField &) {
    DGM_UNDEFINED;
  }
  /// apply a linearized boundary condition
  virtual void linear_apply(const Scalar t, const vField &, const vField &) {
    DGM_UNDEFINED;
  }
  /// apply the linearized flux-type boundary condition
  virtual void linear_apply_flux(const Scalar, const vField &,
                                 const vField &) {
    DGM_UNDEFINED;
  }
  /// apply the adjoint boundary condition
  virtual void adjoint_apply(const Scalar t, const vField &, const vField & ) {
    DGM_UNDEFINED;
  }
  /// apply the adjoint flux-type boundary condition
  virtual void adjoint_apply_flux(const Scalar, const vField &,
                                  const vField &) {
    DGM_UNDEFINED;
  }
  /// apply the matrix boundary condition at a specific time
  virtual void matrix_apply(const Scalar t, const vField &) {
    DGM_UNDEFINED;
  }
  /// apply a matrix flux-type boundary condition
  virtual void matrix_apply_flux(const Scalar t, const vField &) {
    DGM_UNDEFINED;
  }
  //@}
  /// return a Ctrl pointer if defined
  virtual Ctrl* ctrl() { return NULL; }
  /// return a constant Ctrl pointer if defined
  virtual const Ctrl* ctrl() const { return NULL; }

protected:

  /// provides a basic warning message
  static void warning(std::string msg) {
    DGM::Comm::World->warning(msg);
  }
  /// provides a basic error message
  static void error(std::string msg, int code=-1) {
    DGM::Comm::World->error(msg,code);
  }
  /// scan an input file stream for a left-bracket "{"
  static void scan_lb(ifstream &in ) {
    std::string token;
    if (!(in >> token)) error("BC syntax error:  Cannot read BC type");
    if ( token != "{" )
      error("BC syntax error:  Expected a \"{\"");
  }
  /// scan an input file stream for a right-bracket "}"
  static void scan_rb(ifstream &in ) {
    std::string token;
    while (token != "}" )
      if (!(in >> token)) error("BC syntax error:  Cannot find \"}\"");
  }
};

/// Generic State boundary condition class
class StateBC : public BC {
  dVector values;
 public:
  /// basic constructor
  StateBC(const std::string t, dVector &d) : BC(t) {
    // cout << "StateBC(dVector &, std::string)" << endl;
    values.resize( d.size() );
    values = d;
  }
  /// file constructor
  StateBC(const std::string t, ifstream &in, Ordinal ndof=0) : BC(t) {
    // cout << "StateBC(const std::string, ifstream &, Ordinal)" << endl;
    scan_lb(in);
    if (ndof==0)
      if (!(in >> ndof)) error("StateBC::Cannot read ndof");
    values.resize(ndof);
    for (Ordinal n=0; n<ndof; n++)
      if (!(in >> values[n])) error("StateBC::Cannot read values");
    scan_rb(in);
  }

  void apply(const Scalar, const vField &);
  void apply_flux(const Scalar, const vField &);

  void matrix_apply( const Scalar, const vField & );
  void matrix_apply_flux( const Scalar, const vField & );

  void adjoint_apply( const Scalar, const vField &, const vField & );
  void adjoint_apply_flux( const Scalar, const vField &, const vField & );
};

/// Generic function State boundary condition class
class FuncBC : public BC {
 protected:
  std::vector<std::string> expr; ///< the expression that defines this function
  dVector s;                     ///< storage for the evaluated expression
  /// evaluates the expression on boundary sides of the given vector Field
  void evaluate(const vField &F, const Scalar t=0.0);
  const bool initializeOnce;

 public:
  /// Constructor
  FuncBC(const std::string t, ifstream &in, Ordinal ndof=0,
         const bool initOnce=true) : BC(t), initializeOnce(initOnce) {
    //cout << "FuncBC(const std::string, ifstream &, Ordinal)" << endl;
    scan_lb(in);
    if (ndof==0)
      if (!(in >> ndof)) error("FuncBC::Cannot read ndof");
    expr.resize(ndof);
    std::string buffer;
    getline(in,buffer);     // eat the carriage return
    for (Ordinal n=0; n<ndof; n++) {
      getline(in,expr[n]);  // would it be better to use in << expr[0]
      //expr[n] += '\n';    // parser needs a newline
      std::string::size_type loc = expr[n].find(":=");
      if  (loc == std::string::npos) {
        stringstream msg;
        msg<<"FuncBC("<<t<<"):  Did not find := required for inline "
             "parser for field index "<<n;
        throw DGM::exception(msg.str());
      }
      // Move to the point right after the := token
      loc += 2;
      //cout << "dof = " << n << ", expression = " << expr[n] << endl;
      //expr[n] = expr[n].substr(loc);
      expr[n].erase(expr[n].begin(),expr[n].begin()+loc);
      string::size_type cont = std::string::npos;
      while ( (cont=expr[n].find("\\")) != std::string::npos) {
        expr[n].erase(expr[n].begin()+cont,expr[n].end());
        getline(in,buffer);
        expr[n] += buffer;
      }
      //cout << "dof = " << n << ", expression = " << expr[n] << endl;
    }
    scan_rb(in);
  }

  virtual void apply(const Scalar, const vField &);
  virtual void apply_flux(const Scalar, const vField &);

  virtual void adjoint_apply( const Scalar, const vField &, const vField & );
  virtual void adjoint_apply_flux( const Scalar, const vField &,
                                   const vField & );
};

} // namespace DGM

#endif // DGM_BC_HPP

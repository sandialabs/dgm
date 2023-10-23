#ifndef DGM_OPERATOR_HPP
#define DGM_OPERATOR_HPP

/** \file Operator.hpp
    \brief Operator class declaration
    \author Scott Collis
*/

#ifdef DGM_USE_EPETRA

// standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// DGM libraries
#include "Comm.hpp"
#include "vField.hpp"
#include "Domain.hpp"

// Trilinos includes
#ifdef DGM_PARALLEL
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Operator.h"

namespace DGM {

  //===========================================================================
  //                     Epetra_Operator
  //===========================================================================
  
  /// Epetra_Operator for Matrix Free computation
  class Operator : public virtual Epetra_Operator {
    Domain *domain;
    string label;
    const Epetra_Comm *comm;
    const Teuchos::RCP<const Epetra_Map> domain_map;
    const Teuchos::RCP<const Epetra_Map> range_map;
    mutable vField x, y;
  public:
    Operator(Domain *domain_, Epetra_Comm *comm_,
        Epetra_BlockMap *map_) :
          domain(domain_),
          label("Operator"),
          comm(comm_),
          domain_map(vField::BlockMap2PointMap(*map_)),
          range_map(domain_map), x(domain->get_comm()), y(domain->get_comm())
    {
      for (vField::size_type i=0; i<domain->U.size(); i++) {
        x.push_back( new Field( domain->U[i], domain->root,
            domain->U[i]->name) );
        y.push_back( new Field( domain->U[i], domain->root,
            domain->U[i]->name) );
      }
      x.set_name("x"); y.set_name("y");
      x.reset_storage(); y.reset_storage();
      x.zero(); y.zero();
    }
    virtual ~Operator() {
    }
    int SetUseTranspose(bool UseTranspose) { return -1; }
    int Apply(const Epetra_MultiVector &X, Epetra_MultiVector &Y) const {
      assert( X.NumVectors() == Y.NumVectors() );
      assert( X.MyLength() == Y.MyLength() );
      for (int i=0; i<X.NumVectors(); i++) {
        assert( x.ndof() == (Ordinal)X.MyLength() );
        assert( y.ndof() == (Ordinal)Y.MyLength() );
        std::copy( X[i], X[i] + X.MyLength(), x.elmt_data.data() );
        x.unpack();
        x.set_state(Element::Transform);
        x.backward_transform();
        domain->action( x, y );
        y.pack();
        std::copy( y.elmt_data.data(), y.elmt_data.data() + y.ndof(), Y[i] );
        y.zero();
      }
      return 0;
    }
    int ApplyInverse(const Epetra_MultiVector &X, Epetra_MultiVector &Y) const {
      cout << "Operator::ApplyInverse " << label << endl;
      return -1;
    }
    Scalar NormInf() const { return 0.0; }
    const char *Label() const { return label.c_str(); }
    bool UseTranspose() const { return false; }
    bool HasNormInf() const { return false; }
    const Epetra_Comm &Comm() const { return *comm; }
    const Epetra_Map &OperatorDomainMap() const { return *domain_map; }
    const Epetra_Map &OperatorRangeMap() const { return *range_map; }
  };
  
} // namespace DGM
  
#endif  // DGM_USE_EPETRA

#endif  // DGM_DOMAIN_HPP

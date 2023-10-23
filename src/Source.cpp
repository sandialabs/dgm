/** \file Source.cpp
    \brief DGM Source base class implementation
    \author Scott Collis
*/

// DGM includes
#include "Source.hpp"

namespace DGM {

void FuncSource::apply( const Scalar t, const vField &, vField &F ) {
  assert( (size_t)F.size() == expr.size() );
  evaluate(F,t);
  Ordinal n=0;
  dVector wk;
  for (vField::size_type i=0; i<F.size(); ++i) {
    for (LocalSize e=0; e<F[i]->ne; ++e) {   // loop over elements
      Element *E = F[i]->el[e];              // local element
      wk.alias(s,n,E->qtot);
      E->u -= wk;                            // put on LHS
      n += E->qtot;
    }
  }
}

void FuncSource::evaluate(const vField &F, const Scalar t) {
  if (s.size() != 0 && initializeOnce) return;
  //cout<<"FuncSource::evaluate(...)"<<endl;
  //cout<<"F.size() = "<<F.size()<<endl;
  parser_init();  // make sure that the parser is initialized
  //cout<<"parser_init() complete"<<endl;
  //cout<<"expr.size() = "<<expr.size()<<endl;
  assert( (size_t)F.size() == expr.size() );
  // WARNING:  this is the size of the entire vField
  if(s.size()==0) s.resize(F.qtot());
  //cout<<"s.size() = "<<s.size()<<endl;
  Ordinal n=0;
  dVector wk;
  if (F.nsd() == 1) {
    for (vField::size_type i=0; i<F.size(); ++i) {
      for (LocalSize e=0; e<F[i]->ne; e++) {   // loop over elements
        Element *E = F[i]->el[e];              // local element
        wk.alias(s,n,E->qtot);
        Parser::VectorFunction f("x", "t", expr[i]);
        f.evaluate( E->C->x, wk, t);
        n += E->qtot;
      }
    }
  } else if (F.nsd() == 2) {
    for (vField::size_type i=0; i<F.size(); ++i) {
      for (LocalSize e=0; e<F[i]->ne; ++e) {   // loop over elements
        Element *E = F[i]->el[e];              // local element
        wk.alias(s,n,E->qtot);
        Parser::VectorFunction f("x", "y", "t", expr[i]);
        f.evaluate( E->C->x, E->C->y, wk, t);
        n += E->qtot;
      }
    }
  } else if (F.nsd() == 3) {
    for (vField::size_type i=0; i<F.size(); ++i) {
      for (LocalSize e=0; e<F[i]->ne; ++e) {   // loop over elements
        Element *E = F[i]->el[e];              // local element
        wk.alias(s,n,E->qtot);
        Parser::VectorFunction f("x", "y", "z", "t", expr[i]);
        f.evaluate( E->C->x, E->C->y, E->C->z, wk, t );
        n += E->qtot;
      }
    }
  } else
    error("FuncSource::evaluate(...) Illegal value of F.nsd()");
  parser_clean();
  //cout<<"FuncSource::evaluate(...) complete"<<endl;
}

} // namespace DGM

/** \file BC.cpp
    \brief Boundary Condition (BC) implementation
    \author Scott Collis

    This module implements general BC's that all modules can take advantage of.
*/

#include "BC.hpp"
#include "Boundary.hpp"

namespace DGM {

//=============================================================================
//            S t a t e   B o u n d a r y   C o n d i t i o n
//=============================================================================

void StateBC::apply(const Scalar t, const vField &F) {
  if (F.size() != values.size())
    cout << F.size() << " " << values.size() << endl;
  assert( F.size() == values.size() );
  for (LocalSize n=0; n<F[0]->nbc; ++n) { // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = values[i];
      }
    }
  }
}

void StateBC::apply_flux(const Scalar t, const vField &F) {
  //cout << "StateBC::apply_flux(...)"<<endl;
  assert( F.size() == values.size() );
  for (LocalSize n=0; n<F[0]->nbc; ++n) {      // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        //F[i]->bc[n]->B->u = 0.0;       // old behavior [ssc]
        for (Ordinal q=0; q<F[i]->bc[n]->S->qtot(); ++q)
          F[i]->bc[n]->B->u[q] = -F[i]->bc[n]->S->u[q];
      }
    }
  }
}
// agerste: -> needs testing, I don't actually use this kind of BC
void StateBC::matrix_apply( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = values[i];
      }
    }
  }
}
// agerste: -> needs testing, I don't actually use this kind of BC
void StateBC::matrix_apply_flux( const Scalar t, const vField &F ) {
  for (LocalSize n=0; n<F[0]->nbc; ++n) {  // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        F[i]->bc[n]->B->u = F[i]->bc[n]->S->u;
      }
    }
  }
}


/* For the adjoint state/flux boundary, we assume zero fluctuation/zero
   traction for the adjoint state/flux BC a little hardwired [gqchen]
*/
void StateBC::adjoint_apply(const Scalar t, const vField &state,
                            const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n) {  // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0;
      }
    }
  }
}


void StateBC::adjoint_apply_flux(const Scalar t, const vField &state,
                                 const vField &adjoint) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n) {  // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0;
      }
    }
  }
}

//=============================================================================
//         F u n c t i o n   B o u n d a r y   C o n d i t i o n
//=============================================================================

void FuncBC::apply(const Scalar t, const vField &F) {
  //cout << "FuncBC::apply(...)" << endl;
  assert( (size_t)F.size() == expr.size() );
  evaluate(F,t);
  Ordinal start=0;
  dVector wk;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {      // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        Side *B = F[i]->bc[n]->B;
        wk.alias(s,start,B->qtot());
        B->u = wk;
        start += B->qtot();
      }
    }
  }
}

void FuncBC::apply_flux(const Scalar t, const vField &F) {
  //cout << "FuncBC::apply_flux(...)"<<endl;
  for (LocalSize n=0; n<F[0]->nbc; ++n) {      // loop over field boundaries
    if (F[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<F.size(); ++i) {
        //F[i]->bc[n]->B->u = 0.0;       // old behavior [ssc]
        for (Ordinal q=0; q<F[i]->bc[n]->S->qtot(); ++q)
          F[i]->bc[n]->B->u[q] = -F[i]->bc[n]->S->u[q];
      }
    }
  }
}

void FuncBC::adjoint_apply( const Scalar t, const vField &state,
                            const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n) {   // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0;
      }
    }
  }
}

void FuncBC::adjoint_apply_flux( const Scalar t, const vField &state,
                                 const vField &adjoint ) {
  for (LocalSize n=0; n<adjoint[0]->nbc; ++n) {  // loop over field boundaries
    if (adjoint[0]->bc[n]->type == type ) {
      for (vField::size_type i=0; i<adjoint.size(); ++i) {
        adjoint[i]->bc[n]->B->u = 0;
      }
    }
  }
}

void FuncBC::evaluate(const vField &F, const Scalar t) {
  if (s.size() != 0 && initializeOnce) return;
  // cout<<"FuncSource::evaluate(...)"<<endl;
  // cout<<"F.size() = "<<F.size()<<endl;
  parser_init();  // make sure that the parser is initialized
  // cout<<"parser_init() complete"<<endl;
  // cout<<"expr.size() = "<<expr.size()<<endl;
  assert( (size_t)F.size() == expr.size() );
  LocalSize length = 0;
  for (LocalSize n=0; n<F[0]->nbc; ++n)
    if (F[0]->bc[n]->type == type )
      for (vField::size_type i=0; i<F.size(); ++i)
        length += F[i]->bc[n]->B->qtot();
  if(s.size()==0) s.resize(length);
  // cout<<"s.size() = "<<s.size()<<endl;
  Ordinal start=0;
  dVector wk;
  if (F.nsd() == 1) {
    cout <<"FuncBC::evaluate not implemented for nsd=1" <<endl;
  } else if (F.nsd() == 2) {
    for (LocalSize n=0; n<F[0]->nbc; ++n) {
      if (F[0]->bc[n]->type == type ) {
        for (vField::size_type i=0; i<F.size(); ++i) {
          Side *B = F[i]->bc[n]->B;
          Element *E = F[i]->el[B->leid()];
          const Ordinal qtot(B->qtot());
          Point *pside = new Point[qtot];
          E->get_side_coordinates( B->id(), pside );
          dVector x(qtot);
          dVector y(qtot);
          for (Ordinal j=0; j<qtot; ++j) {
            x[j] = pside[j].x;
            y[j] = pside[j].y;
          }
          wk.alias(s,start,qtot);
          Parser::VectorFunction f("x", "y", "t", expr[i]);
          f.evaluate( x, y, wk, t);
          start += B->qtot();
          delete[] pside;
        }
      }
    }
  } else if (F.nsd() == 3) {
    //cout <<"FuncBC::evaluate not implemented for nsd=3" <<endl;
    for (LocalSize n=0; n<F[0]->nbc; ++n) {
      if (F[0]->bc[n]->type == type ) {
        Side *B = F[0]->bc[n]->B;
        Element *E = F[0]->el[B->leid()];
        const Ordinal qtot(B->qtot());
        Point *pside = new Point[qtot];
        E->get_side_coordinates( B->id(), pside );
        dVector x(qtot);
        dVector y(qtot);
        dVector z(qtot);
        for (Ordinal j=0; j<qtot; ++j) {
          x[j] = pside[j].x;
          y[j] = pside[j].y;
          z[j] = pside[j].z;
        }
        wk.alias(s,start,qtot);
        Parser::VectorFunction f("x", "y", "z", "t", expr[0]);
        f.evaluate( x, y, z, wk, t);
        // for (Ordinal q=0; q<qtot; ++q)
        //   cout<<x[q]<<"  "<<y[q]<<"  "<<z[q]<<"  "<<wk[q]<<endl;
        start += B->qtot();
        delete[] pside;
      }
    }
  } else {
    error("FuncBC::evaluate(...) Illegal value of F.nsd()");
  }
  parser_clean();
  // cout<<"FuncBC::evaluate(...) complete"<<endl;
}

} // namespace DGM

/*=============================================================================
  Module:     Reo Linearized Burgers Module

  Author:     Scott Collis

  Copyright:  (c) 2008 Sandia National Laboratories
=============================================================================*/

/** \file LinBurgers.cpp
    \brief Linearized Burgers implementation
*/

// local includes
#include "ReoConfig.hpp"
#include "LinBurgers.hpp"
#include "BurgersIC.hpp"
#include "BurgersBC.hpp"

namespace Reo {

// if defined then perform a projection when computing the diffusive flux
#define REO_PROJECT_DIFF_FLUX

/// Constructor
LinBurgers::LinBurgers( DGM::ArgList &args, const State *base_,
                        const DGM::Comm::Ptr comm_) :
  Burgers(args,comm_),
  base_state(dynamic_cast<const Burgers_State*>(base_)),
  Ubase(comm_)  {

  // make auxiliary Fields using copy constructor
  Ubase.push_back( new Field(U[0], root, U[0]->name) );

  zero_all_fields();
}

void LinBurgers::zero_all_fields() {
  Burgers::zero_all_fields();
  Ubase.zero();
}

void LinBurgers::time_derivative( vField &Us, vField &Uf ) {
#ifdef REO_BURGERS_NO_CONVECTION
  Uf.zero();
#else
  convection( Us, Uf );
#endif
  diffusion( Us, Uv, Uf );
  add_source( Us, Uf );
  project( Uf );
}

void LinBurgers::prestep( vField &F, const Ordinal istep,
                          const Ordinal sstep, const Scalar time ) {
  // cout<<"LinBurgers:  Loaded Ubase "<<istep<<" "<<sstep<<endl;
  base_state->load_field( Ubase, istep, sstep );
  const_cast<Control*>(base_state->get_control())->set_data( istep, sstep );
}

void LinBurgers::poststep( vField &F, const Ordinal istep,
                           const Ordinal sstep, const Scalar time ) {
}

/// Compute the convection term in the form:
/**
   \f[ \int_{\Omega_e} w ( (u u')_{,x} ) d\Omega +
   \int_{\Gamma_e} w ( \hat F'_n - F'_n ) d\Gamma  \f]
*/
void LinBurgers::convection( vField &Uf, vField &Ff ) {
  // nonlinear state
  Ubase.fill_sides();
  Ubase.share_sides();
  const_cast<Burgers_State*>(base_state)->enforce_bc(Ubase);

  // linear state
  Uf.fill_sides();
  Uf.share_sides();
  enforce_bc(Uf);

  convective_flux(Ubase, Uf, Ff );

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];           // linearized state
    Element *F = Ff[0]->el[e];           // flux
    Element *S = Ubase[0]->el[e];        // base state
    dvmul( S->u, U->u, F->u );
    U->gradient( F->u, F->u );
    U->lift( F, F->u ); // add side fluxes to interior
  }
}

Scalar LinBurgers::dfabs( Scalar x ) {
  if (x > 0.0)
    return 1.0;
  else if (x < 0.0)
    return -1.0;
  else
    return 0.0;
}

/// Lax-Friedrichs flux
void LinBurgers::convective_flux(const vField &Ub, vField &Uf, vField &Ff) {
  Scalar nx;
  Scalar sl, sr, lmax, dlmax, lf_flux;
  Scalar bl, br, fl, fr;

  for (LocalSize e=0; e<Uf[0]->ne; e++) {
    Element *U = Uf[0]->el[e];
    Element *F = Ff[0]->el[e];
    const Element *B = Ub[0]->el[e];
    for (LocalSize i=0; i<U->nSides(); i++) {
      if (U->side[i]->link) {
        for (LocalSize q=0; q<U->side[i]->qtot(); q++) {
          nx = U->side[i]->nx(q);

          sl = U->side[i]->u[q];     // linear state
          bl = B->side[i]->u[q];     // base state
          fl = bl*nx*sl;

          sr = U->side[i]->link->u[q];  // linear state
          br = B->side[i]->link->u[q];  // base state
          fr = br*nx*sr;

#ifdef REO_BURGERS_HACK_FLUX
          lmax = 0.5;
          dlmax = 0.0;
#else
#ifdef REO_BURGERS_AVG_FLUX
          lmax = 0.5*(fabs(bl)+fabs(br));
          dlmax = 0.5*(dfabs(bl)*sl + dfabs(br)*sr);
#else
#ifdef REO_BURGERS_CENTRAL_FLUX
          lmax = 0.0;
          dlmax = 0.0;
#else
          lmax = max(fabs(bl),fabs(br));
          dlmax = 0.0;
#endif
#endif
#endif
          // Lax-Friedrichs flux
          lf_flux = 0.5*(fl + fr + lmax*(sl - sr) + dlmax*(bl - br));

          // put numerical flux on the F field sides
          F->side[i]->u[q]       =  lf_flux;
          F->side[i]->link->u[q] = -lf_flux;

          // put actual flux on the U field sides
          U->side[i]->u[q]       =  fl;
          U->side[i]->link->u[q] = -fr;
        }
      }
    }
  }
}

//===========================================================================
//                        BC database management
//===========================================================================

#if 0

// Load up the available BC types
void LinBurgers::setup_BCdb( ) {

  // set default BC types
  BC_db["D"].reset( new DirichletBC("D", 0.0) );
  BC_db["F"].reset( new NeumannBC("F", 0.0) );
  BC_db["N"].reset( new NeumannBC("N", 0.0) );
  BC_db["O"].reset( new OutflowBC("O") );
  BC_db["R"].reset( new RobinBC("R",0.0) );

  // read new BC types from file
  string fname = root+".bct";
  ifstream in(fname.c_str());
  if (in) LinBurgers::read_BCdb( in );   // database of active BC types
}

void LinBurgers::read_BCdb( ifstream &in ) {
  // cout << "LinBurgers::read_BCdb( ifstream &in )" << endl;
  string tag;
  BC *pbc;
  while ( (pbc = LinBurgers::make_BC(in,tag)) ) {
    if ( BC_db.find(tag) != BC_db.end() )
      comm->cout() << "LinBurgers::read_BCdb() Overriding BC type \""
                   << tag << "\"." << endl;
    BC_db[tag].reset( pbc );
  }
}

BC* LinBurgers::make_BC( ifstream &in, string &tag ) {
  // cout << "LinBurgers::make_BC(ifstream &in, string &tag)" << endl;
  string code;
  if (!(in >> code)) return NULL;
  code = lowerCase(code);
  if (code == "dirichlet") {
    if (!(in >> tag)) error("LinBurgers::make_BC() Cannot read Dirichlet tag");
    return new DirichletBC(tag,in);
  } else if (code == "neumann") {
    if (!(in >> tag)) error("LinBurgers::make_BC()  Cannot read Neumann tag");
    return new NeumannBC(tag,in);
  } else if (code == "robin") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read Robin tag");
    return new RobinBC(tag,in);
  } else if (code == "dirichletcontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read DirichletControl tag");
    return new DirichletControlBC(tag,in);
  } else if (code == "neumanncontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read NeumannControl tag");
    return new NeumannControlBC(tag,in);
  } else if (code == "robincontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read RobinControl tag");
    return new RobinControlBC(tag,in);
  } else if (code == "steadydirichletcontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read SteadyDirichletControl tag");
    return new SteadyDirichletControlBC(tag,in);
  } else if (code == "steadyneumanncontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read SteadyNeumannControl tag");
    return new SteadyNeumannControlBC(tag,in);
  } else if (code == "steadyrobincontrol") {
    if (!(in >> tag))
      error("LinBurgers::make_BC() Cannot read SteadyRobinControl tag");
    return new SteadyRobinControlBC(tag,in);
  } else {
    error("LinBurgers::make_BC() Illegal BC type:  "+code,-1);
  }
  return NULL;
}

/// Construct source terms
Source* LinBurgers::make_Source( ifstream &in, string &tag ) {
  // cout << "LinBurgers::make_Source" << endl;
  string code;
  if (!(in >> code)) return NULL;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("LinBurgers::Cannot read ConstSource tag");
    return new ConstSource(tag,in,1);
  } else if (lowerCase(code) == "distributedcontrol") {
    if (!(in >> tag)) error("LinBurgers::Cannot read distributedcontrol tag");
    return new DistributedControl(tag, in, U);
  } else if (lowerCase(code) == "steadydistributedcontrol") {
    if (!(in >> tag))
      error("LinBurgers::Cannot read steady distributedcontrol tag");
    return new SteadyDistributedControl(tag, in, U);
  } else {
    error("LinBurgers::make_Source() Illegal Source type");
  }
  return NULL;
}

// Add source terms
void LinBurgers::add_source(const vField &Us, vField &Ur) {
  // cout << "LinBurgers::add_source(vField &)" << endl;
  for (Source::db_itr i=Source_db.begin(); i!= Source_db.end(); ++i) {
    // cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur );
  }
}

#endif

/// Set the field from a file
void LinBurgers::set_ic(vField &F, string ext) {
  t = 0.0; step = 0;
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Could not open initial condition " << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
  getline(in,buffer);
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile,F);
  } else if (lowerCase(code) == "shock") {
    ShockIC shock;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += shock.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "cockburnshock") {
    CockburnShockIC shock;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += shock.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else if (lowerCase(code) == "step") {
    StepIC ic;
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        F[0]->el[e]->u[q] += ic.eval( (*F[0]->el[e]->C)[q] );
      }
    }
  } else {
    comm->error("LinBurgers:set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  project( F ); // project field to the polynomial space
#endif
}

} // namespace Reo

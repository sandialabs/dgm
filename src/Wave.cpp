/*=============================================================================
  Module:     Wave Module

  Authors:    Guoquan Chen & Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file Wave.cpp
    \brief DGM wave equation module impementation
    \author Scott Collis
*/

// system includes
#include <ctime>

// DGM includes
#include "TimeInt.hpp"

// local includes
#include "Reo.hpp"
#include "Wave.hpp"
#include "Wavetype.hpp"

namespace Reo {

/// constructor
Wave::Wave( DGM::ArgList &args, const DGM::Comm::Ptr comm_ ) :
  Domain(args,comm_), gamma(1.4), Up(comm_), Um(comm_) {

  Ordinal p, q;
  p = params["p"];                     // polynomial order
  if ( !(q=params["q"]) ) q = p + 2;   // number of quadrature points
  nsd = params["nsd"];                 // number of space dimensions

  parse_args(args);

  gamma = params.get("gamma",gamma);   // ratio of specific heats

  setup_BCdb();                        // make the BC database 

  vector<string> field_names;          // Field names
  field_names.push_back("R");

  // build a Field of Elements, Faces, and Sides
  if (params["imesh"]) {
    Mesh mesh(params);
    U.push_back( new Field(p, q, mesh, root, field_names[0],
                           Field::FULL, comm));
    partition = U[0]->partition;
  } else if (params["bmesh"]) {
    U.push_back( new Field(p, q, root, field_names[0], partition, 1,
                           Reo::NumEqntype, p2i(WAVE), comm ) );
  } else {
    U.push_back( new Field(p, q, root, field_names[0], partition, comm ) );
  }

  // set some additional domain parameters
  ne = U[0]->ne;
  nsd = U[0]->nsd();

#ifdef REO_USE_GETSIDEMAPS
  setup_side_maps();
#endif

  if (nsd == 1) {
    Nfields = 2;
    field_names.push_back("U");
  } else if (nsd == 2) {
    Nfields = 3;
    field_names.push_back("U");
    field_names.push_back("V");
  } else if (nsd == 3) {
    Nfields = 4;
    field_names.push_back("U");
    field_names.push_back("V");
    field_names.push_back("W");
  } else {
    cerr << "Illegal value for nsd = " << nsd << " in Wave::Wave" << endl;
    comm->exit(DGM::FAILURE);
  }

  // build the rest of the vector field
  for (vField::size_type i=1; i<Nfields; i++)
    U.push_back( new Field( U[0], root, field_names[i] ) );

  // make auxiliary Fields using copy constructor
  for (vField::size_type i=0; i<Nfields; i++) {
    Ut.push_back( new Field( U[0], root, field_names[i]) );
    // make the mean flow Field
    Um.push_back( new Field( U[0], root, field_names[i]) );
    // make the primitive variable solution field
    Up.push_back( new Field( U[0], root,field_names[i] ) );
  }

  // allocate workspace
  wk1.resize(10*max(Lmax(),Qmax()));
  wk2.resize(10*max(Lmax(),Qmax()));

  // make sure that storage is initialized
  zero_all_fields();

  // set default Mach number and Prandtl numbers (SSC: why is this hardwired?)
  Ma = 1.0;  // SSC:  used to be 0.3, changed to 1
  Pr = 1.0;

  // make responseiEul object
  response = Response::factory(U, this);

  setup_Sourcedb();

  set_TimeInt();
}

/// Parse parameters from the argument list
void Wave::parse_args(DGM::ArgList &args) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-gamma") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["gamma"] = atof(value.c_str());
      } else if (name == "-help") {
        params["showUsage"] = 1;
        showUsage();
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

// this version is more useful since it takes a string as input
int Wave::plot(const string &rst) {
  string fname, name(rst);
  char buf[80];
  read( rst, Up );
  name.erase(name.find(".rst"));  // erase extension
  sprintf(buf,"%s.dat",name.c_str()); fname = buf;
  // WARNING: should collect all information on the master if parallel...
  if (DGM::Comm::World->Master()) Up.tecplot(fname,"Solution");
#if 0
  // output to plot3d multi-grid format
  sprintf(buf,"%s.xyz",name.c_str()); fname = buf;
  if (DGM::Comm::World->Master()) U.plot3d_xy(fname,"Solution");
  sprintf(buf,"%s.q",name.c_str()); fname = buf;
  if (DGM::Comm::World->Master()) U.plot3d_q2(fname,"Solution");
#endif
  // compute_vorticity();
  // WARNING: should collect all information on the master if parallel...
  // sprintf(buf,"%s.aux.dat",name.c_str()); fname = buf;
  // if (DGM::Comm::World->Master()) Ut.tecplot(fname,"Vorticity");
  return 0;
}

// override Domain::solve()
int Wave::solve() {
  Format sci(4); sci.scientific().width(12);

  if (DGM::Comm::World->Master()) cout << "Title = " << title << endl;

  set_mean(Um);    // set the mean flow field
  set_ic(Up);      // set the initial condition (primitive field)
  make_U(U,Um,Up); // make the initial condition (solution variable)

  if (step==0) write(step,U);

#ifndef DGM_PARALLEL
  Up.tecplot("ic.dat","Initial Condition");
#endif

  // estimate the stability condition
  // if (DGM::Comm::World->Master()) cout<<"CFL = "<<compute_cfl( U )<<endl;

  comm->cout() << "Advancing solution " << Nt << " time steps" << endl;

  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  Stopwatch cpu; cpu.start();
  for (lstep=1; lstep<=Nt; lstep++) {
    step++;
    time_int->advance(this);
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
    if (DGM::Comm::World->Master()) printf("%5lld %12.4e %12.4e\n",
                                           (long long)step,t,ctime);
    if (step%Ntout==0)  {
      get_Up(Up,Um,U);
      write(step, Up);
      Up.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0;
  DGM::Comm::World->SumAll( &ttime, &atime, 1 );  // average cpu time
  DGM::Comm::World->SumAll( &stime, &otime, 1 );  // standard deviation
  int n = max(1,cnt*DGM::Comm::World->NumProc());
  if (DGM::Comm::World->Master()) {
    cout << "Average time per step: " << sci(atime/n)
         << ", standard deviation:  "
         << sci( ::sqrt((n*otime-atime*atime)/(n*max(int(n-1),1))) ) << endl;
  }
#endif
  get_Up(Up,Um,U);
  write(root+".rst",U);
  write(step, Up);
  if (step%Ntout!=0) Up.norm();
#ifndef DGM_PARALLEL
  get_Up(Up,Um,U);
  Up.tecplot("out.dat","Final solution");
#endif
  return 0;
}

void Wave::time_derivative( vField &Us, vField &Uf ) {
  convection( Us, Uf );
  add_source( Us, Uf );
  project( Uf );
}

Scalar Wave::set_time_step(vField&U) {
  Scalar cfl = dt;
  return cfl;
}

void Wave::convection( vField &Us, vField &Uf ) {
  Element *U[3], *F[3],*Fm[3];
  dVector u1, u2, u3, Fx1, Fx2, Fx3, Fx4, Fy1, Fy2, Fy3, Fy4, d;
  Scalar w[4], u[2], c;

  Us.fill_sides();
  Um.fill_sides();    // fill side for the mean flow field
  Um.share_sides();
  enforce_mean_state_bc(Um);
  enforce_bc(Us);
  Us.share_sides();
  convective_flux( Us, Uf );

  for (LocalSize e=0; e<Us[0]->ne; e++) {

    // local version of the state
    U[0] = Us[0]->el[e];
    U[1] = Us[1]->el[e];
    U[2] = Us[2]->el[e];

    // local version of the flux
    F[0] = Uf[0]->el[e];
    F[1] = Uf[1]->el[e];
    F[2] = Uf[2]->el[e];

    // local version of the mean flow
    Fm[0] = Um[0]->el[e];
    Fm[1] = Um[1]->el[e];
    Fm[2] = Um[2]->el[e];

    const Ordinal qtot = Us[0]->el[e]->qtot;

    Fx1.alias(wk1,0,qtot);
    Fx2.alias(wk1,qtot,qtot);
    Fx3.alias(wk1,2*qtot,qtot);
    Fy1.alias(wk1,3*qtot,qtot);
    Fy2.alias(wk1,4*qtot,qtot);
    Fy3.alias(wk1,5*qtot,qtot);
    d.alias(wk1,6*qtot,qtot);

    // For simple case, the mean flow is uniform flow.
    // Since A(au), B(au) constant matrix
    // we can get F(u(x)),x = A(au) u,x
    //            G(u(x)),y = B(au) u,y
    // In future, if the mean flow varies spatially we should use
    //     Set    F(u(x)),x = (A(au) u),x
    //            G(u(x)),y = (B(au) u),y

    for (LocalSize q=0; q<qtot; q++) {
      //
      // AMinvQ = vector([q[2], (-u[1]^2+c^2)*q[1]+2*u[1]*q[2],
      //                 -u[1]*u[2]*q[1]+u[2]*q[2]+u[1]*q[3]])
      for(vField::size_type i=0;i<Nfields;i++) w[i]=U[i]->u[q];
      //rho = Fm[0]->u[q];
      u[0]= Fm[1]->u[q];
      u[1]= Fm[2]->u[q];
      c = one / Ma;

      // Need to modify: In the Jacobian matrix for mean flow: dp/drho != c^2
      // [gqchen]

      // So, $U$ is actually the Quasi-conservative variables and for zero
      // base flow:
      //   \rho'_{,t} + (\rho u')_{,x} + {\rho v'}_{,y} = 0
      //   (\rho u')_{,t} + (c^2 \rho')_{,x} = 0
      //   (\rho u')_{,t} + (c^2 \rho')_{,y} = 0

      Fx1[q] = w[1];
      Fx2[q] = -w[0]*u[0]*u[0]+w[0]*c*c+2.0*u[0]*w[1];
      Fx3[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

      Fy1[q] = w[2];
      Fy2[q] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
      Fy3[q] = -w[0]*u[1]*u[1]+w[0]*c*c+2.0*u[1]*w[2];
    }

    U[0]->gradient(Fx1, F[0]->u, 'x');
    U[0]->gradient(Fy1, d, 'y');
    dvadd(d,F[0]->u);

    U[1]->gradient(Fx2, F[1]->u, 'x');
    U[1]->gradient(Fy2, d, 'y');
    dvadd(d,F[1]->u);

    U[2]->gradient(Fx3, F[2]->u, 'x');
    U[2]->gradient(Fy3, d, 'y');
    dvadd(d,F[2]->u);

    // add the surface contribution
    for (vField::size_type i=0; i<Nfields; i++)
      U[i]->lift( F[i], F[i]->u );
  }
}

// For descriptions of the numerical fluxes
// See:  E.F. Toro, "Riemann Solvers and Numerical Methods for Fluid
//       Dynamics," 2nd Edition, Springer, 1999, p. 305.
void Wave::convective_flux(vField &Us, vField &Uf) {
  // cout << "Wave::convective_flux()" << endl;
  flux_type flux = LaxFriedrichs; // StegerWarming; // vanLeer;
#ifdef REO_USE_GETSIDEMAPS
  iVector mapl, mapr;
#endif
  dVector sl(Nfields), sr(Nfields), f(Nfields);
  dVector slm(Nfields), srm(Nfields);
  Scalar ulm, clm;
  Scalar urm, crm;
  vector<Side *> Ssl(Nfields), Ssr(Nfields);
  vector<Side *> Sbl(Nfields), Sbr(Nfields);        // base flow field side
  vector<Side *> Sfl(Nfields), Sfr(Nfields);
  dVector fpl(Nfields), fmr(Nfields),lam(Nfields);
  Scalar lmax, c;
  Scalar w[4], u[2];
  dVector Fx(Nfields), Fy(Nfields);

  for (LocalSize e=0; e<Us[0]->ne; e++) {                // loop over elements
    Element* U = Us[0]->el[e];
    for (LocalSize i=0; i<Us[0]->el[e]->nSides(); i++) { // loop over sides
      if (Us[0]->el[e]->side[i]->master()) {             // master side
        // localize the state, base and flux side pointers
        for (vField::size_type ni=0; ni<Nfields; ni++) {
          Ssl[ni] =  Us[ni]->el[e]->side[i];        // left state side
          Ssr[ni] =  Us[ni]->el[e]->side[i]->link;  // right state side
          Sfl[ni] =  Uf[ni]->el[e]->side[i];        // left flux side
          Sfr[ni] =  Uf[ni]->el[e]->side[i]->link;  // right flux side
          Sbl[ni] = Um[ni]->el[e]->side[i];         // left base side
          Sbr[ni] = Um[ni]->el[e]->side[i]->link;   // right base side
        }
#ifdef REO_USE_GETSIDEMAPS
        get_side_maps( Ssl[0], Ssr[0], mapl, mapr );
#endif

        const Ordinal qtot = Ssl[0]->qtot();      // number of quad pts on side
        for (LocalSize q=0; q<qtot; q++) {        // loop over side quad-pts
#ifdef REO_USE_GETSIDEMAPS
          const LocalSize ql = mapl[q];
          const LocalSize qr = mapr[q];
#else
          const LocalSize ql = U->sideMap(Ssl[0], q);
          const LocalSize qr = U->sideMap(Ssr[0], q);
#endif

          const Scalar nx = Us[0]->el[e]->side[i]->nx(ql);
          const Scalar ny = Us[0]->el[e]->side[i]->ny(ql);

          // compute normal flux from interior (left)

          // From solution U
          for(vField::size_type k=0;k<Nfields;k++)
            sl[k] = Ssl[k]->u[ql];

          // normal velocity -- mean flow
          ulm = Sbl[1]->u[ql]*nx +Sbl[2]->u[ql]*ny;
          //ul = Ssl[1]->u[ql]*nx +Ssl[2]->u[ql]*ny;

          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssl[k]->u[ql];
          //rho = Sbl[0]->u[ql];
          u[0]= Sbl[1]->u[ql];
          u[1]= Sbl[2]->u[ql];
          c = one/Ma;

          // Assume d(p)/d(rho)=c^2, c is from mean flow. Need to modify: In
          // the Jacobi matrix from mean flow dp/drho != c^2 [gqchen]
          Fx[0] = w[1];
          Fx[1] = -w[0]*u[0]*u[0]+w[0]*c*c+2.0*u[0]*w[1];
          Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

          Fy[0] = w[2];
          Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fy[2] = -w[0]*u[1]*u[1]+w[0]*c*c+2.0*u[1]*w[2];

          Ssl[0]->u[ql] = Fx[0]*nx + Fy[0]*ny;
          Ssl[1]->u[ql] = Fx[1]*nx + Fy[1]*ny;
          Ssl[2]->u[ql] = Fx[2]*nx + Fy[2]*ny;

          // compute normal flux from exterior (right)

          // adjacent state
          // Primitive form
          for(vField::size_type k=0;k<Nfields;k++)
            sr[k] = Ssr[k]->u[qr];

          urm = Sbr[1]->u[qr]*nx +Sbr[2]->u[qr]*ny;
          // ur = Ssr[1]->u[qr]*nx +Ssr[2]->u[qr]*ny;

          // Local sound speed from mean flow
          for(vField::size_type k=0;k<Nfields;k++) w[k]=Ssr[k]->u[qr];

          // rho = Sbr[0]->u[ql];
          u[0]= Sbr[1]->u[ql];
          u[1]= Sbr[2]->u[ql];
          c = one/Ma;

          // Assume d(p)/d(rho) =c^2, c is from mean flow. Need to modify: In
          // the Jacobi matrix from mean flow dp/drho != c^2 [gqchen] code
          Fx[0] = w[1];
          Fx[1] = -w[0]*u[0]*u[0]+w[0]*c*c+2.0*u[0]*w[1];
          Fx[2] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];

          Fy[0] = w[2];
          Fy[1] = -u[0]*u[1]*w[0]+u[1]*w[1]+u[0]*w[2];
          Fy[2] = -w[0]*u[1]*u[1]+w[0]*c*c+2.0*u[1]*w[2];

          Ssr[0]->u[qr] = Fx[0]*nx + Fy[0]*ny;
          Ssr[1]->u[qr] = Fx[1]*nx + Fy[1]*ny;
          Ssr[2]->u[qr] = Fx[2]*nx + Fy[2]*ny;

          switch (flux) {
          case LaxFriedrichs:
            lmax = zero;
            clm = one/Ma; // ::sqrt(Sbr[Nfields-1]->u[qr])/Ma;
            lam[0] = ulm;
            lam[1] = ulm+clm;
            lam[2] = ulm-clm;
            for(vField::size_type j=0; j<Nfields;j++) {  // left flux
              lmax = max(lmax,fabs(lam[j]));
              fpl[j] = Ssl[j]->u[ql];
            }
            crm = one/Ma; // ::sqrt(Sbr[Nfields-1]->u[qr])/Ma;
            lam[0] = urm;
            lam[1] = urm+crm;
            lam[2] = urm-crm;
            for(vField::size_type j=0; j<Nfields; j++) { // right flux
              lmax = max(lmax,fabs(lam[j]));
              fmr[j] = Ssr[j]->u[qr];
            }
            // Lax-Friedrichs flux
            f[0] = pt5 * ( fpl[0] + fmr[0] + lmax * ( sl[0] - sr[0] ) );
            f[1] = pt5 * ( fpl[1] + fmr[1] + lmax * ( sl[1] - sr[1] ) );
            f[2] = pt5 * ( fpl[2] + fmr[2] + lmax * ( sl[2] - sr[2] ) );
#ifdef VERBOSE
            cout << "Lax-Friedrichs: Element " << e << ", Side " << i << endl;
            cout << f[0] << ", "
                 << f[1] << ", "
                 << f[2] << endl;
#endif
            break;
          default:
            cerr << "Illegal value of flux type" << endl;
            comm->exit(DGM::FAILURE);
          }
          // put fluxes on flux field sides
          for (vField::size_type ni=0; ni<Nfields; ni++) {
            Ssr[ni]->u[qr] *= -one;         // correct for normal
            Sfl[ni]->u[ql]  =  f[ni];       // upwind flux
            Sfr[ni]->u[qr]  = -f[ni];       // correct for normal
          }
        }
      }
    }
  }
}

void Wave::enforce_mean_state_bc(vField &S) {
  dVector us[3];
  dVector ub[3];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    // dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    // dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type=="W") {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = 1.0; //  us[0][i];
        ub[1][i] = 0.0; // (us[1][i]*ny[i] - us[2][i]*nx[i])*ny[i];
        ub[2][i] = 0.0; // (us[2][i]*nx[i] - us[1][i]*ny[i])*nx[i];

      }
    } else {
      for (vField::size_type i=0; i<Nfields; i++) {
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      for (LocalSize i=0; i<qtot; i++) {
        ub[0][i] = 1.0; // us[0][i];
        ub[1][i] = 0.0; // us[1][i];
        ub[2][i] = 0.0; // us[2][i];
      }
    }
  }
}

void Wave::enforce_bc(vField &S) {
  // Here we only consider the no mean flow, so the quasi-variable the first
  // three are same as the primitive ones, refer to the Jacobimatrix from mean
  // flow so for wall normal B.C, its implementation is similar to the
  // conservative form

  // For inflow B.C, since fluctuation there are all zero, so we set them all
  // zero, it should be O.K.

  Scalar rho,u[2],rhop,up,vp,w[4];
  Scalar tmp1;

  dVector um[3];
  dVector us[3];
  dVector ub[3];
  for (LocalSize n=0; n<S[0]->nbc; n++) {
    const LocalSize sid = S[0]->bc[n]->sid;
    const LocalSize qtot = S[0]->bc[n]->elmt->side[sid]->qtot();
    dVector &nx = S[0]->bc[n]->elmt->side[sid]->nx();
    dVector &ny = S[0]->bc[n]->elmt->side[sid]->ny();
    if (S[0]->bc[n]->type=="W") {   // Wall
      for (vField::size_type i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[n]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );

      }
      for (LocalSize i=0; i<qtot; i++) {
        for(vField::size_type m=0;m<Nfields;m++) w[m] = us[m][i];
        rho  = um[0][i];
        u[0] = um[1][i];
        u[1] = um[2][i];

        // Get Up
        rhop = w[0];
        up   = -u[0]/rho*w[0]+1/rho*w[1];
        vp   = -u[1]/rho*w[0]+1/rho*w[2];

        // Form the new Up
        //rhop = rhop;
        tmp1 = (up*ny[i] - vp*nx[i])*ny[i];
        vp   = (vp*nx[i] - up*ny[i])*nx[i];
        up   = tmp1;

        w[0] = rhop; w[1] = up; w[2]=vp;
        // For Quasi U = M*Up
        ub[0][i] = w[0];
        ub[1][i] = u[0]*w[0]+rho*w[1];
        ub[2][i] = u[1]*w[0]+rho*w[2];
      }
    } else {
      for (vField::size_type i=0; i<Nfields; i++) {
        um[i].alias( Um[i]->bc[n]->elmt->side[sid]->u );
        us[i].alias( S[i]->bc[n]->elmt->side[sid]->u );
        ub[i].alias( S[i]->bc[n]->elmt->side[sid]->link->u );
      }
      Scalar amp = 0.02;
      Scalar x0 = 0.0;
      Scalar sigma = 0.7;
      Scalar c = 1.0/Ma;
      Scalar k = 2.5;
      AcousticWave pw(Ma,Pr,gamma,amp,x0,sigma,'x','p',
                      AcousticWave::Gaussian);
      Point cxy;
      Point *pside = new Point[S[0]->bc[n]->elmt->side[sid]->qtot()];
      S[0]->bc[n]->elmt->get_side_coordinates(sid,pside);

      for (LocalSize i=0; i<qtot; i++) {
        // Size indexp = get_side_point(S[0]->bc[n]->elmt,side,i);
        // cxy = Point(S[0]->bc[n]->elmt->C->x[indexp],
        //             S[0]->bc[n]->elmt->C->y[indexp]);
        cxy = Point(pside[i].x,pside[i].y);
        w[0] = pw.R(cxy)*sin(k*(cxy.x-0-c*t)); // rho
        w[1] = pw.U(cxy)*sin(k*(cxy.x-0-c*t)); // u
        w[2] = pw.V(cxy)*sin(k*(cxy.x-0-c*t)); // v

        // transform to the quasi-variable
        rho =  um[0][i];
        u[0] = um[1][i];
        u[1] = um[2][i];

        // form the quasi_variable
        ub[0][i] = w[0];
        ub[1][i] = u[0]*w[0]+rho*w[1];
        ub[2][i] = u[1]*w[0]+rho*w[2];
      }
    }
  }
}

void Wave::enforce_flux_bc(vField &S) {
  cout << "Wave::enforce_flux_bc(vField &U)" << endl;
}

//===========================================================================
//                        Source database management
//===========================================================================

/// Construct source terms
Source::Ptr Wave::make_Source( ifstream &in, string &tag ) {
  string code;
  Source::Ptr p;
  if (!(in >> code)) return p;
  //cout << "Wave::make_Source" << endl;
  while (code[0]=='#') {  // eat comment lines
    string buffer;
    getline(in,buffer);
    if (!(in >> code)) return p;
  }
  if (lowerCase(code) == "constant") {
    if (!(in >> tag)) error("Wave::Cannot read ConstSource tag",1);;
    p.reset( new ConstSource(tag,in,3) );
  } else if (lowerCase(code) == "file") {
    if (!(in >> tag)) error("Wave::Cannot read FileSource tag",1);;
    p.reset( new FileSource(tag,in,U) );
  } else if (lowerCase(code) == "function") {
    if (!(in >> tag)) error("Wave::Cannot read FuncSource tag",1);;
    p.reset( new FuncSource(tag,in,3) );
  } else if (lowerCase(code) == "ricker") {
    if (!(in >> tag)) error("Wave::Cannot read RickerSource tag",1);;
    p.reset( new RickerSource(tag,in) );
#if 0
  } else if (lowerCase(code) == "sponge") {
    if (!(in >> tag)) error("Wave::Cannot read Sponge tag",1);;
    p.reset( new Sponge(tag, in) );
#endif
  } else {
    error("Wave::make_Source() Illegal Source type",1);
  }
  return p;
}

// Add source terms
void Wave::add_source(const vField &Us, vField &Ur) {
  //cout << "Wave::add_source(vField &)" << endl;
  for (Source::db_citr i=Source_db.begin(); i!= Source_db.end(); ++i)
    //cout << "Adding source: " << i->first << endl;
    i->second->apply( t, Us, Ur);
}

//===========================================================================
//                        Initial Conditions
//===========================================================================

// set the initial condition
void Wave::set_ic(vField &F, string ext) {
  string fname = root+ext;
  ifstream in(fname.c_str());
  if (!in) {
    comm->cerr() << "Could not open initial condition " << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code",1);
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    F.fill(in);
  } else if (lowerCase(code) == "restart") {
    string rstfile;
    if (!(in>>rstfile)) {
      comm->cerr() << "Cannot read restart file name from " << fname << endl;
      comm->exit(DGM::FAILURE);
    }
    read(rstfile, F);
  } else if (lowerCase(code) == "wave"  || lowerCase(code) == "cylwave") {
    Scalar amp = 0.005;      // acoustic amplitude
    Scalar sigma = 0.2;      // width of the cylindrical pulse
    Scalar x0 = 2.0;         // center of the cylindrical pulse
    Scalar y0 = 2.0;         // center of the cylindrical pulse
    Scalar r0 = 1.0;         // radius of the initial cylinderical pulse
    in>>Ma;                  // get the Mach number
    AcousticWave pw( Ma, Pr, gamma, amp, x0, y0, sigma, 'p',
                     AcousticWave::Cylindrical, r0 );
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q],F[0]->el[e]->C->y[q]);
        Scalar rho = pw.R(cxy);
        Scalar u   = pw.U(cxy);
        Scalar v   = pw.V(cxy);
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = u;
        F[2]->el[e]->u[q] = v;
      }
    }
  } else if (lowerCase(code) == "planewave") {
    Scalar amp = 0.02;
    Scalar x0 = 0.0;
    Scalar sigma = 0.7;
    AcousticWave pw( Ma, Pr, gamma, amp, x0, sigma, 'x', 'p',
                     AcousticWave::Gaussian );
    Scalar k = 2.5; // spatial wave number
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q],F[0]->el[e]->C->y[q]);
        Scalar rho = pw.R(cxy)*sin(k*(cxy.x-0.0));
        Scalar u   = pw.U(cxy)*sin(k*(cxy.x-0.0));
        Scalar v   = pw.V(cxy)*sin(k*(cxy.x-0.0));
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = u;
        F[2]->el[e]->u[q] = v;
      }
    }
  } else if (lowerCase(code) == "cyl-test") {
    // SSC:  added this to test a simple cylindrical wave pulse in a domain
    // that is similar to a wave propagation model.
    Scalar amp = 1.0;        // acoustic amplitude
    Scalar sigma = 50.0;     // width of the cylindrical pulse
    Scalar x0 = 4000.0;      // center of the cylindrical pulse
    Scalar y0 = 1000.0;      // center of the cylindrical pulse
    Scalar r0 = 250.0;       // radius of the initial cylinderical pulse
    in>>Ma>>amp>>x0>>y0>>sigma>>r0; // read wave properties from input
    AcousticWave pw( Ma, Pr, gamma, amp, x0, y0, sigma, 'p',
                     AcousticWave::Cylindrical, r0 );
    for (LocalSize e=0; e<ne; e++) {
      for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
        Point cxy = Point(F[0]->el[e]->C->x[q],F[0]->el[e]->C->y[q]);
        Scalar rho = pw.R(cxy);
        Scalar u   = pw.U(cxy);
        Scalar v   = pw.V(cxy);
        F[0]->el[e]->u[q] = rho;
        F[1]->el[e]->u[q] = u;
        F[2]->el[e]->u[q] = v;
      }
    }
  } else {
    comm->error("Wave::set_ic()  Unsupported IC type");
  }
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<F.size(); i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  comm->cout() << "Projecting initial condition to polynomial space" << endl;
  project(F);
#endif
}

//===========================================================================
//                        Output methods
//===========================================================================

/// If defined than the side jumps are used in computing vorticity
#define REO_WAVE_JUMP

void Wave::compute_vorticity() {
  Element *S[4], *F[4];
  dVector u, v, p, e, wk;
  dVector r, ru, rv, E;

//  #ifdef REO_WAVE_JUMP
//    U.fill_sides();
//    enforce_bc( U );
//    primitive_sides( U );
//    U.share_sides();
//    average_side_flux( U, Ut, '+' );
//  #endif

  for (LocalSize i=0; i<U[0]->ne; i++) {
    // local version of the state
    S[0] = U[0]->el[i];
    S[1] = U[1]->el[i];
    S[2] = U[2]->el[i];
    S[3] = U[3]->el[i];

    // local version of the state
    F[0] = Ut[0]->el[i];
    F[1] = Ut[1]->el[i];
    F[2] = Ut[2]->el[i];
    F[3] = Ut[3]->el[i];

    const Ordinal qtot = U[0]->el[i]->qtot;

    r.alias (S[0]->u);  // rho
    ru.alias(S[1]->u);  // rho u
    rv.alias(S[2]->u);  // rho v
    E.alias (S[3]->u);  // total Energy

    u.alias(wk1,0,qtot);
    v.alias(wk1,qtot,qtot);
    p.alias(wk1,2*qtot,qtot);
    e.alias(wk1,3*qtot,qtot);
    wk.alias(wk1,4*qtot,qtot);

    dvdiv(ru, r, u);   // compute u
    dvdiv(rv, r, v);   // compute v
    dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

    dvmul(u,u,wk);     // wk = u^2
    dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
    daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

    // p = (gamma-1.0)*(E-0.5*(r*u*u + r*v*v))
    dvmul(u, ru, p);
    dvvtvp(v, rv, p, p);
    scale(-0.5*(gamma-1.0), p);
    daxpy(gamma-1.0, E, p);

#ifdef REO_WAVE_JUMP
//      dVector ux(qtot);
//      dVector uy(qtot);
//      dVector vx(qtot);
//      dVector vy(qtot);

//      gradient( S[1], F[1], u, ux, uy );
//      gradient( S[2], F[2], v, vx, vy );

//      // vorticity:   F[0]
//      scale(-1.0, uy);
//      dvadd(vx, uy, F[0]->u);

//      // divergence:  F[1]
//      dvadd(ux, vy, F[1]->u);
#else
    // vorticity:   F[0]
    F[0]->gradient(u, F[0]->u, 'y');
    F[1]->gradient(v, F[1]->u, 'x');
    scale(-1.0,F[0]->u);
    dvadd(F[1]->u, F[0]->u);

    // divergence:  F[1]
    F[1]->gradient(u, F[1]->u, 'x');
    F[2]->gradient(v, F[2]->u, 'y');
    dvadd(F[2]->u,F[1]->u);
#endif
    F[2]->fill(p);
    F[3]->fill(e);
  }
}

/** \warning This seems wrong [ssc]. */
void Wave::write_bndry_stats() {
  Ordinal qtot;
  dVector x, y, r, ru, rv, E;
  U[0]->bndry_stats->compute( x, y, r );
  U[1]->bndry_stats->compute( x, y, ru );
  U[2]->bndry_stats->compute( x, y, rv );
  U[3]->bndry_stats->compute( x, y, E );

  qtot = x.size();
  dVector u(qtot), v(qtot), p(qtot), e(qtot), wk(qtot);

  dvdiv(ru, r, u);   // compute u
  dvdiv(rv, r, v);   // compute v
  dvdiv(E,  r, e);   // internal energy + 0.5 |V|^2

  dvmul(u,u,wk);     // wk = u^2
  dvvtvp(v,v,wk,wk); // wk = u^2 + v^2
  daxpy(-0.5,wk,e);  // e  = e - 0.5 * wk = internal energy

  // p = (gamma-1.0)*(E-0.5*(r*u*u + r*v*v))
  dvmul(u, ru, p);
  dvvtvp(v, rv, p, p);
  scale(-0.5*(gamma-1.0), p);
  daxpy(gamma-1.0, E, p);

  string fname = root+".bdt";
  FILE *out = fopen(fname.c_str(),"w");
  for (Ordinal q=0; q<x.size(); ++q )
    fprintf(out,"%12.5e %12.5e %12.5e %12.5e %12.5e %12.5e %12.5e %12.4e\n",
            x[q], y[q], r[q], ru[q], rv[q], E[q], p[q], e[q]);
  fclose(out);
}

// Set the mean flow
void Wave::set_mean(vField &Fm) {
  // WARNING:  currently hardwired to zero mean flow
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<Fm[0]->el[e]->qtot; q++) {
      Fm[0]->el[e]->u[q] = 1.0;
      Fm[1]->el[e]->u[q] = 0.0;
      Fm[2]->el[e]->u[q] = 0.0;
    }
  }
  // project fields to the polynomial space just to make sure
  project( Fm );
}

// helper function to make quasi-conservative variables
void Wave::make_U(vField &F, const vField &Fm, const vField &Fp) {
  Scalar rho,u[2],w[3];
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=Fp[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      u[0]= Fm[1]->el[e]->u[q];
      u[1]= Fm[2]->el[e]->u[q];

      F[0]->el[e]->u[q] = w[0];
      F[1]->el[e]->u[q] = u[0]*w[0]+rho*w[1];
      F[2]->el[e]->u[q] = u[1]*w[0]+rho*w[2];
    }
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Total solution condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      F[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  F.project();
#endif
}

// helper function to subtract the mean flow from a total solution
void Wave::get_Up(vField &Fp, const vField &Fm, const vField &F) {
  Scalar rho,u[2],w[4];
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize q=0; q<F[0]->el[e]->qtot; q++) {
      for(vField::size_type i=0;i<Nfields;i++) w[i]=F[i]->el[e]->u[q];
      rho = Fm[0]->el[e]->u[q];
      u[0]= Fm[1]->el[e]->u[q];
      u[1]= Fm[2]->el[e]->u[q];

      Fp[0]->el[e]->u[q] = w[0];
      Fp[1]->el[e]->u[q] = -u[0]/rho*w[0]+1/rho*w[1];
      Fp[2]->el[e]->u[q] = -u[1]/rho*w[0]+1/rho*w[2];
    }
  }
#ifdef DGM_NO_PROJECT_IC
  cout << "WARNING:  No projection of Initial condition" << endl;
  for (LocalSize i=0; i<Nfields; i++)
    for (LocalSize e=0; e<ne; e++)
      Fp[i]->el[e]->state = Physical;
#else
  // project fields to the polynomial space just to make sure
  Fp.project();
#endif
}

void Wave::zero_all_fields() {
  Domain::zero_all_fields();
  Um.zero();
  Up.zero();
}

} // namespace Reo

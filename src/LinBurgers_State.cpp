/*=============================================================================
  Module:     Reo LinBurgers_State Module

  Author:     S. Scott Collis

  Copyright:  S. Scott Collis
              Department of Mechanical Engineering and Materials Science
              Rice University, MS 321
              Houston, TX 77005-1892
              (713) 348-3617
              collis@rice.edu
=============================================================================*/

/** \file  LinBurgers_State.cpp
    \brief State implementation for the linearized Burgers equation. */

// DGM includes
#include "ObjFunc.hpp"
#include "TimeInt.hpp"

// local includes
#include "LinBurgers_State.hpp"

namespace Reo {

#if 0  // just use the base class method

Scalar LinBurgers_State::compute(const int npredict, ControlPtr control_,
                                 const int iter) {
  static Format sci(8,15,'e');
  char tmp[80];

  time_int->initialize();

  // initialize the control
  control = control_;
  control->set_data( 0 );

  ObjFunc J( control.get(), objective, comm );

#ifndef DGM_PARALLEL
  sprintf(tmp,"%s.%d_%d.dat",root.c_str(),0,iter);
  U.tecplot(tmp,"State IC");
#endif

  if (iter==0) {
    comm->cout() << "Advancing solution " << npredict
                 << " time steps" << endl;
  } else {
    comm->cout() << "Predicting solution " << npredict
                 << " time steps" << endl;
  }

  Scalar ctime=0, stime=0, ttime=0;
  int cnt=0;
  Stopwatch cpu; cpu.start();

  for (lstep=1; lstep<=npredict; lstep++) {
    step++;
    time_int->advance(this,&J);
    ctime = cpu.restart();
    if (lstep>1) { ttime += ctime; stime += ctime*ctime; cnt++; }
    if (lstep%ntout==0)
      comm->cout()<<setw(6)<<lstep<<setw(6)
                  <<step<<sci(t)
                  <<sci(dt)<<sci(ctime)<<endl;
    if (lstep%Ntout==0) {
#ifdef DGM_PARALLEL
      string fname;
      sprintf(tmp,"%s.%d_%d.rst",root.c_str(),lstep,iter);
      fname = tmp;
      write(fname,U);
#else
      sprintf(tmp,"%s.%d_%d.dat",root.c_str(),lstep,iter);
      U.tecplot(tmp,"State");
#endif
       U.norm();
      cpu.restart();
    }
  }
#ifdef DGM_PARALLEL
  Scalar atime=0, otime=0;
  comm->SumAll( &ttime, &atime, 1 );  // average cpu time
  comm->SumAll( &stime, &otime, 1 );  // standard deviation
  int n = max(1,cnt*comm->NumProc());
  atime /= n; otime /= n;
  Scalar stdev = ::sqrt(otime - atime*atime);
  comm->cout() << "Average time per step: " << sci(atime)
               << ", standard deviation:  " << sci(stdev) << endl;
#endif
  Scalar Jvalue=0;
  J.value += J.terminal( U, npredict );
  get_comm()->SumAll( &J.value, &Jvalue, 1 );
  get_comm()->cout()<<"J = "<<sci(Jvalue)<<endl;
  return Jvalue;
}

#endif

} // namespace Reo

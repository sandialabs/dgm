/** \file  NS_Control.cpp
    \brief Navier-Stokes Control class

    \todo Remove this almost empty class
*/

// system includes
#include <list>

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Format.hpp"
#include "BC.hpp"
#include "Source.hpp"
#include "Ctrl.hpp"

// local includes
#include "NS_State.hpp"
#include "NS_Control.hpp"

namespace Reo {

/// Constructor
NS_Control::NS_Control(DGM::ArgList &args_, State *state_,
                       const DGM::Comm::Ptr comm_ ) :
  Control(args_,state_,comm_) {
  comm->cout() << "Building NS_Control..." << std::endl;

  Ordinal phi_size = 0;

  // get the state domain
  Domain *omega(state->domain());

  // need to explicitly use the NS BC database
  NS_State *state1 = dynamic_cast<NS_State*>(state);

  // loop through the sources
  for (Source::db_citr i=omega->Source_db.begin();
       i!= omega->Source_db.end(); ++i) {
    if (i->second->ctrl()) {
      i->second->ctrl()->initialize();

      // get the len/disp for the Source control
      // Warning: assumes Source control is FULL Field [gqchen]
      CMC::Vector<Size,Ordinal> cdisp;
      CMC::Vector<Ordinal,Ordinal> clen;
      cdisp.resize(omega->U[0]->partition->nodal_disp.size());
      clen.resize(omega->U[0]->partition->nodal_len.size());
      cdisp = omega->U[0]->partition->nodal_disp;
      clen = omega->U[0]->partition->nodal_len;
      Entry::Ptr entry(new Entry(this, i->first, phi_size, npp,
                                 i->second->ctrl(), dt, cdisp, clen,
                                 omega->U[0]->partition->nodal_glen(), comm) );
      phi_db.push_back(entry);
      phi_size += phi_db.back()->length;
      comm->cout() <<"Found source control: " << i->first
                   <<", ctrl_size = " << phi_db.back()->ctrl_size()
                   <<", length = "<< phi_db.back()->length << endl;
    }
  }

  // loop through the state boundaries and accumulate ctrl sizes
  for (LocalSize n=0; n<state1->U[0]->nbc; n++) {
    BC::db_citr i = state1->BC_db.find(state1->U[0]->bc[n]->type);
    if (i->second->ctrl()) i->second->ctrl()->size(0);
  }
  for (LocalSize n=0; n<state1->U[0]->nbc; n++) {
    BC::db_citr i = state1->BC_db.find(state1->U[0]->bc[n]->type);
    if (i->second->ctrl()) {
      const Ordinal new_size = 
        i->second->ctrl()->size() + omega->U[0]->bc[n]->S->qtot();
      i->second->ctrl()->size(new_size);
    }
  }

  // loop through the boundary conditions and initialize controls
  for (BC::db_citr i=state1->BC_db.begin(); i!= state1->BC_db.end(); ++i) {
    if (i->second->ctrl()) {
      i->second->ctrl()->initialize();

      // set Euler ctrl data to the NS ctrl data
      // Euler::data.alias( NS::data )

      // get the len/disp for the Boundary control
      // cdisp/clen are not used for Serial computating
      CMC::Vector<Size,Ordinal> cdisp;
      CMC::Vector<Ordinal,Ordinal> clen;
      Size glen=0;

#ifdef DGM_PARALLEL
      vector<int> global_eid, global_sid;
      iVector global_len, global_disp;
      Ordinal lnbc=0, sum_size=0;

      // get the global boundary len/disp information
      string fname = omega->root+".bc";
      ifstream in(fname.c_str());
      string buffer,type;
      int gnbc,geid,gsid;
      getline(in,buffer);        // strip off header line
      if (!(in>>gnbc))           // global number of boundary conditions
        error("Cannot read number of boundary conditions",1);
      getline(in,buffer);
      for (int j=0;j<gnbc;j++) {
        in >> type >> geid >> gsid;
        if (type == i->second->type) {  // only include the current BC
          global_eid.push_back(geid);
          global_sid.push_back(gsid);
        }
        getline(in,buffer);
      }
      global_disp.resize(global_eid.size());
      global_len.resize(global_eid.size());
      global_len = 0;
      global_disp[0] = 0;
      // get the global displacement/length information
      for (int e=0; e<(int)global_eid.size(); e++) {
        if (e!=0) global_disp[e] = global_disp[e-1] + sum_size;
        // if element is in my partition
        if (omega->U[0]->partition->owns(global_eid[e])) {
          int leid = omega->U[0]->partition->inc(global_eid[e]);
          global_len[e] = omega->U[0]->el[leid]->side[global_sid[e]]->qtot();
          lnbc++;
        }
        comm->SumAll(&global_len[e], &sum_size, 1 );
        glen += sum_size;
      }
#ifdef REO_CONTROL_RESTART_DEBUG
      comm->Barrier();
      comm->cout()<<"Global mapping data"<<endl;
      if(comm->Master()) {
        for(int e=0; e<global_eid.size(); ++e) {
          cout << comm->MyPID() << ": " << global_disp[e] << "  "
               << global_len[e] << endl;
        }
      }
      comm->Barrier();
      if(comm->MyPID()==1) {
        for(int e=0; e<global_eid.size(); ++e) {
          cout << comm->MyPID() << ": " << global_disp[e] << "  "
               << global_len[e] << endl;
        }
      }
      comm->Barrier();
#endif
      clen.resize(lnbc);  // size of the local number of bc of this type
      cdisp.resize(lnbc);

      // Distribute the displacement/length among processes
      int n=0;
      for (int j=0; j<(int)global_eid.size(); j++) {
        // if element is in my partition
        if (omega->U[0]->partition->owns(global_eid[j])) {
          cdisp[n] = global_disp[j];
          clen[n]  = global_len[j];
          n++;
        }
      }
#ifdef REO_CONTROL_RESTART_DEBUG
      comm->Barrier();
      comm->cout()<<"Local mapping data"<<endl;
      if(comm->Master()) {
        for(int e=0; e<cdisp.size(); ++e) {
          cout << comm->MyPID() << ": " << cdisp[e] << "  "
               << clen[e] << endl;
        }
      }
      comm->Barrier();
      if(comm->MyPID()==1) {
        for(int e=0; e<cdisp.size(); ++e) {
          cout << comm->MyPID() << ": " << cdisp[e] << "  "
               << clen[e] << endl;
        }
      }
      comm->Barrier();
#endif
#endif  // DGM_PARALLEL
      Entry::Ptr entry(new Entry(this, i->first, phi_size, npp,
                                 i->second->ctrl(),
                                 dt, cdisp, clen, glen, comm) );
      phi_db.push_back(entry);
      phi_size += phi_db.back()->length;
      comm->cout() <<"Found boundary control: " << i->first
                   <<", ctrl_size = " << phi_db.back()->ctrl_size()
                   <<", offset = "<< phi_db.back()->offset
                   <<", length = "<< phi_db.back()->length
                   << endl;
      comm->Barrier();
#ifdef REO_CONTROL_RESTART_DEBUG
      if (comm->MyPID()==1) {
        cout <<"Found boundary control: " << i->first
             <<", ctrl_size = " << phi_db.back()->ctrl_size()
             <<", offset = "<< phi_db.back()->offset
             <<", length = "<< phi_db.back()->length
             << endl;
      }
      comm->Barrier();
#endif
    }
  }
  phi.resize( phi_size );
  zero();

  // Need some parallel communication to get this correct

  comm->cout() << "Number of controls = " << phi_db.size() << endl;
  comm->cout() << "Total length of control vector = " << phi_size <<endl;

  //get the global length
#ifndef DGM_PARALLEL
  global_len = numeric_cast<int>(phi_size);
#else
  comm->SumAll( &phi_size, &glen, 1 );
  global_len.resize(comm->NumProc());
  global_disp.resize(comm->NumProc());
  intVector len(comm->NumProc());
  intVector disp(comm->NumProc());
  len = 1;
  for (int i=0; i<comm->NumProc(); ++i) disp[i] = i;
  {
    const int i = static_cast<int>(phi_size);
    comm->GatherAll( &i, 1, global_len.data(), len.data(), disp.data() );
  }
  global_disp[0] = 0;
  for (int i=1; i<comm->NumProc(); ++i)
    global_disp[i] = global_disp[i-1] + global_len[i-1];
  if (comm->Master()) {
    for (int i=1; i<comm->NumProc(); ++i) {
      cout << "NS_Control: global_disp = " << global_disp[i]
           << ", global_len = " << global_len[i] << endl;
    }
  }
#endif
}

// copy constructor
NS_Control::NS_Control( const NS_Control *in) : Control(in) {
}

} // namespace Reo

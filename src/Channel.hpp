#ifndef REO_CHANNEL_HPP
#define REO_CHANNEL_HPP

/** \file Channel.hpp
    \brief Planar turbulent channel module
    \author Scott Collis
*/

// DGM includes
#include "Statistics.hpp"
#include "vField.hpp"
using namespace DGM;

// json includes
#ifdef DGM_USE_JSON
#include "json/json.h"
/// Switch to use Json format for channel parameters
#define DGM_CHANNEL_USE_JSON
#endif

namespace Reo {

/// Channel flow class
/*! Computes and outputs statistics for planar channel flow. */
class Channel {
  string ext;             ///< filename extension
public:
  typedef DGM::Size GlobalSize;
  typedef DGM::Ordinal LocalSize;

  bool valid;             ///< true if this class is valid
  Ordinal Nx;             ///< dimensions of channel
  Ordinal Ny;             ///< dimensions of channel
  Ordinal Nz;             ///< dimensions of channel

  DGM::Statistics *stats; ///< statistics
  DGM::Comm::Ptr comm;    ///< parallel communicator

  /// Constructor
  Channel( string root, DGM::Statistics *_stats, DGM::Comm::Ptr _comm ) :
    ext(".chn"), valid(false), Nx(8), Ny(8), Nz(8), stats(_stats), comm(_comm)
  {
    string fname = root+".chn";
    ifstream in(fname.c_str());
    if (!in) return;                // return if not a channel
#ifdef DGM_CHANNEL_USE_JSON
    Json::Reader reader;
    Json::Value value;
    if (!reader.parse(in, value, true)) {
      throw DGM::exception("Failed to parse the parameter file " +
                           fname + ":  " +
                           reader.getFormattedErrorMessages());
    }
    const int verb = value.get("Verbosity",0).asInt();
    if (verb) {
      Json::StyledWriter writer;
      string output = writer.write(value);
      comm->cout() << "Read " << fname << " and executing with Channel "
          "parameters:\n" << output;
    }
    Nx = value.get("Nx",Nx).asDouble();
    Ny = value.get("Ny",Ny).asDouble();
    Nz = value.get("Nz",Nz).asDouble();
#else
    if (!(in >> Nx >> Ny >> Nz)) error("Channel cannot read dimensions");
#endif
    valid = true;

    // setup the statistics for Channel flow
    stats->setup("time",0.0,"time","Simulation time");
    stats->setup("phi",0.0,"phi","Bulk density");
    stats->setup("psi",0.0,"psi","Bulk mass flow in x");
    stats->setup("eta",0.0,"eta","Bulk mass flow in y");
    stats->setup("zeta",0.0,"zeta","Bulk mass flow in z");
    stats->setup("xi",0.0,"xi","Bulk energy");
  }
  /// Determine if the input file exists
  static bool exists( string root ) {
    string fname = root+".chn";
    ifstream in(fname.c_str());
    if (!in)
      return false;            // must not be a channel
    else
      return true;
  }
  /// Performs a planar average over the channel
  void plane_average( vField &Us ) {
    Us.plane_average();
    if (!valid) return;
    // now do real plane averages for the channel
    cout << "WARNING: Channel::plane_average() is using an "
         << Nx<<"x"<<Ny<<"x"<<Nz<<" mesh\n";
    for (vField::size_type n=0; n<Us.size(); n++) {
      // loop over planes (elementwise)
      for (Ordinal k=0; k<Nz; k++) {
        // cout << "Averaging k = " << k << endl;
        Ordinal count = 0;
        dVector avg( Us[n]->el[k*Nx*Ny]->u.size(), 0.0 );
        for (Ordinal j=0; j<Ny; j++) {
          for (Ordinal i=0; i<Nx; i++) {
            Ordinal e = i + j * Nx + k * Nx * Ny;
            count++;
            dvadd( Us[n]->el[e]->u, avg );
          }
        }
        scale( 1.0/count, avg );
        for (Ordinal j=0; j<Ny; j++) {
          for (Ordinal i=0; i<Nx; i++) {
            Ordinal e = i + j * Nx + k * Nx * Ny;
            Us[n]->el[e]->u = avg;
          }
        }
      }
    }
  }
  /// Hold the bulk mass flow in the streamwise direction constant
  void holdBulkMassFlow(const Scalar t, vField &Uf) {
    Scalar phi = 0, psi = 0, eta = 0, zeta = 0, xi = 0, vol = 0;
    dVector lvol(Uf[1]->ne);
    for (LocalSize k=0; k<Uf[1]->ne; k++) {
      psi  += Uf[0]->el[k]->integrate( &lvol[k] );
      phi  += Uf[1]->el[k]->integrate( &lvol[k] );
      eta  += Uf[2]->el[k]->integrate( &lvol[k] );
      zeta += Uf[3]->el[k]->integrate( &lvol[k] );
      xi   += Uf[4]->el[k]->integrate( &lvol[k] );
      vol  += lvol[k];
    }
#ifdef DGM_PARALLEL
    Scalar local = psi;
    comm->SumAll( &local, &psi , 1 );
    local = phi;
    comm->SumAll( &local, &phi , 1 );
    local = eta;
    comm->SumAll( &local, &eta , 1 );
    local = zeta;
    comm->SumAll( &local, &zeta, 1 );
    local = xi;
    comm->SumAll( &local, &xi  , 1 );
    local = vol;
    comm->SumAll( &local, &vol,  1 );
#endif
    psi  /= vol;
    phi  /= vol;
    eta  /= vol;
    zeta /= vol;
    xi   /= vol;
    for (LocalSize k=0; k<Uf[1]->ne; k++) {
      for (LocalSize q=0; q<Uf[1]->el[k]->qtot; q++) {
        Uf[0]->el[k]->u[q] -= psi;      // hold the bulk density
        Uf[1]->el[k]->u[q] -= phi;      // hold the bulk mass flow in x
        // Uf[2]->el[k]->u[q] -= eta;   // don't need to hold in y
        // Uf[3]->el[k]->u[q] -= zeta;  // nor in z
        Uf[4]->el[k]->u[q] -= xi;       // hold the bulk energy
      }
    }
    stats->update("time",t);
    stats->update("phi",phi);
    stats->update("psi",psi);
    stats->update("eta",eta);
    stats->update("zeta",zeta);
    stats->update("xi",xi);
    stats->increment();
  }
};

} // namespace Reo

#endif  // REO_CHANNEL_HPP

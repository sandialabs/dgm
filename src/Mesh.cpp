/** \file Mesh.cpp
    \brief Simple rectilinear mesh generator implementation
    \author Scott Collis
    \author James Overfelt
    \author Curt Ober
    \author Tom Smith
    \author Noel Belcourt
*/

// system includes
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>
using namespace std;

// TPL includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// Boost includes
#ifdef DGM_USE_BOOST_DATETIME
#include "boost/date_time/posix_time/posix_time.hpp"
#endif

#ifdef DGM_USE_BOOST_RANDOM
#include "boost/random/linear_congruential.hpp"
#endif

// DGM includes
#include "BinaryFileIO.hpp"
#include "Mesh.hpp"
#include "Element.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#endif
#include "String.hpp"
#include "Partition.tpp"
#include "Utilities.hpp"

namespace DGM {

// define static storage
const Scalar Mesh::slop = 0;
const Scalar Mesh::EPSILON = 1.0e-10;
const unsigned Mesh::nodes[NumEtype] =
  { 2, 4, 3, 8, 4, 5, 2, 4, 8, 3, 4, 2, 4, 8 };
const unsigned Mesh::sides[NumEtype] =
  { 2, 4, 3, 6, 4, 5, 2, 4, 6, 3, 4, 2, 4, 6 };

/// Modulo function
template <typename T>
T Mesh::mod(const T x, const T y) {
  if (y==0) return 0;
  return x - y * (T)floor((Scalar)x/(Scalar)y);
}

/// Construct a rectilinear Mesh from a parameter Table
Mesh::Mesh(Table &params, iVector elem_depth, dVector depths,
           vector<string> ifnames, const bool Nodal, const bool Spectral,
           const bool Periodic, const int verb, const DGM::Comm::Ptr COMM) :
  comm(COMM), partition(), nsd(0), ne(0), nx(0), ny(0), nz(0), x0(0.0),
  y0(0.0), z0(0.0), Lx(0.0), Ly(0.0), Lz(0.0), dx(0.0), dy(0.0), dz(0.0),
  Cx(0.0), Cy(0.0), Cz(0.0), Dx(0.0), Dy(0.0), Dz(0.0), theta(0.0), phi(0.0),
  nodal(Nodal), spectral(Spectral), periodic(Periodic), verbose(verb) {

#if 0
#ifdef DGM_USE_BOOST_RANDOM
  // setup random number generators
  typedef boost::minstd_rand random_number_generator;
  typedef boost::uniform_01<random_number_generator, Scalar>
    random_distribution;
  random_distribution urand;
#endif
#endif

  // Make sure that parameters is filled with defaults
  setDefaults(params);

  MyCon c;
  nsd = params["nsd"];
  x0 = params["x0"];
  y0 = params["y0"];
  z0 = params["z0"];
  theta = params["theta"];
  phi = params["phi"];
  int tri = params["tri"];
  bool pencils = params["pencils"];

  if (nsd==1) {
    if      (nodal)    cout << "  Making 1d NodalLine DGM::Mesh" << endl;
    else if (spectral) cout << "  Making 1d SpectralLine DGM::Mesh" << endl;
    else               cout << "  Making 1d Line DGM::Mesh" << endl;

    Lx = params["Lx"];
    nx = params["nx"]; nx++;
    Cx = params["Cx"];
    Dx = params["Dx"];
    if (verbose) {
      cout << "    Cx = " << Cx << endl;
      cout << "    Dx = " << Dx << endl;
    }
    dx = Lx/(nx-1);
    Point C(x0, y0, z0);
    ne = (nx-1);

    LocalSize nlayers;
    if (elem_depth.size() > 0) {
      nlayers = elem_depth.size()-1;
      nx = 0;
      for (LocalSize i=0; i<nlayers; i++) nx += elem_depth[i+1];
      nx++;
    } else {  // Build a single layer from the input params.
      nlayers = 1;
      elem_depth.resize(nlayers+1);
      depths.resize(nlayers+1);
      elem_depth[0] = 0;
      elem_depth[1] = nx-1;
      depths[0] = x0;
      depths[1] = x0 + Lx;
    }

    for (LocalSize l=0; l<nlayers; l++) {
      Lx = depths[l+1]-depths[l];
      const LocalSize lnx = elem_depth[l+1]+1;
      x0 = depths[l];
      dx = Lx/(lnx-1);
      for (Size i=0; i<lnx-1; i++) {     // two verts per Line element
        const Scalar x  = distribute( Lx, Cx, nx, i, x0, Dx );
        const Scalar xp = distribute( Lx, Cx, nx, i+1, x0, Dx );
        C.x = x;            // i
        point.push_back(C);
        C.x = xp;           // i+1
        point.push_back(C);
      }
    }
    // make connectivity
    Size eid = 0;
    Topology::ElementType et;
    if      (nodal)    et = Topology::NodalLine;
    else if (spectral) et = Topology::SpectralLine;
    else               et = Topology::Line;
    if (ne==1) {
      etype.push_back(et);
      con.push_back( c.set(eid,0,eid,1) );
      con.push_back( c.set(eid,1,eid,0) );
    } else {
      etype.push_back(et);
      if (periodic) con.push_back( c.set(eid,0,ne-1,1) );
      con.push_back( c.set(eid,1,eid+1,0) );
      for (eid=1; eid<ne-1; eid++) {
        etype.push_back(et);
        con.push_back( c.set(eid,0,eid-1,1) );
        con.push_back( c.set(eid,1,eid+1,0) );
      }
      eid = ne-1;
      etype.push_back(et);
      con.push_back( c.set(eid,0,eid-1,1) );
      if (periodic) con.push_back( c.set(eid,1,0,0) );
    }

  } else if (nsd==2) {
    if      (nodal)    cout << "  Making 2d Nodal";
    else if (spectral) cout << "  Making 2d Spectral";
    else               cout << "  Making 2d";
    if (tri) cout << "Tri";
    cout << " DGM::Mesh" << endl;
    Lx = params["Lx"];
    Ly = params["Ly"];
    nx = params["nx"]; nx++;
    ny = params["ny"]; ny++;
    Cx = params["Cx"];
    Cy = params["Cy"];
    Dx = params["Dx"];
    Dy = params["Dy"];
    if (verbose) {
      cout << "    Cx = " << Cx << ", Cy = " << Cy << endl;
      cout << "    Dx = " << Dx << ", Dy = " << Dy << endl;
    }
    dx = Lx/(nx-1);
    dy = Ly/(ny-1);
    Point C(x0, y0, z0);
    ne = (nx-1) * (ny-1);
    LocalSize nlayers;
    if (elem_depth.size() > 0) {
      nlayers = elem_depth.size()-1;
      int temp_ny = 0;
      for (LocalSize i=0; i<nlayers; i++) temp_ny += elem_depth[i+1];
      temp_ny++;
      if (ny != temp_ny) {
        cerr << "The number y elements specified in ny = " << ny-1
             << ", does not match\n"
             << "the sum of y elements in the root.lyr, " << temp_ny-1
             << endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
    } else {  // Build a single layer from the input params.
      nlayers = 1;
      elem_depth.resize(nlayers+1);
      depths.resize(nlayers+1);
      elem_depth[0] = 0;
      elem_depth[1] = ny-1;
      depths[0] = y0;
      depths[1] = y0 + Ly;
    }

    // Create vectors for interfaces on boths sides (p-plus and m-minus)
    // the current layer.
    vector<Scalar> ifacem;
    vector<Scalar> ifacep;
    ifacem.resize(nx);
    ifacep.resize(nx);

    if (ifnames.empty() || (ifnames[0] == "")) {
      for (vector<string>::size_type ii=0; ii<ifacem.size(); ii++) {
        ifacem[ii] = depths[0];
      }
    } else {
      ifstream fin(ifnames[0].c_str());
      if (!fin) {
        cerr << "Failure to open " << ifnames[0] << endl;
        DGM::Comm::World->exit(DGM::FAILURE);
      }
      for (vector<string>::size_type ii=0; ii<ifacem.size(); ii++) {
        fin >> ifacem[ii];
      }
      fin.close();
    }

    const Scalar cr = cos(phi*pi/180.0);
    const Scalar sr = sin(phi*pi/180.0);
    for (LocalSize l=0; l<nlayers; l++) {
      if (ifnames.empty() || (ifnames[l+1] == "")) {
        for (vector<string>::size_type ii=0; ii<ifacep.size(); ii++)
          ifacep[ii] = depths[l+1];
      } else {
        ifstream fin(ifnames[l+1].c_str());
        if (!fin) {
          cerr << "Failure to open " << ifnames[l+1] << endl;
          DGM::Comm::World->exit(DGM::FAILURE);
        }
        for (vector<string>::size_type ii=0; ii<ifacep.size(); ii++)
          fin >> ifacep[ii];
        fin.close();
      }

      // Quad coordinates:
      //     (xa,yd) - - (xb,yc)
      //        |           |
      //        |           |
      //     (xa,ya) - - (xb,yb)
      LocalSize nye = elem_depth[l+1];
      for (LocalSize j=0; j<nye; j++) {   // four verts per Quad element
        for (int i=0; i<nx-1; i++) {
          const Scalar xa = distribute( Lx, Cx, nx,    i,   x0, Dx );
          const Scalar xb = distribute( Lx, Cx, nx,    i+1, x0, Dx );

          Ly = ifacep[i]-ifacem[i];
          y0 = ifacem[i];
          const Scalar ya = distribute( Ly, Cy, nye+1, j,   y0, Dy );
          const Scalar yd = distribute( Ly, Cy, nye+1, j+1, y0, Dy );

          Ly = ifacep[i+1]-ifacem[i+1];
          y0 = ifacem[i+1];
          const Scalar yb = distribute( Ly, Cy, nye+1, j,   y0, Dy );
          const Scalar yc = distribute( Ly, Cy, nye+1, j+1, y0, Dy );

          if (tri) {
            // Quad coordinates, split quad for tris
            //     (xa,yd) - - (xb,yc)
            //        |           |
            //        |           |
            //     (xa,ya) - - (xb,yb)
            //
            // if (tri == 3) use randomly oriented diagonals
            // if random number in [0,1] is less than 1/2
            //
            if (tri == 1) { // || (tri == 3 && urand() <= 0.5)) {
              // diagonal top-left bottom-right
              C.x =  xa*cr + ya*sr;
              C.y = -xa*sr + ya*cr;
              point.push_back(C);
              C.x =  xb*cr + yb*sr;
              C.y = -xb*sr + yb*cr;
              point.push_back(C);
              C.x =  xa*cr + yd*sr;
              C.y = -xa*sr + yd*cr;
              point.push_back(C);
              C.x =  xb*cr + yb*sr;
              C.y = -xb*sr + yb*cr;
              point.push_back(C);
              C.x =  xb*cr + yc*sr;
              C.y = -xb*sr + yc*cr;
              point.push_back(C);
              C.x =  xa*cr + yd*sr;
              C.y = -xa*sr + yd*cr;
              point.push_back(C);
            }
            // if (tri == 3) use randomly oriented diagonals
            // if random number in [0,1] is less than 1/2
            else if (tri == 2) { // || (tri == 3 && 0.5 < urand())) {
              // diagonal bottom-left top-right
              C.x =  xa*cr + ya*sr;
              C.y = -xa*sr + ya*cr;
              point.push_back(C);
              C.x =  xb*cr + yb*sr;
              C.y = -xb*sr + yb*cr;
              point.push_back(C);
              C.x =  xb*cr + yc*sr;
              C.y = -xb*sr + yc*cr;
              point.push_back(C);
              C.x =  xa*cr + ya*sr;
              C.y = -xa*sr + ya*cr;
              point.push_back(C);
              C.x =  xb*cr + yc*sr;
              C.y = -xb*sr + yc*cr;
              point.push_back(C);
              C.x =  xa*cr + yd*sr;
              C.y = -xa*sr + yd*cr;
              point.push_back(C);
            }
            else if (tri == 4) {
              // both diagonals (split quad into 4 tris)
              // Quad coordinates
              //     (xa,yd) - - - (xb,yc)
              //        |   \    /  |
              //        |      * <- | -- (x,y)
              //        |   /    \  |
              //     (xa,ya) - - - (xb,yb)
              const Scalar x = xa + (xb-xa)/2;
              const Scalar y = ya + (yc-ya)/2;
              // bottom tri
              C.x =  xa*cr + ya*sr;
              C.y = -xa*sr + ya*cr;
              point.push_back(C);
              C.x =  xb*cr + yb*sr;
              C.y = -xb*sr + yb*cr;
              point.push_back(C);
              C.x =  x*cr + y*sr;
              C.y = -x*sr + y*cr;
              point.push_back(C);
              // left tri
              C.x =  xa*cr + yd*sr;
              C.y = -xa*sr + yd*cr;
              point.push_back(C);
              C.x =  xa*cr + ya*sr;
              C.y = -xa*sr + ya*cr;
              point.push_back(C);
              C.x =  x*cr + y*sr;
              C.y = -x*sr + y*cr;
              point.push_back(C);
              // right tri
              C.x =  xb*cr + yb*sr;
              C.y = -xb*sr + yb*cr;
              point.push_back(C);
              C.x =  xb*cr + yc*sr;
              C.y = -xb*sr + yc*cr;
              point.push_back(C);
              C.x =  x*cr + y*sr;
              C.y = -x*sr + y*cr;
              point.push_back(C);
              // top tri
              C.x =  xa*cr + yd*sr;
              C.y = -xa*sr + yd*cr;
              point.push_back(C);
              C.x =  x*cr + y*sr;
              C.y = -x*sr + y*cr;
              point.push_back(C);
              C.x =  xb*cr + yc*sr;
              C.y = -xb*sr + yc*cr;
              point.push_back(C);
            }
          }
          else {
            C.x =  xa*cr + ya*sr;
            C.y = -xa*sr + ya*cr;
            point.push_back(C);
            C.x =  xb*cr + yb*sr;
            C.y = -xb*sr + yb*cr;
            point.push_back(C);
            C.x =  xb*cr + yc*sr;
            C.y = -xb*sr + yc*cr;
            point.push_back(C);
            C.x =  xa*cr + yd*sr;
            C.y = -xa*sr + yd*cr;
            point.push_back(C);
          }

          if (!ifnames.empty()) {
            if ((ifnames[l]=="")&&(ifnames[l+1]=="")) crv_els.push_back(false);
            else                                      crv_els.push_back(true);
          }
        }
      }
      ifacem = ifacep;
    }
    // make connectivity
    Size eid = 0;
    Topology::ElementType et;
    if (tri) {
      if      (nodal)    et = Topology::NodalTri;
      // else if (spectral) et = Topology::SpectralTri;
      else               et = Topology::Tri;
    }
    else {
      if      (nodal)    et = Topology::NodalQuad;
      else if (spectral) et = Topology::SpectralQuad;
      else               et = Topology::Quad;
    }
    if (ne==1) {
      if (tri) {
        if (tri == 1) {
          // tl-br
          con.push_back( c.set(eid,0,eid+1,1) );
          con.push_back( c.set(eid,1,eid+1,2) );
          con.push_back( c.set(eid,2,eid+1,0) );
          con.push_back( c.set(eid+1,0,eid,2) );
          con.push_back( c.set(eid+1,1,eid,0) );
          con.push_back( c.set(eid+1,2,eid,1) );
          etype.push_back( et );
          etype.push_back( et );
          ne = 2;
        }
        else if (tri == 2) {
          // bl-tr
          con.push_back( c.set(eid,0,eid+1,1) );
          con.push_back( c.set(eid,1,eid+1,2) );
          con.push_back( c.set(eid,2,eid+1,0) );
          con.push_back( c.set(eid+1,0,eid,2) );
          con.push_back( c.set(eid+1,1,eid,0) );
          con.push_back( c.set(eid+1,2,eid,1) );
          etype.push_back( et );
          etype.push_back( et );
          ne = 2;
        }
        else if (tri == 3) {
        }
        else if (tri == 4) {
          // split quad into 4 tris
          // bottom
          con.push_back( c.set(eid,0,eid+3,2) );
          con.push_back( c.set(eid,1,eid+2,2) );
          con.push_back( c.set(eid,2,eid+1,1) );
          // left
          con.push_back( c.set(eid+1,0,eid+2,0) );
          con.push_back( c.set(eid+1,1,eid,2) );
          con.push_back( c.set(eid+1,2,eid+3,0) );
          // right
          con.push_back( c.set(eid+2,0,eid+1,0) );
          con.push_back( c.set(eid+2,1,eid+3,1) );
          con.push_back( c.set(eid+2,2,eid,1) );
          // top
          con.push_back( c.set(eid+3,0,eid+1,2) );
          con.push_back( c.set(eid+3,1,eid+2,1) );
          con.push_back( c.set(eid+3,2,eid,0) );
          etype.push_back( et );
          etype.push_back( et );
          etype.push_back( et );
          etype.push_back( et );
          ne = 4;
        }
      }
      else {
        etype.push_back( et );
        con.push_back( c.set(eid,0,eid,2) );
        con.push_back( c.set(eid,1,eid,3) );
        con.push_back( c.set(eid,2,eid,0) );
        con.push_back( c.set(eid,3,eid,1) );
      }
    } else {
      if (tri == 4) ne *= 4;
      else if (tri) ne *= 2;
      for (int j=0; j<ny-1; j++) {    // four verts per Quad element
        for (int i=0; i<nx-1; i++) {
          // cout << "i, j = " << i << ", " << j << endl;
          eid = i + j * (nx-1);
          int n = i + mod(j+1,ny-1) * (nx-1);
          int s = i + mod(j-1,ny-1) * (nx-1);
          int e = mod(i+1,nx-1) + j * (nx-1);
          int w = mod(i-1,nx-1) + j * (nx-1);
          if (tri) {
            eid *= 2;
            etype.push_back( et );
            etype.push_back( et );
            n *= 2; e *= 2; s *= 2; w *= 2;
            if (tri == 1) {
              // tl-br, bottom top edges
              con.push_back( c.set(eid,0,s+1,1) );
              con.push_back( c.set(eid+1,1,n,0) );
              // diagonal edge
              con.push_back( c.set(eid,1,eid+1,2) );
              con.push_back( c.set(eid+1,2,eid,1) );
              // right left edges
              con.push_back( c.set(eid,2,w+1,0) );
              con.push_back( c.set(eid+1,0,e,2) );
            } else if (tri == 2) {
              // bl-tr, bottom top edges
              con.push_back( c.set(eid,0,s+1,1) );
              con.push_back( c.set(eid+1,1,n,0) );
              // left right edge
              con.push_back( c.set(eid,1,e+1,2) );
              con.push_back( c.set(eid+1,2,w,1) );
              // diagonal edge
              con.push_back( c.set(eid,2,eid+1,0) );
              con.push_back( c.set(eid+1,0,eid,2) );
            } else if (tri == 3) {
              throw DGM::exception("Random diagonals currently unsupported");
            } else if (tri == 4) {
              // split quad into 4 tris
              eid *= 2;
              etype.push_back( et );
              etype.push_back( et );
              n *= 2; e *= 2; s *= 2; w *= 2;
              // bottom top edges
              con.push_back( c.set(eid,0,s+3,2) );
              con.push_back( c.set(eid+3,2,n,0) );
              // left right edges
              con.push_back( c.set(eid+1,0,w+2,0) );
              con.push_back( c.set(eid+2,0,e+1,0) );
              // 4 middle edges
              // lower-left edge
              con.push_back( c.set(eid,2,eid+1,1) );
              con.push_back( c.set(eid+1,1,eid,2) );
              // lower-right edge
              con.push_back( c.set(eid,1,eid+2,2) );
              con.push_back( c.set(eid+2,2,eid,1) );
              // upper-left edge
              con.push_back( c.set(eid+1,2,eid+3,0) );
              con.push_back( c.set(eid+3,0,eid+1,2) );
              // upper-rightedge
              con.push_back( c.set(eid+2,1,eid+3,1) );
              con.push_back( c.set(eid+3,1,eid+2,1) );
            }
          } else {
            etype.push_back( et );
            if (periodic || j!=0   ) con.push_back( c.set(eid,0,s,2) );
            if (periodic || i!=nx-2) con.push_back( c.set(eid,1,e,3) );
            if (periodic || j!=ny-2) con.push_back( c.set(eid,2,n,0) );
            if (periodic || i!=0   ) con.push_back( c.set(eid,3,w,1) );
          }
        }
      }
    }
  } else if (nsd==3) {
    if      (nodal)    cout << "  Making 3d NodalHex DGM::Mesh" << endl;
    else if (spectral) cout << "  Making 3d SpectralHex DGM::Mesh" << endl;
    else               cout << "  Making 3d Hex DGM::Mesh" << endl;
    Lx = params["Lx"];
    Ly = params["Ly"];
    Lz = params["Lz"];
    nx = params["nx"]; nx++;
    ny = params["ny"]; ny++;
    nz = params["nz"]; nz++;
    Cx = params["Cx"];
    Cy = params["Cy"];
    Cz = params["Cz"];
    Dx = params["Dx"];
    Dy = params["Dy"];
    Dz = params["Dz"];
    if (verbose) {
      cout << "    Cx = " << Cx << ", Cy = " << Cy << ", Cz = " << Cz << endl;
      cout << "    Dx = " << Dx << ", Dy = " << Dy << ", Dz = " << Dz << endl;
    }
    dx = Lx/(nx-1);
    dy = Ly/(ny-1);
    dz = Lz/(nz-1);
    Point C(x0,y0,z0);
    ne = (nx-1) * (ny-1) * (nz-1);
    if (!(theta==0.0 && phi==0.0)) {
      comm->cout() << "    Rotating mesh about z-axis and y'-axis by\n"
                   << "    phi = " << phi << ", theta = " << theta
                   << " degrees" << endl;
      const Scalar ct = cos(theta*pi/180.0);
      const Scalar st = sin(theta*pi/180.0);
      const Scalar cf = cos(phi*pi/180.0);
      const Scalar sf = sin(phi*pi/180.0);
      for (int k=0; k<nz-1; k++) {
        const Scalar z  = distribute( Lz, Cz, nz, k, z0, Dz );
        const Scalar zp = distribute( Lz, Cz, nz, k+1, z0, Dz );
        for (int j=0; j<ny-1; j++) {
          const Scalar y  = distribute( Ly, Cy, ny, j, y0, Dy );
          const Scalar yp = distribute( Ly, Cy, ny, j+1, y0, Dy );
          for (int i=0; i<nx-1; i++) {
            const Scalar x  = distribute( Lx, Cx, nx, i, x0, Dx );
            const Scalar xp = distribute( Lx, Cx, nx, i+1, x0, Dx );
            C.x = z *st + ct*(x *cf + y *sf);     // i
            C.y = y *cf - x *sf;                  // i
            C.z = z *ct - st*(x *cf + y *sf);     // i
            point.push_back(C);
            C.x = z *st + ct*(xp*cf + y *sf);     // i+1
            C.y = y *cf - xp*sf;                  // i
            C.z = z *ct - st*(xp*cf + y *sf);     // i
            point.push_back(C);
            C.x = z *st + ct*(xp*cf + yp*sf);     // i+1
            C.y = yp*cf - xp*sf;                  // i+1
            C.z = z *ct - st*(xp*cf + yp*sf);     // i
            point.push_back(C);
            C.x = z *st + ct*(x *cf + yp*sf);     // i
            C.y = yp*cf - x *sf;                  // i+1
            C.z = z *ct - st*(x *cf + yp*sf);     // i
            point.push_back(C);
            C.x = zp*st + ct*(x *cf + y *sf);     // i
            C.y = y *cf - x *sf;                  // i
            C.z = zp*ct - st*(x *cf + y *sf);     // i+1
            point.push_back(C);
            C.x = zp*st + ct*(xp*cf + y *sf);     // i+1
            C.y = y *cf - xp*sf;                  // i
            C.z = zp*ct - st*(xp*cf + y *sf);     // i+1
            point.push_back(C);
            C.x = zp*st + ct*(xp*cf + yp*sf);     // i+1
            C.y = yp*cf - xp*sf;                  // i+1
            C.z = zp*ct - st*(xp*cf + yp*sf);     // i+1
            point.push_back(C);
            C.x = zp*st + ct*(x *cf + yp*sf);     // i
            C.y = yp*cf - x *sf;                  // i+1
            C.z = zp*ct - st*(x *cf + yp*sf);     // i+1
            point.push_back(C);
          }
        }
      }
    } else {
      LocalSize nlayers;
      if (elem_depth.size() > 0) {
        nlayers = elem_depth.size()-1;
        int temp_nz = 0;
        for (LocalSize i=0; i<nlayers; i++) temp_nz += elem_depth[i+1];
        temp_nz++;
        if (nz != temp_nz) {
          cerr << "The number z elements specified in nz = " << nz-1
               << ", does not match\n"
               << "the sum of z elements in the root.lyr, " << temp_nz-1
               << endl;
          DGM::Comm::World->exit(DGM::FAILURE);
        }
      } else {
        // Build a single layer from the input params.
        nlayers = 1;
        elem_depth.resize(nlayers+1);
        depths.resize(nlayers+1);
        elem_depth[0] = 0;
        elem_depth[1] = nz-1;
        depths[0] = z0;
        depths[1] = z0 + Lz;
      }

      // Create vectors for interfaces on boths sides (p-plus and m-minus)
      // the current layer.
      vector<Scalar> ifacem;
      vector<Scalar> ifacep;
      ifacem.resize(nx*ny);
      ifacep.resize(nx*ny);

      if (ifnames.empty() || (ifnames[0] == "")) {
        for (vector<string>::size_type ii=0; ii<ifacem.size(); ii++) {
          ifacem[ii] = depths[0];
        }
      } else {
        ifstream fin(ifnames[0].c_str());
        if (!fin) {
          cerr << "Failure to open " << ifnames[0] << endl;
          DGM::Comm::World->exit(DGM::FAILURE);
        }
        for (vector<string>::size_type ii=0; ii<ifacem.size(); ii++) {
          fin >> ifacem[ii];
        }
        fin.close();
      }

      for (LocalSize l=0; l<nlayers; l++) {
        if (ifnames.empty() || (ifnames[l+1] == "")) {
          for (vector<string>::size_type ii=0; ii<ifacep.size(); ii++)
            ifacep[ii] = depths[l+1];
        } else {
          ifstream fin(ifnames[l+1].c_str());
          if (!fin) {
            cerr << "Failure to open " << ifnames[l+1] << endl;
            DGM::Comm::World->exit(DGM::FAILURE);
          }
          for (vector<string>::size_type ii=0; ii<ifacep.size(); ii++)
            fin >> ifacep[ii];
          fin.close();
        }

        // Hex coordinates:
        //           (xa,yc,zh) - - (xb,yc,zg)
        //           /|             /|
        //          / |            / |
        // (xa,ya,ze) - - (xb,ya,zf) |
        //         |  |           |  |
        //         | (xa,yc,zd) - | (xb,yc,zc)
        //         | /            | /
        //         |/             |/
        // (xa,ya,za) - - (xb,ya,zb)
        Size nze = elem_depth[l+1];
        if (pencils) {
          for (int i=0; i<nx-1; i++) {
            const Scalar xa = distribute( Lx, Cx, nx, i,   x0, Dx );
            const Scalar xb = distribute( Lx, Cx, nx, i+1, x0, Dx );
            for (int j=0; j<ny-1; j++) {
              const Scalar ya = distribute( Ly, Cy, ny, j,   y0, Dy );
              const Scalar yc = distribute( Ly, Cy, ny, j+1, y0, Dy );
              for (LocalSize k=0; k<nze; k++) {
                int ii = i + nx*j;
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar za = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar ze = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i+1 + nx*j;
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zb = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zf = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i+1 + nx*(j+1);
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zc = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zg = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i + nx*(j+1);
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zd = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zh = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                C.x = xa;           // (i  )
                C.y = ya;           // (j  )
                C.z = za;           // (k  )
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = ya;           // (j  )
                C.z = zb;           // (k  )
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = yc;           // (j+1)
                C.z = zc;           // (k  )
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = yc;           // (j+1)
                C.z = zd;           // (k  )
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = ya;           // (j  )
                C.z = ze;           // (k+1)
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = ya;           // (j  )
                C.z = zf;           // (k+1)
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = yc;           // (j+1)
                C.z = zg;           // (k+1)
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = yc;           // (j+1)
                C.z = zh;           // (k+1)
                point.push_back(C);

                if (!ifnames.empty()) {
                  if ((ifnames[l]=="")&&(ifnames[l+1]==""))
                    crv_els.push_back(false);
                  else
                    crv_els.push_back(true);
                }
              }
            }
          }
        }
        else {
          for (Size k=0; k<nze; k++) {
            for (int j=0; j<ny-1; j++) {
              const Scalar ya = distribute( Ly, Cy, ny, j,   y0, Dy );
              const Scalar yc = distribute( Ly, Cy, ny, j+1, y0, Dy );
              for (int i=0; i<nx-1; i++) {
                const Scalar xa = distribute( Lx, Cx, nx, i,   x0, Dx );
                const Scalar xb = distribute( Lx, Cx, nx, i+1, x0, Dx );

                int ii = i + nx*j;
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar za = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar ze = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i+1 + nx*j;
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zb = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zf = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i+1 + nx*(j+1);
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zc = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zg = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                ii = i + nx*(j+1);
                Lz = ifacep[ii]-ifacem[ii];
                z0 = ifacem[ii];
                const Scalar zd = distribute( Lz, Cz, nze+1, k,   z0, Dz );
                const Scalar zh = distribute( Lz, Cz, nze+1, k+1, z0, Dz );

                C.x = xa;           // (i  )
                C.y = ya;           // (j  )
                C.z = za;           // (k  )
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = ya;           // (j  )
                C.z = zb;           // (k  )
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = yc;           // (j+1)
                C.z = zc;           // (k  )
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = yc;           // (j+1)
                C.z = zd;           // (k  )
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = ya;           // (j  )
                C.z = ze;           // (k+1)
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = ya;           // (j  )
                C.z = zf;           // (k+1)
                point.push_back(C);
                C.x = xb;           // (i+1)
                C.y = yc;           // (j+1)
                C.z = zg;           // (k+1)
                point.push_back(C);
                C.x = xa;           // (i  )
                C.y = yc;           // (j+1)
                C.z = zh;           // (k+1)
                point.push_back(C);

                if (!ifnames.empty()) {
                  if ((ifnames[l]=="")&&(ifnames[l+1]==""))
                    crv_els.push_back(false);
                  else
                    crv_els.push_back(true);
                }
              }
            }
          }
        }
        ifacem = ifacep;
      }
    }
    // make connectivity
    Size eid = 0;
    Topology::ElementType et;
    if      (nodal)    et = Topology::NodalHex;
    else if (spectral) et = Topology::SpectralHex;
    else               et = Topology::Hex;
    if (ne==1) {
      etype.push_back( et );
      con.push_back( c.set(eid,0,eid,5) );
      con.push_back( c.set(eid,1,eid,3) );
      con.push_back( c.set(eid,4,eid,2) );
      con.push_back( c.set(eid,2,eid,4) );
      con.push_back( c.set(eid,3,eid,1) );
      con.push_back( c.set(eid,5,eid,0) );
    } else {
      for (int k=0; k<nz-1; k++) {
        for (int j=0; j<ny-1; j++) {
          for (int i=0; i<nx-1; i++) {
            eid = i + j * (nx-1) + k * (nx-1)*(ny-1);
            // if (verbose) cout << "    e = " << setw(7) << eid+1 << flush;
            if (verbose) cout << "    e = " << eid+1 << flush;
            etype.push_back( et );
            int am = mod(i-1,nx-1) + j * (nx-1) + k * (nx-1)*(ny-1);
            int ap = mod(i+1,nx-1) + j * (nx-1) + k * (nx-1)*(ny-1);
            int bp = i + mod(j+1,ny-1) * (nx-1) + k * (nx-1)*(ny-1);
            int bm = i + mod(j-1,ny-1) * (nx-1) + k * (nx-1)*(ny-1);
            int cp = i + j * (nx-1) + mod(k+1,nz-1) * (nx-1)*(ny-1);
            int cm = i + j * (nx-1) + mod(k-1,nz-1) * (nx-1)*(ny-1);
            if (periodic || k!=0   ) con.push_back( c.set(eid,0,cm,5) );
            if (periodic || j!=0   ) con.push_back( c.set(eid,1,bm,3) );
            if (periodic || i!=nx-2) con.push_back( c.set(eid,2,ap,4) );
            if (periodic || j!=ny-2) con.push_back( c.set(eid,3,bp,1) );
            if (periodic || i!=0   ) con.push_back( c.set(eid,4,am,2) );
            if (periodic || k!=nz-2) con.push_back( c.set(eid,5,cp,0) );
            if (verbose) cout << "\r";
          }
        }
      }
      if (verbose) cout << endl;
    }
  } else {
    cerr << "Illegal value of nsd = " << nsd << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
}

/// Construct a Mesh from an ASCII DGM msh file
Mesh::Mesh(const string &name, const int verb, const DGM::Comm::Ptr COMM) :
  comm(COMM), partition(), nsd(0), ne(0), nx(0), ny(0), nz(0), x0(0.0),
  y0(0.0), z0(0.0), Lx(0.0), Ly(0.0), Lz(0.0), dx(0.0), dy(0.0), dz(0.0),
  Cx(0.0), Cy(0.0), Cz(0.0), Dx(0.0), Dy(0.0), Dz(0.0), theta(0.0), phi(0.0),
  nodal(false), spectral(false), periodic(true), verbose(false) {
  if (verb) cout << "Mesh::Mesh(name,verb)" << endl;
  string buffer;
  // open mesh file and read parameters
  ifstream in(name.c_str());
  if (!in) {
    cerr << "Mesh::Mesh: Could not open mesh file: " << name << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  if (verb) cout << "  Reading mesh from " << name << endl;
  getline(in,buffer);
  if (!(in>>ne)) error("Cannot read number of elements");
  if (!(in>>nsd)) error("Cannot read number of dimensions");
  getline(in,buffer);
  if (verb) cout << "  ne = " << ne << ", nsd = " << nsd << endl;
  resize(nsd,ne);
  // make the elements
  if (nsd==1) {
    vector<Point> X(2);
    for (Size e=0; e<ne; e++) {
      getline(in,buffer);  // get element description
      in >> X[0].x >> X[1].x;
      getline(in,buffer);
      etype.push_back( Topology::Line );
      point.push_back(X[0]);
      point.push_back(X[1]);
    }
  } else if (nsd==2){
    int nverts;
    vector<Point> X(4);
    for (Size e=0; e<ne; e++) {
      getline(in,buffer);  // get element description
      if ( buffer.find("Quad")==buffer.npos &&
           buffer.find("quad")==buffer.npos &&
           buffer.find("QUAD")==buffer.npos)
        nverts = 3;
      else
        nverts = 4;
      for (int i=0; i<nverts; i++) in >> X[i].x;
      getline(in,buffer);
      for (int i=0; i<nverts; i++) in >> X[i].y;
      getline(in,buffer);
      if (nverts == 4) {
        if      (nodal)    etype.push_back( Topology::NodalQuad );
        else if (spectral) etype.push_back( Topology::SpectralQuad );
        else               etype.push_back( Topology::Quad );
        for (int i=0; i<nverts; i++)
          point.push_back(X[i]);
      } else {
        etype.push_back( Topology::Tri );
        for (int i=0; i<nverts; i++)
          point.push_back(X[i]);
      }
    }
  }
  else if (nsd==3) {
    int nverts;
    vector<Point> X(8);
    for (Size e=0; e<ne; e++) {
      getline(in,buffer);  // get element description
      if ( buffer.find("Hex")==buffer.npos &&
           buffer.find("hex")==buffer.npos &&
           buffer.find("HEX")==buffer.npos)
        nverts = 4; // if not Hex then Tet
      else
        nverts = 8; // Hex
      for (int i=0; i<nverts; i++) in >> X[i].x;
      getline(in,buffer);
      for (int i=0; i<nverts; i++) in >> X[i].y;
      getline(in,buffer);
      for (int i=0; i<nverts; i++) in >> X[i].z;
      getline(in,buffer);
      if (nverts == 4) {
        etype.push_back( Topology::Tet );
        for (int i=0; i<nverts; i++)
          point.push_back(X[i]);
      } else {
        if (nodal)         etype.push_back( Topology::NodalHex );
        else if (spectral) etype.push_back( Topology::SpectralHex );
        else               etype.push_back( Topology::Hex );
        for (int i=0; i<nverts; i++)
          point.push_back(X[i]);
      }
    }
  }
}

//=============================================================================
//                I n p u t / O u t p u t   R o u t i n e s
//=============================================================================

/// Write a Json formatted file header
streamoff Mesh::write_header(const string &fname,
                             const streamoff offset) const {
  streamoff pos(0);
  if (comm->Master()) {
    fstream fs;
    fs.open(fname.c_str(), ios::out);
    if (!fs) throw DGM::exception("Mesh::write_header could not open file");
    fs.seekp(offset);
    if (!fs) throw DGM::exception("Mesh::write_header could not seek offset");
    Json::Value root;
    root["Name"] = fname;
#ifdef DGM_USE_BOOST_DATETIME
    namespace pt = boost::posix_time;
    root["Date"] = pt::to_iso_string(pt::second_clock::local_time());
#else
    time_t rawtime;
    time(&rawtime);
    string stime = string(ctime(&rawtime));
    size_t len = stime.find("\n");
    root["Date"] = stime.substr(0,len);
#endif
    root["Types"] = Json::Value(Json::objectValue);
    root["Types"]["GlobalSize"] = type<DGM::Size>();
    root["Types"]["LocalSize"] = type<DGM::Ordinal>();
    root["Types"]["Scalar"] = type<DGM::Scalar>();
    DGM::ByteOrder byteOrder;
    root["Types"]["ByteOrder"] = byteOrder.asString();

    root["Nel"] = (Json::Value::UInt64)ne;
    root["Nsd"] = (Json::Value::Int)nsd;
    root["Version"] = 1.0;
    Json::StyledWriter writer;
    string header = writer.write(root);
    fs << header;
    if (!fs) throw DGM::exception("Mesh could not write file header.");
    pos = fs.tellp();
    if (!fs) throw DGM::exception("Mesh::write_header could not get position");
    comm->Broadcast(&pos);
  }
  return pos;
}

/// Read a Json formated file header
streamoff Mesh::read_header(const string &fname, Json::Value &root,
                            const streamoff offset) {
  if (verbose) comm->cout() << "  Mesh::read_header("<<fname<<","<<offset<<")"
                            << endl;
  ifstream fs;
  fs.open(fname.c_str(), ios::in);
  if (!fs) throw DGM::exception("Could not open file "+fname);
  fs.seekg(offset);
  if (!fs.good())
    throw DGM::exception("Could not seek to offset "+asString(offset)+
                         " on file "+fname);
  string token;
  if (!(fs >> token))
    throw DGM::exception("Cannot read header from "+fname);
  // If we don't find a "{" then assume that there is no header and proceed
  // using default values
  if (token != "{")  {
    if (verbose)
      comm->cout() << "Mesh read header expected a \"{\" but found \" "
                   << token+"\" reading from file "+fname << endl;
    root.clear();
    root["Types"]["GlobalSize"] = "int32";
    root["Types"]["LocalSize"] = "int32";
    root["Types"]["Scalar"] = "float64";
    DGM::ByteOrder byteOrder;
    root["Types"]["ByteOrder"] = byteOrder.asString();
    root["Version"] = 0;
    return offset;
    // throw DGM::exception("Mesh read header expected a \"{\" but found \""+
    // token+"\" reading from file "+fname);
  }
  string buffer;
  string header = read_block(fs);
  const int status = scan_rb(fs);
  if (status) comm->error("Could not find closing bracket for header "
                          " on file "+fname);
  //cout << "Read header from " << fname << "\n" << header;
  getline(fs,buffer);
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( header, root, true );
  if (!parsingSuccessful)
    comm->error("Mesh read_header could not parse input from "+fname+"\n"+
                reader.getFormattedErrorMessages());
  if (fs.fail())
    throw DGM::exception("Could not read Json data at offset "+
                         asString(offset)+" from file "+fname);
  if (fs.bad())
    throw DGM::exception("Stream is bad when reading Json data at offset "+
                         asString(offset)+" from file "+fname);
  if (fs.eof())
    throw DGM::exception("End of file encountered when reading from "+fname);
#ifdef DGM_MESH_DEBUG_HEADER
  size_t sizeofGlobalSize(0);
  if (root["GlobalSize"].asString() == "int32")
    sizeofGlobalSize = sizeof(int32_t);
  if (root["GlobalSize"].asString() == "int64")
    sizeofGlobalSize = sizeof(int64_t);
  else
    DGM::exception("Illegal GlobalSize type = "+root["GlobalSize"].asString()+
                   " in "+fname+" header");
  comm->cout() << "    Size of GlobalSize = " << sizeofGlobalSize << endl;
#endif
  return fs.tellg();
}

/// Write a binary Mesh to file
streamoff Mesh::write(const string &fname, const streamoff offset) const {
  comm->cout() << "  Mesh::write("<<fname<<","<<offset<<")" << endl;
#ifdef DGM_PARALLEL
  if (!valid_parallel()) {
    throw DGM::exception("DGM::Mesh:  Must make sure that parallel information"
                         " is setup before doing parallel I/O");
  }
  return MPI_write(comm,partition,fname,offset);
#endif
  fstream fs;
  if (offset!=0)
    fs.open(fname.c_str(),ios::in|ios::out);
  else
    fs.open(fname.c_str(),ios::out);
  if (!fs) error("Error opening file "+fname);
  fs.seekp(offset);
  if (!fs.good()) error("Error seeking offset in file "+fname);
  fs.write(reinterpret_cast<const char*>(&ne),sizeof(ne));
  fs.write(reinterpret_cast<const char*>(&nsd),sizeof(nsd));
  const GlobalSize glen = numeric_cast<GlobalSize>(point.size());
  fs.write(reinterpret_cast<const char*>(&glen),sizeof(glen));
#if 0
  cout<<"    ne = "<<ne<<", nsd = "<<nsd<<", glen = "<<glen<<endl;
  cout<<"    sizeof(glen) = "<<sizeof(glen)<<endl;
#endif
  for (GlobalSize e=0; e<ne; e++) {
    fs.write(reinterpret_cast<const char*>(&etype[e]),sizeof(Topology::ElementType));
    if (!fs) error("Error writing element types");
  }
  GlobalSize disp = 0;
  for (GlobalSize e=0; e<ne; e++) {
    fs.write(reinterpret_cast<const char*>(&disp),sizeof(disp));
    disp += nodes[etype[e]];
  }
  assert( disp == glen );
  // Since this has to fit on one rank, glen has to fit in LocalSize
  const LocalSize lglen = numeric_cast<LocalSize>(glen);
  dVector x(lglen), y(lglen), z(lglen);
  for (LocalSize e=0, i=0; e<ne; e++) {
    for (unsigned n=0; n<nodes[etype[e]]; n++, i++) {
      x[i] = point[i].x;
      y[i] = point[i].y;
      z[i] = point[i].z;
    }
  }
  fs.write(reinterpret_cast<const char*>(x.data()),sizeof(Scalar)*glen);
  if (nsd>1)
    fs.write(reinterpret_cast<const char*>(y.data()),sizeof(Scalar)*glen);
  if (nsd>2)
    fs.write(reinterpret_cast<const char*>(z.data()),sizeof(Scalar)*glen);
  if (fs.bad()) error("Error in Mewsh::write.  Write to file "+fname+
                      " failed.  Disk full?");
  return fs.tellp();
}

/// helpers for reading variable-type data
namespace {
  template <typename Tin, typename Tout>
  void readConvert(ifstream &fs, Tout &out) {
    Tin in;
    fs.read(reinterpret_cast<char*>(&in),sizeof(Tin));
    out = static_cast<Tout>(in);
  }
#if defined(__APPLE__) && defined(DTK_SIZE_UNSIGNED_LONG_LONG)
  template<> void readConvert<int,unsigned long long>(ifstream &fs,
      unsigned long long &out) {
    fs.read(reinterpret_cast<char*>(&out),sizeof(int));
  }
#endif
#if defined(__APPLE__) && defined(DTK_SIZE_SIZE_T)
  template<> void readConvert<size_t,size_t>(ifstream &fs, size_t &out){
    fs.read(reinterpret_cast<char*>(&out),sizeof(size_t));
  }
#endif
#if defined(DTK_SIZE_UINT64)
  template<> void readConvert<uint64_t,uint64_t>(ifstream &fs, uint64_t &out){
    fs.read(reinterpret_cast<char*>(&out),sizeof(uint64_t));
  }
#endif
  template <typename Tin, typename Tout>
  void readConvert(ifstream &fs, std::vector<Tout> &out) {
    std::vector<Tin> in(out.size());
    fs.read(reinterpret_cast<char*>(&(in[0])),sizeof(Tin)*out.size());
    for (size_t i=0; i<out.size(); ++i)
      out[i] = Tout(in[i]);
  }

#ifdef DGM_PARALLEL

  /// Helper to read a Mesh using MPI-IO
  template <typename mySize, typename myOrdinal, typename myScalar>
  MPI_Offset MPI_read_mesh(const string &fname, const MPI_Offset offset,
                           Mesh &mesh, const Json::Value &header) {
    const Comm::Ptr comm = mesh.get_comm();
    const int verb = comm->verbosity();
    if (verb>1)
      comm->cout()<<"  MPI_read_mesh("<<fname<<","<<offset<<")"<<endl;
    const char *cnative="native";
    const Partition<Size,Ordinal,Scalar>::Ptr partition = mesh.get_partition();
    char *native = const_cast<char*>(cnative);
    MPI_File fh;
    MPI_Status status;
    MPI_Datatype filetype, inttype, disptype;
    MPI_Offset disp = offset;
    MPI_Info info;
    int stat;
    stat = MPI_Info_create(&info);
    if (stat) comm->error("MPI_Info_create", stat);

    const Mesh::LocalSize NE = numeric_cast<Mesh::LocalSize>(partition->ne());

    mesh.ne = NE;

    // make inttype
    intVector ilen(NE); ilen = 1;
    std::vector<MPI_Aint> byte_disp(NE);
    for (Mesh::LocalSize i=0; i<NE; ++i)
      byte_disp[i] = partition->eid(i)*sizeof(int);
    stat = MPI_Type_create_hindexed(NE, ilen.data(),
                                    &byte_disp.front(), mpiType<int>(),
                                    &inttype);
    if (stat) comm->error("MPI_Type_create_hindexed: inttype", stat);
    stat = MPI_Type_commit(&inttype);
    if (stat) comm->error("MPI_Type_commit: inttype", stat);
    if (verb>2) comm->cout() << "  MPI_Type_commit: inttype" << endl;

    // make disptype
    for (Mesh::LocalSize i=0; i<NE; ++i)
      byte_disp[i] = partition->eid(i)*sizeof(mySize);
    stat = MPI_Type_create_hindexed(NE, ilen.data(),
                                    &byte_disp.front(), mpiType<mySize>(),
                                    &disptype);
    if (stat) comm->error("MPI_Type_create_hindexed: disptype", stat);
    stat = MPI_Type_commit(&disptype);
    if (stat) comm->error("MPI_Type_commit: disptype", stat);
    if (verb>2) comm->cout() << "  MPI_Type_commit: disptype" << endl;

    stat = MPI_File_open(dynamic_cast<const DGM::MpiComm*>
                         (comm.get())->mpi_comm,
                         const_cast<char*>(fname.c_str()),
                         MPI_MODE_RDWR | MPI_MODE_CREATE, info, &fh);
    if (stat) {
      comm->cout() << "Error opening file, " << fname << endl;
      comm->error("MPI_File_open", stat);
    }
    if (verb>2) comm->cout() << "  Completed MPI_File_open" << endl;

    // read the global number of elements
    mySize gne;
    stat = MPI_File_set_view(fh, disp, mpiType<mySize>(), mpiType<mySize>(),
                             native, info);
    if (stat) comm->error("MPI_File_set_view", stat);
    MPI_File_read_all(fh, &gne, 1, mpiType<mySize>(), &status);
    disp += sizeof(mySize);
    if ( gne != (mySize)partition->gne() ) {
      comm->cout() << "Mismatched number of elements" << endl;
      comm->cout() << "gne = " << gne << endl;
      comm->cout() << "partition->gne = " << partition->gne() << endl;
      assert( gne == (mySize)partition->gne() );
    }
    if (verb>2) comm->cout() << "  Read global number of elements "
                             << gne << endl;

    // read the global number of space dimensions
    myOrdinal nsd;
    MPI_File_set_view(fh, disp, mpiType<myOrdinal>(), mpiType<myOrdinal>(),
                      native, info);
    MPI_File_read_all(fh, &nsd, 1, mpiType<myOrdinal>(), &status);
    mesh.nsd = numeric_cast<Ordinal>(nsd);
    disp += sizeof(myOrdinal);
    if (verb>2)
      comm->cout()<<"  Read global number of space dimensions "
                  << mesh.nsd << endl;

    // read the global data length
    mySize glen;
    MPI_File_set_view(fh, disp, mpiType<mySize>(), mpiType<mySize>(),
                      native, info);
    MPI_File_read_all(fh, &glen, 1, mpiType<mySize>(), &status);
    disp += sizeof(mySize);
    if (verb>2) comm->cout() << "  Read global data length " << glen << endl;

    // read the element types (stored as int)
    mesh.etype.resize(NE);
    MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
    MPI_File_read_all(fh, &(mesh.etype.front()), NE,
                      MPI_INT, &status);
    disp += partition->gne()*sizeof(int);
    if (verb>2) comm->cout() << "  Read element types" << endl;
#ifdef DGM_MESH_CHECK_ETYPES
    // check element types
    for(int e=0; e<NE; e++) {
      if ( etype[e] != Topology::Hex )
        cout << comm->MyPID()<<" e = "<<e<<" etype = "<<etype[e]<<endl;
    }
#endif
    // read data displacements
    CMC::Vector<mySize, myOrdinal> D(NE);
    MPI_File_set_view(fh, disp, mpiType<mySize>(), disptype, native, info);
    MPI_File_read_all(fh, D.data(), NE,mpiType<mySize>(),&status);
    disp += partition->gne()*sizeof(mySize);
    if (verb>2) comm->cout() << "  Read data displacements" << endl;

    // make the data lengths (MPI requires that these be int)
    intVector  L(NE);
    uint64_t len = 0;
    for (Ordinal e=0; e<NE; e++) {
      L[e] = Mesh::nodes[mesh.etype[e]];
      len += numeric_cast<uint64_t>(L[e]);
    }
    uint64_t global_len=0;
    comm->SumAll(&len,&global_len,1);
    if (verb>2) comm->cout() << "  Made the data lengths" << endl;
    {
      std::vector<MPI_Aint> byte_disp(NE);
      for (myOrdinal i=0; i<numeric_cast<myOrdinal>(NE); ++i)
        byte_disp[i] = numeric_cast<MPI_Aint>(D[i]*sizeof(myScalar));
      stat = MPI_Type_create_hindexed(NE, L.data(),
                                      &byte_disp.front(), mpiType<myScalar>(),
                                      &filetype);
    }
    MPI_Type_commit(&filetype);
    MPI_File_set_view(fh, disp, mpiType<myScalar>(), filetype, native, info);

    CMC::Vector<myScalar,Mesh::LocalSize> x(len), y, z;
    MPI_File_read_all(fh, x.data(), len, mpiType<myScalar>(), &status);
    disp += glen*sizeof(myScalar);
    if (verb>5) comm->cout() << "  Read x" << x << endl;
    if (nsd>1) {
      y.resize(len);
      MPI_File_set_view(fh, disp, mpiType<myScalar>(), filetype, native, info);
      MPI_File_read_all(fh, y.data(), len, mpiType<myScalar>(), &status);
      disp += glen*sizeof(myScalar);
      if (verb>5) comm->cout() << "  Read y" << y << endl;
    }
    if (nsd>2) {
      z.resize(len);
      MPI_File_set_view(fh, disp, mpiType<myScalar>(), filetype, native, info);
      MPI_File_read_all(fh, z.data(), len, mpiType<myScalar>(), &status);
      disp += glen*sizeof(myScalar);
      if (verb>5) comm->cout() << "  Read z" << z << endl;
    }
    if (verb>2) comm->cout() << "  Starting to make points" << endl;
    Scalar xl, yl, zl;
    mesh.point.clear();
    for (Size e=0, i=0; e<mesh.ne; e++) {
      for (unsigned n=0; n<mesh.nodes[mesh.etype[e]]; n++, i++) {
        if (nsd==1) {
          xl=numeric_cast<Scalar>(x[i]);
          yl=0, zl=0;
        } else if (nsd==2) {
          xl=numeric_cast<Scalar>(x[i]);
          yl=numeric_cast<Scalar>(y[i]);
          zl=0;
        } else {
          xl=numeric_cast<Scalar>(x[i]);
          yl=numeric_cast<Scalar>(y[i]);
          zl=numeric_cast<Scalar>(z[i]);
        }
        Point p( xl, yl, zl );
        mesh.point.push_back(p);
        //cout << i << " " << p << endl;
      }
    }
    if (verb>2) comm->cout() << "  Completed making points" << endl;
  #ifdef DGM_MESH_OUTPUT_COORDINATES
    if (comm->Master()) {
      for (int n=0; n<len; n++)
        cout << n << ", " << x[n] << ", " << y[n] <<endl;
    }
  #endif
    MPI_Type_free(&filetype);
    MPI_Type_free(&inttype);
    MPI_Type_free(&disptype);
    MPI_File_close(&fh);
    MPI_Info_free(&info);
    if (verb>2) comm->cout() << "  Completed MPI_read_mesh" << endl;
    return disp;
  }

  /// Read a connectivity file using MPI parallel I/O
  template <typename mySize, typename myOrdinal>
  MPI_Offset MPI_read_cn(const string &fname, const MPI_Offset offset,
                         Mesh &mesh, const Json::Value &header) {
    const Comm::Ptr comm = mesh.get_comm();
    const int verb = comm->verbosity();
    if (verb>1) comm->cout()<<"  MPI_read_cn("<<fname<<","<<offset<<")"<<endl;
    const Partition<Size,Ordinal,Scalar>::Ptr partition = mesh.get_partition();
    const char *cnative="native";
    char *native = const_cast<char*>(cnative);
    MPI_File fh;
    MPI_Status status;
    MPI_Datatype filetype, size_type, ordinal_type, con_type;
    MPI_Offset disp = offset;
    MPI_Info info;
    const Mesh::LocalSize NE = numeric_cast<Mesh::LocalSize> (partition->ne());

    if (const int stat = MPI_Info_create(&info))
      comm->error("MPI_Info_create", stat);
    {
      vector<int>           ilen(NE,1);
      vector<MPI_Aint> byte_disp(NE);
      for (Mesh::LocalSize i=0; i<NE; ++i)
        byte_disp[i]=partition->eid(i)*sizeof(mySize);
      if (const int stat = MPI_Type_create_hindexed(NE, &ilen.front(),
                                      &byte_disp.front(), mpiType<mySize>(),
                                      &size_type))
        comm->error("MPI_Type_create_hindexed", stat);
      if (const int stat = MPI_Type_commit(&size_type))
        comm->error("MPI_Type_commit", stat);

      for (Mesh::LocalSize i=0; i<NE; ++i)
        byte_disp[i]=partition->eid(i)*sizeof(myOrdinal);
      if (const int stat = MPI_Type_create_hindexed(NE, &ilen.front(),
                                      &byte_disp.front(), mpiType<myOrdinal>(),
                                      &ordinal_type))
        comm->error("MPI_Type_create_hindexed", stat);
      if (const int stat = MPI_Type_commit(&ordinal_type))
        comm->error("MPI_Type_commit", stat);
    }
    if (const int stat =
      MPI_File_open(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
                    const_cast<char*>(fname.c_str()),
                    MPI_MODE_RDWR | MPI_MODE_CREATE, info, &fh))
      comm->error("MPI_File_open", stat);

    // read data displacements
    CMC::Vector<   mySize, myOrdinal>  D(NE);
    if ( const int stat = MPI_File_set_view(fh, disp, mpiType<mySize>(),
                                            size_type, native, info)     )
      error("MPI_File_set_view", stat);
    if ( const int stat = MPI_File_read_all(fh, D.ptr(), NE,
                                            mpiType<mySize>(), &status) )
      error("MPI_File_read_all", stat);
    MPI_Type_free(&size_type);

    disp += partition->gne()*sizeof(mySize);

    // read data lengths
    CMC::Vector<myOrdinal, myOrdinal>  L(NE);
    if ( const int stat = MPI_File_set_view(fh, disp, mpiType<myOrdinal>(),
                                           ordinal_type, native, info)      )
      error("MPI_File_set_view", stat);
    if ( const int stat = MPI_File_read_all(fh, L.ptr(), NE,
                                            mpiType<myOrdinal>(), &status) )
      error("MPI_File_read_all", stat);

    MPI_Type_free(&ordinal_type);


    disp += partition->gne()*sizeof(myOrdinal);

    const bool Version_0 = header["Version"]==0;
    if (Version_0) {
      // Original Con had 5 ints
      for (myOrdinal i=0; i<numeric_cast<myOrdinal>(NE); ++i) L[i] /= 5;
      for (myOrdinal i=0; i<numeric_cast<myOrdinal>(NE); ++i) D[i] /= 5;
    }

#ifdef DGM_MESH_DEBUG_CONNECTIVITY
    // Debug information
    cout << "Header[Version] = " << header["Version"] << endl;
    cout << "Displacements = " << endl;
    cout << D;
    cout << "Lengths = " << endl;
    cout << L;
    const uint64_t ConSize = mesh.con_size();
    cout << "  ConSize = " << ConSize << endl;
    cout << "  con.size() = " << mesh.con.size() << endl;
    cout << "  L.Sum() = " << L.Sum() << endl;
#endif


    typedef Mesh::Con<mySize,myOrdinal> myCon;
    const unsigned ConSize = sizeof(myCon);

    if (const int stat = MPI_Type_contiguous(ConSize, MPI_BYTE, &con_type))
      comm->error("MPI_Type_contiguous: con_type ", stat);
    if (const int stat = MPI_Type_commit(&con_type))
      comm->error("MPI_Type_commit: con_type ", stat);

    {
      vector<int>           ilen(NE);
      vector<MPI_Aint> byte_disp(NE);
      for (myOrdinal i=0; i<numeric_cast<myOrdinal>(NE); ++i) {
        ilen[i]      = numeric_cast<int>(L[i]);
        byte_disp[i] = numeric_cast<MPI_Aint>
                        (numeric_cast<uint64_t>(D[i]) * ConSize);
      }
      if (const int stat = MPI_Type_create_hindexed(NE,
                               &ilen.front(), &byte_disp.front(),
                               con_type, &filetype))
        comm->error("MPI_Type_create_hindexed", stat);
      if (const int stat = MPI_Type_commit(&filetype))
        comm->error("MPI_Type_commit", stat);
    }
    if (const int stat = MPI_File_set_view(fh, disp, con_type, filetype,
                                                         native, info))
      error("MPI_File_set_view", stat);

    const int len = numeric_cast<int>(L.Sum());
    vector<myCon> con(len);
    if (const int stat = MPI_File_read_all(fh, &con.front(),
                                                len, con_type, &status))
      error("MPI_File_read_all", stat);
    MPI_Type_free(&con_type);

    mesh.con.resize(len);
    for (int i=0; i<len; ++i) mesh.con[i] = Mesh::MyCon(con[i]);

    /// \todo This needs to read in mySize,myOrdinal and numeric_cast
#ifdef DGM_MESH_DEBUG_CONNECTIVITY
    for (size_t i=0; i<mesh.con.size(); ++i) cout << mesh.con[i] << endl;
#endif
    MPI_Type_free(&filetype);
    MPI_File_close(&fh);
    MPI_Info_free(&info);
    return disp;
  }

#endif  // DGM_PARALLEL

  /// Read a binary Mesh from a file using template defined types
  template <typename mySize, typename myOrdinal, typename myScalar>
  streamoff read_mesh(const string &fname, const streamoff offset,
                      Mesh &mesh, const Json::Value &header) {
    DGM::Comm::Ptr comm = mesh.get_comm();
#ifdef DGM_PARALLEL
    if (!mesh.valid_parallel()) {
      throw DGM::exception("read_mesh:  Must make sure that parallel "
                           "information is setup before doing parallel read");
    }
    return MPI_read_mesh<mySize,myOrdinal,myScalar>(fname,offset,mesh,header);
#endif
    ifstream fs(fname.c_str());
    if (!fs) throw DGM::exception("Could not open binary mesh file: "+fname);
    fs.seekg(offset);
    readConvert<mySize,DGM::Size>(fs,mesh.ne);
    if (fs.bad())
      throw DGM::exception("Could not read number of elements from "+fname);
    readConvert<myOrdinal,DGM::Ordinal>(fs,mesh.nsd);
    if (fs.bad())
      throw DGM::exception("Could now read number of space dimensions from "+
                           fname);
    if (mesh.ne<=0)
      throw DGM::exception("Illegal number of elements: "+asString(mesh.ne));
    if (mesh.nsd<1 || mesh.nsd>3)
      throw DGM::exception("Illegal number of space dimensions: "+
                           asString(mesh.nsd));
    DGM::Size glen;
    readConvert<mySize,DGM::Size>(fs,glen);
    if (fs.bad())
      throw DGM::exception("Could not read global length from "+fname);
    if (0) cout<<"    ne = "<<mesh.ne<<", nsd = "<<mesh.nsd
               <<", glen = "<<glen<<endl;
    mesh.etype.resize(mesh.ne);
    for (DGM::Size e=0; e<mesh.ne; e++)
      fs.read(reinterpret_cast<char*>(&mesh.etype[e]),
              sizeof(Topology::ElementType));
    if (fs.bad())
      throw DGM::exception("Error reading element types from "+fname);
    CMC::Vector<mySize,DGM::Size> disp(mesh.ne);
    for (DGM::Size e=0; e<mesh.ne; e++)
      fs.read(reinterpret_cast<char*>(&(disp[e])),sizeof(mySize));
    if (fs.bad())
      throw DGM::exception("Error reading displacements from "+fname);
    assert( glen == (DGM::Size)(disp[mesh.ne-1]+
                    mesh.nodes[mesh.etype[mesh.ne-1]]) );
    std::vector<Scalar> x, y, z;
    x.resize(glen);
    readConvert<myScalar,Scalar>(fs,x);
    if (fs.bad())
      throw DGM::exception("Error reading x coordinates from "+fname);
    if (mesh.nsd>1) {
      y.resize(glen);
      readConvert<myScalar,Scalar>(fs,y);
      if (fs.bad())
        throw DGM::exception("Error reading y coordinates from "+fname);
    }
    if (mesh.nsd>2) {
      z.resize(glen);
      readConvert<myScalar,Scalar>(fs,z);
      if (fs.bad())
        throw DGM::exception("Error reading z coordinates from "+fname);
    }
    mesh.point.clear();
    Scalar xl, yl, zl;
    for (Size e=0, i=0; e<mesh.ne; ++e) {
      for (unsigned n=0; n<mesh.nodes[mesh.etype[e]]; ++n, ++i) {
        if (mesh.nsd==1) {
          xl=x[i]; yl=0; zl=0;
        } else if (mesh.nsd==2) {
          xl=x[i]; yl=y[i]; zl=0;
        } else {
          xl=x[i]; yl=y[i]; zl=z[i];
        }
        Point p( xl, yl, zl );
        mesh.point.push_back(p);
      }
    }
    if (fs.bad()) throw DGM::exception("Unknown error reading "+fname);
    return fs.tellg();
  }

  /// Helper function to read the connectivity data
  template <typename mySize, typename myOrdinal>
  streamoff read_cn(const string &fname, const streamoff offset, Mesh &mesh,
                    const Json::Value &header) {
    DGM::Comm::Ptr comm = mesh.get_comm();
#ifdef DGM_PARALLEL
    if (!mesh.valid_parallel()) {
      throw DGM::exception("DGM::Mesh:  Must make sure that parallel "
                           "information is setup before doing parallel "
                           "read_connectivity");
    }
    return MPI_read_cn<mySize,myOrdinal>(fname,offset,mesh,header);
#endif
    ifstream fs(fname.c_str());
    if (!fs) error("Error opening connectivity file "+fname);
    fs.seekg(offset);
    if (fs.bad()) error("Error seeking connectivity offset from "+fname);

    // read data displacements
#ifdef DGM_MESH_DEBUG_CONNECTIVITY
    cout<<"mesh.ne = "<<mesh.ne<<", sizeof(mesh.ne) = "<<sizeof(mesh.ne)
        <<", sizeof(myOrdinal) = "<<sizeof(myOrdinal)<<endl;
    cout<<"numeric_limits<Ordinal>::max() = "
        <<numeric_limits<Ordinal>::max()<<endl;
    cout<<"numeric_limits<Size>::max() = "
        <<numeric_limits<Size>::max()<<endl;
#endif
    CMC::Vector<mySize,myOrdinal> D(numeric_cast<myOrdinal>(mesh.ne));
    fs.read(reinterpret_cast<char*>(D.ptr()),mesh.ne*sizeof(mySize));
    if (fs.bad()) error("Error reading data displacements from "+fname);

    // read data lengths
    CMC::Vector<myOrdinal,myOrdinal> L(numeric_cast<myOrdinal>(mesh.ne));
    fs.read(reinterpret_cast<char*>(L.ptr()),mesh.ne*sizeof(myOrdinal));
    if (fs.bad()) error("Error reading data lengths from "+fname);

    // get sizes
    const uint64_t len = L.Sum();
    // read connectivity data
    if (header["Version"]==0)
      mesh.con.resize(len/5);  // Original Con had 5 ints
    else
      mesh.con.resize(len);
#ifdef DGM_MESH_DEBUG_CONNECTIVITY
    // Debug information
    cout << "Displacements = " << endl;
    cout << D;
    cout << "Lengths = " << endl;
    cout << L;
    const uint64_t ConSize = mesh.con_size();
    cout << "  ConSize = " << ConSize << endl;
    cout << "  con.size() = " << mesh.con.size() << endl;
    cout << "  L.Sum() = " << L.Sum() << endl;
#endif
    typedef Mesh::Con<mySize,myOrdinal> myCon;
    readConvert<myCon,Mesh::MyCon>(fs,mesh.con);
#ifdef DGM_MESH_DEBUG_CONNECTIVITY
    for (size_t i=0; i<mesh.con.size(); ++i) cout << mesh.con[i] << endl;
#endif
    if (fs.bad()) error("Error reading connectivity data from "+fname);
    return fs.tellg();
  }

}  // end anonymous namespace

/// Read a mesh given types defined in a Json header
streamoff Mesh::read(const string &fname, const streamoff offset,
                     const Json::Value &header) {
  if ( (header.isMember("Verbose")) && (header["Verbose"].asInt() > 0) )
      comm->cout() << "Using Mesh::read with: " << header;
  // typically the header is now populated with original DGM types
  if (header.empty())
    return read_mesh<int,int,Scalar>(fname,offset,*this,header);
  const Json::Value &types =
    header.isMember("Types") ?  header["Types"] : header;
  // check the byte order
  if (types.isMember("ByteOrder")) {
    DGM::ByteOrder byteOrder;
    if (!byteOrder.is(types["ByteOrder"].asString())) {
      throw DGM::exception("Mesh file "+fname+" is incompatible: "
                           "ByteOrder = "+types["ByteOrder"].asString()+
                           "\n  while code expects "+byteOrder.asString());
    }
  }
  // use the default types from original DGM (but they are now populated
  // in Domain::read_header
  if (types.empty())
    return read_mesh<int,int,Scalar>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int32" &&
            types["LocalSize"].asString() == "int32" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<int32_t,int32_t,double>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int32" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<int64_t,int32_t,double>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int64" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<int64_t,int64_t,double>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int32" &&
            types["LocalSize"].asString() == "int32" &&
            types["Scalar"].asString() == "float32" )
    return read_mesh<int32_t,int32_t,float>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint32" &&
            types["LocalSize"].asString() == "uint32" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<uint32_t,uint32_t,double>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int32" &&
            types["Scalar"].asString() == "float32" )
    return read_mesh<int64_t,int32_t,float>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int64" &&
            types["Scalar"].asString() == "float32" )
    return read_mesh<int64_t,int64_t,float>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint64" &&
            types["LocalSize"].asString() == "uint64" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<uint64_t,uint64_t,double>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint64" &&
            types["LocalSize"].asString() == "int32" &&
            types["Scalar"].asString() == "float64" )
    return read_mesh<uint64_t,int32_t,double>(fname,offset,*this,header);
  else
    throw DGM::exception("Unknown data types in file "+fname);
  return read_mesh<Size,Ordinal,Scalar>(fname,offset,*this,header);
}

/// Read a mesh given types defined in a Json header
streamoff Mesh::read_connectivity(const string &fname, const streamoff offset,
                                  const Json::Value &header) {
  if (header.isMember("Verbose"))
    if (header["Verbose"].asInt() > 0)
      comm->cout() << "Using Mesh::read_connectivity with: " << header;
  if (header.empty())
    return read_cn<int,int>(fname,offset,*this,header);
  const Json::Value &types =
    header.isMember("Types") ?  header["Types"] : header;
  // check the byte order
  if (types.isMember("ByteOrder")) {
    DGM::ByteOrder byteOrder;
    if (!byteOrder.is(types["ByteOrder"].asString())) {
      throw DGM::exception("Connectivity file "+fname+" is incompatible: "
                           "ByteOrder = "+types["ByteOrder"].asString()+
                           "\n  while code expects "+byteOrder.asString());
    }
  }
  // use the default types from original DGM
  if (types.empty())
    return read_cn<int,int>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int32" &&
            types["LocalSize"].asString() == "int32")
    return read_cn<int32_t,int32_t>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint32" &&
            types["LocalSize"].asString() == "uint32")
    return read_cn<uint32_t,uint32_t>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int32")
    return read_cn<int64_t,int32_t>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "int64" &&
            types["LocalSize"].asString() == "int64")
    return read_cn<int64_t,int64_t>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint64" &&
            types["LocalSize"].asString() == "uint64")
    return read_cn<uint64_t,uint64_t>(fname,offset,*this,header);
  else if ( types["GlobalSize"].asString() == "uint64" &&
            types["LocalSize"].asString() == "int32")
    return read_cn<uint64_t,int32_t>(fname,offset,*this,header);
  else
    throw DGM::exception("Unknown data types in file "+fname);
  return read_cn<Size,Ordinal>(fname,offset,*this,header);
}

/// Read a binary Mesh from a file (deprecated)
streamoff Mesh::read(const string &fname, const streamoff offset) {
  comm->cout() << "  Mesh::read("<<fname<<","<<offset<<")" << endl;
  typedef int mySize;
  typedef DGM::Ordinal myOrdinal;
  typedef DGM::Scalar myScalar;
#ifdef DGM_PARALLEL
  if (!valid_parallel()) {
    throw DGM::exception("DGM::Mesh:  Must make sure that parallel information"
                         " is setup before doing parallel read");
  }
  return MPI_read(comm,partition,fname,offset);
#endif
  ifstream fs(fname.c_str());
  if (!fs) throw DGM::exception("Could not open binary mesh file: "+fname);
  fs.seekg(offset);
  readConvert<mySize,DGM::Size>(fs,ne);
  if (fs.bad())
    throw DGM::exception("Could not read number of elements from "+fname);
  readConvert<myOrdinal,DGM::Ordinal>(fs,nsd);
  if (fs.bad())
    throw DGM::exception("Could now read number of space dimensions from "+
                         fname);
  if (ne<=0) throw DGM::exception("Illegal number of elements: "+asString(ne));
  if (nsd<1 || nsd>3)
    throw DGM::exception("Illegal number of space dimensions: "+asString(nsd));
  GlobalSize glen;
  readConvert<mySize,GlobalSize>(fs,glen);
  if (fs.bad())
    throw DGM::exception("Could not read global length from "+fname);
  if (1) cout<<"    ne = "<<ne<<", nsd = "<<nsd<<", glen = "<<glen<<endl;
  etype.resize(ne);
  for (GlobalSize e=0; e<ne; e++)
    fs.read(reinterpret_cast<char*>(&etype[e]),sizeof(Topology::ElementType));
  if (fs.bad())
    throw DGM::exception("Error reading element types from "+fname);
  CMC::Vector<GlobalSize,GlobalSize> disp(ne);
  for (GlobalSize e=0; e<ne; e++)
    fs.read(reinterpret_cast<char*>(&(disp[e])),sizeof(GlobalSize));
  if (fs.bad())
    throw DGM::exception("Error reading displacements from "+fname);
  assert( glen == (GlobalSize)(disp[ne-1]+nodes[etype[ne-1]]) );
  std::vector<Scalar> x, y, z;
  x.resize(glen);
  readConvert<myScalar,Scalar>(fs,x);
  if (fs.bad())
    throw DGM::exception("Error reading x coordinates from "+fname);
  if (nsd>1) {
    y.resize(glen);
    readConvert<myScalar,Scalar>(fs,y);
    if (fs.bad())
      throw DGM::exception("Error reading y coordinates from "+fname);
  }
  if (nsd>2) {
    z.resize(glen);
    readConvert<myScalar,Scalar>(fs,z);
    if (fs.bad())
      throw DGM::exception("Error reading z coordinates from "+fname);
  }
  point.clear();
  Scalar xl, yl, zl;
  for (GlobalSize e=0, i=0; e<ne; ++e) {
    for (unsigned n=0; n<nodes[etype[e]]; ++n, ++i) {
      if (nsd==1) {
        xl=x[i]; yl=0; zl=0;
      } else if (nsd==2) {
        xl=x[i]; yl=y[i]; zl=0;
      } else {
        xl=x[i]; yl=y[i]; zl=z[i];
      }
      Point p( xl, yl, zl );
      point.push_back(p);
    }
  }
  if (fs.bad()) throw DGM::exception("Unknown error reading "+fname);
  return fs.tellg();
}

/// Read binary connectivity information to file (deprecated)
/** \note Not updated for new file format */
streamoff Mesh::read_connectivity(const string &fname,
                                  const streamoff offset) {
  cout << "Mesh::read_connectivity("<<fname<<","<<offset<<")" << endl;
#ifdef DGM_PARALLEL
  if (!valid_parallel()) {
    throw DGM::exception("DGM::Mesh:  Must make sure that parallel information"
                         " is setup before doing parallel read_connectivity");
  }
  return MPI_read_connectivity(comm,partition,fname,offset);
#endif
  ifstream fs(fname.c_str());
  if (!fs) error("Error opening file "+fname);
  fs.seekg(offset);
  if (fs.bad()) error("Error seeking offset from "+fname);

  // read data displacements
  const LocalSize lne = numeric_cast<LocalSize>(ne);
  iVector D(lne);
  fs.read(reinterpret_cast<char*>(&(D[0])),ne*sizeof(int));
  if (fs.bad()) error("Error reading data displacements from "+fname);

  // read data lengths
  iVector L(lne);
  fs.read(reinterpret_cast<char*>(&(L[0])),ne*sizeof(int));
  if (fs.bad()) error("Error reading data lengths from "+fname);

  // get sizes
  const size_t ConSize = MyCon::size();
  const size_t len = L.Sum();
#ifdef DGM_MESH_DEBUG
  // Debug information
  cout << "Displacements = " << endl;
  cout << D;
  cout << "Lengths = " << endl;
  cout << L;
  cout << "  ConSize = " << ConSize << endl;
  cout << "  con.size() = " << con.size() << endl;
  cout << "  L.Sum() = " << L.Sum() << endl;
#endif
  // read connectivity data
  con.resize(len);
#if 0
  typedef int mySize;
  typedef DGM::Ordinal myOrdinal;
  typedef DGM::Scalar myScalar;
  typedef Con<mySize,myOrdinal> myCon;
  readConvert<myCon,MyCon>(fs,con);
  for (size_t i=0; i<con.size(); ++i) cout << con[i] << endl;
#else
  fs.read(reinterpret_cast<char*>(&con.front()),len*ConSize);
#endif
  if (fs.bad()) error("Error reading connectivity data from "+fname);
#ifdef DGM_MESH_DEBUG
  for (size_t i=0; i<con.size(); ++i) cout << con[i] << endl;
#endif
  return fs.tellg();
}

/// Write binary connectivity information to file (deprecated)
/** \note This has been refactored to use variable datatypes. */
streamoff Mesh::write_connectivity(const string &fname,
                                   const streamoff offset) const {
  comm->cout() << "  Mesh::write_connectivity("<<fname<<","<<offset<<")"<<endl;
#ifdef DGM_PARALLEL
  if (!valid_parallel()) {
    throw DGM::exception("DGM::Mesh:  Must make sure that parallel information"
                         " is setup before doing parallel write_connectivity");
  }
  return MPI_write_connectivity(comm,partition,fname,offset);
#endif
  fstream fs;
  if (offset!=0)
    fs.open(fname.c_str(), ios::out|ios::in);
  else
    fs.open(fname.c_str(), ios::out);
  if (!fs) error("Error opening file "+fname);
  fs.seekp(offset);
  if (fs.bad()) error("Error seeking offset in file "+fname);
  const size_t ConSize = MyCon::size();
  CMC::Vector<GlobalSize,GlobalSize> D(ne);
  CMC::Vector<LocalSize,GlobalSize> L(ne);
  D = 0; L = 0;
  GlobalSize e = 0;
  D[e] = 0;
  for (size_t i=0; i<con.size(); ++i) {
    const GlobalSize eid = con[i].eid;
    if (eid >= ne)
      throw DGM::exception("Element out of range in reading "+fname);
    if (eid!=e) { // Only works if con is increasing order.
                  // does this catch the last one?
      D[eid] = D[e]+L[e];
      e = eid;
    }
    L[e] += 1;   // Old v0 format used ConSize here...
  }
#ifdef DGM_MESH_DEBUG_CONNECTIVITY
  // Debug information
  cout << "Displacements = " << endl;
  cout << D;
  cout << "Lengths = " << endl;
  cout << L;
  cout << "  ConSize = " << ConSize << endl;
  cout << "  con.size() = " << con.size() << endl;
  cout << "  L.Sum() = " << L.Sum() << endl;
#endif
  fs.write(reinterpret_cast<const char*>(D.ptr()),D.size()*sizeof(GlobalSize));
  fs.write(reinterpret_cast<const char*>(L.ptr()),L.size()*sizeof(LocalSize));
  const GlobalSize len = D[ne-1]+L[ne-1];
  fs.write(reinterpret_cast<const char*>(&con.front()),len*ConSize);
  //for (size_t i=0; i<con.size(); ++i) cout << con[i] << endl;
  if (fs.bad())
    error("Error in Mesh::write_connectivity_binary.  Write to file " +fname+
          "failed.  Disk full?");
  return fs.tellp();
}

/// Write curve file
void Mesh::write_curve(const string &fname) const {
  comm->cout() << "  Mesh::write_curve("<<fname<<")" << endl;
#ifdef DGM_PARALLEL
  throw DGM::exception("DGM::Mesh: Writing crv file only available in serial.");
#endif
  int ncrv = 0;
  for (vector<bool>::size_type ii=0; ii<crv_els.size(); ii++)
    if (crv_els[ii]) ncrv++;
  ofstream crv(fname.c_str());
  crv << "** Curved Sides **\n\n"
      << "2 Number of curve type(s)\n\n"
      << "Straight\nskewed\n\n"
      << "Affine\naffine\n\n"
      << ncrv << " Number of curved side(s)\n\n";
  // zero (is_curved true), one (is_affine true)
  vector<int> crv_elems(crv_els.begin(), crv_els.end());
  for (vector<bool>::size_type ii=0; ii<crv_els.size(); ii++)
    if (crv_els[ii]) {
      crv << ii << " 0 skewed\n";
      crv_elems[ii] = 0;
    }
    else {
      crv_elems[ii] = 1;
    }
  crv.close();
#ifdef DGM_PARALLEL
  // write binary curve file
  namespace mpi = boost::mpi;
  mpi::communicator world;
  cv_file cf(fname, world);
  cv_data cvd[2];
  cvd[0] = cv_data("Straight", "skewed");
  cvd[1] = cv_data("Affine", "affine");
  write_curve_types(cvd, cvd+2, cf);
  // locally owned global element ids
  GlobalSize* e_it = partition->eid_data(), *e_end = e_it + partition->ne();
  // sizes for each element (number of sides for each locally owned element)
  vector<unsigned int> nsides(crv_elems.size());
  vector<Topology::ElementType>::const_iterator et_it = etype.begin();
  for (int i=0; et_it != etype.end(); ++et_it, ++i)
    nsides[i] = Topology::num_sides(*et_it);
  // write the binary curve file
  GlobalSize gne = partition->gne();
  write_curved_elements(gne, e_it, e_end, crv_elems.begin(),
                        nsides.begin(), cf);
#endif
}

void Mesh::CopyIn(const vector<Element*> &el) {
  for (size_t i=0; i<con.size(); ++i) {
    const GlobalSize eid = con[i].eid;
    const LocalSize side = con[i].side;
    const Element *e = el[eid];
    const Side *s    = e->side[side];
    const GlobalSize gid = s->link ? s->link->gid() : s->base->gid();
    con[i].gid = gid;
  }
  // Make sure that the connectivity is sorted
  sort( con.begin(), con.end() );
}

#ifdef DGM_PARALLEL

/** \note Perhaps this should use typeinfo to handle all element types. */
void Mesh::CopyIn(ifstream &in, const vector<Element*> &el,
                  const Partition<Size,Ordinal,Scalar>::Ptr partition) {
  etype.resize(el.size());
  for (size_t i=0; i<el.size(); ++i) {
    const Element *e = el[i];
    //use type_id.name()
    //if (typeid(e).name() == typeid(DGM::SpectralHex).name())
    //  etype[i] = Mesh::SpectralHex;
    //etype[i] = e->type_id();
    switch (e->nVerts()) {
      case 2 : etype[i] = Topology::Line; break;
      case 3 : etype[i] = Topology::Tri ; break;
      case 4 : etype[i] = Topology::Quad; break;
      case 8 : etype[i] = Topology::Hex ; break;
    default :
      throw DGM::exception("Unknown element type in Mesh::CopyIn"); break;
    }
  }
  point.clear();
  for (size_t i=0; i<el.size(); ++i) {
    const Element *e = el[i];
    for (Ordinal n=0; n<e->nVerts(); ++n) {
      point.push_back(*e->vert[n]);
    }
  }
  con.clear();
  string buffer;
  char type;
  GlobalSize eid, leid;
  LocalSize sid, lsid;
  getline(in,buffer);
  getline(in,buffer);
  typedef pair<GlobalSize,LocalSize> lnk;
  map<lnk,lnk> links;
  while (in >> type >> eid >> sid >> leid >> lsid) {
    getline(in,buffer);
    const lnk from(eid,sid), to(leid,lsid);
    const map<lnk,lnk>::value_type m(from,to);
    links.insert(m);
  }
  for (size_t i=0; i<el.size(); ++i) {
    const Element *e = el[i];
    for (LocalSize n=0; n<e->nSides(); ++n) {
      const GlobalSize gid = (e->side[n]->link ? e->side[n]->link->gid() :
                              e->side[n]->base->gid());
      const lnk from(partition->eid(i),n);
      if (!links.count(from)) {
        const GlobalSize leid = Mesh::undefined<GlobalSize>();
        const LocalSize lsid = Mesh::undefined<LocalSize>();
        Mesh::MyCon c(partition->eid(i), n, leid, lsid, gid);
        con.push_back(c);
      } else {
        const lnk to = links[from];
        const GlobalSize leid = to.first;
        const LocalSize lsid = to.second;
        Mesh::MyCon c(partition->eid(i), n, leid, lsid, gid);
        con.push_back(c);
      }
    }
  }
}

/// Write a Mesh file using MPI parallel I/O
MPI_Offset Mesh::MPI_write(const Comm::Ptr comm,
                           const Partition<Size,Ordinal,Scalar>::Ptr partition,
                           const string &fname,
                           const MPI_Offset offset) const {
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype, inttype;
  MPI_Offset disp = offset;
  int stat;

  MPI_Info info;
  stat = MPI_Info_create(&info);
  if (stat) comm->error("MPI_Info_create", stat);

  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> byte_disp(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      byte_disp[i]=partition->eid(i)*sizeof(int);
    stat = MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                                    &byte_disp.front(), MPI_INT, &inttype);
    if (stat) comm->error("MPI_Type_create_hindexed", stat);
  }
  stat = MPI_Type_commit(&inttype);
  if (stat) comm->error("MPI_Type_commit", stat);

  stat = MPI_File_open(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
                       const_cast<char*>(fname.c_str()),
                       MPI_MODE_WRONLY | MPI_MODE_CREATE, info, &fh);
  if (stat) comm->error("MPI_File_open", stat);
  // MPI_File_set_atomicity(fh,1);

  // write the global number of elements
  // comm->Barrier();
  stat = MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  if (stat) comm->error("MPI_File_set_view", stat);
  int gne = partition->gne();
  MPI_File_write_all(fh, &gne, 1, MPI_INT, &status);
  disp += sizeof(int);

  // write the global number of space dimensions
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  const int num_spatial=nsd;
  MPI_File_write_all(fh, const_cast<int*>(&num_spatial), 1, MPI_INT, &status);
  disp += sizeof(int);

  // write the global data length
  const int len = point.size();
  int glen;
  comm->SumAll(&len,&glen,1);
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_write_all(fh, const_cast<int *>(&glen), 1, MPI_INT, &status);
  disp += sizeof(int);

  // write the element types
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_write_all(fh, const_cast<Topology::ElementType *>(&(etype.front())),
                     partition->ne(),MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  // make the data lengths
  intVector L(partition->ne());
  intVector D(partition->ne());
  int count = 0;
  for (LocalSize e=0; e<partition->ne(); e++) L[e] = Mesh::nodes[etype[e]];
  for (LocalSize e=0; e<partition->ne(); e++) count += L[e];
  partition->global_scan(D,L);

  // write data displacements
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_write_all(fh, D.data(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  // setup data types
  MPI_Type_indexed(partition->ne(), L.data(), D.data(), MPI_DOUBLE, &filetype);
  MPI_Type_commit(&filetype);

  dVector x(count), y(count), z(count);
  for (int i=0; i<count; ++i) {
    x[i] = point[i].x;
    y[i] = point[i].y;
    z[i] = point[i].z;
  }
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);
  MPI_File_write_all(fh, x.data(), count, MPI_DOUBLE, &status);
  disp += glen*sizeof(Scalar);
  if (nsd>1) {
    // comm->Barrier();
    MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);
    MPI_File_write_all(fh, y.data(), count, MPI_DOUBLE, &status);
    disp += glen*sizeof(Scalar);
  }
  if (nsd>2) {
    // comm->Barrier();
    MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);
    MPI_File_write_all(fh, z.data(), count, MPI_DOUBLE, &status);
    disp += glen*sizeof(Scalar);
  }
  MPI_Type_free(&filetype);
  MPI_Type_free(&inttype);
  MPI_File_close(&fh);
  MPI_Info_free(&info);
  return disp;
}

/// Read a Mesh file using MPI parallel I/O
/** \todo Need to add a verbosity flag
    \note gne here is not 64bit safe
*/
MPI_Offset Mesh::MPI_read(const Comm::Ptr comm,
                          const Partition<Size,Ordinal,Scalar>::Ptr partition,
                          const string &fname, const MPI_Offset offset) {
  const int verb=comm->verbosity();
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype, inttype;
  MPI_Offset disp = offset;
  MPI_Info info;
  int stat;
  stat = MPI_Info_create(&info);
  if (stat) comm->error("MPI_Info_create", stat);
  if (verb>1) comm->cout() << "  Mesh::MPI_read" << endl;

  ne = partition->ne();

  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> byte_disp(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      byte_disp[i]=partition->eid(i)*sizeof(int);
    stat = MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                                    &byte_disp.front(), MPI_INT, &inttype);
    if (stat) comm->error("MPI_Type_create_hindexed", stat);
  }
  stat = MPI_Type_commit(&inttype);
  if (stat) comm->error("MPI_Type_commit", stat);
  if (verb>2) comm->cout() << "  MPI_Type_commit" << endl;
  stat = MPI_File_open(dynamic_cast<const DGM::MpiComm*>
                       (comm.get())->mpi_comm,
                       const_cast<char*>(fname.c_str()),
                       MPI_MODE_RDWR | MPI_MODE_CREATE, info, &fh);
  if (stat) {
    comm->cout() << "Error opening file, " << fname << endl;
    comm->error("MPI_File_open", stat);
  }
  if (verb>2) comm->cout() << "  Completed MPI_File_open" << endl;
  // MPI_File_set_atomicity(fh,1);

  // read the global number of elements
  int gne;
  // comm->Barrier();
  stat = MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  if (stat) comm->error("MPI_File_set_view", stat);
  MPI_File_read_all(fh, &gne, 1, MPI_INT, &status);
  disp += sizeof(int);
  if ( gne != (int)partition->gne() ) {
    comm->cout() << "gne = " << gne << endl;
    comm->cout() << "partition->gne = " << partition->gne() << endl;
    assert( gne == (int)partition->gne() );
  }
  if (verb>2) comm->cout() << "  Read global number of elements" << endl;

  // read the _global number of space dimensions
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_read_all(fh, &nsd, 1, MPI_INT, &status);
  disp += sizeof(int);
  if (verb>2) comm->cout()<<"  Read global number of space dimensions" << endl;

  // read the global data length
  int glen;
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, native, info);
  MPI_File_read_all(fh, &glen, 1, MPI_INT, &status);
  disp += sizeof(int);
  if (verb>2) comm->cout() << "  Read global data length" << endl;

  // read the element types
  etype.resize(partition->ne());
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_read_all(fh, &(etype.front()), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);
  if (verb>2) comm->cout() << "  Read element types" << endl;
  // read data displacements
  intVector D(partition->ne());
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_read_all(fh, D.data(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);
  if (verb>2) comm->cout() << "  Read data displacements" << endl;

  // make the data lengths
  intVector L(partition->ne());
  int len = 0;
  for (Ordinal e=0; e<partition->ne(); e++) {
    L[e] = Mesh::nodes[etype[e]];
    len += L[e];
  }
  int global_len =0;
  comm->SumAll(&len,&global_len,1);
  if (verb>2) comm->cout() << "  Made the data lengths" << endl;

  MPI_Type_indexed(partition->ne(), L.data(), D.data(), MPI_DOUBLE, &filetype);
  MPI_Type_commit(&filetype);
  // comm->Barrier();
  MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);

  dVector x(len), y, z;
  MPI_File_read_all(fh, x.data(), len, MPI_DOUBLE, &status);
  disp += glen*sizeof(Scalar);
  if (verb>1) comm->cout() << "  Read x" << endl;
  if (nsd>1) {
    y.resize(len);
    // comm->Barrier();
    MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);
    MPI_File_read_all(fh, y.data(), len, MPI_DOUBLE, &status);
    disp += glen*sizeof(Scalar);
    if (verb>1) comm->cout() << "  Read y" << endl;
  }
  if (nsd>2) {
    z.resize(len);
    // comm->Barrier();
    MPI_File_set_view(fh, disp, MPI_DOUBLE, filetype, native, info);
    MPI_File_read_all(fh, z.data(), len, MPI_DOUBLE, &status);
    disp += glen*sizeof(Scalar);
    if (verb>1) comm->cout() << "  Read z" << endl;
  }
  if (verb>2) comm->cout() << "  Starting to make points" << endl;
  Scalar xl, yl, zl;
  point.clear();
  for (Size e=0, i=0; e<ne; e++) {
    for (unsigned n=0; n<nodes[etype[e]]; n++, i++) {
      if (nsd==1) {
        xl=x[i], yl=0, zl=0;
      } else if (nsd==2) {
        xl=x[i], yl=y[i], zl=0;
      } else {
        xl=x[i], yl=y[i], zl=z[i];
      }
      Point p( xl, yl, zl );
      point.push_back(p);
    }
  }
  if (verb>2) comm->cout() << "  Completed making points" << endl;
  MPI_Type_free(&filetype);
  MPI_Type_free(&inttype);
  MPI_Info_free(&info);
  MPI_File_close(&fh);
  if (verb>2) comm->cout() << "  Completed Mesh::MPI_read" << endl;
  return disp;
}

/// Read a Mesh file using MPI parallel I/O
/** \warning This needs to be updated for variable Ordinal/Size types
    \todo Need to add a verbosity flag. */
MPI_Offset Mesh::MPI_read_connectivity
(const Comm::Ptr comm,
 const Partition<Size,Ordinal,Scalar>::Ptr partition,
 const string &fname, const MPI_Offset offset) {
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype, inttype;
  MPI_Offset disp = offset;
  MPI_Info info;
  int stat;
  stat = MPI_Info_create(&info);
  if (stat) comm->error("MPI_Info_create", stat);

  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> byte_disp(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      byte_disp[i]=partition->eid(i)*sizeof(int);
    stat = MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                                    &byte_disp.front(), MPI_INT, &inttype);
    if (stat) comm->error("MPI_Type_create_hindexed", stat);
  }
  stat = MPI_Type_commit(&inttype);
  if (stat) comm->error("MPI_Type_commit", stat);

  stat = MPI_File_open(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
                       const_cast<char*>(fname.c_str()),
                       MPI_MODE_RDWR | MPI_MODE_CREATE, info, &fh);
  if (stat) comm->error("MPI_File_open", stat);
  // MPI_File_set_atomicity(fh,1);

  // read data displacements
  intVector D(partition->ne());
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_read_all(fh, D.ptr(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  const int ConSize = MyCon::size();
  // read data lengths
  intVector L(partition->ne());
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_read_all(fh, L.ptr(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  const int len = L.Sum();

  con.resize(len/ConSize);

  MPI_Type_indexed(partition->ne(), L.ptr(), D.ptr(), MPI_INT, &filetype);
  MPI_Type_commit(&filetype);
  MPI_File_set_view(fh, disp, MPI_INT, filetype, native, info);
  MPI_File_read_all(fh, &(con.front()), len, MPI_INT, &status);

  MPI_Type_free(&filetype);
  MPI_Type_free(&inttype);
  MPI_File_close(&fh);
  MPI_Info_free(&info);
  return disp;
}

/// Write a binary connectivity information to file
/** Get the element index where the node is inside and returns element
    number

    \warning This is wrong...
    \todo This needs to be updated to read data lengths
*/
MPI_Offset Mesh::MPI_write_connectivity
(const Comm::Ptr comm,
 const Partition<Size,Ordinal,Scalar>::Ptr partition,
 const string &fname, const MPI_Offset offset) const {
  comm->cout() << "WARNING: MPI_write_connectivity has not been "
                  "thoroughly tested" << endl;
  const char *cnative="native";
  char *native = const_cast<char*>(cnative);
  MPI_File fh;
  MPI_Status status;
  MPI_Datatype filetype, inttype;
  MPI_Offset disp = offset;
  MPI_Info info;
  int stat;
  stat = MPI_Info_create(&info);
  if (stat) comm->error("MPI_Info_create", stat);

  intVector ilen(partition->ne()); ilen = 1;
  {
    std::vector<MPI_Aint> byte_disp(partition->ne());
    for (LocalSize i=0; i<partition->ne(); ++i)
      byte_disp[i]=partition->eid(i)*sizeof(int);
    stat = MPI_Type_create_hindexed(partition->ne(), ilen.data(),
                                    &byte_disp.front(), MPI_INT, &inttype);
    if (stat) comm->error("MPI_Type_create_hindexed", stat);
  }
  stat = MPI_Type_commit(&inttype);
  if (stat) comm->error("MPI_Type_commit", stat);

  stat = MPI_File_open(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpi_comm,
                       const_cast<char*>(fname.c_str()),
                       MPI_MODE_WRONLY | MPI_MODE_CREATE, info, &fh);
  if (stat) comm->error("MPI_File_open", stat);
  // MPI_File_set_atomicity(fh,1);

  // make the data lengths and displacements
  const int ConSize = numeric_cast<int>(MyCon::size());
  intVector D(partition->ne());
  intVector L(partition->ne());
  D = 0; L = 0;
  int e  = con[0].eid;
  int le = partition->inc(e);
  int len = 0;
  for (size_t i=0; i<con.size(); ++i) {
    const int eid = con[i].eid;
    if (eid!=e) {
      e  = eid;
      le = partition->inc(e);
    }
    L[le] += ConSize;
    len += L[le];
  }
  partition->global_scan(D,L);

  // write data displacements
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_write_all(fh, D.ptr(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  // write data lengths
  MPI_File_set_view(fh, disp, MPI_INT, inttype, native, info);
  MPI_File_write_all(fh, L.ptr(), partition->ne(), MPI_INT, &status);
  disp += partition->gne()*sizeof(int);

  // write connectivity data
  MPI_Type_indexed(partition->ne(), L.data(), D.data(), MPI_INT, &filetype);
  MPI_Type_commit(&filetype);
  MPI_File_set_view(fh, disp, MPI_INT, filetype, native, info);
  MPI_File_write_all(fh, const_cast<Mesh::MyCon *>(&(con.front())),
                     len, MPI_INT, &status);

  MPI_Type_free(&filetype);
  MPI_Type_free(&inttype);
  MPI_File_close(&fh);
  MPI_Info_free(&info);
  return disp;
}

#endif  // DGM_PARALLEL

/** Get the element index where the node is inside and returns element number
    including the point.
    \note This only works in 2d
    \todo This should use an iVector for the elemindex, not a int*
    \todo This likely should use the STL search and/or find routine [SSC]
*/
Size Mesh::find_source_elem(Point pnode, Size *elemindex, const int verb) {
  Scalar x_min, x_max, y_min, y_max, nx, ny;
  unsigned nverts=0;
  assert(nsd==2);  // NOTE that this only works in 2d

  // node coordinates x,y
  nx = pnode.x;
  ny = pnode.y;

  if (verb>1) cout<<"pnode.x = "<<nx<<", pnode.y = "<<ny<<endl;

  // Variable for searching
  Scalar A[5], tmp[5], Asum;   // A[3] for trangular
  Scalar din;
  int npass1, npass2, isin;
  npass1=npass2=isin=0;
  Asum=0;
  Size maxelm=0;
  Size pointn=0;
  for (Size i=0; i<ne; i++) {
    switch(etype[i]) {
    case Topology::Line:
    case Topology::NodalLine:
    case Topology::SpectralLine:
      nverts = 2;
      break;
    case Topology::Quad:
    case Topology::NodalQuad:
    case Topology::SpectralQuad:
      nverts = 4;
      break;
    case Topology::Tri:
    case Topology::NodalTri:
      nverts = 3;
      break;
    default:
      DGM::Comm::World->cerr()<<"Mesh::find_source_elem() unsupported "
        "element type: "<<etype[i]<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
      break;
    }
    // define coordinate bounding box
    x_min = x_max = point[pointn].x;
    y_min = y_max = point[pointn].y;
    for(unsigned m=1;m<nverts;m++) {
      check_bounds( point[pointn+m].x, x_min, x_max );
      check_bounds( point[pointn+m].y, y_min, y_max );
    }

    // continue search if the node lies outside the bounding box (cheap test)
    if (x_max < nx ||x_min > nx||y_max < ny||y_min > ny) {
      pointn =pointn+nverts;
      continue;
    }

    // cout << "in bounding box " << i << " " << nx << " " << ny << endl;

    // continue search if the node lies outside the true element boundaries
    for(unsigned j =0; j<nverts;j++) {
      tmp[j] = get_phase_angle(point[pointn+j].x-nx,point[pointn+j].y-ny);
      // cout << point[pointn+j].x << " " << point[pointn+j].y << endl;
    }

    // Add the beginning points
    tmp[nverts] = get_phase_angle(point[pointn].x-nx,point[pointn].y-ny);

    for(unsigned j=0; j<nverts;j++) {
      A[j] = (tmp[j+1]-tmp[j])/pi;
      // cout<<"tmp[j] ="<<tmp[j]<<" "<<tmp[j+1]<<endl;
      // cout<<"A[j] ="<<A[j]<<endl;
    }

    for(unsigned j=0; j<nverts;j++) {
      A[j] = A[j] + 2.0 * ( (A[j]<-1 ? 1.0 : 0.0) - (A[j]>1 ? 1.0 : 0.0) );
      Asum = Asum +A[j];
      if(fabs(A[j]-1.0)<EPSILON) npass2=1;
      if(fabs(A[j]+1.0)<EPSILON) npass1=1;
      // cout<<"A1[j] ="<<A[j]<<endl;
    }
    // cout<<"Asum ="<<Asum<<endl;
    // cout<<"npass = "<<npass1<<" "<<npass2<<endl;

    isin = abs(npass2-npass1);
    npass1 = npass2 = 0;
    din = (fabs(Asum)-isin)/2.0;

    isin = (int)din;
    if ((din-isin)>EPSILON) isin++;
    Asum = 0;

    // Check for vortexs
    for(unsigned j=0;j<nverts;j++) {
      if(sqrt((nx-point[pointn+j].x)*(nx-point[pointn+j].x)+
              (ny-point[pointn+j].y)*(ny-point[pointn+j].y))<EPSILON) {
        isin=1;
        break;
      }
    }
    // cout<<"isin2 = "<<isin<<endl;
    if(isin ==1) {
      isin =0;
      din=0;
      // save the current elment ID
      elemindex[maxelm] = i;
      maxelm++;
    }
    if(maxelm==4) break; // reaching the maximum element index
    pointn = pointn +nverts;
  }
  return maxelm;
}

namespace {

bool is_in_element_2d(const Point &pnode,
                      const std::vector<Point> &vertex,
                      const unsigned nside,
                      const Scalar epsilon) {
  const Scalar nx = pnode.x;
  const Scalar ny = pnode.y;
  bool is_in = true;
  for(unsigned i=0; i<nside && is_in; ++i) {
    const unsigned j =  (i+1)%nside;
    const Scalar x1 =  vertex[i].x;
    const Scalar y1 =  vertex[i].y;

    const Scalar x2 =  vertex[j].x;
    const Scalar y2 =  vertex[j].y;

    // compute face vector
    const Scalar fx = x2 - x1;
    const Scalar fy = y2 - y1;

    const Scalar px = nx - x1;
    const Scalar py = ny - y1;

    const Scalar cross = fx*py - fy*px;

    is_in = (-epsilon <= cross);
    // Extra check that the vertex are clockwise
    static bool check = true;
    if (check) {
      const unsigned k =  (j+1)%nside;
      const Scalar x3 =  vertex[k].x;
      const Scalar y3 =  vertex[k].y;
      const Scalar gx = x3 - x1;
      const Scalar gy = y3 - y1;
      const Scalar c = fx*gy - fy*gx;
      if (c < 0) {
        cout << " WARNING: found clockwise element."<<endl;
        cout << " vertex for element:";
        for (unsigned l=0; l<nside; ++l)
           cout << "("<<vertex[l].x<<", "<<vertex[l].y<<")  ";
        cout <<endl;
        check = false;
      }
    }
  }
  // Check for vortices
  for(unsigned i=0; i<nside && !is_in; ++i) {
    const Scalar x = nx-vertex[i].x;
    const Scalar y = ny-vertex[i].y;
    if( x*x + y*y < epsilon*epsilon) is_in = true;
  }
  return is_in;
}

bool is_in_element_3d_tet(const Point &pnode,
                      const std::vector<Point> &vertex,
                      const unsigned nside,
                      const Scalar epsilon) {

  if (nside!=4)
    error("Mesh::is_in_element_3d_tet "
          " Only works for tet elements.");
  static const unsigned v_num[4][3] = {{0,1,2},
                                       {0,3,1},
                                       {1,3,2},
                                       {0,2,3}};

  bool is_in = true;
  for(unsigned i=0; i<nside && is_in; ++i) {
    const unsigned *I=v_num[i];

    Scalar v1[3], v2[3], v3[3];
    for (unsigned j=0; j<3; j++) {
      v1[j] = vertex[I[1]][j] - vertex[I[0]][j];
      v2[j] = vertex[I[2]][j] - vertex[I[0]][j];
      v3[j] =        pnode[j] - vertex[I[0]][j];
    }
    const Scalar dot_cross  =
         v3[0]*(v1[1]*v2[2] - v1[2]*v2[1])
      -  v3[1]*(v1[0]*v2[2] - v1[2]*v2[0])
      +  v3[2]*(v1[0]*v2[1] - v1[1]*v2[0]);

    is_in = -epsilon <= dot_cross;
    // Extra check that the vertex are clockwise
    static bool check = true;
    if (check) {
      const unsigned k[4] = {3,2,0,1};
      for (unsigned j=0; j<3; j++)
        v3[j] = vertex[k[i]][j] - vertex[I[0]][j];

      const Scalar c  =
           v3[0]*(v1[1]*v2[2] - v1[2]*v2[1])
        -  v3[1]*(v1[0]*v2[2] - v1[2]*v2[0])
        +  v3[2]*(v1[0]*v2[1] - v1[1]*v2[0]);
      if (c < 0) {
        cout << " WARNING: found clockwise element."<<endl;
        cout << " vertex for element:";
        for (unsigned l=0; l<nside; ++l)
           cout << "("<<vertex[l].x<<", "<<vertex[l].y<<")  ";
        cout <<endl;
        check = false;
      }
    }
  }
  // Check for vortices
  for(unsigned i=0; i<nside && !is_in; ++i) {
    const Scalar x = pnode.x-vertex[i].x;
    const Scalar y = pnode.y-vertex[i].y;
    const Scalar z = pnode.z-vertex[i].z;
    if( x*x + y*y + z*z < epsilon*epsilon) is_in = true;
  }
  return is_in;
}

} // end anonymous namespace

/** Index_into_point_vector is returned from boxes for the given element
    number. */
bool Mesh::is_in_element_line(const Point &pnode,
                              const std::vector<Point> &vertex,
                              const Scalar epsilon) {
  const Scalar nx = pnode.x;
  bool is_in=false;
  // check to see if pnode is inside element
  if (nx >= vertex[0].x && nx <= vertex[1].x) {
    is_in = true;
  }
  // Check for vortices
  for(unsigned j=0; j<2 && !is_in; ++j) {
    const Scalar x = nx-vertex[j].x;
    if( x*x < epsilon*epsilon) is_in = true;
  }
  return is_in;
}

bool Mesh::is_in_element_tri(const Point &pnode,
                             const std::vector<Point> &vertex,
                             const Scalar epsilon) {
  return is_in_element_2d(pnode, vertex, 3, epsilon);
}

bool Mesh::is_in_element_tet(const Point &pnode,
                             const std::vector<Point> &vertex,
                             const Scalar epsilon) {
  return is_in_element_3d_tet(pnode, vertex, 4, epsilon);
}

bool Mesh::is_in_element_quad(const Point &pnode,
                              const std::vector<Point> &vertex,
                              const Scalar epsilon) {
  return is_in_element_2d(pnode, vertex, 4, epsilon);
}

bool Mesh::is_in_element_hex(const Point &pnode,
                             const std::vector<Point> &vertex,
                             const Scalar epsilon) {
  const unsigned nverts  = 8;
  const unsigned nsides  = 6;
  const unsigned nfverts = 4;
  const Scalar   inv_nfverts = 0.25;
  const unsigned v_num[nsides][nfverts] =
        {{0,1,2,3},{0,1,5,4},{1,2,6,5},
         {3,2,6,7},{0,3,7,4},{4,5,6,7}};

  // face orientation based on exodusII standard hex element
  const Scalar orient[6] = {-1.0,1.0,1.0,-1.0,-1.0,1.0};
  const Scalar nx = pnode.x;
  const Scalar ny = pnode.y;
  const Scalar nz = pnode.z;
  dMatrix face_coords(nfverts,3);
  dVector a(3), b(3), a_cross_b(3);
  dVector point_vec(3), face_center(3);
  bool is_in = true;
  for(unsigned i =0; i<nsides && is_in; ++i) {
    for(unsigned j =0; j<nfverts; ++j) {
      face_coords[j][0] = vertex[v_num[i][j]].x;
      face_coords[j][1] = vertex[v_num[i][j]].y;
      face_coords[j][2] = vertex[v_num[i][j]].z;
    }

    // compute face normal
    a[0] = face_coords[2][0] - face_coords[0][0];
    a[1] = face_coords[2][1] - face_coords[0][1];
    a[2] = face_coords[2][2] - face_coords[0][2];

    b[0] = face_coords[3][0] - face_coords[1][0];
    b[1] = face_coords[3][1] - face_coords[1][1];
    b[2] = face_coords[3][2] - face_coords[1][2];

    a_cross_b[0] = orient[i]*(a[1]*b[2] - a[2]*b[1]);
    a_cross_b[1] = orient[i]*(a[2]*b[0] - a[0]*b[2]);
    a_cross_b[2] = orient[i]*(a[0]*b[1] - a[1]*b[0]);

    // compute face center
    face_center[0] = face_coords[0][0];
    face_center[1] = face_coords[0][1];
    face_center[2] = face_coords[0][2];
    for(unsigned j =1; j<nfverts; ++j) {
      face_center[0] += face_coords[j][0];
      face_center[1] += face_coords[j][1];
      face_center[2] += face_coords[j][2];
    }
    face_center[0] *= inv_nfverts;
    face_center[1] *= inv_nfverts;
    face_center[2] *= inv_nfverts;

    point_vec[0] = nx - face_center[0];
    point_vec[1] = ny - face_center[1];
    point_vec[2] = nz - face_center[2];

    const Scalar dot =
          a_cross_b[0]*point_vec[0] +
          a_cross_b[1]*point_vec[1] +
          a_cross_b[2]*point_vec[2];
    is_in = (dot <= epsilon);
  }
  // Check for vortices
  for(unsigned i=0; i<nverts && !is_in; ++i) {
    const Scalar x = nx-vertex[i].x;
    const Scalar y = ny-vertex[i].y;
    const Scalar z = nz-vertex[i].z;
    if( x*x + y*y + z*z < epsilon*epsilon) is_in = true;
  }
  return is_in;
}

/// First attempt to find elements for 1D Line elements.
/** \todo May be better to add to find_source_elem(). */
Size Mesh::find_source_elem_1d(Point pnode, Size *elemindex) {
  Scalar x_min, x_max;
  const unsigned nverts=2;

  assert(nsd==1);  // NOTE that this only works in 1d

  //node coordinates x,y
  const Scalar nx = pnode.x;

  Size maxelm=0;
  Size pointn=0;

  for (Size i=0; i<ne; i++) {
    // define coordinate bounding box
    x_min = x_max = point[pointn].x;
    check_bounds( point[pointn+1].x, x_min, x_max );
    // continue search if the node lies outside the bounding box (cheap test)
    if (x_max < nx || x_min > nx) {
      pointn = pointn+nverts;
      continue;
    }
    // check to see if pnode is inside element
    vector<Point> points(2);
    points[0] = point[pointn];
    points[1] = point[pointn+1];
    if(is_in_element_line(pnode, points, EPSILON)) {
      // save the current element ID
      elemindex[maxelm] = i;
      maxelm++;
    }
    if(maxelm==2) break; // reaching the maximum element index
    pointn = pointn +nverts;
  }
  return maxelm;
}

/// First attempt to find elements for quad and tri elements.
/** \todo May be better to add to find_source_elem(). */
Size Mesh::find_source_elem_2d(Point pnode, Size *elemindex) {
  assert(nsd==2);  // NOTE that this only works in 2d

  //node coordinates x,y
  const Scalar nx = pnode.x;
  const Scalar ny = pnode.y;

  Size maxelm = 0;
  Size pointn = 0;

  for (Size i=0; i<ne; ++i) {
    unsigned nsides = 0;
    switch(etype[i]) {
    case Topology::Quad:         nsides  = 4; break;
    case Topology::NodalQuad:    nsides  = 4; break;
    case Topology::SpectralQuad: nsides  = 4; break;
    case Topology::Tri:          nsides  = 3; break;
    case Topology::NodalTri:     nsides  = 3; break;
    default:
      DGM::Comm::World->cerr()<<"Mesh::find_source_elem_2d() unsupported "
        "element type: "<<etype[i]<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
      break;
    }

    // define coordinate bounding box
    Scalar x_min, x_max, y_min, y_max;
    x_min = x_max = point[pointn].x;
    y_min = y_max = point[pointn].y;

    for(unsigned m=1;m<nsides;m++) {
      check_bounds( point[pointn+m].x, x_min, x_max );
      check_bounds( point[pointn+m].y, y_min, y_max );
    }

    // continue search if the node lies outside the bounding box (cheap test)
    if (x_max < nx || x_min > nx || y_max < ny || y_min > ny) {
      pointn = pointn+nsides;
      continue;
    }

    vector<Point> points(nsides);
    for (unsigned j=0; j<nsides; ++j) points[j] = point[pointn+j];
    if(is_in_element_2d (pnode, points, nsides, EPSILON)) {
      // save the current elment ID
      elemindex[maxelm] = i;
      maxelm++;
    }
    if(maxelm==4) break; // reaching the maximum element index
    pointn = pointn +nsides;
  }
  return maxelm;
}

namespace {

  void set_indices(vector<size_t> &indices,
                   const vector<Topology::ElementType> &etype) {
    const size_t ne = etype.size();
    indices.resize(ne);
    size_t pointn=0;
    for (size_t i=0; i<ne; ++i) {
      indices[i] = pointn;
      unsigned nverts=0;
      switch(etype[i]) {
        case Topology::Hex:          nverts = 8; break;
        case Topology::Quad:         nverts = 4; break;
        case Topology::Tri:          nverts = 3; break;
        case Topology::Line:         nverts = 2; break;
        case Topology::NodalHex:     nverts = 8; break;
        case Topology::NodalTet:     nverts = 4; break;
        case Topology::NodalQuad:    nverts = 4; break;
        case Topology::NodalTri:     nverts = 3; break;
        case Topology::NodalLine:    nverts = 2; break;
        case Topology::SpectralLine: nverts = 2; break;
        case Topology::SpectralQuad: nverts = 4; break;
        case Topology::SpectralHex:  nverts = 8; break;
        default:
          DGM::Comm::World->cerr()<<"Mesh::boxes() unsupported element "
            "type: "<<etype[i]<<endl;
          DGM::Comm::World->exit(DGM::FAILURE);
      }
      pointn += nverts;
    }
  }

} // end anonymous namespace

vector<float> Mesh::box(const Size element_number) {
  if (indices.empty()) set_indices(indices, etype);
  const Size i=element_number;
  unsigned nverts=0;
  switch(etype[i]) {
    case Topology::Hex:          nverts = 8; break;
    case Topology::Quad:         nverts = 4; break;
    case Topology::Tri:          nverts = 3; break;
    case Topology::Line:         nverts = 2; break;
    case Topology::NodalHex:     nverts = 8; break;
    case Topology::NodalTet:     nverts = 4; break;
    case Topology::NodalQuad:    nverts = 4; break;
    case Topology::NodalTri:     nverts = 3; break;
    case Topology::NodalLine:    nverts = 2; break;
    case Topology::SpectralLine: nverts = 2; break;
    case Topology::SpectralQuad: nverts = 4; break;
    case Topology::SpectralHex:  nverts = 8; break;
    default:
      DGM::Comm::World->cerr()<<"Mesh::boxes() unsuppoted element "
        "type: "<<etype[i]<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
      break;
  }
  // define coordinate bounding box
  std::vector<float> bounds(6);
  bounds[0] = bounds[1] = bounds[2] = std::numeric_limits<float>::max();
  bounds[3] = bounds[4] = bounds[5] = std::numeric_limits<float>::min();
  for (size_t m=indices[i]; m<nverts+indices[i]; ++m) {
    for (unsigned j=0; j<3; ++j) {
      if (point[m][j] < bounds[j+0]) bounds[j+0]=point[m][j];
      if (bounds[j+3] < point[m][j]) bounds[j+3]=point[m][j];
    }
  }
  return bounds;
}

/** The return vector are indexes into the Mesh's Point array where each
    element starts.  Used in the call to is_in_element. */
void Mesh::boxes(vector< vector<float> > &bounds) {
  bounds.clear(); bounds.reserve(ne);
  for (Size i=0; i<ne; ++i) bounds.push_back(box(i));
}

bool Mesh::is_in_element(const Scalar * const xyz,
                         const size_t element_number) {
  unsigned nverts=0;
  if (indices.empty()) set_indices(indices, etype);
  const size_t index_into_points = indices[element_number];
  switch(etype[element_number]) {
    case Topology::Hex:          nverts = 8; break;
    case Topology::Quad:         nverts = 4; break;
    case Topology::Tri:          nverts = 3; break;
    case Topology::Line:         nverts = 2; break;
    case Topology::NodalHex:     nverts = 8; break;
    case Topology::NodalTet:     nverts = 4; break;
    case Topology::NodalQuad:    nverts = 4; break;
    case Topology::NodalTri:     nverts = 3; break;
    case Topology::NodalLine:    nverts = 2; break;
    case Topology::SpectralLine: nverts = 2; break;
    case Topology::SpectralQuad: nverts = 4; break;
    case Topology::SpectralHex:  nverts = 8; break;
    default:
      DGM::Comm::World->cerr()<<"Mesh::is_in_element() unsupported element "
        "type: "<<etype[element_number]<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
      break;
  }
  vector<Point> vertex(nverts);
  for (unsigned m=0; m<nverts; ++m) vertex[m] = point[index_into_points+m];
  Point obs_point;
  if (0<nsd) obs_point.x = xyz[0];
  if (1<nsd) obs_point.y = xyz[1];
  if (2<nsd) obs_point.z = xyz[2];
  bool inside=false;
  switch (etype[element_number]) {
    case Topology::Hex:
    case Topology::NodalHex:
    case Topology::SpectralHex:
      inside = is_in_element_hex(obs_point,vertex,EPSILON);
      break;
    case Topology::Quad:
    case Topology::NodalQuad:
    case Topology::SpectralQuad:
      inside = is_in_element_quad(obs_point,vertex,EPSILON);
      break;
    case Topology::Tri:
    case Topology::NodalTri:
      inside = is_in_element_tri(obs_point,vertex,EPSILON);
      break;
    case Topology::Line:
    case Topology::NodalLine:
    case Topology::SpectralLine:
      inside = is_in_element_line(obs_point,vertex,EPSILON);
      break;
    default:
      DGM::Comm::World->cerr()<<"Mesh::is_in_element() unsupported element "
        "type: "<<etype[element_number]<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
  }
  return inside;
}

/// First attempt to find elements for Hex elements.
/** \todo May be better to add to find_source_elem(). */
Size Mesh::find_source_elem_3d(Point pnode, Size *elemindex) {
  const unsigned nverts=8;
  Scalar x_min, x_max, y_min, y_max, z_min, z_max;

  assert(nsd==3);  // NOTE that this only works in 3d

  // node coordinates x,y
  const Scalar nx = pnode.x;
  const Scalar ny = pnode.y;
  const Scalar nz = pnode.z;

  Size maxelm=0;
  Size pointn=0;

  for (Size i=0; i<ne; ++i) {

    if ( (etype[i] != Topology::Hex        ) &&
         (etype[i] != Topology::NodalHex   ) &&
         (etype[i] != Topology::SpectralHex)    ) {
      DGM::Comm::World->cerr()<<"Mesh::find_source_elem_3d() unsupported for "
        "element type: "<<etype[i] <<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }

    // define coordinate bounding box
    x_min = x_max = point[pointn].x;
    y_min = y_max = point[pointn].y;
    z_min = z_max = point[pointn].z;

    for(unsigned m=1; m<nverts; m++) {
      check_bounds( point[pointn+m].x, x_min, x_max );
      check_bounds( point[pointn+m].y, y_min, y_max );
      check_bounds( point[pointn+m].z, z_min, z_max );
    }

    // continue search if the node lies outside the bounding box (cheap test)
    if (x_max < nx || x_min > nx || y_max < ny ||
        y_min > ny || z_max < nz || z_min > nz) {
      pointn = pointn+nverts;
      continue;
    }

    vector<Point> points(8);
    for (unsigned j=0; j<8; ++j) points[j] = point[pointn+j];
    if (is_in_element_hex(pnode, points, EPSILON)) {
      elemindex[maxelm] = i;  // save the current element ID
      maxelm++;
    }
    if(maxelm==8) break;      // reaching the maximum element index
    pointn = pointn + nverts;
  }
  return maxelm;
}

/// Helper function that find the min and max bounds for a range of values
void Mesh::check_bounds(const Scalar coord, Scalar &min, Scalar &max) const {
  if (coord < min)
    min = coord;
  if (coord > max)
    max = coord;
  return;
}

/// SSC: don't remember what this is...
Scalar Mesh::get_phase_angle(const Scalar x, const Scalar y) {
  Scalar phase;
  if (y>0 && fabs(x)< EPSILON) {
    phase = pt5*pi;
    // cout << "1,x,y,phase " << x << " " << y << " " << phase << endl;
  } else if (y<0 && fabs(x)<EPSILON) {
    phase = three*pi*pt5;
    // cout << "2,x,y,phase " << x << " " << y << " " << phase << endl;
  } else if (x>0 && y>=0) {
    phase = atan(y/x);
    // cout << "3,x,y,phase " << x << " " << y << " " << phase << endl;
  } else if (x>0 && y<0) {
    phase = two*pi+atan(y/x);
    // cout << "4,x,y,phase " << x << " " << y << " " << phase << endl;
  } else {
    phase = pi+atan(y/x);
    // cout << "5,x,y,phase " << x << " " << y << " " << phase << endl;
  }
  return phase;
}

} // namespace DGM

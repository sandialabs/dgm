/** \file Field.cpp
    \brief DGM Field implementation
    \author Scott Collis
    \author Axel Gerstenberger
    \author Noel Belcourt
    \author James Overfelt 
*/

// system includes
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <limits>
#include <time.h>
#include <cassert>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

// boost includes
#include <boost/lexical_cast.hpp>
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#endif
#include <boost/algorithm/string/case_conv.hpp>

// DGM includes
#include "Field.hpp"
#include "EuclideanVector.hpp"
#include "String.hpp"
#include "Format.hpp"
#include "ParUtils.hpp"
#include "Color.hpp"
// DGM elements
#include "Line.hpp"
#include "NodalLine.hpp"
#include "SpectralLine.hpp"
#include "Quad.hpp"
#include "NodalQuad.hpp"
#include "SpectralQuad.hpp"
#include "Tri.hpp"
#include "NodalTri.hpp"
#include "Hex.hpp"
#include "SpectralHex.hpp"
#include "NodalHex.hpp"
#include "NodalTet.hpp"
#ifdef DGM_USE_COMPILETIMEQUAD
#include "CompileTimeQuad.hpp"
#endif
#ifdef DGM_USE_SLAB
#include "Slab.hpp"
#endif
// DGM element blocks
#include "QuadBlock.hpp"
#include "HexBlock.hpp"
// DGM partitioning and weights database
#include "Partition.tpp"
#include "WeightsDatabase.hpp"
#include "CaseInsensitiveString.hpp"
#ifdef DGM_USE_ZOLTAN
#include "Zoltan.hpp"
#include <Zoltan2_BasicVectorAdapter.hpp>
#include <Zoltan2_InputTraits.hpp>
#include <Zoltan2_PartitioningSolution.hpp>
#include <Zoltan2_PartitioningProblem.hpp>
#endif
// Json
#ifdef DGM_USE_JSON
#include "json/json.h"
#include "json/serialization.h"
#endif

namespace DGM {

// define Field static variables

const int Field::con2d[4][4] = {{1,1,0,0},
                                {1,1,0,0},
                                {0,0,1,1},
                                {0,0,1,1}};
// local anonymous namespace
namespace {

  typedef DGM::Size GlobalSize;
  typedef DGM::Ordinal LocalSize;

#ifdef DGM_USE_COMPILETIMEQUAD
  // Helper for creating quad elements
  Quad* new_quad(Ordinal e, const LocalSize pl, const LocalSize ql,
                 vector<Point>& X)
  {
    using boost::lexical_cast;
    using std::string;
    Quad *q = 0;
    // pl is the polynomial order
    switch (pl) {
      case 1:
        q = new CompileTimeQuad<1,3>(e,pl,ql,X);
        break;
      case 2:
        q = new CompileTimeQuad<2,4>(e,pl,ql,X);
        break;
      case 3:
        q = new CompileTimeQuad<3,5>(e,pl,ql,X);
        break;
      case 4:
        q = new CompileTimeQuad<4,6>(e,pl,ql,X);
        break;
      case 5:
        q = new CompileTimeQuad<5,7>(e,pl,ql,X);
        break;
      case 6:
        q = new CompileTimeQuad<6,8>(e,pl,ql,X);
        break;
      case 7:
        q = new CompileTimeQuad<7,9>(e,pl,ql,X);
        break;
      case 8:
        q = new CompileTimeQuad<8,10>(e,pl,ql,X);
        break;
      case 9:
        q = new CompileTimeQuad<9,11>(e,pl,ql,X);
        break;
      case 10:
        q = new CompileTimeQuad<10,12>(e,pl,ql,X);
        break;
      case 11:
        q = new CompileTimeQuad<11,13>(e,pl,ql,X);
        break;
      case 12:
        q = new CompileTimeQuad<12,14>(e,pl,ql,X);
        break;
      case 13:
        q = new CompileTimeQuad<13,15>(e,pl,ql,X);
        break;
      case 14:
        q = new CompileTimeQuad<14,16>(e,pl,ql,X);
        break;
      case 15:
        q = new CompileTimeQuad<15,17>(e,pl,ql,X);
        break;
      case 16:
        q = new CompileTimeQuad<16,18>(e,pl,ql,X);
        break;
      case 17:
        q = new CompileTimeQuad<17,19>(e,pl,ql,X);
        break;
      case 18:
        q = new CompileTimeQuad<18,20>(e,pl,ql,X);
        break;
      case 19:
        q = new CompileTimeQuad<19,21>(e,pl,ql,X);
        break;
      case 20:
        q = new CompileTimeQuad<20,22>(e,pl,ql,X);
        break;
      case 21:
        q = new CompileTimeQuad<21,23>(e,pl,ql,X);
        break;
      case 22:
        q = new CompileTimeQuad<22,24>(e,pl,ql,X);
        break;
      default:
        throw DGM::exception("Field: unable to allocate a new Quad for "
                             "p order " + lexical_cast<string>(pl));
    }
    return q;
  }
#endif

  // Helper functions for set_flip

  /// Are two scalars approximately equal
  template<typename Scalar>
  inline bool approx_equal(const Scalar u,   const Scalar v,
                           const Scalar REL, const Scalar ABS) {
    if (u == v) return true;
    const Scalar diff = std::abs(u - v);
    if (diff <= ABS) return true;
    const Scalar ref = std::max(std::abs(u),std::abs(v));
    return (diff <= REL*ref );
  }
  /// Are two scalars approximately less then
  template<typename Scalar>
  inline int approx_less(const Scalar u,   const Scalar v,
                         const Scalar REL, const Scalar ABS) {
    if      (approx_equal(u,v,REL,ABS)) return  0;
    else if (u<v)                       return  1;
    else                                return -1;
  }
  /// Return the sign of a scalar
  template <typename Scalar>
  int sgn(Scalar val) {
    return (val > Scalar(0)) - (val < Scalar(0));
  }

  /// Packing and unpacking operations
  enum Buf_Operation {COUNT, PACK, UNPACK};

#ifdef DGM_PARALLEL
  /// Pack and unpack vertex information from a buffer
  unsigned pack_unpack_buffer(Pcon<GlobalSize,LocalSize,Scalar> &pc,
                              vector<Point> &vert,
                              unsigned sdof,
                              const Element *el,
                              const DGM::Comm::Ptr comm,
                              const Buf_Operation op) {
    const LocalSize size = 8; // Tets, fill with 0's
    switch (op) {
    case COUNT : pc.len += 3*size;  break;
    case PACK :
      for (LocalSize k=0; k<size; ++k)
        for (int j=0; j<3; ++j)
          pc.buf[sdof++] = k < el->nVerts() ? (*el->vert[k])[j] : 0;
      break;
    case UNPACK :
      vert.resize(size);
      for (LocalSize k=0; k<size; ++k) {
        vert[k].x = pc.buf[sdof++];
        vert[k].y = pc.buf[sdof++];
        vert[k].z = pc.buf[sdof++];
      }
      break;
    }
    return sdof;
  }

  /// Pack and unpack a vector of vertex information
  map<Size,vector<Point> > pack_unpack_buffer
  ( vector< Pcon<GlobalSize,LocalSize,Scalar> > &pc,
    const vector<Element*> &el,
    const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition,
    const DGM::Comm::Ptr comm,
    const Buf_Operation op) {
    map<Size, vector<Point> > verts;
    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      Size sdof = 0;
      const Connect<GlobalSize,LocalSize> &cinfo = partition->cinfo[n];
      for (LocalSize i=0; i<cinfo.nsides; i++) {
        vector<Point> vert;
        const Link<GlobalSize,LocalSize> &link  = cinfo.links[i];
        const int elmtid  = link.elmtid;
        const int sideid  = link.sideid;
        const Element *e  = el[elmtid];
        sdof = pack_unpack_buffer(pc[n], vert, sdof, e, comm, op);
        if (op==UNPACK) verts[e->side[sideid]->gid()] = vert;
      }
    }
    return verts;
  }
#endif

  /// Share vertex information
  /** \note SendReceiveReplace avoids deadlock. */
  map <Size, vector<Point> > share_vertex
  (const vector<Element*> &el,
   const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition,
   const DGM::Comm::Ptr comm) {
    map<Size,vector<Point> > vertex;
#ifdef DGM_PARALLEL
    vector< Pcon<GlobalSize,LocalSize,Scalar> > pc(partition->ncprocs());
    pack_unpack_buffer(pc, el, partition, comm, COUNT);
    for (LocalSize n=0; n<partition->ncprocs(); n++)
      pc[n].buf.resize(pc[n].len);
    pack_unpack_buffer(pc, el, partition, comm, PACK);
    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      comm->SendReceiveReplace( pc[n].buf.data(),
                                pc[n].len,
                                partition->cinfo[n].cprocid,
                                partition->cinfo[n].cprocid,
                                partition->cinfo[n].cprocid,
                                comm->MyPID() );
    }
    vertex = pack_unpack_buffer(pc, el, partition, comm, UNPACK);
#endif  // DGM_PARALLEL
    return vertex;
  }

}  // unnamed namespace

#ifdef DGM_DOXYGEN
/// Activates debug information when setting the side flips and rotations
#define DGM_FLIP_DEBUG
#endif

/// Set the transpose and flips
/**
  In order to get the side quadrature points to align between two
  sides, we need to set the transpose and flip flags.  In 1D, no
  transpose or flips are required as a single point is matched
  between adjacent lines.  In 2D, no transpose is required, but the
  side->flip needs to be set so that the a-axes match (they point
  in the same direction, side->flip=false; and they point in the
  opposite direction, side->flip=true).

  For 3D Hexes, the transpose and both flips (a-axis and b-axis)
  need to be set.  THE TRANSPOSE AND FLIPS ARE APPLIED TO THE SIDE
  ON THE MASTER ELEMENT (which is usually the element with the
  smallest element id).  To help understand this, the following
  diagram and map are useful.

  \verbatim
        b
        |               sideVertMap( side->id, vertex index )
        |                                           side->id
        3-------2             v_num = { {0,1,2,3},     0     # back
       /.      /|                       {0,1,5,4},     1     # bottom
      / .     / |                       {1,2,6,5},     2     # right
     7------ 6  |                       {3,2,6,7},     3     # top
     |  0....|..1 --- a                 {0,3,7,4},     4     # left
     | .     | /                        {4,5,6,7} }    5     # front
     |.      |/
     4-------5          vertex index =   0 1 2 3
    /
   c
  \endverbatim

  Given two elements and their associated faces (e.g., a line from
  a root.con file:  "E 3 0 27 2").  The element nodes match such
  that we have the following situation.

  \verbatim
        Element 27        Element 3
        Face 2            Face 0
             a1
             |
             |            b0
             2 . . . . . .|. 2
            /|            | /|
           / |            |/ | a0
          6 . . . . . . . 3  |/
          |  1 . . . . . .|. 1
          | /             | /
          |/              |/
          5 . . . . . . . 0
         /
        b1
  \endverbatim

  In face coordinates, the a-axis goes from vertex index = 0 to
  vertex index = 1, and the b-axis goes from vertex index = 0 to
  vertex index = 3.

  To align the quadrature points between the two sides, we first
  determine if the a-axes are parallel, a0.a1 = [+1,-1] (a0 indicates
  the a-axis on the master element, and a1 the a-axis on the slave
  element).  If the a-axes are not parallel, the transpose flag is
  set to true (side->transp = true), indicating after a transpose
  we would have

  \verbatim
        Element 27        Element 3
        Face 2            Face 0
             a1
             |
             |            A0
         a1p 2 . . . . . .|. 2
          | /|            | /|
          |/ |            |/ | B0
          6 . . . . . . . 1  |/
          |  1 . . . . . .|. 3
          | /             | /
          |/              |/
          5 . . . . . . . 0
         /
        b1
  \endverbatim

  To determine if the axes are pointing with or against each other,
  we test the sign of A0.a1 = b0.a1 = [+1,-1] (-1 => side->flip =
  true) and B0.b1 = a0.b1 = [+1,-1] (-1 => side->flip_b = true).
  Note: because we transpose the quadrature points in the physics
  and not here, we work with the original a0 and b0 axes (we are
  just setting the transpose and flip flags; not actually doing it
  yet).

  Note that the original face orientations could have been shown
  as the above with A0.a1 ~ +1.  Because A0 uses different nodes
  than a1 to create its vector AND the face could be highly skewed,
  they are not necessarily parallel.  Therefore we need to also
  test a0.a1p = [+1,-1] when determining if the a-axes are parallel
  (where a1p goes from vertex index = 3 to vertex index = 2).

  For 3D Tets, the transpose and both flip need to be set.
  THE TRANSPOSE AND FLIPS ARE APPLIED TO THE SIDE
  ON THE MASTER ELEMENT (which is usually the element with the
  smallest element id).  To help understand this, the following
  diagram and map are useful.

  \verbatim
        b
        |               sideVertMap( side->id, vertex index )
        |                                           side->id
        3                     v_num = { {0,1,2},     0     # bottom
       /. \                             {0,1,3},     1     # right
      / .  \                            {1,2,3},     2     # back
     /  .   \                           {0,2,3}}     3     # left
    /   0    \
   /  /   \   \
  /____________\
 2              1       vertex index =   0 1 2

  \endverbatim

*/
void Field::set_flip(const bool pc) {
  if (verb>1) comm->cout()<<"  Field::set_flip()"<<endl;
  map<Size, vector<Point> > remote_vertex;
  // Only need to communicate during parallel construction in 3d
  if (pc && _nsd==3) {
    //comm->cout()<<"share_vertex"<<endl;
    remote_vertex = share_vertex(el, partition, comm);
    //comm->Barrier();
    //comm->cout()<<"end share_vertex"<<endl;
  }
  for (size_t e=0; e<el.size(); ++e) {
    for (Ordinal i=0; i<el[e]->nSides(); ++i) {
      Side *side = el[e]->side[i];
      if ( side->base && side->link ) {
        if (_nsd==1 || el[e]->element_type() == Topology::Slab ) {
          side->flip_a(false);
          side->flip_b(false);
          side->transp(false);
        } else if (_nsd==2) {
          side->flip_a((bool)con2d[side->id()][side->link->id()]);
          side->flip_b(false);
          side->transp(false);
        } else if (_nsd==3) {
          if (!side)
            throw DGM::exception("Field::set_flip: Illegal side");
          if (!side->link)
            throw DGM::exception("Field::set_flip: Illegal side link");
          if (!side->elink)
            throw DGM::exception("Field::set_flip: Illegal side elink");
          if (!side->link->elink && !remote_vertex.count(side->gid()))
            throw DGM::exception("Field::set_flip: Illegal side link elink");
#ifdef DGM_FLIP_DEBUG
          if (side->link->elink)
            cout << "------------------------------------------------------\n"
              << "Element id = " << e << " side id = " << side->id()
              << " connected to Element id = " << side->link->elink->gid()
              << " side id = " << side->link->id() << endl;
#endif
          /// \todo rewrite this with vector dot products like the hex version.
          if (side->q2() == 1 && side->q1() != 1) {
            if (side->link->q2() == 1 && side->link->q1() != 1) {
              vector<iMatrix> P(6);
              {
                const Ordinal I[3][3]={{1,0,0},{0,1,0},{0,0,1}};
                Ordinal J[3] = {0,1,2};
                for (Ordinal p=0; p<6; ++p, next_permutation(J,J+3)) {
                  P[p].resize(3,3);
                  for (Ordinal i=0; i<3; ++i) {
                    for (Ordinal j=0; j<3; ++j) P[p][i][j] = I[i][J[j]];
                  }
                }
              }
              // This is a tri face use special tri logic
              const Ordinal V0[3] = {el[e]->sideVertMap(side->id(),0),
                                     el[e]->sideVertMap(side->id(),1),
                                     el[e]->sideVertMap(side->id(),2)};
              const Ordinal V1[3] = {el[e]->sideVertMap(side->link->id(),0),
                                     el[e]->sideVertMap(side->link->id(),1),
                                     el[e]->sideVertMap(side->link->id(),2)};
              const Point T0[3] ={*side->elink->vert[V0[0]],
                                  *side->elink->vert[V0[1]],
                                  *side->elink->vert[V0[2]]};

              Point T1[3];
              if (side->link->elink) {
                 if (4==side->link->elink->vert.size()) {
                   T1[0] = *side->link->elink->vert[V1[0]];
                   T1[1] = *side->link->elink->vert[V1[1]];
                   T1[2] = *side->link->elink->vert[V1[2]];
                 } else {
                   T1[0] = T0[0];
                   T1[1] = T0[1];
                   T1[2] = T0[2];
                 }
              } else {
                 T1[0] = remote_vertex.find(side->gid())->second[V1[0]];
                 T1[1] = remote_vertex.find(side->gid())->second[V1[1]];
                 T1[2] = remote_vertex.find(side->gid())->second[V1[2]];
              }

              iMatrix I(3,3,0);
              {
                const Scalar zero(0);
                for (Ordinal i=0; i<3; ++i)
                  for (Ordinal j=0; j<3; ++j)
                    I[i][j]=approx_equal(zero,T0[i].distance_sq(T1[j]),
                                         repsM,aepsM);
              }
              const iMatrix zero(3,3,0);
              if (zero == I) { // \todo HACK HACK HACK for periodic
                const Point C0 = (T0[0] + T0[1] + T0[2])/3;
                const Point C1 = (T1[0] + T1[1] + T1[2])/3;
                const Point  T = C1 - C0;
                const Point N[3] = {T0[0]+T, T0[1]+T, T0[2]+T};
                const Scalar zero(0);
                for (Ordinal i=0; i<3; ++i)
                  for (Ordinal j=0; j<3; ++j)
                    I[i][j]=approx_equal(zero,N[i].distance_sq(T1[j]),
                                         repsM,aepsM);
              }
              side->transp(false);
              side->flip_a(false);
              side->flip_b(false);
              Ordinal p = 0;
              for (p=0; p<6; p++) if (I==P[p]) break;
              switch (p) {
                case 0: // V0[0]==V1[0], V0[1]==V1[1], V0[2]==V1[2]
                  side->transp(false);
                  side->flip_a(false);
                  side->flip_b(false);
                  break;
                case 1: // V0[0]==V1[0], V0[1]==V1[2], V0[2]==V1[1] flip about 0
                  side->transp(false);
                  side->flip_a(true );
                  side->flip_b(false);
                  break;
                case 2: // V0[0]==V1[1], V0[1]==V1[0], V0[2]==V1[2] flip about 2
                  side->transp(false);
                  side->flip_a(true );
                  side->flip_b(true );
                  break;
                case 3: // V0[0]==V1[1], V0[1]==V1[2], V0[2]==V1[0] rotate clock
                  side->transp(true );
                  side->flip_a(true );
                  side->flip_b(false);
                  break;
                case 4: // V0[0]==V1[2], V0[1]==V1[0], V0[2]==V1[1] rotate counter
                  side->transp(true );
                  side->flip_a(false);
                  side->flip_b(true );
                  break;
                case 5: // V0[0]==V1[2], V0[1]==V1[1], V0[2]==V1[0] flip about 1
                  side->transp(false);
                  side->flip_a(false);
                  side->flip_b(true );
                  break;
                default :
                  throw DGM::exception("Error in determining the flip and "
                                       "rotation for adjacent sides in the "
                                       "Tet mesh.");
              }
            }
          } else {  // standard Quad Face.
            const Ordinal v00 = el[e]->sideVertMap(side->id(),0);
            const Ordinal v01 = el[e]->sideVertMap(side->id(),1);
            const Ordinal v03 = el[e]->sideVertMap(side->id(),3);

            // make a shorthand for the Euclidean vector type
            typedef EuclideanVector Vec;

            Vec a0(*(side->elink->vert[v01]),*(side->elink->vert[v00]));
            Vec b0(*(side->elink->vert[v03]),*(side->elink->vert[v00]));
#ifdef DGM_FLIP_DEBUG
            const Ordinal v02 = el[e]->sideVertMap(side->id(),2);
            cout << "p00="<< side->elink->vert[v00] << endl;
            cout << "p01="<< side->elink->vert[v01] << endl;
            cout << "p02="<< side->elink->vert[v02] << endl;
            cout << "p03="<< side->elink->vert[v03] << endl;
#endif
            a0.normalize();
            b0.normalize();

            const Ordinal v10 = el[e]->sideVertMap(side->link->id(),0);
            const Ordinal v11 = el[e]->sideVertMap(side->link->id(),1);
            const Ordinal v12 = el[e]->sideVertMap(side->link->id(),2);
            const Ordinal v13 = el[e]->sideVertMap(side->link->id(),3);

            // when constructing in parallel, the linked elements across
            // a parallel partition are not available.  For now, generate an
            // error message, but this needs to be fixed
            if (!side->link->elink && !remote_vertex.count(side->gid()))
              throw DGM::exception("Unset side element link on element "+
                                   asString(e)+" local side "+asString(i)+
                                   " side-id "+asString(side->id())+"\n This"
                                   " is a known issue with the binary mesh "
                                   "reader");

            // An idea is to pick a default orientation for all parallel sides
            // so that both partitions flip to the same orientation

            Vec a1 = side->link->elink ?
              Vec(*(side->link->elink->vert[v11]),
                  *(side->link->elink->vert[v10])) :
              Vec(remote_vertex.find(side->gid())->second[v11],
                  remote_vertex.find(side->gid())->second[v10]);

            Vec b1 = side->link->elink ?
              Vec(*(side->link->elink->vert[v13]),
                  *(side->link->elink->vert[v10])) :
              Vec(remote_vertex.find(side->gid())->second[v13],
                  remote_vertex.find(side->gid())->second[v10]);

            Vec a1p = side->link->elink ?
              Vec(*(side->link->elink->vert[v12]),
                  *(side->link->elink->vert[v13])) :
              Vec(remote_vertex.find(side->gid())->second[v12],
                  remote_vertex.find(side->gid())->second[v13]);

#ifdef DGM_FLIP_DEBUG
            if (side->link->elink) {
              cout<<"p10="<< side->link->elink->vert[v10] << endl;
              cout<<"p11="<< side->link->elink->vert[v11] << endl;
              cout<<"p12="<< side->link->elink->vert[v12] << endl;
              cout<<"p13="<< side->link->elink->vert[v13] << endl;
            } else
              cout<<"p10="<<remote_vertex.find(side->gid())->second[v10]<<endl;
              cout<<"p11="<<remote_vertex.find(side->gid())->second[v11]<<endl;
              cout<<"p12="<<remote_vertex.find(side->gid())->second[v12]<<endl;
              cout<<"p13="<<remote_vertex.find(side->gid())->second[v13]<<endl;
            }
#endif
            a1.normalize();
            b1.normalize();
            a1p.normalize();

            // initialize to false on all flips (just to be safe)
            side->transp(false);
            side->flip_a(false);
            side->flip_b(false);

            const Scalar a0da1  = a0.dot(a1);
            const Scalar a0da1p = a0.dot(a1p);

#ifdef DGM_FLIP_DEBUG
            cout << "a0  = ("<< a0.x <<", "<< a0.y <<", "<< a0.z <<")"<< endl;
            cout << "a1  = ("<< a1.x <<", "<< a1.y <<", "<< a1.z <<")"<< endl;
            cout << "a1p = ("<< a1p.x<<", "<< a1p.y<<", "<< a1p.z<<")"<< endl;
            cout << "a0.a1  = " << a0da1 << endl;
            cout << "a0.a1p = " << a0da1p << endl;
#endif
            // parallel - parallel
            if ( approx_equal( abs(a0da1 ), one, repsM, aepsM ) ||
                 approx_equal( abs(a0da1p), one, repsM, aepsM ) ) {
              const Scalar b0db1  = b0.dot(b1);
#ifdef DGM_FLIP_DEBUG
              cout << "Parallel: a0.a1 = " << sgn(a0da1) << ", b0.b1 = "
                   << sgn(b0db1) << endl;
#endif
              side->transp(false);
              if (sgn(a0da1) == -1 ) side->flip_a(true);
              if (sgn(b0db1) == -1 ) side->flip_b(true);
            } else {  // transpose
              const Scalar b0da1 = b0.dot(a1);
              const Scalar a0db1 = a0.dot(b1);
#ifdef DGM_FLIP_DEBUG
              cout << "Transposed: b0.a1 = " << sgn(b0da1) << ", a0.b1 = "
                   << sgn(a0db1) << endl;
#endif
              side->transp(true);
              if (sgn(b0da1) == -1 ) side->flip_a(true);
              if (sgn(a0db1) == -1 ) side->flip_b(true);
            }
          }
        } else {
          throw DGM::exception("Illegal nsd in Field::side_flip, nsd = " +
                               asString(_nsd));
        }
      }
    }
  }
  if (verb>5) comm->cout() << "  Finished set_flip" << endl;
}

/** Constructs Field from an external mesh file (new parallel construction)

    \note This routine is experimental and uses a new ordering to build the
    Field to prevent the severe memory constraints that the older version has.

    \param[in] p default polynomial order
    \param[in] q default quadrature order
    \param[in] root_ root file name
    \param[in] name_ name of this Field
    \param[in] domain_partition parallel partition for the parent Domain
    \param[in] parallel denotes that you want to use parallel construction
    \param[in] comm_ communicator for this object
    \param[in] p_inc increment in polynomial order
    \param[in] blocksize blocksize if doing element blocks
*/
Field::Field(const Ordinal p, const Ordinal q,
             const std::string &root_, const std::string &name_,
             Partition<GlobalSize,LocalSize,Scalar>::Ptr &domain_partition,
             const int parallel, const unsigned numeqns, const int physics,
             const DGM::Comm::Ptr comm_, const int p_inc,
             const Ordinal blocksize ) :
  comm(comm_), nbc(0), BlockSize(blocksize), root(root_), name(name_),
  bndry_stats(NULL), verb(comm->verbosity()), write_partition(true),
  use_zoltan(use_zoltan_partitioning()), have_my_bbox(false)
{
  comm->cout()<<"Constructing Field for "<<name
              <<" using binary, parallel approach"<<endl;
  string buffer;
  if (root=="-help") comm->exit(DGM::SUCCESS);
#ifdef DGM_FIELD_READ_ASCII_MESH
  // open ASCII mesh file and read parameters (now deprecated)
  string fname = root+".msh";
  if (comm->Master()) {
    ifstream in(fname.c_str());
    if (!in) {
      stringstream msg;
      msg << "Field::Field() Could not open mesh file: " << fname;
      comm->error(msg.str());
    }
    if (verb>1) comm->cout() << "  Reading mesh data from " << fname << endl;
    getline(in,buffer);
    if (!(in>>ne))
      comm->error("Field::Field() Cannot read number of elements");
    if (!(in>>_nsd))
      comm->error("Field::Field() Cannot read number of dimensions");
    getline(in,buffer);
    in.close();
  }
#else
  // open Binary mesh file and read parameters
  string fname = root+".grd";
  if (comm->Master()) {
    Mesh mesh;
    Json::Value header;
    streamoff offset = mesh.read_header(fname,header);
    gne = 0; _nsd = 0;  // try to get information from Json header if there
    if (header.isMember("Nel")) gne = (GlobalSize)header["Nel"].asInt64();
    if (header.isMember("Nsd")) _nsd = (LocalSize)header["Nsd"].asInt();
    //comm->cout() << header;
    //comm->cout() << "gne = " << gne << ", nsd = "<< _nsd << endl;
    if (gne==0 || _nsd==0) {
      ifstream in(fname.c_str());
      if (!in)
        throw DGM::exception("Field::Field() Could not open mesh file: "+fname);
      in.seekg(offset);
      if (!in.good())
        throw DGM::exception("Could not seek to offset "+asString(offset)+
                             " on file "+fname);
      if (verb>1) comm->cout() << "  Reading mesh data from " << fname << endl;
      // This block should only be executed when there is not a complete Json
      // header.  By convention, this can only occur when the datatypes are
      //   GlobalSize=int32, LocalSize=int32, Scalar=float64
      // so read binary data in those types.
      int32_t lgne;
      in.read(reinterpret_cast<char*>(&lgne),sizeof(lgne));
      gne = (GlobalSize)lgne;
      if (in.bad())
        throw DGM::exception("Could not read number of elements from "+fname);
      int32_t lnsd;
      in.read(reinterpret_cast<char*>(&lnsd),sizeof(lnsd));
      _nsd = (LocalSize)lnsd;
      if (in.bad())
        throw DGM::exception("Could now read number of space dimensions from "+
                             fname);
      if (gne==numeric_limits<GlobalSize>::max())
        throw DGM::exception("Illegal number of elements: "+asString(gne));
      if (_nsd<1 || _nsd>3)
        throw DGM::exception("Invalid number of space dimensions: "+
                             asString(_nsd));
      in.close();
    }
  }
#endif
  comm->Broadcast( &gne );
  comm->Broadcast( &_nsd );
  if (verb>1) comm->cout() << "  Building " << name << " Field:  ne = "
                         << gne << ", nsd = " << _nsd << endl;
  if (verb>1) comm->cout() << "  Global number of elements = " << gne << endl;
  if ((GlobalSize)comm->NumProc() > gne)
    comm->error("Field::Field() Number of processors exceeds numbers of "
                "elements");
  partition.reset( new Partition<GlobalSize,LocalSize,Scalar>(gne,root,comm) );
  ne = partition->ne();
  if (verb>1) comm->cout() << "  Read the parallel partition" << endl;
  if (verb>1) comm->cout() << "  Building Mesh object" << endl;
  if (use_zoltan) {
    Mesh mesh2;
    mesh2.setup_parallel(comm,partition);
    OrderMap pm1, qm1;
    read_elements(mesh2,p,q,fname,p_inc,pm1,qm1);
    read_curve_pc(root);           // read in curve types
    iVector weight(numeric_cast<Ordinal>(el.size()), 1);
    // get database from Json first, or the environment if not found
    if (!weight_database.empty()) {
      try {
        if (comm->Master())
          cout << "  Using weights database: " << weight_database << endl;
        WeightsDatabase db(weight_database.c_str(), numeqns, physics);
        Topology::ElementType et;
        bool c;
        Ordinal porder;
        for (size_t e=0; e<el.size(); ++e) {
          el[e]->get_weight_props(et, c, porder);
          weight[numeric_cast<Ordinal>(e)] = db.get_weight(et, c, porder);
        }
      }
      catch (WeightsDatabase::file_not_found &e) {
        if (comm->Master())
          comm->cout() << "  Unable to open weights database file "
                       << weight_database.c_str() << "\n"
                       << "  Using default (internal) weights" << endl;
        // use fallback weights
        for (size_t e=0; e<el.size(); ++e)
          weight[e] = el[e]->get_weight();
      }
    } else {
      if (comm->Master()) cout << "  Using default (internal) weights" << endl;
      for (size_t e=0; e<el.size(); ++e)
        weight[numeric_cast<Ordinal>(e)] = el[e]->get_weight();
    }
    zoltan2(mesh2, weight.begin(), weight.end());
    ne = partition->ne();
    // Clear comm world reference count by releasing curves.
    // Some curves may move to other processors leaving this
    // processor's reference count invalid.
    // Free all curve objects here, they'll be constructed below.
    for (size_t e=0; e<el.size(); ++e)
      el[e]->curve.reset();
  }
  Mesh mesh;
  mesh.setup_parallel(comm,partition);
  OrderMap pm, qm;
  read_elements(mesh,p,q,fname,p_inc,pm,qm);

  // setup side element links and ids
  for (size_t i=0; i<el.size(); ++i) {
    for (Ordinal j=0; j<el[i]->nSides(); ++j) {
      el[i]->side[j]->elink = el[i];
      el[i]->side[j]->geid(partition->eid((LocalSize)i));
      for (size_t k=0; k<el[i]->side[j]->subsides().size(); ++k) {
        el[i]->side[j]->subsides()[k]->elink = el[i];
      }
    }
  }

  read_curve_pc(root);           // read in curve types
  if (verb>1) comm->cout() << "  set_side_links_pc" << endl;
  set_side_links_pc(mesh,pm,qm); // make connectivity links
  if (verb>1) comm->cout() << "  set_global_side_id_pc" << endl;
  set_global_side_id_pc();       // make global node, element, and side id's
  if (verb>1) comm->cout() << "  adjust_side_order_pc" << endl;
  adjust_side_order_pc();        // adjust side qpts to match
  if (verb>1) comm->cout() << "  make_partition" << endl;
  make_partition();              // partition the mesh if parallel
  // SSC: This seems redundant with make_partition
  if (verb>1) comm->cout() << "  set_flip" << endl;
  set_flip(true);                // set side flips
  if (verb>1) comm->cout() << "  initialize_bc" << endl;
  initialize_bc(root);           // setup boundary sides
  if (verb>1) comm->cout() << "  make_storage" << endl;
  make_storage();                // allocate storage
  CMC::Stopwatch timer; timer.start();
  if (verb>1) { comm->cout() << "  compute_geometry..."; comm->cout().flush(); }
  compute_geometry();            // make elmt mappings, Jacobian, mass matrix
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
  timer.reset(); timer.start();
  if (verb>1) {
    comm->cout() << "  compute_side_geometry..."; comm->cout().flush();
  }
  compute_side_geometry();       // make side mapping, Jacobian, normal vectors
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
#ifdef DGM_ALLOW_HANGING_NODES
  timer.reset(); timer.start();
  if (verb>1) {
    comm->cout() << "  compute_subside_geometry..."; comm->cout().flush();
  }
  compute_subside_geometry();    // make side mapping, Jacobian, normal vectors
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
#endif
#ifdef DGM_USE_ELEMENT_BLOCKS
  initialize_element_blocks();
#endif
  if (verb>1) comm->cout() << "  write_weights" << endl;
  write_weights( root+".wgt" );
  if (verb>1) comm->cout() << "  write_graph" << endl;
  write_graph( root+".grf" );
  if (verb>1) comm->cout() << "  BndryStats" << endl;
  bndry_stats = new BndryStats( root, this );  // setup bndry statistics
#ifdef DGM_FIELD_VERBOSE
  print_side_links();            // check connectivity
  if (comm->Master()) write_mesh("mesh.dat");
  if (comm->Master()) write_connectivity("connect.dat");
#endif
  domain_partition = partition;  // set the Domain partition to be the field's
#ifdef DGM_OUTPUT_DOF            // output the degrees of freedom
  cout<<comm->MyPID()<<":  ne = "<<ne<<", ndof = "<<ndof()<<endl;
#endif
#if defined(DGM_WRITE_BINARY_FILES) && defined(DGM_PARALLEL)
  {
    Mesh mesh;
    mesh.nsd = _nsd;
    for (Size i=0; i<partition->ne(); ++i) {
      cout << comm->MyPID() <<" id=["<<i<<"]:"<<el[i]->id<<endl;
    }
    ifstream con((root+".con").c_str());
    mesh.CopyIn(con, el, partition);
    mesh.MPI_write(comm, partition, root+".grd");
    mesh.MPI_write_connectivity(comm, partition, root+".cn");
    mesh.MPI_read(comm, partition, root+".grd");
    if (comm->MyPID())
      mesh.write("Check_Mesh_1.msh");
    else
      mesh.write("Check_Mesh_0.msh");
    cerr<<" Finished writing Binary files.  I'm going now....."<<endl;
    throw DGM::exception("Debugging termination");
  }
#endif
  if (verb>1) comm->cout() << "Finished Field::Field constructor" << endl;
}

/// Use the binary mesh and connectivity readers to build elements
/** \note The p and q order maps are adjusted according to the element
    types so they leave this method modified. */
void Field::read_elements(Mesh &mesh, const Ordinal p,
                          const Ordinal q, string fname,
                          const int p_inc, OrderMap &pm, OrderMap &qm) {
  string buffer;
  Json::Value header;
  if (verb>1) comm->cout() << "  Reading binary mesh " << root+".grd" << endl;
  mesh.read(root+".grd",mesh.read_header(root+".grd",header),header);
  if (verb>1)
    comm->cout() << "  Reading binary connectivity " << root+".cn" << endl;
  mesh.read_connectivity(root+".cn",mesh.read_header(root+".cn",header),
                         header);
  if (verb>1) comm->cout() << "  Finished reading mesh" << endl;

  // make a list of linked elements
  SizeMap elist;
  for (size_t n=0; n<mesh.con.size(); ++n) {
    const GlobalSize geid  = mesh.con[n].eid;
    const GlobalSize gleid = mesh.con[n].leid;
    if (partition->owns(geid) && !partition->owns(gleid)) {
      const SizeMap::value_type v(gleid,geid);
      // use insert because SizeMap is a multi-map since a single
      // gleid could be a neighbor to multiple owned elements.
      elist.insert(v);
    }
  }
  // Initialize p & q for partition elements (p & q must be pre-incremented)
  for (LocalSize e=0; e<partition->ne(); ++e) {
    GlobalSize k = partition->eid(e);
    pm[k] = p; qm[k] = q;
  }
  // Initialized p & q for linked elements (p & q must be pre-incremented)
  for (SizeMap::iterator it=elist.begin(); it!=elist.end(); ++it) {
    GlobalSize k = it->first;
    pm[k] = p; qm[k] = q;
  }
  fname = root+".ord";
  ifstream order(fname.c_str());
  if (order) {
    GlobalSize k;              // global element id (could be huge)
    LocalSize pl, ql;
    comm->cout() << "  Reading order file " << fname << endl;
    getline(order,buffer);
    while (order >> k >> pl >> ql) {
      getline(order,buffer);
      if (k<numeric_limits<GlobalSize>::min() || k>gne)
        comm->error("Field::Field() Illegal element number in order file");
      // if element is on or linked to this partition
      if ( elist.find(k) != elist.end() || partition->owns(k)) {
        if (verb>4)
          cout << "  " << comm->MyPID() << ": adding p & q for linked element"
            " geid = " << k << " to order map" << endl;
        pm[k] = pl + p_inc;
        qm[k] = ql;
        // The default number of quadrature points in the interior is q = p +
        // 1.5 \approx p + 2 which makes sure that the interior integrals are
        // computed to order 2p when using Gauss-Lobatto-Legendre quadrature
        // which can integrate 2q-3 polynomial exactly.  The condition
        // required for convergence of smooth solutions is that you must
        // integrate 2p polynomials exactly to ensure p+1 convergence as
        // discussed by Cockburn & Shu (JCP 141, p. 203, 1998)
        if (qm[k]==0)
          qm[k] = pm[k] + 2;  // default is q = p + 2
        else
          qm[k] += p_inc;     // need to increment quadrature order as well
      }
    }
  }
  order.close();

#ifdef DGM_USE_MD_COUPLE
  // read the model file (if present) [currently not scalable]
  vector<Model::Type> pmodel(gne);
  fname = root+".mod";
  ifstream model(fname.c_str());
  if (model) {
    GlobalSize k;
    int pm;
    comm->cout() << "  Model file is present" << endl;
    getline(model,buffer);
    while (model >> k >> pm) {
      getline(model,buffer);
      if (k<0 || k>gne)
        comm->error("Field::Field() Illegal element number in model file");
      switch(pm){
      case 0:
        pmodel[k] = Model::ADV_DIFF;
        break;
      case 1:
        pmodel[k] = Model::EULER;
        break;
      case 2:
        pmodel[k] = Model::NAVIER_STOKES;
        break;
      case 3:
        pmodel[k] = Model::WAVE;
        break;
      case 4:
        pmodel[k] = Model::LINEULER;
        break;
      default:
        comm->error("Field::Field() Illegal Model::Type in model file");
      }
    }
  } else
    for(GlobalSize k=0; k<gne; ++k) pmodel[k] = Model::EULER;
#endif

  comm->Barrier();
  if (verb>1) comm->cout() << "  Starting to build elements..." << endl;
  CMC::Stopwatch cpu;
  if (comm->Master()) cpu.start();

  // initialize the maximum Quadrature and Mode orders for this field
  Qmax = 0;
  Lmax = 0;

  // make the elements
  el.resize(partition->ne());
  if (_nsd==1) {
    vector<Point> X(2);
    for (Ordinal e=0, v=0; e<partition->ne(); e++) {
      const Size eid = partition->eid(e);
      Ordinal &pl = pm[eid];
      Ordinal &ql = qm[eid];
      X[0] = mesh.point[v++];
      X[1] = mesh.point[v++];
      if (Topology::Line == mesh.etype[e]) {
        el[e] = new Line(e,pl,ql,X);
      } else if (Topology::NodalLine == mesh.etype[e]) {
        el[e] = new NodalLine(e,pl,X);
        ql = pl+1;
      } else if (Topology::SpectralLine == mesh.etype[e]) {
        el[e] = new SpectralLine(e,pl,X);
        ql = pl+1;
      } else {
        comm->error("Field::Field() illegal 1d element type "+
                     asString(mesh.etype[e])+" for element id = "+
                     asString(eid));
      }
      Qmax = std::max( Qmax, ql );
      Lmax = std::max( Lmax, pl+1);
      el[e]->gid(eid);
    }
  } else if (_nsd==2) {
    vector<Point> X(4);
    for (Ordinal e=0,v=0; e<partition->ne(); e++) {
      const Size eid = partition->eid(e);
      Ordinal &pl = pm[eid];
      Ordinal &ql = qm[eid];
      const int nverts = Mesh::nodes[mesh.etype[e]];
      for (int i=0; i<nverts; i++) X[i] = mesh.point[v++];
#ifdef DGM_USE_MD_COUPLE
      if (nverts == 4) {
        if ( Topology::Quad == mesh.etype[e] ) {
          el[e] = new Quad(e,pl,ql,X,pmodel[e]);
        } else if ( Topology::NodalQuad == mesh.etype[e] ) {
          el[e] = new NodalQuad(e,pl,ql,X,pmodel[e]);
          ql = pl+1;
        } else if ( Topology::SpectralQuad == mesh.etype[e] ) {
          el[e] = new SpectralQuad(e,pl,ql,X,pmodel[e]);
          ql = pl+1;
        } else {
          comm->error("Field::Field() illegal 2d element type "+
                      asString(mesh.etype[e])+" for element id = "+
                      asString(eid));
        }
        Qmax = std::max( Qmax, ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+1) );
      } else {
        if (Topology::NodalTri != mesh.etype[e]) {
          el[e] = new Tri(e,pl,ql,X,pmodel[e]);
        } else {
          el[e] = new NodalTri(e,pl,ql,X,pmodel[e]);
          ql = pl+1;
        }
        Qmax = std::max( Qmax, ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+1+1)/2 );
      }
#else
      if (nverts == 4) {
        if ( Topology::Quad == mesh.etype[e] ) {
#ifdef DGM_USE_COMPILETIMEQUAD
          el[e] = new_quad(e,pl,ql,X);
#else
          el[e] = new Quad(e,pl,ql,X);
#endif

        } else if ( Topology::NodalQuad == mesh.etype[e] ) {
          el[e] = new NodalQuad(e,pl,X);
          ql = pl+1;
        } else if ( Topology::SpectralQuad == mesh.etype[e] ) {
          el[e] = new SpectralQuad(e,pl,X);
          ql = pl+1;
        } else {
          comm->error("Field::Field() illegal 2d element type "+
                      asString(mesh.etype[e])+" for element id = "+
                      asString(eid));
        }
        Qmax = std::max( Qmax, ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+1) );
      } else {
        if ( Topology::NodalTri != mesh.etype[e] ) {
          el[e] = new Tri(e,pl,ql,X);
        } else {
          el[e] = new NodalTri(e,pl,X);
          ql = pl+1;
        }
        Qmax = std::max( Qmax, ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+1+1)/2 );
      }
#endif
      el[e]->gid(eid);
    }
  } else if (_nsd==3) {
    vector<Point> X(8);
    for (Ordinal e=0, v=0; e<partition->ne(); ++e) {
      const Ordinal nverts = Mesh::nodes[mesh.etype[e]];
      const Size eid = partition->eid(e);
      Ordinal &pl = pm[eid];
      Ordinal &ql = qm[eid];
      for (Ordinal i=0; i<nverts; i++) X[i] = mesh.point[v++];
      if (nverts == 8) {
        if ( Topology::Hex == mesh.etype[e] ) {
          el[e] = new Hex(e,pl,ql,X);
        } else if ( Topology::NodalHex == mesh.etype[e] ) {
          el[e] = new NodalHex(e,pl,X);
          ql = pl+1;
        } else if ( Topology::SpectralHex == mesh.etype[e] ) {
          el[e] = new SpectralHex(e,pl,X);
          ql = pl+1;
        } else {
          comm->error("Field::Field() illegal 3d element type "+
                      asString(mesh.etype[e])+" for element id = "+
                      asString(eid));
        }
        Qmax = std::max( Qmax, ql * ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+1)*(pl+1) );
      } else {
        if ( Topology::NodalTet == mesh.etype[e] ) {
          el[e] = new NodalTet(e,pl,X);
          ql = pl+1;
        } else {
          comm->error("Field::Field() Modal Tet elements not supported.");
        }
        Qmax = std::max( Qmax, ql * ql * ql );
        Lmax = std::max( Lmax, (pl+1)*(pl+2)*(pl+3)/6 );
      }
      el[e]->gid(eid);
    }
  } else {
    stringstream msg;
    msg<<"Illegal value: nsd = " << _nsd << " in Field::Field()";
    comm->error(msg.str());
  }
  comm->Barrier();
  comm->cout()<<"  Constructed "<<gne<<" elements in "<<cpu.stop()
              <<" seconds."<<endl;
}

/// Read curved side data
/** \note Currently we do not support curved sides with a constant bases. */
void Field::read_curve_pc(const string &root) {
  static Color bold(Color::BOLD);
  static Color red(Color::RED);
  static Color def(Color::DEFAULT);
  static Color green(Color::GREEN);
  Curve::db_type ctype;             // database of active curve types
  ctype["Nonaffine2D"].reset(new Straight(comm));
  ctype["Nonaffine3D"].reset(new Straight3D(comm));
  string buffer, tag;
  string fname = root+".crv";
  ifstream in(fname.c_str());
  if (in) {
#ifndef DGM_FIELD_USE_OLD_CURVE_READ
    Curve::read(comm, partition, fname, in, ctype, el);
#else
    // read curved types
    Curve::read(comm, fname, in, ctype);
    // read curved sides
    GlobalSize eid;
    LocalSize nsides, side;
    if (!(in>>nsides)) comm->error("Field: Cannot read number of curved sides");
    getline(in,buffer);
    if (nsides) {
      if (ctype.size()==0) comm->error("Field: No curve types specified.");
      for (LocalSize i=0; i<nsides; i++) {
        if (!(in >> eid >> side >> tag))
          comm->error("Field: Unable to read curved side information.");
        if (eid > gne) comm->error("Field: Too many elements in crv file");
        if (!partition->owns(eid)) continue;
        const Ordinal k = partition->inc(eid);
        if (el[k]->L() > 1) {
          if (ctype.find(tag) == ctype.end() )
            comm->error("Curve: unsupported curve type = "+tag);
          el[k]->curve.reset( ctype[tag]->clone() );
          el[k]->curve->side = side;
        } else {
          comm->cout() << "WARNING:  curved element " << eid
                       << " has constant basis" << endl;
        }
      }
    }
#endif
  }
  // Now figure out if any additional elements are non-affine
  Size numElements=0;
  for (size_t e=0; e<el.size(); e++) {
    const bool affine = el[e]->is_affine();
    if (!affine && !el[e]->curve.get()) {
      numElements++;
      if (el[e]->nsd()==3)
        el[e]->curve.reset( ctype["Nonaffine3D"]->clone() );
      else if (el[e]->nsd()==2)
        el[e]->curve.reset( ctype["Nonaffine2D"]->clone() );
      else
        throw DGM::exception("One dimensional element cannot be curved");
      el[e]->curve->side = 0;
    }
  }
  Size totalNumElements=0;
  comm->SumAll(&numElements,&totalNumElements,1);
  if (totalNumElements!=0)
    comm->cout()<<bold<<"NOTE:  determined that an additional "
                <<totalNumElements
                <<" elements are non-affine!"<<def<<endl;
}

namespace {

  map<pair<Ordinal,Ordinal>, bool> communicate_integration_type
  (const vector<Element*> &el,
   const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition,
   const DGM::Comm::Ptr comm) {

    map<pair<Ordinal,Ordinal>, bool> GLLs;
#ifdef DGM_PARALLEL
    vector< Pcon<GlobalSize,LocalSize,Scalar> > pc(partition->ncprocs());

    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      pc[n].len = partition->cinfo[n].nsides;
      pc[n].buf.resize(pc[n].len);
    }

    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      Size sdof = 0;
      const Connect<GlobalSize,LocalSize> &cinfo = partition->cinfo[n];
      for (LocalSize i=0; i<cinfo.nsides; i++) {
        const Link<GlobalSize,LocalSize> &link  = cinfo.links[i];
        const int elmtid  = link.elmtid;
        const int sideid  = link.sideid;
        const Side *s  = el[elmtid]->side[sideid];
        pc[n].buf[sdof++] = s->Gauss_Lobatto();
      }
    }

    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      comm->SendReceiveReplace( pc[n].buf.data(),
                                pc[n].len,
                                partition->cinfo[n].cprocid,
                                partition->cinfo[n].cprocid,
                                partition->cinfo[n].cprocid,
                                comm->MyPID() );
    }

    for (LocalSize n=0; n<partition->ncprocs(); n++) {
      Size sdof = 0;
      const Connect<GlobalSize,LocalSize> &cinfo = partition->cinfo[n];
      for (LocalSize i=0; i<cinfo.nsides; i++) {
        const Link<GlobalSize,LocalSize> &link  = cinfo.links[i];
        const pair<Ordinal,Ordinal> k(link.elmtid, link.sideid);
        GLLs[k] = pc[n].buf[sdof++];
      }
    }
#endif  // DGM_PARALLEL
    return GLLs;
  }

}

/// Set links based on internal mesh object
/** This version uses a map for the p-order and q-order information. */
void Field::set_side_links_pc(const Mesh &mesh, const OrderMap &pv,
                              const OrderMap &qv) {
  if (verb>2) comm->cout() << "  Starting Field::set_side_links_pc(Mesh &, "
      "OrderMap &, OrderMap &)"<<endl;
  if (verb>2) comm->cout() << "    Global ne = " << gne;
  if (verb>2) comm->cout() << ", Partition ne = " << partition->ne() << endl;

#ifdef DGM_ALLOW_HANGING_NODES
  std::set<pair<int,int> > hangnodes;
#endif
  {
    std::set<pair<Size,Ordinal> > links;
    for (size_t n=0; n<mesh.con.size(); n++) {
      // connectivity contains global element ids
      const GlobalSize  geid = mesh.con[n].eid;
      const LocalSize   side = mesh.con[n].side;
      const GlobalSize gleid = mesh.con[n].leid;
      if ( Mesh::defined(gleid) ) {
        const pair<Size,Ordinal> from(geid, side);
        if (links.count(from)) {
#ifdef DGM_ALLOW_HANGING_NODES
          hangnodes.insert(from);
#else
          comm->error("Field::set_side_links_pc() "
                      "Not compiled with "
                      "DGM_ALLOW_HANGING_NODES. "
                      "Hanging node meshes not supported");
#endif
        } else {
          links.insert(from);
        }
      }
    }
  }

  for (size_t n=0; n<mesh.con.size(); ++n) {
    // connectivity contains global element ids
    const GlobalSize geid  = mesh.con[n].eid;
    const LocalSize  side  = mesh.con[n].side;
    const GlobalSize gleid = mesh.con[n].leid;
    const LocalSize  lside = mesh.con[n].lside;
    const GlobalSize gid   = mesh.con[n].gid;
#ifdef DGM_FIELD_DEBUG
    cout << comm->MyPID() << ": n = " << n << ", "
         << geid << " " << side << " "
         << gleid << " " << lside << " "
         << gid << endl;

    cout << comm->MyPID() << ": n = " << n << ", "
         << Mesh::undefined(geid) << " " << side << " "
         << Mesh::undefined(gleid) << " " << lside << " "
         << Mesh::undefined(gid) << endl;
#endif
    if (Mesh::undefined(gleid)) continue;

    if (!partition->owns(geid)) continue;  // element is not on this partition

    // get local element ids
    const LocalSize eid = partition->inc(geid);
    Element *elem = el[eid];
    elem->side[side]->gid(gid);

    if (!partition->owns(gleid)) {    // linked element is not on this partition

      const bool GLL = false; // Don't know what to set it to since the owning
                              // element is not on this processor.  Set it to
                              // false and fix later.

      Side *l=0;
      if (verb>5)
        comm->cout() << "  gid = " << geid << ", eid = " << eid << ", etype = "
                     << mesh.etype[eid] << endl;
      if (pv.find(gleid) == pv.end())
        cout << comm->MyPID() << ": WARNING p-order for gleid = " << gleid
             << " not found" << endl;
      if (qv.find(gleid) == qv.end())
        cout << comm->MyPID() << ": WARNING q-order for gleid = " << gleid
             << " not found" << endl;
      const Ordinal L  = pv.find(gleid)->second+1;
      const Ordinal qa = qv.find(gleid)->second;
      const Ordinal nverts = Mesh::nodes[mesh.etype[eid]];
      if (_nsd==1) {
        Edge *ed = new Edge(lside,elem,L,1,false);
        l = ed;
      } else if (_nsd==2) {
        const Ordinal nModes = (nverts==4) ? L*L : L*(L+1)/2;
#ifdef DGM_USE_MD_COUPLE
        Edge *ed = new Edge(lside,elem,nModes,qa-1,pmodel[gleid]);
#else
        if (verb>5)
          comm->cout() << "  lside = " << lside << " elem = " << elem
                       << " nModes = " << nModes
                       << " qa-1 = " << qa-1 << endl;
        Edge *ed = new Edge(lside,elem,nModes,qa-1,GLL);
#endif
        l = ed;
      } else if (_nsd==3) {
        if (nverts == 8) {
          const Ordinal nModes = L*L*L;
          Face *fac = new Face(lside,elem,nModes,qa-1,qa-1,GLL);
          l = fac;
        } else { // Must be a NodalTet......
          const Ordinal qedg   = L*(L+1)      /2;
          const Ordinal nModes = L*(L+1)*(L+2)/6;
          Face *fac = new Face(lside,elem,nModes,qedg,1,GLL);
          l = fac;
        }
      } else {
        stringstream msg;
        msg<<"Illegal value: nsd = " << _nsd
           << " in Field::set_side_links_pc()";
        comm->error(msg.str());
      }
      Side *this_side = elem->side[side];
      this_side->geid ( elem->gid() );
#ifdef DGM_ALLOW_HANGING_NODES
      if (hangnodes.count( make_pair(geid,side) ) ) {
        this_side->link = 0;
        this_side->base = 0;
        l->id( lside );
        l->gid( gid );
        l->geid( gleid);
        l->link  = 0; // comm-buf has not link
        l->elink = 0;
        l->base  = 0; // comm-buf has not base
        Side::Ptr sub_side (this_side->deep_copy());
        sub_side->subsides().clear();
        sub_side->base  = l;
        sub_side->link  = l;
        sub_side->id( this_side->id());
        if (1 == sub_side->q1() || 1 != sub_side->q2()) {
          sub_side->q1(this_side->q1());
          sub_side->q2(this_side->q2());
        } else {
          sub_side->q1(this_side->q1()*(2*this_side->q1()+1));
        }
        sub_side->gid( gid );
        sub_side->geid( this_side->geid());
        this_side->subsides().push_back(sub_side);
      } else
#endif
      {
        l->id(lside);
        l->geid(gleid);
        l->elink = 0;
        l->gid(gid);
        l->link = 0;
        this_side->link = l;
        this_side->base = this_side;
        l->base =  gleid < geid ? this_side : l;
      }
    } else {
      const LocalSize leid = partition->inc(gleid);
      // check to see if the opposite link is already set
#ifdef DGM_ALLOW_HANGING_NODES
      if (hangnodes.count( make_pair(geid,side) ) ) {
        Side *this_side = el [eid]->side [side];
        Side *nbr_side  = el[leid]->side[lside];
        Side::Ptr sub_side(nbr_side->deep_copy());
        //sub_side->subsides().clear();
        sub_side->id( this_side->id() );
        if (1 == sub_side->q1() || 1 != sub_side->q2()) {
          sub_side->q1( this_side->q1() );
          sub_side->q2( this_side->q2() );
        } else {
          sub_side->q1(this_side->q1()*(2*this_side->q1()+1));
          sub_side->Gauss_Lobatto(this_side->Gauss_Lobatto());
        }
        sub_side->gid( this_side->gid() );
        sub_side->elink = this_side->elink;
        this_side->geid( el [eid]->gid());
        nbr_side->geid( el[leid]->gid());
        sub_side->geid( this_side->geid());

        sub_side->link  =        0; // sub is slave
        sub_side->base  = nbr_side; // link to neighbor
        nbr_side->link  = sub_side.get(); // neighbor is master
        nbr_side->base  = nbr_side; // link to self
        this_side->link =        0; // not master
        this_side->base =        0; // like a boundary

        this_side->subsides().push_back(sub_side);

      } else if (hangnodes.count( make_pair(gleid,lside) ) ) {
        // do nothing, wait for the reverse link to set the links.
      } else
#endif
      {
        if ( const Side *slink = el[leid]->side[lside]->link ) {
          // if so, make sure that the links match, otherwise error
          if ( slink != elem->side[side] ) {
            stringstream msg;
            msg << "Contradictory side links: Eid " <<eid<<", side "<<side
                << ", lEid "<<leid<<", lside "<<lside<<endl;
            comm->error(msg.str());
          }
          // just set the base if the other link is valid
          elem->side[side]->base      = el[leid]->side[lside];
          el[leid]->side[lside]->base = el[leid]->side[lside];
        } else {
          elem->side[side]->link = el[leid]->side[lside];
        }
      }
    }
  }
  if (verb>2) comm->cout() << "  Finished Field::set_side_links_pc()" << endl;
}

/// Set links based on internal mesh object
/** This version uses a vector (of size global number of elements) for the
    p-order and q-order information. */
void Field::set_side_links_pc(const Mesh &mesh, const vector<int> &pv,
                              const vector<int> &qv) {
  if (verb>2) comm->cout() << "  Starting Field::set_side_links_pc(...)"<<endl;
  if (verb>2) comm->cout() << "    mesh.etype.size() = " << mesh.etype.size();
  if (verb>2) comm->cout() << ", Global ne = " << ne;
  if (verb>2) comm->cout() << ", Partition ne = " << partition->ne() << endl;

#ifdef DGM_ALLOW_HANGING_NODES
  std::set<pair<GlobalSize,LocalSize> > hangnodes;
#endif
  {
    std::set<pair<GlobalSize,LocalSize> > links;
    for (size_t n=0; n<mesh.con.size(); n++) {
      // connectivity contains global element ids
      const GlobalSize  geid = mesh.con[n].eid;
      const LocalSize   side = mesh.con[n].side;
      const GlobalSize gleid = mesh.con[n].leid;
      if ( Mesh::defined(gleid) ) {
        const pair<GlobalSize,LocalSize> from(geid, side);
        if (links.count(from)) {
#ifdef DGM_ALLOW_HANGING_NODES
          hangnodes.insert(from);
#else
          comm->error("Field::set_side_links_pc() "
                      "Not compiled with "
                      "DGM_ALLOW_HANGING_NODES. "
                      "Hanging node meshes not supported");
#endif
        } else {
          links.insert(from);
        }
      }
    }
  }

  const map<pair<Ordinal,Ordinal>, bool> GLLs =
    communicate_integration_type (el, partition, comm);

  for (size_t n=0; n<mesh.con.size(); ++n) {

    // connectivity contains global element ids
    const GlobalSize geid = mesh.con[n].eid;
    const LocalSize side  = mesh.con[n].side;
    const GlobalSize gleid = mesh.con[n].leid;
    const LocalSize lside = mesh.con[n].lside;
    const GlobalSize gid = mesh.con[n].gid;

    // WARNING:  this needs to be fixed!!!!
    if ( !Mesh::defined(gleid) ) continue;

    if (!partition->owns(geid)) continue;

    // get local element ids
    const LocalSize eid  = partition->inc(geid);
    Element* elem = el[eid];
    elem->side[side]->gid(gid);
    if (!partition->owns(gleid)) {
      const pair<Ordinal,Ordinal> key(eid,side);
      const map<pair<Ordinal,Ordinal>, bool>::const_iterator
        value = GLLs.find(key);
      if (value == GLLs.end()) {
        static bool first_time = true;
        if (first_time) {
          stringstream msg;
          msg<<"Attempting to set up side communication classes:" <<endl
             << " and could not determine type of Side"
             << " integration rule (GLL or GL)"
             << " across processor boundary."<<endl
             <<__FILE__":"<<__LINE__<<endl;
          cout << msg.str();
        }
        first_time = false;
      }
      const bool GLL = value != GLLs.end() ? value->second : false;

      Side *l=0;
      const Ordinal L  = pv[gleid] + 1;
      const Ordinal qa = qv[gleid];
      const Ordinal nverts = Mesh::nodes[mesh.etype[eid]];
      if (_nsd==1) {
        Edge *ed = new Edge(lside,elem,L,1,false);
        l = ed;
      } else if (_nsd==2) {
        const Ordinal nModes = (nverts==4) ? L*L : L*(L+1)/2;
        comm->cout() << "  nModes = " << nModes << endl;
#ifdef DGM_USE_MD_COUPLE
        Edge *ed = new Edge(lside,elem,nModes,qa-1,pmodel[gleid]);
#else
        comm->cout() << "  lside = " << lside << " elem = " << elem
                     << " nModes = " << nModes
                     << " qa-1 = " << qa-1 << endl;
        Edge *ed = new Edge(lside,elem,nModes,qa-1,GLL);
#endif
        l = ed;
      } else if (_nsd==3) {
        if (nverts == 8) {
          const Ordinal nModes = L*L*L;
          Face *fac = new Face(lside,elem,nModes,qa-1,qa-1,GLL);
          l = fac;
        } else { // Must be a NodalTet.....
          const Ordinal qedg   = L*(L+1)      /2;
          const Ordinal nModes = L*(L+1)*(L+2)/6;
          Face *fac = new Face(lside,elem,nModes,qedg,1,GLL);
          l = fac;
        }
      } else {
        stringstream msg;
        msg<<"Illegal value: nsd = " << _nsd
           << " in Field::set_side_links_pc()";
        comm->error(msg.str());
      }
      Side *this_side = elem->side[side];
      this_side->geid (elem->gid());
#ifdef DGM_ALLOW_HANGING_NODES
      if (hangnodes.count( make_pair(geid,side) ) ) {
        this_side->link = 0;
        this_side->base = 0;
        l->id     (lside);
        l->gid    (gid);
        l->geid   (gleid);
        l->link  = 0; // comm-buf has not link
        l->elink = 0;
        l->base  = 0; // comm-buf has not base
        Side::Ptr sub_side(this_side->deep_copy());
        sub_side->subsides().clear();
        sub_side->base  = l;
        sub_side->link  = l;
        sub_side->id    ( this_side->id());
        if (1 == sub_side->q1() || 1 != sub_side->q2()) {
          sub_side->q1    ( this_side->q1());
          sub_side->q2    ( this_side->q2());
        } else {
          sub_side->q1(this_side->q1()*(2*this_side->q1()+1));
        }
        sub_side->gid   ( gid);
        sub_side->geid  ( this_side->geid());
        this_side->subsides().push_back(sub_side);
      } else
#endif
      {
        l->id    (lside);
        l->gid   (gid);
        l->geid  (gleid);
        l->link = 0;
        l->elink = 0;
        l->base = (gleid < geid) ? elem->side[side] : l;
        this_side->link = l;
        this_side->base = elem->side[side];
      }
    } else {
      const Size leid = partition->inc(gleid);
      // check to see if the opposite link is already set
#ifdef DGM_ALLOW_HANGING_NODES
      if (hangnodes.count( make_pair(geid,side) ) ) {
        Side *this_side = el [eid]->side [side];
        Side *nbr_side  = el[leid]->side[lside];
        Side::Ptr sub_side(nbr_side->deep_copy());
        //sub_side->subsides().clear();
        sub_side->id    ( this_side->id());
        if (1 == sub_side->q1() || 1 != sub_side->q2()) {
          sub_side->q1    ( this_side->q1());
          sub_side->q2    ( this_side->q2());
        } else {
          sub_side->q1(this_side->q1()*(2*this_side->q1()+1));
          sub_side->Gauss_Lobatto(this_side->Gauss_Lobatto());
        }
        sub_side->gid   ( this_side->gid());
        sub_side->elink = this_side->elink;
        this_side->geid    ( el [eid]->gid());
        nbr_side->geid     ( el[leid]->gid());
        sub_side->geid     ( this_side->geid());

        sub_side->link      =        0; // sub is slave
        sub_side->base      = nbr_side; // link to neighbor
        nbr_side->link      = sub_side.get(); // neighbor is master
        nbr_side->base      = nbr_side; // link to self
        this_side->link     =        0; // not master
        this_side->base     =        0; // like a boundary

        this_side->subsides().push_back(sub_side);

      } else if (hangnodes.count( make_pair(gleid,lside) ) ) {
        // do nothing, wait for the reverse link to set the links.
      } else
#endif
      {
        if ( const Side *llink = el[leid]->side[lside]->link ) {
          // if so, make sure that the links match, otherwise error
#ifndef DGM_FIELD_NO_CHECK_SIDE_LINKS
          // Turn this off inorder to allow for internal periodicity
          // WARNING:  this has not be fully tested
          if ( llink != el[eid]->side[side] ) {
            stringstream msg;
            msg << "Contradictory side links: Eid " <<eid<<", side "<<side
                << ", lEid "<<leid<<", lside "<<lside
                <<"   "<<__FILE__<<":"<<__LINE__<<endl;
            comm->error(msg.str());
          }
#endif
        } else {
          Side *this_side   = el [eid]->side[side];
          Side *nbr_side    = el[leid]->side[lside];
          this_side->link   = nbr_side;
          this_side->base   = this_side;
          nbr_side->link    = 0;
          nbr_side->base    = this_side;
          this_side->geid  ( el [eid]->gid());
          nbr_side->geid   ( el [leid]->gid());
        }
      }
    }
  }
  if (verb>2) comm->cout() << "  Finished Field::set_side_links_pc()" << endl;
}

/// Set global ids for all the sides
/** \warning This gives unique gids but that will not be the same for
    different partitions and may not match gids in serial. */
void Field::set_global_side_id_pc() {
  // comm->cout()<<"set_global_side_id_pc"<<endl;
  uint64_t el_size = el.size();
  uint64_t gid;
  comm->Scan(&el_size, &gid);
  gid -= el_size;
  for (size_t e=0; e<el.size(); e++) {
    for (Ordinal i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];
      if ( Side::undefined(side->gid()) ) {
        if ( side->base ) {
          side->gid(numeric_cast<GlobalSize>(gid));
          if ( side->link ) side->link->gid(numeric_cast<GlobalSize>(gid));
          ++gid;
        }
      }
    }
  }
}

/// Field add helper
void add( const Field *X, const std::vector<Size>&X_to_Y, Field *Y) {
  using std::endl;
  for (Field::LocalSize e=0; e<X->ne; e++) {
    Size i = e;
    if (!X_to_Y.empty()) {
      const Field::GlobalSize xgid = X->partition->eid(e);
      const Field::GlobalSize ygid = X_to_Y[xgid];
      i = Y->partition->inc(ygid);
    }
    if (Y->ne < i) {
      DGM::Comm::World->cerr()<<"Mapping from sub-field to field bad."
        <<" man entry:"<<i <<" greater than max element:"<<Y->ne<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    if (0 <= i) {
      const Element *x = X->el[e];
      Element *y = Y->el[i];
      dvadd( x->u, y->u );
    }
  }
}

/// Field extract helper
void extract( Field *X, const std::vector<Size>&X_to_Y, const Field *Y) {
  using std::endl;
  for (Field::LocalSize e=0; e<X->ne; e++) {
    const Field::GlobalSize xgid = X->partition->eid(e);
    const Field::GlobalSize ygid = X_to_Y[xgid];
    const Field::LocalSize     i = Y->partition->inc(ygid);
    if (Y->ne < i) {
      DGM::Comm::World->cerr()<<"Mapping from sub-field to field bad."
        <<" man entry:"<<i <<" greater than max element:"<<Y->ne<<endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    if (0 <= i) {
      Element *x = X->el[e];
      const Element *y = Y->el[i];
      x->u = y->u;
    }
  }
}

/// Adjust for side quadrature order to support variable order elements
/** It is important to make sure that the element Qmax, Lmax are sufficient
 *  to hold that of any neighboring side.  While this is usually the case,
 *  when you have a low-order element right next to a very high-order element
 *  and there is a parallel partition between the two, then this case cause
 *  trouble.  That is why we update the element workspace and the Field Qmax
 *  just to be safe.
*/
void Field::adjust_side_order_pc() {
  // cout << "Field::adjust_side_order_pc()" << endl;
  for (size_t e=0; e<el.size(); e++) {
    for (Ordinal i=0; i<el[e]->nSides(); i++) {
      Side *s = el[e]->side[i];
      if (s->link) {             // on master side
        Side *master = s;
        Side *slave  = s->link;
        master->match(slave);
        el[e]->update_workspace(master->qtot());
        if (master->qtot()>Qmax) Qmax = master->qtot();
      } else if (!s->subsides().empty()) {
        for (size_t j=0; j<s->subsides().size(); j++) {
          Side *slave  = s->subsides()[j].get();
          Side *master = s->subsides()[j]->base;
          master->match(slave);
          el[e]->update_workspace(master->qtot());
          if (master->qtot()>Qmax) Qmax = master->qtot();
        }
      }
    }
  }
}

/// Return true if no root.part.# file and Zoltan is active in the json input
bool Field::use_zoltan_partitioning() {
  bool uz = false;
#if defined(DGM_USE_ZOLTAN) && defined(DGM_PARALLEL)
  if (verb) comm->cout() << "  Field::use_zoltan_partitioning" << endl;
  Json::Value value;
  if (comm->Master()) {
    const int nprocs = comm->NumProc();
    string file = root + ".part." + boost::lexical_cast<string>(nprocs);
    ifstream in(file.c_str());
    if (!in) {      // no root.part.# file, check for zoltan parameter file
      file = root + ".json";
      ifstream json(file.c_str());
      if (json) {    // if root.json exists, check for Zoltan block
        Json::Reader reader;
        if (verb>1) cout << "  Reading JSON Zoltan input from " << file << endl;
        if (!reader.parse(json, value, true)) {
          throw DGM::exception("Failed to parse the parameter file " +
                               file + ":  " +
                               reader.getFormattedErrorMessages());
        }
        if (value.isMember("Zoltan")) {
          if (verb>2) {
            Json::StyledWriter writer;
            string output = writer.write(value["Zoltan"]);
            cout << "  Zoltan partition parameters:\n" << output;
          }
          uz = true;
          value = value["Zoltan"];
          if (value.isMember("Write Partition"))
            write_partition = value.get("Write Partition",
                                        write_partition).asBool();
          if (value.isMember("Weights")) {
            value = value["Weights"];
            if (value.isMember("File")) {
              weight_database = value.get("File", "reo_weights.txt").asString();
              if (!weight_database.empty()) {
                struct stat buf;
                // check if file exists in this directory
                int rc = stat(weight_database.c_str(), &buf);
                if (0 != rc) {
                  // file not found, get $PATH env variable
                  string path = getenv("PATH");
                  // parse out search paths and search for file
                  string::size_type st = path.find(':');
                  while (string::npos != st) {
                    // extract this path
                    string dirpath(path.begin(), path.begin()+st);
                    // search for weight_database name
                    dirpath += '/' + weight_database;
                    rc = stat(dirpath.c_str(), &buf);
                    if (0 == rc) {
                      // file exists in this directory
                      weight_database = dirpath;
                      break;
                    }
                    path = path.erase(0, st+1);
                    st = path.find(':');
                  }
                  // never found the weight database
                  if (rc != 0) {
                    cout << "  User specified weight database "
                         << weight_database
                         << " was not found" << endl;
                    weight_database.clear();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (1 == comm->NumProc()) uz = false;
  comm->Broadcast(&uz, sizeof(bool), 0);
  comm->Broadcast(&write_partition, sizeof(bool), 0);
  // broadcast string length
  int sz = weight_database.size();
  comm->Broadcast(&sz, 1, 0);
  // if valid weights database
  if (0 != sz) {
    // for terminating null
    ++sz;
    // allocate on non master nodes
    if (!comm->Master()) weight_database.resize(sz);
    comm->Broadcast(&weight_database[0], sz, 0);
  }
#endif
  return uz;
}

/// Zoltan parallel partitioning
/** Use Zoltan2 to perform a parallel, inline partitioning of the DGM::Field
    \todo Use PHG (hypergraph) from Zoltan
*/
void Field::zoltan2(const Mesh& mesh, Ordinal* w_it, Ordinal* w_end) const {
#ifdef DGM_USE_ZOLTAN
  if (!use_zoltan) return;

#if defined(DGM_PARALLEL) && defined(DGM_USE_EPETRA)

  // create zoltan2 partition file
  int nprocs = comm->NumProc();
  string nprocs_str = boost::lexical_cast<string>(nprocs);

  // use existing partition file if present
  string part_file(string(root + ".part." + nprocs_str).c_str());
  ifstream in(part_file.c_str());
  if (in) return;

  if (verb) comm->cout() << "  Starting Zoltan2 decomposition" << endl;
  CMC::Stopwatch cpu; if (comm->Master()) cpu.start();

  // extract zoltan parameters from root.json
  Json::Value value;
  if (comm->Master()) {
    string fname = root + ".json";
    ifstream file(fname.c_str());
    Json::Reader reader;
    reader.parse(file, value, true);
    value = value["Zoltan"];
  }
  Json::broadcast(comm,value);

  // trilinos xml input
  Teuchos::ParameterList params("test params");
  Json::Value &zoltan = value;
  Json::Value &block_2 = zoltan["Partition"];
  case_insensitive_string cis(block_2.get("algorithm",
                                          "pqjagged").asCString());
  params.set("algorithm", boost::algorithm::to_lower_copy(cis).c_str());

  // if PQJagged or RCB use Zoltan2 interface
  // if hypergraph, use Zoltan interface
  if (cis == "pqjagged" || cis == "rcb") {
    if (comm->Master()) cout << "  Using Zoltan2 " << cis.c_str() << endl;

    // second (partition) block (used by both rcb and pqjagged)
    params.set("imbalance_tolerance",
      block_2.get("imbalance_tolerance", 1.1).asDouble());
    params.set("compute_metrics",
      block_2.get("compute_metrics", "true").asString());
    // num_global_parts input is unsupported from the root.json file
    // to avoid having inconsistent mpi size errors
    params.set("num_global_parts", nprocs);

    // first (parameter) block
    Json::Value &parameters = zoltan["Parameters"];
    params.set("debug_level", parameters.get("debug_level",
      "basic_status").asString());
    params.set("debug_procs", parameters.get("debug_procs", 0).asInt());
    params.set("error_check_level",
      parameters.get("error_check_level", "debug_mode_assertions").asString());

    // third (geometry) block
    Json::Value &geometry = zoltan["Geometry"];
    params.set("bisection_num_test_cuts",
               geometry.get("bisection_num_test_cuts", 1).asInt());

    if (cis == "pqjagged") {
      // check invariant (what is it?)
      params.set("pqParts", geometry.get("pqParts", "1").asString());
      params.set("timer_output_stream",
                 geometry.get("timer_output_stream", "std::cout").asString());
      params.set("force_binary_search",
                 geometry.get("force_binary_search", "no").asString());
      params.set("force_linear_search",
                 geometry.get("force_linear_search", "no").asString());
      params.set("parallel_part_calculation_count",
                 geometry.get("parallel_part_calculation_count", "1").asInt());
    }

    // zoltan types
    typedef Scalar scalar_t;
    typedef std::make_signed<LocalSize> ::type  localId_t;
    typedef std::make_signed<GlobalSize>::type globalId_t;

    vector<scalar_t> wgts(w_it, w_end);

    // rearrange for zoltan2 coordinates
    vector<const scalar_t *> coordvec(_nsd);
    vector<int> coordStrides(_nsd, _nsd);
    coordvec[0] = &mesh.point[0].x;
    if (1 < _nsd) coordvec[1] = &mesh.point[0].y;
    if (2 < _nsd) coordvec[2] = &mesh.point[0].z;

    // global ids
    vector<globalId_t> global_ids(mesh.ne);
    for (GlobalSize i=0; i<mesh.ne; ++i) global_ids[i] = partition->eid(i);

    // weights
    vector<const scalar_t*> weightVec(1, &wgts[0]);
    vector<int> weightStrides(1);

    // Zoltan2 types
    typedef Zoltan2::BasicUserTypes<scalar_t, localId_t, globalId_t> myTypes;
    typedef Zoltan2::BasicVectorAdapter<myTypes> inputAdapter_t;

    // decompose
    inputAdapter_t ia(mesh.ne, &global_ids[0], coordvec, coordStrides,
                      weightVec, weightStrides);
    Zoltan2::PartitioningProblem<inputAdapter_t>
      zoltan_problem(&ia, &params,
                     dynamic_cast<const DGM::MpiComm*>(comm.get())->mpicomm());
    zoltan_problem.solve();

    const Zoltan2::PartitioningSolution<inputAdapter_t> &solution =
      zoltan_problem.getSolution();
#if (TRILINOS_MAJOR_MINOR_VERSION >= 111300)
    const inputAdapter_t::part_t *partition2 = solution.getPartListView();
#elif (TRILINOS_MAJOR_MINOR_VERSION > 110800)
    const inputAdapter_t::part_t *partition2 = solution.getPartList();
#else
    const zoltan2_partId_t *partition2 = solution.getPartList();
#endif

    // update the partition with new decomposition
    partition->update(partition2, partition2+mesh.ne);
  }
  else if (cis == "hypergraph") {
    if (comm->Master())
      cout << "  Repartitioning using Zoltan Parallel Hypergraph" << endl;
    HyperGraphData hg;
    std::vector<int> wgt_it(w_it,w_end);
    hg.wgt_it = wgt_it.data();
    hg.numMyVertices = mesh.ne;
    // number of hyperedges is number of elements
    hg.numMyHEdges = mesh.ne;
    // total number of hyperedge vertices
    hg.numAllNbors = mesh.con.size() + mesh.ne;
    // global id of vertices (elements)
    hg.vtxGID = new ZOLTAN_ID_TYPE[hg.numMyVertices];
    // global id of each hyperedge, since one edge per element
    // use global element id
    hg.edgeGID = new ZOLTAN_ID_TYPE[hg.numMyVertices];
    for (int i=0; i<hg.numMyVertices; ++i)
      hg.edgeGID[i] = hg.vtxGID[i] = partition->eid(i);
    // index into nborGID array of hyperedge's vertices (elements)
    hg.nborIndex = new int[hg.numMyHEdges];
    hg.nborIndex[0] = 0;
    // Vertices of edge edgeGID[i] begin at nborGID[nborIndex[i]]
    hg.nborGID = new ZOLTAN_ID_TYPE[hg.numAllNbors];
    // basically just con array (if con array is ordered by local element id)
    hg.nborGID[0] = mesh.con[0].eid;
    hg.nborGID[1] = mesh.con[0].leid;
    int k=1;
    for (unsigned int i=1,j=2; i<mesh.con.size(); ++i,++j) {
      assert(k <= hg.numAllNbors);
      if (mesh.con[i-1].eid != mesh.con[i].eid) {
        hg.nborIndex[k] = j;
        ++k;
        hg.nborGID[j] = mesh.con[i].eid;
        ++j;
      }
      hg.nborGID[j] = mesh.con[i].leid;
    }

    struct Zoltan_Struct *zz =
      Zoltan_Create(dynamic_cast<const DGM::MpiComm*>(comm.get())->mpicomm());

    // set phg parameters (no user setable parameters just yet)
    Zoltan_Set_Param(zz, "DEBUG_LEVEL", "0");
    Zoltan_Set_Param(zz, "LB_METHOD", "HYPERGRAPH");   // partitioning method
    Zoltan_Set_Param(zz, "HYPERGRAPH_PACKAGE", "PHG"); // version of method
    Zoltan_Set_Param(zz, "NUM_GID_ENTRIES", "1");   // global IDs are integers
    Zoltan_Set_Param(zz, "NUM_LID_ENTRIES", "1");   // local IDs are integers
    Zoltan_Set_Param(zz, "RETURN_LISTS", "EXPORT"); // export AND import lists
    Zoltan_Set_Param(zz, "IMBALANCE_TOL", "1.0");
    // vertex weight is elmt wgt
    Zoltan_Set_Param(zz, "OBJ_WEIGHT_DIM", "1");  // default vertex weights
    Zoltan_Set_Param(zz, "EDGE_WEIGHT_DIM", "0"); // default hyperedge weights
    Zoltan_Set_Param(zz, "LB_APPROACH", "PARTITION");
    Zoltan_Set_Param(zz, "PHG_REFINEMENT_QUALITY", "10.0");

    // to ensure we get same random number everytime we run.
    unsigned int idum = 123456789u;
    idum = (1664525u*idum + 1013904223u) >> 1;
    string seed = boost::lexical_cast<string>(idum);
    Zoltan_Set_Param(zz, "Seed", seed.c_str());

    // query functions
    Zoltan_Set_Num_Obj_Fn(zz, get_number_of_vertices, &hg);
    Zoltan_Set_Obj_List_Fn(zz, get_vertex_list, &hg);
    Zoltan_Set_HG_Size_CS_Fn(zz, get_hypergraph_size, &hg);
    Zoltan_Set_HG_CS_Fn(zz, get_hypergraph, &hg);

    int changes, numGidEntries, numLidEntries, numImport, numExport;
    int *importProcs = 0, *importToPart = 0;
    int *exportProcs = 0, *exportToPart = 0;
    ZOLTAN_ID_PTR importGlobalGids, importLocalGids;
    ZOLTAN_ID_PTR exportGlobalGids, exportLocalGids;

    // Zoltan_Generate_Files(zz, "kdd", 1, 0, 0, 1);
    int rc = Zoltan_LB_Partition(zz, // input (remaining fields are output)
      &changes,          // 1 if partitioning was changed, 0 otherwise
      &numGidEntries,    // Number of integers used for a global ID
      &numLidEntries,    // Number of integers used for a local ID
      &numImport,        // Number of vertices to be sent to me
      &importGlobalGids, // Global IDs of vertices to be sent to me
      &importLocalGids,  // Local IDs of vertices to be sent to me
      &importProcs,      // Process rank for source of each incoming vertex
      &importToPart,     // New partition for each incoming vertex
      &numExport,        // Number of vertices I must send to other processes
      &exportGlobalGids, // Global IDs of the vertices I must send
      &exportLocalGids,  // Local IDs of the vertices I must send
      &exportProcs,      // Process to which I send each of the vertices
      &exportToPart);    // Partition to which each vertex will belong
    if (rc != ZOLTAN_OK)
      throw DGM::exception("Zoltan failed to partition mesh");

    // partition after calling zoltan
    int rank = comm->MyPID();
    vector<int> parts(hg.numMyVertices, rank);
    for (int i=0; i<numExport; ++i)
      parts[exportLocalGids[i]] = exportToPart[i];

    // check that each core ended up with at least one element
    vector<int> out_parts(comm->NumProc()), all_parts(comm->NumProc());;
    for (vector<int>::size_type i=0; i<parts.size(); ++i) ++out_parts[parts[i]];
    comm->MaxAll(&out_parts[0], &all_parts[0], all_parts.size());
    // count number of ranks with zero elements
    int min_nepc = count(all_parts.begin(), all_parts.end(), 0);
    if (0 < min_nepc)
      // exit if any core has zero elements
      throw DGM::exception("Zoltan produced partition with zero elements "
                           "on some cores");

    // update the partition with new decomposition
    partition->update(parts.begin(), parts.end());

    // acquire / release semantics (LIFO)
    Zoltan_LB_Free_Part(&importGlobalGids, &importLocalGids,
                        &importProcs, &importToPart);
    Zoltan_LB_Free_Part(&exportGlobalGids, &exportLocalGids,
                        &exportProcs, &exportToPart);
    Zoltan_Destroy(&zz);
    delete [] hg.nborGID;
    delete [] hg.nborIndex;
    delete [] hg.edgeGID;
    delete [] hg.vtxGID;
  }

  // user settable flag to write global partition
  // file after running zoltan
  if (write_partition) {

    int rank = comm->MyPID();
    GlobalSize gne = partition->gne();

    // For large problems don't want each rank allocating a
    // contiguous buffer of size gne, so we iteratively reduce
    // the global partition vector into buffers of this size.
    GlobalSize bufsize = 10000000;
    bufsize = bufsize < gne ? bufsize : gne;

    // populate our global element index with rank (assume they're sorted)
    const GlobalSize *it = partition->eid_data();
    const GlobalSize *end = it, *last = it + partition->ne();

    if (0 == rank) {
      // always write partition file after running zoltan
      string part_file = root + ".part." + nprocs_str;
      std::ofstream ofp(part_file.c_str());
      cout << "  Writing Zoltan Partition to " << part_file << endl;

      // allocate vectors to assemble global partition in
      vector<GlobalSize> global_part_list(bufsize);
      vector<GlobalSize> local_part_list(bufsize);
      GlobalSize amt = bufsize;

      for (GlobalSize j=0; j<gne; j+=bufsize) {

        // position iterators for element ids in range [j,j+bufsize)
        while (*it < j) ++it;
        while (end != last && *end < j+bufsize) ++end;

        for (; it != end; ++it) {
          local_part_list[*it-j] = rank;
        }
        comm->Max(&local_part_list[0], &global_part_list[0], bufsize);

        // write out the next bufsize partition ranks
        if (gne - j < bufsize) amt = gne - j;
        for (GlobalSize i=0; i<amt; ++i) {
          ofp << global_part_list[i] << '\n';
        }

        // zero out for next block
        std::fill(local_part_list.begin(), local_part_list.end(), 0);
      }

      ofp.close();
    } else {
      GlobalSize eid = 0;
      vector<GlobalSize> local_part_list(bufsize);
      for (GlobalSize j=0; j<gne; j+=bufsize) {

        // position iterators for element ids in range [j,j+bufsize)
        while (*it < j) ++it;
        while (end != last && *end < j+bufsize) ++end;

        for (; it != end; ++it) {
          local_part_list[*it-j] = rank;
        }

        comm->Max(&local_part_list[0], &eid, bufsize);

        // zero out for next block
        std::fill(local_part_list.begin(), local_part_list.end(), 0);
      }
    }
  }
  comm->Barrier();
  if (verb) comm->cout() << "  Completed Zoltan2 decomposition in "
                         << cpu.stop() << " sec" <<endl;
#endif  // defined(DGM_PARALLEL) && defined(DGM_USE_EPETRA)
#endif  // DGM_USE_ZOLTAN
}

/** Constructs Field from an external mesh file (original version)
    \param[in] p default polynomial order
    \param[in] q default quadrature order
    \param[in] root_ root file name
    \param[in] name_ name of this Field
    \param[in] domain_partition parallel partition for the parent Domain
    \param[in] comm_ communicator for this object
    \param[in] p_inc increment in polynomial order
    \param[in] blocksize blocksize if doing element blocks
*/
Field::Field(const Ordinal p, const Ordinal q, const string &root_,
             const string &name_,
             Partition<GlobalSize,LocalSize,Scalar>::Ptr &domain_partition,
             const DGM::Comm::Ptr comm_, const int p_inc,
             const Ordinal blocksize ) :
  comm(comm_), nbc(0), BlockSize(blocksize), root(root_), name(name_),
  bndry_stats(NULL), verb(comm->verbosity()),
  write_partition(true), use_zoltan(use_zoltan_partitioning()),
  have_my_bbox(false)
{
  comm->cout() << "Constructing Field for " << name
               << " using ASCII, serial approach" << endl;
  string buffer;
  if (root=="-help") comm->exit(DGM::SUCCESS);

  // open mesh file and read parameters
  string fname = root+".msh";
  if (verb>1) comm->cout() << "  Opening file " << fname << endl;
  ifstream in(fname.c_str());
  if (!in) {
    stringstream msg;
    msg << "Field::Field() Could not open mesh file: " << fname;
    comm->error(msg.str());
  }
  if (verb>1) comm->cout() << "  Reading mesh from " << fname << endl;
  getline(in,buffer);
  if (!(in>>gne)) comm->error("Field: Cannot read number of elements");
  if (gne >= (GlobalSize)numeric_limits<LocalSize>::max())
    throw DGM::exception("Global number of elements overflows local element\n"
                         "storage.  Must use parallel construction!");
  else
    ne = (LocalSize)gne;
  if (!(in>>_nsd)) comm->error("Field: Cannot read number of dimensions");
  getline(in,buffer);
  if (verb>1) comm->cout() << "Building " << name << " Field:  ne = "
                         << ne << ", nsd = " << _nsd << endl;

  // read the order file (if present).   [currently not scalable]

  // This assumes that p and q have already been incremented
  vector<LocalSize> pv(gne,p);
  vector<LocalSize> qv(gne,q);
  fname = root+".ord";
  ifstream order(fname.c_str());
  if (order) {
    //comm->cout() << "  Reading the order file" << endl;
    GlobalSize i;
    LocalSize pl, ql;
    comm->cout() << "  Reading order file " << fname << endl;
    getline(order,buffer);
    while (order >> i >> pl >> ql) {
      getline(order,buffer);
      if (i>gne) comm->error("Field: Illegal element number in ord file");
      pv[i] = pl + p_inc;
      qv[i] = ql;
      // The default number of quadrature points in the interior is q = p +
      // 1.5 \approx p + 2 which makes sure that the interior integrals are
      // computed to order 2p when using Gauss-Lobatto-Legendre quadrature
      // which can integrate 2q-3 polynomial exactly.  The condition required
      // for convergence of smooth solutions is that you must integrate 2p
      // polynomials exactly to ensure p+1 convergence as discussed by
      // Cockburn & Shu (JCP 141, p. 203, 1998)
      if (qv[i]==0)
        qv[i] = pv[i] + 2;  // default
      else
        qv[i] += p_inc;     // need to increment quadrature order as well
    }
  }
#ifdef DGM_FIELD_VERBOSE
  // write debug information for element order
  for (GlobalSize e=0; e<gne; e++)
    cout << e << ", " << pv[e] << ", " << qv[e] << endl;
#endif

#ifdef DGM_USE_MD_COUPLE
  // read the model file (if present) [currently not scalable]
  vector<Model::Type> pmodel(ne);
  fname = root+".mod";
  ifstream model(fname.c_str());
  if (model) {
    GlobalSize i;
    LocalSize pm;
    comm->cout() << "  Reading model file " << fname << endl;
    getline(model,buffer);
    while (model >> i >> pm) {
      getline(model,buffer);
      if (i>gne) comm->error("Field: Illegal element number in model file");
      switch(pm){
      case 0:
        pmodel[i] = Model::ADV_DIFF;
        break;
      case 1:
        pmodel[i] = Model::EULER;
        break;
      case 2:
        pmodel[i] = Model::NAVIER_STOKES;
        break;
      case 3:
        pmodel[i] = Model::WAVE;
        break;
      case 4:
        pmodel[i] = Model::LINEULER;
        break;
      default:
        comm->error("Field: Illegal Model::Type in model file");
      }
    }
  } else
    for(Size i=0;i<ne;i++) pmodel[i] = Model::EULER;
#endif

  comm->Barrier();
  if (verb>1) comm->cout() << "  Starting to build elements" << endl;
  CMC::Stopwatch cpu; cpu.start();

  // initialize the maximum Quadrature and Mode orders for this field
  Qmax = 0;
  Lmax = 0;

  // make the elements [should only do on the local number of elements]
  el.resize(ne);
  if (_nsd==1) {
    vector<Point> X(2);
    for (LocalSize e=0; e<ne; e++) {
      getline(in,buffer);  // get element description
      in >> X[0].x >> X[1].x;
      if ( lowerCase(buffer).find("nodalline") != buffer.npos) {
        el[e] = new NodalLine(e,pv[e],X);
      } else if ( lowerCase(buffer).find("spectralline") != buffer.npos) {
        el[e] = new SpectralLine(e,pv[e],X);
      } else if ( lowerCase(buffer).find("line") != buffer.npos) {
        el[e] = new Line(e,pv[e],qv[e],X);
      } else {
        throw DGM::exception("Unsupported 1d element type = "+buffer);
      }
      getline(in,buffer);
      Qmax = std::max( Qmax, qv[e] );
      Lmax = std::max( Lmax, pv[e]+1);
    }
  } else if (_nsd==2) {
    int nverts;
    string type;
    vector<Point> X(4);
    for (LocalSize e=0; e<ne; e++) {
      getline(in,type);  // get element description
      if ( lowerCase(type).find("quad")==type.npos ) // must be a Tri
        nverts = 3;
      else
        nverts = 4;
      // cout << "Element " << e << " of type " << type << " with nverts = "
      //      << nverts << endl;
      for (int i=0; i<nverts; ++i)
        in >> X[i].x;
      getline(in,buffer);
      for (int i=0; i<nverts; ++i)
        in >> X[i].y;
      getline(in,buffer);
#ifdef DGM_USE_MD_COUPLE
      if (nverts == 4) {
        if ( lowerCase(type).find("nodalquad")!=type.npos ) {
          el[e] = new NodalQuad(e,pv[e],X,pmodel[e]);
        } else if ( lowerCase(type).find("spectralquad")!=type.npos ) {
          el[e] = new SpectralQuad(e,pv[e],X,pmodel[e]);
        } else {
          el[e] = new Quad(e,pv[e],qv[e],X,pmodel[e]);
        }
        Qmax = std::max( Qmax, qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1) );
      } else {

        if ( type.find("NodalTri")==type.npos &&
             type.find("nodaltri")==type.npos &&
             type.find("NODALTRI")==type.npos) {
          el[e] = new Tri(e,pv[e],qv[e],X,pmodel[e]);
        } else {
          el[e] = new NodalTri(e,pv[e],qv[e],X,pmodel[e]);
        }
        Qmax = std::max( Qmax, qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1+1)/2 );
      }
#else
      if (nverts == 4) {
        if ( lowerCase(type).find("nodalquad")!=type.npos ) {
          el[e] = new NodalQuad(e,pv[e],X);
        } else if ( lowerCase(type).find("spectralquad")!=type.npos ) {
          el[e] = new SpectralQuad(e,pv[e],X);
        } else {
#ifdef DGM_USE_COMPILETIMEQUAD
          el[e] = new_quad(e,pv[e],qv[e],X);
#else
          el[e] = new Quad(e,pv[e],qv[e],X);
#endif
        }
        Qmax = std::max( Qmax, qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1) );
      } else if (nverts == 3) {
        if ( type.find("NodalTri")==type.npos &&
             type.find("nodaltri")==type.npos &&
             type.find("NODALTRI")==type.npos) {
          el[e] = new Tri(e,pv[e],qv[e],X);
        } else {
          el[e] = new NodalTri(e,pv[e],X);
        }
        Qmax = std::max( Qmax, qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1+1)/2 );
      } else {
        throw DGM::exception("Field: nVerts = "+asString(nverts)+
                             " not supported for element type "+type);
      }
#endif
    }
  } else if (_nsd==3) {
#ifdef DGM_PARALLEL
    // was 3*nverts*ne; for now, most nverts can be is 8
    const int num_coords = 3*8*ne;
    vector<Scalar> coords(num_coords);
    vector<int> nverts(ne);
    vector<int> hex_type(ne, 0);
    int lerror = 0;
    if (comm->Master()) {    // just the master reads
      int n=0;
      for (LocalSize e=0; e<ne; ++e) {
        getline(in,buffer);  // get element description
        const string lcbuf = lowerCase(buffer);
        if (lcbuf.find("hex")!=lcbuf.npos) {
          nverts[e] = 8;
          if ( lcbuf.find("nodalhex")!=lcbuf.npos )
            hex_type[e] = 1;
          else if (lcbuf.find("spectralhex")!=lcbuf.npos )
            hex_type[e] = 2;
        } else if (lcbuf.find("tet")!=lcbuf.npos) {
          nverts[e] = 4;
#ifdef DGM_USE_SLAB
        } else if (lcbuf.find("slab")!=lcbuf.npos) {
          nverts[e] = 2;
#endif
        } else {
          comm->cerr()<<"Field::Field() Unknown 3d element type" << endl;
          lerror = 1;
        }
        for (int i=0; i<nverts[e]; ++i) in >> coords[n++];
        getline(in,buffer);
        for (int i=0; i<nverts[e]; ++i) in >> coords[n++];
        getline(in,buffer);
        for (int i=0; i<nverts[e]; ++i) in >> coords[n++];
        getline(in,buffer);
      }
      if (n > num_coords) {     // NodalTets won't use whole buffer
        comm->cerr() << "Field::Field() File read error of some kind." << endl;
        lerror = 1;
      }
    }
    comm->Broadcast(&lerror, 1, 0); // Master is always 0
    if (lerror) comm->error("Field: Error reading elements");
    comm->Broadcast(&coords[0], num_coords, 0);
    comm->Broadcast(&nverts[0], ne, 0);
    comm->Broadcast(&hex_type[0], ne, 0);
    vector<Point> X(8);
    int n = 0;
    for (LocalSize e=0; e<ne; ++e) {
      for (int i=0; i<nverts[e]; i++) X[i].x = coords[n++];
      for (int i=0; i<nverts[e]; i++) X[i].y = coords[n++];
      for (int i=0; i<nverts[e]; i++) X[i].z = coords[n++];
      if (nverts[e] == 8) {
        if ( hex_type[e]==0 )
          el[e] = new Hex(e,pv[e],qv[e],X);
        else if (hex_type[e]==1)
          el[e] = new NodalHex(e,pv[e],X);
        else if (hex_type[e]==2) {
          el[e] = new SpectralHex(e,pv[e],X);
        } else
          throw DGM::exception("Field: illegal hex_type "+asString(hex_type)+
                               " on element id "+asString(e));
        Qmax = std::max( Qmax, qv[e] * qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1)*(pv[e]+1) );
      } else if (nverts[e] == 4) {
        el[e] = new NodalTet(e,pv[e],X);
        Qmax = std::max( Qmax, qv[e] * qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+2)*(pv[e]+3)/6 );
#ifdef DGM_USE_SLAB
      } else if (nverts[e] == 2) {
        // \todo Need a way to input Nx, Nz and Lx, Lz
         const Ordinal Nx=8;
         const Ordinal Nz=8;
         const Scalar Lx=two*pi;
         const Scalar Lz=two*pi;
         comm->cout()<<"Making Slab("<<Nx<<","<<Nz<<","<<Lx<<","<<Lz
             <<") for element " << e << endl;
         el[e] = new Slab(e,pv[e],qv[e],X,Nx,Nz,Lx,Lz);
         Qmax = std::max( Qmax, qv[e] );
         Lmax = std::max( Lmax, (pv[e]+1) );
#endif
      } else {
        comm->error("Field::Field() unknown 3d element with nverts = "+
                    asString(nverts[e]));
      }
    }
#else
    int nverts = 0;
    string type;
    vector<Point> X(8);
    for (LocalSize e=0; e<ne; e++) {
      getline(in,type);       // get element description
      const string lctype = lowerCase(type);
      if ( lctype.find("tet") != lctype.npos )
        nverts = 4;
      else if ( lctype.find("hex") != lctype.npos )
        nverts = 8;
#ifdef DGM_USE_SLAB
     else if ( lctype.find("slab") != lctype.npos )
        nverts = 2;
#endif
     else
        comm->error("Field::Field() unknown 3d element type "+type);
      for (int i=0; i<nverts; i++) in >> X[i].x;
      getline(in,buffer);
      for (int i=0; i<nverts; i++) in >> X[i].y;
      getline(in,buffer);
      for (int i=0; i<nverts; i++) in >> X[i].z;
      getline(in,buffer);
      if (nverts == 8) {
        if ( lctype.find("nodalhex") != lctype.npos )
          el[e] = new NodalHex(e,pv[e],X);
        else if ( lctype.find("spectralhex") != lctype.npos )
          el[e] = new SpectralHex(e,pv[e],X);
        else
          el[e] = new Hex(e,pv[e],qv[e],X);
        Qmax = std::max( Qmax, qv[e] * qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+1)*(pv[e]+1) );
      } else if ( lctype.find("tet") != lctype.npos ) {
        if ( lowerCase(type).find("nodaltet")!=type.npos )
          el[e] = new NodalTet(e,pv[e],X);
        else
          comm->error("Field::Field() Modal Tet elements not supported yet!");
        Qmax = std::max( Qmax, qv[e] * qv[e] * qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1)*(pv[e]+2)*(pv[e]+3)/6 );
#ifdef DGM_USE_SLAB
      } else if ( lctype.find("slab") != lctype.npos ) {
        // \todo Need a way to input Nx, Nz and Lx, Lz
        const Ordinal Nx=8;
        const Ordinal Nz=8;
        const Scalar Lx=two*pi;
        const Scalar Lz=two*pi;
        comm->cout()<<"Making Slab("<<Nx<<","<<Nz<<","<<Lx<<","<<Lz
            <<") for element " << e << endl;
        el[e] = new Slab(e,pv[e],qv[e],X,Nx,Nz,Lx,Lz);
        Qmax = std::max( Qmax, qv[e] );
        Lmax = std::max( Lmax, (pv[e]+1) );
#endif
      } else {
        comm->error("Field::Field() unknown 3d element type "+type);
      }
    }
#endif
  } else {
    stringstream msg;
    msg<<"Illegal value: nsd = " << _nsd << " in Field::Field()";
    comm->error(msg.str());
  }
  comm->Barrier();
  comm->cout()<<"  Constructed "<<ne<<" elements in "<<cpu.stop()
              <<" seconds."<<endl;

  // setup global element ids (on sides and elements)
  // Doing so, makes the resulting code a little clearer since the local
  // and global ids are the same during this startup phase.
  for (LocalSize e=0; e<ne; e++) {
    el[e]->gid(el[e]->lid());
    for (Ordinal n=0; n<el[e]->nSides(); ++n) {
      //cout << comm->MyPID() << ": e = " << e << ", side = " << n << endl;
      el[e]->side[n]->geid(el[e]->gid());
    }
  }
  // setup a default partition with all elements on all processors.  This
  // gets distributed and reset in make_partition
  partition.reset(new Partition<GlobalSize,LocalSize,Scalar>(gne,comm));

  if (verb>1) comm->cout() << "  read_curve" << endl;
  read_curve( root );           // read in curve types
  if (verb>1) comm->cout() << "  read_node_connectivity" << endl;
  read_node_connectivity(root); // setup nodal connectivity
  if (verb>1) comm->cout() << "  set_side_links" << endl;
  set_side_links(root);         // make connectivity links
  if (verb>1) comm->cout() << "  set_global_side_id" << endl;
  set_global_side_id();         // make global side id's
  if (verb>1) comm->cout() << "  adjust_side_order" << endl;
  adjust_side_order();          // adjust side qpts to match
  if (verb>1) comm->cout() << "  make_partition" << endl;
  make_partition( root );       // partition the mesh if parallel
  if (verb>1) comm->cout() << "  initialize_bc" << endl;
  initialize_bc(root);          // setup boundary sides
  if (verb>1) comm->cout() << "  make_storage" << endl;
  make_storage();               // allocate storage
  CMC::Stopwatch timer; timer.start();
  if (verb>1) {
    comm->cout() << "  compute_geometry...";
    comm->cout().flush();
  }
  compute_geometry();           // make element mappings, Jacobian, mass matrix
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
  if (verb>1) {
    comm->cout() << "  compute_side_geometry...";
    comm->cout().flush();
  }
  compute_side_geometry();      // make side mapping, Jacobian, normal vectors
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
#ifdef DGM_ALLOW_HANGING_NODES
  if (verb>1) {
    comm->cout() << "  compute_subside_geometry...";
    comm->cout().flush();
  }
  compute_subside_geometry();   // make side mapping, Jacobian, normal vectors
  if (verb>1) comm->cout() << "in " << timer.stop() << " seconds" << endl;
#endif
#ifdef DGM_USE_ELEMENT_BLOCKS
  if (verb>1) comm->cout() << "  initialize_element_blocks" << endl;
  initialize_element_blocks();
#endif
  if (verb>1) comm->cout() << "  write_weights" << endl;
  write_weights( root+".wgt" );
  if (verb>1) comm->cout() << "  write_graph" << endl;
  write_graph( root+".grf" );
  if (verb>1) comm->cout() << "  bndry_stats" << endl;
  bndry_stats = new BndryStats( root, this );  // setup bndry statistics
#ifdef DGM_FIELD_VERBOSE
  print_side_links();           // check connectivity
  if (comm->Master()) write_mesh("mesh.dat");
  if (comm->Master()) write_connectivity("connect.dat");
#endif
  in.close();
  domain_partition = partition; // set the Domain partition to be the field's
#ifdef DGM_OUTPUT_DOF           // output the degrees of freedom
  cout<<comm->MyPID()<<":  ne = "<<ne<<", ndof = "<<ndof()<<endl;
#endif
#ifdef DGM_WRITE_BINARY_FILES
  {
    Mesh mesh;
    mesh.nsd = _nsd;
    for (LocalSize i=0; i<partition->ne(); ++i) {
      cout << comm->MyPID() <<" id=["<<i<<"]:"<<el[i]->id<<endl;
    }
    ifstream con((root+".con").c_str());
    mesh.CopyIn(con, el, partition);
    mesh.MPI_write(comm, partition, root+".grd");
    mesh.MPI_write_connectivity(comm, partition, root+".cn");
    mesh.MPI_read (comm, partition, root+".grd");
    if (comm->MyPID())
      mesh.write("Check_Mesh_1.msh");
    else
      mesh.write("Check_Mesh_0.msh");
    cerr<<" Finished writing Binary files.  I'm going now....."<<endl;
    throw DGM::exception("Debugging termination");
  }
#endif
#if 0
  {
    bool pass = true;
    for (LocalSize e=0; e<ne; e++) {
      if (el[e]->gid != el[e]->id) {
        cout << comm->MyPID() << ": " << e << " " << el[e]->gid
             << " " << el[e]->id << endl;
        pass = false;
      }
    }
    if (!pass) throw DGM::exception("Did not pass global id test");
  }
#endif
  if (verb>1) comm->cout() << "Finished Field::Field constructor" << endl;
}

/** Construct Field from an internal DGM::Mesh
    \param[in] p default polynomial order
    \param[in] q default quadrature order
    \param[in] grid Mesh data-structure for this Field
    \param[in] name_ name of this Field
    \param[in] action type of construction to perform
    \param[in] comm_ communicator for this object
    \param[in] blocksize blocksize if doing element blocks
*/
Field::Field(const Ordinal p, const Ordinal q, Mesh &grid, const string &root_,
             const string &name_, const Construction action,
             const DGM::Comm::Ptr comm_, const Ordinal blocksize) :
  comm(comm_), nbc(0), BlockSize(blocksize), root(root_), name(name_),
  bndry_stats(NULL), verb(comm->verbosity()),
  use_zoltan(use_zoltan_partitioning()), have_my_bbox(false)
{
  comm->cout() << "Constructing Field for " << name
               << " from a DGM::Mesh" << endl;
  gne = grid.ne;
  if (gne >= (GlobalSize)numeric_limits<LocalSize>::max())
    throw DGM::exception("Global number of elements overflows local element\n"
                         "storage building Field from internal mesh!");
  else
    ne = numeric_cast<LocalSize>(gne);
  _nsd = grid.nsd;
  ndof(0);
  qtot(0);
  el.resize(gne);
  GlobalSize n = 0;
  Qmax = 0;
  Lmax = 0;
  if (verb>1)
    comm->cout() << "  Global nel = " << gne << ", nsd = " << _nsd << endl;
  for (LocalSize e=0; e<ne; ++e) {
    if (_nsd == 1) {
      if (grid.etype[e] == Topology::Line) {
        vector<Point> X(2);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        el[e]= new Line(e,p,q,X);
        Qmax = std::max( Qmax, q );
        Lmax = std::max( Lmax, p+1);
      } else if (grid.etype[e] == Topology::NodalLine) {
        vector<Point> X(2);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        el[e]= new NodalLine(e,p,X);
        Qmax = std::max( Qmax, q );
        Lmax = std::max( Lmax, p+1);
      } else if (grid.etype[e] == Topology::SpectralLine) {
        vector<Point> X(2);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        el[e]= new NodalLine(e,p,X);
        Qmax = std::max( Qmax, q );
        Lmax = std::max( Lmax, p+1);
      } else {
        stringstream ss;
        ss << "Field: Unknown 1d element type (etype = " <<grid.etype[e]<< ") "
           << "for element " << e;
        comm->error(ss.str());
      }
    } else if (_nsd == 2) {
      if (grid.etype[e] == Topology::Quad) {
        vector<Point> X(4);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        //comm->cout()<<"  Making Quad e = "<<e<<", p = "<<p<<", q = "<<q<<endl;
#ifdef DGM_USE_COMPILETIMEQUAD
        el[e] = new_quad(e,p,q,X);
#else
        el[e] = new Quad(e,p,q,X);
#endif
        Qmax = std::max( Qmax, q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::NodalQuad) {
        vector<Point> X(4);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        el[e] = new NodalQuad(e,p,X);
        Qmax = std::max( Qmax, q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::SpectralQuad) {
        vector<Point> X(4);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        el[e] = new SpectralQuad(e,p,X);
        Qmax = std::max( Qmax, q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::Tri) {
        vector<Point> X(3);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        el[e] = new Tri(e,p,q,X);
        Qmax = std::max( Qmax, q*q );
        Lmax = std::max( Lmax, (p+1)*(p+2)/2 );
      } else if (grid.etype[e] == Topology::NodalTri) {
        vector<Point> X(3);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        el[e] = new NodalTri(e,p,X);
        Qmax = std::max( Qmax, q*q );
        Lmax = std::max( Lmax, (p+1)*(p+2)/2 );
      } else {
        stringstream ss;
        ss << "Field: Unknown 2d element type (etype = " <<grid.etype[e]<< ") "
           << "for element " << e;
        comm->error(ss.str());
      }
    } else if (_nsd == 3) {
      if (grid.etype[e] == Topology::Hex) {
        vector<Point> X(8);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        X[4] = grid.point[n++];
        X[5] = grid.point[n++];
        X[6] = grid.point[n++];
        X[7] = grid.point[n++];
        el[e] = new Hex(e,p,q,X);
        Qmax = std::max( Qmax, q*q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::NodalHex) {
        vector<Point> X(8);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        X[4] = grid.point[n++];
        X[5] = grid.point[n++];
        X[6] = grid.point[n++];
        X[7] = grid.point[n++];
        el[e] = new NodalHex(e,p,X);
        Qmax = std::max( Qmax, q*q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::SpectralHex) {
        vector<Point> X(8);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        X[4] = grid.point[n++];
        X[5] = grid.point[n++];
        X[6] = grid.point[n++];
        X[7] = grid.point[n++];
        el[e] = new SpectralHex(e,p,X);
        Qmax = std::max( Qmax, q*q*q );
        Lmax = std::max( Lmax, (p+1)*(p+1)*(p+1) );
      } else if (grid.etype[e] == Topology::NodalTet) {
        vector<Point> X(4);
        X[0] = grid.point[n++];
        X[1] = grid.point[n++];
        X[2] = grid.point[n++];
        X[3] = grid.point[n++];
        el[e] = new NodalTet(e,p,X);
        Qmax = std::max( Qmax, q*q*q );
        Lmax = std::max( Lmax, (p+1)*(p+2)*(p+3)/6 );
      } else {
        stringstream ss;
        ss << "Field: Unknown 3d element type (etype = " <<grid.etype[e]<< ") "
           << "for element " << e;
        comm->error(ss.str());
      }
    } else {
      stringstream msg;
      msg << "Field: Illegal value of nsd = " << _nsd << endl;
      comm->error(msg.str());
    }
  }

  // Setup global element ids (on sides and elements). Doing so, makes the
  // resulting code a little clearer since the local and global ids are the
  // same during this startup phase.
  for (GlobalSize e=0; e<gne; e++) {
    el[e]->gid(el[e]->lid());
    for (LocalSize n=0; n<el[e]->nSides(); ++n) {
      // cout << comm->MyPID() << ": e = " << e << ", side = " << n << endl;
      el[e]->side[n]->geid(el[e]->gid());
    }
  }
  // setup a default partition with all elements on all processors.  This
  // gets distributed and reset in make_partition
  partition.reset( new Partition<GlobalSize,LocalSize,Scalar>(gne,comm) );
  if (action==MINIMAL) return; // Just set the elements, don't allocate or link
  set_side_links(grid);        // make connectivity links
  set_global_side_id();        // make global node, element, and side id's
  set_flip();                  // set side flips
  adjust_side_order();         // adjust side qpts to match
  make_partition(root);        // partition the mesh if parallel
  initialize_bc(root);         // setup boundary sides
  make_storage();              // allocate storage
  compute_geometry();          // make element mappings, Jacobian, mass matrix
  compute_side_geometry();     // make side mapping, Jacobian, normal vectors
#ifdef DGM_ALLOW_HANGING_NODES
  compute_subside_geometry();  // make side mapping, Jacobian, normal vectors
#endif
#ifdef DGM_USE_ELEMENT_BLOCKS
  initialize_element_blocks(); // setup element blocks
#endif
  bndry_stats = new BndryStats(root, this);  // setup bndry statistics
#ifdef DGM_FIELD_VERBOSE
  print_side_links();          // check connectivity
  if (comm->Master()) write_mesh("mesh.dat");
  if (comm->Master()) write_connectivity("connect.dat");
#endif
#ifdef DGM_OUTPUT_DOF          // output the degrees of freedom
  cout<<comm->MyPID()<<":  ne = "<<ne<<", ndof = "<<ndof()<<endl;
#endif
  if (verb>1) comm->cout() << "Finished Field::Field constructor" << endl;
}

/** Copy constructor
    \param[in] F Field to copy
    \param[in] root_ root file name
    \param[in] name_ name of new Field

    \todo Should also do a copy_sides( F, this );
*/
Field::Field(const Field *F, const string &root_, const string &name_)
  : comm(F->comm), BlockSize(F->BlockSize),
    root(root_=="" ? F->root : root_),
    name(name_=="" ? F->name : name_),
    bndry_stats(NULL), verb(F->verb), use_zoltan(F->use_zoltan),
    have_my_bbox(false)
{
  Stopwatch cpu;
  if (verb>1 && comm->Master()) cpu.start();
  if (verb) comm->cout() << "Copy constructing Field " << name
                         << " from " << F->name << endl;
  gne = F->gne;
  ne = F->ne;
  nbc = F->nbc;
  _nsd = F->nsd();
  ndof(F->ndof());
  qtot(F->qtot());
  Qmax = F->Qmax;
  Lmax = F->Lmax;
  if (verb>1) comm->cout() << "  Building " << name << " Field:  gne = "
                           << gne << ", nsd = " << _nsd << endl;
  el.resize(F->ne);
  //cout << "ne = " << ne << endl;
  for (LocalSize e=0; e<ne; e++) el[e] = F->el[e]->clone();
  if (verb>5) comm->cout() << "  Starting set_side_links(F)" << endl;
  set_side_links(F);
  if (verb>5) comm->cout() << "  Finished set_side_links(F)" << endl;
  partition = F->partition;
  make_partition_sides(F);
  initialize_bc(root);
  make_storage();
  copy( F, this, false );    // added to match copy constructor semantics [SSC]
#ifdef DGM_USE_ELEMENT_BLOCKS
  initialize_element_blocks();
#endif
  bndry_stats = new BndryStats( root, this );
  if (verb>1) comm->cout() << "Finished Field copy constructor in "
                           << cpu.stop() << " seconds" << endl;
}

/// Destructor
Field::~Field() {
  if (verb) comm->cout()<<"~Field() for " << name << endl;
  if (verb>4) comm->cout()<<"  Deleting elements"<<endl;
  for (size_t i=0; i<el.size(); ++i) {
    delete el[i];
  }
  for (map<int,Element*>::const_iterator i=ghost_el.begin();
      i!=ghost_el.end(); ++i) {
    delete i->second;
  }
#ifdef DGM_USE_ELEMENT_BLOCKS
  if (verb>4) comm->cout()<<"  Deleting element blocks"<<endl;
  for (size_t i=0; i<eb.size(); ++i) {
    delete eb[i];
  }
#endif
  if (verb>4) comm->cout()<<"  Deleting BC's"<<endl;
  for (size_t i=0; i<bc.size(); ++i) {
    delete bc[i];
  }
  bc.clear();
  bc_types.clear();
  bc_by_type.clear();

  if (verb>4) comm->cout()<<"  Deleting PC's"<<endl;
  // note: in make_partition_sides(Field), sides are created. Calling delete
  // pc[i] does not delete these sides, because Pcon does not have a
  // Destructor function that deletes sides. So I created
  // clear_partition_sides, which deletes the sides and then the Pcon
  // objects. This fixes a memory bug, where we loose access to pointers
  // during parallel runs.  Maybe deleting sides should be in the Pcon
  // destructor? (agerste)
  clear_partition_sides();
  if (bndry_stats) {
    if (verb>4) comm->cout()<<"  Deleting BndryStats"<<endl;
    delete bndry_stats;
  }
  if (verb>2) comm->cout()<<"Completed destroying Field " << name << endl;
}

/// Set the field interior and side storage
/** If DGM_CONTIGUOUS then actually allocate the memory otherwise just compute
    the number of quad pts and modes in field

    \todo The side storage is not optimally set -- should be set like
    you use in convective_flux
*/
void Field::make_storage() {
  //comm->cout() << "Field::make_storage()" << endl;
  _qtot = 0;  // total number of quadtrature points in field
  for (size_t e=0; e<el.size(); e++) {
    _qtot += el[e]->qtot;
    //cout << "e = " << e << " el[e]->qtot = " << el[e]->qtot << " _qtot = "
    //     << _qtot << endl;
  }
  _ndof = 0;  // total number of modes in field
  for (size_t e=0; e<el.size(); e++) _ndof += el[e]->nModes();
  _sdof = 0;  // total side degrees of freedom
  for (size_t e=0; e<el.size(); e++) {
    for (Ordinal i=0; i<el[e]->nSides(); i++) {
      _sdof += el[e]->side[i]->qtot();
      if (!el[e]->side[i]->subsides().empty()){
        for (size_t j=0; j<el[e]->side[i]->subsides().size();j++) {
          _sdof += el[e]->side[i]->subsides()[j]->qtot();
        }
      }
    }
  }
  // interior storage
#ifdef DGM_CONTIGUOUS
  elmt_data.resize(qtot());   // contiguous storage for physical space storage
  Ordinal start = 0;
  for (size_t e=0; e<el.size(); e++) { // set the element storage
    el[e]->u.alias( elmt_data, start, el[e]->qtot );
    el[e]->uh.alias( el[e]->u, el[e]->nModes() );
    el[e]->state = Element::Undefined;
    start += el[e]->qtot;
  }
  // side storage
  side_data.resize(sdof());     // contiguous side storage
  side_data = 0;
  start = 0;
  for (size_t e=0; e<el.size(); e++) {// set the side storage
    const Element *E = el[e];
    for (SideLoop S(E); !S.end(); ++S) {
      if (S.master_side()) {
        if (S.side(E)->elink) {
          Side *l = S.side(E);
          l->u.alias( side_data, start, l->qtot() );
          start += l->qtot();
        }
        if (S.link(E)->elink != S.link(E)->elink) {
          Side *r = S.link(E);
          r->u.alias( side_data, start, r->qtot() );
          start += r->qtot();
        }
      }
    }
  }
  const Scalar *begin = side_data.begin();
  const Scalar *end   = side_data.end();
  for (size_t e=0; e<el.size(); e++) { // set the side storage
    const Element *E = el[e];
    for (Ordinal i=0; i<E->nSides(); i++) {
      Side *S = E->side[i];
      const Scalar *u = S->u.data();
      // So, if the address was set in the above loop then
      // side_data.begin() <= u < side_data.end()
      // otherwise we should probably set it.
      if (u < begin || end <= u) {
        S->u.alias( side_data, start, S->qtot() );
        start += S->qtot();
      }
      for (size_t j=0; j<S->subsides().size();j++) {
        Side::Ptr SS = S->subsides()[j];
        const Scalar *u = SS->u.data();
        if (u < begin || end <= u) {
          SS->u.alias( side_data, start, SS->qtot() );
          start += SS->qtot();
        }
      }
    }
  }
  if (start != sdof())
    throw DGM::exception("Error in setting side storage.");
#endif
  elmt_data = 0;
}

/// Reset the field interior and side storage to be contiguous
void Field::reset_storage( dVector &eld, dVector &sld ) {
  // cout << "Field::reset_storage()" << endl;
  // interior storage
  elmt_data.alias(eld, qtot());
  // cout << "reset Field elmt storage" << endl;
  elmt_data = 0;
  Ordinal start = 0;
  for (LocalSize e=0; e<ne; e++) {  // set the element storage
    el[e]->u.alias( elmt_data, start, el[e]->qtot );
    el[e]->uh.alias( el[e]->u, el[e]->nModes() );
    el[e]->state = Element::Undefined;
    start += el[e]->qtot;
  }
  // side storage
  side_data.alias(sld, sdof());     // contiguous side storage
  // cout << "reset Field side storage" << endl;
  side_data = 0;
  start = 0;
  for (LocalSize e=0; e<ne; e++) {  // set the side storage
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      el[e]->side[i]->u.alias( side_data, start, el[e]->side[i]->qtot() );
      start += el[e]->side[i]->qtot();
    }
  }
#ifdef DGM_USE_ELEMENT_BLOCKS
  for (vector<ElementBlock*>::const_iterator i=eb.begin(); eb.end()!=i; ++i)
    delete *i;
  eb.clear();
  initialize_element_blocks();
#endif
}

/// Set global ids for all the sides (ASCII mesh files)
void Field::set_global_side_id() {
  // comm->cout() << "Field::set_global_side_id()" << endl;
  GlobalSize gid = 0;
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];
      if ( Side::undefined(side->gid()) ) {
        if ( side->base ) {
          side->gid(gid);
          if ( side->link ) side->link->gid(gid);
          ++gid;
        }
      }
    }
  }
}

/// Partition a Field for parallel execution
void Field::make_partition(const string &root) {
  //comm->cout() << "Field::make_partition" << endl;
  if ( (GlobalSize)comm->NumProc() > gne)
    comm->error("Field: Number of processors exceeds numbers of elements");
  partition.reset( new Partition<GlobalSize,LocalSize,Scalar>(gne,root,comm) );
#ifdef DGM_PARALLEL
  partition->connectivity(el, use_zoltan);
  set_flip();
  vector<Element*> loc_el;
  partition->reset_side_links(el, loc_el, pc);
  if (loc_el.size() >= (size_t)numeric_limits<LocalSize>::max())
    throw DGM::exception("Local element size overflows local element storage\n"
                         "Run on more MPI ranks.");
  ne = (LocalSize)loc_el.size();
  el = loc_el;
#else
  set_flip();
  partition->setup_local_id_array();
#endif
}

/// Partition a Field for parallel execution
void Field::make_partition() {
#ifdef DGM_PARALLEL
  partition->connectivity_pc(el, use_zoltan);
  set_flip(true);
  partition->reset_side_links(el, pc, use_zoltan);
#else
  set_flip();
  partition->setup_local_id_array();
#endif
}

/// Adjust for side quadrature order to support variable order elements
/** It is important to make sure that the element Qmax, Lmax are sufficient
 *  to hold that of any neighboring side.  While this is usually the case,
 *  when you have a low-order element right next to a very high-order element
 *  and there is a parallel partition between the two, then this case cause
 *  trouble.  That is why we update the element workspace and the Field Qmax
 *  just to be safe.
*/
void Field::adjust_side_order() {
  // cout << "Field::adjust_side_order()" << endl;
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *s = el[e]->side[i];
      if (s->link) {             // on master side
        Side *master = s;
        Side *slave  = s->link;
        master->match(slave);
        el[e]->update_workspace(master->qtot());
        if (master->qtot()>Qmax) Qmax = master->qtot();
      } else if (!s->subsides().empty()) {
        for (unsigned j=0; j<s->subsides().size();j++) {
          Side *slave  = s->subsides()[j].get();
          Side *master = s->subsides()[j]->base;
          master->match(slave);
          el[e]->update_workspace(master->qtot());
          if (master->qtot()>Qmax) Qmax = master->qtot();
        }
      }
    }
  }
}

/// Computes geometry objects 
/** (curves sides, coordinates, normals, Mass matrix) */
void Field::compute_geometry() {
  for (size_t e=0; e<el.size(); e++) {
    el[e]->generate_curve();
    el[e]->get_coordinates();
    el[e]->compute_geometry();
    el[e]->get_mass_matrix();
  }
}

/// Computes geometry objects 
/** (curves sides, coordinates, normals, Mass matrix) */
void Field::compute_geometry(const std::map<int,Element*> &elements) {
  for (map<int,Element*>::const_iterator e=elements.begin();
      e!=elements.end(); e++) {
    e->second->generate_curve();
    e->second->get_coordinates();
    e->second->compute_geometry();
    e->second->get_mass_matrix();
  }
}

/// Compute the geometry for the sides of each Element
void Field::compute_side_geometry() {
  const map<pair<Ordinal,Ordinal>, bool> GLLs =
    communicate_integration_type (el, partition, comm);
  for (size_t e=0; e<el.size(); e++) {
    for (Ordinal i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];
      if (!partition->owns(side->geid())) {
        pair<Ordinal,Ordinal> key(numeric_cast<Ordinal>(e),i);
        if (!GLLs.count(key)) {
          stringstream msg;
          msg<<"Attempting to set up side communication classes:" <<endl
             << " and could not determine type of Side integration rule "
             << "(GLL or GL) across processor boundary."<<endl
             << "   On processor:"<<comm->MyPID()<<" for element:"<<e
             << " side:"<<side<<"  "<<__FILE__<<":"<<__LINE__<<endl;
          comm->error(msg.str());
        }
        const bool GLL = GLLs.find(key)->second;
        side->Gauss_Lobatto(GLL);
      }
    }
  }
  for (size_t e=0; e<el.size(); e++) el[e]->compute_side_geometry();
}

/// Compute the geometry for the subsides of each Element
void Field::compute_subside_geometry() {
#ifdef DGM_ALLOW_HANGING_NODES
  unsigned local_has_subsides = 0;
  for (size_t e=0; e<el.size() && !local_has_subsides; e++) {
    const Element *g = el[e];
    for (Ordinal i=0; i<g->nSides() && !local_has_subsides; i++) {
      const Side *t = g->side[i];
      if (!t->subsides().empty()) local_has_subsides = 1;
    }
  }
  unsigned global_has_subsides = 0;
  comm->SumAll(&local_has_subsides, &global_has_subsides, 1);
  if (global_has_subsides) {
    const side_coord_map coord_map = Field::share_side_coord();
    for (size_t e=0; e<el.size(); e++) {
      const Element *g = el[e];
      for (Ordinal ns=0; ns<g->nSides(); ns++) {
        const Side *t = g->side[ns];
        for (size_t ss=0; ss<t->subsides().size(); ++ss) {
          Side *s = t->subsides()[ss].get();
          if (s->base) {
            const GlobalSize eid = s->base->leid();
            const LocalSize j = s->base->id();
            const Element *f = el[eid];
            const Side *n = f->side[j];
            const LocalSize sj = s->J().size();
            g->compute_subside_geometry(s,*f);
            if (n->J().size()      != sj) error(__FILE__" Size mismatch.");
            if (n->J_orig().size() != sj) error(__FILE__" Size mismatch.");
            s->J_orig().resize(sj);

            s->nx()=n->nx(); s->ny()=n->ny(); s->nz()=n->nz();
            s->nx() *= -1; s->ny() *= -1; s->nz() *= -1;

            dVector Jac_scale(sj);
            s->push_to_subside(t->J_scale(), Jac_scale);
            s->J() = n->J_orig();
            for (Ordinal i=0; i<sj;++i) s->J_orig(i) = s->J(i)/Jac_scale[i];
          } else {
            const LocalSize sj = s->J().size();
            const key k(e,pair<Ordinal,Size>(ns,s->gid()));
            side_coord_map::const_iterator c = coord_map.find(k);
            if (c == coord_map.end()) comm->error("key not found.");
            const value v = c->second;
            const Scalar J = g->compute_subside_geometry(s,v);
            g->push_side_geom_to_subside(s, t, J);
            s->J() =  s->J_orig();
            for (Ordinal i=0; i<sj;++i) s->J_orig(i) = s->J(i)/s->J_scale(i);
          }
        }
      }
    }
    Field::share_normals();
  }
#endif
}

/// Compute the geometry for the sides of each Element
void Field::compute_side_geometry(const map<int,Element*> &elements) {
  for (map<int,Element*>::const_iterator e=elements.begin();
      e!=elements.end(); e++) {
    e->second->compute_side_geometry();
  }
}

#ifdef DGM_USE_ELEMENT_BLOCKS

namespace {

/// Count the blocks of various sizes on this processor.
vector<unsigned> local_count(const vector<ElementBlock*> &eb) {
  map<unsigned, unsigned> c;
  for (vector<ElementBlock*>::const_iterator i=eb.begin(); eb.end()!=i; ++i) {
    ++c[(*i)->eb.size()];
  }
  vector<unsigned> r;
  for (map<unsigned,unsigned>::const_iterator i=c.begin(); c.end()!=i; ++i) {
    r.push_back(i->first);
    r.push_back(i->second);
  }
  return r;
}

unsigned integrate(vector<int> &d, const vector<unsigned> &r) {
  d.resize(r.size());
  for (size_t j=0; d.size()!=j+1 && d.size()!=j; ++j) {
    d[j+1] = d[j]+r[j];
  }
  return d.back() + r.back();
}

map<unsigned,unsigned> reduce_counts(const vector<unsigned> &c) {
  map<unsigned, unsigned> t;
  for (vector<unsigned>::const_iterator i=c.begin(); c.end()!=i; i+=2) {
    t[*i] += *(i+1);
  }
  return t;
}

void print_report(const map<unsigned,unsigned> &t) {
  cout <<"  Element Block Report           "<<endl;
  cout <<"  ------------------------------ "<<endl;
  cout <<"   Elements        Number of"<<endl;
  cout <<"   In Block    Blocks This Size "<<endl;
  for (map<unsigned,unsigned>::const_iterator i=t.begin(); t.end()!=i; ++i) {
    cout <<"  "<<setw(5)<<i->first<<"       "<<setw(10)<<i->second<<endl;
  }
  cout <<"  ------------------------------ "<<endl;
}

void print_element_block_report(const DGM::Comm::Ptr comm,
                                const vector<ElementBlock*> &eb) {
  static bool print_once=false;
  if (print_once) return;
  print_once = true;
  vector<unsigned> local = local_count(eb);
  vector<unsigned> r(comm->NumProc(),0);
  unsigned size = local.size();
  comm->Gather(&size, 1, &r[0], r.size());
  vector<int> displs;
  const unsigned buf_len = integrate(displs, r);
  vector<unsigned> recvbuf(buf_len);
  vector<int> rc;
  for (vector<unsigned>::const_iterator i=r.begin(); r.end()!=i; ++i)
    rc.push_back(*i);
  comm->GatherV(&local[0], local.size(), &recvbuf[0], &rc[0], &displs[0]);
  map<unsigned,unsigned> totals = reduce_counts(recvbuf);
  if (!comm->MyPID()) print_report(totals);
}

}  // end namespace

/// Fills in the element block vector with homogeneous element blocks.
/** \todo Needs to support other element types besides Quad and Hex. */
void Field::initialize_element_blocks() {
  const vector<Element*>::const_iterator end=el.end();
  vector<Element*>::const_iterator i=el.begin();
  for (; i != end; ++i) {
    // Will need to iterate types here.
    if (2==_nsd && 4==(*i)->nVerts()) {
      if (eb.empty() || !eb.back()->push_back(*i)) {
        eb.push_back(new QuadBlock(*i, BlockSize));
      }
    } else if (3==_nsd && 8==(*i)->nVerts()) {
      if (eb.empty() || !eb.back()->push_back(*i)) {
        eb.push_back(new HexBlock(*i, BlockSize));
      }
    }
  }
#if defined(DGM_USE_CUDA) || defined(DGM_USE_KOKKOS)
  eb.front()->initialize_gpu();
#endif // DGM_USE_CUDA or DGM_USE_KOKKOS
  print_element_block_report(get_comm(), eb);
}

#endif // DGM_USE_ELEMENT_BLOCKS

#ifdef DGM_ALLOW_HANGING_NODES

namespace {

Field::MultiSideSet find_subsides(ifstream &in) {
  Field::MultiSideSet multisides;
  Field::MultiSideSet links;
  string buffer;
  char type;
  GlobalSize eid, leid;
  LocalSize sid, lsid;
  getline(in,buffer);
  getline(in,buffer);
  while (in >> type >> eid >> sid >> leid >> lsid) {
    getline(in,buffer);
    pair<GlobalSize,LocalSize> link(eid,sid);
    if (links.count(link)) {
      multisides.insert(link);
    } else {
      links.insert(link);
    }
  }
  return multisides;
}

} // anonymous namespace

#endif

/// Read the connectivity file
void Field::read_connectivity(ifstream &in, const MultiSideSet &multisides) {
  string buffer;
  char type;
  LocalSize sid, lsid;
  GlobalSize eid, leid;
  getline(in,buffer);
  getline(in,buffer);
  while (in >> type >> eid >> sid >> leid >> lsid) {
    //comm->cout()<<type<<","<<eid<<","<<sid<<","<<leid<<","<<lsid<<endl;
    getline(in,buffer);
    if ( Side::defined(leid) ) {
      // check to see if the opposite link is already set
#ifdef DGM_ALLOW_HANGING_NODES
      if (multisides.count( MultiSidePair(eid,sid) ) ) {
        Side *this_side = el[eid]->side[sid];
        Side *nbr_side  = el[leid]->side[lsid];
        Side::Ptr sub_side(nbr_side->deep_copy());
        sub_side->id( this_side->id() );
        if (1 == sub_side->q1() || 1 != sub_side->q2()) {
          sub_side->q1( this_side->q1() );
          sub_side->q2( this_side->q2() );
        } else {
          sub_side->q1(this_side->q1()*(2*this_side->q1()+1));
          sub_side->Gauss_Lobatto(this_side->Gauss_Lobatto());
        }
        sub_side->elink = this_side->elink;
        sub_side->gid( this_side->gid() );
        this_side->geid( el[eid]->gid() );
        sub_side ->geid( el[eid]->gid() );
        nbr_side ->geid( el[leid]->gid() );

        sub_side->link  = 0;              // sub is slave
        sub_side->base  = nbr_side;       // link to neighbor
        nbr_side->link  = sub_side.get(); // neighbor is master
        nbr_side->base  = nbr_side;       // link to self
        this_side->link = 0;              // not master
        this_side->base = 0;              // like a boundary

        this_side->subsides().push_back(sub_side);
      } else if (multisides.count( MultiSidePair(leid,lsid) ) ) {
        // do nothing, wait for the reverse link to set the links.
      } else
#endif
      {
        if ( const Side *llink = el[leid]->side[lsid]->link ) {
          // if so, make sure that the links match, otherwise error
#ifndef DGM_FIELD_NO_CHECK_SIDE_LINKS
          // Turn this off in order to allow for internal periodicity
          // WARNING:  this has not be fully tested
          if ( llink != el[eid]->side[sid] ) {
            stringstream msg;
            msg << "Contradictory side links: Eid " <<eid<<", sid "<<sid
                << ", leid "<<leid<<", lsid "<<lsid<<endl;
            comm->error(msg.str());
          }
#endif
        } else {
          Side *this_side = el[eid]->side[sid];
          Side *nbr_side  = el[leid]->side[lsid];
          this_side->link = nbr_side;              // this is master
          this_side->base = this_side;             // link to self
          nbr_side ->link = 0;                     // neighbor is slave
          nbr_side ->base = this_side;             // link to master
          this_side->geid( el[eid]->gid() );
          nbr_side ->geid( el[leid]->gid() );
        }
      }
#ifdef DGM_USE_GENERAL_GHOSTING
      if (el[eid]->adj_els.empty()) {
        el[eid]->adj_els.resize(el[eid]->side.size(),-1);
      }
      el[eid]->adj_els[sid] = leid;
#endif
    } else {
      throw DGM::exception("Undefined element in connectivity");
    }
  }
  //comm->cout()<<"Finished read_connectivity()"<<endl;
}

#if defined(DGM_USE_EPETRA) && defined(DGM_USE_GENERAL_GHOSTING)

/// Reconnect sides for element facing ghost elements based on element
/// neighbors
void Field::reset_side_links() {
  for (LocalSize e=0; e<ne; e++) {
    const Element *const ele = el[e]; // ele is a row element
    assert(ele->adjacent_elements().size() == (size_t)ele->nSides()); // debug
    for (Ordinal i=0; i<ele->nSides(); i++) {
      Side *const Us_loc = ele->side[i];
      if (!Us_loc->is_bc()) {
        const Size neighbor_ele_gid = ele->adjacent_elements()[i];
        assert(neighbor_ele_gid != Element::invalid_ele_neighbor);
        if (GhostElementExists(neighbor_ele_gid)) { // if neighbor is ghost elem
          Element *const nele = GetGhostElement(neighbor_ele_gid);
          int inside = -1;
          for (Ordinal in=0; in != nele->nSides(); in++) {
            if (nele->adjacent_elements()[in] == ele->gid()) {
              inside = in;
              break;
            }
          }
          assert(inside != -1);
          // nele must be a ghost element
          assert(!ele_rmap->MyGID(static_cast<int>(nele->gid())));
          // comm->cerr() << "Found row element with overlapping "
          //                 "element as neighbor"<<endl;
          Us_loc->link = nele->side[inside];
          Us_loc->base = ele->side[i];
          nele->side[inside]->link = 0;
          nele->side[inside]->base = ele->side[i];
          assert(nele->side[inside]->elink != NULL);
        }
      }
    }     // loop over sides
  }       // loop over row elements
}

#endif  // DGM_USE_EPETRA && DGM_USE_GENERAL_GHOSTING

/// Write the side connectivity file
/** \todo Update to use a stream. */
void Field::write_connectivity(const string &fname) const {
  // cout << "Field::write_connectivity" << endl;
#if 0
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"# CONNECTIVITY DATA\n");
  fprintf(fp,"%lu ne\n",el.size());
  for (size_t n=0; n<el.size(); n++) el[n]->write_connectivity(fp);
  fclose(fp);
#else
  ofstream f(fname.c_str());
  f << "# CONNECTIVITY DATA\n";
  f << el.size() << " ne\n";
  for (size_t n=0; n<el.size(); n++) el[n]->write_connectivity(f);
#endif
}

/// Write the node connectivity file
void Field::write_node_connectivity(const string &fname) const {
  // cout << "Field::write_node_connectivity" << endl;
  ofstream f(fname.c_str());
  f << "# NODE CONNECTIVITY DATA\n";
  f << el.size() << " ne\n";
  for (size_t n=0; n<el.size(); n++) el[n]->write_node_connectivity(f);
}

/// read mesh information to treat the DG mesh as Continuous Galerkin (CG) mesh
/** Read the connectivity file (if present).
    This assumes that an element already exists and that the input file
    contains one line for every element with the format:
    # Comment                                                        line 1
      NumEle                                                     ,-- line 2
      NumNodePerElement  NodeGID1  NodeGID2  NodeGID3  NodeGID4  ...
      NumNodePerElement  NodeGID1  NodeGID2  NodeGID3  NodeGID4  ...
      NumNodePerElement  NodeGID1  NodeGID2  NodeGID3  NodeGID4  ...
*/
void Field::read_node_connectivity(const string &root, const string &ext) {
  //comm->Barrier();
  if (verb>2) comm->cout() << "  read_node_connectivity()" << endl;
  const string fname = root+ext;
  ifstream f(fname.c_str());
  if ( f.is_open() ) {
    comm->cout() << "  Reading the element-node connectivity file: "
                 << fname << endl;
    string buffer;
    // ignore the first line
    getline(f, buffer);
    // read number of elements
    GlobalSize num_elem;
    f >> num_elem;
    if (num_elem != gne)
      comm->error("Field: Illegal number of elements in connectivity file");
    // Grabs the rest of the line
    getline(f, buffer);
    // loop over the elements
    for (GlobalSize e=0; e<gne; ++e) {
      getline(f,buffer);
      istringstream ist(buffer);
      // read number of nodes to follow
      LocalSize nn; ist >> nn;
      for (LocalSize n = 0; n < nn; ++n) {
        GlobalSize GID; ist >> GID;
        el[e]->vert[n]->gid = GID;
      }
    }
  }
  //comm->Barrier();
  if (verb>2) comm->cout() << "  Finished read_node_connectivity()" << endl;
}

/// set vertex gids of each element
void Field::set_vertex_gid(vector<vector<int> > &nglob) {
  // cout << "Field::set_vertex_gid" << endl;
  for (LocalSize e = 0; e < ne; ++e) {
    for (LocalSize inode = 0; inode < el[e]->nVerts(); ++inode) {
      el[e]->vert[inode]->gid = nglob[e][inode];
    }
  }
}

/// Set the Side links based on connectivity file
void Field::set_side_links(const string &root) {
  LocalSize e = 0;
  if (root != "") {
    string fname = root+".con";
    ifstream fp(fname.c_str());
    if (fp) {
#ifdef DGM_ALLOW_HANGING_NODES
      const MultiSideSet multisides = find_subsides(fp);
      fp.close();
      fp.open(fname.c_str());
#else
      const MultiSideSet multisides;
#endif
      read_connectivity(fp, multisides);
    } else
      comm->error("Field::set_side_links -- Couldn't open connectivity file");
  } else {
    if (_nsd==1) {   // Hardwired for 1-d problems, from left to right
      e = 0;
      if (ne==1) {
        el[e]->side[0]->link = 0;
        el[e]->side[0]->base = 0;
        el[e]->side[1]->link = 0;
        el[e]->side[1]->base = 0;
        return;
      }
      el[e]->side[0]->link = 0;
      el[e]->side[0]->base = 0;
      el[e]->side[1]->link = el[e+1]->side[0];
      el[e]->side[1]->base = el[e]->side[1];
      for (e=1; e<ne-1; e++) {
        el[e]->side[0]->base = el[e-1]->side[1];
        el[e]->side[1]->link = el[e+1]->side[0];
        el[e]->side[1]->base = el[e]->side[1];
      }
      e = ne-1;
      el[e]->side[0]->base = el[e-1]->side[1];
      el[e]->side[1]->link = 0;
      el[e]->side[1]->base = 0;
    } else {
      stringstream msg;
      msg << "Field::set_side_links -- Illegal value of nsd = " <<_nsd<<endl;
      comm->error(msg.str());
    }
  }
}

/// Set links based on internal mesh object
void Field::set_side_links(const Mesh &grid) {
  for (size_t n=0; n<grid.con.size(); n++) {
    const Mesh::GlobalSize &eid = grid.con[n].eid;
    const Mesh::LocalSize &side = grid.con[n].side;
    const Mesh::GlobalSize &leid = grid.con[n].leid;
    const Mesh::LocalSize &lside = grid.con[n].lside;
    // check to see if the opposite link is already set
    if ( const Side *slink = el[leid]->side[lside]->link ) {
      // if so, make sure that the links match, otherwise error
      if ( slink != el[eid]->side[side] ) {
        stringstream msg;
        msg << "Contradictory side links: Eid " <<eid<<", side "<<side
            << ", lEid "<<leid<<", lside "<<lside
              <<"   "<<__FILE__<<":"<<__LINE__<<endl;
        comm->error(msg.str());
      }
      // just set the base if the other link is valid
      el[eid]->side[side]->base = el[leid]->side[lside];
      el[leid]->side[lside]->base = el[leid]->side[lside];
    } else {
      el[eid]->side[side]->link = el[leid]->side[lside];
      // WARNING:  should this be set?
      // el[eid]->side[side]->base = el[eid]->side[side];
    }
  }
}

/// Set links based on an existing field
void Field::set_side_links(const Field *F) {
  Size leid;
  LocalSize lside;
  if ( ne != F->ne )
    comm->error("Field::set_side_links -- number of elements mismatch");
  // loop over elements
  for (LocalSize e=0; e<ne; e++) {
    if ( el[e]->nSides() != F->el[e]->nSides() )
      comm->error("Field::set_side_links -- number of sides mismatch");
    // loop over sides
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];               // shorthand
      if ( side->base ) {                        // not a boundary side
        if (side->link) {                        // master
          leid = side->link->leid();
          lside = side->link->id();
          // Careful not to overwrite subside's neighbors links.  Subside
          // vectors has not been set up yet (see the next loop over
          // subsides), but the conversion matrixies have been copied when the
          // field was created, so check for a non-zero conversion matrix
          // size.
          const bool subside = side->link->has_subsides();
          side->base = side;
          if (!subside) side->link = el[leid]->side[lside];
        } else {                               // slave
          leid = side->base->leid();
          lside = side->base->id();
          side->base = el[leid]->side[lside];
          side->link = 0;
        }
      }
      for (unsigned s=0; s<side->subsides().size(); ++s) {
        Side *sub_side  = side->subsides()[s].get();
        if (sub_side->link) {            // communication side
          Side *nbr_side       = sub_side->link->clone(); // slave side;
          sub_side->link       = nbr_side;
          nbr_side->geid       ( sub_side->geid());
          nbr_side->id         ( sub_side->id());
          sub_side->base       = 0;
          nbr_side->link       = 0;
          nbr_side->base       = nbr_side;
          side->base = 0;
          side->link = side->clone();
          nbr_side->u.resize(sub_side->link->qtot()); // slave side;
          side->link->u.resize(side->qtot());
          nbr_side->u = 0;
          side->link->u = 0;
        } else {
          leid            = sub_side->base->leid();
          lside           = sub_side->base->id();
          Side *nbr_side  = el[leid]->side[lside];
          sub_side->link  =             0; // slave side;
          sub_side->base  =      nbr_side; // link to master;
          nbr_side->link  =      sub_side; // master side;
          nbr_side->base  =      nbr_side; // link to self;
        }
      }
    }
  }
}

#ifdef DGM_PARALLEL

namespace {

LocalSize pack_unpack_buffer(Pcon<GlobalSize,LocalSize,Scalar> &pc,
                             Side *side,
                             LocalSize sdof,
                             const LocalSize cprocid,
                             const DGM::Comm::Ptr comm,
                             const bool link_is_subside,
                             const bool this_subside,
                             const Buf_Operation op) {
  const Ordinal nx_size = side->nx().size();
  const Ordinal ny_size = side->ny().size();
  const Ordinal nz_size = side->nz().size();
  switch (op) {
    case COUNT : pc.len += (nx_size + ny_size + nz_size);  break;
    case PACK :
      for (Ordinal k=0; k<nx_size; ++k) pc.buf[sdof++]=side->nx()[k];
      for (Ordinal k=0; k<ny_size; ++k) pc.buf[sdof++]=side->ny()[k];
      for (Ordinal k=0; k<nz_size; ++k) pc.buf[sdof++]=side->nz()[k];
      break;
    case UNPACK :
      if (this_subside) {
        for (Ordinal k=0; k<nx_size; ++k) side->nx()[k] = -pc.buf[sdof++];
        for (Ordinal k=0; k<ny_size; ++k) side->ny()[k] = -pc.buf[sdof++];
        for (Ordinal k=0; k<nz_size; ++k) side->nz()[k] = -pc.buf[sdof++];
      } else if (link_is_subside) {
        sdof += (nx_size + ny_size + nz_size);
      } else if (side->link->geid() < side->geid()) {//I'm slave
        for (Ordinal k=0; k<nx_size; ++k) side->nx()[k] = -pc.buf[sdof++];
        for (Ordinal k=0; k<ny_size; ++k) side->ny()[k] = -pc.buf[sdof++];
        for (Ordinal k=0; k<nz_size; ++k) side->nz()[k] = -pc.buf[sdof++];
      } else {
        sdof += (nx_size + ny_size + nz_size);
      }
      break;
  }
  return sdof;
}

void pack_unpack_buffer(
  vector<Pcon<GlobalSize,LocalSize,Scalar> > &pc,
  vector<Element*> &el,
  const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition,
  const DGM::Comm::Ptr comm,
  const vector<Pcon<GlobalSize,LocalSize,Scalar> > &link_ss,
  const Buf_Operation op) {
  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    LocalSize sdof = 0;
    const Connect<GlobalSize,LocalSize> &cinfo = partition->cinfo[n];
    const LocalSize cprocid = cinfo.cprocid;
    for (LocalSize i=0; i<cinfo.nsides; i++) {
      const bool lnk_ss = link_ss[n].buf[i];
      const Link<GlobalSize,LocalSize> &link  = cinfo.links[i];
      const GlobalSize elmtid  = link.elmtid;
      const LocalSize sideid  = link.sideid;
      const GlobalSize sidegid = link.sidegid;
      Side *side = el[elmtid]->side[sideid];
      if (side->subsides().empty()) {
        sdof = pack_unpack_buffer(pc[n], side, sdof, cprocid,
                                  comm, lnk_ss, false, op);
      } else {
        for (size_t s=0; s<side->subsides().size(); ++s) {
          Side *ss = side->subsides()[s].get();
          if (ss->gid() == sidegid) {
            sdof = pack_unpack_buffer(pc[n], ss, sdof, cprocid,
                                      comm, lnk_ss, true, op);
            break;
          }
        }
      }
    }
  }
}

void communicate_flags
(vector<Pcon<GlobalSize,LocalSize,Scalar> > &pc,
 const vector<Element*> &el,
 const Partition<GlobalSize,LocalSize,Scalar>::Ptr partition,
 const DGM::Comm::Ptr comm) {
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    const Connect<GlobalSize,LocalSize> &cinfo = partition->cinfo[n];
    pc[n].len = cinfo.nsides;
    pc[n].buf.resize(pc[n].len);
    for (LocalSize i=0; i<cinfo.nsides; i++) {
      const Link<GlobalSize,LocalSize> &link  = cinfo.links[i];
      Side *side = el[link.elmtid]->side[link.sideid];
      pc[n].buf[i] = !side->subsides().empty();
    }
  }
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    comm->SendReceiveReplace(
        pc[n].buf.data(),
        CMC::castInt(pc[n].len),
        CMC::castInt(partition->cinfo[n].cprocid),
        CMC::castInt(partition->cinfo[n].cprocid),
        CMC::castInt(partition->cinfo[n].cprocid),
        comm->MyPID() );
  }
}

} // anonymous namepace

#endif

/// Parallel communication (the send_receive approach is the best!)
void Field::share_normals() {
#ifdef DGM_PARALLEL
  vector<Pcon<GlobalSize,LocalSize,Scalar> > subsides(partition->ncprocs());
  communicate_flags(subsides, el, partition, comm);

  vector<Pcon<GlobalSize,LocalSize,Scalar> > pc(partition->ncprocs());
  pack_unpack_buffer(pc, el, partition, comm, subsides, COUNT);
  for (LocalSize n=0; n<partition->ncprocs(); n++) pc[n].buf.resize(pc[n].len);

  pack_unpack_buffer(pc, el, partition, comm, subsides, PACK);
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    comm->SendReceiveReplace( pc[n].buf.data(),
        pc[n].len,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        comm->MyPID() );
  }
  pack_unpack_buffer(pc, el, partition, comm, subsides, UNPACK);

  for (size_t e=0; e<el.size(); e++) {
    const Element *g = el[e];
    for (LocalSize i=0; i<g->nSides(); i++) {
      Side *t = g->side[i];
      if (!t->master() && t->base) {
        t->nx().resize(t->base->nx()).Zero().Sub(t->base->nx());
        t->ny().resize(t->base->ny()).Zero().Sub(t->base->ny());
        t->nz().resize(t->base->nz()).Zero().Sub(t->base->nz());
      }
      for (size_t ss=0; ss<t->subsides().size(); ++ss) {
        Side *s  = t->subsides()[ss].get();
        if (!s->master() && s->base) {
          s->nx().resize(s->base->nx()).Zero().Sub(s->base->nx());
          s->ny().resize(s->base->ny()).Zero().Sub(s->base->ny());
          s->nz().resize(s->base->nz()).Zero().Sub(s->base->nz());
        }
      }
    }
  }
#endif  // DGM_PARALLEL
  return;
}

/// Parallel communication (the send_receive approach is the best!)
Field::side_coord_map Field::share_side_coord() const {
  side_coord_map side_coords;
#ifdef DGM_PARALLEL
#ifdef DGM_ALLOW_HANGING_NODES
  // Fill buffer and send side information to neighbors
  vector<Pcon<GlobalSize,LocalSize,Scalar> > pn(partition->ncprocs());
  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    const unsigned l = partition->cinfo[n].nsides;
    pn[n].len      = l;
    pn[n].buf.resize(l);
    for (unsigned i=0; i<l; ++i) {
      const int elmtid = partition->cinfo[n].links[i].elmtid;
      const int sideid = partition->cinfo[n].links[i].sideid;
      pn[n].buf[i] = el[elmtid]->get_side_endpoints(sideid).size();
    }
  }
  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    comm->SendReceiveReplace( pn[n].buf.data(),
        pn[n].len,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        comm->MyPID() );
  }

  vector<Pcon<GlobalSize,LocalSize,Scalar> > pc(partition->ncprocs());
  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    unsigned sdof=0;
    const unsigned l = partition->cinfo[n].nsides;
    for (unsigned i=0; i<l; ++i) {
      const int elmtid = partition->cinfo[n].links[i].elmtid;
      const int sideid = partition->cinfo[n].links[i].sideid;
      const unsigned llen = el[elmtid]->get_side_endpoints(sideid).size();
      const unsigned rlen = static_cast<unsigned>(0.5+pn[n].buf[i]);
      sdof += std::max(llen, rlen);
    }
    pc[n].len      = 3*sdof;
    pc[n].buf.resize(3*sdof);
  }

  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    unsigned sdof = 0;
    const unsigned l = partition->cinfo[n].nsides;
    for (unsigned i=0; i<l; i++) {
      const int elmtid = partition->cinfo[n].links[i].elmtid;
      const int sideid = partition->cinfo[n].links[i].sideid;
      const vector<Point> p=el[elmtid]->get_side_endpoints(sideid);
      for (unsigned j=0; j!=p.size(); ++j) {
        pc[n].buf[sdof++] = p[j].x;
        pc[n].buf[sdof++] = p[j].y;
        pc[n].buf[sdof++] = p[j].z;
      }
      const unsigned rlen = static_cast<unsigned>(0.5+pn[n].buf[i]);
      for (unsigned j=p.size(); j<rlen; ++j) {
        pc[n].buf[sdof++] = std::numeric_limits<Scalar>::max();
        pc[n].buf[sdof++] = std::numeric_limits<Scalar>::max();
        pc[n].buf[sdof++] = std::numeric_limits<Scalar>::max();
      }
    }
    comm->SendReceiveReplace( pc[n].buf.data(),
        pc[n].len,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        partition->cinfo[n].cprocid,
        comm->MyPID() );
  }

  for (Ordinal n=0; n<partition->ncprocs(); n++) {
    unsigned sdof = 0;
    const unsigned l = partition->cinfo[n].nsides;
    for (unsigned i=0; i<l; i++) {
      const int elmtid = partition->cinfo[n].links[i].elmtid;
      const int sideid = partition->cinfo[n].links[i].sideid;
      const unsigned llen = el[elmtid]->get_side_endpoints(sideid).size();
      const unsigned rlen = static_cast<unsigned>(0.5+pn[n].buf[i]);
      value P;
      for (unsigned j=0; j<rlen; ++j) {
        value::value_type p;
        p.x = pc[n].buf[sdof++];
        p.y = pc[n].buf[sdof++];
        p.z = pc[n].buf[sdof++];
        P.push_back(p);
      }
      for (unsigned j=rlen; j<llen; ++j) sdof += 3;
      const int sidegid= partition->cinfo[n].links[i].sidegid;
      const key k(elmtid,pair<int,int>(sideid,sidegid));
      side_coords[k] = P;
    }
  }
#endif  // DGM_ALLOW_HANGING_NODES
#endif  // DGM_PARALLEL
  return side_coords;
}

#ifdef CPLANT
/// DGM_SEND_RECEIVE scales better on CPLANT
#define DGM_SEND_RECEIVE
#else
/// DGM_SEND_RECEIVE_REPLACE is logically simpler
#define DGM_SEND_RECEIVE_REPLACE
#endif

/// Parallel communication (the send_receive approach is the best!)
void Field::share_sides() {
#ifdef DGM_PARALLEL
#ifdef DGM_SEND_RECEIVE_REPLACE
  // Fill buffer and send side information to neighbors
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    size_t sdof = 0;
    for (LocalSize i=0; i<partition->cinfo[n].nsides; i++) {
      const GlobalSize elmtid = partition->cinfo[n].links[i].elmtid;
      const GlobalSize sideid = partition->cinfo[n].links[i].sideid;
      const GlobalSize sidegid= partition->cinfo[n].links[i].sidegid;
      const Side *s=el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        for (LocalSize j=0; j<s->qtot(); j++) pc[n]->buf[sdof++] = s->u[j];
      } else {
        for (size_t k=0; k<s->subsides().size(); ++k) {
          const Side *ss = s->subsides()[k].get();
          if (ss->gid() == sidegid) {
            for (LocalSize j=0; j<ss->qtot(); j++) pc[n]->buf[sdof++]=ss->u[j];
            break;
          }
        }
      }
    }
    comm->SendReceiveReplace( pc[n]->buf.data(),
                              pc[n]->len,
                              partition->cinfo[n].cprocid,
                              partition->cinfo[n].cprocid,
                              partition->cinfo[n].cprocid,
                              comm->MyPID() );
  }
#else
  // comm->Barrier();
  // Fill buffer and send side information to neighbors
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    size_t sdof = 0;
    for (LocalSize i=0; i<partition->cinfo[n].nsides; i++) {
      const GlobalSize elmtid = partition->cinfo[n].links[i].elmtid;
      const GlobalSize sideid = partition->cinfo[n].links[i].sideid;
      const GlobalSize sidegid= partition->cinfo[n].links[i].sidegid;
      const Side *s=el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        for (LocalSize j=0; j<s->qtot(); j++) pc[n]->buf[sdof++] = s->u[j];
      } else {
        for (size_t k=0; k<s->subsides().size(); ++k) {
          const Side *ss = s->subsides()[k].get();
          if (ss->gid == sidegid) {
            for (LocalSize j=0; j<ss->qtot(); j++) pc[n]->buf[sdof++]=ss->u[j];
            break;
          }
        }
      }
    }
    comm->Send( partition->cinfo[n].cprocid, pc[n]->buf.data(),
                pc[n]->len, partition->cinfo[n].cprocid );
  }
  // receive side information from neighbors directly to side buffer
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    comm->Receive( comm->MyPID(), pc[n]->buf.data(),
                   pc[n]->len, partition->cinfo[n].cprocid );
  }
#endif  // DGM_SEND_RECIEVE_REPLACE
#endif  // DGM_PARALLEL
}

/// Nonblocking share sides
void Field::begin_share_sides() {
#ifdef DGM_PARALLEL
  // receive side information from neighbors directly to side buffer
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    comm->iReceive( comm->MyPID(), pc[n]->buf.data(),
                    pc[n]->len, partition->cinfo[n].cprocid );
  }
  // Fill send buffer and send side information to neighbors
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    size_t sdof = 0;
    for (LocalSize i=0; i<partition->cinfo[n].nsides; i++) {
      const GlobalSize elmtid = partition->cinfo[n].links[i].elmtid;
      const GlobalSize sideid = partition->cinfo[n].links[i].sideid;
      const GlobalSize sidegid= partition->cinfo[n].links[i].sidegid;
      const Side *s=el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        for (LocalSize j=0; j<s->qtot(); j++) pc[n]->sbuf[sdof++] = s->u[j];
      } else {
        for (size_t k=0; k<s->subsides().size(); ++k) {
          const Side::Ptr ss = s->subsides()[k];
          if (ss->gid() == sidegid) {
            for (LocalSize j=0; j<ss->qtot(); j++) pc[n]->sbuf[sdof++]=ss->u[j];
            break;
          }
        }
      }
    }
    comm->iSend( partition->cinfo[n].cprocid, pc[n]->sbuf.data(),
                 pc[n]->len, partition->cinfo[n].cprocid );
  }
  // Use the following to mimic blocking send/receives
  // comm->cout() << "Calling WaitAll" << endl;
  // comm->WaitAll();
  // comm->cout() << "Finished WaitAll" << endl;
#endif
}

/// Wait for completion of share sides
void Field::end_share_sides() const {
#ifdef DGM_PARALLEL
  comm->WaitAll();
#endif
}

/// Read curved side data
void Field::read_curve(const string &root) {
  Curve::db_type ctype;             // database of active curve types
  ctype["Nonaffine2D"].reset(new Straight(comm));
  ctype["Nonaffine3D"].reset(new Straight3D(comm));
  string fname = root+".crv";
  ifstream in(fname.c_str());
  if (in) Curve::read(comm,partition,fname,in,ctype,el);
  // Now figure out if any additional elements are non-affine
  Size numElements=0;
  for (size_t e=0; e<el.size(); e++) {
    bool affine = el[e]->is_affine();
    if (!affine && !el[e]->curve.get()) {
      numElements++;
      if (el[e]->nsd()==3)
        el[e]->curve.reset(ctype["Nonaffine3D"]->clone());
      else if (el[e]->nsd()==2)
        el[e]->curve.reset(ctype["Nonaffine2D"]->clone());
      else
        throw DGM::exception("One dimensional element cannot be curved");
      el[e]->curve->side = 0;
    }
  }
  if (numElements!=0)
    comm->cout()<<"NOTE:  determined that an additional "<<numElements
    <<" elements are non-affine!"<<endl;
}

/// Outputs the side links as a useful debugging capability
void Field::print_side_links() const {
  for (int i=0; i<comm->NumProc(); ++i) {
    if (i==comm->MyPID()) {
      cout<<"Print Side Links on processor  "<<comm->MyPID()<<endl;
      cout<<"Eid"<<'\t'<<"side"<<'\t'<<"&Side"<<'\t'<<"Link"<<'\t'
          <<"Base"<<endl;
      for (size_t e=0; e<el.size(); e++) {
        for (LocalSize n=0; n<el[e]->nSides(); n++) {
          cout << std::setw(4) << e << '\t'
               << std::setw(4) << n << '\t'
               << std::setw(10) << el[e]->side[n] << '\t'
               << std::setw(10) << el[e]->side[n]->link << '\t'
               << std::setw(10) << el[e]->side[n]->base << endl;
          for (unsigned s=0; s<el[e]->side[n]->subsides().size(); s++) {
            Side *ss = el[e]->side[n]->subsides()[s].get();
            cout <<"subside "<<setw(4)<<s<< '\t'
                 <<std::setw(10) << ss << '\t'
                 <<std::setw(10) << ss->link << '\t'
                 <<std::setw(10) << ss->base << endl;
          }
        }
      }
#ifdef DGM_PARALLEL
      cout << "Parallel connectivity on processor " << comm->MyPID() << endl;
      for (LocalSize p=0; p<partition->ncprocs(); p++)
        for (LocalSize n=0; n<partition->cinfo[p].nsides; n++) {
          cout << partition->cinfo[p].cprocid << '\t'
               << partition->cinfo[p].links[n].elmtid << '\t'
               << partition->cinfo[p].links[n].sideid << '\t'
               << partition->cinfo[p].links[n].sidegid
               << endl;
        }
#endif
    }
    cout.flush();
    comm->Barrier();
  }
}

/// Write out the element connectivity graph
/** \todo Add capability to write graph when running in parallel. */
void Field::write_graph(const string &fname) const {
  // cout << "Field::write_graph" << endl;
#ifndef DGM_PARALLEL
  // figure out the number of unique side links
  int nsides = 0;
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];    // shorthand
      if ( side->base ) {             // not a boundary side
        if (side->link) nsides++;     // master
      }
    }
  }
  // now write out the graph file
#if 0
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  //fprintf(fp,"%lu %d\n",ne,nsides);
  fprintf(fp,"%d %d\n",ne,nsides);
  for (GlobalSize e=0; e<ne; e++) {
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];    // shorthand
      if ( side->base ) {             // not a boundary side
        if (side->link)               // master
          fprintf(fp,"%d ",side->link->geid()+1);
        else
          fprintf(fp,"%d ",side->base->geid()+1);
      }
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
#else
  ofstream fp(fname.c_str());
  fp << ne << " " << nsides << endl;
  for (LocalSize e=0; e<ne; e++) {
    for (LocalSize i=0; i<el[e]->nSides(); i++) {
      Side *side = el[e]->side[i];    // shorthand
      if (side->base) {               // not a boundary side
        if (side->link)               // master
          fp << side->link->geid()+1 << " ";
        else
          fp << side->base->geid()+1 << " ";
      }
    }
    fp << endl;
  }
  fp.close();
#endif
#endif
}

/// Write out the relative weights that represent computational cost
/** \todo We should consider writing this out as a binary file to improve
 *  performance.  Of course, with internal partitioning, perhaps this file
 *  is no longer needed.
*/
void Field::write_weights(const string &fname) const {
#ifdef DGM_NO_WEIGHTS
  return;
#endif
  bool writeWeights = true;
  if (comm->Master()) {
    string file = root + ".json";
    ifstream json(file.c_str());
    if (json) {
      Json::Value value;
      Json::Reader reader;
      if (!reader.parse(json,value,true)) {
        throw DGM::exception("Failed to parse the json input file " + file +
                             ":  " + reader.getFormattedErrorMessages());
      }
      if (value.isMember("Field")) {
        Json::Value field = value["Field"];
        writeWeights = field.set("Write weights",writeWeights).asBool();
        if (verb>1) {
          Json::StyledWriter writer;
          string output = writer.write(field);
          cout << "  Field parameters:\n" << output;
        }
      }
    }
  }
  comm->Broadcast(&writeWeights);
  if (!writeWeights) return;
#ifdef DGM_PARALLEL
  iVector weight(el.size());
  iVector eids(el.size());
  for (size_t e=0; e<el.size(); e++) {
    weight[e] = el[e]->get_weight();
    eids[e] = el[e]->gid();
  }
  const int np = comm->NumProc();
  intVector rcounts(np); // integer because of MPI_AllGatherV
  intVector displs(np);  // integer because of MPI_AllGatherV
  const int nel = numeric_cast<int>(el.size()); // integer because of rcounts
  comm->GatherAll(&nel, rcounts.ptr(), 1);
  for (int i=0; i<np; i++) {
    displs[i] = 0;
    for (int j=0; j<i; j++) displs[i] += rcounts[j];  // make displacements
  }
  const Ordinal gne = numeric_cast<Ordinal>(partition->gne());
  // this is expensive since it is of size global number of elements
  iVector gweight(gne);
  iVector geid(gne);
#if 0
  comm->GatherAll(weight, el.size(), gweight, rcounts, displs);
#else
  // GatherV should be faster than AllGatherV and we only need info on master
  comm->GatherV(weight.ptr(), el.size(), gweight.ptr(), rcounts.ptr(),
                displs.ptr());
  comm->GatherV(eids.ptr(), el.size(), geid.ptr(), rcounts.ptr(),
                displs.ptr());
#endif
  if (comm->Master()) {
    // This is expensive as it is size global number of elements
    // sort the weights based on global element id
    vector< pair<Ordinal,Ordinal> > gw(gne);
    for (Ordinal e=0; e<gne; ++e) {
      gw[e].first = geid[e];
      gw[e].second = gweight[e];
    }
    std::sort(gw.begin(),gw.end());
    ofstream fp(fname.c_str());
    if (fp.fail())
      comm->error("Field: Could not open weight file for writing");
    fp << gne <<"\n";;
    if (fp.fail()) comm->error("Field: Error writing weight data");
    for (Ordinal e=0; e<gne; e++) {
      //fp << gweight[e] << " \n";
      fp << gw[e].second << " \n";
      if (fp.fail()) comm->error("Field: Error writing weight data");
    }
    fp.close();
  }
  comm->Barrier();
#else
  ofstream fp(fname.c_str());
  if (fp.fail()) comm->error("Field: Could not open weight file for writing");
  fp << gne <<"\n";;
  if (fp.fail()) comm->error("Field: Error writing weight data");
  for (size_t e=0; e<el.size(); e++) {
    fp << el[e]->get_weight() << " \n";
    if (fp.fail()) comm->error("Field: Error writing weight data");
  }
  fp.close();
#endif
}

/// Output the mesh in ASCII
void Field::write_mesh(const string &fname, const string &info) const {
  // cout << "Field::write_mesh" << endl;
#if 0
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  if (fp == NULL) comm->error("Field: Could not open mesh.dat for writing");
  if (fprintf(fp,"%s",((string)"# MESH DATA "+info+"\n").c_str())==EOF) {
    comm->error("Field: Error writing mesh data");
  }
  if ( fprintf(fp,"%lu %d NE NSD\n",el.size(),_nsd) == EOF )
    comm->error("Field: Error writing mesh data");
  for (size_t e=0; e<el.size(); e++) el[e]->write_mesh(fp);
  fclose(fp);
#else
  ofstream f(fname.c_str());
  if (!f) comm->error("Field: Could not open mesh.dat for writing");
  f << "# MESH DATA " << info << '\n';
  if (!f) comm->error("Field: Error writing mesh data");
  f << el.size() << " " << _nsd << " NE NSD\n";
  if (!f) comm->error("Field: Error writing mesh data");
  for (size_t e=0; e<el.size(); ++e) el[e]->write_mesh(f);
#endif
}

/// Set boundary conditions on a field
/** \note This currently generates an error is there is not root.bc */
void Field::initialize_bc(const string &root, const string &ext) {
  string fname = root+ext;
  // cout << "Field::initialize_bc from file " << fname << endl;
  ifstream fp(fname.c_str());
  if (fp) {
    read_bc(fp);
  } else {
    //comm->cout()<<"WARNING: Field::initialize_bc() could not open "+
    //fname<<endl;
    //comm->cout()<<"  Using default (no) boundary conditions"<<endl;
    comm->error("Field::initialize_bc() could not open "+fname);
  }
  // link in the boundary sides
  for (LocalSize n=0; n<nbc; n++) {
    GlobalSize eid = bc[n]->eid;
    LocalSize sid = bc[n]->sid;
    if (!el[eid]->side[sid]->subsides().empty()) {
      static bool message=true;
      if (message)
        comm->cout()<<"Warning: Don't know how to set BCs on subsides -- "
          <<eid<<":"<<sid<<":"<<el[eid]->side[sid]->subsides().size()<<endl;
      message = false;
      el[eid]->side[sid]->subsides().clear();
    }
    el[eid]->side[sid]->link = bc[n]->side;
    el[eid]->side[sid]->base = 0;
    el[eid]->side[sid]->flip_a(false);
    el[eid]->side[sid]->flip_b(false);
    el[eid]->side[sid]->transp(false);
    el[eid]->side[sid]->bc(true);
    bc[n]->side->flip_a(false);
    bc[n]->side->flip_b(false);
    bc[n]->side->transp(false);
    bc[n]->side->base = el[eid]->side[sid];
  }
#ifdef DGM_FIELD_VERBOSE
  write_bc("bc.dat");
#endif
}

/// Read the boundary conditions for this Field
/** \todo Add some error checking so it doesn't seg fault. */
void Field::read_bc(ifstream &in) {
  // cout << "Field::read_bc" << endl;
  string buffer;
  getline(in,buffer);        // strip off header line
  if (!(in>>nbc))
    comm->error("Field: Cannot read number of boundary conditions");
  getline(in,buffer);
  if (bc.size()!=0)
    for (size_t i=0; i<bc.size(); ++i) delete bc[i];
  bc.clear();
  bc_types.clear();
  bc_by_type.clear();
  for (LocalSize i=0; i<nbc; i++) {
    Boundary *tbc = new Boundary(partition, i, el, in);
    if (tbc->type == "")
      delete tbc;
    else {
      bc.push_back( tbc );
      std::vector<std::string>::const_iterator b = bc_types.begin();
      while (bc_types.end() != b && tbc->type != *b) ++b;
      if (b == bc_types.end()) bc_types.push_back(tbc->type);
      bc_by_type[tbc->type].push_back(tbc);
    }
  }
  sort (bc.begin(), bc.end(), sort_bc);
  nbc = (LocalSize)bc.size();  // number of Boundary sides in this partition
}

/// Write the boundary conditions for this Field
void Field::write_bc(const string &fname) const {
  //  cout << "Field::write_bc" << endl;
#if 0
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  if (fp == NULL) comm->error("Field: Could not open bc.dat for writing");
  if ( fprintf(fp,"# BOUNDARY CONDITION DATA\n") == EOF )
    comm->error("Field: Error writing bc data");
  if ( fprintf(fp,"%d nbc\n",nbc) == EOF )
    //if ( fprintf(fp,"%lu nbc\n",nbc) == EOF )
    comm->error("Field: Error writing bc data");
  for (GlobalSize n=0; n<nbc; n++) bc[n]->write(fp);
  fclose(fp);
#else
  ofstream fp(fname.c_str());
  if (!fp) comm->error("Field: Could not open bc.dat for writing");
  fp << "# BOUNDARY CONDITION DATA" << endl;
  fp << nbc << " nbc" << endl;
  for (LocalSize n=0; n<nbc; ++n) bc[n]->write(fp);
  fp.close();
#endif
}

/// Set the Field from a file
void Field::set(const string &root) {
  string fname = root+".ic";
  ifstream fp(fname.c_str());
  if (fp)
    read_ic(fp);
  else {
    stringstream msg;
    msg << "Field: Could not open initial condition: " << fname;
    comm->error(msg.str());
  }
  // project field to the polynomial space
  forward_transform();
  backward_transform();
}

/// Read an initial condition using inline parser
/** This uses the inline parser and combines lines using continuation
    character "\" **/
void Field::read_ic(ifstream &in) {
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) comm->error("Field: Cannot read IC code");
  getline(in,buffer);
  //  cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    getline(in,buffer);
    //buffer += '\n';   // parser needs a newline
    string::size_type loc = buffer.find(":=");
    if (loc == std::string::npos) {
      stringstream msg;
      msg<<"Field::fill(ifstream):  Did not find := required for inline "
           "parser";
      throw DGM::exception(msg.str());
    }
    // Move to the point after the := token
    loc += 2;
    string expr = buffer.substr(loc);
    string::size_type cont = std::string::npos;
    while ( (cont=expr.find("\\")) != std::string::npos) {
      expr.erase(expr.begin()+cont,expr.end());
      getline(in,buffer); expr += buffer;
    }
    for (LocalSize e=0; e<ne; e++) el[e]->fill(expr);
  } else if (lowerCase(code) == "restart") {
    string fname;
    if (!(in>>fname)) comm->error("Field: Cannot read restart file name");
    read(fname);
  }
}

//=============================================================================
//   These IO routines are obsolete and should be removed (3-21-2002)
//=============================================================================

/// Read a field file (deprecated)
void Field::read(const string &fname) {
  //  cout << "Field::read(const string)" << endl;
  ifstream fp(fname.c_str());
  if (!fp) {
    stringstream msg;
    msg << "Field: Could not open restart file:  " << fname;
    comm->error(msg.str());
  }
  string buffer;
  getline(fp,buffer);
  if (!(fp>>name)) comm->error("Field: Cannot read field name");
  getline(fp,buffer);
  if (!(fp>>ne>>_nsd>>Lmax)) comm->error("Field: Cannot read ne,nsd,Lmax");
  getline(fp,buffer);
  getline(fp,buffer);
  read(fp);
}

/// Read field data (deprecated)
void Field::read(ifstream &fs) {
#ifdef DGM_CONTIGUOUS
  // contiguous data
  fs.read(reinterpret_cast<char*>(elmt_data.data()),
          sizeof(Scalar)*elmt_data.size());
#else
  // non contiguous data
  for (GlobalSize e=0; e<ne; e++)
    // the reinterpret_cast is needed to treat Scalars as char
    fs.read(reinterpret_cast<char*>(el[e]->u.data()),
            sizeof(Scalar)*el[e]->u.size());
#endif
}

/// Write field data (deprecated)
void Field::write(ofstream &fs) const {
#ifdef DGM_CONTIGUOUS
  // contiguous data
  fs.write(reinterpret_cast<const char*>(elmt_data.data()),
      sizeof(Scalar)*elmt_data.size());
#else
  // non contiguous data
  for (GlobalSize e=0; e<ne; e++) {
    // the reinterpret_cast is needed to treat Scalars as char
    fs.write(reinterpret_cast<const char*>(el[e]->u.data()),
        sizeof(Scalar)*el[e]->u.size());
  }
#endif
}

//=============================================================================

/// Output the Field data to a Tecplot (ASCII) file
/** This is only really useful for mesh diagnostics. */
void Field::tecplot(const string &fname, const string &title) const {
  FILE *fp;
  fp = fopen(fname.c_str(),"w");
  fprintf(fp,"TITLE=\"%s\"\n",title.c_str());
  if (_nsd==1) {
    fprintf(fp,"VARIABLES=\"x\" \"%s\" \"d%s/dx\"\n",
            name.c_str(),name.c_str());
    fprintf(fp,"ZONE F=POINT\n");
  } else if (_nsd==2) {
    fprintf(fp,"VARIABLES=\"x\" \"y\" \"%s\" \"d%s/dx\" \"d%s/dy\"\n",
            name.c_str(),name.c_str(),name.c_str());
  } else if (_nsd==3) {
    fprintf(fp,"VARIABLES=\"x\" \"y\" \"z\" \"%s\"\n",
            name.c_str());
  } else {
    throw DGM::exception("Illegal number of space dimensions in "
                         "Field::tecplot");
  }
  for (LocalSize e=0; e<ne; e++) el[e]->tecplot(fp);
  fclose(fp);
}

/// Output the infinity, L2 and H1 norms of a Field
void Field::norm( const string &Name ) const {
  static Color bold(Color::BOLD);
  static Color red(Color::RED);
  static Color def(Color::DEFAULT);
  static Color green(Color::GREEN);
  //comm->cout()<<"Field::norm(string)"<<endl;
  string output_name;
  if (Name.size()!=0)
    output_name=Name;
  else
    output_name=name;
  static Format sci(10,18,'e');
  Scalar Linf=0, L2=0, H1=0;
  norm( Linf, L2, H1 );
  if (comm->Master()) {
    comm->cout()<<bold<<"Field: "<<setw(5)<<output_name
                <<sci(Linf)<<sci(L2)<<sci(H1)
                <<" (Linf L2 H1)"<<def<<endl;
  }
}

/// Compute the norms
void Field::norm( Scalar &Linf, Scalar &L2, Scalar &H1 ) const {
  Scalar area = 0.0;
  L2=0.0; H1=0.0; Linf=0.0;
  Scalar L2l=0.0, H1l=0.0, areal=0.0;
  for (LocalSize e=0; e<ne; e++) {
    el[e]->norm_L2(&L2l,&areal);
    el[e]->norm_H1(&H1l,&areal);
    Linf = std::max( el[e]->norm_Linf(), Linf );
    L2 += L2l;
    H1 += H1l;
    area += areal;
  }
#ifdef DGM_PARALLEL
  Scalar Linfl;
  Linfl = Linf; L2l = L2; H1l = H1; areal = area;
  comm->MaxAll( &Linfl, &Linf, 1);
  comm->SumAll(   &L2l,   &L2, 1);
  comm->SumAll(   &H1l,   &H1, 1);
  comm->SumAll( &areal, &area, 1);
#endif
  L2 = sqrt(abs(L2/area));  // note that they are area independent
  H1 = sqrt(abs(H1/area));  // note that this are area independent
}

/// Pack the Field into minimal, contiguous storage in modal space
void Field::pack() {
#ifndef DGM_CONTIGUOUS
  elmt_data.resize(qtot());
#endif
  LocalSize cnt=0;
  for (LocalSize e=0; e<ne; e++) {
    // el[e]->state = Element::Undefined;
    for (LocalSize k=0; k<el[e]->nModes(); k++)
      elmt_data[cnt++] = el[e]->uh[k];
  }
  for (LocalSize k=ndof(); k<qtot(); k++) elmt_data[k]=0.0;
}

/// Unpack the Field to a form that is compatible with a backward_transform
void Field::unpack() {
  LocalSize cnt = ndof();
#if 0
  // Old approach only worked for signed indices
  for (LocalSize e=ne-1; e>=0 && ne>e; e--) {
    // el[e]->state = Element::Undefined;
    for (int k=el[e]->qtot()-1; k>el[e]->nModes()-1; k--)
      el[e]->u[k] = 0.0;
    for (int k=el[e]->nModes()-1; k>=0; k--)
      el[e]->u[k] = elmt_data[--cnt];
  }
#else
  // Use a reverse iterator to march backward
  vector<Element*>::reverse_iterator rit;
  for (rit=el.rbegin(); rit<el.rend(); ++rit) {
    Element *e = *rit;
    // e->state = Element::Undefined;
    for (LocalSize k=e->qtot; --k > e->nModes()-1; )
      e->u[k] = 0.0;
    for (LocalSize k=e->nModes(); k-- > 0; )
      e->u[k] = elmt_data[--cnt];
  }
#endif
}

/// Apply the metric of integration (Gauss weights and |J|)
void Field::apply_metric() {
  for (LocalSize e=0; e<ne; e++) el[e]->apply_metric();
}

/// Apply the metric of integration (Gauss weights and |J|)
void Field::remove_metric() {
  for (LocalSize e=0; e<ne; e++) el[e]->remove_metric();
}

/// Compute the spatial average of the Field
Scalar Field::average() const {
  Scalar avg  = DGM::zero;
  Scalar area = DGM::zero;
  Scalar elmt_area = DGM::zero;
  for (LocalSize e=0; e<ne; e++) {
    avg  += el[e]->integrate(&elmt_area);
    area += elmt_area;
  }
#ifdef DGM_PARALLEL
  Scalar avgl  = avg;
  Scalar areal = area;
  comm->SumAll(  &avgl,  &avg, 1);
  comm->SumAll( &areal, &area, 1);
#endif
  return avg/area;
}

/// Do a planar average of the Field (this is useful for channel flows)
void Field::plane_average() {
  for (LocalSize e=0; e<ne; e++) {
    // cout << "Averaging element " << e << endl;
    el[e]->plane_average();
  }
}

/// Output the range (minimum and maximum) values in the Field
void Field::range() const {
  static DGM::Format sci(8); sci.scientific().width(15);
  Scalar fmin = this->min();
  Scalar fmax = this->max();
  comm->cout() << "  " << setw(8) << right << get_name()
               << ": min, max = " <<sci(fmin)<< ", " <<sci(fmax)<< "\n";
}

/// Output the side range (minimum and maximum) values in the Field
void Field::rangeSide() const {
  static DGM::Format sci(8); sci.scientific().width(15);
  Scalar fmin = this->minSide();
  Scalar fmax = this->maxSide();
  comm->cout() << "  " << setw(8) << right << get_name()
               << ": min, max = " <<sci(fmin)<< ", " <<sci(fmax)<< "\n";
}

/// Make partition sides (these sides should be contiguous for efficiency)
void Field::make_partition_sides(const Field *F) {
#ifdef DGM_PARALLEL
  // cout << "Field::make_partition_sides(Field *)" << endl;
  pc.clear();
  for (LocalSize n=0; n<partition->ncprocs(); n++) {
    pc.push_back( new Pcon<GlobalSize,LocalSize,Scalar> );
    size_t sdof = 0;  // side degrees of freedom in connection
    for (LocalSize i=0; i<partition->cinfo[n].nsides; i++) {
      GlobalSize elmtid = partition->cinfo[n].links[i].elmtid;
      LocalSize  sideid = partition->cinfo[n].links[i].sideid;
      GlobalSize sidegid= partition->cinfo[n].links[i].sidegid;
      Side *s=el[elmtid]->side[sideid];
      if (s->subsides().empty()) {
        sdof         += s->qtot();
        s->link       = F->el[elmtid]->side[sideid]->link->clone();
        s->base       = 0;
        s->link->link = 0;
        s->link->base = s->link;
        pc[n]->side.push_back( s->link );
      } else {
        for (size_t j=0; j<s->subsides().size(); ++j) {
          Side *ss = s->subsides()[j].get();
          if (ss->gid() == sidegid) {
            sdof += ss->qtot();
            ss->link       = F->el[elmtid]->side[sideid]->
                             subsides()[j]->link->clone();
            ss->link->u.resize(F->el[elmtid]->side[sideid]->
                               subsides()[j]->link->qtot());
            ss->base       = 0;
            ss->link->link = 0;
            ss->link->base = ss->link;
            pc[n]->side.push_back( ss->link );
            break;
          }
        }
      }
    }
    // make contiguous space for partition sides of size sdof
    pc[n]->len = sdof;
    pc[n]->buf.resize(sdof);
    pc[n]->sbuf.resize(sdof);
    size_t start = 0;
    for (size_t i=0; i<pc[n]->side.size(); i++) {
      pc[n]->side[i]->u.alias( pc[n]->buf, start, pc[n]->side[i]->qtot() );
      start += pc[n]->side[i]->qtot();
    }
  }
#endif
}

/** Clear partition sides (when we have ghost elements, these are not needed)
 *
 *  \note Since we delete sides belonging to Pcon, maybe this functionality
 *  should be in the (currently not existing) Pcon destructor?
 */
void Field::clear_partition_sides() {
#ifdef DGM_PARALLEL
  // cout << "Field::clear_partition_sides()" << endl;
  for (size_t n=0; n<pc.size(); n++) {
    Pcon<GlobalSize,LocalSize,Scalar>* pcon = pc[n];
    for (size_t i=0; i<pcon->side.size(); i++) {
      delete pcon->side[i];
    }
    delete pcon;
  }
  pc.clear();
#endif
}

//============================================================================
//              Stuff to locate elements within a field
//============================================================================

/// Returns a 3d bounding box around a given element id within the Field
/** \param[in] element_id The (local) id of the element to bound
    \return    A vector defining the bounding box   */
std::vector<float> Field::box(const Ordinal element_id) const {
  const Ordinal i = element_id;
  const Element &e = *el[i];
  std::vector<float> bnd(6);
  bnd[0] = numeric_cast<float>(e.box.first.x);
  bnd[1] = numeric_cast<float>(e.box.first.y);
  bnd[2] = numeric_cast<float>(e.box.first.z);
  bnd[3] = numeric_cast<float>(e.box.second.x);
  bnd[4] = numeric_cast<float>(e.box.second.y);
  bnd[5] = numeric_cast<float>(e.box.second.z);
  return bnd;
}

/// Builds bounding boxes around every element in the Field
/** \param[in,out] bounds a vector of bounding box vectors. */
void Field::boxes(std::vector< std::vector<float> > &bounds) const {
  bounds.clear();
  bounds.reserve(ne);
  for (LocalSize e=0; e<ne; ++e) bounds.push_back(box(e));
}

/// Returns the bounding box around the elements in this Field
/** This computes the local bounding box. */
const BoundingBox & Field::my_box() const {
  if (!have_my_bbox) {
    Scalar lower[3] = {std::numeric_limits<Scalar>::max()};
    Scalar upper[3] = {std::numeric_limits<Scalar>::min()};
    std::vector<float> bnd(6);
    for (size_t e=0; e<el.size(); ++e) {
      bnd = box(numeric_cast<Ordinal>(e));
      if (bnd[0] < lower[0]) lower[0] = bnd[0];
      if (bnd[1] < lower[1]) lower[1] = bnd[1];
      if (bnd[2] < lower[2]) lower[2] = bnd[2];
      if (upper[0] < bnd[3]) upper[0] = bnd[3];
      if (upper[1] < bnd[4]) upper[1] = bnd[4];
      if (upper[2] < bnd[5]) upper[2] = bnd[5];
    }
    BoundingBox& Box = const_cast<BoundingBox&>(my_bbox);
    add(Point(lower[0],lower[1],lower[2]), Box);
    add(Point(upper[0],upper[1],upper[2]), Box);

    // need to do this since it is logically a const method
    const_cast<bool&>(have_my_bbox) = true;
  }
  return my_bbox;
}

/// Returns the bounding box around the elements in this Field
/** This computes the global bounding box. */
BoundingBox Field::box() const {
  Scalar lower[3] = {std::numeric_limits<Scalar>::max()};
  Scalar upper[3] = {std::numeric_limits<Scalar>::min()};
  std::vector<float> bnd(6);
  for (size_t e=0; e<el.size(); e++) {
    bnd = box(numeric_cast<Ordinal>(e));
    if (bnd[0] < lower[0]) lower[0] = bnd[0];
    if (bnd[1] < lower[1]) lower[1] = bnd[1];
    if (bnd[2] < lower[2]) lower[2] = bnd[2];
    if (upper[0] < bnd[3]) upper[0] = bnd[3];
    if (upper[1] < bnd[4]) upper[1] = bnd[4];
    if (upper[2] < bnd[5]) upper[2] = bnd[5];
  }
  Scalar L[3] = {std::numeric_limits<Scalar>::max()};
  Scalar U[3] = {std::numeric_limits<Scalar>::min()};
  comm->MinAll(lower, L, 3);
  comm->MaxAll(upper, U, 3);
  BoundingBox Box;
  add(Point(L[0],L[1],L[2]),Box);
  add(Point(U[0],U[1],U[2]), Box);
  return Box;
}

/// Determines if a given point is inside a given element in the Field
/** \param[in] point A point in space
    \param[in] element_id The (local) id for the element under consideration
    \param[in] epsilon Optional tolerance for the check
    \return Returns a boolean that is true if the point is in the element   */
bool Field::is_in_element(const Point &point,
                          const Ordinal element_id,
                          const Scalar epsilon) const {
  const Ordinal nverts = el[element_id]->nVerts();
  const std::vector<Vertex::Ptr> &vert = el[element_id]->vert;
#if 0
  const std::vector<Point> points(vert.begin(), vert.end());
#else
  std::vector<Point> points;
  for (Ordinal i=0; i<nverts; ++i) points.push_back( *vert[i] );
#endif
  bool inside=false;
  if (el[element_id]->curve.get()) {
    // Curved elements are quite difficult. Handle as special case.
#if 1
    const std::vector<float> box = Field::box(element_id);
    Scalar diameter = 0;
    for (unsigned j=0; j<3; ++j)
     diameter = std::max(diameter,numeric_cast<Scalar>(abs(box[j+3]-box[j])));
    // Scale error is a fraction of the longest side.
    diameter /= 100;
    inside = box[0]-diameter <= point.x && point.x <= box[3]+diameter &&
             box[1]-diameter <= point.y && point.y <= box[4]+diameter &&
             box[2]-diameter <= point.z && point.z <= box[5]+diameter;
    if (inside) {
      Scalar r=0, s=0, t=0;
      switch (nverts) {
      case 8:
        inside = el[element_id]->get_local_coordinates(point,r,s,t);
        break;
      case 4:
        inside = el[element_id]->get_local_coordinates(point,r,s);
        break;
      case 3:
        inside = el[element_id]->get_local_coordinates(point,r,s);
        break;
      case 2:
        inside = el[element_id]->get_local_coordinates(point,r);
        break;
      default:
        stringstream msg;
        msg << "Field::is_in_element() unsupported number of vertices: "
            <<nverts;
        comm->error(msg.str());
      }
    }
#else
    Scalar r=0, s=0, t=0;
    switch (nverts) {
    case 8:
      inside = el[element_id]->get_local_coordinates(point,r,s,t);
      break;
    case 4:
      inside = el[element_id]->get_local_coordinates(point,r,s);
      break;
    case 3:
      inside = el[element_id]->get_local_coordinates(point,r,s);
      break;
    case 2:
      inside = el[element_id]->get_local_coordinates(point,r);
      break;
    default:
      stringstream msg;
      msg << "Field::is_in_element() unsupported number of vertices: "<<nverts;
      comm->error(msg.str());
    }
#endif
  } else {
    switch (nverts) {
    case 8: inside = Mesh::is_in_element_hex (point, points, epsilon); break;
    case 4: 4 == el[element_id]->nEdges() ?
            inside = Mesh::is_in_element_quad(point, points, epsilon) :
            inside = Mesh::is_in_element_tet (point, points, epsilon) ; break;
    case 3: inside = Mesh::is_in_element_tri (point, points, epsilon); break;
    case 2: inside = Mesh::is_in_element_line(point, points, epsilon); break;
    default:
      stringstream msg;
      msg << "Field::is_in_element() unsupported number of vertices: "<<nverts;
      comm->error(msg.str());
    }
  }
  return inside;
}

//============================================================================
//              T r i l i n o s   I n f r a s t r u c t u r e
//============================================================================

#ifdef DGM_USE_EPETRA

/// create initial element row and col maps, fill ghost element array
void Field::init_redistribution_framework(const Epetra_Comm& Comm) {
#ifdef DGM_USE_GENERAL_GHOSTING
  //comm->cerr() << "init_redistribution_framework" << endl;
  // build element rmap
  vector<int> myele;
  myele.reserve(el.size());
  for (size_t iele=0; iele<el.size(); iele++) {
    myele.push_back(el[iele]->gid());
  }

  // create non-overlapping map
  const int myele_size = numeric_cast<int>(myele.size());
  ele_rmap = Teuchos::rcp(new Epetra_Map(-1, myele_size, &myele[0], 0, Comm));

  // overlapping map is currently the same, since no ghosts have been sent
  // around
  ele_cmap = Teuchos::rcp(new Epetra_Map(*row_element_map()));

  // fill column element vector with already present elements
  ghost_el.clear();

  // fix element neighbors: Sides with bc shall have no neighbors
  for (size_t iele = 0; iele != el.size(); iele++) {
    Element *ele = el[iele];
    for (Ordinal iside = 0; iside != ele->nSides(); iside++) {
      Side *s = ele->side[iside];
      if (s->is_bc()) {
        ele->adj_els[iside] = Element::invalid_ele_neighbor;
      }
    }
  }
  // comm->cerr() << "init_redistribution_framework done!" << endl;
#endif // DGM_USE_GENERAL_GHOSTING
}

/*!
 *  \brief This method ghosts all neighbor elements to all processors
 */
void Field::ghost_aura() {
#ifdef DGM_USE_GENERAL_GHOSTING
  // build element cmap: we want only element adjacent elements ghosted
  std::set<int> own_and_aura_ele;
  for (size_t lid=0; lid<el.size(); lid++) {
    const Element*const ele = el[lid];
    own_and_aura_ele.insert(ele->gid());
    for (size_t iside=0; iside < ele->adjacent_elements().size(); ++iside) {
      const Size ele_gid = ele->adjacent_elements()[iside];
      if (ele_gid != Element::invalid_ele_neighbor) {
        // only add valid element gids
        own_and_aura_ele.insert(ele_gid);
      }
    }
  }
  // copy, because the Epetra_Map needs a continuous integer array
  std::vector<int> tmp( own_and_aura_ele.begin(), own_and_aura_ele.end() );
  ele_cmap = Teuchos::rcp(
    new Epetra_Map(-1, (int)tmp.size(), &tmp[0], 0, row_element_map()->Comm()));

  // build source map 'gid -> element'
  map<int,Element*> elementmap;
  for (size_t iele=0; iele<el.size(); iele++) {
    Element* ele = el[iele];
    elementmap[ele->gid()] = ele;
  }

  // reshuffle, elementmap will contain all elements mentioned in ele_cmap
  // i.e. in this case all owned plus aura (ghost) elements
  DGM::Exporter exporter(*row_element_map(), *col_element_map(), *comm);
  exporter.ExportViaStrings(elementmap);

  // fill column element vector with ghost elements
  // elements, that have been here before, are unchanged!
  // new elements are created
  for (map<int,Element*>::const_iterator iter = elementmap.begin();
       iter != elementmap.end(); iter++) {
    int gid = iter->first;
    // put only not owned elements in there
    if (row_element_map()->MyGID(gid) == false) {
      // int lid = ele_cmap->LID(gid);
      // cout << "ghost" << endl;
      Element* ele = iter->second;
      ghost_el[gid] = ele;
    }
  }
  // Todo: now, we have to reconnect all the pointers and stuff
  // the following is a copy from the Field constructor.
  // we just have to look at each and see, what needs to be set up
  // read_curve( root );            // needed for cubit meshes!!
  // comm->cout() << "read_curve() done" << endl;
  // read_node_connectivity(root);  // setup nodal connectivity
  // set_side_links( root );        // make connectivity links
  clear_partition_sides();          // erase partition sides, because we will
                                    // reconnect to ghost elements next
  reset_side_links();
  // set_global_side_id();          // make global side id's
  // adjust_side_order();           // adjust side qpts to match
  // make_partition( root );        // partition the mesh if parallel
  // make_storage();                // allocate storage
  // comm->cout() << "compute_geometry()" << endl;
  compute_geometry(ghost_el);       // elmt mappings, Jacobian, mass matrix
  compute_side_geometry(ghost_el);  // side mapping, Jacobian, normal vectors
  // initialize_bc(root);           // setup boundary sides
#endif // DGM_USE_GENERAL_GHOSTING
}

/// test serialization of element vector
void Field::test_element_serialization() {
#ifdef DGM_USE_GENERAL_GHOSTING
  comm->cerr() << "test_element_serialization" << endl;
  // serialize
  std::ostringstream sendstream;
  boost::archive::binary_oarchive oar(sendstream);
  oar & el;
  string sends(sendstream.str());
  comm->cerr() << "serialized" << endl;

  // dummy transfer data
  string recvs;
  recvs = sends;

  // deserialize
  std::istringstream recvstream(recvs);
  boost::archive::binary_iarchive iar(recvstream);
  vector<Element*> test_el;
  iar & test_el;
  comm->cerr() << "deserialized" << endl;

  // put elements back into map
  // for (vector<Element*>::const_iterator i=test_el.begin();
  //      i!=test_el.end(); i++) {
  //   Element* ele = *i;
  //   Element& eleref = *ele;
  //   comm->cerr() << eleref << endl;
  // }
#endif // DGM_USE_GENERAL_GHOSTING
}

#endif // DGM_USE_EPETRA

} // namespace DGM

/** \file Boundary.cpp
    \brief Boundary implementation
    \author Scott Collis
*/

// DGM includes
#include "Boundary.hpp"

namespace DGM {

Boundary::Boundary() {
  // cout << "Boundary default constructor" << endl;
  id   = undefined<LocalSize>();
  type = "";
  geid = undefined<GlobalSize>();
  eid  = undefined<LocalSize>();
  sid  = undefined<LocalSize>();
  elmt = NULL;
  S    = NULL;
  B    = NULL;
  side = NULL;
  V    = NULL;
}

Boundary::Boundary(Partition<Size,Ordinal,Scalar>::Ptr partition,
                   const LocalSize ID, const vector<Element*> &el,
                   ifstream &in) {
  // cout << "Boundary() for id = " << ID << endl;
  const int verb=0;
  id   = ID;
  type = "";
  geid = undefined<GlobalSize>();
  eid  = undefined<LocalSize>();
  sid  = undefined<LocalSize>();
  elmt = NULL;
  S    = NULL;
  B    = NULL;
  side = NULL;
  V    = NULL;
  read(in);
  if (!partition->owns(geid))
    type = "";                              // mark for removal
  else {
    eid = partition->inc(geid);             // global to local eid
    elmt = el[eid];
    if ( undefined(sid) || sid >= elmt->nSides() ) {
      DGM::Comm::World->cerr()
        << "Invalid side id read from boundary condition file" << endl
        << "  for BC id      = " << id << endl
        << "      type       = " << type << endl
        << "  for geid       = " << geid << endl
        << "  for eid        = " << eid << endl
        << "  for sid        = " << sid << endl
        << "  undefined(sid) = " << undefined(sid)
        << "  with max sid   = " << elmt->nSides()-1 << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    if (verb) {
      cout
        << "Side id read from boundary condition file" << endl
        << "  for BC id      = " << id << endl
        << "      type       = " << type << endl
        << "  for geid       = " << geid << endl
        << "  for eid        = " << eid << endl
        << "  for sid        = " << sid << endl
        << "  undefined(sid) = " << undefined(sid)
        << "  with max sid   = " << elmt->nSides()-1 << endl;
    }
    side = elmt->side[sid]->clone();
    side->u.resize(elmt->side[sid]->qtot());  // since not contiguous
    S = elmt->side[sid];
    B = side;
    V = elmt->side[sid]->clone();
    V->u.resize(elmt->side[sid]->qtot());  // since not contiguous
  }
}

Boundary::~Boundary() {
  if (side) delete side;
  if (V) delete V;
}

void Boundary::read(ifstream &in) {
  string buffer;
  in >> type >> geid >> sid;
  getline(in,buffer);
}

void Boundary::write(ofstream &out) const {
  if (type=="D")
    out << type << " " << elmt->gid() << " " << sid << " " << 0.0 << endl;
  else if (type=="F")
    out << type << " " << elmt->gid() << " " << sid << " " << 0.0 << endl;
  else if (type=="W" || type=="S" || type=="J" || type=="O")
    out << type << " " << elmt->gid() << " " << sid << endl;
  else {
    DGM::Comm::World->error("Boundary::write_bndry() Unsupported Boundary type: "
                            +type);
  }
}

} // namespace DGM

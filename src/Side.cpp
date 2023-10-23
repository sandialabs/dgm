/** \file Side.cpp
    \brief DGM element side class implementation
*/

// system includes
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Side.hpp"
#include "Element.hpp"

namespace DGM {

// Explicit instantiation
template class Side::Info<Side::GlobalSize,Side::LocalSize,DGM::Scalar>;

/// Default constructor
Side::Side() :
  elink(0),
  link(0), base(0),
  subside()
#ifdef DGM_USE_MD_COUPLE
  , modeltype = Model::EULER
#endif
{
  info.reset( new MyInfo() );
}

#ifdef DGM_USE_MD_COUPLE

// normal constructor with multi-domain coupling
Side::Side(const LocalSize id_i, Element *e_i, const LocalSize nModes_i,
           const LocalSize q1_i, const LocalSize q2_i,
           const bool GLL, const Model::Type model) : subside() {
  //  cout << "Side constructor " << this << endl;
  info.reset( new MyInfo(id_i, MyInfo::uid<LocalSize>(),
                         MyInfo::uid<LocalSize>(),
                         nModes_i, q1_i, q2_i, GLL) );
  elink = e_i;
  link = 0;
  base = 0;
#ifndef DGM_CONTIGUOUS
  u.resize(qtot());
#endif
  J_orig.resize(qtot);    J_Orig = 0;
  J_scale.resize(qtot);   J_scale = 0;
  modeltype = model;
}

#else  // !DGM_USE_MD_COUPLE

// normal constructor
Side::Side(const LocalSize id_i, Element *elink_i, const LocalSize nModes_i,
     const LocalSize q1_i, const bool GLL, const LocalSize q2_i) : subside() {
  //  cout << "Side constructor " << this << endl;
  info.reset( new MyInfo(id_i, MyInfo::uid<GlobalSize>(),
                         MyInfo::uid<GlobalSize>(),
                         nModes_i, q1_i, q2_i, GLL) );
  elink = elink_i;
  link = 0;
  base = 0;
#ifndef DGM_CONTIGUOUS
  u.resize(qtot());
#endif
}

#endif

/// copy constructor
Side::Side(const Side &side) : info(side.info), elink(side.elink),
                               link(side.link), base(side.base),
                               subside(side.subside) {
  // cout<<"Side& copy constructor: "<<&side<<" to "<<this<<endl;
#ifdef DGM_USE_MD_COUPLE
  u.resize(qtot());
  u = side.u;
  modeltype = side.modeltype;
#else
#ifndef DGM_CONTIGUOUS
  u.resize(side.u.size());
  u = side.u;
#endif
#endif
}

/// copy constructor
Side::Side(const Side *side) : info(side->info), elink(side->elink),
                               link(side->link), base(side->base) ,
                               subside(side->subside)  {
#ifdef DGM_USE_MD_COUPLE
  u.resize(qtot());
  u = side->u;
  modeltype = side->modeltype;
#else
#ifndef DGM_CONTIGUOUS
  u.resize(qtot());
  u = side->u;
#endif
#endif
}

void Side::match( Side *s ) {
  // cout << "Side::match(Side *)" << endl;
  q1(max(q1(), s->q1()));
  q2(max(q2(), s->q2()));
  s->q1(q1()); s->q2(q2());
  if (q2()) {
    resize(q1()*q2());
    s->resize(q1()*q2());
  } else {
    resize(q1());
    s->resize(q1());
  }
}

/// resize the storage on a Side
void Side::resize(const LocalSize q) {
  // cout << "Side::resize(const int)" << endl;
  if (q == u.size()) return;
  info->resize(q);
#ifndef DGM_CONTIGUOUS
  u.resize(q);
#endif
}

Size Side::leid() const {
  if (elink == NULL) throw exception("Local element id is unknown to Side, "
                                     "because elink is not set up!");
  return elink->lid();
}


Side& Side::operator=(const Side& side) {
  if (this == &side) return *this;
  if (qtot() != side.qtot())
    throw DGM::exception("Side::operator=() mismatch");
  info = side.info;
  elink = side.elink;
  link = side.link;
  base = side.base;
  u.resize(side.u.size());
  u = side.u;
  subside = side.subside;
#ifdef DGM_USE_MD_COUPLE
  modeltype = side.modeltype;
#endif
  return *this;
}

Side& Side::deep_copy_info(const Side& side) {
  if (this == &side) return *this;
  if (qtot() != side.qtot())
    throw DGM::exception("Side::deep_copy_info=() mismatch");
  *info = *side.info;
  elink = side.elink;
  link = side.link;
  base = side.base;
  u.resize(side.u.size());
  u = side.u;
  for (unsigned i=0; i<subside.size(); ++i) {
    subside[i]->u.resize(side.subside[i]->u.size());
    subside[i]->u =      side.subside[i]->u;
  }
#ifdef DGM_USE_MD_COUPLE
  modeltype = side.modeltype;
#endif
  return *this;
}

// destructor
Side::~Side() {}

/// output a Side to a stream
std::ostream & operator<<(std::ostream &os, const Side &side) {
  os << "Side: " << endl <<
    "  id      = " << side.id() << endl <<
    "  gid     = " << side.gid() << endl <<
    "  geid    = " << side.geid() << endl <<
    "  leid    = " << side.leid() << endl <<
    "  qtot    = " << side.qtot() << endl <<
    "  q1      = " << side.q1() << endl <<
    "  q2      = " << side.q2() << endl <<
    "  flip_a  = " << side.flip_a() << endl <<
    "  flip_b  = " << side.flip_b() << endl <<
    "  transp  = " << side.transp() << endl <<
    "  info    = " << side.info.get() << endl <<
    "  elink   = " << side.elink << endl <<
    "  link    = " << side.link << endl <<
    "  base    = " << side.base << endl <<
    "  measure = " << side.measure() << endl <<
    "  h_n_inv = " << side.h_n_inv() << endl <<
    "  bc      = " << side.bc() << endl;
  return os;
}

} // namespace DGM

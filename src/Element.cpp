/** \file Element.cpp
    \brief Abstract Element base class implementation
    \author Scott Collis

    Element is an abstract class so that there actually are no objects of
    type Element, only objects that are derived from Element.  Because of
    this, most of Elements virtual methods are not implemented.  However,
    there are a few methods that are generic and they are implemented here.
*/

// System includes
#include <iostream>
using namespace std;

// DGM includes
#include "Comm.hpp"
#include "Coordinates.hpp"
#include "Element.hpp"
#include "Utilities.hpp"

namespace DGM {

// define static data
unsigned int Element::random_state_length(32);
CMC::Vector<char,unsigned int> Element::random_state;

#ifdef DGM_USE_GENERAL_GHOSTING
const Size Element::invalid_ele_neighbor = std::numeric_limits<int>::max();
#endif

/// Destructor
Element::~Element() {}

//=============================================================================
// Side methods
//=============================================================================

void Element::fill_side(const dVector &f, const int side_id, dVector &f_side){
 DGM_UNDEFINED;
}
void Element::fill_sides(const Scalar f, const Operation operation) {
  switch (operation) {
  case Equal: {
    for (Ordinal i=0; i<nSides(); ++i) {
      side[i]->u = f;
    }
    break;
  }
  case Add: {
    for (Ordinal i=0; i<nSides(); ++i) {
      side[i]->u += f;
    }
    break;
  }
  case Subtract: {
    for (Ordinal i=0; i<nSides(); ++i) {
      side[i]->u -= f;
    }
    break;
  }
  case Multiply: {
    for (Ordinal i=0; i<nSides(); ++i) {
      side[i]->u *= f;
    }
    break;
  }
  case Divide: {
    for (Ordinal i=0; i<nSides(); ++i) {
      side[i]->u /= f;
    }
    break;
  }
  default:
    throw DGM::exception("Unsupported operation in Element::fill_sides");
    break;
  }
#ifdef DGM_ALLOW_HANGING_NODES
  this->push_to_subsides();
#endif
}
void Element::fill_sides(const dVector &) {DGM_UNDEFINED;}
void Element::fill_sides(const dVector &, const dVector &) {DGM_UNDEFINED;}
void Element::fill_sides(const dVector &, const dVector &,
                         const dVector &) {DGM_UNDEFINED;}
void Element::fill_sides(const Scalar t, const string function_string,
                         const Operation operation) {
  parser_init();
  if (nsd()==1) {
    for (Ordinal i=0; i<nSides(); ++i) {
      const Ordinal qtot(side[i]->qtot());
      std::vector<Point> pside(qtot);
      get_side_coordinates(i, &pside[0]);
      dVector x(qtot);
      for (Ordinal j=0; j<qtot; ++j) {
        x[j] = pside[j].x;
      }
      Parser::VectorFunction f("x", "t", function_string );
      f.evaluate( x, side[i]->u, t, convert(operation) );
    }
  } else  if (nsd()==2) {
    for (Ordinal i=0; i<nSides(); ++i) {
      const Ordinal qtot(side[i]->qtot());
      std::vector<Point> pside(qtot);
      get_side_coordinates(i, &pside[0]);
      dVector x(qtot), y(qtot);
      for (Ordinal j=0; j<qtot; ++j) {
        x[j] = pside[j].x;
        y[j] = pside[j].y;
      }
      Parser::VectorFunction f("x", "y", "t", function_string );
      f.evaluate( x, y, side[i]->u, t, convert(operation) );
    }
  } else if (nsd()==3) {
    for (Ordinal i=0; i<nSides(); ++i) {
      const Ordinal qtot(side[i]->qtot());
      std::vector<Point> pside(qtot);
      get_side_coordinates(i, &pside[0]);
      dVector x(qtot), y(qtot), z(qtot);
      for (Ordinal j=0; j<qtot; ++j) {
        x[j] = pside[j].x;
        y[j] = pside[j].y;
        z[j] = pside[j].z;
      }
      Parser::VectorFunction f("x", "y", "z", "t", function_string );
      f.evaluate( x, y, z, side[i]->u, t, convert(operation) );
    }
  } else {
    error("Illegal nsd in Element::fill_sides():  nsd = "+asString(nsd()));
  }
#ifdef DGM_ALLOW_HANGING_NODES
  this->push_to_subsides();
#endif
  return;
}

void Element::fill_sides_uniform(const dVector &) {DGM_UNDEFINED;}
void Element::lift(const Element *const, dVector &, const char)
  const {DGM_UNDEFINED;}
/// Compute an integral over all element sides
Scalar Element::compute_side_integral() const {
  Scalar result=0.0;
  for (Ordinal sid=0; sid<nSides(); sid++) {
    result += compute_side_integral(side[sid]->u,sid);
  }
  return result;
}
Scalar Element::compute_side_integral(dVector &, Ordinal) const {
  DGM_UNDEFINED; return 0.0;
}
Scalar Element::compute_side_measure() const {
  DGM_UNDEFINED; return 0.0;
}
//void Element::push_to_subsides() const {DGM_UNDEFINED;}
void Element::push_side_geom_to_subside(Side *,
                                  const Side *,
                                  const Scalar) const {DGM_UNDEFINED;}
vector<Point> Element::get_side_endpoints(const Ordinal) const
{DGM_UNDEFINED; return vector<Point>();}
Ordinal Element::sideMap(const Side *s, const Ordinal ql) const {
  DGM_UNDEFINED; return 0;
}

void Element::sideMap(const Side *s, const Ordinal qt, Ordinal *k) const {
  for (Ordinal ql=0; ql<qt; ++ql) {
    k[ql] = this->sideMap(s,ql);
  }
}

Ordinal Element::sideVertMap(const Ordinal lsid, const Ordinal lvid) const {
  DGM_UNDEFINED; return 0;
}
void Element::side2size(const Ordinal side, iVector &q) const {
  DGM_UNDEFINED;
}
Ordinal Element::side2size(const Ordinal side) const {
  DGM_UNDEFINED; return 0;
}

Scalar Element::compute_subside_geometry(Side *, const Element &)
                  const {DGM_UNDEFINED; return 0;}
Scalar Element::compute_subside_geometry(Side *, const vector<Point> &)
                  const {DGM_UNDEFINED; return 0;}

// Initialization
void Element::get_mass_matrix() {DGM_UNDEFINED;}
void Element::get_mass_matrix(const dVector &) {DGM_UNDEFINED;}
void Element::get_1d_mass_matrix(Minfo &) const {DGM_UNDEFINED;}
void Element::get_derivative_matrix() {DGM_UNDEFINED;}

/** Default implementation should work for most elements. */
void Element::zero() { state = Physical; u=0.0; }

/** Absolute value should work for most elements. */
void Element::Abs() { state = Physical; u.Abs(); }

/** Default implementation should work for most elements. */
void Element::fill(const Scalar v, Operation operation) {
  state = Physical;
  switch (operation) {
  case Equal:
    u = v;
    break;
  case Add:
    u += v;
    break;
  case Subtract:
    u -= v;
    break;
  case Multiply:
    u *= v;
    break;
  case Divide:
    u /= v;
    break;
  default:
    throw DGM::exception("Invalid operation requested in Element::fill"
                         "(const Scalar v, int operation");
  }
}

/** Default implementation should work for most elements. */
void Element::fill(PF pf, Operation operation) {
  state = Physical;
  if (operation==Equal) {
    for (Ordinal q=0; q<qtot; q++) u[q] = pf((*C)[q]);
  }
  else if (operation==Add) {
    for (Ordinal q=0; q<qtot; q++) u[q] += pf((*C)[q]);
  }
  else if (operation==Subtract) {
    for (Ordinal q=0; q<qtot; q++) u[q] -= pf((*C)[q]);
  }
  else if (operation==Multiply) {
    for (Ordinal q=0; q<qtot; q++) u[q] *= pf((*C)[q]);
  }
  else if (operation==Divide) {
    for (Ordinal q=0; q<qtot; q++) u[q] /= pf((*C)[q]);
  }
  else {
    throw DGM::exception("Invalid operation requested in Element::fill"
                         "(PF pf, int operation");
  }
}

void Element::fill(string, Operation operation) { DGM_UNDEFINED; }
void Element::fill(Mode &) {DGM_UNDEFINED;}
void Element::fill(Mode &, dVector &) const {DGM_UNDEFINED;}

/** Default implementation should work for most elements. */
void Element::fill(const dVector &v) {
  state = Physical; u = v;
}

void Element::random() {DGM_UNDEFINED;}

/** Default implementation should work for most elements. */
void Element::extract(dVector &v) const {
  if (state != Physical) error("Element::extract not in physical space",1);
  v = u;
}
void Element::set(const dVector &, const Ordinal) {DGM_UNDEFINED;}

//=============================================================================
// Local assembly matrices and residuals
//=============================================================================

void Element::get_local_mass_matrix(const dVector &) {DGM_UNDEFINED;}
void Element::get_local_derivative_matrix() {DGM_UNDEFINED;}
void Element::get_local_derivative_matrix(const dVector &) {DGM_UNDEFINED;}
void Element::get_local_laplace_matrix() {DGM_UNDEFINED;}
void Element::get_local_laplace_matrix(const dVector &) {DGM_UNDEFINED;}
/// The inner product of the element against the Basis
void Element::test_on_shape() {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  // just a wrapper, but better name
  inner_product();
}
/// The inner product of a vector over the element against the Basis
void Element::test_on_shape(const dVector &v, dVector &vh) const {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  // just a wrapper, but better name
  dVector tmp(v.size());
  tmp = 0;
  tmp += v;
  inner_product(tmp, vh);
}
void Element::test_on_shape_side(const dVector &v, const int sid, dVector &vh)
const {
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  dVector f( side[sid]->qtot() );
  dVector fh( qtot );
  assert ( f.size() == v.size() );
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], fh );
    load_side( fh, sid, f );
    dvmul(v,f);
    vh[m] = compute_side_integral(f,sid);
  }
}
/// Inner product over the element against the derivative of the Basis
/** This is a very bad implementation that is tremendously slow.  Instead,
    one should use the local derivative operators and replace this with
    BLAS Level 3 operations.
    \todo Should be re-written (it is an order of magnitude too slow)   */
void Element::test_on_grad_shape(const dVector &v, char dir, dVector &vh) const{
  //static FunctionTimer timer(__PRETTY_FUNCTION__);
  //FunctionSentry sentry(timer);
  dVector f(qtot);
  dVector df(qtot);
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    gradient( f, df, dir);
    vh[m]=L2_inner_product(df,v);
  }
}
/// Default implementation errors out
std::vector<dMatrix*> Element::get_interpolation_matrices () const {
  std::vector<dMatrix*> matrices;
  DGM::exception("Element get_interpolation_matrices not implemented!");
  return matrices;
}
/** \note This is slow right now, but I have sped it up a bit. */
void Element::test_on_normal_times_gradient_side(const dVector &v,
                                                 const int sid,
                                                 dVector &vh ) const {
  dVector fsum( side[sid]->qtot() );
  dVector f( qtot );
  assert ( fsum.size() == v.size() );
  assert ( (dVector::size_type)nModes() == vh.size() );
  for (Ordinal m=0; m<nModes(); m++) {
    fill( psi->mode[m], f );
    normal_times_gradient_side( f, sid, fsum );
    dvmul(v, fsum);
    vh[m] = compute_side_integral(fsum,sid);
  }
}
void Element::normal_times_gradient_side(const dVector&, const int sid,
                                         dVector&) const {
  DGM_UNDEFINED;
}

//=============================================================================
// Transforms methods
//=============================================================================

Basis* Element::get_basis(const int der) const {DGM_UNDEFINED; return 0;}
void Element::inner_product() {DGM_UNDEFINED;}
void Element::inner_product(dVector &, dVector &) const {DGM_UNDEFINED;}

void Element::forward_transform() {DGM_UNDEFINED;}
void Element::forward_transform(dVector &, dVector &) const {DGM_UNDEFINED;}
void Element::forward_transform(Element *E) const {
  E->zero();
  if (state == Transform) {
    E->set(uh,nModes());
  } else {
    // transform to mode space, if physical space
    dVector utmp = u;
    dVector uhtmp(nModes());
    this->forward_transform(utmp, uhtmp);
    E->set(uhtmp,nModes());
  }
}
void Element::forward_transform(Element *, Element *) {DGM_UNDEFINED;}

void Element::backward_transform() {DGM_UNDEFINED;}
void Element::backward_transform(dVector &, dVector &) const {DGM_UNDEFINED;}

void Element::solve_mass_matrix(dVector &) const {DGM_UNDEFINED;}
void Element::solve_mass_matrix(dMatrix &) {DGM_UNDEFINED;}
void Element::interpolate_to_uniform() {DGM_UNDEFINED;}

//=============================================================================
// Filter methods
//=============================================================================

void Element::make_constant() {DGM_UNDEFINED;}
void Element::low_modes(const Ordinal) {DGM_UNDEFINED;}
void Element::kill_constant() {DGM_UNDEFINED;}
void Element::filter(const dVector &){DGM_UNDEFINED;}
void Element::exp_filter(const Scalar, const Scalar ){DGM_UNDEFINED;}
void Element::coarse_scales(const int){DGM_UNDEFINED;}
void Element::coarse_scales(const int, dVector &){DGM_UNDEFINED;}
void Element::fine_scales(const int){DGM_UNDEFINED;}
void Element::fine_scales(const int, dVector &){DGM_UNDEFINED;}
void Element::fine_scales_transform(const int, dVector &)const{DGM_UNDEFINED;}
/** \brief fill element specific linear Legendre->Lagrange basis shift matrix
 *
 * Used for multigrid computations
 *
 * @param G element transformation matrix to be filled
*/
void Element::fill_basis_shift_matrix(dMatrix &G)const{DGM_UNDEFINED;}

/// Bound the element solution
/** Default implementation is based on CMC::Vector::clamp(). */
void Element::bound(const Scalar low, const Scalar high) {
  if (state != Physical) error("Element::extract not in physical space",1);
  u.Clamp(low,high);
}
void Element::vms_isolate_small(){DGM_UNDEFINED;}
void Element::vms_isolate_small(dVector &, dVector &) {DGM_UNDEFINED;}
void Element::vms_isolate_small(dVector &) {DGM_UNDEFINED;}

// Derivative methods
void Element::gradient(const dVector &, dVector &) const {DGM_UNDEFINED;}
void Element::gradient(const dVector &, dVector &, char) const {DGM_UNDEFINED;}
void Element::gradient(const dVector &, dVector &, dVector &)
  const {DGM_UNDEFINED;}
void Element::gradient(const dVector &, dVector &,
                       dVector &, dVector &) const {DGM_UNDEFINED;}
void Element::local_gradient(const dVector &, dVector &,
                             dVector &) const {DGM_UNDEFINED;}
void Element::local_gradient(const dVector &, dVector &,
                             dVector &, dVector &) const {DGM_UNDEFINED;}

// Geometry methods
void Element::get_coordinates() {DGM_UNDEFINED;}
void Element::get_straight_coordinates() {DGM_UNDEFINED;}
void Element::get_curved_coordinates() {DGM_UNDEFINED;}
void Element::get_side_coordinates(const Ordinal, Point *)const{DGM_UNDEFINED;}
void Element::compute_geometry() {DGM_UNDEFINED;}
void Element::compute_straight_geometry() {DGM_UNDEFINED;}
void Element::compute_curved_geometry() {DGM_UNDEFINED;}
Element::StabMetrics Element::compute_metrics() {
  Element::StabMetrics tmp;
  DGM_UNDEFINED;
  return tmp;
}

/// Compute the element metrics in 1d
/** This should be in the BaseLine element. */
Element::StabMetrics Element::compute_metrics_1d() {
#ifdef DGM_STORE_METRICS
  dVector &dxr = geom->dxr;
  dVector &ivol = geom->ivol;
  dVector &acoustic = geom->acoustic;
#else
  dVector dxr(qtot);
  dVector ivol(qtot);
  dVector acoustic(qtot);
#endif
  // compute coordinate gradients in mapped space
  Scalar xr = pt5 * (vert[1]->x - vert[0]->x);
  dxr = 0;
  Scalar dr;
  for (Ordinal i=0, q=0; i<qa; i++) {
    if (i==0)
      dr = (psi->za[i+1] - psi->za[i]);
    else if (i==qa-1)
      dr = (psi->za[i] - psi->za[i-1]);
    else
      dr = pt5 * (psi->za[i+1] - psi->za[i-1]);
    q = i;
    dxr[q] = xr * dr;
    ivol[q] =  one / ( dr * geom->J[q] );
    acoustic[q] = one; // dxr[q];
    // cout << "ivol = " << ivol[q] << ", acoustic = " << acoustic[q] << endl;
  }
  StabMetrics metrics;
#ifndef DGM_STORE_METRICS
  // Need to use an insert instead of copy constructor, because
  // dVector's copy constructor does not resize to the RHS dVector.
  //metrics[DXR]      = dxr;
  //metrics[IVOL]     = ivol;
  //metrics[ACOUSTIC] = acoustic;
  metrics.insert(StabMetrics::value_type( DXR,  dxr  ));
  metrics.insert(StabMetrics::value_type( IVOL, ivol ));
  metrics.insert(StabMetrics::value_type( ACOUSTIC, acoustic ));
#endif
  return metrics;
}

/// Compute metric terms for stability estimates for 2d tensor product elements
/** While this works fairly well, it is not consistent in the sense that
    the stability criteria is based on the quadrature rule used, which is
    certainly not really the case. Once the polynomial basis is set, that
    should be all that is needed to determine the stability criteria.

    \note Only valid for tensor product elements.  As such, should really
    be in the derived classes. */
Element::StabMetrics Element::compute_metrics_2d_tensor_prod() {
#ifdef DGM_STORE_METRICS
  dVector &dxr = geom->dxr;
  dVector &dyr = geom->dyr;
  dVector &dxs = geom->dxs;
  dVector &dys = geom->dys;
  dVector &ivol = geom->ivol;
  dVector &acoustic = geom->acoustic;
#else
  dVector dxr(qtot);
  dVector dyr(qtot);
  dVector dxs(qtot);
  dVector dys(qtot);
  dVector ivol(qtot);
  dVector acoustic(qtot);
#endif

  // temporary storage
  dVector xr(qtot), xs(qtot);
  dVector yr(qtot), ys(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs );
  local_gradient( C->y, yr, ys );

  dxr = 0; dxs = 0;
  dyr = 0; dys = 0;
  Scalar dr, ds;
  for (Ordinal i=0, q=0; i<qa; i++) {
    if (i==0)
      dr = (psi->za[i+1] - psi->za[i]);
    else if (i==qa-1)
      dr = (psi->za[i] - psi->za[i-1]);
    else
      dr = pt5 * (psi->za[i+1] - psi->za[i-1]);
    for (Ordinal j=0; j<qb; j++) {
      if (j==0)
        ds = (psi->zb[j+1] - psi->zb[j]);
      else if (j==qb-1)
        ds = (psi->zb[j] - psi->zb[j-1]);
      else
        ds = pt5 * (psi->zb[j+1] - psi->zb[j-1]);
      q = j + i * qb;
      dxr[q] = xr[q] * dr;
      dxs[q] = xs[q] * ds;
      dyr[q] = yr[q] * dr;
      dys[q] = ys[q] * ds;
      ivol[q] =  one / ( dr * ds * geom->J[q] );
      acoustic[q] = sqrt( (dxr[q]+dyr[q])*(dxr[q]+dyr[q]) +
                          (dxs[q]+dys[q])*(dxs[q]+dys[q]) );
    }
  }
  StabMetrics metrics;
#ifndef DGM_STORE_METRICS
  // Need to use an insert instead of copy constructor, because
  // dVector's copy constructor does not resize to the RHS dVector.
  //metrics[DXR]      = dxr;
  //metrics[DYR]      = dyr;
  //metrics[DXS]      = dxs;
  //metrics[DYS]      = dys;
  //metrics[IVOL]     = ivol;
  //metrics[ACOUSTIC] = acoustic;
  metrics.insert(StabMetrics::value_type( DXR,  dxr  ));
  metrics.insert(StabMetrics::value_type( DYR,  dyr  ));
  metrics.insert(StabMetrics::value_type( DXS,  dxs  ));
  metrics.insert(StabMetrics::value_type( DYS,  dys  ));
  metrics.insert(StabMetrics::value_type( IVOL, ivol ));
  metrics.insert(StabMetrics::value_type( ACOUSTIC, acoustic ));
#endif
  return metrics;
}

namespace {

  bool left_edge(Ordinal i, Ordinal qa) {
    Scalar left = (1.0+sqrt(4.0*qa*(qa+1.0)-8.0*i+1.0))/Scalar(2);
    // if index i is on left edge, left will be an integer value
    return(left == int(left));
  }

  bool right_edge(Ordinal i, Ordinal qa) {
    Scalar right = (1.0+sqrt(4.0*qa*(qa+1.0)-8.0*i-7.0))/Scalar(2);
    // if index i is on right edge, right will be an integer value
    return(right == int(right));
  }

} // anonyomous namespace

/// Compute metric terms for stability estimates for 2d nodal triangles
/** \note Only valid for nodal tris.  As such, should really be in the derived
    classes. */
Element::StabMetrics Element::compute_metrics_nodal_tri() {
#ifdef DGM_STORE_METRICS
  dVector &dxr = geom->dxr;
  dVector &dyr = geom->dyr;
  dVector &dxs = geom->dxs;
  dVector &dys = geom->dys;
  dVector &ivol = geom->ivol;
  dVector &acoustic = geom->acoustic;
#else
  dVector dxr(qtot);
  dVector dyr(qtot);
  dVector dxs(qtot);
  dVector dys(qtot);
  dVector ivol(qtot);
  dVector acoustic(qtot);
#endif

  // temporary storage
  dVector xr(qtot), xs(qtot);
  dVector yr(qtot), ys(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs );
  local_gradient( C->y, yr, ys );

  dxr = 0; dxs = 0;
  dyr = 0; dys = 0;
  Scalar dr=0, ds=0;
  for (Ordinal q=0, q_left=0, q_diff=qa+1; q<qtot; q++) {
    if (q<qtot-1) { // ignore top point for dr
      if (left_edge(q, qa)) {
        q_left = q;
        q_diff -= 1;
        dr = (psi->znt_r[q+1] - psi->znt_r[q]);
      } else if (right_edge(q, qa))
        dr = (psi->znt_r[q] - psi->znt_r[q-1]);
      else
        dr = pt5 * (psi->znt_r[q+1] - psi->znt_r[q-1]);
    }

    if (q<qa)  // bottom edge
      ds = (psi->znt_s[q_left+qa] - psi->znt_s[q_left]);
    else if (q==qtot-1) { // Top node
      ds = (psi->znt_s[q] - psi->znt_s[q-2]);
      dr = ds; // by symmetry (I hope)
    }
    else
      ds = pt5*(psi->znt_s[q_left+q_diff] - psi->znt_s[q_left-(q_diff+1)]);

    dxr[q] = xr[q] * dr;
    dxs[q] = xs[q] * ds;
    dyr[q] = yr[q] * dr;
    dys[q] = ys[q] * ds;
    ivol[q] =  one / ( dr * ds * geom->J[q] );
    acoustic[q] = sqrt( (dxr[q]+dyr[q])*(dxr[q]+dyr[q]) +
                        (dxs[q]+dys[q])*(dxs[q]+dys[q]) );
  }
  StabMetrics metrics;
#ifndef DGM_STORE_METRICS
  // Need to use an insert instead of copy constructor, because
  // dVector's copy constructor does not resize to the RHS dVector.
  //metrics[DXR]      = dxr;
  //metrics[DYR]      = dyr;
  //metrics[DXS]      = dxs;
  //metrics[DYS]      = dys;
  //metrics[IVOL]     = ivol;
  //metrics[ACOUSTIC] = acoustic;
  metrics.insert(StabMetrics::value_type( DXR,  dxr  ));
  metrics.insert(StabMetrics::value_type( DYR,  dyr  ));
  metrics.insert(StabMetrics::value_type( DXS,  dxs  ));
  metrics.insert(StabMetrics::value_type( DYS,  dys  ));
  metrics.insert(StabMetrics::value_type( IVOL, ivol ));
  metrics.insert(StabMetrics::value_type( ACOUSTIC, acoustic ));
#endif
  return metrics;
}

/// Compute metric terms for stability estimates for 3d tensor product elements
/** \note This is only valid for a tensor-product element. */
Element::StabMetrics Element::compute_metrics_3d_tensor_prod() {
#ifdef DGM_STORE_METRICS
  dVector &dxr = geom->dxr;
  dVector &dyr = geom->dyr;
  dVector &dzr = geom->dzr;
  dVector &dxs = geom->dxs;
  dVector &dys = geom->dys;
  dVector &dzs = geom->dzs;
  dVector &dxt = geom->dxt;
  dVector &dyt = geom->dyt;
  dVector &dzt = geom->dzt;
  dVector &ivol = geom->ivol;
  dVector &acoustic = geom->acoustic;
#else
  dVector dxr(qtot);
  dVector dyr(qtot);
  dVector dzr(qtot);
  dVector dxs(qtot);
  dVector dys(qtot);
  dVector dzs(qtot);
  dVector dxt(qtot);
  dVector dyt(qtot);
  dVector dzt(qtot);
  dVector ivol(qtot);
  dVector acoustic(qtot);
#endif

  // temporary storage
  dVector xr(qtot), xs(qtot), xt(qtot);
  dVector yr(qtot), ys(qtot), yt(qtot);
  dVector zr(qtot), zs(qtot), zt(qtot);

  // compute coordinate gradients in mapped space
  local_gradient( C->x, xr, xs, xt );
  local_gradient( C->y, yr, ys, yt );
  local_gradient( C->z, zr, zs, zt );

  dxr = 0; dxs = 0; dxt = 0;
  dyr = 0; dys = 0; dyt = 0;
  dzr = 0; dzs = 0; dzt = 0;
  Scalar dr, ds, dt;
  for (Ordinal i=0, q=0; i<qa; i++) {
    if (i==0)
      dr = (psi->za[i+1] - psi->za[i]);
    else if (i==qa-1)
      dr = (psi->za[i] - psi->za[i-1]);
    else
      dr = pt5 * (psi->za[i+1] - psi->za[i-1]);
    for (Ordinal j=0; j<qb; j++) {
      if (j==0)
        ds = (psi->zb[j+1] - psi->zb[j]);
      else if (j==qb-1)
        ds = (psi->zb[j] - psi->zb[j-1]);
      else
        ds = pt5 * (psi->zb[j+1] - psi->zb[j-1]);
      for (Ordinal k=0; k<qc; k++) {
        if (k==0)
          dt = (psi->zc[k+1] - psi->zc[k]);
        else if (k==qc-1)
          dt = (psi->zc[k] - psi->zc[k-1]);
        else
          dt = pt5 * (psi->zc[k+1] - psi->zc[k-1]);
        q = i*qb*qc + j*qc + k;
        dxr[q] = xr[q] * dr;
        dxs[q] = xs[q] * ds;
        dxt[q] = xt[q] * dt;
        dyr[q] = yr[q] * dr;
        dys[q] = ys[q] * ds;
        dyt[q] = yt[q] * dt;
        dzr[q] = zr[q] * dr;
        dzs[q] = zs[q] * ds;
        dzt[q] = zt[q] * dt;
        ivol[q] =  one / ( dr * ds * dt * geom->J[q] );
        acoustic[q] = sqrt( (dxr[q]+dyr[q]+dzr[q])*(dxr[q]+dyr[q]+dzr[q]) +
                            (dxs[q]+dys[q]+dzs[q])*(dxs[q]+dys[q]+dzs[q]) +
                            (dxt[q]+dyt[q]+dzt[q])*(dxt[q]+dyt[q]+dzt[q]) );
      }
    }
  }
  StabMetrics metrics;
#ifndef DGM_STORE_METRICS
  // Need to use an insert instead of copy constructor, because
  // dVector's copy constructor does not resize to the RHS dVector.
  //metrics[DXR]      = dxr;
  //metrics[DYR]      = dyr;
  //metrics[DZR]      = dzr;
  //metrics[DXS]      = dxs;
  //metrics[DYS]      = dys;
  //metrics[DZS]      = dzs;
  //metrics[DXT]      = dxt;
  //metrics[DYT]      = dyt;
  //metrics[DZT]      = dzt;
  //metrics[IVOL]     = ivol;
  //metrics[ACOUSTIC] = acoustic;
  metrics.insert(StabMetrics::value_type( DXR,  dxr  ));
  metrics.insert(StabMetrics::value_type( DYR,  dyr  ));
  metrics.insert(StabMetrics::value_type( DZR,  dzr  ));
  metrics.insert(StabMetrics::value_type( DXS,  dxs  ));
  metrics.insert(StabMetrics::value_type( DYS,  dys  ));
  metrics.insert(StabMetrics::value_type( DZS,  dzs  ));
  metrics.insert(StabMetrics::value_type( DXT,  dxt  ));
  metrics.insert(StabMetrics::value_type( DYT,  dyt  ));
  metrics.insert(StabMetrics::value_type( DZT,  dzt  ));
  metrics.insert(StabMetrics::value_type( IVOL, ivol ));
  metrics.insert(StabMetrics::value_type( ACOUSTIC, acoustic ));
#endif
  return metrics;
}
void Element::compute_side_geometry() {DGM_UNDEFINED;}
void Element::forward_transform_side(dVector &, dVector &) {DGM_UNDEFINED;}
Scalar Element::interpolate_point(const Point &p) const {
  DGM_UNDEFINED; return 0.0;
}
void Element::calculate_interpolation_matrices(vector<fMatrix>&,
                                                const vector<Point>&) const{
  DGM_UNDEFINED;
}
void Element::apply_interpolation_matrices(dVector &vals,
                                             const vector<fMatrix>&) const{
  DGM_UNDEFINED;
}
void Element::calculate_interpolation_matrices(vector<dMatrix>&,
                                                const vector<Point>&) const{
}
void Element::apply_interpolation_matrices(dVector &vals,
                                             const vector<dMatrix>&) const{
  DGM_UNDEFINED;
}

void Element::interpolate_points(const vector<Point> &ps, dVector &vals) const {
  DGM_UNDEFINED;
}
int Element::get_local_coordinates(const Point &p, Scalar &r) const {
  DGM_UNDEFINED; return 0;
}
int Element::get_local_coordinates(const Point &p, Scalar &r, Scalar &s) const {
  DGM_UNDEFINED; return 0;
}
int Element::get_local_coordinates(const Point &p, Scalar &r, Scalar &s,
                                   Scalar &t) const {
  DGM_UNDEFINED; return 0;
}

//=============================================================================
// Curved side methods
//=============================================================================

void Element::get_curved_side_info(const Ordinal sid, vector<Point> &p,
    dVector &z, int &orientation) const {DGM_UNDEFINED;}
void Element::J_backward_transform(dVector &, dVector &) {DGM_UNDEFINED;}
void Element::solve_1d_mass_matrix(dVector &) const {DGM_UNDEFINED;}
void Element::forward_transform_side(const Ordinal, dVector &, dVector &,
                                     dVector*) {DGM_UNDEFINED;}
void Element::get_straight_side_coordinates(const Ordinal, dVector &, dVector &,
                                            dVector &) const {DGM_UNDEFINED;}
void Element::get_edge(Ordinal, Ordinal, Scalar *, Ordinal, Scalar *) {
  DGM_UNDEFINED;
}

void Element::generate_curve() {
  // cout << "Element::generate_curve() for " << gid() << endl;
  if (curve.get()) {
    if (qc) {           // if 3d
      dVector x, y, z;  // temporary vectors
      curve->generate( this, x, y, z );
      // only quadratic and beyond elements can have curved sides
      if (L() > 2) {
        // compute modal coefficients for mapping (Face/Edge)
        // curve->xh     face modes
        // curve->xh_e   edge modes
        forward_transform_side(curve->side, x, curve->xh, curve->xh_e);
        forward_transform_side(curve->side, y, curve->yh, curve->yh_e);
        forward_transform_side(curve->side, z, curve->zh, curve->zh_e);
      }
    } else if (qb) {   // 2d
      dVector x, y;    // temporary vectors
      curve->generate( this, x, y );
      // only quadratic and beyond elements can have curved sides (watch out!)
      if (L() > 2) {
        // compute modal coefficients for mapping
        forward_transform_side(x, curve->xh);
        forward_transform_side(y, curve->yh);
      }
    } else {
      throw DGM::exception("Trying to defined a 1d curved element for "
          "element = "+asString(gid()));
    }
  }
}

void Element::set_box() {
  const Scalar mx = std::numeric_limits<Scalar>::max();
  Point min(mx,mx,mx), max(-mx,-mx,-mx);
  for (Ordinal i=0; i<nVerts(); ++i) {
    if (vert[i]->x < min.x) min.x = vert[i]->x;
    if (vert[i]->y < min.y) min.y = vert[i]->y;
    if (vert[i]->z < min.z) min.z = vert[i]->z;
    if (max.x < vert[i]->x) max.x = vert[i]->x;
    if (max.y < vert[i]->y) max.y = vert[i]->y;
    if (max.z < vert[i]->z) max.z = vert[i]->z;
  }    
  box.first  = min; 
  box.second = max; 
}

bool Element::is_in_element(const Point &p, const Scalar radius) const {
  const Scalar radius_sq = radius*radius;
  Ordinal i=0;
  for (; i<qtot; ++i) {
    if (p.distance_sq((*C)[i]) < radius_sq) break;
  }
  const bool is_within_radius = i < qtot;
  return is_within_radius;
}

bool Element::is_in_element(const Point &p,
                            const dMatrix &unit,
                            const dVector &radius) const {
  Ordinal i=0;
  dVector Y(3), X(3);
  for (; i<qtot; ++i) {
    for (Ordinal j=0; j<3; ++j) X[j] = (*C)[i][j] - p[j];
    mvmult(unit,X,Y);
    const Scalar distance_sq = (Y[0]*Y[0])/(radius[0]*radius[0]) +
                               (Y[1]*Y[1])/(radius[1]*radius[1]) +
                               (Y[2]*Y[2])/(radius[2]*radius[2]);
    if (distance_sq< 1) break;
  }
  const bool is_within_radius = i < qtot;
  return is_within_radius;
}

//=============================================================================
// Utilities
//=============================================================================

/// Output a tecplot (ASCII) file
void Element::tecplot(FILE *) {DGM_UNDEFINED;}
/// Dump various information to a file
void Element::output(FILE *, const char) const {DGM_UNDEFINED;}
/// Return length of particular binary data
streamoff Element::binaryLength(const OutputType) const {
  DGM_UNDEFINED;
  return 0;
}
/// Output in a binary format
void Element::binaryOutput(FILE *, const OutputType) const {DGM_UNDEFINED;}
#if 0
/// Write to a mesh file
void Element::write_mesh(FILE *, const string) const {DGM_UNDEFINED;}
#else
/// Write to a mesh file
void Element::write_mesh(ostream &, const unsigned) const {DGM_UNDEFINED;}
#endif
/// Get element weights and properties
void Element::get_weight_props(Topology::ElementType&, bool&, Ordinal&) const {}

/// Default is to return equal weights of 100
int Element::get_weight() const { return 100; }

/// Clone interface -- must be provided by derived types
Element* Element::clone() const {DGM_UNDEFINED; return 0;}

//=============================================================================
// Norm and inner product methods
//=============================================================================

Scalar Element::norm_Linf() const {DGM_UNDEFINED; return 0.0;}
Scalar Element::norm_L2() const {DGM_UNDEFINED; return 0.0;}
Scalar Element::norm_H1() const {DGM_UNDEFINED; return 0.0;}
void   Element::norm_L2(Scalar *, Scalar *) const {DGM_UNDEFINED;}
void   Element::norm_H1(Scalar *, Scalar *) const {DGM_UNDEFINED;}
Scalar Element::integrate( Scalar *) const {
  DGM_UNDEFINED;
  return 0.0;
}
Scalar Element::integrate(const dVector &, Scalar *) const {
  DGM_UNDEFINED;
  return 0.0;
}
Scalar Element::compute_measure() const {DGM_UNDEFINED; return 0.0;}
Scalar Element::L2_inner_product(const Element *Y, Scalar *measure) const {
  DGM_UNDEFINED;
  return 0.0;
}
Scalar Element::L2_inner_product(const dVector &x, const dVector &y,
                                 Scalar *measure) const {
  DGM_UNDEFINED;
  return 0.0;
}

//=============================================================================
// The following methods may not be very useful -- use with care...
//=============================================================================

void Element::apply_metric() {DGM_UNDEFINED;}
void Element::remove_metric() {DGM_UNDEFINED;}

} // namespace DGM

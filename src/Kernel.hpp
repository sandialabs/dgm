#ifndef DGM_KERNEL_HPP
#define DGM_KERNEL_HPP

/** \file Kernel.hpp
    \brief DGM kernel class declarations
    \author Scott Collis
*/

// system includes
#include <limits>
#include <vector>

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// DGM includes
#include "Types.hpp"
#include "String.hpp"
#include "Element.hpp"
#include "Coordinates.hpp"
#include "Field.hpp"
#include "vField.hpp"

namespace DGM {

//============================================================================
//                              K e r n e l
//============================================================================

  /// Abstract base class for spatial kernels
  class Kernel {
  protected:
    Scalar x0;           ///< location in x
    Scalar y0;           ///< location in y
    Scalar z0;           ///< location in z
    int verb;            ///< verbosity level
  public:
    /// Constructor
    Kernel(const Scalar x_0=0, const Scalar y_0=0, const Scalar z_0=0)
      : x0(x_0), y0(y_0), z0(z_0), verb(0) {}
    Kernel(const Point x) : x0(x.x), y0(x.y), z0(x.z), verb(0) {}
    /// Destructor
    virtual ~Kernel() {}
    /// Shared pointer type
    typedef DGM::Shared<Kernel>::Ptr Ptr;
    /// Evaluate at a Point
    virtual Scalar operator() (const Point &C) const = 0;
    /// Add scaled kernel to an element
    virtual void addScaled(Element *E, const Scalar value) const = 0;
    /// added kernel to an element
    void add(Element *E) const { addScaled(E,1.0); }
    /// Apply the kernel to a Field
    virtual Scalar apply(const Field *F, const Scalar factor=1.0) = 0;
    /// Add scaled kernel to a Field
    virtual void addScaled(Field *F, const Scalar amp) const = 0;
    /// Add kernel to a Field
    virtual void add(Field *F) const { addScaled(F,1.0); }
    /// Create a list of elements for which this kernel is active
    virtual void create_element_vector(const vField &U) {}
    /// Get number of elements this kernel spans on this rank
    virtual size_t get_number_elements() const { DGM_UNDEFINED; return 0; }
    virtual Ordinal get_number_quadrature_points() const { return 0; }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(3);
      centroid[0] = x0; centroid[1] = y0; centroid[2] = z0;
      return centroid;
    }
  };

  /// Delta spatial kernel
  class Delta : public Kernel {
    const std::vector<Size> eids; ///< element id number(s).
                                  ///< Plurl if on boundary.
    const Point P;                ///< a point in space
    mutable std::vector<Point> L; ///< local coordinates of P in eids

    void fill_L(const Field *F) const {
      L.reserve(eids.size());
      for (size_t eid=0; eid<eids.size(); ++eid) {
        const Ordinal eidx = F->partition->inc(eids[eid]);
        const Element *E = F->el[eidx];
        L.push_back(E->get_local_coordinates(P));
      }
    }
  public:
    /// Constructor
    Delta(const Size _eid, const Scalar x_0=0, const Scalar y_0=0,
          const Scalar z_0=0) : Kernel(x_0,y_0,z_0), eids(1,_eid),
                                P(x_0,y_0,z_0),
                                L() {
      if (verb)
        DGM::Comm::World->cout() << "Building Delta at eid = " << _eid
                                 << " and point " << P << endl;
    }
    /// Vector constructor
    Delta(const Size _eid, const Point &X)
        : Kernel(X.x,X.y,X.z), eids(1,_eid), P(X), L() {
      if (verb)
        DGM::Comm::World->cout() << "Building Delta at eid = " << _eid
                                 << " and point " << P << endl;
    }
    Delta(const std::vector<Size> _eids, const Point &X)
                 : Kernel(X.x,X.y,X.z), eids(_eids), P(X), L() {
      if (verb) {
        DGM::Comm::World->cout() << "Building Delta at eids = ";
        for (size_t i=0; i<eids.size(); ++i)
          DGM::Comm::World->cout() << eids[i];
        DGM::Comm::World->cout() << " and point " << P << endl;
      }
    }
    /// Destructor
    ~Delta() {}
    /// Evaluate at a Point
    virtual Scalar operator() (const Point &C) const {
      if (C == P) return 1.0;
      return 0.0;
    }
    /// Add to an Element
    virtual void addScaled(Element *E, const Scalar value) const {
      E->add_Dirac_delta(P,value);
    }
    virtual Scalar apply(const Field *F, const Scalar factor=1.0) {
      Scalar r=0;
      if (L.empty()) fill_L(F);
      for (size_t eid=0; eid<eids.size(); ++eid) {
        const Ordinal eidx = F->partition->inc(eids[eid]);
        const Element *E = F->el[eidx];
        r += factor*E->interpolate_local_point(L[eid]);
      }
      return r;
    }
    /// Evaluate on a Field
    virtual void addScaled(Field *F, const Scalar value) const {
      if (L.empty()) fill_L(F);
      for (size_t eid=0; eid<eids.size(); ++eid) {
        const Ordinal eidx = F->partition->inc(eids[eid]);
        Element *E = F->el[eidx];
        E->add_local_Dirac_delta(L[eid],value);
      }
    }
  };

  /// GaussianBase spatial kernel
  class GaussianBase : public Kernel {
  protected:
    const Scalar sigma;               ///< Standard deviation, \f$\sigma\f$
    const Scalar twos2i;              ///< \f$ 1/(2\sigma^2)\f$
    const Scalar sr2pi;               ///< \f$ 1/(\sigma \sqrt{2\pi}) \f$
    const Scalar numStdDev;           ///< number of standard deviations
    vector<Size> elements;            ///< active elements for this Kernel
    Ordinal numQuadPts;               ///< number of quadrature pts in support
  public:
    static const int NSIGMA = 5;      ///< default number of std dev.
    /// Shared pointer type
    typedef DGM::Shared<GaussianBase>::Ptr Ptr;
    /// Constructor
    GaussianBase(const Scalar _sigma, const Scalar x_0, const Scalar y_0,
             const Scalar z_0, const Scalar num_std_dev=NSIGMA)
      : Kernel(x_0,y_0,z_0),
        sigma(_sigma),
        twos2i(one/(two*pow(sigma,2))),
        sr2pi(one/(sigma*sqrt(two*pi))),
        numStdDev(num_std_dev),
        numQuadPts(0) { }
    GaussianBase(const Scalar _sigma, const Point _P,
                 const Scalar num_std_dev=NSIGMA)
      : Kernel(_P),
        sigma(_sigma),
        twos2i(one/(two*pow(sigma,2))),
        sr2pi(one/(sigma*sqrt(two*pi))),
        numStdDev(num_std_dev),
        numQuadPts(0) { }
    /// Destructor
    ~GaussianBase() {}
    /// Return the standard deviation
    Scalar get_sigma() const {return sigma;}
    /// Return the number of standard deviations
    Scalar get_numStdDev() const {return numStdDev;}
    /// Evaluate at a Point
    virtual Scalar operator() (const Point &P) const = 0;
    /// Add a scaled kernel at a coordinate to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const = 0;
    /// Add scaled kernel to an Element
    virtual void addScaled(Element *E, const Scalar value) const {
#ifdef DGM_USE_SCALAR_EVALUATOR
      // This barely sped things...likely that the virtual function is too low
      for (Ordinal q=0; q<E->qtot; q++) {
        E->u[q] += value * operator()((*E->C)[q]);
      }
#else
      // This is a vectorized version that hopefully is faster
      addScaled(*E->C,value,E->u);
#endif
    }
    /// Apply the kernel to a Field
    virtual Scalar apply(const Field *F, const Scalar factor=1.0) {
      Scalar result=0.0;
      dVector temporary(F->Qmax); temporary=0.0; dVector integrand;
      if (!elements.empty()) {
        vector<Size>::const_iterator e=elements.begin(), end=elements.end();
        for (; e!=end; ++e) {
          Element *E = F->el[*e];
          integrand.alias(temporary,E->qtot);
          for (Ordinal q=0; q<E->qtot; ++q)
            integrand[q] = this->operator()((*E->C)[q]);
          dvmul( E->u, integrand );
          integrand *= factor;
          result += E->integrate(integrand);
        }
      }
      return result;
    }
    /// Add scaled kernel to a Field
    /** Be smart about where to apply the Kernel if possible. */
    virtual void addScaled(Field *F, const Scalar value) const {
      if (!elements.empty()) {
        // apply the Kernel only to the elements within its support
        vector<Size>::const_iterator i=elements.begin(), end=elements.end();
        for (; i!=end; ++i) {
          Element *E = F->el[*i];
          addScaled(E,value);
        }
      }
    }
    /// Determine if a point is near the kernel
    virtual bool within_distance(const Point &C,
                                 const vector<Scalar> &centroid) {
      Scalar d = pow(C.x-centroid[0],2);
      if (1<centroid.size()) d += pow(C.y-centroid[1],2);
      if (2<centroid.size()) d += pow(C.z-centroid[2],2);
      const bool t = d < pow(numStdDev*sigma,2);
      return t;
    }
    /// Create a list of elements and numqpts within the support of this
    /// Kernel
    virtual void create_element_vector(const vField &U) {
      vector<Scalar> centroid = center();
      elements.clear(); numQuadPts=0;
      for (Ordinal e=0; e<U[0]->ne; e++) {
        Element *E = U[0]->el[e];
        for (Ordinal q=0; q<E->qtot; q++) {
          if (within_distance((*E->C)[q], centroid)) {
            elements.push_back(e);
            // cout<<"Adding element id = "<<E->gid()<<endl;
            break;
          }
        }
        for (Ordinal q=0; q<E->qtot; q++) {
          if (within_distance((*E->C)[q], centroid)) numQuadPts++;
        }
      }
    }
    /// Return the number of elements in the element list
    virtual size_t get_number_elements() const {
      return elements.size();
    }
    /// Return the number of quadrature points
    virtual Ordinal get_number_quadrature_points() const {
      return numQuadPts;
    }
  protected:
    static Scalar Exp(const Scalar arg) {
      return ( arg > -34.0 ? exp(arg) : 1.0e-15 );
    }
  };

  /// Gaussian 1d kernel
  class Gaussian1d : public GaussianBase {
  public:
    /// Constructor
    Gaussian1d(const Scalar _sigma, const Scalar x_0,
               const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x_0,0,0,num_std_dev) { }
    /// Vector constructor
    Gaussian1d(const Scalar _sigma, const Point &x,
               const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x.x,0,0,num_std_dev) { }
    /// Destructor
    ~Gaussian1d() {}
    /// Evaluate at a Point
    virtual Scalar operator() (const Point &C) const {
      return sr2pi*Exp(-(pow(C.x-x0,2))*twos2i);
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*sr2pi;
      for (Ordinal i=0; i<C.size(); ++i) {
        u[i] += fact*Exp(-(pow(C.x[i]-x0,2))*twos2i);
      }
    }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(1);
      centroid[0] = x0;
      return centroid;
    }
  };

  /// Gaussian 2d spatial kernel
  class Gaussian2d : public GaussianBase {
    const Scalar sr2pi2;
  public:
    /// Constructor
    Gaussian2d(const Scalar _sigma, const Scalar x_0, const Scalar y_0,
               const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x_0,y_0,0,num_std_dev), sr2pi2(pow(sr2pi,2)) { }
    /// Vector constructor
    Gaussian2d(const Scalar _sigma, const Point &x,
               const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x.x,x.y,0,num_std_dev), sr2pi2(pow(sr2pi,2)) { }
    /// Destructor
    ~Gaussian2d() {}
    /// Evaluate at a Point
    virtual Scalar operator() ( const Point &C) const {
      return sr2pi2*Exp(-(pow(C.x-x0,2)+pow(C.y-y0,2))*twos2i);
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*sr2pi2;
      for (Ordinal i=0; i<C.size(); ++i) {
        u[i] += fact*Exp(-(pow(C.x[i]-x0,2)+pow(C.y[i]-y0,2))*twos2i);
      }
    }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(2);
      centroid[0] = x0; centroid[1] = y0;
      return centroid;
    }
  };

  /// Gaussian 3d spatial kernel
  class Gaussian3d : public GaussianBase {
    const Scalar sr2pi3;
  public:
    /// Constructor
    Gaussian3d(const Scalar _sigma, const Scalar x_0, const Scalar y_0,
               const Scalar z_0, const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x_0,y_0,z_0,num_std_dev), sr2pi3(pow(sr2pi,3)) { }
    /// Vector Constructor
    Gaussian3d(const Scalar _sigma, const Point &x,
               const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma,x.x,x.y,x.z,num_std_dev), sr2pi3(pow(sr2pi,3)) { }
    /// Destructor
    ~Gaussian3d() {}
    /// Evaluate at a Point
    virtual Scalar operator() (const Point &C) const {
      return sr2pi3*Exp(-(pow(C.x-x0,2)+pow(C.y-y0,2)+pow(C.z-z0,2))*twos2i);
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*sr2pi3;
      for (Ordinal q=0; q<u.size(); ++q) {
        u[q] += fact*Exp(-(pow(C.x[q]-x0,2)+pow(C.y[q]-y0,2)+
                pow(C.z[q]-z0,2))*twos2i);
      }
    }
  };

  /// Gaussian line spatial kernel in two-dimensions
  /** This is used to make a line source that has a Gaussian profile in the
      cross direction. */
  class GaussianLine2d : public GaussianBase {
   public:
    enum Direction { Xdirection, Ydirection };
    /// Constructor
    GaussianLine2d(const Scalar _sigma, const Scalar a,
                   const Direction dir=Xdirection)
      : GaussianBase(_sigma,(dir==Ydirection ? a : 0),
                        (dir==Xdirection ? a : 0), 0 ), _dir(dir) { }
    /// Destructor
    ~GaussianLine2d() {}
    /// Evaluate at a Point
    virtual Scalar operator()(const Point &C) const {
      switch (_dir) {
      case Xdirection:
        return sr2pi*Exp(-(pow(C.y-y0,2))*twos2i);
        break;
      case Ydirection:
        return sr2pi*Exp(-(pow(C.x-x0,2))*twos2i);
        break;
      default:
        throw DGM::exception("GaussianLine2d unknown direction");
        break;
      }
      return 0.0;
    }
    /// Add a scaled kernel to the supplied vector at the supplied coordinates
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      const Scalar fact = value*sr2pi;
      switch (_dir) {
      case Xdirection:
        for (Ordinal i=0; i<u.size(); ++i) {
          u[i] += fact*Exp(-(pow(C.y[i]-y0,2))*twos2i);
        }
        break;
      case Ydirection:
        for (Ordinal i=0; i<u.size(); ++i) {
          u[i] += fact*Exp(-(pow(C.x[i]-x0,2))*twos2i);
        }
        break;
      default:
        throw DGM::exception("GaussianLine2d unknown direction");
        break;
      }
    }
    /// Determine if a point is near the kernel
    virtual bool within_distance(const Point &C,
                                 const vector<Scalar> &centroid) {
      switch (_dir) {
      case Xdirection: {
        Scalar d = pow(C.y-centroid[1],2);
        return d < pow(numStdDev*sigma,2);
        break;
      }
      case Ydirection: {
        Scalar d = pow(C.x-centroid[0],2);
        return d < pow(numStdDev*sigma,2);
        break;
      }
      default:
        throw DGM::exception("GaussianLine2d unknown direction");
        break;
      }
      return false;
    }
   private:
    const Direction _dir;
  };

  /// Gaussian line-segment spatial kernel in two-dimensions
  /** This is used to make a line-segment source that has a Gaussian
      profile in the cross direction from the line segment and from
      the end points. */
  class GaussianLineSegment2d : public GaussianBase {
   public:
    const Point P1;           ///< end point of the line segment
    const Point P2;           ///< end point of the line segment
    const Scalar length_sq;   ///< squared length between end points.
    const Scalar sr2pi2;
    /// Constructor
    GaussianLineSegment2d(const Scalar _sigma,
                          const Point & _P1,
                          const Point & _P2,
                          const Scalar _num_std_dev=NSIGMA )
      : GaussianBase(_sigma, midpoint(_P1,_P2), _num_std_dev), P1(_P1),
        P2(_P2), length_sq(distance_sq(P1, P2)), sr2pi2(pow(sr2pi,2)) {}
    /// Destructor
    ~GaussianLineSegment2d() {}
    /// Evaluate the distance between the line segment and a point.
    /** t - a scaled projection length. t<0 => beyond P1; t>1 => beyond P2. */
    Scalar LS_distance(const Point &C) const {
      if (length_sq == zero) return distance(P1, C);
      const Scalar t = dot(C-P1, P2-P1)/length_sq;
      if (t < zero) return distance(P1, C);     // beyond P1
      else if (t > one) return distance(P2, C); // beyond P2
      const Point pj = t*(P2-P1) + P1;          // proj. onto line segment
      return distance(pj, C);
    }
    /// Evaluate at a Point
    virtual Scalar operator()(const Point &C) const {
      const Scalar D = LS_distance(C);
      Scalar result = sr2pi2*Exp(-(pow(D,2))*twos2i);
      return result;
    }
    /// Add a scaled kernel to the supplied vector at the supplied coordinates
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      for (Ordinal i=0; i<C.size(); ++i) {
        const Point c(C.x[i],C.y[i],zero);
        u[i] += value*(*this)(c);
      }
    }
    /// Determine if a point is near the kernel
    virtual bool within_distance(const Point &C,
                                 const vector<Scalar> &centroid) {
      const bool t = LS_distance(C) < numStdDev*sigma;
      return t;
    }

    /// Reader for JSON 2D GaussianLineSegment
    static std::vector<GaussianLineSegment2d *>
    reader(const Json::Value &json,
           const Scalar nsd,
           const DGM::Comm::Ptr comm,
           const Ordinal verb=0);
  };

  /// GaussianEllipseBase spatial kernel
  class GaussianEllipseBase : public GaussianBase {
  protected:
    const Scalar sigma1;         ///< Standard deviation in direction 1
    const Scalar sigma2;         ///< Standard deviation in direction 2
    const Scalar sigma3;         ///< Standard deviation in direction 3

    const Ordinal deriv1;        ///< Order of derivative in direction 1
    const Ordinal deriv2;        ///< Order of derivative in direction 2
    const Ordinal deriv3;        ///< Order of derivative in direction 3

    const Scalar twos1_2i;       ///< \f$1/(2\sigma_1^2)\f$
    const Scalar twos2_2i;       ///< \f$1/(2\sigma_2^2)\f$
    const Scalar twos3_2i;       ///< \f$1/(2\sigma_3^2)\f$

    const Scalar s1_r2pi;        ///< \f$1/(\sigma_1\sqrt{2\pi})\f$
    const Scalar s2_r2pi;        ///< \f$1/(\sigma_2\sqrt{2\pi})\f$
    const Scalar s3_r2pi;        ///< \f$1/(\sigma_3\sqrt{2\pi})\f$

    std::vector<Scalar> unit1;   ///< unit vector in direction 1
    std::vector<Scalar> unit2;   ///< unit vector in direction 2
    std::vector<Scalar> unit3;   ///< unit vector in direction 3

    const Scalar numStdDev;      ///< number of standard deviations

    vector<Size> elements;       ///< active elements for this Kernel
    Ordinal numQuadPts;          ///< number of quadrature pts in support

  public:
    static const int NSIGMA = 5; ///< default number of std dev.

    /// Constructor
    GaussianEllipseBase(const Scalar x_0, const Scalar y_0, const Scalar z_0,
                        const Scalar _sigma1, const Scalar _sigma2=-1.0,
                        const Scalar _sigma3=-1.0,
                        const Ordinal _deriv1=0, const Ordinal _deriv2=0,
                        const Ordinal _deriv3=0,
                        const Scalar _dir1x=1.0, const Scalar _dir1y=0.0,
                        const Scalar _dir1z=0.0,
                        const Scalar _dir2x=0.0, const Scalar _dir2y=1.0,
                        const Scalar _dir2z=0.0,
                        const Scalar _dir3x=0.0, const Scalar _dir3y=0.0,
                        const Scalar _dir3z=1.0,
                        const Scalar num_std_dev=NSIGMA)
      : GaussianBase(_sigma1,x_0,y_0,z_0,num_std_dev),
        sigma1(_sigma1),
        sigma2(_sigma2==-1.0 ? _sigma1 : _sigma2),
        sigma3(_sigma3==-1.0 ? _sigma1 : _sigma3),
        deriv1(_deriv1),
        deriv2(_deriv2),
        deriv3(_deriv3),
        twos1_2i(one/(two*pow(sigma1,2))),
        twos2_2i(one/(two*pow(sigma2,2))),
        twos3_2i(one/(two*pow(sigma3,2))),
        s1_r2pi(one/(sigma1*sqrt(two*pi))),
        s2_r2pi(one/(sigma2*sqrt(two*pi))),
        s3_r2pi(one/(sigma3*sqrt(two*pi))),
        numStdDev(num_std_dev),
        numQuadPts(0) {
      vector<Scalar> centroid = center();

      // Check sigmas for errors
      if (sigma1 <= 0.0) error("GaussianEllipseBase: sigma1 <= 0.0");

      // Make unit vectors
      Scalar norm1 = pow(_dir1x,2);
      Scalar norm2 = 1.0;
      Scalar norm3 = 1.0;
      if (1<centroid.size()) {
        norm1 += pow(_dir1y,2);
        norm2  = pow(_dir2x,2) + pow(_dir2y,2);
      }
      if (2<centroid.size()) {
        norm1 += pow(_dir1z,2);
        norm2 += pow(_dir2z,2);
        norm3  = pow(_dir3x,2) + pow(_dir3y,2) + pow(_dir3z,2);
      }

      if (norm1 <= 0.0) error("GaussianEllipseBase: norm1 <= 0.0");
      unit1.push_back(_dir1x/norm1);
      if (1<centroid.size()) {
        if (norm2 <= 0.0) error("GaussianEllipseBase: norm2 <= 0.0");
        unit1.push_back(_dir1y/norm1);
        unit2.push_back(_dir2x/norm2);
        unit2.push_back(_dir2y/norm2);
      }
      if (2<centroid.size()) {
        if (norm3 <= 0.0) error("GaussianEllipseBase: norm3 <= 0.0");
        unit1.push_back(_dir1z/norm1);
        unit2.push_back(_dir2z/norm2);
        unit3.push_back(_dir3x/norm3);
        unit3.push_back(_dir3y/norm3);
        unit3.push_back(_dir3z/norm3);
      }
    }

    /// Destructor
    ~GaussianEllipseBase() {}

    /// Evaluate at a Point
    virtual Scalar operator() (const Point &P) const = 0;

    /// Add a scaled kernel at a coordinate to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const = 0;

    /// Determine if a point is near the kernel
    virtual bool within_distance(const Point &C,
                                 const vector<Scalar> &centroid) {
      Scalar d1 = unit1[0]*(C.x-centroid[0]);
      Scalar d2 = 0.0;
      Scalar d3 = 0.0;
      if (1<centroid.size()) {
        d1 += unit1[1]*(C.y-centroid[1]);
        d2 += unit2[0]*(C.x-centroid[0]) + unit2[1]*(C.y-centroid[1]);
      }
      if (2<centroid.size()) {
        d1 += unit1[2]*(C.z-centroid[2]);
        d2 += unit2[2]*(C.z-centroid[2]);
        d3 += unit3[0]*(C.x-centroid[0]) + unit3[1]*(C.y-centroid[1]) +
                     unit3[2]*(C.z-centroid[2]);
      }

      Scalar d = pow(d1,2)/pow(sigma1,2);
      if (1<centroid.size()) d += pow(d2,2)/pow(sigma2,2);
      if (2<centroid.size()) d += pow(d3,2)/pow(sigma3,2);
      const bool t = d < pow(numStdDev,2);
      return t;
    }
  };

  /// Gaussian Ellipse 1d spatial kernel
  class GaussianEllipse1d : public GaussianEllipseBase {
  public:
    /// Constructor
    GaussianEllipse1d(const Scalar x_0,
               const Scalar _sigma1,
               const Ordinal _deriv1,
               const Scalar num_std_dev=NSIGMA)
      : GaussianEllipseBase(x_0, 0.0, 0.0,
          _sigma1, -1.0, -1.0,
          _deriv1, 0, 0,
          1.0, 0.0, 0.0,
          0.0, 1.0, 0.0,
          0.0, 0.0, 1.0,
          num_std_dev) {}

    /// Vector constructor
    GaussianEllipse1d(const Point &x,
               const Scalar _sigma1,
               const Ordinal _deriv1,
               const Scalar num_std_dev=NSIGMA)
      : GaussianEllipseBase(x.x, 0.0, 0.0,
          _sigma1, -1.0, -1.0,
          _deriv1, 0, 0,
          1.0, 0.0, 0.0,
          0.0, 1.0, 0.0,
          0.0, 0.0, 1.0,
          num_std_dev) {}

    /// Destructor
    ~GaussianEllipse1d() {}
    /// Evaluate at a Point
    virtual Scalar operator() ( const Point &C) const {
      const Scalar d1 = (C.x-x0);

      Scalar result = s1_r2pi*Exp(-(twos1_2i*pow(d1,2)));

      if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
      else if (deriv1 == 2) result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
      else if (deriv1 > 2)
        error("GaussianEllipse1d: Only derivatives up to order "
              "2 supported.");

      return result;
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*s1_r2pi;
      for (Ordinal i=0; i<C.size(); ++i) {
        const Scalar d1 = (C.x[i]-x0);
        Scalar result = fact*Exp(-(twos1_2i*pow(d1,2)));
        if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
        else if (deriv1 == 2)
          result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
        else if (deriv1 > 2)
          error("GaussianEllipse1d: Only derivatives up to "
                "order 2 supported.");
        u[i] += result;
      }
    }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(2);
      centroid[0] = x0; centroid[1] = y0;
      return centroid;
    }
  };

  /// Gaussian Ellipse 2d spatial kernel
  class GaussianEllipse2d : public GaussianEllipseBase {
  public:
    /// Constructor
    GaussianEllipse2d(const Scalar x_0, const Scalar y_0,
                      const Scalar _sigma1, const Scalar _sigma2=-1.0,
                      const Ordinal _deriv1=0, const Ordinal _deriv2=0,
                      const Scalar _dir1x=1.0, const Scalar _dir1y=0.0,
                      const Scalar _dir2x=0.0, const Scalar _dir2y=1.0,
                      const Scalar num_std_dev=NSIGMA)
      : GaussianEllipseBase(x_0, y_0, 0.0,
                            _sigma1, _sigma2, -1.0,
                            _deriv1, _deriv2, 0,
                            _dir1x, _dir1y, 0.0,
                            _dir2x, _dir2y, 0.0,
                            0.0,    0.0,    1.0,
                            num_std_dev) {}

    /// Vector constructor
    GaussianEllipse2d(const Point &x,
                      const Scalar _sigma1, const Scalar _sigma2=-1.0,
                      const Ordinal _deriv1=0, const Ordinal _deriv2=0,
                      const Scalar _dir1x=1.0, const Scalar _dir1y=0.0,
                      const Scalar _dir2x=0.0, const Scalar _dir2y=1.0,
                      const Scalar num_std_dev=NSIGMA)
      : GaussianEllipseBase(x.x, x.y, 0.0,
                            _sigma1, _sigma2, -1.0,
                            _deriv1, _deriv2, 0,
                            _dir1x, _dir1y, 0.0,
                            _dir2x, _dir2y, 0.0,
                            0.0,    0.0,    1.0,
                            num_std_dev) {}

    /// Destructor
    ~GaussianEllipse2d() {}
    /// Evaluate at a Point
    virtual Scalar operator() ( const Point &C) const {
      const Scalar d1 = unit1[0]*(C.x-x0) + unit1[1]*(C.y-y0);
      const Scalar d2 = unit2[0]*(C.x-x0) + unit2[1]*(C.y-y0);

      Scalar result = s1_r2pi*s2_r2pi*
        Exp(-(twos1_2i*pow(d1,2)+twos2_2i*pow(d2,2)));

      if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
      else if (deriv1 == 2) result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
      else if (deriv1 > 2)
        error("GaussianEllipse2d: Only derivatives up to order "
              "2 supported.");

      if (deriv2 == 1) result *= -2.0*twos2_2i*d2;
      else if (deriv2 == 2) result *= -2.0*twos2_2i*(1.0-2.0*twos2_2i*d2*d2);
      else if (deriv2 > 2)
        error("GaussianEllipse2d: Only derivatives up to order "
              "2 supported.");

      return result;
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*s1_r2pi*s2_r2pi;
      for (Ordinal i=0; i<C.size(); ++i) {
        const Scalar d1 = unit1[0]*(C.x[i]-x0) + unit1[1]*(C.y[i]-y0);
        const Scalar d2 = unit2[0]*(C.x[i]-x0) + unit2[1]*(C.y[i]-y0);
        Scalar result = fact*
          Exp(-(twos1_2i*pow(d1,2)+twos2_2i*pow(d2,2)));

        if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
        else if (deriv1 == 2)
          result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
        else if (deriv1 > 2)
          error("GaussianEllipse2d: Only derivatives up to order "
                "2 supported.");

        if (deriv2 == 1) result *= -2.0*twos2_2i*d2;
        else if (deriv2 == 2)
          result *= -2.0*twos2_2i*(1.0-2.0*twos2_2i*d2*d2);
        else if (deriv2 > 2)
          error("GaussianEllipse2d: Only derivatives up to order "
                "2 supported.");

        u[i] += result;
      }
    }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(2);
      centroid[0] = x0; centroid[1] = y0;
      return centroid;
    }
  };

  /// Gaussian Ellipse 3d spatial kernel
  class GaussianEllipse3d : public GaussianEllipseBase {
  public:
    /// Constructor
    GaussianEllipse3d(const Scalar x_0, const Scalar y_0,
                      const Scalar z_0,
                      const Scalar _sigma1, const Scalar _sigma2=-1.0,
                      const Scalar _sigma3=-1.0,
                      const Ordinal _deriv1=0, const Ordinal _deriv2=0,
                      const Ordinal _deriv3=0,
                      const Scalar _dir1x=1.0, const Scalar _dir1y=0.0,
                      const Scalar _dir1z=0.0,
                      const Scalar _dir2x=0.0, const Scalar _dir2y=1.0,
                      const Scalar _dir2z=0.0,
                      const Scalar _dir3x=0.0, const Scalar _dir3y=0.0,
                      const Scalar _dir3z=1.0,
                      const Scalar num_std_dev=NSIGMA)
    : GaussianEllipseBase(x_0, y_0, z_0,
                          _sigma1, _sigma2, _sigma3,
                          _deriv1, _deriv2, _deriv3,
                          _dir1x, _dir1y, _dir1z,
                          _dir2x, _dir2y, _dir2z,
                          _dir3x, _dir3y, _dir3z,
                          num_std_dev) {}

    /// Vector constructor
    GaussianEllipse3d(const Point &x,
                      const Scalar _sigma1, const Scalar _sigma2=-1.0,
                      const Scalar _sigma3=-1.0,
                      const Ordinal _deriv1=0, const Ordinal _deriv2=0,
                      const Ordinal _deriv3=0,
                      const Scalar _dir1x=1.0, const Scalar _dir1y=0.0,
                      const Scalar _dir1z=0.0,
                      const Scalar _dir2x=0.0, const Scalar _dir2y=1.0,
                      const Scalar _dir2z=0.0,
                      const Scalar _dir3x=0.0, const Scalar _dir3y=0.0,
                      const Scalar _dir3z=1.0,
                      const Scalar num_std_dev=NSIGMA)
    : GaussianEllipseBase(x.x, x.y, x.z,
                          _sigma1, _sigma2, _sigma3,
                          _deriv1, _deriv2, _deriv3,
                          _dir1x, _dir1y, _dir1z,
                          _dir2x, _dir2y, _dir2z,
                          _dir3x, _dir3y, _dir3z,
                          num_std_dev) {}

    /// Destructor
    ~GaussianEllipse3d() {}
    /// Evaluate at a Point
    virtual Scalar operator() ( const Point &C) const {
      const Scalar d1 = unit1[0]*(C.x-x0) + unit1[1]*(C.y-y0) +
                        unit1[2]*(C.z-z0);
      const Scalar d2 = unit2[0]*(C.x-x0) + unit2[1]*(C.y-y0) +
                        unit2[2]*(C.z-z0);
      const Scalar d3 = unit3[0]*(C.x-x0) + unit3[1]*(C.y-y0) +
                        unit3[2]*(C.z-z0);
      Scalar result = s1_r2pi*s2_r2pi*s3_r2pi*
        Exp(-(twos1_2i*pow(d1,2)+twos2_2i*pow(d2,2)+twos3_2i*pow(d3,2)));

      if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
      else if (deriv1 == 2) result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
      else if (deriv1 > 2)
        error("GaussianEllipse3d: Only derivatives up to order "
              "2 supported.");

      if (deriv2 == 1) result *= -2.0*twos2_2i*d2;
      else if (deriv2 == 2) result *= -2.0*twos2_2i*(1.0-2.0*twos2_2i*d2*d2);
      else if (deriv2 > 2)
        error("GaussianEllipse3d: Only derivatives up to order "
              "2 supported.");

      if (deriv3 == 1) result *= -2.0*twos3_2i*d3;
      else if (deriv3 == 2) result *= -2.0*twos3_2i*(1.0-2.0*twos3_2i*d3*d3);
      else if (deriv3 > 2)
        error("GaussianEllipse3d: Only derivatives up to order "
              "2 supported.");

      return result;
    }
    /// Evaluate, scale and add to a vector
    virtual void addScaled(const Coord &C, const Scalar value,
                           dVector &u) const {
      // assert( C.size() == u.size() );
      const Scalar fact = value*s1_r2pi*s2_r2pi*s3_r2pi;
      for (Ordinal i=0; i<C.size(); ++i) {
        const Scalar d1 = unit1[0]*(C.x[i]-x0) + unit1[1]*(C.y[i]-y0) +
                          unit1[2]*(C.z[i]-z0);
        const Scalar d2 = unit2[0]*(C.x[i]-x0) + unit2[1]*(C.y[i]-y0) +
                          unit2[2]*(C.z[i]-z0);
        const Scalar d3 = unit3[0]*(C.x[i]-x0) + unit3[1]*(C.y[i]-y0) +
                          unit3[2]*(C.z[i]-z0);

        Scalar result = fact*
          Exp(-(twos1_2i*pow(d1,2)+twos2_2i*pow(d2,2)+twos2_2i*pow(d3,2)));

        if (deriv1 == 1) result *= -2.0*twos1_2i*d1;
        else if (deriv1 == 2)
          result *= -2.0*twos1_2i*(1.0-2.0*twos1_2i*d1*d1);
        else if (deriv1 > 2)
          error("GaussianEllipse3d: Only derivatives up to order "
                "2 supported.");

        if (deriv2 == 1) result *= -2.0*twos2_2i*d2;
        else if (deriv2 == 2)
          result *= -2.0*twos2_2i*(1.0-2.0*twos2_2i*d2*d2);
        else if (deriv2 > 2)
          error("GaussianEllipse3d: Only derivatives up to order "
                "2 supported.");

        if (deriv3 == 1) result *= -2.0*twos3_2i*d3;
        else if (deriv3 == 2)
          result *= -2.0*twos3_2i*(1.0-2.0*twos3_2i*d3*d3);
        else if (deriv3 > 2)
          error("GaussianEllipse3d: Only derivatives up to order "
                "2 supported.");

        u[i] += result;
      }
    }
    /// Return the center of the kernel
    virtual std::vector<Scalar> center() const {
      std::vector<Scalar> centroid(3);
      centroid[0] = x0; centroid[1] = y0; centroid[2]=z0;
      return centroid;
    }
  };

  //==========================================================================
  //                       K e r n e l R e s p o n s e
  //==========================================================================

  /// Kernel class for use in Response functions
  /** I am not sure why this is different from the standard Kernel.  The idea
    * Why not have a base class for Kernel and one for a Sensor or somesuch
    */
  class KernelResponse {
  public :
    typedef DGM::Shared<KernelResponse>::Ptr Ptr;
    KernelResponse(const Size i, const std::string &name, const Point C);
    virtual ~KernelResponse();

    Ordinal element_index(const Ordinal i) const {return eidx[i];}
    Size    global_id         () const {return  gid;}
    std::string name          () const {return  identifier;}
    Point   center_of_kernel  () const {return  center;}
    Ordinal size              () const {
      return  numeric_cast<Ordinal>(eidx.size());
    }
    bool    locally_evaluated () const {return !eidx.empty();}
    Ordinal owning_processor  () const {return  proc_with_center;}
    Ordinal divide_for_average() const {return  multiplicity;}
    bool    multiple_processor() const {return  multi_processor;}
    bool    owned_by_this_proc() const {return  center_on_proc;}
    DGM::Comm::Ptr        comm() const {return  probe_comm;}

    virtual Scalar evaluate(const Field *F) const = 0;
    virtual Scalar integrate_probes(const Field *F) = 0;
    virtual bool get_interp_matrix(vector<dMatrix> &interp,
                                   const Ordinal i)=0;
    virtual Point get_local_coord(const Ordinal i) const = 0;
    virtual void addScaled(Field *F, const Scalar amp) const = 0;

    Kernel * get() { return base_kernel.get(); }
    
    virtual void json_output(Json::Value &json) const {
      json["Name"] = name();
      json["ID"] = global_id();
      json["Size"] = size();
      json["Center"] = Json::Value(Json::arrayValue);
      json["Center"].resize(3);
      json["Center"][0] = center_of_kernel().x;
      json["Center"][1] = center_of_kernel().y;
      json["Center"][2] = center_of_kernel().z;
    }
  protected :
    const Size           gid;
    const std::string    identifier;
    const Point          center;
    std::vector<Ordinal> eidx;                    ///< element index number
    Ordinal              proc_with_center;
    Ordinal              multiplicity;
    bool                 center_on_proc;
    bool                 multi_processor;
    Kernel::Ptr          base_kernel;
    DGM::Comm::Ptr       probe_comm;
  };

  /// Gaussian spatial kernel
  class GaussianResponse : public KernelResponse {
    std::vector<dVector> local_gaussian_coeff;
    mutable dVector      workspace;
  public:
    /// Constructor
    GaussianResponse(const Size global_id,
                     const std::string &name,
                     const Point C,
                     const Field *F,
                     const vector<Size> &elem,
                     const Scalar _sigma,
                     const Scalar num_std_dev=GaussianBase::NSIGMA);

    /// Destructor
    virtual ~GaussianResponse() {}

    /// Output information in Json format
    virtual void json_output(Json::Value &json) const {
      KernelResponse::json_output(json);
      GaussianBase *kernel = dynamic_cast<GaussianBase*>(base_kernel.get());
      json["Sigma"] = kernel->get_sigma();
      json["Number of standard deviations"] = kernel->get_numStdDev();
    }
    
    /// evaluate the kernel to a Field
    virtual Scalar evaluate(const Field *F) const {
      Scalar X = 0;
      for (Ordinal k=0; k<size(); ++k) {
        const Element *el = F->el[element_index(k)];
        dVector T; T.clone(el->u);
        T *= local_gaussian_coeff[k];
        X += el->integrate(T);
      }
      return X;
    }

    virtual void addScaled(Field *F, const Scalar amp) const {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);
      for (Ordinal j=0; j<size(); ++j) {
        Element *el = F->el[element_index(j)];
        dVector tmp(workspace, el->qtot);
        tmp = local_gaussian_coeff[j];
        tmp *= amp;
        el->u += tmp;
      }
    }

    virtual Scalar integrate_probes(const Field *F) {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);
      Scalar integrand = 0;
      for (Ordinal j=0; j<size(); ++j) {
        const Element *el = F->el[element_index(j)];
        dVector tmp(workspace,el->qtot);
        tmp  = local_gaussian_coeff[j];
        tmp *= el->u;
        integrand += el->integrate(tmp);
      }
      return integrand;
    }

    virtual bool get_interp_matrix(vector<dMatrix> &interp,
                                   const Ordinal i) {
      const Ordinal size = local_gaussian_coeff[i].size();
      interp.resize(1);
      interp[0].alias(local_gaussian_coeff[i], 1, size);
      return true;
    }

    virtual Point get_local_coord(const Ordinal) const {
      DGM_UNDEFINED;
      return Point();
    }

  };

  /// Gaussian Ellipse spatial kernel
  class GaussianEllipseResponse : public KernelResponse {
    std::vector<dVector> local_gaussian_coeff;
    mutable dVector      workspace;
  public:
    /// Constructor
    GaussianEllipseResponse(const Size global_id,
                            const std::string &name,
                            const Point C,
                            const Field *F,
                            const dMatrix &directions,
                            const Ordinal derivatives[3],
                            const Scalar _sigma[3],
                            const Scalar num_std_dev=GaussianBase::NSIGMA);

    /// Destructor
    virtual ~GaussianEllipseResponse() {}

    /// evaluate the kernel to a Field
    virtual Scalar evaluate(const Field *F) const {
      Scalar X = 0;
      for (Ordinal k=0; k<size(); ++k) {
        const Element *el = F->el[element_index(k)];
        dVector   T; T.clone(el->u);
        T *= local_gaussian_coeff[k];
        X += el->integrate(T);
      }
      return X;
    }

    virtual void addScaled(Field *F, const Scalar amp) const {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);

      for (Ordinal j=0; j<size(); ++j) {
        Element *el = F->el[element_index(j)];
        dVector tmp(workspace, el->qtot);
        tmp    = local_gaussian_coeff[j];
        tmp   *= amp;
        el->u += tmp;
      }
    }

    virtual Scalar integrate_probes(const Field *F) {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);

      Scalar integrand = 0;
      for (Ordinal j=0; j<size(); ++j) {
        const Element *el = F->el[element_index(j)];
        dVector tmp(workspace,el->qtot);
        tmp  = local_gaussian_coeff[j];
        tmp *= el->u;
        integrand += el->integrate(tmp);
      }
      return integrand;
    }

    virtual bool get_interp_matrix(vector<dMatrix> &interp,
                                   const Ordinal i) {
      const Ordinal size = local_gaussian_coeff[i].size();
      interp.resize(1);
      interp[0].alias(local_gaussian_coeff[i], 1, size);
      return true;
    }

    virtual Point get_local_coord(const Ordinal) const {
      DGM_UNDEFINED;
      return Point();
    }

  };

  /// Gaussian Line Segment 2D response spatial kernel
  class GaussianLineSegment2dResponse : public KernelResponse {
    std::vector<dVector> local_gaussian_coeff;
    mutable dVector      workspace;
  public:
    /// Constructor
    GaussianLineSegment2dResponse(const Size global_id,
                                  const std::string &name,
                                  const Field *F,
                                  GaussianLineSegment2d *gls);

    /// Destructor
    virtual ~GaussianLineSegment2dResponse() {}

    /// evaluate the kernel to a Field
    virtual Scalar evaluate(const Field *F) const {
      Scalar X = 0;
      for (Ordinal k=0; k<size(); ++k) {
        const Element *el = F->el[element_index(k)];
        dVector   T; T.clone(el->u);
        T *= local_gaussian_coeff[k];
        X += el->integrate(T);
      }
      return X;
    }

    virtual void addScaled(Field *F, const Scalar amp) const {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);

      for (Ordinal j=0; j<size(); ++j) {
        Element *el = F->el[element_index(j)];
        dVector tmp(workspace, el->qtot);
        tmp    = local_gaussian_coeff[j];
        tmp   *= amp;
        el->u += tmp;
      }
    }

    virtual Scalar integrate_probes(const Field *F) {
      if (workspace.size() < F->Qmax) workspace.resize(F->Qmax);

      Scalar integrand = 0;
      for (Ordinal j=0; j<size(); ++j) {
        const Element *el = F->el[element_index(j)];
        dVector tmp(workspace,el->qtot);
        tmp  = local_gaussian_coeff[j];
        tmp *= el->u;
        integrand += el->integrate(tmp);
      }
      return integrand;
    }

    virtual bool get_interp_matrix(vector<dMatrix> &interp,
                                   const Ordinal i) {
      const Ordinal size = local_gaussian_coeff[i].size();
      interp.resize(1);
      interp[0].alias(local_gaussian_coeff[i], 1, size);
      return true;
    }

    virtual Point get_local_coord(const Ordinal) const {
      DGM_UNDEFINED;
      return Point();
    }

  };

  /// Delta spatial kernel
  class DeltaResponse : public KernelResponse {
    std::vector<Point>                 local_coordinates;
    std::vector<std::vector<dMatrix> > local_interpolate;

  public:
    /// Constructor
    DeltaResponse(const Size global_id,
                  const std::string &name,
                  const Point C,
                  const Field *F,
                  const vector<Size> &elem,
                  const bool average);

    /// Destructor
    virtual ~DeltaResponse() {}

    /// evaluate the kernel to a Field
    virtual Scalar evaluate(const Field *F) const {
      Scalar X = 0;
      if (local_interpolate.empty() || local_interpolate[0].empty()) {
        X = base_kernel->apply(F, 1.);
      } else {
        dVector V(1,0);
        for (Ordinal k=0; k<size(); ++k) {
          const Element *el = F->el[element_index(k)];
          el->apply_interpolation_matrices(V,local_interpolate[k]);
          X += V[0];
        }
      }
      return X;
    }

    virtual void addScaled(Field *F, const Scalar amp) const {
      if (local_interpolate.empty() || local_interpolate[0].empty()) {
        for (Ordinal j=0; j<size(); ++j) {
          const Ordinal  eidx = element_index(j);
          const Point    &xpt = get_local_coord(j);
          F->el[eidx]->add_local_Dirac_delta(xpt, amp);
        }
      } else {
        for (Ordinal j=0; j<size(); ++j) {
          const Ordinal  eidx = element_index(j);
          F->el[eidx]->add_local_Dirac_delta(local_interpolate[j], amp);
        }
      }
    }

    virtual Scalar integrate_probes(const Field *F) {
      Scalar integrand = 0;
      if (local_interpolate.empty() || local_interpolate[0].empty()) {
        for (Ordinal j=0; j<size(); ++j) {
          const Point &xpt = get_local_coord(j);
          integrand += F->el[element_index(j)]->interpolate_local_point(xpt);
        }
      } else {
        dVector V(1,0);
        for (Ordinal j=0; j<size(); ++j) {
          const Element *el = F->el[element_index(j)];
          el->apply_interpolation_matrices(V,local_interpolate[j]);
          integrand += V[0];
        }
      }
      return integrand;
    }

    virtual bool get_interp_matrix(vector<dMatrix> &interp,
                                   const Ordinal i) {
      if (local_interpolate.empty() || local_interpolate[0].empty()) {
        return false;
      } else {
        interp.resize(local_interpolate[i].size());
        for (size_t j=0; j<local_interpolate[i].size(); ++j) {
          interp[j].alias(local_interpolate[i][j]);
        }
        return true;
      }
    }

    virtual Point get_local_coord(const Ordinal i) const {
      return local_coordinates[i];
    }

  private :
    DeltaResponse(const DeltaResponse &);
    DeltaResponse operator=(const DeltaResponse &);
  };

}  // namespace DGM

#endif // DGM_KERNEL_HPP

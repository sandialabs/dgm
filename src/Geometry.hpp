#ifndef DGM_GEOMETRY_HPP
#define DGM_GEOMETRY_HPP

/** \file Geometry.hpp
    \brief Class that holds basic element-level geometry information
    \author Scott Collis and James Overfelt
*/

// System includes
#include <set>
#include <cfloat>
using namespace std;

namespace DGM {

/// Element geometry specification
/*! This class holds the components and determinate of the Jacobian matrix
    that characterizes the mapping from computational coordinates \f$(a,b,c)\f$
    to physical-space coordinates \f$(x,y,z)\f$. */
class Geometry {

public:

  typedef DGM::Shared<Geometry>::Ptr Ptr;  ///< smart pointer

  Size id;        ///< identification number
  Ordinal nsd;    ///< number of space dimensions

  // components of the Jacobian from \f$(r,s,t)\f$ to \f$(x,y,z)\f$
  dVector rx;     ///< \f$\frac{\partial r}{\partial x}\f$ 
  dVector ry;     ///< \f$\frac{\partial r}{\partial y}\f$ 
  dVector rz;     ///< \f$\frac{\partial r}{\partial z}\f$
  dVector sx;     ///< \f$\frac{\partial s}{\partial x}\f$
  dVector sy;     ///< \f$\frac{\partial s}{\partial y}\f$
  dVector sz;     ///< \f$\frac{\partial s}{\partial z}\f$
  dVector tx;     ///< \f$\frac{\partial t}{\partial x}\f$
  dVector ty;     ///< \f$\frac{\partial t}{\partial y}\f$
  dVector tz;     ///< \f$\frac{\partial t}{\partial z}\f$

#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  // This notation means, for example "dx" in the "r"-direction
  dVector dxr;     ///< Metric terms for stability estimates
  dVector dxs;     ///< Metric terms for stability estimates
  dVector dxt;     ///< Metric terms for stability estimates
  dVector dyr;     ///< Metric terms for stability estimates
  dVector dys;     ///< Metric terms for stability estimates
  dVector dyt;     ///< Metric terms for stability estimates
  dVector dzr;     ///< Metric terms for stability estimates
  dVector dzs;     ///< Metric terms for stability estimates
  dVector dzt;     ///< Metric terms for stability estimates
  dVector ivol;    ///< Metric terms for stability estimates
  dVector acoustic;///< Metric terms for stability estimates
#endif // DGM_STORE_METRICS

  dVector J;       ///< Determinant of the Jacobian of mapping

#ifdef DGM_USE_WJ
  dVector wJ;      ///< Quadrature weighted Jacobians
  dVector srwJ;    ///< Quadrature weighted Jacobians
  dVector isrwJ;   ///< Quadrature weighted Jacobians
#endif

  int singular;    ///< flag for singular mapping

  /// default constructor
  Geometry(const Size, const Ordinal, const Ordinal, const Ordinal);

  /// alias copy constructor
  Geometry(Geometry *);

  /// deep copy constructor
  Geometry(const Geometry &g);

  /// approximately equal
  inline bool approx(const Geometry &f, 
                     const Scalar EPS, const Scalar  ABS) const;

  /// approximately less then
  inline bool approx_less(const Geometry &f,
                          const Scalar EPS, const Scalar  ABS) const;

  /// equal
  inline bool operator==(const Geometry &f) const;

  /// not equal
  inline bool operator!=(const Geometry &f) const {
    return (!(*this == f));
  }

  /// less then
  inline bool operator<(const Geometry &f) const;

  /// Defines an equals operator for comparing Geometry classes
  struct EQ : public std::unary_function<const Geometry::Ptr, bool> {
    const Geometry::Ptr &g;
    EQ(const Geometry::Ptr &f) : g(f) {}
    bool operator()(const Geometry::Ptr f) const {
      const bool eq = (*g == *f);
      return eq;
    }
  };

  /// Defines a less than operator for comparing Geometry classes
  struct Less : public std::unary_function<const Geometry::Ptr, bool> {
    bool operator()(const Geometry::Ptr g, const Geometry::Ptr f) const {
      const bool less = (*g < *f);
      return less;
    }
  };

  /// Defines an approximately equal operator for comparing Geometry classes
  struct Approx :
    public std::unary_function<const Geometry::Ptr, bool> {
    const Geometry::Ptr &g;
    Approx(const Geometry::Ptr &f) : g(f) {}
    bool operator()(const Geometry::Ptr f) const {
      const Scalar REL_EPSILON = 5.0*DBL_EPSILON;
      const Scalar ABS_EPSILON = 5.0*DBL_EPSILON;
      const bool eq = g->approx(*f,REL_EPSILON,ABS_EPSILON);
      return eq;
    }
  };

  /// Defines an approximately less than operator for comparing Geometry classes
  struct ApproxLess : public std::binary_function<const Geometry::Ptr,
                      const Geometry::Ptr, bool> {
    bool operator()(const Geometry::Ptr g, const Geometry::Ptr f) const {
      const Scalar REL_EPSILON = 20.0*DBL_EPSILON;
      const Scalar ABS_EPSILON = 20.0*DBL_EPSILON;
      const bool less = g->approx_less(*f,REL_EPSILON,ABS_EPSILON);
      return less;
    }
  };

};

/// Constructor
inline Geometry::Geometry(const Size i_d, const Ordinal n_s_d, 
                          const Ordinal nverts, const Ordinal qtot) {
  //  cout << "Geometry::Geometry constructor, eid = " << i_d << endl;
  id = i_d;
  nsd = n_s_d;
  rx.resize(qtot);
#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  dxr.resize(qtot);
  ivol.resize(qtot);
  acoustic.resize(qtot);
#endif // DGM_STORE_METRICS
  if (nsd>1) {
    ry.resize(qtot);
    sx.resize(qtot);
    sy.resize(qtot);
#ifdef DGM_STORE_METRICS
    // Metrics used for CFL and timestep size (stability) estimates.
    dxs.resize(qtot);
    dyr.resize(qtot);
    dys.resize(qtot);
#endif // DGM_STORE_METRICS
  }
  if (nsd>2) {
    rz.resize(qtot);
    sz.resize(qtot);
    tx.resize(qtot);
    ty.resize(qtot);
    tz.resize(qtot);
#ifdef DGM_STORE_METRICS
    // Metrics used for CFL and timestep size (stability) estimates.
    dxt.resize(qtot);
    dyt.resize(qtot);
    dzr.resize(qtot);
    dzs.resize(qtot);
    dzt.resize(qtot);
#endif // DGM_STORE_METRICS
  }
  J.resize(qtot);
#ifdef DGM_USE_WJ
  wJ.resize(qtot); srwJ.resize(qtot); isrwJ.resize(qtot);
  wJ=0; srwJ=0; isrwJ=0;
#endif
  singular = 0;
  rx=0;  ry=0;  rz=0;
  sx=0;  sy=0;  sz=0;
  tx=0;  ty=0;  tz=0;
#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  dxr=0;   dxs=0;   dxt=0;
  dyr=0;   dys=0;   dyt=0;
  dzr=0;   dzs=0;   dzt=0;
  ivol=0;  acoustic=0;
#endif // DGM_STORE_METRICS
  J=0;
}

/// Copy constructor
inline Geometry::Geometry(Geometry *G) {
  // cout << "Geometry::Geometry copy constructor, eid = " << G->id << endl;
  if (G==0) return;
  id = G->id;
  nsd = G->nsd;
  rx.alias(G->rx);
  if (nsd>1) {
    ry.alias(G->ry);
    sx.alias(G->sx);
    sy.alias(G->sy);
#ifdef DGM_STORE_METRICS
    // Metrics used for CFL and timestep size (stability) estimates.
    dxr.alias(G->dxr);
    dxs.alias(G->dxs);
    dyr.alias(G->dyr);
    dys.alias(G->dys);
    ivol.alias(G->ivol);
    acoustic.alias(G->acoustic);
#endif // DGM_STORE_METRICS
  }
  if (nsd>2) {
    rz.alias(G->rz);
    sz.alias(G->sz);
    tx.alias(G->tx);
    ty.alias(G->ty);
    tz.alias(G->tz);
  }
  J.alias(G->J);
#ifdef DGM_USE_WJ
  wJ.alias(G->wJ); srwJ.alias(G->srwJ); isrwJ.alias(G->isrwJ);
#endif
  singular = G->singular;
}

inline Geometry::Geometry(const Geometry &G) :
  id(G.id),
  nsd(G.nsd),
  rx(G.rx.size()),
  ry(G.ry.size()),
  rz(G.rz.size()),
  sx(G.sx.size()),
  sy(G.sy.size()),
  sz(G.sz.size()),
  tx(G.tx.size()),
  ty(G.ty.size()),
  tz(G.tz.size()),
#ifdef DGM_STORE_METRICS
  // Used for CFL and timestep size estimtes
  dxr(G.dxr.size()),
  dxs(G.dxs.size()),
  dyr(G.dyr.size()),
  dys(G.dys.size()),
  ivol(G.ivol.size()),
  acoustic(G.acoustic.size()),
#endif // DGM_STORE_METRICS
  J(G.J.size())
#ifdef DGM_USE_WJ
  , wJ(G.wJ.size()),
  srwJ(G.srwJ.size()),
  isrwJ(G.isrwJ.size())
#endif
  , singular(G.singular)
{
  rx = G.rx;
  ry = G.ry;
  rz = G.rz;
  sx = G.sx;
  sy = G.sy;
  sz = G.sz;
  tx = G.tx;
  ty = G.ty;
  tz = G.tz;
#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  dxr = G.dxr;
  dxs = G.dxs;
  dyr = G.dyr;
  dys = G.dys;
  ivol = G.ivol;
  acoustic = G.acoustic;
#endif // DGM_STORE_METRICS
  J = G.J;
#ifdef DGM_USE_WJ
  wJ = G.wJ;
  srwJ = G.srwJ;
  isrwJ = G.isrwJ;
#endif
}

/// Less then
bool Geometry::operator<(const Geometry &f) const {
  const Geometry &g = *this;
  if ( g.J.size() < f.J.size() ) return true;
  if ( f.J.size() < g.J.size() ) return false;

  if ( g.rx < f.rx  ) return true;
  if ( f.rx < g.rx  ) return false;
  if ( g.ry < f.ry  ) return true;
  if ( f.ry < g.ry  ) return false;
  if ( g.rz < f.rz  ) return true;
  if ( f.rz < g.rz  ) return false;

  if ( g.sx < f.sx  ) return true;
  if ( f.sx < g.sx  ) return false;
  if ( g.sy < f.sy  ) return true;
  if ( f.sy < g.sy  ) return false;
  if ( g.sz < f.sz  ) return true;
  if ( f.sz < g.sz  ) return false;

  if ( g.tx < f.tx  ) return true;
  if ( f.tx < g.tx  ) return false;
  if ( g.ty < f.ty  ) return true;
  if ( f.ty < g.ty  ) return false;
  if ( g.tz < f.tz  ) return true;
  if ( f.tz < g.tz  ) return false;

  if ( g.J  < f.J   ) return true;
  if ( f.J  < g.J   ) return false;

#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  if ( g.dxr < f.dxr ) return true;
  if ( f.dxr < g.dxr ) return false;
  if ( g.dxs < f.dxs ) return true;
  if ( f.dxs < g.dxs ) return false;
  if ( g.dyr < f.dyr ) return true;
  if ( f.dyr < g.dyr ) return false;
  if ( g.dys < f.dys ) return true;
  if ( f.dys < g.dys ) return false;
#endif // DGM_STORE_METRICS

  return false;
}

/// Equal
bool Geometry::operator==(const Geometry &f) const {
  const Geometry &g = *this;
  const bool eq =
    g.singular  == f.singular
    && g.nsd       == f.nsd
    && g.rx.size() == f.rx.size()

    && g.rx  ==   f.rx
    && g.ry  ==   f.ry
    && g.rz  ==   f.rz

    && g.sx  ==   f.sx
    && g.sy  ==   f.sy
    && g.sz  ==   f.sz

    && g.tx  ==   f.tx
    && g.ty  ==   f.ty
    && g.tz  ==   f.tz

    && g.J   ==   f.J

#ifdef DGM_STORE_METRICS
    // Metrics used for CFL and timestep size (stability) estimates.
    && g.dxr  ==  f.dxr
    && g.dxs  ==  f.dxs
    && g.dyr  ==  f.dyr
    && g.dys  ==  f.dys

    && g.ivol  ==  f.ivol
    && g.acoustic  ==  f.acoustic
#endif // DGM_STORE_METRICS
    ;
  return eq;
}

/// Approximately equal
bool Geometry::approx(const Geometry &f, const Scalar EPS = 1.e-8,
                  const Scalar  ABS = 1.e-8) const {
  using CMC::approx;
  const Geometry &g = *this;
  const bool eq =
    g.singular  == f.singular
    && g.nsd       == f.nsd
    && g.rx.size() == f.rx.size()

    && approx(g.rx, f.rx, EPS, ABS)
    && approx(g.ry, f.ry, EPS, ABS)
    && approx(g.rz, f.rz, EPS, ABS)

    && approx(g.sx, f.sx, EPS, ABS)
    && approx(g.sy, f.sy, EPS, ABS)
    && approx(g.sz, f.sz, EPS, ABS)

    && approx(g.tx, f.tx, EPS, ABS)
    && approx(g.ty, f.ty, EPS, ABS)
    && approx(g.tz, f.tz, EPS, ABS)

    && approx(g.J, f.J, EPS, ABS)

#ifdef DGM_STORE_METRICS
    // Metrics used for CFL and timestep size (stability) estimates.
    && approx(g.dxr, f.dxr, EPS, ABS)
    && approx(g.dxs, f.dxs, EPS, ABS)
    && approx(g.dyr, f.dyr, EPS, ABS)
    && approx(g.dys, f.dys, EPS, ABS)

    && approx(g.ivol, f.ivol, EPS, ABS)
    && approx(g.acoustic, f.acoustic, EPS, ABS)
#endif // DGM_STORE_METRICS
    ;
  return eq;
}

/// Approximately less than
bool Geometry::approx_less(const Geometry &f, const Scalar EPS = 1.e-8,
                       const Scalar  ABS = 1.e-8) const {
  using CMC::approx_less;
  const Geometry &g = *this;
  if ( approx_less(g.rx, f.rx, EPS, ABS) ) return true;
  if ( approx_less(f.rx, g.rx, EPS, ABS) ) return false;
  if ( approx_less(g.ry, f.ry, EPS, ABS) ) return true;
  if ( approx_less(f.ry, g.ry, EPS, ABS) ) return false;
  if ( approx_less(g.rz, f.rz, EPS, ABS) ) return true;
  if ( approx_less(f.rz, g.rz, EPS, ABS) ) return false;

  if ( approx_less(g.sx, f.sx, EPS, ABS) ) return true;
  if ( approx_less(f.sx, g.sx, EPS, ABS) ) return false;
  if ( approx_less(g.sy, f.sy, EPS, ABS) ) return true;
  if ( approx_less(f.sy, g.sy, EPS, ABS) ) return false;
  if ( approx_less(g.sz, f.sz, EPS, ABS) ) return true;
  if ( approx_less(f.sz, g.sz, EPS, ABS) ) return false;

  if ( approx_less(g.tx, f.tx, EPS, ABS) ) return true;
  if ( approx_less(f.tx, g.tx, EPS, ABS) ) return false;
  if ( approx_less(g.ty, f.ty, EPS, ABS) ) return true;
  if ( approx_less(f.ty, g.ty, EPS, ABS) ) return false;
  if ( approx_less(g.tz, f.tz, EPS, ABS) ) return true;
  if ( approx_less(f.tz, g.tz, EPS, ABS) ) return false;

  if ( approx_less(g.J, f.J, EPS, ABS) ) return true;
  if ( approx_less(f.J, g.J, EPS, ABS) ) return false;

#ifdef DGM_STORE_METRICS
  // Metrics used for CFL and timestep size (stability) estimates.
  if ( approx_less(g.dxr, f.dxr, EPS, ABS) ) return true;
  if ( approx_less(f.dxr, g.dxr, EPS, ABS) ) return false;
  if ( approx_less(g.dxs, f.dxs, EPS, ABS) ) return true;
  if ( approx_less(f.dxs, g.dxs, EPS, ABS) ) return false;
  if ( approx_less(g.dyr, f.dyr, EPS, ABS) ) return true;
  if ( approx_less(f.dyr, g.dyr, EPS, ABS) ) return false;
  if ( approx_less(g.dys, f.dys, EPS, ABS) ) return true;
  if ( approx_less(f.dys, g.dys, EPS, ABS) ) return false;
#endif // DGM_STORE_METRICS

  return false;
}

/// Implements a Geometry database using a std::set
class GeometryDBSet {
public:
  typedef std::set<Geometry::Ptr,Geometry::Less> DB;
  GeometryDBSet(const std::string &n) : name(n), geom_db() {}
  ~GeometryDBSet() {
#if DGM_USE_GEOM_DB>=2
    std::cout
     <<"Final size of the "<<name
     <<" GeometryDBSet GeometryDatabase: "<<geom_db.size()
     <<std::endl;
#endif
  }
  bool add(Geometry::Ptr &p) {
    DB::iterator found = geom_db.find(p);
    if (geom_db.end() != found) {
      p = *found;
    } else {
      geom_db.insert(p);
    }
    return (geom_db.end() != found);
  }
  size_t size() const {
    return geom_db.size();
  }
private:
  const std::string name;
  DB geom_db;
};

/// Implements a Geometry database using a std::set with approximate less
class GeometryDBSetApprox {
public:
  typedef std::set<Geometry::Ptr,Geometry::ApproxLess> DB;
  GeometryDBSetApprox(const std::string &n) : name(n), geom_db() {}
  ~GeometryDBSetApprox() {
#if DGM_USE_GEOM_DB>=2
    std::cout
     <<"Final size of the "<<name
     <<" GeometryDBSetApprox Geometry Database: "<<geom_db.size()
     <<std::endl;
#endif
  }
  bool add(Geometry::Ptr &p) {
    DB::iterator found = geom_db.find(p);
    if (geom_db.end() != found) {
      p = *found;
    } else {
      geom_db.insert(p);
    }
    return (geom_db.end() != found);
  }
  size_t size() const {
    return geom_db.size();
  }
  void clear() {
    return geom_db.clear();
  }
private:
  const std::string name;
  DB geom_db;
};

/// Implements a Geometry database using a std::vector with approximate equal
class GeometryDBVectorApprox {
public:
  typedef std::vector<Geometry::Ptr> DB;
  GeometryDBVectorApprox(const std::string &n) : name(n), geom_db() {}
  ~GeometryDBVectorApprox() {
#if DGM_USE_GEOM_DB>=2
    std::cout
     <<"Final size of the "<<name
     <<" GeometryDBVectorApprox Geometry Database: "<<geom_db.size()
     <<std::endl;
#endif
  }
  bool add(Geometry::Ptr &p) {
    DB::iterator found =
      find_if(geom_db.begin(), geom_db.end(), Geometry::Approx(p));
    if (geom_db.end() != found) {
      p = *found;
    } else {
      geom_db.push_back(p);
    }
    return (geom_db.end() != found);
  }
  size_t size() const {
    return geom_db.size();
  }
private:
  const std::string name;
  DB geom_db;
};

/// Implements a Geometry database using a std::vector
class GeometryDBVector {
public:
  typedef std::vector<Geometry::Ptr> DB;
  GeometryDBVector(const std::string &n) : name(n), geom_db() {}
  ~GeometryDBVector() {
#if DGM_USE_GEOM_DB>=2
    std::cout
     <<"Final size of the "<<name
     <<" GeometryDBVector Geometry Database: "<<geom_db.size()
     <<std::endl;
#endif
  }
  bool add(Geometry::Ptr &p) {
    DB::iterator found = 
      find_if(geom_db.begin(), geom_db.end(), Geometry::EQ(p));
    if (geom_db.end() != found) {
      p = *found;
    } else {
      geom_db.push_back(p);
    }
    return (geom_db.end() != found);
  }
  size_t size() const {
    return geom_db.size();
  }
private:
  const std::string name;
  DB geom_db;
};

} // namespace DGM

#endif  // DGM_GEOMETRY_HPP

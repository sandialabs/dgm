/**
 * \file Curve.cpp
 * \brief Curved side implementation
 * \author S. Scott Collis
*/

// system libraries
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

// boost libraries
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// json includes
#ifdef DGM_USE_JSON
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#endif

// DGM libraries
#include "Comm.hpp"
#include "Constants.hpp"
#include "Basis.hpp"
#include "Curve.hpp"
#include "Types.hpp"
#include "Element.hpp"
#include "Polylib.tpp"
#include "String.hpp"
#include "Format.hpp"
#include "Partition.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/export.hpp>
#endif

#ifdef DGM_USE_GENERAL_GHOSTING
/// register classes for serialization of polymorphic types
BOOST_CLASS_EXPORT_GUID(DGM::Straight,   "DGM::Straight");
BOOST_CLASS_EXPORT_GUID(DGM::Straight3D, "DGM::Straight3D");
BOOST_CLASS_EXPORT_GUID(DGM::Arc,        "DGM::Arc");
#endif

namespace DGM {

namespace {
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
} // anonymous namespace

/// Activate JSON reader for curve types
#define DGM_USE_CURVE_JSON_FORMAT

/// Read the curve types from an input stream
void Curve::read(DGM::Comm::Ptr comm, string &fname,
                 ifstream &in, Curve::db_type &ctype) {
#ifdef DGM_USE_CURVE_JSON_FORMAT
  char c = in.peek();
  if (!in) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    read_old(comm,fname,in,ctype);
  } else {
    Json::Value value;
    read_json(comm,fname,in,ctype,value);
  }
#else
  read_old(comm,fname,in,ctype);
#endif
}

/// Read the curve types and sides from an input stream
void Curve::read(DGM::Comm::Ptr comm,
                 const Partition<Size,Ordinal,Scalar>::Ptr partition,
                 const string &fname, ifstream &in,
                 Curve::db_type &ctype, vector<Element*> &el) {
#ifdef DGM_USE_CURVE_JSON_FORMAT
  char c = in.peek();
  if (!in) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    read_old(comm,fname,in,ctype);
    read_sides(comm,partition,fname,in,ctype,el);
  } else {
    Json::Value value;
    read_json(comm,fname,in,ctype,value);
    // try reading from json but revert to old side format if necessary
    if (!read_sides(comm,partition,fname,value,ctype,el))
      read_sides(comm,partition,fname,in,ctype,el);
  }
#else
  read_old(comm,fname,in,ctype);
  read_sides(comm,partition,fname,in,ctype,el);
#endif
}

/// Read in the curved sides from a file stream using Json format
bool Curve::read_sides(DGM::Comm::Ptr comm,
                       const Partition<Size,Ordinal,Scalar>::Ptr partition,
                       const string &fname, Json::Value &value,
                       Curve::db_type &ctype, vector<Element*> &el) {
  static bool firstwarn = true;
  const int verb = value["Verbosity"].asInt();
  if (value.isMember("Curved side location")) {
    if (!value["Curved side location"].isString())
      comm->error("Curve:  \"Curved side location\" must be a string value");
    Json::Value &location = value["Curved side location"];
    if (lowerCase(location.asString())=="at end") {
      if (verb) comm->cout()<<"  Using \"At end\" curved side reader"<<endl;
      return false;
    } else if (!(lowerCase(location.asString())=="inline") &&
               !(lowerCase(location.asString())=="json")) {
      comm->error("Curve:  Illegal value of \"Curved side location\" = "+
                  location.asString());
    }
  } else {
    value.set("Curved side location","Inline");
  }
  if (!value.isMember("Curved sides"))
    comm->error("Curve: File "+fname+" is missing Curved sides specification");
  Json::Value &sides = value["Curved sides"];
  if (!sides.isArray()) comm->error("Curved sides must be an array");
  const Json::ArrayIndex nsides = sides.size();
  for (Json::ArrayIndex i=0; i<nsides; ++i) {
    Json::Value &side = sides[i];
    if (!side.isObject())
      comm->error("Curve:  side "+asString(i)+" is not a Json object");
    const Size eid = numeric_cast<Size>(side["Element"].asInt64());
    const Ordinal sid = numeric_cast<Ordinal>(side["Side"].asInt());
    const string tag = side["Curve"].asString();
    if (eid>partition->gne()-1)
      comm->error("Curve: Too many elements in "+fname);
    if (eid<numeric_limits<Size>::min() || eid>numeric_limits<Size>::max())
      comm->error("Curve: Illegal element id "+asString(eid)+" in "+fname);
    if (!partition->owns(eid)) continue;
    const Ordinal k = partition->inc(eid);
    if (el[k]->L() > 1) {
      if (ctype.find(tag) == ctype.end() )
        comm->error("Curve: unsupported curve type = "+tag);
      el[k]->curve.reset( ctype[tag]->clone() );
      el[k]->curve->side = sid;
    } else {
      if (firstwarn) {
        if (comm->Master())
          cout << "WARNING:  curved element " << eid
          << " has constant basis, suppressing further warnings."
          << endl;
        firstwarn=false;
      }
    }
  }
  if (verb) {
    Json::StyledWriter writer;
    string output = writer.write(sides);
    cout << "  Curved sides:\n" << output;
  }
  if (verb) comm->cout()<<"  Completed reading curved sides"<<endl;
  return true;
}

/// Read in the curved sides from a file stream using old format
void Curve::read_sides(DGM::Comm::Ptr comm,
                       const Partition<Size,Ordinal,Scalar>::Ptr partition,
                       const string &fname, ifstream &in,
                       Curve::db_type &ctype, vector<Element*> &el) {
  static bool firstwarn = true;
  Ordinal nsides, side;
  Size eid;
  if (!(in>>nsides))
    comm->error("Curve: Cannot read number of curved sides from "+fname);
  string buffer, tag;
  getline(in,buffer);
  if (nsides) {
    if (ctype.size()==0)
      comm->error("Curve: No curve types specified in "+fname);
    for (Ordinal i=0; i<nsides; i++) {
      if (!(in >> eid >> side >> tag))
        comm->error("Curve:  Unable to read curved side information.");
      if (eid>(Size)(partition->gne()-1))
        comm->error("Curve: Too many elements in "+fname);
      if (eid<numeric_limits<Size>::min() || eid>numeric_limits<Size>::max())
        comm->error("Curve: Illegal element id in "+fname);
      if (!partition->owns(eid)) continue;
      const Ordinal k = partition->inc(eid);
      if (el[k]->L() > 1) {
        if (ctype.find(tag) == ctype.end() )
          comm->error("Curve: unsupported curve type = "+tag);
        el[k]->curve.reset( ctype[tag]->clone() );
        el[k]->curve->side = side;
      } else {
        if (firstwarn) {
          if (comm->Master())
            cout << "WARNING:  curved element " << eid
            << " has constant basis, suppressing further warnings."
            << endl;
          firstwarn=false;
        }
      }
    }
  }
}

/// Read the curve types from an JSON formated input stream
void Curve::read_json(DGM::Comm::Ptr comm, const string &fname,
                     ifstream &in, Curve::db_type &ctype, Json::Value &value) {
  comm->cout()<<"  Reading JSON Curve types from: " << fname << endl;
  char c = in.peek();
  if (!in) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{')
    throw DGM::exception("Cannot read Json header from "+fname+
                         " first character is not an open bracket:`{`");
  string token;
  if (!(in >> token))
    throw DGM::exception("Error reading Json header from "+fname);
  string buffer = read_block(in);
  const int status = scan_rb(in);
  if (status) comm->error("Could not find closing bracket for Json header "
                          " on file "+fname);
  // comm->cout()<<"Read curve types from "<<fname<<"\n"<<buffer<<endl;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse(buffer, value, true);
  if (!parsingSuccessful)
    comm->error("Curve::read_json could not parse input from "+
                fname+"\n"+reader.getFormattedErrorMessages());
  getline(in,buffer);
  const int verb = value.set("Verbosity",0).asInt();
  if (!value.isMember("Curve types"))
    comm->error("Curve types block is missing");
  Json::Value &curves = value["Curve types"];
  if (!curves.isArray())
    comm->error("Curve types must be an array");
  const Json::ArrayIndex ncrvs = curves.size();
  for (Json::ArrayIndex i=0; i<ncrvs; ++i) {
    Json::Value &curve = curves[i];
    string tag;
    Curve *pcrv = make_json(comm,curve,tag);
    if (0 != pcrv) ctype[tag].reset(pcrv);
  }
  if (verb) {
    Json::StyledWriter writer;
    string output = writer.write(value);
    cout << "  Curve parameters:\n" << output;
  }
  if (verb) comm->cout()<<"  Completed reading curve types"<<endl;
}

/// Read the curve types from an old-style input stream
void Curve::read_old(DGM::Comm::Ptr comm, const string &fname,
                     ifstream &in, Curve::db_type &ctype) {
  comm->cout() << "  Reading old Curve types from: " << fname << endl;
  string buffer, tag, code;
  getline(in,buffer);
  Ordinal ncrvs=0;
  if (!(in>>ncrvs)) comm->error("Cannot read number of curve types");
  getline(in,buffer);
  for (Ordinal i=0; i<ncrvs; i++) {
    Curve *pcrv = make(comm,in,tag);
    if (0 != pcrv) ctype[tag].reset(pcrv);
  }
}

/// Virtual constructor for curved elements
/**
 * This serves as a factory for Curves using a JSON input specification
*/
Curve* Curve::make_json(DGM::Comm::Ptr comm, Json::Value &curve, string &tag ) {
  if (!curve.isMember("Type"))
    comm->error("Cannot read curve type");
  if (!curve.isMember("Name"))
    comm->error("Cannot read curve name");
  const string code = lowerCase(curve["Type"].asString());
  tag = curve["Name"].asString();
  if (code == "affine") {
    return NULL;
  } else if (code=="straight" || code=="nonaffine" || code=="skewed" ) {
    return new Straight(curve,comm);
  } else if (code=="straight3d" || code=="nonaffine3d" || code=="skewed3d") {
    return new Straight3D(curve,comm);
  } else if (code=="arc") {
    return new Arc(curve,comm);
  } else if (code=="circle") {
    return new Arc(curve, comm);
  } else if (code=="ellipse") {
    return new Ellipse(curve,comm);
  } else if (code=="sine") {
    return new Sine(curve, comm);
  } else if (code=="sphere") {
    return new Sphere(curve, comm);
  } else {
    comm->error("Illegal Curve type "+code);
  }
  return NULL;
}

/// Virtual constructor for curved elements
/**
 * This serves as a factory for Curves using the old-style input format
*/
Curve* Curve::make(DGM::Comm::Ptr comm, ifstream &in, string &tag ) {
  string buffer, code;
  if (!(in >> code)) comm->error("Cannot read curve type");
  if (lowerCase(code) == "affine") {
    if (!(in >> tag)) comm->error("Cannot read Affine data");
    return 0;
  } else if (lowerCase(code) == "straight" || lowerCase(code) == "nonaffine" ||
      lowerCase(code) == "skewed" ) {
    if (!(in >> tag)) comm->error("Cannot read Straight data");
    return new Straight(comm);
  } else if (lowerCase(code) == "straight3d" ||
      lowerCase(code) == "nonaffine3d" || lowerCase(code) == "skewed3d") {
    if (!(in >> tag)) comm->error("Cannot read Straight data");
    return new Straight3D(comm);
  } else if (lowerCase(code) == "arc") {
    Scalar r;
    if (!(in >> tag >> r)) comm->error("Cannot read Arc radius");
    return new Arc(r,comm);
  } else if (lowerCase(code) == "circle") {
    Scalar x_c, y_c, r;
    if (!(in >> tag >> x_c >> y_c >> r))
      comm->error("Cannot read Circle data");
    return new Arc(x_c, y_c, r, comm);
  } else if (lowerCase(code) == "ellipse") {
    Scalar x_c, y_c, a_a, b_b;
    int sign;
    if (!(in >> tag >> x_c >> y_c >> a_a >> b_b >> sign))
      comm->error("Cannot read Ellipse data");
    return new Ellipse(x_c, y_c, a_a, b_b, sign, comm);
  } else if (lowerCase(code) == "sine") {
    Scalar x_o, y_o, a, w;
    if (!(in >> tag >> x_o >> y_o >> a >> w))
      comm->error("Cannot read Sine data");
    return new Sine(x_o, y_o, a, w, comm);
  } else if (lowerCase(code) == "sphere") {
    Scalar x_c, y_c, z_c, r;
    if (!(in >> tag >> x_c >> y_c >> z_c >> r))
      comm->error("Cannot read Sphere data");
    return new Sphere(x_c, y_c, z_c, r, comm);
  } else {
    comm->error("Illegal Curve type");
  }
  return NULL;
}

/// Generic generate causes an error
void Curve::generate(const Element *E, dVector &x, dVector &y) const {
  comm->cerr() << "Curve::generate() is not defined for 2d" << endl;
  comm->exit(DGM::FAILURE);
}

/// Generic generate causes an error
void Curve::generate(const Element *E, dVector &x, dVector &y, dVector&z)
const {
  cerr << "Curve::generate() is not defined for 3d" << endl;
  comm->exit(DGM::FAILURE);
}

/// Generate straight sided element (needed for arbitrary 2d elements)
/**
 * Make a general, straight-sides element in 2d
 * \param[in] E Pointer to the element with curved side
 * \param[out] x Vector of x coordinates on curved side
 * \param[out] y Vector of y coordinates on curved side
 * \throws DGM::Exception If not two-dimensional problem
*/
void Straight::generate(const Element *E, dVector &x, dVector &y) const {
  if (verb) comm->cout() << "Straight::generate() Element = " << E->gid()
                         << " side = " << side << endl;
  if (E->nsd()!=2) throw DGM::exception("Tried to generate a 2d Straight "
      "element but for an element with nsd = "+asString(E->nsd()));
#ifndef DGM_USE_OLD_STRAIGHT_GENERATE
  dVector z;
  vector<Point> p;
  int orientation = 1;
  E->get_curved_side_info(side,p,z,orientation);
  const Ordinal q = z.size();

  // initialize as a straight line accounting for side orientation
  x.resize(q); y.resize(q);
  for (Ordinal i=0; i<q; ++i) {
    const Scalar zl = orientation==1 ? z[i] : z[q-1-i];
    x[i] = pt5*(one-zl)*p[0].x + pt5*(one+zl)*p[1].x;
    y[i] = pt5*(one-zl)*p[0].y + pt5*(one+zl)*p[1].y;
  }
#else
  // WARNING:  this has a bug and is only valid for positive side orientations
  Point p1, p2;
  const Ordinal q = E->qa;
  dVector z(q), w(q);
  x.resize(q);
  y.resize(q);

  zwgll(z,w);  // Gauss-Lobatto-Legendre points and weights

  p1.x = E->vert[side]->x;
  p1.y = E->vert[side]->y;
  p2.x = E->vert[(side+1)%E->nVerts()]->x;
  p2.y = E->vert[(side+1)%E->nVerts()]->y;

  for(Ordinal i = 0; i < q; ++i) {
    x[i] = p1.x + pt5*(p2.x-p1.x)*(z[i]+one);
    y[i] = p1.y + pt5*(p2.y-p1.y)*(z[i]+one);
  }
#endif
}

/// Generate 3d straight sided element (needed for arbitrary 3d elements)
/**
 * Makes a simple non-affine, straight-sided 3d element
 * \param[in] E Pointer to the element with curved side
 * \param[out] x Vector of x-coordinates on curved side
 * \param[out] y Vector of y-coordinates on curved side
 * \param[out] z Vector of z-coordinates on curved side
 * \throws DGM::Exception If not three-dimensional problem
*/
void Straight3D::generate( const Element *E,
                           dVector &x, dVector &y, dVector &z) const {
  // cout << "Straight3D::generate() side = " << side << endl;
  if (E->nsd()!=3) throw DGM::exception("Tried to generate a 3d Straight "
      "element but for an element with nsd = "+asString(E->nsd()));
#ifndef DGM_USE_OLD_STRAIGHT3D_GENERATE
  E->get_straight_side_coordinates(side, x, y, z);
#else
  const Ordinal q = E->qa;
  dVector z_gll(q), w(q);
  Scalar phi[4];

  Ordinal qq;
  if(side == 0 || side == 5)
    qq = E->qa*E->qb;
  else if(side == 1 || side == 3)
    qq = E->qa*E->qc;
  else
    qq = E->qb*E->qc;

  x.resize(qq); x = 0;
  y.resize(qq); y = 0;
  z.resize(qq); z = 0;

  zwgll(z_gll,w);  // Gauss-Lobatto-Legendre points and weights

#ifdef DGM_DEBUG_STRAIGHT3D
  cout << "side: " << side << endl;
  for (Ordinal k = 0; k < 4; ++k) {
    n = E->sideVertMap(side,k);
    cout << "n: " << n << " verts: "
         << E->vert[n].x << " " << E->vert[n].y << " "
         << E->vert[n].z << endl;
  }
#endif

  for (Ordinal i=0; i<q; ++i) {
    for (Ordinal j=0; j<q; ++j) {
      const Scalar r = z_gll[i];
      const Scalar s = z_gll[j];
      phi[0]=pt25*(1.0-r)*(1.0-s);
      phi[1]=pt25*(1.0+r)*(1.0-s);
      phi[2]=pt25*(1.0+r)*(1.0+s);
      phi[3]=pt25*(1.0-r)*(1.0+s);
      for (Ordinal k=0; k<4; ++k) {
        const Ordinal n = E->sideVertMap(side,k);
        x[j+i*q] += phi[k]*(E->vert[n]->x);
        y[j+i*q] += phi[k]*(E->vert[n]->y);
        z[j+i*q] += phi[k]*(E->vert[n]->z);
      }
#ifdef DGM_DEBUG_STRAIGHT3D
      cout << "i= " << i << " j= " << j
           << " r,s: "  << r << " " << s << " "
           << "x,y,z: " << x[i*q+j] << " " << y[i*q+j] << " "
           << z[i*q+j] << endl;
      cout << "phi: " << phi[0] << " " << phi[1] << " "
           << phi[2] << " " << phi[3] << endl;
      cout << "x: " << E->vert[E->sideVertMap(side,0)].x << " "
                    << E->vert[E->sideVertMap(side,1)].x << " "
                    << E->vert[E->sideVertMap(side,2)].x << " "
                    << E->vert[E->sideVertMap(side,3)].x << " " << endl;
      cout << "y: " << E->vert[E->sideVertMap(side,0)].y << " "
                    << E->vert[E->sideVertMap(side,1)].y << " "
                    << E->vert[E->sideVertMap(side,2)].y << " "
                    << E->vert[E->sideVertMap(side,3)].y << " " << endl;
      cout << "z: " << E->vert[E->sideVertMap(side,0)].z << " "
                    << E->vert[E->sideVertMap(side,1)].z << " "
                    << E->vert[E->sideVertMap(side,2)].z << " "
                    << E->vert[E->sideVertMap(side,3)].z << " " << endl;
#endif
    }
  }
#endif
}

/// Generate an arc of a circle (2d)
/**
 * This uses a geometric approach to identify the possible two circles of
 * a given radius that also passes through two prescribed points which in
 * this case are two vertices forming an element edge in 2d.
 * \param[in] E Pointer to the element with curved side
 * \param[out] x Vector of x coordinates on curved side
 * \param[out] y Vector of y coordinates on curved side
 * \throws DGM::Exception If not two-dimensional problem
*/
void Arc::generate(const Element *E, dVector &x, dVector &y) const {
  if (verb) comm->cout()<<"Arc::generate for Element = "<<E->gid()
                        <<" side = "<<side<<endl;
  if (E->nsd()!=2) throw DGM::exception("Tried to generate a 2d Arc "
      "element but for an element with nsd = "+asString(E->nsd()));
  dVector z;
  vector<Point> p;
  int orientation = 1;
  E->get_curved_side_info(side,p,z,orientation);
  const Ordinal q = z.size();

  const Scalar arclength = p[0].distance(p[1]);

  // The arc-length has to be bigger than twice the radius for the circle to fit
  if(fabs(arclength/radius) > two) {
    comm->cerr() << "Arc radius = " << radius << " is too small to fit on "
        "  Element id = " << E->gid() << ", side = " << side << endl;
    comm->exit(DGM::FAILURE);
  }

  // find the mid-point on the arc
  Point pm;
  pm.x = (p[0].x + p[1].x) * pt5;
  pm.y = (p[0].y + p[1].y) * pt5;

  // The mirror line which is perpendicular to the arc-length is given by
  // ( p[1].y-p[0].y, p[0].x-p[1].x ) / arclength to normalize to unit length
  // the distance to move from p3 to the center circle is sqrt(r^2-(q/2)^2)
  // If the radius is positive, assume concave and move down the mirror line
  const Scalar dist = sqrt(radius*radius - arclength*arclength*pt25) *
                      ((radius>0.0) ? -one : one);

  // The center of the circle is then given by
  Point pc;
  pc.x = pm.x + dist * (p[1].y - p[0].y) / arclength;
  pc.y = pm.y + dist * (p[0].x - p[1].x) / arclength;

  // Check computed center against input data
  if (check_center) {
    static Format sci(10,18,'e');
    if (verb>1) comm->cout()<<"Computed center is at: "
                            <<sci(pc.x)<<","<<sci(pc.y)<<endl;
#ifdef DGM_ARC_CHECK_CENTER_EXCEPTION
    if (!approx_equal(pc.x,center_x,sqrt(repsM),sqrt(aepsM)))
      throw DGM::exception("Center x location is incorrect on Arc");
    if (!approx_equal(pc.y,center_y,sqrt(repsM),sqrt(aepsM)))
      throw DGM::exception("Center y location is incorrect on Arc");
#endif
  }
  // compute absolute value of distance and radius
  const Scalar adis = fabs(dist);
  const Scalar arad = fabs(radius);
  // A vector displacement from the center with length radius is given by
  Point pd;
  pd.x  = (pm.x - pc.x) * (arad / adis);
  pd.y  = (pm.y - pc.y) * (arad / adis);
  // the half angle of the inscribed triangle with sign based on radius and
  // corrected for side orientation for this element/side combination
  const Scalar theta = atan(pt5 * arclength / adis) * (radius>0 ? one:-one) *
                       orientation;

  // Use the local coordinates [-1:1] to define points on arc
  x.resize(q); y.resize(q);
  for (Ordinal i=0; i<q; ++i) {
    const Scalar beta = theta * z[i];
    x[i] = pc.x + pd.x * cos(beta) - pd.y * sin(beta);
    y[i] = pc.y + pd.x * sin(beta) + pd.y * cos(beta);
    //cout << i << " x = " << x[i] << ", y = " << y[i] << endl;
  }
  if (verb>1) comm->cout() << "Arc::generate complete" << endl;
}

/// Json constructor
Ellipse::Ellipse(Json::Value &value, DGM::Comm::Ptr comm_) :
  Curve(value,comm_), xc(0.0), yc(0.0),
  aa(value.set("Semi major axis",1.0).asDouble()),
  bb(value.set("Semi minor axis",0.5).asDouble()),
  orientation(value.set("Orientation",1).asInt()) {
  if (verb>1) comm->cout() << "Ellipse JSON constructor"<<endl;
  if (value.isMember("Center")) {
    if (value["Center"].isArray()) {
      Json::ArrayIndex nsd = value["Center"].size();
      if (nsd>0)
        xc = value["Center"][0].asDouble();
      if (nsd>1)
        xc = value["Center"][1].asDouble();
      if (nsd>2)
        comm->error("Ellipse \"Center\" must have one or two components");
    } else {
      comm->error("Ellipse \"Center\" must be an array of doubles");
    }
  }
  if (!(orientation==1 || orientation==-1))
    comm->error("Ellipse \"Orientation\" must be either 1 (clockwise) or "
                "-1 (counter-clockwise)");
}

/// Generate a portion of an ellipse (2d)
/** Forms an elliptical curve between two vertices forming an element edge.
 *  \param[in] E Pointer to the element with curved side
 *  \param[out] x Vector of x coordinates on curved side
 *  \param[out] y Vector of y coordinates on curved side
 *  \throws DGM::Exception If not two-dimensional problem. */
void Ellipse::generate( const Element *E, dVector &x, dVector &y ) const {
  if (E->nsd()!=2) throw DGM::exception("Tried to generate a 2d Ellipse "
      "element but for an element with nsd = "+asString(E->nsd()));
  dVector z;
  vector<Point> p;
  int orien=0;
  E->get_curved_side_info(side,p,z,orien);
  const Ordinal q = z.size();

  // Find the angles theta1 and theta2 corresponding to the side end points
  Scalar theta1=0, theta2=0;
  if ( fabs(p[0].x-xc-aa) < 1e-12 ) {
    if ( orientation == 1 )           // counter clockwise
      theta1=0.0;
    else if ( orientation == -1 )
      theta1=2.0*pi;
    else {
      comm->cerr() << "Orientation can be either 1 or -1 in "
                      "Ellipse class" << endl;
      comm->exit(DGM::FAILURE);
    }
  } else {
    theta1 = acos((p[0].x-xc)/aa);
    if ( p[0].y < yc ) theta1 = 2*pi - theta1;
  }
  if ( fabs(p[1].x-xc-aa) < 1e-12 ) {
    if ( orientation == 1 )           // counter clockwise
      theta2=2.0*pi;
    else if ( orientation == -1 )
      theta2=0.0;
    else {
      comm->cerr() << "Orientation can be either 1 or -1 in "
                      "Ellipse class" << endl;
      comm->exit(DGM::FAILURE);
    }
  } else {
    theta2 = acos((p[1].x-xc)/aa);
    if ( p[1].y < yc ) theta2 = 2*pi - theta2;
  }
  // Compute the arclength
  // comm->cout() << "T1: "<< theta1 << "   " << "T2: " << theta2 << endl;
  Scalar arclen=zero;
  arclength(theta1, theta2, arclen);

  // comm->cout() <<"arclength: "<<arclen<< "  "<< "ID: "<< E->id
  //              << "  "<< "t1: "<< theta1*180/pi <<"  "
  //              <<"t2: "<< theta2*180/pi << endl;
  Scalar s1=0;
  x.resize(q); y.resize(q);
  for (Ordinal i=0; i<q; ++i) {
    const Scalar s = (orientation == 1) ? pt5*arclen*(z[i]+1) :
                                          pt5*arclen*(1-z[i]);
    // Find theta that corresponds to arclength s using Newton-Raphson
    Scalar theta = theta1 + pt5*(theta2-theta1)*(z[i]+1);
    Scalar dsdtheta = sqrt(aa*aa*sin(theta)*sin(theta)+
                           bb*bb*cos(theta)*cos(theta));
    arclength(theta,theta2,s1);
    while (fabs(s1-s) > 1e-10*arclen) {
      theta = theta +(s-s1)/dsdtheta;
      dsdtheta = sqrt(aa*aa*sin(theta)*sin(theta) +
                      bb*bb*cos(theta)*cos(theta));
      arclength(theta,theta2,s1);
      // comm->cout() << i <<"  "<< theta << "  " << dsdtheta
      //              << "   "<< s-s1 <<endl;
    }
    x[i] = xc + aa*cos(theta);
    y[i] = yc + bb*sin(theta);
    cout << x[i] << "   " << y[i] << endl;
  }
}

/// Compute the arc length on an ellipse between theta1 and theta2
void Ellipse::arclength(Scalar t1, Scalar t2, Scalar& arclen) const {
  dVector z1, w1;
  Scalar sum = 0;
  Scalar error = 1.0;
  Scalar tol = 1.e-8*fabs(t2-t1);
  Scalar sum_old = 0.0;
  Ordinal qq = 3;
  while (fabs(error) > tol) {
    z1.resize(qq); w1.resize(qq); sum=0.0;
    zwgll(z1,w1);
    for (Ordinal i=0; i<qq; ++i) {
      Scalar t = pt5*(t1+t2) + pt5*(t1-t2)*z1[i];
      sum += w1[i]*pt5*(t1-t2)*
             sqrt(aa*aa*sin(t)*sin(t) + bb*bb*cos(t)*cos(t));
    }
    error = fabs(sum-sum_old); sum_old=sum; qq=qq+2;
    // comm->cout() << "SUM: " <<sum << "   " << error <<endl;
  }
  arclen = (orientation == -1) ? sum : -sum;
}

/// Json constructor
Sine::Sine(Json::Value &value, DGM::Comm::Ptr comm_) : Curve(value,comm_) {
  DGM_UNDEFINED;
}

/// Generate a sine wave (2d)
/**
 * Forms an sinusoidal curve between two vertices forming an element edge.
 * \param[in] E Pointer to the element with curved side
 * \param[out] x Vector of x coordinates on curved side
 * \param[out] y Vector of y coordinates on curved side
 * \throws DGM::Exception If not two-dimensional problem
*/
void Sine::generate(const Element *E, dVector &x, dVector &y) const {
  if (verb) comm->cout()<<"Sine::generate for Element = "<<E->gid()
                        <<" side = "<<side<<endl;
  if (E->nsd()!=2) throw DGM::exception("Tried to generate a 2d Sine "
      "element but for an element with nsd = "+asString(E->nsd()));
  dVector z;
  vector<Point> p;
  int orientation = 1;
  E->get_curved_side_info(side,p,z,orientation);
  const Ordinal q = z.size();

  // initialize as a straight line accounting for side orientation
  x.resize(q); y.resize(q);
  for (Ordinal i=0; i<q; ++i) {
    const Scalar zl = orientation==1 ? z[i] : z[q-1-i];
    x[i] = pt5*(one-zl)*p[0].x + pt5*(one+zl)*p[1].x;
    y[i] = pt5*(one-zl)*p[0].y + pt5*(one+zl)*p[1].y;
  }
  // add in the sine wave perturbation
  for (Ordinal i=0; i<q; ++i) y[i] = yo+amp*sin(two*pi*(x[i]-xo)/wavelength);
}

/// Sphere Json constructor
Sphere::Sphere(Json::Value &value, DGM::Comm::Ptr comm_) :
  Curve(value,comm_),
  center_x(0.0), center_y(0.0), center_z(0.0),
  radius(value.set("Radius",0.0).asDouble())
{
  if (verb>1) comm->cout() << "Sphere("<<radius<<") JSON constructor"<<endl;
  if (value.isMember("Center")) {
    if (value["Center"].isArray()) {
      Json::ArrayIndex nsd = value["Center"].size();
      if (nsd!=3) comm->error("Sphere center must be 3d");
      center_x = value["Center"][0].asDouble();
      center_y = value["Center"][1].asDouble();
      center_z = value["Center"][2].asDouble();
    } else {
      comm->error("Sphere \"Center\" must be an array of doubles");
    }
  }
}

/// Generate a face on a prescribed Sphere (3d)
/**
 * Forms a spherical side
 * \param[in] E Pointer to the element with curved side
 * \param[out] x Vector of x-coordinates on curved side
 * \param[out] y Vector of y-coordinates on curved side
 * \param[out] z Vector of z-coordinates on curved side
 * \throws DGM::Exception If not three-dimensional problem
*/
void Sphere::generate(const Element *E,
                      dVector &x, dVector &y, dVector &z ) const {
  if (E->nsd()!=3) throw DGM::exception("Tried to generate a 3d Sphere "
      "element but for an element with nsd = "+asString(E->nsd()));
  const Ordinal q = E->side2size(side);
  E->get_straight_side_coordinates(side, x, y, z);
  add(-center_x, x, x);
  add(-center_y, y, y);
  add(-center_z, z, z);
  for(Ordinal i=0; i<q; ++i) {
    const Scalar phi   = atan(z[i]/sqrt(x[i]*x[i]+y[i]*y[i]));
    const Scalar theta = atan2(y[i],x[i]);
    z[i] = radius*sin(phi);
    x[i] = radius*cos(phi)*cos(theta);
    y[i] = radius*cos(phi)*sin(theta);
  }
  add(center_x, x, x);
  add(center_y, y, y);
  add(center_z, z, z);
}

} // namespace DGM

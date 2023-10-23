#ifndef DGM_REMOVE_FOR_RELEASE

#ifndef REO_SHALLOW_HPP
#define REO_SHALLOW_HPP

/** \file  Shallow.hpp
    \brief Declarations for the 2d Shallow equations
    \author Vincent Mousseau
    \author S. Scott Collis
*/

// DGM includes
#include "Comm.hpp"
#include "Domain.hpp"
#include "Element.hpp"
#include "ShallowIC.hpp"
#include "Ctrl.hpp"
using namespace DGM;

// Reo includes
#include "ReoConfig.hpp"

namespace Reo {

/// Two-dimensional compressible Shallow Domain
class Shallow : public Domain {

  dVector wk1;   ///< local workspace
  dVector wk2;   ///< local workspace

  vField Usrc;

  vField Utmp;

protected:

  static const int NFIELDS = 3; ///< fixed number of fields for static arrays

public:

  // BC declarations (definitions below)
  class WallBC;
  class SubsonicOutflowBC;
  class SupersonicOutflowBC;
  class LinearControlBC;
  class SteadyLinearControlBC;
  class ControlBC;
  class SteadyControlBC;

  // Source terms
  class XMomSource;
  class YMomSource;

  class ForceSource;
  class GaussianSource;

  class ForceSourceCtrl;
  class ForceSourceCtrlII;
  class DistributedControl;

  /// Constructor
  Shallow( DGM::ArgList &args, const DGM::Comm::Ptr = DGM::Comm::World,
           const int pinc=0);

  /// Destructor
  virtual ~Shallow();

  // local methods
  void parse_args( DGM::ArgList &args );
  void showUsage();

  // override virtual Domain methods
  virtual int plot(const string&);

  void set_material();

  void time_derivative( vField &, vField & );

  Scalar set_time_step( vField & );
  void set_ic( vField &, string=".ic" );

  void setup_BCdb( );
  void read_BCdb( ifstream & );
  BC* make_BC( ifstream &, string & );

  Source::Ptr make_Source( ifstream &, string & );
  void add_source(const vField &, vField & );

  void write_bndry_stats();

  // TODO: move this to a method on the domain so that derived classes
  // can use it too
  void verify_input_parameters();

protected:

  /// Supported numerical fluxes
  enum flux_type {
    LaxFriedrichs          ///< Lax-Friedrichs flux
  };

  /// Active numerical flux
  flux_type flux;

  // local methods
  void convection( vField &, vField & );
  void gradient( Element *, Element *, dVector &, dVector &, dVector & );
  void primitive_sides( vField & );
  void convective_flux( vField &, vField & );
  void compute_primatives();
};

//===========================================================================
//                           X Momentum Source
//===========================================================================

class Shallow::XMomSource : public Source {
  Bore ic;
public:
  XMomSource(const string tag, ifstream &in) : Source(tag) {
    scan_lb(in);
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &U, vField &F) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[1]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        const Scalar phi = U[0]->el[e]->u[q];
        E->u[q] -= gPhiDhDx( (*E->C)[q], time, phi );
      }
    }
  }

  /// \todo This needs to be implemented so make it noisy
  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {
    cout << "XMomSource::adjoint_apply(...)" << endl;
  }

private:
  Scalar gPhiDhDx(const Point &C, const Scalar t, const Scalar phi) {
    const Scalar grav = ic.G(C);
    const Scalar dhdx = ic.DHDX(C);
    Scalar source = grav * phi * dhdx;
    return source;
  }
};

//===========================================================================
//                           Y Momentum Source
//===========================================================================

class Shallow::YMomSource : public Source {
  Bore ic;
public:
  YMomSource(const string tag, ifstream &in) : Source(tag) {
    scan_lb(in);
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &U, vField &F) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[2]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        const Scalar phi = U[0]->el[e]->u[q];
        E->u[q] -= gPhiDhDy( (*E->C)[q], time, phi );
      }
    }
  }

  /// \todo This needs to be implemented so make it noisy
  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {
    cout << "YMomSource::adjoint_apply(...)" << endl;
  }

private:
  Scalar gPhiDhDy(const Point &C, const Scalar t, const Scalar phi) {
    const Scalar grav = ic.G(C);
    const Scalar dhdy = ic.DHDY(C);
    Scalar source = grav * phi * dhdy;
    return source;
  }
};

//===========================================================================
//                           Force Source
//===========================================================================

class Shallow::ForceSource : public Source {
  const DGM::Comm::Ptr comm;     ///< Communicator
  Bore ic;                       ///< reference
  int verb;                      ///< verbosity level
public:
  ForceSource(const string tag, ifstream &in, DGM::Comm::Ptr comm_) :
    Source(tag), comm(comm_), verb(0) {
    scan_lb(in);
    Json::Value root;
    Json::Reader reader;
    string buffer = read_block(in);
    bool parsingSuccessful = reader.parse(buffer,root,true);
    if (!parsingSuccessful) {
      comm->cout()<<"Shallow::ForceSource could not "
                                "parse Json input"<<endl;
      comm->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
    verb = root.get("Verbosity",verb).asInt();
    scan_rb(in);
  }

  void apply(const Scalar time, const vField &U, vField &F) {
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *Eu = F[1]->el[e];
      Element *Ev = F[2]->el[e];
      for (LocalSize q=0; q<Eu->qtot; q++) {
        const Scalar phi = U[0]->el[e]->u[q];
        Eu->u[q] -= gPhiDhDx( (*Eu->C)[q], time, phi );
        Ev->u[q] -= gPhiDhDy( (*Ev->C)[q], time, phi );
      }
    }
  }

  /** \note This may not yet be correct. */
  void adjoint_apply(const Scalar time, const vField &State,
                     const vField &U, vField &F) {
    if (verb) comm->cout() << "ForceSource::adjoint_apply(...)" << endl;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[0]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        const Scalar ut = U[1]->el[e]->u[q];
        const Scalar vt = U[2]->el[e]->u[q];
        // SSC: not sure that sign is right
        E->u[q] -= gPhiDhDx((*E->C)[q], time, ut) +
                   gPhiDhDy((*E->C)[q], time, vt);
      }
    }
  }

private:
  Scalar gPhiDhDx(const Point &C, const Scalar t, const Scalar phi) {
    const Scalar grav = ic.G(C);
    const Scalar dhdx = ic.DHDX(C);
    Scalar source = grav * phi * dhdx;
    return source;
  }
  Scalar gPhiDhDy(const Point &C, const Scalar t, const Scalar phi) {
    const Scalar grav = ic.G(C);
    const Scalar dhdy = ic.DHDY(C);
    Scalar source = grav * phi * dhdy;
    return source;
  }
};

//===========================================================================
//                          Force Source Ctrl
//===========================================================================

/// This is just a stub in of a Ctrl to help get things going
/** \note Does not yet implement parallel infrastructure. */
class Shallow::ForceSourceCtrl : public Source, public Ctrl {
  const DGM::Comm::Ptr comm;     ///< Communicator
  Bore ic;                       ///< reference
  int verb;                      ///< verbosity level
  dVector data0;                 ///< initial data
public:
  ForceSourceCtrl(const string tag, ifstream &in, DGM::Comm::Ptr comm_) :
    Source(tag), Ctrl(0.0,1), comm(comm_), verb(0) {
    scan_lb(in);
    Json::Value root;
    Json::Reader reader;
    string buffer = read_block(in);
    bool parsingSuccessful = reader.parse(buffer,root,true);
    if (!parsingSuccessful) {
      comm->cout()<<"Shallow::ForceSourceCtrl could not "
                    "parse Json input"<<endl;
      comm->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
    verb = root.get("Verbosity",verb).asInt();
    penalty = root.get("Penalty",penalty).asDouble();
    data0.resize(2);
    data0[0] = root.get("Initial data x",0.0).asDouble();
    data0[1] = root.get("Initial data y",0.0).asDouble();
    scan_rb(in);

    if (verb) {
      Json::StyledWriter writer;
      string output = writer.write(root);
      comm->cout() << "Shallow::ForceSourceCtrl parameters:\n" << output;
    }

    // set the size to 2 since we have two control variables: dhdx, dhdy
    set_size(2);
    initialize();

    data[0] = data0[0];
    data[1] = data0[1];

    // This Ctrl object is replicated across the parallel machine and only the
    // master actually owns a part of the global control vector
    replicated(true);
    if (comm->Master())
      owner(true);
    else
      owner(false);
}

  /// Destructor
  virtual ~ForceSourceCtrl() {}

  // Implement required Source methods

  /// Apply this source control to the State
  void apply(const Scalar time, const vField &U, vField &F) {
    if (verb>2) comm->cout() << "ForceSource::apply() "
                             << data[0] << ", " << data[1] << endl;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *Eu = F[1]->el[e];
      Element *Ev = F[2]->el[e];
      for (LocalSize q=0; q<Eu->qtot; q++) {
        const Scalar phi = U[0]->el[e]->u[q];
        const Point &P = (*Eu->C)[q];
        const Scalar g = ic.G(P);
        Eu->u[q] -= g * phi * data[0] * pt5 * pi * cos(pt5*pi*P.x);
        Ev->u[q] -= 0.0; //g * phi * data[1] * pt5 * pi * cos(pt5*pi*P.y);
      }
    }
  }

  /** \note If you subtract in apply() you add in adjoint_apply(). */
  void adjoint_apply(const Scalar time, const vField &State,
                     const vField &U, vField &F) {
    if (verb>2) comm->cout() << "ForceSource::adjoint_apply(...)"
                             << data[0] << ", " << data[1] << endl;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[0]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        const Scalar ut = U[1]->el[e]->u[q];
        const Scalar vt = U[2]->el[e]->u[q];
        const Point &P = (*E->C)[q];
        const Scalar g = ic.G(P);
        E->u[q] += g * ( data[0] * ut * pt5 * pi * cos(pt5*pi*P.x) +
                         0.0 * data[1] * vt * pt5 * pi * cos(pt5*pi*P.y) );
      }
    }
  }

  /// Register that this is a Ctrl
  inline Ctrl* ctrl() { return this; }

  /// Register that this is a Ctrl
  inline const Ctrl* ctrl() const {  return this; }

  // Implement required Ctrl methods

  /// Set the Ctrl storage vector to the input vector
  virtual void set_data( const dVector &in ) {
    if (verb>1 && owner()) cout << "set_data "<<in[0]<<", "<<in[1]<<endl;
    if (owner()) data = in;
    comm->Broadcast(data.ptr(),numeric_cast<int>(data.size()));
  }

  /// returns true if fill is implemented
  virtual bool has_fill() const { return true; }

  /// Fill the output vector with the reference wavelet
  virtual void fill(const Scalar time, dVector &out) const {
    if (owner()) {
      out[0] = data0[0]; out[1] = data0[1];
    }
  }

  /** \note Simply implements a Euclidean inner product. */
  virtual Scalar inner_product(const dVector &Y) const {
    return data[0]*Y[0] + data[1]*Y[1];
  }

  /** \todo This is close, but check the signs. */
  virtual void objective_function_gradient(const vField &S, const vField &A,
    const Scalar time, dVector &G) const
  {
    assert( G.size() == data.size() );
    G = zero;
    dVector grad(G.size(),zero);
    for (LocalSize e=0; e<S[0]->ne; e++) {
      Element *E1 = A[1]->el[e];
      Element *E2 = A[2]->el[e];
      dVector dhdx(E1->qtot);
      dVector dhdy(E2->qtot);
      for (LocalSize q=0; q<E1->qtot; q++) {
        const Scalar phi = S[0]->el[e]->u[q];
        //const Scalar phit = A[0]->el[e]->u[q];
        const Scalar thetat = A[1]->el[e]->u[q];
        //const Scalar psit = A[2]->el[e]->u[q];
        const Point &P = (*S[0]->el[e]->C)[q];
        const Scalar g = ic.G(P);
        dhdx[q] = g * phi * thetat * pt5 * pi * cos(pt5*pi*P.x);
             // + phit * sin(pt5*pi*P.x); // should only be at the initial time
        dhdy[q] = 0.0; // -g * phi * psit   * pt5 * pi * cos(pt5*pi*P.y);
      }
      grad[0] += E1->integrate(dhdx);
      grad[1] += E2->integrate(dhdy);
    }
    daxpy( penalty, data, grad );                // Tikhanov regularization
    comm->SumAll(grad.ptr(),G.ptr(),numeric_cast<int>(G.size()));
  }

  /** \note Perhaps it would better to have the option to set a
      random direction. */
  virtual void set_direction( dVector &dir ) {
    data[0] = 1.0; data[1] = 0.0;
    if (owner()) {
      assert( dir.size() == data.size() );
      dir[0] = data[0]; dir[1] = data[1];
    }
  }

  virtual bool steady() const { return true; }

  virtual void plot( const vField &state, const Size offset,
                     const dVector &Gphi,
                     const Ordinal npredict, const Ordinal ntout,
                     const Ordinal nsstep, const Ordinal riter) const {
    dVector dv;
    const Ordinal i = 0;
    assert( data_size() == 2 );
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              numeric_cast<Ordinal>(offset+(nsstep*i)*data_size()),data_size());
    comm->cout() << dv[0] << " " << dv[1] << endl;
  }

  /** Each mpi rank has a copy of the Ctrl so don't use parallel IO
      but make sure that this Ctrl is replicated. */
  virtual bool get_parallel_info( Size &glen, CMC::Vector<Size,Ordinal> &disp,
                                  CMC::Vector<Ordinal,Ordinal> &len) const {
    assert( replicated() == true );
    glen = size();
    if (owner()) {
      disp.resize(size());
      len.resize(size());
      disp = 0;
      len = size();
    }
    return true;
  }

};

//===========================================================================
//                          Force Source Ctrl II
//===========================================================================

/// A steady force control 
class Shallow::ForceSourceCtrlII : public Source, public Ctrl {
  const DGM::Comm::Ptr comm;     ///< Communicator
  Bore ic;                       ///< reference
  int verb;                      ///< verbosity level
  dVector data0;                 ///< initial data
public:
  ForceSourceCtrlII(const string tag, ifstream &in, DGM::Comm::Ptr comm_) :
    Source(tag), Ctrl(0.0,1), comm(comm_), verb(0) {
    scan_lb(in);
#if 1
    Json::Value root;
    Json::Reader reader;
    string buffer = read_block(in);
    bool parsingSuccessful = reader.parse(buffer,root,true);
    if (!parsingSuccessful) {
      comm->cout()<<"Shallow::ForceSourceCtrlII could not "
                    "parse Json input"<<endl;
      comm->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
    verb = root.get("Verbosity",verb).asInt();
    x0 = root.get("x0",0.0).asDouble();
    y0 = root.get("y0",0.0).asDouble();
    t0 = root.get("t0",0.0).asDouble();
    sigmax = root.get("Sigma x",0.0).asDouble();
    sigmay = root.get("Sigma y",0.0).asDouble();
    sigmat = root.get("Sigma t",0.0).asDouble();
    hamp = root.get("Hamp",1.0).asDouble();
#else
    // SSC:  keep the old stuff around for reference but it can be removed
    if (!(in >> x0 >> y0 >> t0 >> sigmax >> sigmay >> sigmat >> hamp))
      throw DGM::exception("Shallow::ForceSourceCtlII::Cannot read data.");
#endif
    scan_rb(in);
    if ( (sigmax <= 0) || (sigmay <= 0) || (sigmat <= 0) )
      throw DGM::exception("In ForceSourceCtrlII standard deviation of the "
                           "source is less than or equal to zero.");
    s2x2i = one/( 2.0 * pow(sigmax,2) );
    s2y2i = one/( 2.0 * pow(sigmay,2) );
    s2t2i = one/( 2.0 * pow(sigmat,2) );

    penalty = root.get("Penalty",penalty).asDouble();
    data0.resize(1);
    data0[0] = root.get("Hamp",0.0).asDouble();

    // SSC: this shouldn't be here...?
    // scan_rb(in);

    if (verb) {
      Json::StyledWriter writer;
      string output = writer.write(root);
      comm->cout() << "Shallow::ForceSourceCtrlII parameters:\n" << output;
    }

    // set the size to 1 since we have one control variable: Hamp
    set_size(1);
    initialize();

    data[0] = data0[0];

    // This Ctrl object is replicated across the parallel machine and only the
    // master actually owns a part of the global control vector
    replicated(true);
    if (comm->Master())
      owner(true);
    else
      owner(false);
  }

  /// Destructor
  virtual ~ForceSourceCtrlII() {}

  // Implement required Source methods

  /// Apply this source control to the State
  void apply(const Scalar time, const vField &U, vField &F) {
    if (verb>2) comm->cout() << "ForceSourceCtrlII::apply() hamp:"
                             << data[0] << endl;
//    if(data[0]<0.0) {
//      comm->cerr()<<" ForceSourceCtrlII::apply() Updated value of "
//                    "control variable is not realizable" << endl;
//      comm->exit();
//    }

    //Scalar pertH = data[0] - hamp;
    //hamp = data[0];
    //cout << " Going to compute Gauss3d WITH hamp = " << hamp << endl;
    for (LocalSize e=0; e<F[0]->ne; e++) {
      Element *E = F[0]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) {
        const Point &P = (*E->C)[q];
        E->u[q] -= Gauss3D( P, time, data[0] );
      }
    }
  }

  /** \note If you subtract in apply() you add in adjoint_apply(). */
  void adjoint_apply(const Scalar time, const vField &State,
                     const vField &U, vField &F) {}

  /// Register that this is a Ctrl
  inline Ctrl* ctrl() { return this; }

  /// Register that this is a Ctrl
  inline const Ctrl* ctrl() const {  return this; }

  // Implement required Ctrl methods

  /// Set the Ctrl storage vector to the input vector
  virtual void set_data( const dVector &in ) {
    if (verb>1 && owner()) cout << "set_data "<<in[0]<<", "<<in[1]<<endl;
    if (owner()) data = in;
    comm->Broadcast(data.ptr(),numeric_cast<int>(data.size()));
  }

  /// returns true if fill is implemented
  virtual bool has_fill() const { return true; }

  /// Fill the output vector with the reference solution 
  virtual void fill(const Scalar time, dVector &out) const {
    if (owner()) {
      out[0] = data0[0];
    }
  }

  /** \note Simply implements a Euclidean inner product. */
  virtual Scalar inner_product(const dVector &Y) const {
     return data[0]*Y[0];
  }

  /** \todo This is close, but check the signs. */
  virtual void objective_function_gradient(const vField &S, const vField &A,
    const Scalar time, dVector &G) const {
    assert( G.size() == data.size() );
    G = zero;
    dVector grad(G.size(),zero);
    //comm->cout() << " Going to compute Gauss3d WITH hamp = " << hamp << endl;
    //Scalar pertH = data[0] - hamp;
    for (LocalSize e=0; e<S[0]->ne; e++) {
      Element *E0 = A[0]->el[e];
      dVector wsrc(E0->qtot);
      for (LocalSize q=0; q<E0->qtot; q++) {
        const Scalar w1 = A[0]->el[e]->u[q];
        const Point &P = (*S[0]->el[e]->C)[q];
        const Scalar GaussSource = Gauss3D( P, time, data[0] );
        wsrc[q] = (w1/data[0]) * GaussSource;
      }
      grad[0] += E0->integrate(wsrc);
    }
    daxpy( penalty, data, grad );                // Tikhanov regularization
    comm->SumAll(grad.ptr(),G.ptr(),numeric_cast<int>(G.size()));
  }

  /** \note Perhaps it would better to have the option to set a
      random direction. */
  virtual void set_direction( dVector &dir ) {
    data[0] = 1.0;
    if (owner()) {
      assert( dir.size() == data.size() );
      dir[0] = data[0];
    }
  }

  virtual bool steady() const { return true; }

  virtual void plot( const vField &state, const Size offset,
                     const dVector &Gphi,
                     const Ordinal npredict, const Ordinal ntout,
                     const Ordinal nsstep, const Ordinal riter) const {
    dVector dv;
    const Ordinal i = 0;
    assert( data_size() == 1 );
    dv.alias( *(const_cast<dVector*>(&Gphi)),
              numeric_cast<Ordinal>(offset+(nsstep*i)*data_size()),data_size());
    comm->cout() << dv[0] << endl;
  }

  /** Each mpi rank has a copy of the Ctrl so don't use parallel IO
      but make sure that this Ctrl is replicated. */
  virtual bool get_parallel_info( Size &glen, CMC::Vector<Size,Ordinal> &disp,
                                  CMC::Vector<Ordinal,Ordinal> &len) const {
    assert( replicated() == true );
    glen = size();
    if (owner()) {
      disp.resize(size());
      len.resize(size());
      disp = 0;
      len = size();
    }
    return true;
  }

private:

  Scalar x0, y0, t0, sigmax, sigmay, sigmat, hamp;
  Scalar s2x2i, s2y2i, s2t2i;

  Scalar Gauss3D(const Point &C, const Scalar &t, const Scalar &amp) const {
    const Scalar deltax2 = pow(C.x-x0,2);
    const Scalar deltay2 = pow(C.y-y0,2);
    const Scalar deltat2 = pow(t-t0,2);
    const Scalar value = (deltax2*s2x2i)+(deltay2*s2y2i)+(deltat2*s2t2i);
    const Scalar hsrc = amp * exp(-value);
    return hsrc;
  }
};

//===========================================================================
//                          Gaussian Source
//===========================================================================

/// Gaussian in time and Gaussian in x and y
class Shallow::GaussianSource : public Source {
  int verb;
public:
  GaussianSource(const string tag, ifstream &in) :
    Source(tag), verb(0) {
    scan_lb(in);
#if 1
    Json::Value root;
    Json::Reader reader;
    string buffer = read_block(in);
    bool parsingSuccessful = reader.parse(buffer,root,true);
    if (!parsingSuccessful) {
      DGM::Comm::World->cout()<<"Shallow::GaussianSource could not "
                                "parse Json input"<<endl;
      DGM::Comm::World->cout()<<reader.getFormattedErrorMessages();
      throw DGM::exception("Json parsing error");
    }
    verb = root.get("Verbosity",verb).asInt();
    x0 = root.get("x0",0.0).asDouble();
    y0 = root.get("y0",0.0).asDouble();
    t0 = root.get("t0",0.0).asDouble();
    sigmax = root.get("Sigma x",0.0).asDouble();
    sigmay = root.get("Sigma y",0.0).asDouble();
    sigmat = root.get("Sigma t",0.0).asDouble();
    hamp = root.get("Hamp",1.0).asDouble();
#else
    // SSC:  keep the old stuff around for reference but it can be removed
    if (!(in >> x0 >> y0 >> t0 >> sigmax >> sigmay >> sigmat >> hamp))
      throw DGM::exception("Shallow::GaussianSource::Cannot read data.");
#endif
    scan_rb(in);
    if ( (sigmax <= 0) || (sigmay <= 0) || (sigmat <= 0) )
      throw DGM::exception("In GaussianSource Standard deviation of the "
                           "source is less than or equal to zero.");
    s2x2i = one/( 2.0 * pow(sigmax,2) );
    s2y2i = one/( 2.0 * pow(sigmay,2) );
    s2t2i = one/( 2.0 * pow(sigmat,2) );
  }

 void apply(const Scalar time, const vField &, vField &F) {
    if (verb>1)
      F.get_comm()->cout() << "GaussianSource::apply() time = " << time << endl;
    // Only put the source term in the first Field which is height
    for (LocalSize e=0; e<F[0]->ne; e++) { // Loop over elements
      Element *E = F[0]->el[e];
      for (LocalSize q=0; q<E->qtot; q++) { // Loop over quadrature pts
        E->u[q] -= Gauss3D( (*E->C)[q], time );
      }
    }
  }

 /** \note This is supposed to be a null op. */
  void adjoint_apply(const Scalar, const vField &, const vField &, vField &) {}

private:

  Scalar x0, y0, t0, sigmax, sigmay, sigmat, hamp;
  Scalar s2x2i, s2y2i, s2t2i;

  Scalar Gauss3D(const Point &C, const Scalar t) {
    const Scalar deltax2 = pow(C.x-x0,2);
    const Scalar deltay2 = pow(C.y-y0,2);
    const Scalar deltat2 = pow(t-t0,2);
    const Scalar value = (deltax2*s2x2i)+(deltay2*s2y2i)+(deltat2*s2t2i);
    const Scalar hsrc = hamp * exp(-value);
    return hsrc;
  }
};

} // namespace Reo

#endif  // REO_SHALLOW_HPP

#else // DGM_REMOVE_FOR_RELEASE
// This capability is under development.
#endif // DGM_REMOVE_FOR_RELEASE

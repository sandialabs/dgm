/** \file AdvDiff2dFD.cpp
    \brief Implementation of AdvDiff 2D finite difference methods.
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"

// DGM includes
#include "Format.hpp"

// Reo includes
#include "AdvDiff2dFD.hpp"

// Trilinos includes
#include "Teuchos_RCP.hpp"
#include "Teuchos_Time.hpp"

// Make the Teuchos tuple available
using Teuchos::Array;
using Teuchos::ArrayRCP;

// Make FDM finite-difference coefficients available
using FDM::c1_o4;
using FDM::c2_o4;

using FDM::c1_o6;
using FDM::c2_o6;
using FDM::c3_o6;

using FDM::c1_o8;
using FDM::c2_o8;
using FDM::c3_o8;
using FDM::c4_o8;

using FDM::c1_o10;
using FDM::c2_o10;
using FDM::c3_o10;
using FDM::c4_o10;
using FDM::c5_o10;

using FDM::c1_o12;
using FDM::c2_o12;
using FDM::c3_o12;
using FDM::c4_o12;
using FDM::c5_o12;
using FDM::c6_o12;

namespace Reo {

//=============================================================================
// AdvDiff2dFD mesh
AdvDiff2dFD::AdvDiff2dFD(const FDM::CartesianMeshPtr mesh,
                         Json::Value &root,
                         std::string ext) :
  FDM::Domain( mesh,
               root["Domain"]["t0"].asDouble(),
               root["Domain"]["dt"].asDouble(),
               root["Domain"]["Nt"].asInt(),
               root["Domain"]["Ntout"].asInt(),
               root["Domain"]["Nfout"].asInt()),
  _root(root),
  BC_db(),
  _mesh(mesh),
  _order(root["Domain"]["order"].asInt()),
  _halo(_order/2),
  _dx(),
  _dy(),
  _dxi(),
  _dyi(),
  _nProbe(0),
  _probes(),
  _trace()
{
#ifdef REO_FD_CODETRACE
  out() << "AdvDiff2dFD constructor" << endl;
#endif
  // Require 2D mesh
  if (mesh->numDims() != 2)
    throw std::invalid_argument("AdvDiff2dFD mesh is not 2D");

  // check the finite difference order to make sure that it is supported
  if (_order < FDM::min_order || _order > FDM::max_order || _order%2 != 0 )
    throw DTK::exception("Unsupported finite-difference order");

  // Set the mesh sizes
  Domi::MDArrayView< const FDM::Scalar > x = _mesh->getCoordinates(0);
  Domi::MDArrayView< const FDM::Scalar > y = _mesh->getCoordinates(1);
  _dx = x(1) - x(0);
  if (_dx == 0)
    throw std::invalid_argument("Mesh coordinates x not properly specified");
  _dy = y(1) - y(0);
  if (_dy == 0)
    throw std::invalid_argument("Mesh coordinates y not properly specified");
  _dxi = 1.0 / _dx;
  _dyi = 1.0 / _dy;

  // Create the solution Fields
  createField("u"+ext, "solution", Teuchos::tuple(1,1));

  // Create the convective velocity
  createField("cx", "cx", Teuchos::tuple(0,1));
  createField("cy", "cy", Teuchos::tuple(1,0));

  // Initialize the constants and Fields
  initialize();
}

//=============================================================================
void AdvDiff2dFD::initialize() {

  // Initialize the solution Fields
  FDM::Field &u = *field("u");
  u.getMDVector()->putScalar(0.0);
  u.updateCommPad();

  // Initialize the convective Fields
  FDM::Field &cx = *field("cx");
  FDM::Field &cy = *field("cy");
  const double c_x = _root["Domain"]["c_x"].asDouble();
  const double c_y = _root["Domain"]["c_y"].asDouble();
  out() << "Setting convective velocity to (" << c_x << "," << c_y << ")"
        << endl;
  cx.putScalar(c_x);
  cy.putScalar(c_y);
  cx.updateCommPad();
  cy.updateCommPad();

  // Output the convective field
  cx.writeBinary(0, false);
  cy.writeBinary(0, false);

  // setup U, solution VectorField
  getU().push_back( field("u") );

  // setup time integration method
  const string method =
    _root["Domain"].set("Time method","TVD").asString();
  if (DGM::lowerCase(method)=="leapfrog")
    timeMethod(LeapFrog);
  else if (DGM::lowerCase(method)=="rungekutta")
    timeMethod(RungeKutta);
  else if (DGM::lowerCase(method)=="tvd")
    timeMethod(TVD);
  else {
    out() << "AdvDiff2dFD: Unavailable time integration method "
          << method << endl;
    std::exit(EXIT_FAILURE);
  }

  // Create temporary Fields and VectorField if needed
  if (timeMethod() != LeapFrog) {
    createField("ut", "Temporary solution"  , Teuchos::tuple(1,1));
    // setup Ut, temporary solution VectorField
    getUt().push_back( field("ut") );
    getUt().zero();
    for (FDM::VectorField::size_type n = 0; n < getUt().size(); ++n)
      getUt()[n]->updateCommPad();
  }

  // Set up the time integrator
  switch (timeMethod()) {
  case RungeKutta:
    timeIntegrator(Teuchos::rcp(new DTK::RungeKutta
                                < FDM::Scalar,
                                  FDM::Ordinal,
                                  FDM::VectorField,
                                  FDM::Domain >(this)));
    break;
  case TVD:
    timeIntegrator(Teuchos::rcp(new DTK::TVD
                                < FDM::Scalar,
                                  FDM::Ordinal,
                                  FDM::VectorField,
                                  FDM::Domain >(this)));
    break;
  case LeapFrog:
    break;
  default:
    out() << "AdvDiff2dFD: Unavailable time integration method "
          << method << endl;
    std::exit(EXIT_FAILURE);
  }

  setup_sources();
  setup_receivers();
  setup_initial_condition();
  setup_boundary_conditions();
}

//=============================================================================
/** \deprecated This is kept for compatibility with LeapFrog, should remove. */
void AdvDiff2dFD::computeSource(const FDM::Scalar time) {
  const FDM::Scalar dt = timeStep();
  FDM::VectorField  F;
  F.push_back( field("u") );
  applySource(time, getU(), F, -dt);
}

//=============================================================================
// Output all the probes
void AdvDiff2dFD::outputProbes() {
  Teuchos::Array< FDM::Scalar > localValues( _nProbe,0.0);
  Teuchos::Array< FDM::Scalar > globalValues(_nProbe,0.0);
  FDM::FieldPtr u = field("u");

  // Compute the local results
  Teuchos::Array< FDM::Kernel::Ptr >::iterator it;
  for (it = _probes.begin(); it != _probes.end(); ++it) {
    FDM::Kernel::Ptr probe = *it;
    localValues[probe->id()] = probe->apply(*u,1.0);
  }

  // Sum up the local results into a global array
  const int nProbe = _nProbe;
  Teuchos::reduceAll(*getComm(), Teuchos::REDUCE_SUM, nProbe,
                     localValues.getRawPtr(), globalValues.getRawPtr());

#if 0
  // Write the results from the owning processor
  Array< ProbeFile >::iterator pf;
  for (pf = _probefiles.begin(); pf != _probefiles.end(); ++pf) {
    FDM::Ordinal id = pf->id;
    FDM::Kernel::Ptr probe;
    for (it = _probes.begin(); it != _probes.end(); ++it) {
      probe = *it;
      if (probe->id() == id) break;
    }
    if (it != _probes.end()) {
      Teuchos::Array< FDM::Scalar > center = probe->center();
      int ierr = fprintf(pf->file, "%e %e %e %e\n",
                         time(), globalValues[id], center[0], center[1] );
      if (ierr < 0) perror("Error message");
      fflush(pf->file);
    }
  }
#endif
}

//=============================================================================
// Output the trace
void AdvDiff2dFD::outputTrace(std::string & tracename)
{
  // Initialize
  FDM::Field u = *field("u");
  Domi::Slice bounds = u.getLocalBounds(0);
  // Output the solution trace along the trace line
  for (FDM::Ordinal procID = 0; 
     procID < (FDM::Ordinal)getComm()->getSize(); procID++)
  {
    if (procID == (FDM::Ordinal)getRank())
    {
      if (_trace.size() > 0)
      {
        FILE * traceFile = fopen(tracename.c_str(), "a");
        for (FDM::Ordinal i = bounds.start();  
              i < (FDM::Ordinal)bounds.stop(); ++i)
        {
          float tmp = 0.0;
          for (Array< FDM::InterpInfo >::iterator it = _trace.begin();
              it != _trace.end(); ++it)
            tmp += u(i, it->index[1]) * it->weight;
          fwrite(&tmp, sizeof(float), 1, traceFile);
        }
        fclose(traceFile);
      }
    }
    getComm()->barrier();
  }
}

//=============================================================================

/// Solve interface
int AdvDiff2dFD::solve() {

  // Initialization
  static DGM::Format sci(4, 12, 'e');
  FDM::CommPtr comm = _mesh->getComm();

  // Obtain the coordinates
  Domi::MDArrayView< const FDM::Scalar > x = _mesh->getCoordinates(0);
  Domi::MDArrayView< const FDM::Scalar > y = _mesh->getCoordinates(1);

  // Field initialization
  FDM::Field &u  = *field("u");
  FDM::Field &cx = *field("cx");
  FDM::Field &cy = *field("cy");

  // Loop upper bounds
  Domi::Slice xBounds = u.getLocalBounds(0);
  Domi::Slice yBounds = u.getLocalBounds(1);

  // Output the solution dimensions
  // out() << "Nx = " << nxu << ", Ny = " << nyu << endl;

  // Initialize the trace file
  std::string tracename = "trace.bin";
  if (getRank() == 0)
  {
    // This will clear the trace file for this run
    FILE * tracefile = fopen(tracename.c_str(), "w");
    fclose(tracefile);
  }

  Json::StyledWriter writer;
  string input = writer.write(_root);
  if (_root["Verbosity"].asInt() > 0)
  {
    out() << "Reo::FD::AdvDiff2dFD running with input:\n" << input;
  }

  // echo the input
  if (getRank() == 0)
  {
    ofstream echo("echo.inp");
    echo << input;
  }

  switch (timeMethod())
  {
  case RungeKutta:
  case TVD:
  case LSRK14:
  {
    // Initialize the timer
    Teuchos::Time timer("AdvDiff2dFD Time");

    // Initialize time stepping
    startTimeStepping();

    // Output the initial conditions
    u.writeBinary(stepNumber(), false);
    outputProbes();
    outputTrace(tracename);

    // Time stepping
    while (!finished()) {
      timer.start(true);
      timeIntegrator()->advance(this);
      advanceStep();
      FDM::Scalar t = time();

      // Output the pressure at the probe points
      outputProbes();

      // Output the trace
      outputTrace(tracename);

      if (stepNumber() % timeOutInterval() == 0)
        out() << std::setw(4) << stepNumber() << sci(t)
              << sci(timer.stop()) << endl;

      if (stepNumber() % fieldOutInterval() == 0) {
        out() << "Field:  u" << sci(u.normInf()) << sci(u.norm2())
              << sci(u.norm1()) << " (Linf, L2, L1)" << endl;
        u.writeBinary(stepNumber(), false);
      }
    }
    break;
  }
  case LeapFrog:
  {
    throw std::logic_error("LeapFrog is not currently supported");

    // Initialize the timer
    Teuchos::Time timer("AdvDiff2dFD Time");

    // Initialize time stepping
    FDM::Scalar dt = timeStep();
    startTimeStepping();

#ifdef REO_FD_COMPUTE_CFL
    // Verify the CFL condition (needs to be generalized)
    FDM::Scalar maxDt = _dx / (c * sqrt(2.0));
    out() << "Maximum stable timestep = " << maxDt
                 << ", current timestep = " << dt << endl;
    if (dt > maxDt)
    {
      out() << "WARNING: CFL limit exceeded" << endl;
      std::exit(EXIT_FAILURE);
    }
#endif

    // Output a slice at the intial condition
    u.writeBinary(stepNumber(), false);
    cx.writeBinary(stepNumber(), false);
    cy.writeBinary(stepNumber(), false);

    // Main time stepping loop
    while (!finished()) {
      timer.start(true);

      // First half of time step
      FDM::Scalar t = time();

      // convection
      switch (_order)
      {
      case 2:
      {
        for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
        {
          for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
          {
          }
        }
        break;
      }
      case 4:
      {
        for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
        {
          for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
          {
          }
        }
        break;
      }
      case 6:
      {
        for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
        {
          for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
          {
          }
        }
        break;
      }
      case 8:
      {
        for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
        {
          for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
          {
          }
        }
        break;
      }
      default:
        out() << "Invalid finite difference order = " << _order << endl;
        std::exit(EXIT_FAILURE);
      }

      // Compute the source
      computeSource(t);

      // Update the pressure halo values
      u.updateCommPad();

      // Advance time a half step
      t += 0.5 * dt;

      // Output the pressure at the probe points
      outputProbes();

      // Output the trace
      outputTrace(tracename);

      // Now do advance time remaining half-step
      t += 0.5 * dt;

      // Advance the Domain time index
      advanceStep();

      // Output the timestep statistics
      if (stepNumber() % timeOutInterval() == 0)
        out() << std::setw(4) << stepNumber() << sci(t)
              << sci(timer.stop()) << endl;

      // Output the field norms and a slice of the solution in SU
      // binary format
      if (stepNumber() % fieldOutInterval() == 0) {
        out() << "Field:  u" << sci(u.normInf()) << sci(u.norm2())
              << sci(u.norm1()) << " (Linf, L2, L1)" << endl;
        u.writeBinary(stepNumber(), false);
      }

    }  // while loop
    break;
  }
  default:
    out() << "Invalid time integration method " << endl;
    std::exit(EXIT_FAILURE);
  }
  return 0;
}

//=============================================================================
void AdvDiff2dFD::time_derivative(FDM::VectorField &S,
                                  FDM::VectorField &R)
{
  // Obtain the coordinates
  Domi::MDArrayView< const FDM::Scalar > x = _mesh->getCoordinates(0);
  Domi::MDArrayView< const FDM::Scalar > y = _mesh->getCoordinates(1);

  // Field initialization
  FDM::Field &u = *S[0];

  u.updateCommPad();

  // Get residual fields
  FDM::Field &ut = *R[0];

  ut.updateCommPad();

  // get medium parameters
  FDM::Field &cx = *field("cx");
  FDM::Field &cy = *field("cy");

  cx.updateCommPad(0);
  cy.updateCommPad(1);

  // Loop upper bounds
  Domi::Slice xBounds = u.getLocalBounds(0);
  Domi::Slice yBounds = u.getLocalBounds(1);

#if 0
  for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
  {
    out() << "j = " << j << ", u(-1,j)=" << u(-1,j) << ", u(0,j)=" << u(0,j)
          << endl;
    out() << "j = " << j << ", u(nxu-1,j)=" << u(yBounds.stop()-1,j)
          << ", u(nxu,j)=" << u(yBounds.stop(),j) << endl;
  }
#endif

#if 0
  for (Domi::dim_type i = xBounds.start()-1; i < xBounds.stop()+2; ++i)
  {
    const double xl = 0.5 * (x(i) + x(i+1));
    std::cout << i << ", " << x(i) << ", " << xl << std::endl;
  }
  std::cout << "nxu = " << xBounds.stop() << std::endl;
#endif

  //std::cout << "nxl = " << xBounds.start() << std::endl;
  //std::cout << "nxu = " << xBounds.stop() << std::endl;

  // SSC:  explicitly enforce periodicity (why isn't this automatic?)
  // WFS:  this should now be automatic with use of MDVectors
#if 0
  for (FDM::Ordinal j = yBounds.start(); j < yBounds.stop(); ++j) {
    u(xBounds.start()-1,j) = u(xBounds.stop()-1,j);
    u(xBounds.stop(),j) = u(xBounds.start(),j);
  }
  for (FDM::Ordinal i = xBounds.start(); i < xBounds.stop(); ++i) {
    u(i,yBounds.start()-1) = u(i,yBounds.stop()-1);
    u(i,yBounds.stop()) = u(i,yBounds.start());
  }
#endif

#define FDM_USE_FV = 1

  // Solution
  switch (_order)
  {
  case 2:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
#ifdef FDM_USE_FV
        const double fip = 0.5 * cx(i+1,j) * (u(i+1,j) + u(i,  j));
        const double fim = 0.5 * cx(i,  j) * (u(i  ,j) + u(i-1,j));
        const double fjp = 0.5 * cy(i,j+1) * (u(i,j+1) + u(i,  j));
        const double fjm = 0.5 * cy(i,  j) * (u(i  ,j) + u(i,j-1));
        ut(i,j) = ((fip - fim) * _dxi + (fjp - fjm) * _dyi);
#else
        // this is only true for constant c
        ut(i,j) = (0.5 * cx(i,j) * (u(i+1,j) - u(i-1,j)) * _dxi +
                   0.5 * cy(i,j) * (u(i,j+1) - u(i,j-1)) * _dyi );
#endif
      }
    }
    break;
  }
  case 4:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
      }
    }
    break;
  }
  case 6:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
      }
    }
    break;
  }
  case 8:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
      }
    }
    break;
  }
  case 10:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
      }
    }
    break;
  }
  case 12:
  {
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
      }
    }
    break;
  }
  default:
    out() << "Invalid finite difference order = " << _order <<endl;
    std::exit(EXIT_FAILURE);
  }

  // Compute the source
  FDM::Scalar t = time();

  applySource(t,S,R);

  // Update residuals so that the halo regions are current
  ut.updateCommPad();
}

//=============================================================================
void AdvDiff2dFD::prestep(FDM::VectorField &,
                          const FDM::Ordinal,
                          const FDM::Ordinal,
                          const FDM::Scalar) { }

//=============================================================================
void AdvDiff2dFD::poststep(FDM::VectorField &,
                           const FDM::Ordinal,
                           const FDM::Ordinal,
                           const FDM::Scalar) { }

//=============================================================================
void AdvDiff2dFD::applySource(const FDM::Scalar time,
                              const FDM::VectorField &S,
                              FDM::VectorField &R) {
  applySource(time,S,R,1.0);
}

//=============================================================================
void AdvDiff2dFD::applyBC(const FDM::Scalar time,
                          FDM::VectorField &R) {
  applyBC(time,R,1.0);
}

//=============================================================================
/** Setup the source terms. */
void AdvDiff2dFD::setup_sources() {
  //Json::Value &root(_root);
  // Set the constants (default values)
  //const FDM::Ordinal gnx = getGlobalShape(0);
  //const FDM::Ordinal gny = getGlobalShape(1);
  // LeapFrog needs a factor on the source
  //const FDM::Scalar dt = root["Domain"]["dt"].asDouble();
  //FDM::Scalar fact(1);
  //switch (timeMethod()) {
  //case LeapFrog:
  //  fact = -dt;
  //  break;
  //default:
  //  fact = 1.0;
  //}
  // Setup the source database
  //SourcePtr psrc;
  //if (root.isMember("Source")) {
  //  // put sources here
  //}
}

//=============================================================================
// Source validator
void AdvDiff2dFD::validate_sources() const {
  const Json::Value &root(_root);
  const Json::Value &source(root["Source"]);
  const std::string type = source["Type"].asString();
  const FDM::Ordinal verb = source["Verbosity"].asInt();
  const FDM::Scalar amp = source["Amplitude"].asDouble();
  const FDM::Scalar fp  = source["fp"].asDouble();
  const FDM::Scalar t0  = source["t0"].asDouble();
  const FDM::Ordinal der = source["der"].asInt();
  // This is temporary to get rid of unused variable warnings
  if (verb > 4) {
    out() << "Source parameters: " << endl
          << amp << t0 << der << endl;
  }
  if (fp < 0) {
    out() << "The peak frequency of the source wavelet must be "
          << "nonnegative" << endl;
    std::exit(EXIT_FAILURE);
  }
}

//=============================================================================
/** Setup the receivers. */
void AdvDiff2dFD::setup_receivers() { }

//=============================================================================
/** Setup the intitial condition */
void AdvDiff2dFD::setup_initial_condition() {
  Json::Value &root(_root);
  Json::Value &ic = root["Initial condition"];
  const FDM::Ordinal verb = ic.set("Verbosity",0).asInt();
  const std::string type = ic.set("Type","None").asString();

  // Set the constants (default values)
  const FDM::Ordinal gnx = getGlobalDim(0);
  const FDM::Ordinal gny = getGlobalDim(1);

  // Obtain the coordinates
  Domi::MDArrayView< const FDM::Scalar > x = _mesh->getCoordinates(0);
  Domi::MDArrayView< const FDM::Scalar > y = _mesh->getCoordinates(1);

  FDM::Field &u = *field("u");

  // Get local bounds and dims
  Domi::Slice xBounds = u.getLocalBounds(0,false);
  Domi::Slice yBounds = u.getLocalBounds(1,false);
  const FDM::Ordinal nxu = u.getLocalDim(0,false);
  const FDM::Ordinal nyu = u.getLocalDim(1,false);

  // Initial conditions
  if (DGM::lowerCase(type) == "none")
  {
    u.getMDVector()->putScalar(0.0);
    u.updateCommPad();
  }
  else if (DGM::lowerCase(type) == "function")
  {
    out() << "Setting function initial conditions" << endl;
    FDM::ScalarVector xl(nxu*nyu), yl(nxu*nyu);
    for (FDM::Ordinal j = yBounds.start(); 
       j < (FDM::Ordinal)yBounds.stop(); ++j)
    {
      FDM::Ordinal jj = j - yBounds.start();
      for (FDM::Ordinal i = xBounds.start(); i < 
          (FDM::Ordinal)xBounds.stop(); ++i)
      {
        FDM::Ordinal ii = i - xBounds.start();
        xl(jj*nxu+ii) = u.getCoordinateAtPoint(i,0);
        yl(jj*nxu+ii) = u.getCoordinateAtPoint(j,1);
      }
    }
    std::string expr = ic.set("Expression","0.0").asString();
    expr += '\n';
    parser_init();
    DGM::Parser::VectorFunction f("x","y","t",expr);
    FDM::ScalarVector wk(nxu*nyu);
    f.evaluate(xl,yl,wk,0.0);
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      FDM::Ordinal jj = j - yBounds.start();
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
        FDM::Ordinal ii = i - xBounds.start();
        u(i,j) = wk(jj*nxu+ii);
      }
    }
  }
  else if (DGM::lowerCase(type) == "waves")
  {
    out()<<"Waves IC"<<endl;
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      const double yl = u.getCoordinateAtPoint(j,1);
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
        const double xl = u.getCoordinateAtPoint(i,0);
        u(i,j) = 1.0 - cos(1.0 * M_PI * xl) * cos(1.0 * M_PI * yl);
      }
    }
    u.updateCommPad();
  }
  else if (DGM::lowerCase(type) == "gaussian")
  {
    const FDM::Scalar amp = ic.set("Amplitude",1.0).asDouble();
    const FDM::Scalar x0 = ic.set("x0",(gnx-1)*_dx*0.5).asDouble();
    const FDM::Scalar y0 = ic.set("y0",(gny-1)*_dy*0.5).asDouble();
    const FDM::Scalar sigma = ic.set("sigma",64.0).asDouble();
    const FDM::Scalar twos2i = 1.0 / (2.0 * pow(sigma,2));
    const FDM::Scalar sr2pi  = 1.0 / (sigma * sqrt(2.0*M_PI));
    out() << "Gaussian IC with x0 = " << x0 << ", y0 = " << y0 << endl;
    for (Domi::dim_type j = yBounds.start(); j < yBounds.stop(); ++j)
    {
      for (Domi::dim_type i = xBounds.start(); i < xBounds.stop(); ++i)
      {
        const double xl = u.getCoordinateAtPoint(i,0);
        const double yl = u.getCoordinateAtPoint(j,1);
        u(i,j) += amp * pow(sr2pi,2) *
                  exp(-(pow(xl - x0, 2) + pow(yl - y0, 2)) * twos2i);
      }
    }
    u.updateCommPad();
  }
  else
  {
    out() << "Illegal initial condition type = " << type << endl;
    std::exit(EXIT_FAILURE);
  }
  if (verb)
  {
    out() << "Need to write out IC parameters here" << endl;
  }
}

//=============================================================================
/** Apply all sources from the source database. */
void AdvDiff2dFD::applySource(const FDM::Scalar time,
                              const FDM::VectorField &S,
                              FDM::VectorField &R,
                              const FDM::Scalar fact) {
  for (Source_db_itr i = Source_db.begin(); i!=Source_db.end(); ++i) {
    i->second->apply(time,S,R);
  }
}

//=============================================================================
void AdvDiff2dFD::applyBC(const FDM::Scalar time,
                          FDM::VectorField & R,
                          const FDM::Scalar fact) {
  FDM_UNDEFINED;
}

}  // namespace Reo

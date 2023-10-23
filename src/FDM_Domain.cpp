//! \file   FDM_Domain.cpp
//! \brief  Implementation for the FDM Domain
//! \author Bill Spotz

#include <fstream>
#include <sstream>
#include "Teuchos_oblackholestream.hpp"
#include "Table.hpp"
#include "FDM_Domain.hpp"

namespace FDM
{

namespace
{

DGM::Table setup_params()
{
  DGM::Table params;
  params["incore"] = "1000";
  params["outcore"] = "1";
  params["griewank"] = "0";
  params["incore-stats"] = "2";
  return params;
}

}

// Black Hole ostream
Teuchos::oblackholestream Domain::_blackHole;

////////////////////////////////////////////////////////////////////////////////

Domain::Domain(const Scalar  startTime,
               const Scalar  timeStep,
               const Ordinal numSteps,
               const Ordinal timeOutInterval,
               const Ordinal fieldOutInterval) :
  params(setup_params()),
  _mesh(),
  _fieldSymbols(),
  _constantSymbols(),
  _fields(),
  _constants(),
  _root("domain"),
  _startTime(startTime),
  _timeStep(timeStep),
  _numSteps(numSteps),
  _timeOutInterval(timeOutInterval),
  _fieldOutInterval(fieldOutInterval),
  _stepNumber(0),
  _time(startTime),
  _timeMethod(LeapFrog),
  _pout(&std::cout),
  _perr(&std::cerr)
{
  if (_timeOutInterval  <= 0) _timeOutInterval  =  20;
  if (_fieldOutInterval <= 0) _fieldOutInterval = 100;
}

////////////////////////////////////////////////////////////////////////////////

Domain::Domain(const MeshPtr mesh,
               const Scalar  startTime,
               const Scalar  timeStep,
               const Ordinal numSteps,
               const Ordinal timeOutInterval,
               const Ordinal fieldOutInterval) :
  params(setup_params()),
  _mesh(mesh),
  _fieldSymbols(),
  _constantSymbols(),
  _fields(),
  _constants(),
  _root("domain"),
  _startTime(startTime),
  _timeStep(timeStep),
  _numSteps(numSteps),
  _timeOutInterval(timeOutInterval),
  _fieldOutInterval(fieldOutInterval),
  _stepNumber(0),
  _time(startTime),
  _timeMethod(LeapFrog),
  _pout((mesh->getRank() == 0) ? &std::cout : &_blackHole),
  _perr(&std::cerr)
{
#ifdef DGM_PARALLEL
  // \warning SSC: to get the correct scratch directories, we need to use
  // the existing DGM::Comm::World.  There should be a better way but for now...
  Teuchos::RCP< const Teuchos::MpiComm<int> > teuchosMpiComm =
    Teuchos::rcp_dynamic_cast< const Teuchos::MpiComm<int> >(mesh->getComm());
  MPI_Comm rawMpiComm= *(teuchosMpiComm->getRawMpiComm()());
#if 1
  if (rawMpiComm==MPI_COMM_WORLD) {
    _dgmComm = DGM::Comm::World;
  } else {
    throw std::runtime_error("Can only run FDM::Domain on MPI_COMM_WORLD");
  }
#else
  // SSC:  this won't use the correct scratch space
  _dgmComm = DGM::MpiComm::Ptr(new DGM::MpiComm(rawMpiComm));
#endif
#else
  _dgmComm = DGM::Comm::World;
#endif
  if (_timeOutInterval  <= 0) _timeOutInterval  =  20;
  if (_fieldOutInterval <= 0) _fieldOutInterval = 100;
}

////////////////////////////////////////////////////////////////////////////////

Domain::Domain(const Domain & domain) :
  params(domain.params),
  _mesh(domain._mesh),
  _fieldSymbols(domain._fieldSymbols),
  _constantSymbols(domain._constantSymbols),
  _fields(domain._fields),
  _constants(domain._constants),
  _root(domain._root),
  _dgmComm(domain._dgmComm),
  _startTime(domain._startTime),
  _timeStep(domain._timeStep),
  _numSteps(domain._numSteps),
  _timeOutInterval(domain._timeOutInterval),
  _fieldOutInterval(domain._fieldOutInterval),
  _stepNumber(domain._stepNumber),
  _time(domain._time),
  _timeMethod(domain._timeMethod),
  _pout(domain._pout),
  _perr(domain._perr)
{
}

////////////////////////////////////////////////////////////////////////////////

Domain::~Domain()
{
}

////////////////////////////////////////////////////////////////////////////////

void Domain::addField(const FieldPtr field)
{
  // Initialize _mesh, if necessary
  if (_mesh.is_null())
  {
    _mesh = field->getMesh();
    if (getRank() != 0) _pout = &_blackHole;
  }

  // Check Field's mesh against Domain mesh
  else if (field->getMesh() != _mesh)
    throw std::invalid_argument("Field's mesh is different "
                                "from Domain's mesh");

  // Add the Field to the internal std::map
  if (_fields.count(field->symbol()) == 0)
    _fieldSymbols.push_back(field->symbol());
  _fields[field->symbol()] = field;
}

////////////////////////////////////////////////////////////////////////////////

FieldPtr Domain::createField(const string &               symbol,
                             const string &               name,
                             const ArrayView< const int > stagger)
{
  if (_mesh.is_null())
    throw std::invalid_argument("Domain Mesh has not been set yet");
  FieldPtr result = Teuchos::rcp(new Field(symbol,
                                           name,
                                           _mesh,
                                           stagger));
  addField(result);
  return result;
}

////////////////////////////////////////////////////////////////////////////////

bool Domain::hasField(const std::string & symbol) const
{
  for (int i = 0; i < _fieldSymbols.size(); ++i)
    if (_fieldSymbols[i] == symbol) return true;
  return false;
}

////////////////////////////////////////////////////////////////////////////////

FieldPtr Domain::field(const std::string & symbol)
{
  if (_fields.count(symbol) == 0)
    throw std::invalid_argument("Key '" + symbol + "' not found");
  return _fields[symbol];
}

////////////////////////////////////////////////////////////////////////////////

void Domain::setConstant(const std::string & symbol,
                         const Scalar constant)
{
  if (_constants.count(symbol) == 0)
    _constantSymbols.push_back(symbol);
  _constants[symbol] = constant;
}

////////////////////////////////////////////////////////////////////////////////

// SSC: switched to use at so preserve const
Scalar Domain::getConstant(const std::string & symbol) const
{
  if (_constants.count(symbol) == 0)
    throw std::invalid_argument("Key '" + symbol + "' not found");
  return (*_constants.find(symbol)).second;
}

////////////////////////////////////////////////////////////////////////////////

void Domain::startTimeStepping()
{
  _time       = _startTime;
  _stepNumber = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Domain::advanceTime(const int numSteps)
{
  _time       += numSteps * _timeStep;
  _stepNumber += numSteps;
}

////////////////////////////////////////////////////////////////////////////////

void Domain::global_read(const std::string & fname)
{
  std::cout << "Inside Domain::global_read()" << std::endl;
  std::ifstream in(fname.c_str());
  if (!in)
  {
    in.close();
    throw std::runtime_error("FDM::Domain::global_read(): Cannot open "
                             "filename '" + fname + "'");
  }
  std::string varname;
  long nx, ny;
  in >> varname;
  std::cout << "varname = " << varname << std::endl;
  in >> nx;
  std::cout << "nx = " << nx << std::endl;
  in >> ny;
  std::cout << "ny = " << ny << std::endl;
  if (in.fail())
  {
    in.close();
    throw std::runtime_error("FDM:Domain::global_read(): Error reading "
                             "variable name and array size from '" + fname +
                             "'");
  }
  if (hasField(varname))
  {
    FieldPtr varField = field(varname);
    Ordinal gnx = varField->getGlobalDim(0);
    Ordinal gny = varField->getGlobalDim(1);
    if (((long)gnx != nx) || ((long)gny != ny))
    {
      std::stringstream msg;
      in.close();
      msg << "Field variable '" << varname << "' shape mismatch.  Problem "
          << "shape is (" << gnx << "," << gny << "), file shape is (" << nx
          << "," << ny << ")";
      throw std::runtime_error(msg.str());
    }

    // Read in the data
    Ordinal size = numeric_cast<Ordinal>(nx * ny);
    float f;
    CMC::Vector< Scalar,Ordinal > var(size);
    for (long i = 0; i < nx; ++i)
    {
      for (long j = 0; j < ny; ++j)
      {
        in.read(reinterpret_cast<char*>(&f),4);
        const Ordinal index = numeric_cast<Ordinal>(i+nx*j);
        var[index] = (Scalar)f;
        if (in.gcount() < 4)
        {
          in.close();
          throw std::runtime_error("FDM::Domain::global_read(): unexpected "
                                   "EOF in '" + fname + "'");
        }
      }
    }

    // Copy data to local Field variable
    Ordinal lnx = varField->getLocalDim(0, true);
    Ordinal lny = varField->getLocalDim(1, true);
    Ordinal i0  = varField->getLocalInteriorBounds(0).start();
    Ordinal j0  = varField->getLocalInteriorBounds(1).start();
    Field & vf = *varField;
    const Ordinal onx = numeric_cast<Ordinal>(nx);
    for (Ordinal i = 0; i < lnx; ++i) {
      for (Ordinal j = 0; j < lny; ++j) {
        vf(i,j) = var[(i0+i) + onx*(j0+j)];
      }
    }
    // Update the communication padding
    varField->updateCommPad();
  }
  else
  {
    in.close();
    throw std::runtime_error("FDM::Domian::global_read(): Variable name '" +
                             varname + "' is not a field in domain.");
  }
  in.close();
}

////////////////////////////////////////////////////////////////////////////////

std::string Domain::mkname(const Ordinal iter,
                           const Ordinal istep,
                           const Ordinal sstep,
                           const std::string & s) const
{
  std::stringstream ss;
  ss << "state." << istep << "." << sstep << "." << _mesh->getRank() << ".rst";
  return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

void Domain::local_read(const string & fname,
                        VectorField & F,
                        HeaderType ht,
                        const bool saved_as_float)
{
  if (ht == SKIP_HEADER)
    F.local_read( fname, 0 );
  else
    F.local_read( fname, 0 );
}

////////////////////////////////////////////////////////////////////////////////

void Domain::local_read(istream & fs,
                        VectorField & F,
                        const string & fname,
                        HeaderType ht,
                        const bool saved_as_float)
{
  F.local_read(fs);
}

////////////////////////////////////////////////////////////////////////////////

void Domain::local_read_field(const string & fname,
                              VectorField & F) const
{
  F.local_read( fname, 0 );
}

////////////////////////////////////////////////////////////////////////////////

void Domain::local_write(const string & fname,
                         const VectorField & F,
                         const bool saved_as_float) const
{
  F.local_write( fname, 0 );
}

////////////////////////////////////////////////////////////////////////////////

void Domain::local_write(ostream & fs,
                         const VectorField & F,
                         const string & fname,
                         const bool save_as_float) const
{
  F.local_write( fs );
}

}  // Namespace FDM

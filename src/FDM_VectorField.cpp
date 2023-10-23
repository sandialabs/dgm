//! \file   FDM_VectorField.cpp
//! \brief  Finite Difference VectorField implementation
//! \author Bill Spotz

// FDM includes
#include "FDM_VectorField.hpp"
#include <fstream>

namespace FDM
{

////////////////////////////////////////////////////////////////////////

VectorField::VectorField()
{
}

////////////////////////////////////////////////////////////////////////

VectorField::VectorField(const VectorField *in) :
    _fields(in->_fields)
{
}

////////////////////////////////////////////////////////////////////////

VectorField::~VectorField()
{
}

////////////////////////////////////////////////////////////////////////

void
VectorField::push_back(const FieldPtr field)
{
  _fields.push_back(field);
}

////////////////////////////////////////////////////////////////////////

VectorField::size_type
VectorField::size() const
{
  return _fields.size();
}

////////////////////////////////////////////////////////////////////////

Field *
VectorField::operator[](const size_type i)
{
  return _fields[i].get();
}

////////////////////////////////////////////////////////////////////////

const Field *
VectorField::operator[](const size_type i) const
{
  return _fields[i].get();
}

////////////////////////////////////////////////////////////////////////

FieldPtr
VectorField::operator()(const FDM::Ordinal i) const
{
  return _fields[i];
}

////////////////////////////////////////////////////////////////////////

void
VectorField::fill(const Scalar value)
{
  for (VectorField::size_type i=0; i<size(); ++i)
    _fields[i]->getMDVector()->putScalar(value);
}

////////////////////////////////////////////////////////////////////////

void
VectorField::zero()
{
  for (VectorField::size_type i=0; i<size(); ++i)
    _fields[i]->getMDVector()->putScalar(0);
}

////////////////////////////////////////////////////////////////////////

VectorField *
VectorField::clone() const
{
  std::cout << "Implement VectorField clone()" << std::endl;
  return 0;
}

////////////////////////////////////////////////////////////////////////

void
VectorField::clone(const VectorField &in)
{
  for (VectorField::size_type i = 0; i < in.size(); ++i)
  {
    Field & sf = const_cast<Field &>
      (dynamic_cast< const Field & >(*(in[i])));
    // Note this operator()() is because otherwise there is an implicit
    // cast from Teuchos::ArrayRCP to Teuchos::ArrayView which is deprecated
    // Seems to me that there should be a Teuchos::ArrayRCP::getView() method.
    Field *sfp =
      new Field( sf.symbol(),
                 sf.name(),
                 sf.getMesh(),
                 sf.getStagger().operator()() /*,
                 sf.getCommPad().operator()() */ );
    _fields.push_back( FieldPtr(sfp) );
  }
}

////////////////////////////////////////////////////////////////////////

void
VectorField::random()
{
  for (VectorField::size_type i=0; i<size(); ++i)
    _fields[i]->getMDVector()->randomize();
}

////////////////////////////////////////////////////////////////////////

void
VectorField::norm() const
{
  for (VectorField::size_type i=0; i<size(); ++i)
  {
    std::cout << _fields[i]->symbol() << ": " << _fields[i]->normInf() << " "
              << _fields[i]->norm2() << " " << _fields[i]->norm1() << std::endl;
  }
}

////////////////////////////////////////////////////////////////////////

streamoff
VectorField::local_read(istream & fs)
{
  for (size_t i = 0; i < _fields.size(); i++)
  {
    Teuchos::ArrayView< Scalar > data =
      _fields[i]->getDataNonConst().arrayView();
    fs.read(reinterpret_cast< char* >(&data[0]),
            sizeof(Scalar)*data.size());
  }
  return fs.tellg();
}

////////////////////////////////////////////////////////////////////////

streamoff
VectorField::local_read(const string & fname,
                        const streamoff offset)
{
  std::ifstream fs(fname.c_str());
  fs.seekg(offset);
  return local_read(fs);
}

////////////////////////////////////////////////////////////////////////

streamoff
VectorField::local_write(ostream & fs) const
{
  for (size_t i = 0; i < _fields.size(); i++)
  {
    Teuchos::ArrayView< const Scalar > data =
      Teuchos::av_const_cast< const Scalar >(_fields[i]->getData().arrayView());
    fs.write(reinterpret_cast< const char* >(&data[0]),
             sizeof(Scalar)*data.size());
  }
  return fs.tellp();
}

////////////////////////////////////////////////////////////////////////

streamoff
VectorField::local_write(const string & fname,
                         const streamoff offset) const
{
  ofstream fs(fname.c_str(), ios::app);  // append to file
  return local_write(fs);
}

////////////////////////////////////////////////////////////////////////

bool
VectorField::local_exists(const string & fname) const
{
  std::ifstream fs(fname.c_str());
  return fs.good();
}

////////////////////////////////////////////////////////////////////////

} // namespace FDM

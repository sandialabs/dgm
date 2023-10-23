/** \file FDM_Ctrl.cpp
    \brief FDM::Ctrl interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Ctrl.hpp"

// #define FDM_CODETRACE

namespace FDM
{

// Constructor
Ctrl::Ctrl(Scalar p) :
  penalty(p),
  _owner(true),
  _replicated(false),
  _size(0), _time(0)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl constructor" << endl;
#endif

}

// Destructor
Ctrl::~Ctrl()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl destructor" << endl;
#endif

}

// Initialize the Ctrl data vector to zero
void Ctrl::initialize()
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::initialize" << endl;
#endif

  data.resize(_size);
  data = 0.0;
}

// Determine if rank owns this Ctrl
bool Ctrl::owner() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::owner()" << endl;
#endif

  return _owner;
}

// Set whether rank owns this Ctrl
void Ctrl::owner(const bool owner)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::owner(bool)" << endl;
#endif

  _owner = owner;
}

// Determine parallel IO status
bool Ctrl::replicated() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::replicated()" << endl;
#endif

  return _replicated;
}

// Set the parallel IO status
void Ctrl::replicated(const bool replicated)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::replicated(bool)" << endl;
#endif

  _replicated=replicated;
}

// Set the Ctrl storage vector to the input vector
void Ctrl::set_data(const ScalarVector &in)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::set_data" << endl;
#endif

  data = in;
}

// Extract the Ctrl data vector into the output vector
void Ctrl::get_data(ScalarVector & out) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::get_data" << endl;
#endif

  out = data;
}

// Returns true if fill is overloaded
bool Ctrl::has_fill() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::has_fill" << endl;
#endif

  return false;
}

// Fill the output vector
void Ctrl::fill(const Scalar t,
                ScalarVector & out) const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::fill" << endl;
#endif

  assert(out.size() == data.size());
  out = data;
}

// Returns the norm of Ctrl where the default uses the inner product
Scalar Ctrl::norm() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::norm" << endl;
#endif

  return inner_product(data);
}

// Returns the cost of the Ctrl that appears in the objective functional
Scalar Ctrl::cost() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::cost" << endl;
#endif

  return 0.5*penalty*norm();
}

// Default bound just does a set_data
void Ctrl::bound(const ScalarVector &in)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::bound" << endl;
#endif

  set_data(in);
}

// Default to unsteady control
bool Ctrl::steady() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::steady" << endl;
#endif

  return false;
}

// Returns the size of the Ctrl data vector
Ordinal Ctrl::data_size() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::data_size()" << endl;
#endif

  return data.size();
}

// Sets the size of the data vector
void Ctrl::set_size(const Ordinal size_in)
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::data_size(Size)" << endl;
#endif

  _size=size_in; data.resize(size_in);
}

// Returns the size or length of the data vector
Ordinal Ctrl::get_size() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::get_size" << endl;
#endif

  return data.size();
}

// Output the control to std::cout
void Ctrl::output() const
{
#ifdef FDM_CODETRACE
  cout << "FDM::Ctrl::output" << endl;
#endif

  std::cout << data << std::endl;
}

}  // namespace FDM

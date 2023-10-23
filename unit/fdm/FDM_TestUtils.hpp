#ifndef FDM_TESTUTILS_HPP
#define FDM_TESTUTILS_HPP

// System includes
#include <string>
#include <sstream>

// Teuchos includes
#include "Teuchos_Array.hpp"
#include "Teuchos_ArrayView.hpp"

////////////////////////////////////////////////////////////

namespace FDM_TestUtils
{

// Helper function: split a string in to a vector of integers
void splitString(std::string data, Teuchos::Array< int > & result);

// Helper function: split a string in to a vector of booleans
void splitString(std::string data, Teuchos::Array< bool > & result);

// Helper function: convert a generic type to a string
template <class T>
inline std::string to_string(const T & t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

// Helper function: convert a vector of ints into a readable string
std::string readable(Teuchos::Array< int > & vi);

// Helper function: convert a vector of bools into a readable string
std::string readable(Teuchos::Array< bool > & vb);

}  // Namespace FDM_TestUtils

////////////////////////////////////////////////////////////

namespace Teuchos
{

// Helper operators: operator== for Teuchos::ArrayView
template< class T >
bool operator==(const ArrayView< T > & a1, const ArrayView< T > & a2)
{
  if (a1.size() != a2.size()) return false;
  for (size_t i=0; i < a1.size(); ++i)
    if (a1[i] != a2[i]) return false;
  return true;
}

template< class T >
bool operator==(const ArrayView< const T > & a1, const ArrayView< T > & a2)
{
  if (a1.size() != a2.size()) return false;
  for (size_t i=0; i < a1.size(); ++i)
    if (a1[i] != a2[i]) return false;
  return true;
}

}  // Namespace Teuchos

////////////////////////////////////////////////////////////

#endif

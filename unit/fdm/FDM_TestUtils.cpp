
#include "FDM_TestUtils.hpp"
using std::string;
using std::max_element;
using Teuchos::Array;

////////////////////////////////////////////////////////////

namespace FDM_TestUtils
{

// Helper function: split a string into an Array of integers
void splitString(string data, Array< int > & result)
{
  size_t current = 0;
  while (current < data.size())
  {
    size_t next = data.find(",", current);
    if (next == string::npos) next = data.size();
    result.push_back(atoi(data.substr(current, next-current).c_str()));
    current = next + 1;
  }
}

// Helper function: split a string into an Array of booleans
void splitString(string data, Array< bool > & result)
{
  // Convert the data into an Array of ints
  Array< int > axes;
  splitString(data, axes);
  // Initialize the Array of bools
  result.resize(axes.size());
  // Convert the Array of ints into an Array of bools
  for (size_t i = 0; i < result.size(); ++i)
  {
    result[i] = (axes[i] == 0) ? false : true;
  }
}

// Helper function: convert an Array of ints into a readable string
string readable(Array< int > & vi)
{
  string result = "{ ";
  for (Array< int >::iterator it = vi.begin(); it != vi.end(); ++it)
    result += to_string(*it) + " ";
  result += "}";
  return result;
}

// Helper function: convert an Array of ints into a readable string
string readable(Array< bool > & vb)
{
  string result = "{ ";
  for (int i = 0; i < vb.size(); ++i)
    result += (vb[i] ? "true " : "false ");
  result += "}";
  return result;
}

}  // Namespace FDM_TestUtils

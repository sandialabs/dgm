#ifndef DGM_FIELDSLICE_HPP
#define DGM_FIELDSLICE_HPP

/** \file FieldSlice.hpp
    \brief Database for FieldSlice algorithm storage
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <vector>
#include <string>

// DGM includes
#include "Types.hpp"
#include "vField.hpp"

namespace DGM {

/// Take a slice of a DGM::Field
/**
The initialization function for the FieldSlice class reads a text file
containing Json formatted input parameters.  The file name is root.json where
"root" is taken from the root parameter on the Field. This Json file will be
opened and a parameter list of the same name as the parameter passed in the
FieldSlice constructor is queried for. If found the parameter is read and
parsed for valid FieldSlice parameters. There is no other way to initialize
the FieldSlice class other than to have a Json text file in the proper
directory to be read by the initialization function.

Example setup from the Root.json file:
\verbatim
{
   "Field Slice" : [
      {
         "Dimensions" : [ 201, 241 ],
         "Format" : "FLOAT",
         "Frequency" : 100,
         "Intervals" : [ 12, 13 ],
         "Lattice" : [
            [ 0.10, 0.0 ],
            [ 0.0, 0.050 ]
         ],
         "Origin" : [ -5.0, -6.0 ],
         "Outputs" : [
            {
               "Default" : 0.0,
               "Field" : "r",
               "File" : "r"
            },
            {
               "Default" : 0.0,
               "Field" : "ru",
               "File" : "ru"
            },
            {
               "Default" : 0.0,
               "Field" : "rv",
               "File" : "rv"
            },
            {
               "Default" : 0.0,
               "Field" : "rE",
               "File" : "rE"
            }
         ],
         "Verbosity" : 5
      },
      {
         "Dimensions" : [ 100, 100 ],
         "Format" : "FLOAT",
         "Frequency" : 10,
         "Intervals" : [ 43, 13 ],
         "Lattice" : [
            [ 0.0, 1.0 ],
            [ 1.0, 0.0 ]
         ],
         "Origin" : [ -5.0, -6.0 ],
         "Outputs" : [
            {
               "Default" : 0.0,
               "Field" : "r",
               "File" : "r"
            },
            {
               "Default" : 0.0,
               "Field" : "D",
               "File" : "D"
            }
         ],
         "Verbosity" : 3
      }
   ]
   "Other Kind of Slice" : [
      {
         "Dimensions" : [ 201, 241 ],
         "Format" : "FLOAT",
         "Frequency" : 100,
         "Intervals" : [ 12, 13 ],
         "Lattice" : [
            [ 0.10, 0.0 ],
            [ 0.0, 0.050 ]
         ],
         "Origin" : [ -5.0, -6.0 ],
         "Outputs" : [
            {
               "Default" : 0.0,
               "Field" : "jo",
            },
            {
               "Default" : 0.0,
               "Field" : "heat",
            },
            {
               "Default" : 0.0,
               "Field" : "flux",
            }
         ],
         "Verbosity" : 5
      }
   ]
}
\endverbatim

The outer block name, "Field Slice" and "Other Kind of Slice Slice"
in the example above is not fixed by this class but is defined by
the calling routine. "Field Slice" is used by DGM, but other
slices could be defined by any derived code.

The options and defaults for each parameter are as follows:
\verbatim
"Field Slice" or "Other Slice": The top level is a list of parameter
             sets.  Each parameter lists defines a geometry, called a
             lattice, on which to output a list of fields.  In the first
             example above, the "Field Slice" parameter lists defines
             two parameter sets. The first outputs slices in DOUBLE
             format the second in FLOAT. The parameters between these
             groupings are independent with the same or different fields
             to be sliced. The valid parameters within each entry in
             the list are as follows.

Cache Interpolation Data: Bool flag, "true" or "false".  If true the
             interpolation matrices needed to interpolate the field
             to each lattice point will be computed once and cached
             and reused each time needed instead of being recomputed
             each time. This can be much faster when interpolating
             many times. But this method also requires much more
             memory to store the matrices. So when
             "Cache Interpolation Data" is used, the matrices
             will be computed, stored and applied as "float" data
             not "double". This usually saves half the memory needed
             to store the matrices but also results in a loss of precision
             and means that setting this flag to true will result in
             slightly different values than when the cache is not used.
             If precision or consistancy is important, do not use this
             flag.
             DEFAULT: false
Dimensions : List of Ordinals the length the number of spatial dimensions in
             the Field being sliced. This parameter defines the size of the
             output slice and as such is a list of Ordinals. The output slice
             will be D[0] by D[1] by D[2] samples for a three dimensional slice
             or D[0] by D[1] samples for a two dimensional slice or D[0]
             for a linearly one dimensional slice. This is dependent on
             the dimension of the field being sliced but it is possible to
             define a two dimensional slice through a three dimensional
             Field or a one dimensional slice through a two dimensional
             Field by setting values in the Dimensions list to be 1.
             The length of this list should be consistent with
             the length of the Lattice and Origin parameters.
             The output binary data set will vary fastest in the D[0]
             dimension, then the D[1] then D[2]. To index into the
             data set to get the Nth value in the D[0] direction and
             the Mth value in the D[1] direction the offset would
             be N+M*D[1]. The extension to three dimensions is similar
             with the D[2] dimension varying the slowest.
             DEFAULT: Find the largest value in each coordinate
             direction as defined by the Field being sliced. This is
             the axis aligned upper bounding point of the coordinates
             of the Field. Subtract from this the Origin as specified
             by the Origin parameter or by the default Origin parameter
             if the Origin is not specified. Divide each entry of this
             difference by the norm of the corresponding row of the
             Lattice parameter. This is the L^2 norm and is the length
             of the row of the lattice matrix when viewed as a vector.
             Add .5 to the resulting scalar, take the ceiling of this
             number. The ceiling is the next largest integer not less
             than the number. Add .5 to this result and then truncate
             to an integer. This is all done point-wise for each entry
             in the Dimensions list. If the list defining the
             Dimensions parameter is shorter than the number of
             dimension in the Field being sliced, Dimensions is
             extended by adding "1"s up to the Field dimension.
             NOTE: For manually defined Origin parameters it might
             be necessary to specify the Dimension parameter in order
             to define a non-empty slice.
Format:      The options are "FLOAT" or "DOUBLE" which defines
             the format of the binary output data in the slice.
             The float or double is in the native format of the platform
             the code is compiled on and as such can very from platform
             to platform.  In general "FLOAT" is less precision than
             "DOUBLE" but produces smaller output files.
             DEFAULT: FLOAT
Frequency:   An Ordinal which defines when to output a step.
             When the output_slices() function is called,
             the "step" function parameter is checked and
             a slice is generated if step mod Frequency is zero. If
             not zero the function immediately returns without output.
             In general if the Frequency is N, there will be slices
             output every Nth step.  This output check is OR-ed with the
             output check for the Intervals parameter.
             See the Intervals parameter below.
             DEFAULT: 1
Intervals:   List of Ordinals which defines when to output a step.
             When the output_slices() function is called,
             the "step" function parameter is checked and
             a slice is generated if step is listed in the
             Intervals list.  If not found the function immediately
             returns without output. This output check is OR-ed with
             the output check for the Frequency parameter.
             See the Frequency parameter above.
             DEFAULT: []  the empty list.
Lattice:     List of list of scalar types that defines the lattice
             spacing. Must form a non-singular N by N matrix.
             This lists of lists should form a square matrix
             of size N by N where N is the length of the Dimensions
             parameter and the length of the Origin parameter which
             is also the spatial dimension of the field begin sliced.
             The points in the lattice are defined by the matrix-vector
             equation:
                         O + KL
             where O is the lattice origin as defined by the Origin
             parameter.  See the Origin parameter below. K is an
             Ordinal vector in which each entry is greater than or
             equal to zero and less than the corresponding entry
             in the Dimensions parameter.  See the Dimensions parameter
             above. Given a coordinate point in the Field being sliced
             the equation
                        O + KL = C
             must be solvable for K, the lattice index. Thus it is
             important that L be non-singular. Therefore for a
             two dimensional slice through a three dimensional
             data set the unused rows of L should be set to identity
             vectors and not all zeros.
             The values in L can be negative and the matrix
             need not have a determinate of one.  This L defines
             both the spacing and the direction of increment. These
             are all valid L values:
               Slice every .5 units in y followed by x followed by z:
                  L = [[0, .5, 0], [.5, 0, 0], [0, 0, .5]]
               2D slice with different increments in x and y:
                  L = [[0.5, 0], [0, 1]]
               2D slice of a 3D data set "Dimensions = [100,100,1]":
                  L = [[15,0, 0], [0,15, 0],[0, 0, 1]]
               Rotated 45 degrees 2D slice of 3D data set :
                  L = [[.7071, -.7071, 0], [.7071, .7071, 0], [0, 0, 1]]
               Rotated 45 degrees 1D slice of 3D data set
                        "Dimensions = [1000,1,1]": :
                  L = [[.7071, -.7071, 0], [0, 1, 0], [0, 0, 1]]
             Once the lattice locations have been defined by the
             equation above, the fields are interpolated to the lattice
             points using the element basis functions. These are the
             values output to the slice file.
             DEFAULT: [[1,0,0],[0,1,0],[0,0,1]]
Origin:      List of Scalar which defines the origin of the lattice.
             The length must the same as the Dimensions and Lattice
             parameters which are the same as the scalar dimension
             of the field being sliced. This defines the origin for
             incrementing the lattice to produce the data slice.
             See the Lattice parameter above for the equations
             that define the lattice using the Origin.
             DEFAULT: Find the smallest value in each coordinate
             direction as defined by the Field being sliced. This is
             the axis aligned lower bounding point of the coordinates
             of the Field and is used as the Origin parameter.
             NOTE: For negative lattice increments it will be necessary
             to manually define the Origin as the maximum value of the
             mesh bounding box.
Outputs:     A list of parameter lists defining the Fields on which
             the slice will be computed. All the Fields defined by
             the Output lists will share the same lattice geometry.
             The valid parameters within each Output are as follows.
             DEFAULT: None.  At least one output must be specified.

Outputs::Default: A Scalar parameter defining what scalar to use
                  for lattice points that fall outside the geometry
                  of the Field being sliced. If no element can
                  be found containing the lattice point the the
                  output slice will be filled in with this value
                  at that lattice point.
                  DEFAULT: 0.0
Outputs::Field:   A String parameter defining the name of the Field
                  which the slice will be applied to. Since Field
                  names are application dependent, there is no
                  default for this parameter. It is up to the
                  calling program to determine valid Field names.
                  When output_slice() is called on a vField, the
                  field names in the vField will be iterated and
                  any that match the name specified in this
                  parameter will trigger an output slice.
                  DEFAULT: None.
Outputs::File:    A String parameter defining the base name of the file
                  which the slice will be written to. The actual
                  file name will be constructed using the pattern
                            file_STEP.bin
                  where "file" is the string specified in this
                  parameter, STEP is the step number as passed
                  to the output_slice() function and selected for
                  be the Frequency and Intervals parameters.
                  See the Frequency parameter above.
                  See the Intervals parameter above.
                  The suffix will always be ".bin". The format
                  of the binary data will be defined by the
                  Format parameter. See the Format parameter above.
                  The number of samples will be defined by the
                  Dimensions parameter. See the Dimensions
                  parameter above.
                  DEFAULT: Same as the Field parameter. See the
                           Field parameter above.
Verbosity:        A non-negative Ordinal defining the amount of printout.
                  Smaller values produce less printout, larger
                  more.  Larger values of Verbosity always
                  print all the printout from smaller values so that
                  larger values always produce as much or more printout.
                  Some examples of various printout at
                  various Verbosity levels;
                  0 - No printout
                  3 - Echo the Json file as parsed but before
                      default parameter substitution. This is
                      defined by the maximum verbosity found
                      in any FieldSlice parameter set.
                  4 - Report of timers for various selected functions.
                  6 - Report of the total number of lattice points
                      outside the mesh that will be set to
                      the Default parameter.  See the Default
                      parameter above.
                  7 - Report of the per-processor lattice global ids
                      that are outside the mesh that correspond
                      to the points found in Verbosity 6.
                  8 - Report of the per-processor lattice index
                      vectors that are outside the mesh that
                      correspond to the global ids from Verbosity
                      level 7.
                  9 - Report of the per-processor coordinate
                      vectors of the lattice points outside the
                      mesh that correspond to the index vectors
                      printed in the report from Verbosity level 8.
\endverbatim
*/
class FieldSlice {
public:
  /// Constructor
  explicit FieldSlice(const string &n) :
    Initialized(false),FirstOutputCheck(true),
    Name(n),MaxVerbosity(0),Slices() {}

  /// Destructor
  ~FieldSlice(){}

  /// output_slices will check and call initialize if needed.
  /** It is included here in order to call as early as possible
      to detect input syntax errors early.
   */
  void initialize(const Field *F);

  /// output_slices will check that this is an output step.
  /** Output slices can be called all the time. If there is
      nothing to do, it will quickly return.
   */
  void output_slices(const vField &F, 
                     const Ordinal step=0,
                     const bool AlwaysOutput=false,
                     const bool TimeStepInFileName=true,
                     const std::string &ext=std::string());

private:

  /// All the data is in an opaque class called FSlice.
  /** The only way to setup a slice class is to create
      a root.json file that can be automatically read
      by the initialize function.  There is no way
      to instantiate this class through other methods.
   */
  class FSlice;

  bool                        Initialized;
  bool                        FirstOutputCheck;
  const std::string           Name;
  Ordinal                     MaxVerbosity;
  typedef Shared<FSlice>::Ptr Ptr;
  std::vector<Ptr>            Slices;

  FieldSlice(const FieldSlice&);
  FieldSlice operator=(const FieldSlice &);

  void first_output_check(const vField &F) const;
  
  template <typename SCALAR>
  void output_slices(FSlice &S,
                     const Field *F,
                     const Ordinal step,
                     const bool TimeStepInFileName,
                     const std::string &ext);

};

} // namespace DGM

#endif  // DGM_FIELDSLICE_HPP

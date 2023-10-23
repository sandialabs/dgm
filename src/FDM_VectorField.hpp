#ifndef FDM_VECTOR_FIELD_HPP
#define FDM_VECTOR_FIELD_HPP

//! \file   FDM_VectorField.hpp
//! \brief  Finite Difference VectorField declaration
//! \author Bill Spotz

// std includes
#include <iostream>
#include <string>

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_Mesh.hpp"
#include "FDM_Field.hpp"

namespace FDM
{

//! FDM vector field base class
class VectorField : public DTK::VectorField< Scalar,
                                             Field,
                                             std::vector<FieldPtr>::size_type>
{

public:

  /** \brief Vector size type
   */
  typedef std::vector<FieldPtr>::size_type size_type;

  /** \brief Default constructor
   */
  VectorField();

  /** \brief Constructor for Mpi communicator
   */
  template <typename T>
  VectorField(const T) {}

  /** \brief Pointer copy constructor
   *
   * \param in [in] Source VectorField
   */
  VectorField(const VectorField *in);

  /** \brief Destructor
   */
  virtual ~VectorField();

  /** \brief Push-back (append) method
   *
   * \param field [in] Pointer to Field to be appended
   */
  void push_back(const FieldPtr field);

  /** \brief Size accessor method
   */
  virtual size_type size() const;

  /** \brief Vector pointer accessor operator
   *
   * \param i [in] Field index
   */
  virtual Field * operator[](const size_type i);

  /** \brief Const Vector pointer accessor operator
   *
   * \param i [in] Field index
   */
  virtual const Field * operator[](const size_type i) const;

  /** \brief Const Vector RCP accessor operator
   *
   * \param i [in] Field index
   */
  virtual FieldPtr operator()(const FDM::Ordinal i) const;

  /** \brief Fill method
   *
   * \param value [in] Scalar fill value
   */
  virtual void fill(const Scalar value);

  /** \brief Zero-out method
   */
  virtual void zero();

  /** \brief Return a clone of this VectorField
   */
  virtual VectorField * clone() const;

  /** \brief Make this VectorField a clone of the given VectorField
   *
   * \param in [in] Source VectorField
   */
  void clone(const VectorField &in);

  /** \brief Random fill method
   */
  virtual void random();

  /** \brief Print the norms of the Fields in this VectorField
   */
  virtual void norm() const;

  /** \brief Name assignment method for this VectorField
   *
   * \param name [in] VectorField name
   */
  inline void set_name(std::string name);

  /** \brief Name accessor method
   */
  inline std::string get_name() const;

  /** \brief File existence test
   */
  bool local_exists(const string & fname) const;

  /// \name Local I/O methods
  //@{

  streamoff local_read(istream & fs);
  streamoff local_read(const string & fname,
                       const streamoff offset=0);
  streamoff local_write(ostream & fs) const;
  streamoff local_write(const string & fname,
                        const streamoff offset=0) const;
  //@}

  /// \name Linear algebra on VectorFields
  //@{

  friend void add(const VectorField &in,
                  VectorField &out);
  friend void scale(const Scalar alpha,
                    VectorField &out);
  friend void axpy(const Scalar alpha,
                   const VectorField &in,
                   VectorField &out);
  friend void axpy( const Scalar alpha,
                    const VectorField &in1,
                    const VectorField &in2,
                    VectorField &out);
  friend void axpby( const Scalar alpha1,
                     const VectorField &in1,
		     const Scalar alpha2,
                     const VectorField &in2,
                     VectorField &out);

  //@}

protected:

  // The array of Fields
  std::vector< FieldPtr > _fields;

private:

  // The VectorField name
  std::string _name;

};

////////////////////////////
// Inline implementations //
////////////////////////////

////////////////////////////////////////////////////////////////////////

inline
void
VectorField::set_name(std::string name)
{
  _name=name;
}

////////////////////////////////////////////////////////////////////////

inline
std::string
VectorField::get_name() const
{
  return _name;
}

////////////////////////////////////////////////////////////////////////

inline
void
add(const VectorField &in,
    VectorField &out)
{
  //std::cout << "VectorField::add()" << std::endl;
  assert(in.size() == out.size() );
  for (VectorField::size_type i = 0; i < out.size(); ++i)
    out._fields[i]->update(1.0,
                           *(in._fields[i]),
                           1.0);
}

////////////////////////////////////////////////////////////////////////

inline
void
axpy(const Scalar alpha,
     const VectorField &in,
     VectorField &out )
{
  //std::cout << "VectorField::axpy(3)" << std::endl;
  assert(in.size() == out.size() );
  for (VectorField::size_type i = 0; i < out.size(); ++i)
    out._fields[i]->update(alpha,
                           *(in._fields[i]),
                           1.0);
}

////////////////////////////////////////////////////////////////////////

inline
void
axpy(const Scalar alpha,
     const VectorField &in1,
     const VectorField &in2,
     VectorField &out)
{
  assert(in1.size() == out.size() );
  assert(in2.size() == out.size() );
  for (VectorField::size_type i = 0; i < out.size(); ++i)
  {
    out._fields[i]->update(alpha,
                           *(in1._fields[i]),
                           1.0,
                           *(in2._fields[i]),
                           0.0);
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
axpby(const Scalar alpha1,
      const VectorField &in1,
      const Scalar alpha2,
      const VectorField &in2,
      VectorField &out)
{
  assert(in1.size() == out.size() );
  assert(in2.size() == out.size() );
  for (VectorField::size_type i = 0; i < out.size(); ++i)
  {
    out._fields[i]->update(alpha1,
                           *(in1._fields[i]),
                           alpha2,
                           *(in2._fields[i]),
                           0.0);
  }
}

////////////////////////////////////////////////////////////////////////

inline
void
scale(const Scalar alpha,
      VectorField &out)
{
  for (VectorField::size_type i = 0; i < out.size(); ++i)
    out._fields[i]->scale(alpha);
}

////////////////////////////////////////////////////////////////////////

} // namespace FDM

#endif

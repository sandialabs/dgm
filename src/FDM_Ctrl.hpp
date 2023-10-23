#ifndef FDM_CTRL_HPP
#define FDM_CTRL_HPP

/** \file FDM_Ctrl.hpp
    \brief FDM::Ctrl interface
    \author Scott Collis
    \author Bill Spotz
*/

// FDM includes
#include "FDM_Types.hpp"
#include "FDM_VectorField.hpp"

namespace FDM
{

//! FDM Ctrl
class Ctrl : public DTK::Ctrl< VectorField,
                               ScalarVector,
                               Scalar,
                               Size,
                               Ordinal,
                               IntVector,
                               IntVector >
{
protected:
  Scalar penalty;          ///< Penalty for this Ctrl, controls regularization
  ScalarVector data;       ///< Vector storage (flattened) for Ctrl
  bool _owner;             ///< True if Ctrl owns part of global control vector
  bool _replicated;        ///< True if Ctrl is replicated across ranks
  Size _size;              ///< Size of data vector
  Scalar _time;

public:
  typedef Teuchos::RCP< Ctrl > Ptr;
  mutable VectorField F;
  mutable VectorField G;

  /// Constructor
  Ctrl(Scalar p=0.0);

  /// Destructor
  virtual ~Ctrl();

  /// Initialize the Ctrl data vector to zero
  virtual void initialize();

  /// Determine if rank owns this Ctrl
  virtual bool owner() const;

  /// Set whether rank owns this Ctrl
  virtual void owner(const bool owner);

  /// Determine parallel IO status
  virtual bool replicated() const;

  /// Set the parallel IO status
  virtual void replicated(const bool replicated);

  /// Set the Ctrl storage vector to the input vector
  virtual void set_data(const ScalarVector &in);

  /// Extract the Ctrl data vector into the output vector
  virtual void get_data( ScalarVector &out ) const;

  /// Returns true if fill is overloaded
  virtual bool has_fill() const;

  /// Fill the output vector
  virtual void fill(const Scalar t,
                    ScalarVector &out) const;

  /// Returns the norm of Ctrl where the default uses the inner product
  virtual Scalar norm() const;

  /// Returns the cost of the Ctrl that appears in the objective functional
  virtual Scalar cost() const;

  /// Default bound just does a set_data
  virtual void bound(const ScalarVector &in);

  /// Default to unsteady control
  virtual bool steady() const;

  /// Returns the size of the Ctrl data vector
  virtual Ordinal data_size() const;

  /// Sets the size of the data vector
  virtual void set_size(const Ordinal size_in);

  /// Returns the size or length of the data vector
  virtual Ordinal get_size() const;

  /// Output the control to std::cout
  virtual void output() const;

  /// Update the internal time for this Ctrl
  void time(const Scalar time) { _time=time; }

  /// Get the internal time for this Ctrl
  Scalar time() const { return _time; }
};

}  // namespace FDM

#endif

#ifndef DGM_BLACKBOX_HPP
#define DGM_BLACKBOX_HPP

/** \file BlackBox.hpp
    \brief Black box interface to the DGM Optimizer
    \author Scott Collis
*/

#include "Comm.hpp"
#include "State.hpp"
#include "Adjoint.hpp"
#include "Optimizer.hpp"
#include "OptProblem.hpp"

namespace DGM {

/// Black box optimization interface
class BlackBox : public Optimizer {

  Ordinal asv;                  ///< DAKOTA active state vector

  Scalar total_g;               ///< Norm of gradient of the objective function

  dVector gradient_norms;       ///< Components of the gradient norm

 public:

  BlackBox( State*, Adjoint*, Control::Ptr,
            const DGM::Comm::Ptr = DGM::Comm::World);

  virtual ~BlackBox() {
    if (comm->verbosity()>1) comm->cout() << "~BlackBox()" << endl;
  }

  /// \name Provide the DGM::Optimizer interface
  //@{
  virtual void check_grad();
  virtual void optimize(const Ordinal=0);
  virtual Scalar advance(const Ordinal );
  virtual Ordinal readRestart(const string * = NULL);
  virtual Ordinal readRestart(streamoff &skip, const string * = NULL);
  virtual void writeRestart(const string * = NULL) const;
  virtual void plotControl(const Ordinal ntout=1, const Ordinal riter=0) const;
  virtual void plotGradient(const Ordinal ntout=1, const Ordinal riter=0) const;
  virtual streamoff outputHeader(const string &fname) const;
  /// Compute the difference between two control files
  virtual int diff(const std::string& ctl1, const std::string& ctl2,
                   const Scalar aeps, const Scalar reps);
  virtual int sum(const double mult,
                  const vector<Size> &sub_to_mstr, Optimizer *optimizer);
  virtual int sum(const double mult);
  virtual int ext(const vector<Size> &sub_to_mstr, Optimizer *optimizer);
  void    set_asv(const Ordinal v) { asv = v; }
  Ordinal get_asv() const { return asv; }
  //@}

 private:

  streamoff readHeader(const string &fname, Ordinal &riter, Ordinal &rasv);
  streamoff writeHeader(const string &fname) const;
  streamoff writeJsonHeader(const string &fname) const;
  streamoff readJsonHeader(const string &fname, Ordinal &riter, Ordinal &rasv);

  void showUsage(const string &code) const;
  void parse_args(ArgList &args);

};

} // namespace DGM

#endif  // DGM_BLACKBOX_HPP

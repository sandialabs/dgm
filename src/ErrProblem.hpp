#ifndef DGM_ERR_PROBLEM_HPP
#define DGM_ERR_PROBLEM_HPP

/** \file ErrProblem.hpp
    \brief Error estimation problem declaration
    \author Scott Collis

    This file contains a problem plus error estimators (think of it as an
    updated Problem class). It is used in the same way as the Problem class
    and takes the same arguments.
*/

// DGM includes
#include "Comm.hpp"
#include "Table.hpp"
#include "Domain.hpp"
#include "Estimate.hpp"

namespace DGM {

/// Problem class for use in error estimation
class ErrProblem {

protected:

  const DGM::Comm *comm;  ///< Parallel communicator

  bool use_err;           ///< Toggles a flag used for error estimation

public:

  /// types of supported refinement strategies
  enum RefineType { NONE=0, PERCENT=1, TOLERANCE=2, ABSOLUTE=3 };

  string code;            ///< Name of executable
  string root;            ///< Root file name for run
  Table params;           ///< Parameter table
  Domain *Omega;          ///< Domain to solve problem on

  Estimate *err;          ///< Error estimation class

  /// Constructor
  ErrProblem( DGM::ArgList&, const Table& = Table(),
              const DGM::Comm* = DGM::Comm::World );

  /// Main solve interface
  inline int solve() { return errorEst(); }

  /// Plot the solution
  inline int plot (const string& rst) {return Omega->plot(rst); }

  /// Outputs the supported commandline arguments
  void showUsage(const string&) const;

private:

  /// extracts arguments
  void parse_args(DGM::ArgList& args);

  /// solves the PDE
  inline int solvePDE() { return Omega->solve(); }

  /// performs error estimation
  inline int errorEst() { if (use_err) err->estimate(); return 0; }

};

} // namespace DGM

#endif  // DGM_ERR_PROBLEM_HPP

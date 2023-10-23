/** \file Optimizer.cpp
    \brief Base class for all optimization algorithms
    \author Scott Collis
*/

#include "Optimizer.hpp"

namespace DGM {

namespace {
  
  /// Local helper to parse Json input
  Json::Value & parse_json(Json::Value &json) {
    if (!json.isMember("Optimizer")) json["Optimizer"] = Json::Value();
    return json;
  }

}

Optimizer::Optimizer(State *state_, Adjoint *adjoint_,
                     Control::Ptr control_, const DGM::Comm::Ptr comm_)
  : comm(comm_),
    ctl_comm(comm_),
    total_j(0),
    max_iter(0),
    tol_j(0),
    npredict(100),
    nadvance(100),
    grad_check(0),
    fd_eps(0.1),
    opt_stat(NULL),
    iter(1),
    state(state_),
    adjoint(adjoint_),
    control(control_),
    json(parse_json(state->domain()->json_root)["Optimizer"])
{
  const int verb = json.get("Verbosity",0).asInt();
  if (verb>1) comm->cout() << "Optimizer::Optimizer()" << endl;
  if (verb>2) {
    Json::StyledWriter writer;
    string output = writer.write(json);
    comm->cout()<<"Echo of Optimizer Json input:\n"<< output;
  }
  if (verb>1) comm->cout() << "Completed Optimizer::Optimizer()" << endl;
}

Optimizer::~Optimizer() {
  if (comm->verbosity()>1) comm->cout() << "~Optimizer()" << endl;
  if (opt_stat) fclose(opt_stat);
}

} // namespace DGM

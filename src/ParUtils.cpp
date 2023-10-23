/** \file ParUtils.cpp
    \brief Export data from source to target layout
    \author Axel Gerstenberger
*/

#ifdef DGM_USE_GENERAL_GHOSTING
// system includes
#include <vector>
#ifdef DGM_PARALLEL
#include <boost/mpi/collectives.hpp>
#endif

// DGM includes
#include "ParUtils.hpp"


void DGM::Exporter::construct_exporter() {

  if (SourceMap().SameAs(TargetMap())) return;

#ifdef DGM_PARALLEL
  // init sendpattern to number of procs with no send tasks in the sets
  sendpattern.resize(get_Epetra_Comm().NumProc());

  // to build the sendpattern, everybody has to communicate what he wants
  std::vector<int> target_gids;
  std::copy(TargetMap().MyGlobalElements(),
            TargetMap().MyGlobalElements()+TargetMap().NumMyElements(),
            std::back_inserter(target_gids));

  for (int proc=0; proc<get_Epetra_Comm().NumProc(); ++proc) {
    std::vector<int> recv_gids;
    if (proc==get_Epetra_Comm().MyPID()) {
      recv_gids = target_gids;
    }
    boost::mpi::broadcast(get_boost_comm(), recv_gids, proc);

    // Loop what proc wants and what I have (SendPlan)
    if (proc != get_Epetra_Comm().MyPID()) { // don't send stuff to myself
      for (std::size_t i=0; i<recv_gids.size(); ++i) {
        const int gid = recv_gids[i];
        if (SourceMap().MyGID(gid)) {
          sendpattern[proc].insert(gid);
        }
      }
    }
  }
  // sanity check
  assert(sendpattern[get_Epetra_Comm().MyPID()].empty());

  return;
#endif
}



#endif // DGM_USE_GENERAL_GHOSTING

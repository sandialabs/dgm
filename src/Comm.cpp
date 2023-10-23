/** \file Comm.cpp
    \brief Base class implementation of the DGM communicator
    \author Scott Collis
*/

// system includes
#include <limits>
#ifdef DGM_FILE_SYSTEM_STATS
#include <sys/statvfs.h>
#endif

// DGM includes
#include "Comm.hpp"
#include "Info.hpp"
bool DGM::Comm::firstComm(true);
#include "Info.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
int DGM::MpiComm::NumWorld(0);
#else
#include "SerialComm.hpp"
#endif
#include "Color.hpp"
// Determine whether to use color output
DGM::UseColor DGM::Color::useColor;

// build the DGM::Info object
DGM::Info DGM::Comm::information;

// define the default DGM::Comm::World
DGM::Shared<DGM::Comm>::Ptr DGM::Comm::World;

// initialize to no errors
sig_atomic_t DGM::Comm::fatal_error_in_progress(0);

/// Find the size of the scratch directory
unsigned long DGM::Comm::ScratchSize() const {
  unsigned long s = numeric_limits<unsigned long>::max();
#ifdef DGM_FILE_SYSTEM_STATS
  struct statvfs buffer;
  const int status = statvfs(this->Path().c_str(), &buffer);
  if (!status) s = buffer.f_bavail * buffer.f_bsize;
#endif
  return s;
}

string DGM::Comm::MyPIDstr() const {
  ostringstream s;
  s << "Proc " << MyPID() << ": ";
  return s.str();
}

#ifdef DGM_REDSTORM
/// For some weird reason, RedStorm needed this
double pow( double x, int n ) {
  return pow(x,(double)n);
}
#endif

/// Signal handler exits gracefully
void DGM::Comm::Handler(int sig) {
  if (fatal_error_in_progress) raise(sig);
  fatal_error_in_progress = 1;
  string message;
  switch (sig) {
  case 1:
    message = "SIGHUP (hangup)";
    break;
  case 2:
    message = "SIGINT (interrupt)";
    break;
  case 3:
    message = "SIGQUIT (quit)";
    break;
  case 4:
    message = "SIGILL (illegal instruction)";
    break;
  case 5:
    message = "SIGTRAP (trace trap)";
    break;
  case 6:
    message = "SIGABRT (abort)";
    break;
  case 8:
    message = "SIGFPE (FP error)";
    break;
  case 15:
    message = "SIGTERM (terminate)";
    break;
  default:
    stringstream ss; ss << sig;
    message = ss.str();
    break;
  }

  DGM::Comm::World->cout() << "DGM::Comm caught signal " << message
                           << ", attempting to exit gracefully..." << endl;

  // Need to clean things up here...
  DGM::Comm::World->RemoveScratch();

  // Re-raise the signal but with default handler
  signal(sig, SIG_DFL);
  raise(sig);

#if 0
  // this doesn't work reliably because you cannot guarantee that the
  // program will resume execution nicely after a signal is caught
  //static bool firsttime(true);
  throw DGM::exception("Caught interupt");
  if (firsttime) {
    firsttime = false;
    DGM::Comm::World->cerr() << "Calling DGM::Comm::exit("<<sig<<")"<<endl;
    DGM::Comm::World->exit(sig);
  } else {
    DGM::Comm::World->cerr() << "Calling std::exit("<<sig<<")"<<endl;
    std::exit(sig);
  }
#endif
}

/// Determines which signals to catch
/** Turn off underflow trap and instead throw an exception, sometimes it
    is really nice to know when underflows are occurring since they really
    can slow a code down. Need to make sure to catch both SIGINT and SIGTERM
    as under MPI both of these can be sent to an interrupted process.

    \note You should never try to catch SIGSEGV.
*/
void DGM::Comm::Interupt() {
#ifdef DGM_CATCH_UNDERFLOW
  feenableexcept( FE_UNDERFLOW );
#endif
  signal( SIGINT, Handler );
  signal( SIGILL, Handler );
  signal( SIGABRT, Handler );
  signal( SIGFPE, Handler );
  signal( SIGTERM, Handler );
}

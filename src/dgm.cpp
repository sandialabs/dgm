/*=============================================================================
  Title:      Discontinuous Galerkin Method (DGM)

  Contact:    S. Scott Collis
              Sandia National Laboratories
              Albuquerque, NM 87175
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2003 Rice University
              (c)2008 Sandia National Laboratories
=============================================================================*/

/** \file dgm.cpp
    \brief File containing the main program for DGM
    \author Scott Collis
*/

// system libraries
#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
#include <fenv.h>
#if defined(__x86_64__) && !defined(__APPLE__)
// These are needed to turn off denormals on x86 processors when not APPLE
#include <xmmintrin.h>
#include <pmmintrin.h>
#endif
#endif
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#ifdef DGM_USE_MALLINFO
#include <malloc.h>
#endif
using namespace std;

// third party libraries
#ifdef DGM_TRY_BOOST_FS
#include <boost/filesystem.hpp>
#endif
#include <boost/version.hpp>
#include <boost/numeric/conversion/cast.hpp>

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Format.hpp"
#include "ArgList.hpp"
#include "Trilinos.hpp"
#include "Vector.hpp"
#include "Utilities.hpp"
#include "ClearDBs.hpp"

#if defined(DGM_USE_KOKKOS) || defined(DGM_USE_CUDA)
#include "GpGpu.hpp"
#endif

#if defined(DGM_USE_ZOLTAN) && defined(DGM_USE_EPETRA) && defined(DGM_PARALLEL)
#include "Partition.hpp"
#include "zoltan.h"
#endif

// Reo libraries
#include "Reo.hpp"
#include "ReoInfo.hpp"
#include "ReoProblem.hpp"

// CMC libraries
#include "Stopwatch.hpp"
#ifdef DGM_TRY_RAMDISK
#include "RamDisk.hpp"
#endif
using CMC::Stopwatch;
#include "Vector.hpp"

// Trilinos includes
#ifdef DGM_USE_TRILINOS
#include "Trilinos_version.h"
#endif

// FDM includes
#ifdef DGM_USE_FDM
#include "Teuchos_DefaultComm.hpp"
#include "Tpetra_Details_DefaultTypes.hpp"
#include "Xpetra_MDMapFactory.hpp"
#endif

// Test of intrinsice vector operations
#ifdef DGM_TEST_INTRINSICS
#include <emmintrin.h>  // SSE2
#include <immintrin.h>  // AVX
#include <x86intrin.h>  // Other
#if defined(__GNUC__) || defined(__PGI)
#define ALIGN16 __attribute__((__aligned__(16)))
#define ALIGN32 __attribute__((__aligned__(32)))
#else
#define ALIGN16 __declspec(align(16))
#define ALIGN32 __declspec(align(32))
#endif
#endif

// forward declarations

/// Manage command line inputs
void parse_args( DGM::ArgList &args, DGM::Table &params, DGM::Info &info );

/// Printout the correct usage
void showUsage( const string& code );

#if 0
/// a vField helper to copy a conformal Epetra vector to the vField
using Teuchos::RCP;
using Teuchos::rcp;
void copy( const RCP<const Epetra_Vector> in, vField &out ) {
  std::copy(&((*in)[0]), &((*in)[0])+in->MyLength(),
            out.elmt_data.data());
}
#endif

/// The main DGM program.
/** Manage command line inputs, create the parallel process(es) and construct
    the problem */
int main(int argc, char *argv[]) {
  int status = 0;
  try {
    DGM::Format sci(4,10,'e');
#if defined(DGM_USE_KOKKOS)
    // initialize kokkos
    DGM::GpGpu::initialize_gpu gpu;
#endif
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
    string suffix(""); if (DGM::Comm::World->NumProc()!=1) suffix="s";
    DGM::Comm::World->cout() << "Running DGM on "
                             << DGM::Comm::World->NumProc()
                             << " processor"<<suffix<<"..." << std::endl;
#if defined(DGM_USE_ZOLTAN) && defined(DGM_PARALLEL) && defined(DGM_USE_EPETRA)
    // initialize Zoltan
    float ver = 0;
    Zoltan_Initialize(argc, argv, &ver);
#endif
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    Reo::Info info;
    info.name(out);
    comm->cout()<< "Started Reo on " << DGM::dateTime() << endl;
    comm->cout()<<"  Running on: "<<info.hostname()<<endl;
    comm->cout()<<"  Compiled with: "<<info.compiler()<<endl;
    comm->cout()<<"  System set to: "<<info.system()<<endl;
    comm->cout()<<"  Directory is: "<<info.directory()<<endl;
#ifdef DGM_USE_TRILINOS
    comm->cout()<<"  Trilinos version: " << TRILINOS_VERSION_STRING <<endl;
#endif
#ifdef OPENBLAS_VERSION
    comm->cout()<<"  OpenBLAS version: " << OPENBLAS_VERSION << endl;
    // If using OpenBLAS make sure that it is single threaded
    openblas_set_num_threads(1);
#endif
#ifdef CMC_CLAPACK_VERSION
    comm->cout()<<"  CMC CLAPACK version: " << CMC_CLAPACK_VERSION << endl;
#endif
#ifdef BOOST_VERSION
    comm->cout()<<"  Boost version: " 
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << endl;
#endif
#ifdef DGM_PARALLEL
    int mpi_version, mpi_subversion;
    MPI_Get_version(&mpi_version, &mpi_subversion);
    comm->cout()<<"  MPI version: " << mpi_version << "." 
                << mpi_subversion << endl;
#ifdef OPEN_MPI
    comm->cout()<<"  OpenMPI version: " << OMPI_MAJOR_VERSION << "." 
                << OMPI_MINOR_VERSION << "." << OMPI_RELEASE_VERSION << endl;
#endif
#if defined(VERBOSE) && (MPI_VERSION > 2)
    int len;
    char mpi_string_version[MPI_MAX_LIBRARY_VERSION_STRING];
    MPI_Get_library_version(mpi_string_version, &len);
    comm->cout()<<"  MPI library: " << mpi_string_version << endl;
#endif
#endif
#if defined(CMC_USE_AVX)
#ifdef __AVX__
    comm->cout()<<"  CMC is using AVX instructions"<<endl;
#endif
#ifdef __FMA__
    comm->cout()<<"  CMC is using FMA instructions"<<endl;
#endif
#ifdef __FMA4__
    comm->cout()<<"  CMC is using FMA4 instructions"<<endl;
#endif
#endif
    //
    // Flush denormals to zero if requested
    //
#if defined(DGM_USE_FENV) || defined(DGM_DISABLE_DENORMS)
    comm->cout()<<"  Flushing denormals to zero..."<<endl;
#ifdef __APPLE__
    if (fesetenv(&_FE_DFL_DISABLE_SSE_DENORMS_ENV)) {
      comm->cout()<<"ERROR setting FP environment to disable subnormals"<<endl;
      comm->abort();
    }
#elif defined(__x86_64__)
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
#else
    comm->cout()<<"WARNING: Unable to flush denormals to zero for "
                  "this architecture..."<<endl;
#endif
#endif
#ifdef DGM_TEST_INTRINSICS
    {
#ifdef __SSE2__
      double x=1.2;
      __m128d vx = _mm_load1_pd(&x);
      __m128d vx2 = _mm_mul_pd(vx,vx);
      double ALIGN16 t[2];
      _mm_store_pd(t, vx2);
      comm->cout()<<t[0]<<", "<<t[1]<<std::endl;
#endif
      // Setup for vector test
      const int Nsamples = 1000000;
      const size_t N=257;
      const size_t roundedN = (N+3) & ~3UL;
      const size_t lowerN = N & ~3UL;
      cout<<"Increment = "<<32/sizeof(double)-1<<endl;
      cout<<"N         = "<<N<<endl;
      cout<<"Lower N   = "<<lowerN<<endl;
      cout<<"Rounded N = "<<roundedN<<endl;
      cout<<"Padding   = "<<roundedN-N<<endl;

      // With dynamic memory allocation, even though I ensure that the
      // memory is aligned, the compiler cannot tell that it is
      CMC::Vector<double,size_t> X(N);
      for (size_t i=0; i<N; i++) X[i]=i;
      CMC::Vector<double,size_t> Y(N);
      for (size_t i=0; i<N; i++) Y[i]=2*i;
      CMC::Vector<double,size_t> Z(N);
      for (size_t i=0; i<N; i++) Z[i]=i;
      CMC::Vector<double,size_t> W(N);
      for (size_t i=0; i<N; i++) W[i]=i;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      comm->cout()<<"Y[N] = "<<Y[N-1]<<std::endl;
      comm->cout()<<"Z[N] = "<<Z[N-1]<<std::endl;
      comm->cout()<<"W[N] = "<<W[N-1]<<std::endl;
      {
        CMC::Stopwatch cpu; cpu.start();
        for (int k=0; k<Nsamples; k++) {
          dvvtvp(X,Y,Z,W);
        }
        comm->cout()<<"Time for dvvtvp call = "<<cpu.stop()<<std::endl;
        cpu.reset(); cpu.start();
        for (int k=0; k<Nsamples; k++) {
          dvtvp(X,Y,Z,W);
        }
        comm->cout()<<"Time for dvtvp call = "<<cpu.stop()<<std::endl;
      }
      comm->cout()<<"W[N] = "<<W[N-1]<<std::endl;
      comm->cout()<<"Answer = "<<X[N-1]*Y[N-1]+Z[N-1]<<std::endl;

      // If you use this, the compiler can tell that the data is 32byte
      // aligned and it uses faster loads and stores
      double ALIGN32 aX[roundedN];
      for (size_t i=0; i<roundedN; i++) aX[i]=i;

#ifdef __SSE2__
      // SSE2 (this uses vmulpd vsqrtpd on xmm registers)
      CMC::Stopwatch timer; timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<roundedN; i+=2) {
          __m128d vx = _mm_load_pd(&X[i]);
          __m128d vx2 = _mm_mul_pd(vx,vx);
          vx = _mm_sqrt_pd(vx2);
          _mm_store_pd(&X[i],vx);
        }
      }
      comm->cout()<<"Time for SSE2 vectorized loop = "<<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
#endif
      size_t foo=10l, bar=15l;
      asm volatile ("addq %%rax,%%rbx"
                    : "=b" (bar)
                    : "a" (foo), "b" (bar) );
      cout<<"foo+bar="<<bar<<endl;
#if defined(__AVX__) && defined(CMC_ALIGN)
      // AVX (this uses vmulpd, vsqrtpd on ymm registers)
      timer.reset(); timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<roundedN; i+=4) {
#if 1
          __m256d vx  = _mm256_load_pd(&X[i]);
          __m256d vx2 = _mm256_mul_pd(vx,vx);
          vx = _mm256_sqrt_pd(vx2);
          _mm256_store_pd(&X[i],vx);
#else
          __m256d *vx = (__m256d *)&X[i];
          __m256d vx2 = _mm256_mul_pd(*vx,*vx);
          *vx = _mm256_sqrt_pd(vx2);
#endif
        }
      }
      comm->cout()<<"Time for AVX dynamic aligned loop = "
                  <<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
#endif
#ifdef __AVX__
      // AVX (use unaligned load/store with vmulpd, vsqrtpd on ymm registers)
      timer.reset(); timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<roundedN; i+=4) {
          __m256d vx  = _mm256_loadu_pd(&X[i]);
          __m256d vx2 = _mm256_mul_pd(vx,vx);
          vx = _mm256_sqrt_pd(vx2);
          _mm256_storeu_pd(&X[i],vx);
        }
      }
      comm->cout()<<"Time for AVX unaligned loop = "
                  <<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
#endif
#ifdef __AVX__
      {
      // AVX (use unaligned load/store with vmulpd, vsqrtpd on ymm registers)
      // WARNING:  This version is intentionally unaligned
      CMC::Vector<double,size_t> uX;
      uX.alias(X,1,X.size()-1);
      const size_t roundedN = (uX.size()+3) & ~3UL;
      timer.reset(); timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<roundedN; i+=4) {
          __m256d vx  = _mm256_loadu_pd(&uX[i]);
          __m256d vx2 = _mm256_mul_pd(vx,vx);
          vx = _mm256_sqrt_pd(vx2);
          _mm256_storeu_pd(&uX[i],vx);
        }
      }
      comm->cout()<<"Time for AVX intentionally unaligned loop = "
                  <<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<uX[uX.size()-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
      }
#endif
#ifdef __AVX__
      // AVX (use static aligned vmulpd, vsqrtpd on ymm registers)
      timer.reset(); timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<roundedN; i+=4) {
          __m256d vx  = _mm256_load_pd(&aX[i]);
          __m256d vx2 = _mm256_mul_pd(vx,vx);
          vx = _mm256_sqrt_pd(vx2);
          _mm256_store_pd(&X[i],vx);
        }
      }
      comm->cout()<<"Time for AVX static aligned loop = "
                  <<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
#endif
      // Normal loop (this defaults to vmulsd, vsqrtsd)
      timer.reset(); timer.start();
      for (int k=0; k<Nsamples; k++) {
        for (size_t i=0; i<N; i++) {
          X[i] *= X[i];
          X[i] = sqrt(X[i]);
        }
      }
      comm->cout()<<"Time for standard loop = "<<timer.stop()<<std::endl;
      comm->cout()<<"X[N] = "<<X[N-1]<<std::endl;
      for (size_t i=0; i<N; i++) X[i]=i;
//      for (int i=0; i<X.size(); i++) {
//        comm->cout()<<"X["<<i<<"] = "<<X[i]<<std::endl;
//      }
    }
#endif

#ifdef DGM_TRY_RAMDISK
    // Try out a RamDisk
    CMC::RamDisk<double,int> disk(10000000);
    cout << "disk size = " << disk.size() << endl;
#endif

#ifdef DGM_TRY_BOOST_FS
    try_boost_fs: {
      // Make a file and then see how big it is
      ofstream out("junk.dat");
      out << "My name is Scott" << endl;
      out.close();
      // Now use Boost::Filesystem to manipulate the file
      boost::filesystem::path p("junk.dat");
      cout << "File size " << boost::filesystem::file_size(p) << endl;
      cout << "Now removing " << p << endl;
      boost::filesystem::remove(p);
      cout << "Status of " << p << " is " << boost::filesystem::exists(p)
           << endl;
      p = "tmp";
      cout << "The status of directory " << p << " is "
           << boost::filesystem::exists(p) << endl;
      boost::filesystem::remove_all(p);
      cout << "The status of directory " << p << " is "
           << boost::filesystem::exists(p) << endl;
      return DGM::SUCCESS;
    }
#endif

    // setup parameter list and parse
    DGM::ArgList args( &argc, &argv );
    DGM::Table params;
#if defined(DGM_PARALLEL) && defined(DGM_GROUPS)
    params["ncomm"] = 1;      // default to one global communicator
#endif
    params["pause"] = false;
    parse_args( args, params, info );
    const bool pause = params["pause"];
    if (comm->Master() && pause) {
      cout << "Press enter to continue ";
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    comm->Barrier();

#if defined(DGM_PARALLEL) && defined(DGM_GROUPS)
    ofstream bitBucket("/dev/null");

    // demonstrate and test the use of multiple DGM communicators
    const int ncomm = params["ncomm"];
    const int gnproc = DGM::Comm::World->NumProc();
    if (!(gnproc >= ncomm)) {
      DGM::Comm::World->cerr()<<"Need more processes to make communicators"
                              <<endl;
      return DGM::FAILURE;
    }
    if (gnproc%ncomm != 0) {
      DGM::Comm::World->cerr()<<"Number of processors (" << gnproc
                              << ") must be "
                              <<"divisible by number of communicators ("
                              << ncomm << ")" << endl;
      return DGM::FAILURE;
    }
    const int nproc = gnproc/ncomm;  // number of processes in each comm
    DGM::Comm::World->cout() << "Building " << ncomm
                             << " DGM communicators each with "
                             << nproc << " processors..." << std::endl;
    MPI_Comm mpi_comm = dynamic_cast<DGM::MpiComm*>
      (DGM::Comm::World)->mpi_comm;
    MPI_Comm my_comm;
    MPI_Group mpi_group, my_group;
    DGM::MpiComm *dgm_comm;
    MPI_Comm_group( mpi_comm, &mpi_group );
    int my_ranks[nproc];
    int my_id = DGM::Comm::World->MyPID()/nproc;
    for (int i=0; i<nproc; i++) my_ranks[i] = my_id*nproc+i;
    MPI_Group_incl( mpi_group, nproc, my_ranks, &my_group );
    MPI_Comm_create( mpi_comm, my_group, &my_comm );
    ostringstream comm_name; comm_name << "Comm[" << my_id << "]";
    if (my_id==0)
      dgm_comm = new DGM::MpiComm( my_comm, comm_name.str() );
    else
      dgm_comm = new DGM::MpiComm( my_comm, comm_name.str(),
                                   bitBucket, bitBucket);

#ifdef DGM_TEST_INTER_COMMUNICATORS

    // try out inter-communicators.  In this approach, the 0th
    // sub-communicator acts as a server and accumulates results from all the
    // other active sub-communicators.  At conclusion, only the processes on
    // the server will have the correctly reduced result.  Some form of
    // broadcast would be needed to make everyone else consistent.
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Starting Intercomm" << endl;
    std::vector<MPI_Comm> icomm;
    if (my_id!=0) {
      icomm.push_back( MPI_COMM_NULL );
      MPI_Intercomm_create( my_comm, 0, mpi_comm, 0, my_id, &(icomm[0]) );
    } else {
      for (int k=1, n=0; k<ncomm; ++k, ++n) {
        icomm.push_back( MPI_COMM_NULL );
        MPI_Intercomm_create( my_comm, 0, mpi_comm, k*nproc, k, &(icomm[n]) );
      }
    }
    int sum = DGM::Comm::World->MyPID();
    int gsum = 0;
    int tsum = 0;
    MPI_Allreduce( &sum, &gsum, 1, MPI_INT, MPI_SUM, my_comm );
    tsum += gsum;
    if (my_id!=0) {
      MPI_Allreduce( &sum, &gsum, 1, MPI_INT, MPI_SUM, icomm[0] );
      //tsum += gsum;
    } else {
      for (int n=0; n<icomm.size(); n++)  {
        MPI_Allreduce( &sum, &gsum, 1, MPI_INT, MPI_SUM, icomm[n] );
        tsum += gsum;
      }
    }
    // only global rank 0 will have the right number
    cout << DGM::Comm::World->MyPID() << " " << sum << " " << gsum << " "
         << tsum << endl;
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Finished Intercomm" << endl;

    // another way is to do a sum reduce over all processes is just to use a
    // global intracommunicator, but this won't work for our application
    // since we will already have partial sums on each sub-communicator
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Starting Global Allreduce" << endl;
    int isum = 0;
    MPI_Allreduce( &sum, &isum, 1, MPI_INT, MPI_SUM, mpi_comm );
    cout << DGM::Comm::World->MyPID() << " " << sum << " " << isum << endl;
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Finished Global Allreduce" << endl;

    // another way is to do a local Allreduce on each sub-communicator and
    // then may another intra-communicator that is the root on each
    // sub-communicator.  Then do an Allreduce on that new intra-communicator
    // and finally, if desired, broadcast the result on the root of each
    // sub-communicator to the rest of the processes on the sub-communicators
    // so that everyone is consistent
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Starting hierarchical reduce" << endl;
    MPI_Comm root_comm;
    MPI_Group root_group;
    int roots[ncomm];
    for (int k=0; k<ncomm; ++k) roots[k] = k*nproc;
    MPI_Group_incl( mpi_group, ncomm, roots, &root_group );
    MPI_Comm_create( mpi_comm, root_group, &root_comm );
    int nsum=0;
    MPI_Allreduce( &sum, &gsum, 1, MPI_INT, MPI_SUM, my_comm );
    if (root_comm != MPI_COMM_NULL)
      MPI_Allreduce( &gsum, &nsum, 1, MPI_INT, MPI_SUM, root_comm );
    MPI_Bcast( &nsum, 1, MPI_INT, 0, my_comm );
    cout << DGM::Comm::World->MyPID() << " " << sum << " " << gsum << " "
         << nsum << endl;
    DGM::Comm::World->Barrier();
    DGM::Comm::World->cout() << "Finished hierarchical reduce" << endl;

    // How about summing a vector of storage accross a collection of
    // sub-communicators
    dVector x(10);
    x = my_id;

#endif

    // run the code
    Reo::Problem problem(args, params, dgm_comm);
    Stopwatch cpu;
    cpu.start();
    status = problem.solve();
    dgm_comm->cout() << "Total run time:  " << sci(cpu.stop()) << endl;
    if (dgm_comm) delete dgm_comm;
#else  // regular execution

#ifdef DGM_TEST_FDM
    {
      DGM::Comm::World->cout() << "Trying out FDM..." << endl;
      std::vector<int> shapeVals(2);
      shapeVals[0] = 32;
      shapeVals[1] = 16;
      Teuchos::RCP< const Teuchos::Comm< int > > comm =
        Teuchos::DefaultComm<int>::getComm();
      Teuchos::RCP< const Xpetra::MDMap< int > > map =
        Xpetra::MDVectorFactory< int >::Build(Xpetra::UseTpetra,
                                              comm,
                                              shapeVals);
      cout << "My Xpetra::MDMap is " << map.description() << endl;
      return 0;
    }
#endif

execute:
    {
      Reo::Problem problem(args, params, DGM::Comm::World);

#if defined(DGM_USE_EPETRA) && defined(DGM_USE_RYTHMOS)
      boost::filesystem::path p(problem.Omega->root+".xml");
      if (boost::filesystem::exists(p)) {
        // Test the EpetraExt::ModelEvaluator interface to DGM
        using Teuchos::RCP;
        using Teuchos::rcp;

        // make sure that Epetra is setup
        problem.Omega->make_contiguous();

        // put in test of ModelEvaluator
        DGM::Trilinos::ModelEvaluator Model(problem.Omega);

        // Set input arguments to evalModel call
        EpetraExt::ModelEvaluator::InArgs inArgs = Model.createInArgs();

        RCP<Epetra_Vector> x = rcp(new Epetra_Vector(*(Model.get_x_init())));
        inArgs.set_x(x);

        // Set output arguments to evalModel call
        EpetraExt::ModelEvaluator::OutArgs outArgs = Model.createOutArgs();

        RCP<Epetra_Vector> f = rcp(new Epetra_Vector(x->Map()));
        outArgs.set_f(f);

        Model.evalModel(inArgs, outArgs);

        //x->Print(cout<<"Here is x ");
        //f->Print(cout<<"Here is f ");

        cout << "Trying Rythmos via Piro" << endl;

        string inputFile=problem.Omega->root+".xml";
        RCP<Teuchos::ParameterList> piroParams =
        rcp(new Teuchos::ParameterList("Piro Parameters"));
        Teuchos::updateParametersFromXmlFile(inputFile.c_str(),
                                             piroParams.ptr());

        // might want to use Broadcast version for big problems

        RCP<EpetraExt::ModelEvaluator> piro;
        piro = rcp(new Piro::Epetra::RythmosSolver(piroParams,
                                                   rcp(&Model,false)));

        EpetraExt::ModelEvaluator::InArgs piro_inArgs = piro->createInArgs();
        EpetraExt::ModelEvaluator::OutArgs piro_outArgs = piro->createOutArgs();
        RCP<Epetra_Vector> gx = rcp(new Epetra_Vector(*(piro->get_g_map(0))));
        piro_outArgs.set_g(0,gx);

        piro->evalModel(piro_inArgs, piro_outArgs);

        //gx->Print(cout << "After Rythmos, solution is: \n");

        // need to make sure that the output vector is inserted back into U
        std::copy(&((*gx)[0]), &((*gx)[0])+gx->MyLength(),
                  problem.Omega->U.elmt_data.data());
        problem.Omega->U.tecplot("rythmos.dat","Rythmos solution");
        problem.Omega->write(problem.Omega->root+".rst",problem.Omega->U);
        problem.Omega->U.norm();
        return 0;
      } else
#endif
      {
        Stopwatch cpu;
        cpu.start();
        status = problem.solve();
        const double dwall = cpu.stop();
        if (dwall>1.0) {
          const long long int wall =
          boost::numeric_cast<long long int>(round(cpu.stop()));
          const long long int days = wall/60/60/24;
          const long long int hours = (wall/60/60)%24;
          const long long int mins = (wall/60)%60;
          const long long int secs = wall%60;
          stringstream ss;
          if (days) ss << days << " days ";
          if (hours) ss << hours << " hours ";
          if (mins) ss << mins << " mins ";
          if (secs) ss << secs << " secs";
          DGM::Comm::World->cout() << "Total run time: " << sci(cpu.stop())
          << " sec = " << ss.str() << endl;
        } else {
          DGM::Comm::World->cout() << "Total run time: " << sci(cpu.stop())
          << " sec" << endl;
        }
        // if timing mode, store cpu time in weights file
        // normalized to affine time of polynomial order zero
        if (params.defined("timing")) {
          // get problem parameters (for eqntype)
          // problem.parameters(params);
          // get parameters from the user
          int pt = problem.params["eqntype"];
          int physics = p2i(Reo::EqnType(pt));
          // update database entry for this tuple
          problem.update_timings("dgm", Reo::NumEqntype, physics);
        }
      }
    }
    if (status==2) goto execute;

#ifdef DGM_TEST_GLOBAL_IDS
    // test the global IDs
    const int ne = problem.Omega->U[0]->ne;
    for (int e=0; e<ne; ++e) {
      cout << comm->MyPID() << ": " << e << " "
           << problem.Omega->U[0]->el[e]->id << " "
           << problem.Omega->U[0]->el[e]->gid << endl;
    }
#endif

#ifdef DGM_TEST_BOOST_SERIALIZATION
    // test the boost::serialization
    {
      ofstream ofs("test.txt", ios::binary);
      problem.Omega->save(ofs);
      problem.Omega->step = 10;
      problem.Omega->t = 4.5;
      problem.Omega->save(ofs);
    }
    {
      ifstream ifs("test.txt", ios::binary);
      problem.Omega->restore(ifs);
    }
    return 0;
#endif

    comm->cout() << "Completed Reo on " << DGM::dateTime() << endl;

#ifdef DGM_USE_MALLINFO
    static struct mallinfo minfo;
    minfo = mallinfo();
    /*  Documentation for malloc information
        From: http://www.delorie.com/djgpp/doc/libc/libc_550.html

        arena: The total amount of space, in bytes, handed by sbrk to
        malloc. Note that this is not the same as sbrk(0), since sbrk
        allocates memory in large chunks and then subdivides them and passes
        them to malloc as required. In particular, the result of sbrk(0)
        might be much larger than the arena member of struct mallinfo when
        the DPMI host allocates memory in non-contiguous regions (happens on
        MS-Windows).

        ordblks: The number of "ordinary blocks": the total number of
        allocated and free blocks maintained by malloc.

        smblks: The number of "small blocks". This is normally zero, unless
        malloc was compiled with the symbol NUMSMALL defined to a non-zero
        value. Doing so activates an optional algorithm which serves small
        allocations quickly from a special pool. If this option is activated,
        the smblks member returns the number of free small blocks (the
        allocated small blocks are included in the value of ordblks).

        hblks hblkhd Always zero, kept for compatibility with other systems.

        usmblks: The space (in bytes) in "small blocks" that are in use. This
        is always zero in the DJGPP implementation.

        fsmblks: The space in free "small blocks". Non-zero only of malloc
        was compiled with NUMSMALL defined to a non-zero value. In that case,
        gives the amount of space in bytes in free small blocks.

        uordblks: The amount of space, in bytes, in the heap space currently
        used by the application.  This does not include the small overhead (8
        bytes per block) used by malloc to maintain its hidden information in
        each allocated block.

        fordblks: The amount of free heap space maintained by malloc in its
        free list.
    */
    DGM::Comm::World->cout()
      << "Memory Allocation Summary:"<<endl
      << "  size_t size is " << sizeof(size_t)*8 << " bits"
      <<std::endl
      << "  arena        " << setw(12) <<(unsigned int) minfo.arena
      << "    Total size of memory allocated with sbrk by malloc, in bytes. "
      <<std::endl
      << "  uordblks     " << setw(12) <<(unsigned int) minfo.uordblks
      << "    Total size of memory occupied by chunks handed out by malloc."
      <<std::endl
      << "  fordblks     " << setw(12) <<(unsigned int) minfo.fordblks
      << "    Total size of memory occupied by free (not in use) chunks."
      <<std::endl
      << "  ordblks      " << setw(12) <<minfo.ordblks
      << "    Number of chunks not in use. "
      <<std::endl<<setw(28)<<" "
      << "   (The memory allocator internally gets chunks of "
      <<std::endl<<setw(28)<<" "
      << "   memory from the operating system, and then carves them "
      <<std::endl<<setw(28)<<" "
      << "   up to satisfy individual malloc requests)"
      <<std::endl
      << "  hblkhd       " << setw(12) <<(unsigned int) minfo.hblkhd
      << "    Total size of memory allocated with mmap, in bytes."
      <<std::endl
      << "  hblks        " << setw(12) <<minfo.hblks
      << "    Total number of chunks allocated with mmap."
      <<std::endl
      << "  usmblks      " << setw(12) <<minfo.usmblks
      <<std::endl
      << "  fsmblks      " << setw(12) <<minfo.fsmblks
      <<std::endl
      << "  keepcost     " << setw(12) <<minfo.keepcost
      << "    Size of the top-most releasable chunk that normally borders "
      <<std::endl<<setw(28)<<" "
      <<"   the end of the heap (i.e., the high end of the virtual "
      <<std::endl<<setw(28)<<" "
      <<"   address space's data segment)."
      << std::endl;
#endif
#endif  // defined(DGM_PARALLEL) && defined(DGM_GROUPS)
#ifdef DGM_EXPLICIT_COMM_DESTRUCT
    // explicitly invoke Mpi destructor via shared_ptr
    DGM::Comm::World->Barrier();
#ifdef DGM_USE_TEUCHOS_RCP
    DGM::Comm::World.Teuchos::RCP<Comm>::~Teuchos::RCP();
#else
    DGM::Comm::World.boost::shared_ptr<DGM::Comm>::~shared_ptr();
#endif
#endif
    DGM::ClearDBs();
  }
  catch (int int_e) {
    cout << DGM::Comm::World->MyPID() << ": Integer exception: "<<int_e<<endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(int_e);
    return int_e;
  }
  catch (DGM::exception &dgm_e) {
    if (dgm_e.error_code!=0) {
      cout << DGM::Comm::World->MyPID() << ": DGM exception:  "
          << dgm_e.what() << endl;
      if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    }
    return dgm_e.error_code;
  }
  catch (std::exception &std_e) {
    cout << DGM::Comm::World->MyPID() << ": Standard exception: "
        << std_e.what() << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    return DGM::FAILURE;
  }
  catch (...) {
    cout << DGM::Comm::World->MyPID() << ": Unknown exception..." << endl;
    if (DGM::Comm::World->NumProc()>1) DGM::Comm::World->abort(DGM::FAILURE);
    return DGM::FAILURE;
  }
#ifndef DGM_EXPLICIT_COMM_DESTRUCT
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  DGM::Comm::World->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
#endif
  return status;
}

/// Creates a parameter Table of the input arguments.
void parse_args( DGM::ArgList &args, DGM::Table &params, DGM::Info &info ) {
  string name, value;
  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage("dgm.exe");
      } else if (name == "-defines") {
        if (DGM::Comm::World->Master()) {
          std::ofstream def("defines.out");
          info.defines(def);
        }
      } else if (name == "-timing") {
        params["timing"] = true;
      } else if (name == "-pause") {
        params["pause"] = true;
#if defined(DGM_PARALLEL) && defined(DGM_GROUPS)
      } else if (name == "-ncomm") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["ncomm"] = atoi(value.c_str());
#endif
      }
    }
  }
  // remove tagged arguments
  for (std::list< DGM::ArgList::iterator >::iterator a=li.begin();
  a!=li.end(); a++) args.erase(*a);

  // make sure that enough arguments remain
  if (args.size() < 2) {
    showUsage("dgm.exe");
    throw DGM::exception("Not enough arguments");
  }
}

/// Output the code usage statement
/** If there is an error in the input argument list, this routine prints the
    correct usage information. */
void showUsage(const string& code) {
  DGM::Comm::World->cout()
    << "================================================================\n"
    << "Discontinuous Galerkin Solver                                   \n"
    << "================================================================\n"
    << "Usage:  \t" << code << " [Options] run_name                     \n"
    << "----------------------------------------------------------------\n"
    << "Options: " << '\t' << "Description                              \n"
    << "----------------------------------------------------------------\n"
    << "-help    " << '\t' << "Detailed help                            \n"
    << "-pause   " << '\t' << "Pause execution for debugging            \n"
    << "-defines " << '\t' << "Show compile-time defines                \n"
#if defined(DGM_PARALLEL) && defined(DGM_GROUPS)
    << "-ncomm   " << '\t' << "Number of communicators                  \n"
#endif
    << "----------------------------------------------------------------\n";
}

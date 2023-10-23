/*=============================================================================
  Title:      Discontinuous Galerkin Method (DGM) locate

  Author:     S. Scott Collis
              Scalable Algorithms (1416)
              Sandia National Laboratories
              Albuquerque, NM 87175-1320
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2010 Sandia National Laboratories
=============================================================================*/

/** \file dgm_loc.cpp
    \brief Locates nodes in a DGM mesh. */

// system libraries
#include <cstdio>
#include <cmath>

// CMC libraries
#include "Stopwatch.hpp"
using CMC::Stopwatch;

// DGM libraries
#include "Comm.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif
#include "Partition.hpp"
#include "Mesh.hpp"
#include "Field.hpp"
#include "Coordinates.hpp"
#include "Info.hpp"

#ifdef DGM_USE_STK_SEARCH

// Trilinos includes
#include "CoarseSearch.hpp"

namespace {

  void stk_search_print(FILE             *fp,
                        DGM::Mesh        &mesh,
                        const dMatrix    &xyz,
                        const int         nsd,
                        const std::string &root) {
    // stk_search uses compile time dimensions.  Since 2D is a simple case of
    // 3D, hard code everything to 3D.
    const int NSD_(3);

    // (ID#,Processor#) Do not use Proc # if everything done on proc 0.
    typedef stk::search::ident::IdentProc<size_t, unsigned>IdentProc;
    typedef stk::search::box::AxisAlignedBoundingBox
      <IdentProc,float,NSD_>  RangeBoundingVolume; // Boxes around hexes
    typedef stk::search::box::PointBoundingBox
      <IdentProc,float,NSD_>  DomainBoundingVolume;// Spheres around points
    std::vector<RangeBoundingVolume>  range;
    std::vector<DomainBoundingVolume> domain;
    std::vector<std::pair<DomainBoundingVolume::Key,RangeBoundingVolume::Key> >
      domain_to_range_keys;

    const DGM::Comm *comm = DGM::Comm::World;
    const unsigned np     = comm->NumProc();
    const unsigned my_pid = comm->MyPID();
    if (mesh.ne < np) {
      if (comm->Master())
        cerr<<"Number of processors exceeds numbers of elements"<<endl;
      comm->exit(DGM::FAILURE);
    }

    DGM::Partition::Ptr partition( new DGM::Partition(mesh.ne, root, comm) );

    const size_t nn = xyz.rows();
    const size_t ne = partition->ne;
    const size_t gne = partition->gne;
    const iVector &inc = partition->setup_local_id_array();
    const iVector &eid = partition->eid;

    cout <<" Number of elements on processor "<<my_pid<<" is "<<ne<<std::endl;

    range.reserve(ne);
    for (size_t i=0; i<gne; ++i) {
      if (0<=inc[i]) {
        // Set up the boxes that define the mesh: Range
        const std::vector<float> bound = mesh.box(i);
        IdentProc id(i,0);
        RangeBoundingVolume box(&bound[0], id);
        box.expand(.0000001); // find all boxes bounding a corner or side.
        range.push_back(box);
      }
    }
    // Set up the points to find in the mesh: Domain
    domain.reserve(nn);
    for(int i=0; i<nn; ++i) {
      std::vector<float> obs_point(NSD_,0);
      for (size_t j=0; j<nsd; ++j) obs_point[j] = xyz[i][j];
      IdentProc id(i,0);
      DomainBoundingVolume point(&obs_point[0], id);
      domain.push_back(point);
    }

    stk::search::FactoryOrder order;
    order.m_algorithm =  stk::search::FactoryOrder::BIHTREE;
    // Perform search of all points in all boxes with one function call........
    coarse_search(domain_to_range_keys, range, domain, order);

    typedef std::map<unsigned, std::vector<unsigned> > PrintMap;
    PrintMap printlines;
    if (!my_pid) for(int i=0;i<nn;++i) printlines[i];//if outside every element;

    // determine if point in box is actually in element contained within box...
    for(size_t i=0; i<domain_to_range_keys.size(); ++i) {
      const unsigned src = domain_to_range_keys[i].first.ident;
      const unsigned dst = domain_to_range_keys[i].second.ident;
      if (mesh.is_in_element(xyz[src], dst)) printlines[src].push_back(dst);
    }

    // Serialize printlines and send to processor 0:
    std::vector<unsigned> send_buf;

    for (PrintMap::const_iterator p=printlines.begin();
         p!=printlines.end(); ++p) {
      const std::vector<unsigned> &n = p->second;
      send_buf.push_back(p->first);              // pack observation point
      send_buf.push_back(n.size());              // pack number of elements
      send_buf.insert(send_buf.end(), n.begin(), n.end()); // pack elements
    }

    unsigned n = send_buf.size();
    std::vector<unsigned> recv_count_buf(np,0);
    std::vector<int>      recvcounts(np,0);
    std::vector<int>      displs(np,0);

    comm->Gather(&n, 1, &recv_count_buf[0], 1);// gather to root message sizes

    size_t receive_size=0;
    for (size_t i=0; i!=np; ++i) {
      if (i) displs[i] = receive_size;
      recvcounts[i] = recv_count_buf[i];
      receive_size += recvcounts[i];
    }

    std::vector<unsigned> receive_buffer;
    if (!my_pid) receive_buffer.resize(receive_size); // only receive at root
    comm->GatherV(&send_buf[0], n, &receive_buffer[0], &recvcounts[0],
                  &displs[0]);

    printlines.clear();
    size_t k = 0;
    while (k < receive_size) { // receive_size === 0 on non-root processors
      const unsigned key = receive_buffer[k++];     // unpack observation point
      const unsigned size= receive_buffer[k++];     // unpack number of elements
      std::vector<unsigned> &n = printlines[key];   // unpack elements
      for (size_t i=0; i!=size; ++i) n.push_back(receive_buffer[k++]);
    }

    for (PrintMap::const_iterator i=printlines.begin();
         i!=printlines.end(); ++i) {
      const unsigned src             = i->first;
      std::vector<unsigned> elements = i->second;
      fprintf(fp,"%d ",src);             // node number
      // node coordinates
      for(int j=0;j<nsd;j++) fprintf(fp,"%15.8e ",xyz[src][j]);
      // number of elements where the node lives
      fprintf(fp,"%d ",elements.size());
      std::sort(elements.begin(), elements.end());
      for(int j=0;j<elements.size();j++)
        fprintf(fp,"%d ",elements[j]);  // element IDs where the node is inside
      fprintf(fp,"\n");
    }
  }

} // anonymous namespace

#endif  // DGM_USE_STK_SEARCH

/// DGM utility to locate the elements that contain a list of points
int main(int argc, char **argv) {
  using namespace DGM;
  try {
#ifdef DGM_PARALLEL
    DGM::Comm::World.reset( new DGM::MpiComm( &argc, &argv ) );
#else
    DGM::Comm::World.reset( new DGM::SerialComm() );
#endif
    DGM::Comm::Interupt();
    DGM::Comm::Ptr &comm(DGM::Comm::World);
    std::ostream &out(comm->cout());
    {
      DGM::Info info;
      info.name(out);
    }
    Stopwatch cpu;
    cpu.start();
    comm->cout() << "DGM locate" << endl;

    Ordinal nn, nsd;
    DGM::Ordinal elenum=0;
    char *fname_mesh, *fname_node, *fname_nlocation;
    std::vector<DGM::Size> elemindex(8);
    string buffer;
    Point ptmp;
    FILE *fp=0;

    // Parse command line arguments
    switch(argc) {
    case 4:
      fname_mesh = argv[1];
      fname_node = argv[2];
      fname_nlocation = argv[3];
      break;
    default:
      cerr<<"Usage: dgm_loc.exe root.msh nodes root.anl"<<endl;
      return DGM::SUCCESS;
    }

    // Get the nodes
    ifstream nodes(fname_node);
    if (!nodes) {
      cerr << "  Could not open coordinate file " << fname_node << endl;
      comm->exit(DGM::FAILURE);
    }

    nodes >> nn >> nsd;
    getline(nodes, buffer);
    comm->cout()<<"  Number of nodes = " << nn <<", Dimension = "<<nsd<<endl;

    dMatrix xyz(nn,nsd);

    for (Ordinal i=0; i<nn; i++) {
      for (Ordinal j=0; j<nsd; j++)
        nodes >> xyz[i][j];
      getline(nodes, buffer);
    }

    if (comm->Master()) fp = fopen(fname_nlocation,"w");

    // Output Response format header

    if (comm->Master()) {
      fprintf(fp,"Nnodes Nsd \n");
      fprintf(fp,"%llu %llu\n",(long long unsigned)nn,(long long unsigned)nsd);
      if(nsd==1)
        fprintf(fp,"NodeID   NodeX   Nelmts  EID\n");
      else if(nsd==2)
        fprintf(fp,"NodeID   NodeX   NodeY   Nelmts   EID \n");
      else if(nsd==3)
        fprintf(fp,"NodeID   NodeX   NodeY   NodeZ    Nelmts  EID\n");
    }

    comm->cout() << "  Creating mesh" << endl;
    Mesh mesh(fname_mesh);

    // Searching mesh data to find the location of nodes
#ifdef DGM_USE_STK_SEARCH
    comm->cout() << "  STK searching mesh" << endl;
    stk_search_print(fp, mesh, xyz, nsd, std::string(fname_mesh));
#else
    comm->cout() << "  Normal searching mesh" << endl;
    for(Ordinal i=0; i<nn; i++) {
      if(nsd==1) {
        ptmp = Point(xyz[i][0]);
        elenum = mesh.find_source_elem_1d(ptmp,&elemindex[0]);
      } else if(nsd==2) {
        ptmp = Point(xyz[i][0],xyz[i][1]);
        elenum = mesh.find_source_elem_2d(ptmp,&elemindex[0]);
      } else if(nsd==3) {
        ptmp = Point(xyz[i][0],xyz[i][1],xyz[i][2]);
        elenum = mesh.find_source_elem_3d(ptmp,&elemindex[0]);
      }
      if (comm->Master()) {
        fprintf(fp,"%llu ",(long long unsigned)i);  // node number
        for(Ordinal j=0;j<nsd;j++)
          fprintf(fp,"%15.8e ",xyz[i][j]);      // node coordinates
        // # of elements node lives in
        fprintf(fp,"%llu ",(long long unsigned)elenum);
        // elements with the node inside
        for(Ordinal j=0;j<elenum;j++) {
          fprintf(fp,"%llu ",(long long unsigned)elemindex[j]);
        }
        fprintf(fp,"\n");
      }
    }
#endif // DGM_USE_STK_SEARCH
    if (comm->Master()) fclose(fp);
    cout << "Total execution time:  " << cpu.stop() << " seconds"<< endl;
  }
  catch (int x) {
    // DGM::Comm::World->cout() << "Caught integer exception: " << x << endl;
    return x;
  }
  catch (DGM::exception &e) {
    DGM::Comm::World->cout() << "DGM exception:  " << e.what() << endl;
    return e.error_code;
  }
  catch (std::exception &e) {
    DGM::Comm::World->cout() << "Standard exception: " << e.what() << endl;
    return DGM::FAILURE;
  }
  catch (...) {
    DGM::Comm::World->cout() << "Unknown exception..." << endl;
    return DGM::FAILURE;
  }
#ifdef OPEN_MPI
#if !((OMPI_MAJOR_VERSION <= 1) && (OMPI_MINOR_VERSION <= 8) && \
    (OMP_RELEASE_VERSION <= 4))
  comm->cout()<<"Explicitly calling World::reset()"<<endl;
  DGM::Comm::World.reset();
#endif
#endif
  return DGM::SUCCESS;
}

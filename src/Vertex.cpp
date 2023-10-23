/** \file Vertex.cpp
    \brief DGM element vertex class definitions
    \author S. Scott Collis
    \author Axel Gerstenberber
*/

// system includes
#ifdef DGM_USE_GENERAL_GHOSTING
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#endif

// DGM includes
#include "Vertex.hpp"

#ifdef DGM_USE_GENERAL_GHOSTING
int DGM::Vertex::test_serialization() {

  std::cout << "DGM::Vertex::test_serialization: " << std::flush;

  // create test data
  std::vector<DGM::Vertex> vertices;
  vertices.push_back(DGM::Vertex(1,3,DGM::Point(0.0,1.0,2.0)));
  vertices.push_back(DGM::Vertex(2,8,DGM::Point(8.0,7.0,6.0)));

  // serialize
  std::ostringstream sendstream;
  boost::archive::binary_oarchive oar(sendstream);
  oar & vertices;
  std::string sendstring(sendstream.str());

  // dummy transfer: this could be a distributed memory data transfer
  std::string recvstring = sendstring;

  // deserialize
  std::string s(recvstring);
  std::istringstream recvstream(s);
  boost::archive::binary_iarchive iar(recvstream);
  std::vector<DGM::Vertex> recv_vertices;
  iar & recv_vertices;

  // test size of vector
  int status = 0;
  if (vertices.size() != recv_vertices.size()) {
    status = -1;
  }
  // test content
  for (std::size_t i=0; i != recv_vertices.size();i++) {
    if (vertices[i].id  != recv_vertices[i].id  or
        vertices[i].gid != recv_vertices[i].gid or
        vertices[i].eid != recv_vertices[i].eid or
        vertices[i].x   != recv_vertices[i].x   or
        vertices[i].y   != recv_vertices[i].y   or
        vertices[i].z   != recv_vertices[i].z) {
      status = -1;
    }
    if (status != 0) {
      std::cout << vertices[i] << std::endl;
      std::cout << recv_vertices[i] << std::endl;
    }
  }
  if (status != 0)
    cout << "Test FAILED" << endl;
  else
    cout << "Test SUCCESS" << endl;
  return status;
}
#endif // #ifdef DGM_USE_GENERAL_GHOSTING

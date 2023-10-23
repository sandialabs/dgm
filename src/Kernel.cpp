/** \file Kernel.cpp
    \brief DGM kernel class
    \author Scott Collis
*/

// system includes
#include <limits>
#include <vector>

// JSON includes
#ifdef DGM_USE_JSON
#include "json/json.h"
#endif

// DGM includes
#include "Kernel.hpp"
#include "Types.hpp"
#include "String.hpp"
#include "Element.hpp"
#include "Coordinates.hpp"
#include "Field.hpp"
#include "vField.hpp"
#ifdef DGM_PARALLEL
#include "MpiComm.hpp"
#else
#include "SerialComm.hpp"
#endif

namespace DGM {

namespace {

  /// determine if a point in inside a bounding box to a single tolerance
  bool is_inside( const Point &p, const BoundingBox& box,
                  const Scalar epsilon) {
    Point ll = lower_left(box);
    Point ur = upper_right(box);
    return p.x >= ll.x-epsilon &&
        p.y >= ll.y-epsilon &&
        p.z >= ll.z-epsilon &&
        p.x <= ur.x+epsilon &&
        p.y <= ur.y+epsilon &&
        p.z <= ur.z+epsilon;
  }

  /// is a point insize a bounding box with tolerance in each direction
  bool is_inside( const Point &p, const BoundingBox& box,
                  const dVector &epsilon) {
    Point ll = lower_left(box);
    Point ur = upper_right(box);
    return p.x >= ll.x-epsilon[0] &&
        p.y >= ll.y-epsilon[1] &&
        p.z >= ll.z-epsilon[2] &&
        p.x <= ur.x+epsilon[0] &&
        p.y <= ur.y+epsilon[1] &&
        p.z <= ur.z+epsilon[2];
  }

  /// determine if this rank owns the center of the kernel
  void resolve_parallel(bool    &multi_processor,
                        Ordinal &proc_with_center,
                        bool    &center_on_proc,
                        const    DGM::Comm::Ptr comm,
                        const    std::vector<Ordinal> &eidx)
  {
    unsigned n = eidx.empty() ? 0 : 1 ;
    n = comm->SumAll(n);
    multi_processor = 1<n;
    n = eidx.empty() ? numeric_limits<unsigned>::max() : comm->MyPID();
    comm->MinAll(n);
    if (n == numeric_limits<unsigned>::max())
      comm->error(" Kernel.cpp::resolve_parallel -- failed to find"
                  " an element containing the center of probe.");
    center_on_proc = (comm->MyPID() == numeric_cast<int>(n));
    proc_with_center = n;
  }

  /// make the parallel communicator for this kernel
  DGM::Comm::Ptr initialize_probe_comm(const KernelResponse *kernel,
                                       const DGM::Comm::Ptr  comm) {
    DGM::Comm::Ptr sub_comm;
    stringstream ss;
    ss<<"KernelReponse: "<<kernel->name()<<", original rank = "<<comm->MyPID();
    const string myName = ss.str();
#ifdef DGM_PARALLEL
    if (kernel->multiple_processor()) {
      DGM::MpiComm &myComm = dynamic_cast<DGM::MpiComm &>(*comm);
      MPI_Comm old_mpi_comm = myComm.mpicomm(), new_mpi_comm;
      const int rank = comm->MyPID()+1;
      const int membershipKey = kernel->locally_evaluated() ? 1 : MPI_UNDEFINED;
      const int new_rank      = kernel->owned_by_this_proc()? 0 : rank;
      MPI_Comm_split(old_mpi_comm, membershipKey, new_rank, &new_mpi_comm);
      if (membershipKey != MPI_UNDEFINED)
        sub_comm.reset(new MpiComm(new_mpi_comm, myName));
    } else {
      if (kernel->owned_by_this_proc())
        sub_comm.reset(new MpiComm(MPI_COMM_SELF, myName));
    }
#else
    if (kernel->owned_by_this_proc())
      sub_comm.reset(new SerialComm(myName, Comm::NO_SCRATCH));
#endif
    return sub_comm;
  }

} // anonymous namespace

KernelResponse::KernelResponse(const Size global_id,
                               const std::string &name,
                               const Point C)
  : gid(global_id),
    identifier(name),
    center(C),
    eidx(),
    proc_with_center(0),
    multiplicity    (0),
    center_on_proc  (false),
    multi_processor (false),
    base_kernel(),
    probe_comm()
{}

KernelResponse::~KernelResponse() 
{
   if (probe_comm) probe_comm->CommFree();
}

GaussianResponse::GaussianResponse(const Size global_id,
                                   const std::string &name,
                                   const Point C,
                                   const Field *F,
                                   const vector<Size> &elem,
                                   const Scalar sigma,
                                   const Scalar num_std_dev)
  : KernelResponse(global_id, name, C)
{
  const DGM::Comm::Ptr comm = F->get_comm();
  const Field::PartitionPtr partition = F->partition;
  if (elem.empty()) {
    const BoundingBox &box = F->my_box();
    if ( is_inside(C, box, sigma*num_std_dev +
                   sqrt(numeric_limits<Scalar>::epsilon())) ) {
      for (Ordinal k=0; k<partition->ne(); ++k) {
        if (F->el[k]->is_in_box(C, sigma*num_std_dev)) eidx.push_back(k);
      }
    }
  } else {
    for (size_t j=0; j!=elem.size(); ++j) {
      if (partition->owns(elem[j])) eidx.push_back(partition->inc(elem[j]));
    }
  }

  for (size_t i=0; i<eidx.size() && !center_on_proc; ++i) {
    if (F->is_in_element(C, eidx[i], 0.0)) center_on_proc = true;
  }
  GaussianBase *gaussianbase=0;

  switch (F->nsd()) {
    case 1: gaussianbase = new Gaussian1d(sigma, C, num_std_dev); break;
    case 2: gaussianbase = new Gaussian2d(sigma, C, num_std_dev); break;
    case 3: gaussianbase = new Gaussian3d(sigma, C, num_std_dev); break;
  }
  base_kernel.reset(gaussianbase);

  resolve_parallel(multi_processor,
                   proc_with_center,
                   center_on_proc,
                   comm,
                   eidx);

  probe_comm = initialize_probe_comm(this, comm);

  local_gaussian_coeff.resize(eidx.size());
  for (size_t i=0; i<eidx.size(); ++i) {
    const Element *e =  F->el[eidx[i]];
    local_gaussian_coeff[i].resize(e->qtot);
    local_gaussian_coeff[i] = 0;
    dVector V = local_gaussian_coeff[i];
    const Coord &C = *e->C;
    gaussianbase->addScaled(C, 1., V);
  }
}

GaussianEllipseResponse::GaussianEllipseResponse(const Size global_id,
                                   const std::string &name,
                                   const Point C,
                                   const Field *F,
                                   const dMatrix &directions,
                                   const Ordinal derivatives[3],
                                   const Scalar sigma[3],
                                   const Scalar num_std_dev)
  : KernelResponse(global_id, name, C)
{
  const DGM::Comm::Ptr comm = F->get_comm();
  const Field::PartitionPtr partition = F->partition;
  const BoundingBox &box = F->my_box();

  const Scalar eps = sqrt(numeric_limits<Scalar>::epsilon());
  dVector radius(3);
  radius[0] = sigma[0]*num_std_dev + eps;
  radius[1] = sigma[1]*num_std_dev + eps;
  radius[2] = sigma[2]*num_std_dev + eps;
  if ( is_inside(C, box, radius) ) {
    for (Ordinal k=0; k<partition->ne(); ++k) {
      if (F->el[k]->is_in_element(C, directions, radius)) eidx.push_back(k);
    }
  }

  for (size_t i=0; i<eidx.size() && !center_on_proc; ++i) {
    if (F->is_in_element(C, eidx[i], 0.0)) center_on_proc = true;
  }

  GaussianBase *gaussianbase=0;
  switch (F->nsd()) {
    case 1: gaussianbase = new GaussianEllipse1d(
        C[0],
        sigma[0],
        derivatives[0],
        num_std_dev); break;
    case 2: gaussianbase = new GaussianEllipse2d(
        C[0],
        C[1],
        sigma[0],
        sigma[1],
        derivatives[0],
        derivatives[1],
        directions[0][0],
        directions[0][1],
        directions[1][0],
        directions[1][1],
        num_std_dev); break;
    case 3: gaussianbase = new GaussianEllipse3d(
        C[0],
        C[1],
        C[2],
        sigma[0],
        sigma[1],
        sigma[2],
        derivatives[0],
        derivatives[1],
        derivatives[2],
        directions[0][0],
        directions[0][1],
        directions[0][2],
        directions[1][0],
        directions[1][1],
        directions[1][2],
        directions[2][0],
        directions[2][1],
        directions[2][2],
        num_std_dev); break;
  }
  base_kernel.reset(gaussianbase);

  resolve_parallel(multi_processor, proc_with_center, center_on_proc,
                   comm, eidx);

  probe_comm = initialize_probe_comm(this, comm);

  local_gaussian_coeff.resize(eidx.size());
  for (size_t i=0; i<eidx.size(); ++i) {
    const Element *e =  F->el[eidx[i]];
    local_gaussian_coeff[i].resize(e->qtot);
    local_gaussian_coeff[i] = 0;
    dVector V = local_gaussian_coeff[i];
    const Coord &C = *e->C;
    gaussianbase->addScaled(C, 1., V);
  }
}

GaussianLineSegment2dResponse::GaussianLineSegment2dResponse(
    const Size global_id,
    const std::string &name,
    const Field *F,
    GaussianLineSegment2d *gls
) : KernelResponse(global_id, name, midpoint(gls->P1,gls->P2))
{
  const DGM::Comm::Ptr comm = F->get_comm();
  const Field::PartitionPtr partition = F->partition;
  const BoundingBox &box = F->my_box();

  if (F->nsd()!=two) {
    comm->error("  GaussianLineSegment2dResponse: unsupported "
            "number of space dimensions: "+asString(F->nsd()));
  }

  Scalar zone = gls->get_sigma()*gls->get_numStdDev()
                + sqrt(numeric_limits<Scalar>::epsilon());
  if ( is_inside(gls->P1, box, zone) || is_inside(gls->P2, box, zone) ) {
    std::vector<Scalar> centroid(3);   // Not used for GaussianLineSegment2d
    for (Ordinal e=0; e<partition->ne(); ++e) {
      const Element *E = F->el[e];
      for (Ordinal i=0; i<E->qtot; ++i) {
        const Point qpt(E->C->x[i], E->C->y[i], E->C->z[i]);
        if ( gls->within_distance(qpt,centroid) ) {
          eidx.push_back(e);
          break;
        }
      }
    }
  }

  const Point mp = midpoint(gls->P1,gls->P2);
  for (size_t i=0; i<eidx.size() && !center_on_proc; ++i)
    if (F->is_in_element(mp, eidx[i], 0.0)) center_on_proc = true;

  base_kernel.reset(gls);

  resolve_parallel(multi_processor, proc_with_center, center_on_proc,
                   comm, eidx);

  probe_comm = initialize_probe_comm(this, comm);

  local_gaussian_coeff.resize(eidx.size());
  for (size_t i=0; i<eidx.size(); ++i) {
    const Element *e =  F->el[eidx[i]];
    local_gaussian_coeff[i].resize(e->qtot);
    local_gaussian_coeff[i] = 0;
    dVector V = local_gaussian_coeff[i];
    const Coord &C = *e->C;
    gls->addScaled(C, one, V);
  }
}

/// Helper function to parse Json input specification
std::vector<GaussianLineSegment2d *>
GaussianLineSegment2d::reader(const Json::Value &json,
                              const Scalar nsd,
                              const DGM::Comm::Ptr comm,
                              const Ordinal verb ) {
  std::vector<GaussianLineSegment2d *> GLS;
  if (nsd!=2) {
    comm->error("  GaussianLineSegment kernel unsupported "
                "number of space dimensions: "+asString(nsd));
  }
  const double sigma = json.get("Standard deviation",0).asDouble();
  const double nsigma = json.get("Number of standard deviations",5).asDouble();
  if ( !json.isMember("Segments") ) {
    comm->error("\"Segments\" is a required member of GaussianLineSegment.");
  } else {
    if ( !json["Segments"].isArray() ) {
      comm->error("\"Segments\" must be an array.");
    } else {
      const Json::Value segments = json["Segments"];
      Point p1, p2;
      const Ordinal nseg = (Ordinal)segments.size();
      for (Ordinal s=0; s<nseg; ++s) {
        const Json::Value points = segments[Json::ArrayIndex(s)];
        if ( !points.isArray() ) {
          comm->error("Elements of \"Segments\" must be an array.");
        } else {
          if ( (Ordinal)points.size() != 2 ) {
            comm->error("Each element of \"Segments\" must be "
                        "a two element array (i.e., point 1 and point 2 "
                        "locations - [[x1, y1],[x2, y2]] ).");
          } else {
            const Json::Value p1Array = points[Json::ArrayIndex(zero)];
            if (two == (Ordinal)p1Array.size()) {
              p1.x = p1Array[Json::ArrayIndex(zero)].asDouble();
              p1.y = p1Array[Json::ArrayIndex(one)].asDouble();
              p1.z = zero;
            } else {
              const Ordinal d = (Ordinal)p1Array.size();
              comm->error("  GaussianLineSegment: "
                          "Need 2 dimensions (have "+asString(d)+")"
                          " for segment "+asString(s)+", point 1.");
            }
            const Json::Value p2Array = points[Json::ArrayIndex(one)];
            if (two == (Ordinal)p2Array.size()) {
              p2.x = p2Array[Json::ArrayIndex(zero)].asDouble();
              p2.y = p2Array[Json::ArrayIndex(one)].asDouble();
              p2.z = zero;
            } else {
              const Ordinal d = (Ordinal)p2Array.size();
              comm->error("  GaussianLineSegment: "
                          "Need 2 dimensions (have "+asString(d)+")"
                          " for segment "+asString(s)+", point 2.");
            }
          }
        }
        GLS.push_back( new DGM::GaussianLineSegment2d(sigma, p1, p2, nsigma) );
        if (verb>2)
          comm->cout()
            << "  GaussianLineSegment " << s << " has endpoints:\n"
            << "    (" << p1.x << "," << p1.y << "," << p1.z << ") -> "
            << "(" << p2.x << "," << p2.y << "," << p2.z << ")\n"
            << "    Standard deviation = " << sigma << "\n"
            << "    Number of standard deviations = " << nsigma << endl;
      }
    }
  }
  return GLS;
}

DeltaResponse::DeltaResponse(const Size global_id,
                             const std::string &name,
                             const Point C,
                             const Field *F,
                             const vector<Size> &elem,
                             const bool average)
  : KernelResponse(global_id, name, C)
{
  const Field::PartitionPtr partition = F->partition;
  const DGM::Comm::Ptr           comm = F->get_comm();

  if (elem.empty()) {
    const BoundingBox &box = F->my_box();
    if ( is_inside(C, box, sqrt(numeric_limits<Scalar>::epsilon())) ) {
      for (Ordinal k=0; k<partition->ne(); k++) {
        if (F->el[k]->is_in_box(C)) {
          if (F->is_in_element(C, k, 0.0)) eidx.push_back(k);
        }
      }
    }
  } else {
    for (size_t j=0; j!=elem.size(); ++j) {
      if (partition->owns(elem[j])) eidx.push_back(partition->inc(elem[j]));
    }
  }

  for (size_t i=0; i<eidx.size() && !center_on_proc; ++i) {
    if (F->is_in_element(C, eidx[i], 0.0)) center_on_proc = true;
  }

  if (!eidx.empty()) multiplicity=1;

  vector<Size> eids(eidx.size());
  for (size_t i=0; i<eids.size(); ++i) eids[i] = partition->eid(eidx[i]);
  base_kernel.reset(new Delta(eids, C));

  resolve_parallel(multi_processor,
                   proc_with_center,
                   center_on_proc,
                   comm,
                   eidx);

  if (average) {
    if (multi_processor)
      multiplicity = numeric_cast<Ordinal>(comm->SumAll(eidx.size()));
    else
      multiplicity = numeric_cast<Ordinal>(eidx.size());
  } else {
    multiplicity    = 1;
    multi_processor = false;
    if (center_on_proc) eidx.resize(1);
    else                eidx.clear();
  }

  probe_comm = initialize_probe_comm(this, comm);

  local_interpolate.resize(eidx.size());
  local_coordinates.resize(eidx.size());
  for (size_t i=0; i<eidx.size(); ++i) {
    const Element *e =  F->el[eidx[i]];
    const Point    p = e->get_local_coordinates(C);
    local_coordinates[i] = p;
    vector<Point> ps(1,p);
    e->calculate_interpolation_matrices(local_interpolate[i], ps);
  }
  if (!eidx.empty() && local_interpolate[0].empty()) local_interpolate.clear();
}

}  // namespace DGM


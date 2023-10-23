/** \file BndryStats.cpp
    \brief Extracts the solution on a prescribed interelement boundary
    \author Scott Collis
*/

// system includes
#include <cmath>

// DGM includes
#include "BndryStats.hpp"
#include "Field.hpp"

namespace DGM {

BndryStats::BndryStats(const string &root, Field *Fin) :
  comm(Fin->get_comm()), valid(false), F(Fin) {
  read(root);
}

void BndryStats::read(const string &root) {
  // cout << "Bndry_Status::read(const string&)" << endl;
  string fname = root+".bnd";
  ifstream in(fname.c_str());
  if (!in) return;           // assume user doesn't want boundary info

  string buffer;
  int nsides;
  getline(in,buffer);        // read the header line

  int sid, eid;
  if (!(in>>nsides)) error("Cannot read number of boundary elements",1);
  getline(in,buffer);

  // NOTE: When running in parallel we need to keep track of the global order
  // of the sides as listed in the input file so that we can output data in
  // the correct order.
  if (nsides) {
    for (int i=0; i<nsides; i++) {
      if (!(in >> eid >> sid))
        error("Unable to read boundary element information.",1);
      if( F->partition->owns(eid) ) {               // is element in partition
        sides.push_back( F->el[F->partition->inc(eid)]->side[sid] );
        sorder.push_back(i);
      }
    }
    valid = true; // valid even if partition doesn't contain boundary sides.
  }
}

BndryStats::BndryStats(Field *Fin, const vector<Size> &elem,
                       const vector<Ordinal> &side ) :
  comm(Fin->get_comm()), valid(false), F(Fin) {

  // NOTE: When running in parallel we need to keep track of the global order
  // of the sides as listed in the input file so that we can output data in
  // the correct order.
  size_t nsides = elem.size();
  if (nsides) {
    for (size_t i=0; i<nsides; i++) {
      Size eid = elem[i];
      Ordinal sid = side[i];
      if( F->partition->owns(eid) ) {               // is element in partition
        sides.push_back( F->el[F->partition->inc(eid)]->side[sid] );
        sorder.push_back(i);
      }
    }
    valid = true; // valid even if partition doesn't contain boundary sides.
  }
}

int BndryStats::size() const {
  int qtot(0);
  for (size_t i=0; i<sides.size(); ++i) qtot+=sides[i]->qtot();
  return qtot;
}

void BndryStats::write(const string &root) {
  // cout << "BndryStats::write(const string&)" << endl;
  if (!valid) return;
  string fname = root+".bdt";
  ofstream out(fname.c_str());
  for (size_t i=0; i<sides.size(); ++i) {
    Ordinal qtot = sides[i]->qtot();
    // get x, y, z at the side quadrature points
    F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->C->x);
    dVector x(qtot);
    x = sides[i]->u;
    F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->C->y);
    dVector y(qtot);
    y = sides[i]->u;
    // get solution at the side quadrature points
    F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->u);
    for (Ordinal q=0; q<sides[i]->qtot(); ++q )
      out << sides[i]->leid() << " " << sides[i]->id() << " " << q
          << " " << x[q] << " " << y[q] << " " << sides[i]->u[q] << endl;
  }
}

void BndryStats::get_coordinates(Coord &C, const Mesh mesh) {
  // cout << "BndryStats::get_coordinates(Coord &C)" << endl;
  if (!valid) return;
  get_coordinates( C.x, C.y, C.z, mesh );
}

void BndryStats::get_coordinates(dVector &x, dVector &y, dVector &z,
                                 const Mesh mesh) {
  // cout << "BndryStats::get_coordinates()" << endl;
  if (!valid) return;
  int qtot=0;
  for (size_t i=0; i<sides.size(); ++i) qtot += sides[i]->qtot();
  x.resize(qtot);
  y.resize(qtot);
  z.resize(qtot);
  dVector px, py, pz;
  qtot = 0;
  switch(mesh) {
  case(Uniform):
    //cout << "Inside Uniform" << endl;
    for (size_t i=0; i<sides.size(); ++i) {
      Ordinal qsid = sides[i]->qtot();
      // get x, y, z on uniform side mesh
      F->el[sides[i]->leid()]->
        fill_sides_uniform(F->el[sides[i]->leid()]->C->x);
      px.alias(x,qtot,qsid);
      px = sides[i]->u;
      F->el[sides[i]->leid()]->
        fill_sides_uniform(F->el[sides[i]->leid()]->C->y);
      py.alias(y,qtot,qsid);
      py = sides[i]->u;
      F->el[sides[i]->leid()]->
        fill_sides_uniform(F->el[sides[i]->leid()]->C->z);
      pz.alias(z,qtot,qsid);
      pz = sides[i]->u;
      qtot += qsid;
    }
    break;
  case(Collocation):
    for (size_t i=0; i<sides.size(); ++i) {
      Ordinal qsid = sides[i]->qtot();
      // get x, y, z at the side quadrature points
      F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->C->x);
      px.alias(x,qtot,qsid);
      px = sides[i]->u;
      F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->C->y);
      py.alias(y,qtot,qsid);
      py = sides[i]->u;
      F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->C->z);
      pz.alias(z,qtot,qsid);
      pz = sides[i]->u;
      qtot += qsid;
    }
    break;
  default:
    error("Bndy_Stats::get_coordinates() - Invalid Mesh type");
  }
}

void BndryStats::get_solution(dVector &u, const Mesh mesh) {
  // cout << "BndryStats::get_solution()" << endl;
  if (!valid) return;
  int qtot=0;
  for (size_t i=0; i<sides.size(); ++i) qtot += sides[i]->qtot();
  u.resize(qtot);
  dVector pu;
  qtot = 0;
  switch(mesh) {
  case(Uniform):
    for (size_t i=0; i<sides.size(); ++i) {
      Ordinal qsid = sides[i]->qtot();
      F->el[sides[i]->leid()]->fill_sides_uniform(F->el[sides[i]->leid()]->u);
      pu.alias(u,qtot,qsid);
      pu = sides[i]->u;
      qtot += qsid;
    }
    break;
  case(Collocation):
    for (size_t i=0; i<sides.size(); ++i) {
      Ordinal qsid = sides[i]->qtot();
      F->el[sides[i]->leid()]->fill_sides(F->el[sides[i]->leid()]->u);
      pu.alias(u,qtot,qsid);
      pu = sides[i]->u;
      qtot += qsid;
    }
    break;
  default:
    error("Bndy_Stats::get_solution() - Invalid Mesh type");
  }
}

void BndryStats::fill_sides(Field* fin) {
  if (!valid) return;
  for (size_t i=0; i<sides.size(); ++i)
    fin->el[sides[i]->leid()]->fill_sides(fin->el[sides[i]->leid()]->u);
}

// This is done without using the jump savy gradient
void BndryStats::get_solution_gradient(dVector &fx) {
  // cout << "BndryStats::get_solution_gradient()" << endl;
  if (!valid) return;
  int qtot=0;
  for (size_t i=0; i<sides.size(); ++i) qtot += sides[i]->qtot();

  fx.resize(qtot);

  dVector pfx, gu;
  qtot = 0;

  for (size_t i=0; i<sides.size(); ++i) {
    const Ordinal qsid = sides[i]->qtot();
    // Temporary storage for the gradient of the solution
    gu.resize(F->el[sides[i]->leid()]->qtot);

    // Compute the spatial gradient of the field and then
    // use fill_sides to put it on side gaussian points.
    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'x');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfx.alias(fx,qtot,qsid);
    pfx = sides[i]->u;

    qtot += qsid;
  }
}

// This is done without using the jump savy gradient
void BndryStats::get_solution_gradient(dVector &fx, dVector &fy) {
  // cout << "BndryStats::get_solution_gradient()" << endl;
  if (!valid) return;
  int qtot=0;
  for (size_t i=0; i<sides.size(); ++i)
    qtot += sides[i]->qtot();

  fx.resize(qtot); fy.resize(qtot);

  dVector pfx, pfy, gu;
  qtot = 0;

  for (size_t i=0; i<sides.size(); ++i) {
    const Ordinal qsid = sides[i]->qtot();
    // Temporary storage for the gradient of the solution
    gu.resize(F->el[sides[i]->leid()]->qtot);

    // Compute the spatial gradient of the field and then
    // use fill_sides to put it on side gaussian points.
    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'x');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfx.alias(fx,qtot,qsid);
    pfx = sides[i]->u;

    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'y');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfy.alias(fy,qtot,qsid);
    pfy = sides[i]->u;

    qtot += qsid;
  }
}

// This is done without using the jump savy gradient
void BndryStats::get_solution_gradient(dVector &fx, dVector &fy, dVector &fz) {
  // cout << "BndryStats::get_solution_gradient()" << endl;
  if (!valid) return;
  int qtot=0;
  for (size_t i=0; i<sides.size(); ++i)
    qtot += sides[i]->qtot();

  fx.resize(qtot); fy.resize(qtot); fz.resize(qtot);

  dVector pfx, pfy, pfz, gu;
  qtot = 0;

  for (size_t i=0; i<sides.size(); ++i) {
    const Ordinal qsid = sides[i]->qtot();
    // Temporary storage for the gradient of the solution
    gu.resize(F->el[sides[i]->leid()]->qtot);

    // Compute the spatial gradient of the field and then
    // use fill_sides to put it on side gaussian points.
    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'x');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfx.alias(fx,qtot,qsid);
    pfx = sides[i]->u;

    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'y');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfy.alias(fy,qtot,qsid);
    pfy = sides[i]->u;

    F->el[sides[i]->leid()]->gradient(F->el[sides[i]->leid()]->u,gu,'z');
    F->el[sides[i]->leid()]->fill_sides(gu);
    pfz.alias(fz,qtot,qsid);
    pfz = sides[i]->u;

    qtot += qsid;
  }
}

void BndryStats::compute(dVector &x, dVector &y, dVector &u) {
  // cout << "BndryStats::compute()" << endl;
  if (!valid) return;
  dVector z;
  get_coordinates( x, y, z );
  get_solution( u );
}

// Integrate the Field over the sides.
Scalar BndryStats::integrate(const Field* fin) {
  if (!valid) return 0.0;
  Scalar I = 0.0;
  for(size_t i=0; i<sides.size(); i++){
    Element *elem = fin->el[sides[i]->leid()];
    Ordinal sid = sides[i]->id();
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f(qsid);
    for (Ordinal q=0; q<qsid; q++) f[q] = elem->side[sid]->u[q];
    I += elem->compute_side_integral(f, sid);
  }
  return I;
}

// Area over the sides.
Scalar BndryStats::area() {
  if (!valid) return 0.0;
  Scalar A = 0.0;
  for(size_t i=0; i<sides.size(); i++){
    Element *elem = F->el[sides[i]->leid()];
    Ordinal sid = sides[i]->id();
    A += elem->side[sid]->measure();
  }
  return A;
}

// Average the Field over the sides.
Scalar BndryStats::average(const Field* fin) {
  if (!valid) return 0.0;
  return integrate(fin)/area();
}

// For Euler computations
Scalar BndryStats::liftcalc(const dVector &p) {
  // cout << "BndryStats::liftcalc(dVector &p)" << endl;
  if (!valid) return 0.0;
  Scalar lift = 0.0;
  int qstart = 0;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f(qsid);
    for (Ordinal q=0; q<qsid; q++) f[q] = p[qstart+q] * sides[i]->ny(q);
    lift += F->el[sides[i]->leid()]->compute_side_integral( f, sides[i]->id() );
    qstart += qsid;
  }
  return lift;
}

// For Euler computations
Scalar BndryStats::dragcalc(const dVector &p) {
  // cout << "BndryStats::dragcalc(dVector &p)" << endl;
  if (!valid) return 0.0;
  Scalar drag = 0.0;
  int qstart = 0;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f(qsid);
    for (Ordinal q=0; q<qsid; q++) f[q] = p[qstart+q] * sides[i]->nx(q);
    drag += F->el[sides[i]->leid()]->compute_side_integral( f, sides[i]->id() );
    qstart += qsid;
  }
  return drag;
}

// For Navier-Stokes computations
Scalar BndryStats::liftcalc(const dVector &p,const dVector &tau12,
                            const dVector &tau22) {
  // cout << "BndryStats::liftcalc(dVector &p)" << endl;
  if (!valid) return 0.0;
  Scalar lift = 0.0;
  int qstart = 0;
  Scalar nx, ny;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f(qsid);
    for (Ordinal q=0; q<qsid; q++) {
      nx = sides[i]->nx(q);
      ny = sides[i]->ny(q);
      f[q]  = p[qstart+q] * ny;  // Pressure drag
      f[q] -= nx * tau12[qstart+q] + ny * tau22[qstart+q]; // Viscous drag
    }
    lift += F->el[sides[i]->leid()]->compute_side_integral( f, sides[i]->id() );
    qstart += qsid;
  }
  return lift;
}


// For Navier-Stokes computations
Scalar BndryStats::dragcalc(const dVector &p,const dVector &tau11,
                            const dVector &tau12) {
  // cout << "BndryStats::dragcalc(dVector &p)" << endl;
  if (!valid) return 0.0;
  Scalar drag = 0.0;
  int qstart = 0;
  Scalar nx, ny;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f(qsid);
    for (Ordinal q=0; q<qsid; q++) {
      nx = sides[i]->nx(q);
      ny = sides[i]->ny(q);
      f[q]  =  nx * p[qstart+q]; // Pressure drag
      f[q] -=  nx * tau11[qstart+q] + ny * tau12[qstart+q]; // Viscous drag
    }
    drag += F->el[sides[i]->leid()]->compute_side_integral( f, sides[i]->id() );
    qstart += qsid;
  }
  return drag;
}


// For Multi_Mat_Adv_Diff computations
Scalar BndryStats::flux_boundary_integral(const dVector &fx_all_sides) {
  // cout << "BndryStats::flux_boundary_integral(dVector &f_all_sides)"
  //<< endl;
  if (!valid) return 0.0;
  Scalar flux = 0.0;
  int qstart = 0;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f_one_side(qsid);
    for (Ordinal q=0; q<qsid; q++) {
      const Scalar nx = sides[i]->nx(q);
      f_one_side[q] = nx * fx_all_sides[qstart+q];
    }
    flux += F->el[sides[i]->leid()]->compute_side_integral( f_one_side,
                                                           sides[i]->id() );
    qstart += qsid;
  }
  return flux;
}

// For Multi_Mat_Adv_Diff computations
Scalar BndryStats::flux_boundary_integral(const dVector &fx_all_sides,
                                          const dVector &fy_all_sides) {
  // cout << "BndryStats::flux_boundary_integral(dVector &f_all_sides)"
  // << endl;
  if (!valid) return 0.0;
  Scalar flux = 0.0;
  int qstart = 0;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f_one_side(qsid);
    for (Ordinal q=0; q<qsid; q++) {
      const Scalar nx = sides[i]->nx(q);
      const Scalar ny = sides[i]->ny(q);
      f_one_side[q] = nx * fx_all_sides[qstart+q] + ny * fy_all_sides[qstart+q];
    }
    flux += F->el[sides[i]->leid()]->compute_side_integral( f_one_side,
                                                            sides[i]->id() );
    qstart += qsid;
  }
  return flux;
}

// For Multi_Mat_Adv_Diff computations
Scalar BndryStats::flux_boundary_integral(const dVector &fx_all_sides,
                                          const dVector &fy_all_sides,
                                          const dVector &fz_all_sides) {
  // cout << "BndryStats::flux_boundary_integral(dVector &f_all_sides)"
  // << endl;
  if (!valid) return 0.0;
  Scalar flux = 0.0;
  Ordinal qstart = 0;
  for(size_t i=0; i<sides.size(); i++){
    const Ordinal qsid = sides[i]->qtot();   // number of Gauss points on side
    dVector f_one_side(qsid);
    for (Ordinal q=0; q<qsid; q++) {
      const Scalar nx = sides[i]->nx(q);
      const Scalar ny = sides[i]->ny(q);
      const Scalar nz = sides[i]->nz(q);
      f_one_side[q] = nx * fx_all_sides[qstart+q]
        + ny * fy_all_sides[qstart+q]
        + nz * fz_all_sides[qstart+q];
    }
    flux += F->el[sides[i]->leid()]->compute_side_integral( f_one_side,
                                                            sides[i]->id() );
    qstart += qsid;
  }
  return flux;
}

void BndryStats::gather(dVector &x, dVector &y, dVector &z, dVector &u,
                        const Mesh mesh) {
#ifdef DGM_PARALLEL
  Ordinal lsize = size();        // local number of qpts
  Ordinal len = sides.size();    // local number of bndry_sides
  Ordinal np  = comm->NumProc(); // number of processors

  dVector lx, ly, lz, lu;
  get_coordinates(lx,ly,lz,mesh);
  get_solution(lu,mesh);

  intVector rcounts(np), displs(np);
  intVector rcnts(np), dspls(np);

  Ordinal glen, gsize;
  comm->SumAll(&len, &glen, 1);     // global number of bndry_sides
  comm->SumAll(&lsize, &gsize, 1);  // global number of bndry_qpts

  //cout<<comm->MyPID()<<": Global bndry sides = "<<glen<<endl;
  //cout<<comm->MyPID()<<": Global bndry size = "<<gsize<<endl;

  {
    const int i = len;
    const int j = lsize;
    comm->GatherAll(&i, rcounts.data(), 1); // sides
    comm->GatherAll(&j, rcnts.data(),   1); // qpts
  }
  for(Ordinal i=0;i<np;i++) {
    displs[i] = 0;
    dspls[i] = 0;
    for(Ordinal j=0;j<i;j++) {
      displs[i] += rcounts[j];
      dspls[i] += rcnts[j];
    }
  }
#ifdef DGM_VERBOSE_BNDRY_STATS
  if (comm->Master()) {
    cout<<"glen = "<<glen<<endl;
    for(Ordinal i=0; i<np; i++) {
      cout<<"Proc = "<<i<<", rcount = "<<rcounts[i]
          <<", displs = "<<displs[i]<<endl;
    }
    cout<<"gsize = "<<gsize<<endl;
    for (Ordinal i=0; i<np; i++) {
      cout<<"Proc = "<<i<<", rcnts = "<<rcnts[i]
          <<", dspls = "<<dspls[i]<<endl;
    }
  }
#endif
  iVector local_len(len), local_bid(len), local_pid(len);
  iVector global_bid(glen), global_pid(glen), part_bid(glen);
  iVector global_disp(glen), global_len(glen);

  for (Ordinal i=0; i<len; i++) {
    local_len[i] = sides[i]->qtot();
    local_bid[i] = sorder[i];
    local_pid[i] = comm->MyPID();
  }
  comm->GatherAll(local_len, len, global_len, rcounts, displs);
  comm->GatherAll(local_bid, len, global_bid, rcounts, displs);
  comm->GatherAll(local_pid, len, global_pid, rcounts, displs);

  for(Ordinal i=0; i<glen; i++) part_bid[global_bid[i]] = i;

  global_disp[0] = 0;
  for (Ordinal i=1; i<glen; i++)
    global_disp[i] = global_disp[i-1] + global_len[i-1];
#ifdef DGM_VERBOSE_BNDRY_STATS
  comm->Barrier();
  if (comm->Master()) {
    cout<<"Loop over sides stored in partition order..."<<endl;
    for(Ordinal i=0; i<glen; i++) {
      cout<<"part_bid = "<<i<<", bid = "<<global_bid[i]
          <<", proc = "<<global_pid[i]<<endl;
    }
    cout<<"Loop over sides in bndry order..."<<endl;
    for(Ordinal i=0; i<glen; i++) {
      cout<<"bid = "<<i<<", part_bid = "<<part_bid[i]
          <<", proc = "<<global_pid[part_bid[i]]
          <<", qtot = "<<global_len[part_bid[i]]
          <<", global_disp = "<<global_disp[part_bid[i]]<<endl;
    }
  }
#endif
  // Gather all to partition order (must unscramble on output)
  x.resize(gsize), y.resize(gsize), z.resize(gsize), u.resize(gsize);
  dVector tx(gsize), ty(gsize), tz(gsize), tu(gsize);
  comm->GatherAll(lx, lx.size(), tx, rcnts, dspls);
  comm->GatherAll(ly, ly.size(), ty, rcnts, dspls);
  comm->GatherAll(lz, lz.size(), tz, rcnts, dspls);
  comm->GatherAll(lu, lu.size(), tu, rcnts, dspls);
  // unscramble the data
  Ordinal i, j(0);
  for (Ordinal s=0; s<glen; s++) {
    for (Ordinal q=0; q<global_len[part_bid[s]]; q++) {
      i = global_disp[part_bid[s]]+q;
      x[j] = tx[i];
      y[j] = ty[i];
      z[j] = tz[i];
      u[j] = tu[i];
      j++;
    }
  }
#else
  get_coordinates(x,y,z,mesh);
  get_solution(u,mesh);
#endif
}

} // namespace DGM

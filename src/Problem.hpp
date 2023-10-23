#ifndef DGM_PROBLEM_HPP
#define DGM_PROBLEM_HPP

/** \file Problem.hpp
    \brief Abstract Problem class declaration

    Problem hold the computational Domain and provides both solve and plot
    methods for forward solvers
*/

// standard libraries
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

// DTK includes
#include "DTK.hpp"

// DGM libraries
#include "Comm.hpp"
#include "ArgList.hpp"
#include "Table.hpp"
#include "Domain.hpp"
#include "WeightsDatabase.hpp"

namespace DGM {

/// Abstract DGM Problem definition
/** Problem determines run parameters and sets up a problem on a domain.  This
    class plays the role of a "virtual constructor" in that it holds a generic
    domain, but derived classes construct specific Domains depending on
    prescribed parameters. */
class Problem : public DTK::Problem {

 protected:

  const DGM::Comm::Ptr comm;     ///< Parallel communicator for this Problem

 public:

  std::string code;              ///< Name of executable
  std::string root;              ///< Root file name for run
  Table &params;                 ///< Input parameters

  Domain *Omega;                 ///< Space-time domain

  std::vector<Domain*> vOmega;   ///< Space-time multi-domain physics

  /// Constructor
  Problem( DGM::ArgList &args, Table &table,
           const DGM::Comm::Ptr comm_ = DGM::Comm::World ) :
    comm(comm_), params(table), Omega(NULL) { }

  /// Destructor
  virtual ~Problem() {
    if (comm->verbosity()) comm->cout() << "~DGM::Problem()" << endl;
    if (Omega) delete Omega;
  }

  /// Extract arguments for this Problem
  virtual void parse_args( DGM::ArgList &args ) = 0;

  /// Show the commandline usage for this Problem
  virtual void showUsage(const string &code) const = 0;

  /// Return the communicator
  const DGM::Comm::Ptr get_comm() const {return comm;}

  /// Primary solve method
  virtual inline int solve() { return Omega->solve(); }

  /// Plot the solution
  virtual inline int plot(const string &rst) { return Omega->plot(rst); }

  /// Computer the difference and norms for two solutions
  virtual inline int diff(const string &rst1, const string &rst2,
                          const Scalar aeps, const Scalar reps,
                          const Scalar meps) {
    return Omega->diff(rst1,rst2,aeps,reps,meps);
  }

  /// This method must be implemented in derived problems 
  virtual void physics_names(std::vector<std::string>& p) const = 0;

  /// Update database timing data
  void update_timings(std::string product, unsigned numeqn, int p) {
    using std::string;
    using std::vector;
    // get verbosity from domain
    int verb = Omega->verbosity();
    // get representative element to get curvature, porder and Etype
    Element *element = Omega->U[0]->el[0];
    Topology::ElementType e = Topology::Line;
    bool curve = false;
    Ordinal porder = 0;
    element->get_weight_props(e, curve, porder);

    // get default location of weight file
    string tpl_dir = "./";
    string product_uc = DGM::upperCase(product);
    product_uc += "_HOME";
    const char *tmp = getenv(product_uc.c_str());
    if (tmp != NULL) tpl_dir = tmp;
    if (tpl_dir.empty()) {
      throw DGM::exception(product + " must be set for timing tests.");
    }
    if (0 < verb)
      comm->cout() << product_uc << "=" << tpl_dir << endl;
    struct stat buf;
    Size gne = Omega->partition->gne(); // cpu cost per element
    Scalar cpu = Omega->get_avg_cpu_per_step() / gne;
    string dirpath = tpl_dir;
    // check if directory exists
    int rc = stat(dirpath.c_str(), &buf);
    if (!rc && (buf.st_mode & S_IFDIR) && (buf.st_mode & S_IWUSR) ) {
      // check if performance directory exists
      dirpath += "/performance";
      if (0 < verb)
        comm->cout()<<"Checking on directory "<<dirpath<<endl;
      rc = stat(dirpath.c_str(), &buf);
      if (!rc && (buf.st_mode & S_IFDIR) && (buf.st_mode & S_IWUSR)) {
        // check if weight file exists
        dirpath += "/";
        dirpath += product;
        dirpath += "_weights.txt";
        rc = stat(dirpath.c_str(), &buf);
        if (!rc && (buf.st_mode & S_IFREG) && (buf.st_mode & S_IWUSR)) {
          if (0 < verb)
            comm->cout()<<"Directory path "+dirpath+" exists."<<endl;
          // update this database with just completed problem
          DGM::WeightsDatabase db(dirpath.c_str(), numeqn, p);
          // need cpu time (seconds) per step, not total cpu
          db.add_weight(e, curve, porder, cpu);
          db.write(dirpath.c_str());
          if (0 < verb)
            comm->cout()<<"Completed update of weights database."<<endl;
        } else {
          if (0 < verb)
            comm->cout()<<"File: "<<dirpath<<" doesn't exist, creating"<<endl;
          // create weight database and update this entry
          // pass in creation date/time, machine and
          // list of physics and element names for use in
          // documenting the file in semi-human readable form
          vector<string> p_names;
          vector<string> e_names;
          physics_names(p_names);
          DGM::Topology::names(e_names);
          DGM::WeightsDatabase db(numeqn, p, p_names, e_names);
          db.add_weight(e, curve, porder, cpu);
          db.write(dirpath.c_str());
          if (0 < verb)
            comm->cout()<<"Completed update of weights database."<<endl;
        }
      } else {
        // file creation mode to 755
        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
        if (0 < verb)
          comm->cout()<<"Making directory "<<dirpath<<endl;
        // create tpl_dir/performance
        if (mkdir(dirpath.c_str(), mode))
          throw DGM::exception("Could not make directory "+dirpath);
        // create weight database and update this entry
        // pass in creation date/time, machine and
        // list of physics and element names for use in
        // documenting the file in semi-human readable form
        vector<string> p_names;
        vector<string> e_names;
        physics_names(p_names);
        DGM::Topology::names(e_names);
        DGM::WeightsDatabase db(numeqn, p, p_names, e_names);
        db.add_weight(e, curve, porder, cpu);
        // write physics, element, curvature, p order
        dirpath += "/";
        dirpath += product;
        dirpath += "_weights.txt";
        db.write(dirpath.c_str());
        if (0 < verb)
          comm->cout()<<"Completed update of weights database."<<endl;
      }
    } else {
      perror("stat() failed");
      throw DGM::exception("Directory "+tpl_dir+" must already exist");
    }
  }

};

// The following code if for testing the Python interface
#ifdef DGM_TEST_PYTHON_INTERFACE
  class Rectangle {
  public:
    int x0, y0, x1, y1;
    Rectangle(int X0, int Y0, int X1, int Y1) {
      using std::cout;
      using std::endl;
      x0 = X0;
      y0 = Y0;
      x1 = X1;
      y1 = Y1;
      cout << "Rectangle::Rectangle(...)" << endl;
      cout << "  x0 = " << x0 << endl;
      cout << "  y0 = " << y0 << endl;
      cout << "  x1 = " << x1 << endl;
      cout << "  y1 = " << y1 << endl;
    }
    ~Rectangle() {
      using std::cout;
      using std::endl;
      cout << "Rectangle::~Rectangle()" << endl;
    }
    int getLength() {
      return (x1 - x0);
    }
    int getHeight() {
      return (y1 - y0);
    }
    int getArea() {
      return (x1 - x0) * (y1 - y0);
    }
    void move(int dx, int dy){
      x0 += dx;
      y0 += dy;
      x1 += dx;
      y1 += dy;
    }
  };

  class Foo {
  public:
    Foo( int num ) {
      cout << "Foo::Foo(int)" << endl;
      //cout << "  num = " << num << endl;
      //cout << "  &num = " << &num << endl;
      //cout << "Finished Foo" << endl;
      //cout.flush();
    }
    Foo( ArgList *args ) {
      using std::cout;
      using std::endl;
      cout << "Foo::Foo(ArgList *)" << endl;
      //cout << "  &args = " << args << endl;
      cout << "  args->size() = " << args->size() << endl;
      cout << "Finished Foo" << endl;
    }
    Foo( ArgList &args ) {
      cout << "Foo::Foo(ArgList &)" << endl;
      //cout << "  &args = " << &args << endl;
      //cout << "  args.size() = " << args.size() << endl;
      //cout << "Finished Foo" << endl;
    }
    ~Foo() { std::cout << "Destroying Foo" << std::endl; }
  };

  class Goo {
  public:
    Goo( Rectangle *rect ) {
      using std::cout;
      using std::endl;
      cout << "Goo::Goo(Rectangle *)" << endl;
      cout << "  rect = " << rect << endl;
      cout << "  length = " << rect->getLength() << endl;
      cout << "  height = " << rect->getHeight() << endl;
      cout << "Finished Goo" << endl;
    }
    Goo( Rectangle &rect ) {
      using std::cout;
      using std::endl;
      cout << "Goo::Goo(Rectangle &)" << endl;
      cout << "  &rect = " << &rect << endl;
      cout << "  length = " << rect.getLength() << endl;
      cout << "  height = " << rect.getHeight() << endl;
      cout << "Finished Goo" << endl;
    }
    Goo( int num ) {
      using std::cout;
      using std::endl;
      cout << "Goo::Goo(int)" << endl;
      cout << "  num = " << num << endl;
      cout << "  &num = " << &num << endl;
      cout << "Finished Goo" << endl;
    }
    ~Goo() { std::cout << "Destroying Goo" << std::endl; }
  };
  // End of Python interface test
#endif

} // namespace DGM

#endif  // DGM_PROBLEM_HPP

/** \file  IC.hpp
    \brief Initial Condition classes
    \author Scott Collis
*/

#ifndef DGM_IC_HPP
#define DGM_IC_HPP

namespace DGM {

/// Base class for DGM initial conditions
class IC {
public:
  typedef DGM::Shared<IC>::Ptr Ptr;

  typedef map<string,Ptr> db_type;          ///< database
  typedef db_type::iterator db_itr;         ///< database iterator
  typedef db_type::const_iterator db_citr;  ///< database const iterator
  
  typedef Size GlobalSize;
  typedef Ordinal LocalSize;

  IC() {}
  virtual ~IC() {}
  
  /// Returns a pointer to a Ctrl object
  virtual Ctrl* ctrl() { return 0; }
  
  /// Returns a constant pointer to a Ctrl object
  virtual const Ctrl* ctrl() const { return 0; }

  inline static Ptr factory(const string &fname, Domain &omega, vField &F);
  inline static Ptr factory(Json::Value &root, Domain &omega, vField &F);
};

/// Prescribed initial condition
class Given : public IC {
  const DGM::Comm::Ptr comm;
  const int verb;
public:
  Given(Json::Value &root, vField &F) :
    comm(F.get_comm()),
    verb(root.set("Verbosity",0).asInt())
  {
    for (vField::LocalSize i=0; i<F.size(); ++i) {
      if (verb) comm->cout()<<"Parsing expression for "<<F[i]->get_name()<<endl;
      if (!root.isMember(F[i]->get_name()))
        comm->error("Unable to find expression for Field "+F[i]->get_name());
      const string buffer = root[F[i]->get_name()].asString() + '\n';
      if (verb) comm->cout()<<"  Filling with "<<buffer;
      for (vField::LocalSize e=0; e<F[i]->ne; e++) F[i]->el[e]->fill(buffer);
    }
  }
  Given(ifstream &in, vField &F) : comm(F.get_comm()), verb(0) {
    F.fill(in);
  }
  virtual ~Given() {}
};

/// Initial condition is specified as a restart
class Restart : public IC {
  const DGM::Comm::Ptr comm;
  const int verb;
public:
  Restart(Json::Value &root, Domain &omega, vField &F) :
    comm(F.get_comm()),
    verb(root.set("Verbosity",0).asInt())
  {
    if (!root.isMember("Filename"))
      comm->error("Restart must specify Filename");
    const string filename = root["Filename"].asString();
    if (verb) comm->cout()<<"Restarting from: " << filename << endl;
    omega.read(filename,F);
  }
  Restart(ifstream &in, Domain &omega, vField &F) :
    comm(F.get_comm()), verb(0)
  {
    string rstfile;
    const DGM::Comm::Ptr comm = F.get_comm();
    if (!(in>>rstfile)) {
      comm->cerr() << "IC: Cannot read restart file name from " << endl;
      comm->exit(DGM::FAILURE);
    }
    omega.read(rstfile, F);
    comm->cout() << "Restarting from: " << rstfile << endl;
  }
  virtual ~Restart() {}
};

/// This is the new IC Json format
IC::Ptr IC::factory(Json::Value &root, Domain &omega, vField &F) {
  const DGM::Comm::Ptr comm = F.get_comm();
  IC::Ptr result;
  if (!root.isMember("Type"))
    comm->error("Initial condition Type is missing");
  const string type = root["Type"].asString();
  if (lowerCase(type)=="given")
    result.reset(new Given(root,F));
  else if (lowerCase(type)=="restart")
    result.reset(new Restart(root,omega,F));
  else
    comm->error("DGM::IC::Factory() Unsupported IC type");
  // determine whether to project the initial condition to the DG space
  bool projectIC = root.set("Project",false).asBool();
  if (!projectIC) {
    comm->cout() << "WARNING:  No projection of Initial condition" << endl;
    for (vField::LocalSize i=0; i<F.size(); i++)
      for (vField::LocalSize e=0; e<F[i]->ne; e++)
        F[i]->el[e]->state = Element::Physical;
  } else {
    comm->cout() << "Projecting initial condition to DG space" << endl;
    project(F);
  }
  return result;
}

/// This is the old type of IC file format
IC::Ptr IC::factory(const string &fname, Domain &omega, vField &F) {
  const int verb = 1;
  IC::Ptr result;
  ifstream in(fname.c_str());
  const DGM::Comm::Ptr comm = F.get_comm();
  if (!in) {
    comm->cerr() << "DGM::IC Could not open initial condition file "
                 << fname << endl;
    comm->exit(DGM::FAILURE);
  }
  string buffer, code;
  getline(in,buffer);
  if (!(in>>code)) error("Cannot read IC code");
  getline(in,buffer);
  if (verb) cout << "IC code = " << code << endl;
  if (lowerCase(code) == "given") {
    result.reset(new Given(in,F));
  } else if (lowerCase(code) == "restart") {
    result.reset(new Restart(in,omega,F));
  } else {
    comm->error("DGM::IC::Factory() Unsupported IC type");
  }
#define DGM_NO_PROJECT_IC
#ifdef DGM_NO_PROJECT_IC
  comm->cout() << "WARNING:  No projection of Initial condition" << endl;
  for (vField::LocalSize i=0; i<F.size(); i++)
    for (vField::LocalSize e=0; e<F[i]->ne; e++)
      F[i]->el[e]->state = Element::Physical;
#else
  comm->cout() << "Projecting initial condition to DG space" << endl;
  project( F );
#endif
#undef DGM_NO_PROJECT_IC
  return result;
}

}

#endif /* DGM_IC_HPP */

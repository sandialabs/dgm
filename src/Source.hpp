#ifndef DGM_SOURCE_HPP
#define DGM_SOURCE_HPP

/** \file Source.hpp
    \brief DGM Source base class declaration
    \author Scott Collis
*/

// System includes
#include <map>
#include <string>
#include <vector>
using namespace std;

// DTK includes
#include "DTK.hpp"

// DGM includes
#include "Types.hpp"
#include "vField.hpp"

namespace DGM {

// forward declarations
class Ctrl;
class Obs;

/// Abstraction of a Model
class Model : public DTK::Model<vField,dVector,Scalar,Ordinal> {
public:
  virtual ~Model() {}
};

/// Abstraction of a Source term
class Source : public DTK::Source<vField,dVector,Scalar,Ordinal,Ctrl,Obs> {

 public:

  typedef DGM::Shared<Source>::Ptr Ptr;     ///< shared pointer to Source
  typedef map<string,Ptr> db_type;          ///< source database
  typedef db_type::iterator db_itr;         ///< source database iterator
  typedef db_type::const_iterator db_citr;  ///< source database const iterator

  typedef Size GlobalSize;
  typedef Ordinal LocalSize;

  enum SrcType { SOURCE, SPONGE, OTHER };
  SrcType srctype;

  /// Constructors
  Source(const std::string t, const SrcType s=SOURCE) :
    DTK::Source<vField,dVector,Scalar,Ordinal,Ctrl,Obs>(t), srctype(s) {}

  /// Destructor
  virtual ~Source() {}

  /// State apply method
  virtual void apply( const Scalar, const vField &, vField &) = 0;

  /// Adjoint apply method
  virtual void adjoint_apply( const Scalar, const vField &, const vField &,
                              vField & ) = 0;

  /// Provides a modifyable reset method, default is null-op
  virtual void reset_source(const dVector &data) {}

  /// Return the number of sources
  /** Normally the number of sources is 1 as there would be one source for
      each Source object that is instantiated.  However, it is also useful to
      have each Source object represent a collection of similar sources and in
      this case, this method should return the number of sources in, for
      example, an array of similar sources. */
  virtual Ordinal Nsources() const { return 1; }

  /// Returns a pointer to a Ctrl object
  virtual Ctrl* ctrl() { return 0; }

  /// Returns a constant pointer to a Ctrl object
  virtual const Ctrl* ctrl() const { return 0; }

  /// Returns a pointer to an Obs object (if applicable)
  virtual Obs* obs() { return 0; }

  /// Returns a constant pointer to an Obs object (if applicable)
  virtual const Obs* obs() const { return 0; }

protected:

  /// Source error handler
  static void error(string msg, int code=-1) {
    DGM::Comm::World->error(msg,code);
  }

  /// Scan for a left curly bracket
  static void scan_lb(ifstream &in ) {
    string token;
    if (!(in >> token)) error("Cannot read Source left bracket");
    if ( token != "{" )
      error("Source syntax error:  Expected a \"{\"");
  }

  /// Scan for a right curly bracket
  static void scan_rb(ifstream &in ) {
    string token;
    while (token != "}" )
      if (!(in >> token)) error("Source syntax error:  Cannot find \"}\"");
  }
};

/// Default constant Source class
class ConstSource : public Source {
  dVector values;
 public:
  ConstSource(const string &t, dVector &v) : Source(t) {
    cout << "ConstSource(const, string, dVector &)" << endl;
    values.resize( v.size() );
    values = v;
  }
  ConstSource(const string &t, ifstream &in, Ordinal ndof=0) : Source(t) {
    // cout << "ConstSource(infstream &)" << endl;
    scan_lb(in);
    if (ndof==0) // normally we do not read this from the file
      if (!(in >> ndof)) error("ConstSource::Cannot read ndof");
    values.resize(ndof);
    for (Ordinal n=0; n<ndof; n++)
      if (!(in >> values[n])) error("ConstSource::Cannot read values");
    scan_rb(in);
  }
  ConstSource(const string &t, const Json::Value &json) : Source(t) {
    if (!json.isMember("Values")) 
      DGM::Comm::World->error("Source::ConstSource: "
                  "'Values' is not defined in constant type source.");
    const Json::Value V = json["Values"];
    if  (!V.isArray())
      DGM::Comm::World->error("Source::ConstSource: "
                  "'Values' is not an ARRAY of source blocks "
                  " (in square brackets).");
    const Ordinal N = numeric_cast<Ordinal>(V.size());
    if (!N)
     DGM::Comm::World->error("Source::ConstSource: "
                             "'Values' is a zero length array.");
    values.resize(N);
    for (Ordinal i = 0; i < N; ++i ) values[i] = V[i].asDouble();
  }
  void apply( const Scalar, const vField &, vField &F ) {
    assert( F.size() == static_cast<vField::size_type>(values.size()) );
    for (vField::size_type i=0; i<F.size(); i++) subtract( values[i], F[i] );
  }
  void adjoint_apply( const Scalar, const vField &, const vField &,
                      vField & ) {}
};

/// Builds a Source from a file
class FileSource : public Source {
  dVector values;
  vField S;
  string filename;
 public:
  /// constructor
  FileSource(const string &t, ifstream &in, const vField &F) : 
    Source(t), S(F.get_comm(),"FileSource::S") 
  {
    cout << "FileSource(const, string, dVector &)" << endl;
    for (vField::size_type i=0; i<F.size(); i++) {
      S.push_back( new Field(F[i]) );
    }
    scan_lb(in);
    if (!(in >> filename ))
      error("FileSource::FileSource::Cannot read filename.");
    scan_rb(in);
    cout << "  reading from " << filename << endl;
    S.read(filename);
    cout<<"Source "<<t<<" norm"<<endl;
    S.norm();
  }
  FileSource(const string &t, const Json::Value &json) : 
    Source(t), S(DGM::Comm::World,"FileSource::S") {
    DGM_UNDEFINED;  
  }
  void apply( const Scalar, const vField &, vField &F ) {
    assert( F.size() == S.size() );
    for (vField::size_type i=0; i<F.size(); i++) subtract( S[i], F[i] );
  }
  void adjoint_apply( const Scalar, const vField &, const vField &,
                      vField & ) {}
};

/// Default function Source class (now works in multidimensions)
/** Uses the inline parser and combines lines with continuation character "\" 
 **/
class FuncSource : public Source {
  vector<string> expr;  ///< the expressions for each Field component
  dVector s;            ///< storage for the values
 public:
  /// Constructor
  FuncSource(const string &t, ifstream &in, Ordinal ndof=0,
             const bool initOnce=true) : Source(t), initializeOnce(initOnce) {
    string buffer;
    //cout << "FuncSource(ifstream &)" << endl;
    scan_lb(in);
    if (ndof==0)  // normally we do not read this from the file
      if (!(in >> ndof)) error("FuncSource::Cannot read ndof");
    expr.resize(ndof);
    getline(in,buffer);  // get blank line
    for (Ordinal n=0; n<ndof; n++) {
      getline(in,buffer);
      //expr[n] = buffer + '\n';   // parser needs a newline
      expr[n] = buffer;
      string::size_type loc = expr[n].find(":=");
      if  (loc == std::string::npos) {
        stringstream msg;
        msg<<"FuncSource("<<t<<"):  Did not find := required for inline "
             "parser for field index "<<n;
        throw DGM::exception(msg.str());
      }
      // Move to the point right after the := token
      loc += 2;
      //cout << "dof = " << n << ", expression = " << expr[n] << endl;
      //expr[n] = expr[n].substr(loc);
      expr[n].erase(expr[n].begin(),expr[n].begin()+loc);
      string::size_type cont = std::string::npos;
      while ( (cont=expr[n].find("\\")) != std::string::npos) {
        expr[n].erase(expr[n].begin()+cont,expr[n].end());
        getline(in,buffer);
        expr[n] += buffer;
      }
      //cout << "dof = " << n << ", expression = " << expr[n] << endl;
    }
    scan_rb(in);
  }
  FuncSource(const string &t, const Json::Value &json,
             const bool initOnce=true) : Source(t), initializeOnce(initOnce) {
    DGM_UNDEFINED;
  }
  /// Destructor
  virtual ~FuncSource() {
    //cout << "~FuncSource()" << endl;
  }
  void apply( const Scalar t, const vField &, vField &F );
  void adjoint_apply( const Scalar, const vField &, const vField &,
                      vField & ) {}
private:
  /// Evaluate the function expressions
  void evaluate(const vField &F, const Scalar t=0.0);
  const bool initializeOnce;
};

} // namespace DGM

#endif  // DGM_SOURCE_HPP

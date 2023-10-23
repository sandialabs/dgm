#ifndef DGM_PARSER_HPP
#define DGM_PARSER_HPP

/** \file  Parser.hpp
    \brief DGM inline parser
    \author S. Scott Collis

\verbatim
Notes:
1. Now you can have temporaries like:

rho(x,y) := a=2; a;

2. Note that all expressions MUST end in a semicolon so that this will be
an error

U(x,y) := a=3; a^2

since it doesn’t end in a semicolon.  I think that derived codes have always
used the trailing semicolon so that hopefully this isn’t an issue, but 
there were cases in the DGM test suite that I had to fix.

3. You can now do continuation of expressions to subsequent lines using “\”

v(x,y,z) := a=1; b=a; cos(a*PI*x)* \
            cos(b*pi*y);

4. There currently is not a check to see whether a symbol has be previously
   defined and this is both useful but also can be an issue.  For example,
   The following is useful

w(x) := a=1; a=a+1; a*x;

but this might be confusing

w(x) := PI=1; cos(PI*x);

Even though PI is defined natively, you can currently override it.  This
would be easy to fix in a subsequent update but watch out for now.

5. Note that once you define a temporary, it is in scope for all subsequent
calls to the parser.  So, for example, say you have an initial condition like

R := rho=1; rho;
U := u=1; rho*u;
V := v=1; rho*v;
E := gamma=1.4; T=1; rho*((gamma-1)*T + 0.5*(u^2+v^2);

Gives the result you likely wanted.  However, say you now use the parser
for a different purpose (perhaps a boundary condition or source term) and 
do

f := rho;

Well, that rho is still defined and may not be what you wanted.  Likewise,
you cannot be certain that the initial condition was executed so that rho
is defined.  I will work to make temporaries local in scope in a subsequent
update.

6. Finally, the syntax with “symbol := expression” is required for old style
DGM parsing.  If the expression is part of a Json specification, then you
don’t need that and it just looks something like:

“Initial Condition” : {
  “Given” : [ “rho=1; rho;”, “u=1; rho*u;”, “v=1; rho*v”, 
              “gamma=1.4; T=1; rho*((gamma-1)*T + 0.5*(u^2+v^2);” ]
}

or something similar for Sources and BCs (see the Json specification for
more details).  The point is that the symbol := expression syntax is not
needed.

\endverbatim

*/

// System includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <csignal>
#include <map>
#include <cerrno>

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"
#include "Constants.hpp"

// CMC includes
#include "Quadpack.hpp"

// boost includes
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

/// redefine the yacc left value to make it unique
#define yylval dgm_yylval

/// redefine the main parser name to make it unique
#define yyparse dgm_yyparse

/// error number
//extern int errno;

// use C bindings for lex & yacc routines
extern "C" {
  /// main parser
  int  yyparse();
  /// error handler
  void yyerror(const char *);
  /// lexical response
  int  yylex();
  /// wraps multiple input files into one
  int  yywrap();
}

// forward declarations
void parser_init();
void parser_clean(const bool=false);

namespace DGM {

/// Inline parser used to evaluate short expressions within input files
namespace Parser {

  /// Entries for symbol table
  class Entry {
  public:
    /// function on one argument
    typedef double (*PFD)(double);
    /// function of two arguments
    typedef double (*PF2D)(double, double);
    /// function of three arguments
    typedef double (*PF3D)(double, double, double);
    /// function of four arguments
    typedef double (*PF4D)(double, double, double, double);

    int type;
    string name;
    double value;
    PFD unary;
    PF2D binary;
    PF3D trinary;
    PF4D quaternary;
    bool keyword;

    typedef DGM::Shared<Entry>::Ptr Ptr; ///< Entry pointer type

    // constructors
    Entry(string, bool=true);
    Entry(string, const double, bool=true);
    Entry(string, PFD);
    Entry(string, PF2D);
    Entry(string, PF3D);
    Entry(string, PF4D);
  };

  /// type of symbol table
  typedef std::map<string,Entry::Ptr> Table;

  /// Symbol table
  extern Table symtab;

  /// Symbol table iterator
  typedef Table::iterator SI;

  /// Symbol table constant iterator
  typedef Table::const_iterator CSI;

  /// Symbol table output method
  inline ostream& operator<<(ostream& os, const Table &table) {
    for (CSI n=table.begin(); n!=table.end(); ++n)
      os << n->first << "\t" << n->second->value << "\t" <<
        n->second->unary << "\t" <<
        n->second->binary << "\t" <<
        n->second->trinary << "\t" <<
        n->second->quaternary << endl;
    return os;
  }

  /// Evaluation stack
  extern double stack_value;

  /// Initialization flag
  extern bool already_init;

  /* --------------------------------------------------------------------- *
   *                      Function definitions                             *
   * --------------------------------------------------------------------- */

  /// Remove temporaries from symbol table
  inline void cleanup(Table &table, const bool verb=false) {
    std::vector<string> tmp;
    for (SI e=table.begin(); e!=table.end(); ++e) {
      if (!e->second->keyword) tmp.push_back(e->first);
    }
    for (std::vector<string>::size_type i=0; i<tmp.size(); ++i) {
      if (verb)
        std::cout<<"Parser removing temporary \""<<tmp[i]<<"\""<<std::endl;
      table.erase(tmp[i]);
    }
  }

  /// Generate an error message
  inline void execerrnr(const char *s, const char *t) {
    cerr << s << ", " << t << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }

  /// Error checking function
  inline double errcheck(const double d, const char *s) {
    if (errno == EDOM) {
      errno = 0;
      execerrnr(s, "argument out of domain");
    } else if (errno == ERANGE) {
      errno = 0;
      execerrnr(s, "result out of range");
    }
    return d;
  }

/// This uses a C++ wrapped version of Quadpack
#define DGM_USE_QUADPACK

/// Mollifier function class
/** Mollifier function class as defined by Barth & Larson NASA TR
    NAS-02-001 This class provides a simple function interface through
    operator() that allows one to repeatedly call the Mollifier function
    without incurring the penalty of evaluating the constant term (which
    requires a numerical integration.) */
class MollifierFunction {
  static double f (const double x, void *params) {
    double invr02 = *(double *)params;
    return x*exp(one/(x*x*invr02 - one));
  }
  size_t limit;
  double r0, factor, invr02;
  double abstol, reltol;
  struct Function {
    double invr02;
    Function(const double in) : invr02(in) {}
    double operator()(const double x) {
      return f(x,&invr02);
    }
  };
public:
  MollifierFunction( const double r0_, const bool tilde=false )
  : limit(1000), r0(r0_) {
    abstol=0.0; reltol=1.0e-8;
    invr02 = one/(r0*r0);
    Function func(invr02);
    CMC::Quadpack<Function,double>
      qp(func,abstol,reltol,numeric_cast<int>(limit));
    factor = one/(two*pi*qp.integrate(0.0,r0));
    if (tilde) factor = factor/((*this)(0.0));
    //cout<<"MollifierFunction("<<r0<<","<<tilde<<"): factor = "<<factor<<endl;
  }
  double operator()( const double r ) {
    if (r>=r0)
      return 0.0;
    else
      return factor*exp(one/(r*r*invr02 - one));
  }
};

/// Vector function evaluation class
class VectorFunction {
public:
  int nargs;          ///< number of arguments to this vector function
  string arg[4];      ///< arguments
  Entry::Ptr xyzt[4]; ///< pointers to the Entry
  string function;    ///< the string to evaluate

  ///< Types of operations supported by the evaluation interface
  enum Operation {
    Equal,
    Add,
    Subtract,
    Multiply,
    Divide
  };

  VectorFunction( string x, string t, string f) {
    nargs = 2;
    arg[0] = x;
    arg[1] = t;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x].reset( new Entry(x) );
    xyzt[0] = symtab[x];
    p = symtab.find(t);
    if ( p == symtab.end() )
      symtab[t].reset( new Entry(t) );
    xyzt[3] = symtab[t];
    function = f;
    //cout<<"Made new VectorFunction, "<<"f("<<x<<","<<t<<") = "<<f<<endl;
  };

  VectorFunction( string x, string y, string t, string f) {
    nargs = 3;
    arg[0] = x; arg[1] = y; arg[2] = t;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x].reset( new Entry(x) );
    xyzt[0] = symtab[x];
    p = symtab.find(y);
    if ( p == symtab.end() )
      symtab[y].reset( new Entry(y) );
    xyzt[1] = symtab[y];
    p = symtab.find(t);
    if ( p == symtab.end() )
      symtab[t].reset( new Entry(t) );
    xyzt[3] = symtab[t];
    function = f;
  };

  VectorFunction( string x, string y, string z, string t, string f) {
    nargs = 4;
    arg[0] = x; arg[1] = y; arg[2] = z; arg[3] = t;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x].reset( new Entry(x) );
    xyzt[0] = symtab[x];
    p = symtab.find(y);
    if ( p == symtab.end() )
      symtab[y].reset( new Entry(y) );
    xyzt[1] = symtab[y];
    p = symtab.find(z);
    if ( p == symtab.end() )
      symtab[z].reset( new Entry(z) );
    xyzt[2] = symtab[z];
    p = symtab.find(t);
    if ( p == symtab.end() )
      symtab[t].reset( new Entry(t) );
    xyzt[3] = symtab[t];
    function = f;
  };

  ~VectorFunction() {};

  void evaluate( dVector &x, dVector &f, const Scalar &t,
                 Operation operation=Equal );
  void evaluate( dVector &x, dVector &y, dVector &f, const Scalar &t,
                 Operation operation=Equal);
  void evaluate( dVector &x, dVector &y, dVector &z, dVector &f,
                 const Scalar &t, Operation operation=Equal);
};

/// \name Parser functions
//@{

/// natural logorithm
inline double Log(const double x) {
  return Parser::errcheck(log(x), "log");
}

/// base 10 logorithm
inline double Log10(const double x) {
  return Parser::errcheck(log10(x), "log10");
}

/// Gaussian distribution with peak of one
/** Gaussian(\f$x\f$,\f$\mu\f$,\f$\sigma\f$) where \f$\mu\f$ is the mean and
    \f$\sigma\f$ is the standard deviation and the peak is unity */
inline double Gaussian(const double x, const double mu, const double sigma) {
  // Gaussian's often lead to underflow for large aurguments so this version
  // limits the smallest value to be near machine zero
  const double limit = 34.0;
  double arg = pt5*pow((x-mu)/sigma,2);
  // Note that if you limit to underflow still happens
  return ( arg < limit ? exp(-arg) : 1.0e-15 );
}

/// Normal distribution
/** NormalDistribution(\f$x\f$,\f$\mu\f$,\f$\sigma\f$) where
    \f$\mu\f$ is the mean and \f$\sigma\f$ is the standard deviation */
inline double NormalDistribution(const double x, const double mu,
                                 const double sigma) {
  // Gaussian's often lead to underflow for large aurguments so this version
  // limits the smallest value to be near machine zero
  const double limit = 34.0;
  double arg = pt5*pow((x-mu)/sigma,2);
  double fact = one/(sigma*sqrt(two*pi));
  // Note that if you limit to underflow still happens
  return ( arg < limit ? fact*exp(-arg) : 1.0e-15 );
}

/// Exponential with possibility of error checking
inline double Exp(double x) {
  return exp(x);
  // return Parser::errcheck(exp(x), "exp");  // turn off errorcheck for now
}

/// Square root with possiblity of error checking
inline double Sqrt(const double x) {
  //return Parser::errcheck(sqrt(x), "sqrt");
  return sqrt(x);
}

/// Power function with error checking
inline double Pow(const double x, const double y) {
  const double yn = floor(y + 0.5);
  double px = 1.0;
  if (yn >= 0 && yn == y) {          // Do it inline if y is an integer power
    int n = (int) yn;
    while (n--)
      px *= x;
  } else
    px = Parser::errcheck(pow(x,y), "exponentiation");
  return px;
}

#if __cplusplus > 201402L

/// Hypotenuse function
inline double Hypot(const double x, const double y) {
  return std::hypot(x,y);
}

#endif  // C++17

/// Maximum of two values
inline double Max(const double a, const double b) {
  return std::max(a,b);
}

/// Minimum of two values
inline double Min(const double a, const double b) {
  return std::min(a,b);
}

/// Converts a double to an integer
inline double Integer(double x) {
  return (double) (long) x;
}

/// Generate a random double between [0,x), i.e. including 0 but not x
inline double Rand(const double x) {
#ifndef VCC
  return x*drand48();
#else
#ifdef DGM_PARSER_USE_RAND
  return x*(double)rand()/((double)(RAND_MAX)+(double)(1));
#else
  return x*(double)random()/((double)(RAND_MAX)+(double)(1));
#endif
#endif
}

/// Generate a bump function
/** Generate a bump function of the form:
    \f[
    f(x) = \left\{ \begin{array}{rl}
            -1 & \mbox{for $x \in \big[0,\frac{1}{8}\big)$}           \\[1ex]
             0 & \mbox{for $x \in \big[\frac{1}{8},\frac{1}{4}\big)$} \\[1ex]
            -1 & \mbox{for $x \in \big[\frac{1}{4},\frac{3}{8}\big)$} \\[1ex]
             0 & \mbox{for $x \in \big[\frac{3}{8},\frac{1}{2}\big]$}
           \end{array}
           \right. \f]
    Generates an error outside of the range \f$[0,0.5]\f$. */
inline double Bump(const double x) {
  if(x >= 0. && x < 0.125)
    return -1;
  if(x >= 0.125 && x < 0.25)
    return 0.;
  if(x >= 0.25 && x < 0.375)
    return 1.;
  if(x >= 0.375 && x <= 0.5)
    return 0.0;
  DGM::error("Parser::Bump outside range of [0.0,0.5]");
  return 0.0;
}

/// Computes sqrt(x^2+y^2)
inline double Radius(const double x, const double y) {
  if (x != 0.0 || y != 0.0)
    return sqrt(x*x + y*y);
  else
    return 0.0;
}

/// Bessel Function
inline double Jn(const double i, const double x) {
  return jn((int)i, x);
}

/// Bessel Function
inline double Yn(const double i, const double x) {
  return yn((int)i, x);
}

/// Error Function
inline double Erf(const double x) {
  return erf(x);
}

/// Complementary Error Function
inline double Erfc(const double x) {
  return erfc(x);
}

/// Computes ArcTan(y,x)
inline double Angle(const double x, const double y) {
  double theta = 0.;
  if ((x != 0.0)||(y != 0.0))
    theta = atan2(y,x);
  return theta;
}

/// Heaviside step function H(x-a) = 1 if x >= 0 else = 0
inline double Step(const double x, const double a) {
  double H = 1.0;
  if (x < a)
    H = 0.0;
  return H;
}

/// Generates a "shock wave" profile centered at x=0
inline double Shock(const double x, const double a, const double b) {
  if(x==0)
    return 0.5*(a+b);
  if(x>0)
    return b;
  if(x<0)
    return a;
  return 0;
}

/// Interface to the Mollifier function
/** Simple interface to the MollifierFunction for use by the parser.  This
    is a smart function in that it keeps a map of the Mollifier objects
    that have already been declared and it first checks the map to see is
    the particular Mollifier object has already been constructed and then
    simply calls it's function method. */
inline double Mollifier( const double r0, const double r ) {
  //cout << "Mollifier" << endl;
  typedef DGM::Shared<MollifierFunction>::Ptr MollifierPtr;
  typedef std::map<double,MollifierPtr>::iterator MI;
  static std::map<double,MollifierPtr> mollifier_map;
  MI p = mollifier_map.find(r0);
  MollifierPtr m;
  if ( p == mollifier_map.end() ) {
    m.reset( new MollifierFunction( r0, true ) );
    mollifier_map[r0] = m;
  } else {
    m = p->second;
  }
  return (*m)(r);
}

/// Generates Jacobi polynomials
/** Evaluates the \f$n^{th}\f$ order Jacobi polynomial
    \f$P^{(\alpha,\beta)}_{n}(z)\f$ for \f$\alpha > -1\f$ and \f$\beta > -1\f$
    at \f$z\f$. */
inline double Jacobi(const double z, const double n,
                     const double alpha, const double beta) {
  int    k;
  double one = 1.0;
  double a1,a2,a3,a4;
  double two = 2.0, apb = alpha + beta;
  double poly, polyn1, polyn2;

  poly   = 0.0;
  polyn2 = one;
  polyn1 = 0.5*(alpha - beta + (alpha + beta + 2)*z);

  for(k = 2; k <= n; ++k){
    a1 =  two*k*(k + apb)*(two*k + apb - two);
    a2 = (two*k + apb - one)*(alpha*alpha - beta*beta);
    a3 = (two*k + apb - two)*(two*k + apb - one)*(two*k + apb);
    a4 =  two*(k + alpha - one)*(k + beta - one)*(two*k + apb);

    a2 /= a1;
    a3 /= a1;
    a4 /= a1;

    poly   = (a2 + a3*z)*polyn1 - a4*polyn2;
    polyn2 = polyn1;
    polyn1 = poly  ;
  }
  return poly;
}

//@}

} // namespace Parser

} // namespace DGM

#endif  // DGM_PARSER_HPP

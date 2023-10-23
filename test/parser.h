#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <csignal>
#include <map>
#include <errno.h>

#include "../src/Types.h"

extern int errno;

// use C bindings for lex & yacc routines
extern "C" {
  int  yyparse();
  void yyerror(char *);
  int  yylex();
  int  yywrap();
}

typedef double (*PFD)(const double); 
typedef double (*PF2D)(const double, const double);
typedef double (*PF3D)(const double, const double, const double);
typedef double (*PF4D)(const double, const double, const double, const double);

// Entries for symbol table
class Entry {
public:
  int type;
  string name;
  double value;
  PFD unary;
  PF2D binary;
  PF3D trinary;
  PF4D quaternary;

  // constructors
  Entry(string);
  Entry(string,const double);
  Entry(string,PFD);
  Entry(string,PF2D);
  Entry(string,PF3D);
  Entry(string,PF4D);
};

// Symbol table
extern map<string,Entry*> symtab;

// Symbol table iterators
typedef map<string,Entry*>::iterator SI;
typedef map<string,Entry*>::const_iterator CSI;

// Symbol table output method
inline ostream& operator<<(ostream& os, const map<string,Entry*> &table) {
  for (CSI n=table.begin(); n!=table.end(); ++n)
    os << n->first << "\t" << n->second->value << "\t" << 
       n->second->unary << "\t" <<
       n->second->binary << "\t" <<
       n->second->trinary << "\t" << 
       n->second->quaternary << endl;
  return os;
}

// Evaluation stack
extern double stack_value;

/* --------------------------------------------------------------------- *
 *                      Function definitions                             *
 * --------------------------------------------------------------------- */

inline void execerrnr(const char *s, const char *t) {
  cerr << s << ", " << t << endl;
  exit(-1);
}

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

inline double Log(double x) {
  return errcheck(log(x), "log");
}

inline double Log10(double x) {
  return errcheck(log10(x), "log10");
}

inline double Exp(double x) {
  return errcheck(exp(x), "exp");
}

inline double Sqrt(double x) {
  //return errcheck(sqrt(x), "sqrt");
  return sqrt(x);
}

inline double Pow(double x, double y) {
  const double yn = floor(y + .5);
  double px = 1.0;
  if (yn >= 0 && yn == y) {     /* Do it inline if y is an integer power */
      register int n = (int) yn;
      while (n--) 
         px *= x;
  } else  
      px = errcheck(pow(x,y), "exponentiation");
  return px;
}

inline double Integer(double x) {
  return (double) (long) x;
}

inline double Rand(double x) {
  return x * drand48();
}

inline double Bump(double x) {
  if(x >= 0. && x < .125)
    return -1;
  if(x >= 0.125 && x < .25)
    return 0.;
  if(x >= 0.25 && x < .375)
    return 1.;
  if(x >= 0.375 && x <= .5)
    return 0.;
  return -9999.;
}

inline double Radius(double x, double y) {
  if (x != 0. || y != 0.)
    return sqrt (x*x + y*y);
  else
    return 0.;
}

inline double Jn(double i, double x) {
  return jn((int)i, x);
}

inline double Yn(double i, double x) {
  return yn((int)i, x);
}

inline double Angle(double x, double y) {
  double theta = 0.;
  if ((x != 0.)||(y != 0.))
    theta = atan2 (y,x);
  return theta;
}

// Heaviside step function H(x-a) = 1 if x >= 0 else = 0
inline double Step(double x, double a) {
  double H = 1.0;
  if (x < a)
    H = 0.0;
  return H;
}

inline double Shock(double x, double a, double b) {
  if(x==0)
    return 0.5*(a+b);
  if(x>0)
    return b;
  if(x<0)
    return a;
  return 0;
}

/* -----------------------------------------------------------------
   jacobi() - jacobi polynomials 
   Get 'poly' value of the n_th order Jacobi polynomial
   P^(alpha,beta)_n(z) alpha > -1, beta > -1 at the z
   ----------------------------------------------------------------- */
inline double Jacobi(double z, double n, double alpha, double beta){

  register int i,k;
  double   one = 1.0;
  double   a1,a2,a3,a4;
  double   two = 2.0, apb = alpha + beta;
  double   poly, polyn1,polyn2;
  
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

// Vector function evaluation class
class Vector_Function {

public:
  int nargs;
  string arg[3];
  Entry *xyz[3];
  string function;

  Vector_Function( string x, string f) {
    nargs = 1;
    arg[0] = x;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x] = new Entry(x);
    xyz[0] = symtab[x];
    function = f;
  };

  Vector_Function( string x, string y, string f) {
    nargs = 2;
    arg[0] = x; arg[1] = y;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x] = new Entry(x);
    xyz[0] = symtab[x];
    p = symtab.find(y);
    if ( p == symtab.end() )
      symtab[y] = new Entry(y);
    xyz[1] = symtab[y];
    function = f;
  };

  Vector_Function( string x, string y, string z, string f) {
    nargs = 3;
    arg[0] = x; arg[1] = y; arg[2] = z;
    SI p = symtab.find(x);
    if ( p == symtab.end() )
      symtab[x] = new Entry(x);
    xyz[0] = symtab[x];
    p = symtab.find(y);
    if ( p == symtab.end() )
      symtab[y] = new Entry(y);
    xyz[1] = symtab[y];
    p = symtab.find(z);
    if ( p == symtab.end() )
      symtab[z] = new Entry(z);
    xyz[2] = symtab[z];
    function = f;
  };

  void evaluate( dVector &x, dVector &f );
  void evaluate( dVector &x, dVector &y, dVector &f );
  void evaluate( dVector &x, dVector &y, dVector &z, dVector &f );
};

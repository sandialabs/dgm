%{

/** \file Parser.tab.cpp
    \brief C++ parser for DGM input files

    \details This lex/yacc parser compiles with flex and bison with g++.  Note
    that my action code is built on C++ using the STL which makes some aspects
    like symbol tables much easier to implement and maintain.

    \author Scott Collis

    References:
      \li\c J.R. Levine, T. Mason, and D. Brown, "lex & yacc", O'Reilly, 1995.
      \li\c GNU Flex and Bison man and info pages
*/

#include "Parser.hpp"

namespace DGM {

  namespace Parser {

    /// Symbol table
    std::map<string,Entry::Ptr> symtab;

    /// most recent value on the stack
    double stack_value;

    /// indicates that the parser has already been initialized
    bool already_init = false; 

  } // namespace Parser

} // namespace DGM

%}

%union {
  double dval;
  DGM::Parser::Entry *symbol;
  char *str;
}

%token <dval> NUMBER
%token <symbol> MYNAME UNDEF UNARY BINARY TRINARY QUATERNARY
%token <str> FUNC
%token CONTINUATION PARSER_GT PARSER_LT PARSER_EQ PARSER_GE PARSER_LE PARSER_NEQ
%type <dval> expr asgn
%right '='
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS
%right '^'
%nonassoc '?' ':'
%nonassoc PARSER_GT PARSER_LT PARSER_EQ PARSER_GE PARSER_LE PARSER_NEQ

%%

input:
  /* empty */ 
| input line
;

line:
    '\n'
  | expr ';'   { 
#ifdef DGM_PARSER_DEBUG
  cout<<"expr with ;"<<endl;
  printf("stack = %g\n", $1);
#endif
  DGM::Parser::stack_value=$1; 
}
  | func ';'   { 
#ifdef DGM_PARSER_DEBUG
  cout<<"func with ;"<<endl; 
#endif
}
  | defn ';'   { 
#ifdef DGM_PARSER_DEBUG
  cout<<"defn with ;"<<endl; 
#endif
}
  | ';' {
#ifdef DGM_PARSER_DEBUG
  cout<<"Stray semicolon"<<endl;
#endif
}
  | CONTINUATION {
#ifdef DGM_PARSER_DEBUG
  cout<<"Continuation"<<endl;
#endif
}
  | error '\n' { yyerrok; }
;

asgn:       MYNAME '=' expr           
{ if ($1->keyword)
    DGM::Parser::execerrnr("DGM::Parser error:  attempted to override keyword",
                           $1->name.c_str());
  $$=$1->value=$3;
  $1->type=MYNAME;
  $1->keyword=false;
}
;

expr:       NUMBER                    { $$ = $1; }
  |         MYNAME                    { if ($1->type == UNDEF)
                                          DGM::Parser::execerrnr(
                                           "DGM::Parser error: undefined "
                                           "variable",
                                           $1->name.c_str() );
                                        $$ = $1->value; }
  |         asgn
  |         UNARY '(' expr ')'        { $$ = ($1->unary)($3); }
  |         BINARY '(' expr ',' expr ')'
                                      { $$ = ($1->binary)($3,$5); }
  |         TRINARY '(' expr ',' expr ',' expr ')'
                                      { $$ = ($1->trinary)($3,$5,$7); }
  |         QUATERNARY '(' expr ',' expr ',' expr ',' expr')'
                                      { $$ = ($1->quaternary)($3,$5,$7,$9); }
  |         expr '+' expr             { $$ = $1 + $3; }
  |         expr '-' expr             { $$ = $1 - $3; }
  |         expr '*' expr             { $$ = $1 * $3; }
  |         expr '/' expr             { if ($3 == 0) {
                                          char msg[]="Divide by zero";
                                          yyerror(msg);
                                        } else {
                                          $$ = $1 / $3;
                                        } }
  |         expr PARSER_EQ expr       { $$ = ($1 == $3); }
  |         expr PARSER_NEQ expr      { $$ = ($1 != $3); }
  |         expr PARSER_GT expr       { $$ = ($1 > $3); 
                                        //double a=$1; double b=$3; 
                                        //cout<<"Greater than "<<(a>b) <<endl; 
                                      }
  |         expr PARSER_LT expr       { $$ = ($1 < $3); }
  |         expr PARSER_GE expr       { $$ = ($1 >= $3); }
  |         expr PARSER_LE expr       { $$ = ($1 <= $3); }
  |         expr '^' expr             { $$ = DGM::Parser::Pow($1,$3); }
  |         '(' expr ')'              { $$ = $2; }
  |         '-' expr %prec UMINUS     { $$ = -$2; }
  |         expr '?' expr ':' expr    { //double ans=($1 ? $3 : $5); 
                                        //cout<<"arithmetic if: "<<ans<<endl; 
                                        $$ = ($1 ? $3 : $5); }
;

defn:       MYNAME ':' expr           { 
  if ($1->keyword)
    DGM::Parser::execerrnr("DGM::Parser error:  attempted to override keyword",
                           $1->name.c_str());
  $1->value=$3; $1->type=MYNAME; $1->keyword=false; }

func:       FUNC                      { // EXPERIMENTAL: do not use
                                        string func = $1;
                                        func += ';';
                                        cout<<"Make new parser "<<func<<endl;
                                        DGM::Parser::VectorFunction
                                          fun("x","t",func);
                                        //DGM::dVector x(1), f(1);
                                        //x=1.0; fun.evaluate(x,f,0.0);
                                        //cout<<"f = " << f;
                                      }
;

%%

/// Catch floating point exceptions
void fpecatch(int) {
  DGM::Comm::World->cerr() << "DGM::Parser: Floating point exception\n"
    "Exiting...\n";
  DGM::Comm::World->exit(DGM::FAILURE);
}

/// Catch interupts
void intcatch(int) {
  DGM::Comm::World->cerr() << "DGM::Parser: Interupt received\nExiting...\n";
  DGM::Comm::World->exit(DGM::FAILURE);
}

/// Cleanup the DGM inline parser
void parser_clean(const bool verb) {
  //cout << "Parser cleanup" << endl;
  DGM::Parser::cleanup(DGM::Parser::symtab,verb);
}

/// Initialize the DGM inline parser
void parser_init() {
  using namespace DGM::Parser;

  if (already_init) return;
  already_init = true;        // SSC: this wasn't there before -- why

  // turn this off for now to make more portable
#ifdef DGM_PARSER_USE_INTERUPTS
  signal(SIGFPE,fpecatch);
  signal(SIGINT,intcatch);
#endif

  // load up the symbol table
  symtab["sin"].reset( new Entry("sin",sin) );
  symtab["cos"].reset( new Entry("cos",cos) );
  symtab["tan"].reset( new Entry("tan",tan) );
  symtab["sinh"].reset( new Entry("sinh",sinh) );
  symtab["cosh"].reset( new Entry("cosh",cosh) );
  symtab["tanh"].reset( new Entry("tanh",tanh) );
  symtab["asin"].reset( new Entry("asin",asin) );
  symtab["acos"].reset( new Entry("acos",acos) );
  symtab["atan"].reset( new Entry("atan",atan) );
  symtab["atan2"].reset( new Entry("atan2",atan2) );
  symtab["pow"].reset( new Entry("pow",pow) );
#if __cplusplus > 201402L
  symtab["hypot"].reset( new Entry("hypot", Hypot) );
#else // not C++17
  symtab["hypot"].reset( new Entry("hypot", hypot) );
#endif
  symtab["max"].reset( new Entry("max", Max) );
  symtab["min"].reset( new Entry("min", Min) );
  symtab["abs"].reset( new Entry("abs",fabs) );
  symtab["int"].reset( new Entry("int",Integer) );
  symtab["log"].reset( new Entry("log",Log) );
  symtab["log10"].reset( new Entry("log10",Log10) );
  symtab["exp"].reset( new Entry("exp",Exp) );
  symtab["sqrt"].reset( new Entry("sqrt",Sqrt) );
  symtab["rand"].reset( new Entry("rand",Rand) );
  symtab["random"].reset( new Entry("random",Rand) );
  symtab["bump"].reset( new Entry("bump",Bump) );
  symtab["radius"].reset( new Entry("radius",Radius) );
  symtab["jn"].reset( new Entry("jn",Jn) );
  symtab["yn"].reset( new Entry("yn",Yn) );
  symtab["erf"].reset( new Entry("erf",Erf) );
  symtab["erfc"].reset( new Entry("erfc",Erfc) );
  symtab["ang"].reset( new Entry("ang",Angle) );
  symtab["step"].reset( new Entry("step",Step) );
  symtab["shock"].reset( new Entry("shock",Shock) );
  symtab["jacobi"].reset( new Entry("jacobi",Jacobi) );
  symtab["mollifier"].reset( new Entry("mollifier",Mollifier) );
  symtab["Gaussian"].reset( new Entry("Gaussian",Gaussian) );
  symtab["Normal"].reset( new Entry("NormalDistribution",
                                    NormalDistribution) );
  // load some constants
  symtab["PI"].reset(new Entry("PI",3.14159265358979323846)); // Pi
  symtab["E"].reset(new Entry("E",2.71828182845904523536));   // Natural log
  symtab["GAMMA"].reset(new Entry("GAMMA",0.57721566490153286060)); // Euler
  symtab["DEG"].reset(new Entry("DEG",57.29577951308232087680)); // deg/radian
  symtab["PHI"].reset(new Entry("PHI",1.61803398874989484820)); // golden ratio
  symtab["EPSM"].reset(new Entry("EPSM",DGM::epsM)); // machine precision

#ifdef DGM_PARSER_TEST
  // various tests of symbol table
#ifdef DGM_PARSER_VECTOR_TEST
  // define a vector_function
  Vector_Function fun( "x", "sqrt(x)\n" );
  DGM::dVector x(2), f(2);
  x = -1.0;
  fun.evaluate( x, f );
  cout << "f = " << endl << f << endl;
  Vector_Function xyfun( "x", "y", "exp(x)+sin(y)\n" );
  DGM::dVector y(2), g(2);
  y = 2.0;
  xyfun.evaluate( x, y, g );
  cout << "g = " << endl << g << endl;
#else
  //  cout << "Symbol table" << endl << symtab << endl;
  if (yyparse()) {
    DGM::Comm::World->cerr() << "Error in yyparse" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
#endif
#endif
}

/// Parser error output
void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
  DGM::Comm::World->cerr() << "DGM::Parser error: " << s << endl;
  DGM::Comm::World->exit(DGM::FAILURE);
}

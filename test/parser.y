%{

// C++ parser for Spectral Element input files

// S. Scott Collis

// This lex/yacc parser compiles with flex and bison with g++.  Note that
// Note that my action code is built on C++ using the STL which makes some
// aspects like symbol tables much easier to implement and maintain.

// References:  
//  1) J.R. Levine, T. Mason, and D. Brown, "lex & yaxx", O'Reilly, 1995.
//  2) GNU Flex and Bison man and info pages

#include <fstream>
#include "parser.h"

// Symbol table
map<string,Entry*> symtab;
double stack_value;

%}

%union {
  double dval;
  Entry *symbol;
  char *str;
}
%token <dval> NUMBER
%token <symbol> NAME UNDEF UNARY BINARY TRINARY QUATERNARY
%token <str> FUNC
%type <dval> expr asgn
%right '='
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS
%right '^'

%%

input:  /* empty */
  |        input line
;

line:      '\n'
  |        expr '\n'  { printf("stack = %g\n", $1); stack_value=$1;}
  |        func '\n'  { ; }
  |        error '\n' { yyerrok; }
;

asgn:       NAME '=' expr             { $$=$1->value=$3; $1->type=NAME;}

expr:       NUMBER                    { $$ = $1; }
  |         NAME                      { if ($1->type == UNDEF)
                                          execerrnr(
					   "Parser error: undefined variable",
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
  |         expr '/' expr             { if ($3 == 0) 
			                  yyerror("divide by zero");
			                else
			                  $$ = $1 / $3; }
  |         expr '^' expr             { $$ = Pow($1,$3); }
  |         '(' expr ')'              { $$ = $2; }
  |         '-' expr %prec UMINUS     { $$ = -$2; }
  ;

func:       FUNC                      { string func = $1;
                                        func += '\n';
                                        Vector_Function fun("x",func);
                                        dVector x(2), f(2);
                                        x=1.0; fun.evaluate(x,f);
                                        cout<<"f = " << endl << f << endl;}

%%

void fpecatch(int)	{
  cerr << "Floating point exception\nExiting...\n";
  exit(-1);
}

void intcatch(int)	{
  cerr << "Interupt received\nExiting...\n";
  exit(-1);
}

int main() {

  signal(SIGFPE,fpecatch);
  signal(SIGINT,intcatch);

  // load up the symbol table
  symtab["sin"] = new Entry("sin",sin);
  symtab["cos"] = new Entry("cos",cos);
  symtab["tan"] = new Entry("tan",tan);
  symtab["sinh"] = new Entry("sinh",sinh);
  symtab["cosh"] = new Entry("cosh",cosh);
  symtab["tanh"] = new Entry("tanh",tanh);
  symtab["asin"] = new Entry("asin",asin);
  symtab["acos"] = new Entry("acos",acos);
  symtab["atan"] = new Entry("atan",atan);
  symtab["abs"] = new Entry("abs",fabs);
  symtab["int"] = new Entry("int",Integer);
  symtab["log"] = new Entry("log",Log);
  symtab["log10"] = new Entry("log10",Log10);
  symtab["exp"] = new Entry("exp",Exp);
  symtab["sqrt"] = new Entry("sqrt",Sqrt);
  symtab["rand"] = new Entry("rand",Rand);
  symtab["bump"] = new Entry("bump",Bump);
  symtab["jn"] = new Entry("jn",Jn);
  symtab["yn"] = new Entry("yn",Yn);
  symtab["ang"] = new Entry("ang",Angle);
  symtab["step"] = new Entry("step",Step);
  symtab["shock"] = new Entry("shock",Shock);
  symtab["jacobi"] = new Entry("jacobi",Jacobi);

  // load some constants
  symtab["PI"] = new Entry("PI",3.14159265358979323846);       // Pi
  symtab["E"] = new Entry("E",2.71828182845904523536);         // Natural log
  symtab["GAMMA"] = new Entry("GAMMA",0.57721566490153286060); // Euler
  symtab["DEG"] = new Entry("DEG",57.29577951308232087680);    // deg/radian
  symtab["PHI"] = new Entry("PHI",1.61803398874989484820);     // golden ratio

#if 0
  // define a vector_function
  Vector_Function fun( "x", "sqrt(x)\n" );
  dVector x(2), f(2);
  x = -1.0;
  fun.evaluate( x, f );
  cout << "f = " << endl << f << endl;
  Vector_Function xyfun( "x", "y", "exp(x)+sin(y)\n" );
  dVector y(2), g(2);
  y = 2.0;
  xyfun.evaluate( x, y, g );
  cout << "g = " << endl << g << endl;
#else
  //  cout << "Symbol table" << endl << symtab << endl;
  if (yyparse()) {
    cerr << "Error in yyparse" << endl;
    exit(-1);
  }
#endif 

  // test of binary IO

  {
    dVector u(100);
    u = 1.0;
    string fname = "tmp.dat";
    ofstream fs(fname.c_str());
    fs << "This is a binary file" << endl;
    fs.write( u.data(), sizeof(double)*u.size() );
    fs.close();
  }

  {
    dVector x(100);
    string fname = "tmp.dat";
    string buffer;
    ifstream fs(fname.c_str());
    getline(fs,buffer);
    fs.read( x.data(), sizeof(double)*x.size() );
    fs.close();
    cout << "x = " << x << endl;
  }

  return 0;
}

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

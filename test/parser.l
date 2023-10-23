%{

// C++ Lexer for Spectral Element input files

// S. Scott Collis

#include "parser.h"
#include "parser.tab.h"

static YY_BUFFER_STATE old_buf;
%}

ws [ \t]*
eol \n
word [A-Za-z][A-Za-z0-9]*

%s FUNCTION

%%

{word}{ws}":=" {
  BEGIN FUNCTION;
  cout << "found function" << endl;
}

<FUNCTION>[^;]+ { yylval.str=strdup(yytext); BEGIN INITIAL; return FUNC;}

[;]* ;  /* ignore semicolons */

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { 
  yylval.dval = atof(yytext); 
  return NUMBER; 
}

[ \t] ;  /* ignore white space */

[A-Za-z][A-Za-z0-9]* {
  string key = yytext;
  SI p = symtab.find(key);
  if ( p == symtab.end() )
    symtab[key] = new Entry(key);  // install a new Entry in the symbol table
  yylval.symbol = symtab[key];
  if (yylval.symbol->unary)
    return UNARY;
  else if (yylval.symbol->binary)
    return BINARY;
  else if (yylval.symbol->trinary)
    return TRINARY;
  else if (yylval.symbol->quaternary)
    return QUATERNARY;
  else
    return NAME;
}

<<EOF>> {return 0;}

"$" {return 0;}

\n | 
.  {return yytext[0];}

%%

// if yywrap returns 0 it is assumed that additional input is available, i.e.
// you could set yyin to point to a different file, and scanning continues.
// if yywrap doesn't return 0, then the scanner terminates and returns 0 to 
// its caller (usually yyparse).
int yywrap() { return 1; };

// constructors for Entry class
Entry::Entry(string n) : name(n), value(0.0), type(UNDEF) {
  unary = 0; binary = 0; trinary = 0; quaternary = 0;};
Entry::Entry(string n, const double v) : name(n), value(v), type(NAME) {
  unary = 0; binary = 0; trinary = 0; quaternary = 0;};
Entry::Entry(string n, PFD func) : name(n), value(0.0), type(UNARY) {
  unary = func; binary = 0; trinary = 0; quaternary = 0;};
Entry::Entry(string n, PF2D func) : name(n), value(0.0), type(BINARY) {
  unary = 0; binary = func; trinary = 0; quaternary = 0;};
Entry::Entry(string n, PF3D func) : name(n), value(0.0), type(TRINARY) { 
  unary = 0; binary = 0; trinary = func; quaternary = 0;};
Entry::Entry(string n, PF4D func) : name(n), value(0.0), type(QUATERNARY) {
  unary = 0; binary = 0; trinary = 0; quaternary = func;};

// Vector function evaluation routines
void Vector_Function::evaluate( dVector &x, dVector &f ) {
  if (nargs != 1) {
    cerr << "Error evaluating two argument vector function" << endl;
    exit(1);
  }
  if (x.size() != f.size() ) {
    cerr << "evaluating unequal vectors" << endl;
    exit(1);
  }
  // save original buffer
  YY_BUFFER_STATE old_buf = YY_CURRENT_BUFFER;
  for(int n=0; n<x.size(); n++) {
    xyz[0]->value = x[n]; xyz[0]->type = NAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    if (yyparse()) {
      cerr << "Vector_Function::evaluate -- Error in yyparse" << endl;
      exit(-1);
    }
    yy_delete_buffer(buf);
    f[n] = stack_value;
  }
  // switch back to original buffer
  yy_switch_to_buffer(old_buf);
}

void Vector_Function::evaluate( dVector &x, dVector &y, dVector &f ) {
  if (nargs != 2) {
    cerr << "Error evaluating two argument vector function" << endl;
    exit(1);
  }
  if (x.size() != f.size() || y.size() != f.size()) {
    cerr << "evaluating unequal vectors" << endl;
    exit(1);
  }
  // save original buffer
  YY_BUFFER_STATE old_buf = YY_CURRENT_BUFFER;
  for(int n=0; n<x.size(); n++) {
    xyz[0]->value = x[n]; xyz[0]->type = NAME;
    xyz[1]->value = y[n]; xyz[1]->type = NAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    yyparse();
    yy_delete_buffer(buf);
    f[n] = stack_value;
  }
  // switch back to original buffer
  yy_switch_to_buffer(old_buf);
}

void Vector_Function::evaluate( dVector &x, dVector &y, dVector &z, 
				dVector &f ) {
  if (nargs != 3) {
    cerr << "Error evaluating two argument vector function" << endl;
    exit(1);
  }
  if (x.size() != f.size() || y.size() != f.size() || z.size() != f.size()) {
    cerr << "evaluating unequal vectors" << endl;
    exit(1);
  }
  for(int n=0; n<x.size(); n++) {
    xyz[0]->value = x[n]; xyz[0]->type = NAME;
    xyz[1]->value = y[n]; xyz[1]->type = NAME;
    xyz[2]->value = z[n]; xyz[2]->type = NAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    yyparse();
    yy_delete_buffer(buf);
    f[n] = stack_value;
  }
}

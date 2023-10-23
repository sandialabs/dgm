%{

// C++ Lexer for DGM input files

// Author:  S. Scott Collis

#include "Parser.hpp"
#include "Parser.tab.hpp"

// This prevents the unused function warning 
#define YY_NO_INPUT

// static YY_BUFFER_STATE old_buf;

// option nounput removes the warning regarding unused yy_unput function

// We used to ignore semicolons, now they allow for compound expressions
//[;]* { cout<<"ignored a ;"<<endl; }  /* ignore semicolons */ 

// Note that the FUNCTION stuff is experimental and not working right now
/*
{word}{ws}":=" {
  BEGIN FUNCTION;
  cout << "WARNING: found EXPERIMENTAL function " << yytext << endl;
  cout << "  proceed at your own risk..." << endl;
}

<FUNCTION>[^;]+ { 
  cout<<"function is "<<yytext<<endl; 
  yylval.str=strdup(yytext); 
  BEGIN INITIAL; 
  return FUNC;
}
*/

%}

%option nounput  

ws [ \t]*
eol \n
word [A-Za-z][A-Za-z0-9]*

%s FUNCTION

%%

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { 
  yylval.dval = atof(yytext);
#ifdef DGM_PARSER_DEBUG
  cout << "found number " << yylval.dval << endl;
#endif
  return NUMBER; 
}

[ \t] { 
#ifdef DGM_PARSER_DEBUG
  cout<<"ignored some whitespace"<<endl; 
#endif
}  /* ignore white space */

[A-Za-z][A-Za-z0-9]* {
#ifdef DGM_PARSER_DEBUG
  cout << "found key " << yytext << endl;
#endif
  string key = yytext;
  DGM::Parser::SI p = DGM::Parser::symtab.find(key);
  if ( p == DGM::Parser::symtab.end() )
    DGM::Parser::symtab[key].reset( new DGM::Parser::Entry(key,false) ); 
  yylval.symbol = DGM::Parser::symtab[key].get();
  if (yylval.symbol->unary)
    return UNARY;
  else if (yylval.symbol->binary)
    return BINARY;
  else if (yylval.symbol->trinary)
    return TRINARY;
  else if (yylval.symbol->quaternary)
    return QUATERNARY;
  else
    return MYNAME;
}

":=" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found := "<<endl; 
#endif
  return ':'; 
}

"==" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found == "<<endl; 
#endif
  return PARSER_EQ; 
}

"!=" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found != "<<endl; 
#endif
  return PARSER_NEQ; 
}

">=" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found >= "<<endl; 
#endif
  return PARSER_GE; 
}

"<=" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found <= "<<endl; 
#endif
  return PARSER_LE; 
}

">" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found > "<<endl; 
#endif
  return PARSER_GT; 
}

"<" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found < "<<endl; 
#endif
  return PARSER_LT; 
}

"=" { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found = "<<endl; 
#endif
  return ':'; 
}

\n { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found newline"<<endl; 
#endif
  return yytext[0]; 
}

"\\" {
#ifdef DGM_PARSER_DEBUG
  cout<<"Found continuation"<<endl;
#endif
  return CONTINUATION;
}

. {
#ifdef DGM_PARSER_DEBUG
  cout<<"Found character "<<yytext<<endl;
#endif
  return yytext[0];
}

<<EOF>> { 
#ifdef DGM_PARSER_DEBUG
  cout<<"Found EOF"<<endl; 
#endif
  return 0;
}

%%

// if yywrap returns 0 it is assumed that additional input is available, i.e.
// you could set yyin to point to a different file, and scanning continues.
// if yywrap doesn't return 0, then the scanner terminates and returns 0 to 
// its caller (usually yyparse).
int yywrap() { return 1; }

// constructors for Entry class
DGM::Parser::Entry::Entry(string n, bool kw) : 
  type(UNDEF), name(n), value(0.0), keyword(kw) {
  unary = 0; binary = 0; trinary = 0; quaternary = 0; 
}
DGM::Parser::Entry::Entry(string n, const double v, bool kw) : 
  type(MYNAME), name(n), value(v), keyword(kw) {
  unary = 0; binary = 0; trinary = 0; quaternary = 0; 
}
DGM::Parser::Entry::Entry(string n, Entry::PFD func) : 
  type(UNARY), name(n), value(0.0), keyword(true) {
  unary = func; binary = 0; trinary = 0; quaternary = 0; 
}
DGM::Parser::Entry::Entry(string n, Entry::PF2D func) : 
  type(BINARY), name(n), value(0.0), keyword(true) {
  unary = 0; binary = func; trinary = 0; quaternary = 0; 
}
DGM::Parser::Entry::Entry(string n, Entry::PF3D func) : 
  type(TRINARY), name(n), value(0.0), keyword(true) { 
  unary = 0; binary = 0; trinary = func; quaternary = 0;
}
DGM::Parser::Entry::Entry(string n, Entry::PF4D func) : 
  type(QUATERNARY), name(n), value(0.0), keyword(true) {
  unary = 0; binary = 0; trinary = 0; quaternary = func;
}

/// Vector function evaluation in one-dimension
void DGM::Parser::VectorFunction::evaluate( dVector &x, dVector &f,
                                            const Scalar &t,
                                            Operation operation) {
  if (nargs != 2) {
    DGM::Comm::World->cerr()<< "Error evaluating one-argument vector function" 
                            << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  if (x.size() != f.size() ) {
    DGM::Comm::World->cerr()<< "Evaluating unequal vectors" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  for(DGM::Ordinal n=0; n<x.size(); n++) {
    xyzt[0]->value = x[n]; xyzt[0]->type = MYNAME;
    xyzt[3]->value = t;    xyzt[3]->type = MYNAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    if (yyparse()) {
      DGM::Comm::World->cerr()<<"VectorFunction::evaluate -- Error in yyparse"
                              << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
    yy_delete_buffer(buf);
    dgm_yylex_destroy();
    switch (operation) {
    case Equal:
      f[n] = stack_value;
      break;
    case Add:
      f[n] += stack_value;
      break;
    case Subtract:
      f[n] -= stack_value;
      break;
    case Multiply:
      f[n] *= stack_value;
      break;
    case Divide:
      f[n] /= stack_value;
      break;
    default:
      DGM::Comm::World->cerr()<<"VectorFunction::evaluate -- invalid operation"
                              << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }
}

/// Vector function evaluation in two-dimensions
void DGM::Parser::VectorFunction::evaluate( dVector &x, dVector &y, 
                                            dVector &f, const Scalar &t,
                                            Operation operation ) {
  if (nargs != 3) {
    DGM::Comm::World->cerr()<< "Error evaluating two-argument vector function" 
                            << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  if (x.size() != f.size() || y.size() != f.size()) {
    DGM::Comm::World->cerr()<< "Evaluating unequal vectors" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  for(DGM::Ordinal n=0; n<x.size(); n++) {
    xyzt[0]->value = x[n]; xyzt[0]->type = MYNAME;
    xyzt[1]->value = y[n]; xyzt[1]->type = MYNAME;
    xyzt[3]->value = t;    xyzt[3]->type = MYNAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    yyparse();
    yy_delete_buffer(buf);
    dgm_yylex_destroy();
    //cout << " x: " << x[n] << " y: " << y[n] << " t: " << t << " value: "
    //<< stack_value << endl;
    switch (operation) {
    case Equal:
      f[n] = stack_value;
      break;
    case Add:
      f[n] += stack_value;
      break;
    case Subtract:
      f[n] -= stack_value;
      break;
    case Multiply:
      f[n] *= stack_value;
      break;
    case Divide:
      f[n] /= stack_value;
      break;
    default:
      DGM::Comm::World->cerr()<<"VectorFunction::evaluate -- invalid operation"
                              << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }
}

/// Vector function evaluation in three-dimensions
void DGM::Parser::VectorFunction::evaluate( dVector &x, dVector &y, 
                                            dVector &z, dVector &f,
                                            const Scalar &t,
                                            Operation operation ) {
  if (nargs != 4) {
    DGM::Comm::World->cerr()
      << "Error evaluating three-argument vector function" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  if (x.size() != f.size() || y.size() != f.size() || z.size() != f.size()) {
    DGM::Comm::World->cerr()<< "Evaluating unequal vectors" << endl;
    DGM::Comm::World->exit(DGM::FAILURE);
  }
  for(DGM::Ordinal n=0; n<x.size(); n++) {
    xyzt[0]->value = x[n]; xyzt[0]->type = MYNAME;
    xyzt[1]->value = y[n]; xyzt[1]->type = MYNAME;
    xyzt[2]->value = z[n]; xyzt[2]->type = MYNAME;
    xyzt[3]->value = t;    xyzt[3]->type = MYNAME;
    YY_BUFFER_STATE buf = yy_scan_string( function.c_str() );
    yyparse();
    yy_delete_buffer(buf);
    dgm_yylex_destroy();
    switch (operation) {
    case Equal:
      f[n] = stack_value;
      break;
    case Add:
      f[n] += stack_value;
      break;
    case Subtract:
      f[n] -= stack_value;
      break;
    case Multiply:
      f[n] *= stack_value;
      break;
    case Divide:
      f[n] /= stack_value;
      break;
    default:
      DGM::Comm::World->cerr()<<"VectorFunction::evaluate -- invalid operation"
                              << endl;
      DGM::Comm::World->exit(DGM::FAILURE);
    }
  }
}

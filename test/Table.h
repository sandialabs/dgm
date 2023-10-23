#ifndef TABLE_H
#define TABLE_H

#include <fstream>
#include <string>
#include <map>
using namespace std;

enum Value_type {NONE, DOUBLE, INT, STRING, BOOL};

class Value {

 public:
  Value_type type;
  void* val;

  // constructors
  Value() : type(NONE) { 
    val = 0; 
  }
  Value(const double v) : type(DOUBLE) { 
    val=new double;
    copy( &v, &v+1, static_cast<double*>(val) ); 
  }
  Value(const int v) : type(INT) { 
    val=new int; 
    copy( &v, &v+1, static_cast<int*>(val) );
  }
  Value(const string v) : type(STRING) { 
    val=new string; 
    *(static_cast<string*>(val)) = v;
  }
  Value(const char* v) : type(STRING) { 
    val=new string; 
    *(static_cast<string*>(val)) = v;
  }
  Value(const bool v) : type(BOOL) { 
    val=new bool; 
    copy( &v, &v+1, static_cast<bool*>(val) );
  }

  // cast operators
  operator double() {return *(static_cast<double*>(val));}
  operator int()    {return *(static_cast<int*>(val));}
  operator string() {return *(static_cast<string*>(val));}
  operator bool()   {return *(static_cast<bool*>(val));}

  Value& operator= (const double v) {
    if (val==0) { val=new double; type = DOUBLE; }
    if (type != DOUBLE) {
      cerr << "Illegal type: " << type << " should be " << DOUBLE << endl; 
      exit(1);
    }
    copy( &v, &v+1, static_cast<double*>(val) ); 
    return *this;
  }

  Value& operator= (const int v) { 
    if (val==0) { val=new int; type = INT; }
    if (type != INT) {
      cerr << "Illegal type: " << type << " should be " << INT << endl; 
      exit(1);
    }
    copy( &v, &v+1, static_cast<int*>(val) ); 
    return *this;
  }

  Value& operator= (const char* v) { 
    if (val==0) { val=new string; type = STRING; }
    if (type != STRING) {
      cerr << "Illegal type: " << type << " should be " << INT << endl; 
      exit(1);
    }
    *(static_cast<string*>(val)) = v;
    return *this;
  }

  Value& operator= (const string v) {
    bool b; double d;
    if (val==0) { val=new string; type = STRING; }
    if (type != STRING) {
      switch (type) {
      case DOUBLE:
	*this = atof(v.c_str());
	break;
      case INT:
	*this = atoi(v.c_str());
	break;
      case BOOL:
	b = atoi(v.c_str());
	*this = b;
	break;
      default:
	cerr << "Unsupported value type" << endl;
	exit(1);
      }
    } else
      *(static_cast<string*>(val)) = v;
    return *this;
  }

  Value& operator= (const bool v) { 
    if (val==0) { val=new bool; type = BOOL; }
    if (type != BOOL) {
      cerr << "Illegal type: " << type << " should be " << BOOL << endl; 
      exit(1);
    }
    copy( &v, &v+1, static_cast<bool*>(val) ); 
    return *this;
  }

  friend ostream& operator<<(ostream&, const Value&);
};

// output method
inline ostream& operator<<(ostream& os, const Value& P) {
  switch (P.type) {
  case DOUBLE:
    os << *(static_cast<double*>(P.val));
    break;
  case INT:
    os << *(static_cast<int*>(P.val));
    break;
  case STRING:
    os << *(static_cast<string*>(P.val));
    break;
  case BOOL:
    os << *(static_cast<bool*>(P.val));
    break;
  }
  return os;
}  

//****************************************************************************

class Table {
  map<string,string> prefixes;
  map<string,Value*> table;
 public: 
  // constructor
  Table() { };

  // methods
  void parse( int argc, char *argv[]);
  void read( const string );

  Value& operator[] (const string key) { 
    if ( table[key] == 0 )
      table[key] = new Value();
    return *(table[key]); 
  }

  friend ostream& operator<<(ostream&, const Table&);
};

// Parameter iterators
typedef map<string,Value*>::iterator PI;
typedef map<string,Value*>::const_iterator CPI;

// Read parameters from an input file
inline void Table::read( const string fname ) {
  bool b;
  string name, token, value;
  ifstream fp(fname.c_str());
  if ( fp ) 
    while ( fp >> name >> token >> value ) {      
      // cout << "Table::read " << name << token << value << endl;
      PI p = table.find(name);
      if ( p != table.end() )
	(*this)[name] = value;
      else
	cerr << "Parameter \"" << name << "\" not found in table"<< endl;
    }
}

// Extract parameters from an argument list
inline void Table::parse(int argc, char *argv[]) {
  bool b;
  string name, value, code=argv[0];
  while ( --argc && (*++argv)[0] == '-') {
    name = *argv;
    name.erase(0,1);          // remove the minus
    PI p = table.find(name);
    if ( p != table.end() ) {
      value = *(++argv);      // extract the value 
      argc--;
      (*this)[name] = value;
    } else {
      cerr << "\"" << name << "\" not found in table." << endl;
      goto showUsage;
    }	
  }
  return;
 showUsage:
  cerr << "=================================\n" 
       << "Usage:   " << code << " [Options]\n" 
       << "=================================\n" 
       << "Options: " << '\t' << "Defaults  \n" 
       << "=================================\n";
  cerr << *this;
  exit(-1);
}
  
// output method
inline ostream& operator<<(ostream& os, const Table& P) {
  for (CPI p = P.table.begin(); p != P.table.end(); ++p)
    os << p->first << " = " << *(p->second) << endl;
  return os;
}

#endif

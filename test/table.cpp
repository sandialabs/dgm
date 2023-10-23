// g++ testTable.cpp

#include <iostream>
using namespace std;

#include "Table.h"

int main(int argc, char *argv[]) {

  Table table;

  // booleans
  table["viscous"] = false;
  table["imesh"] = false;

  // Integers
  table["ne"] = 20;        // number of elements
  table["p"] = 5;          // polynomial degree
  table["q"] = 0;          // quadrature points
  table["nsd"] = 1;        // number of space dimensions
  table["Nt"] = 100;       // number of time steps
  table["Ntout"] = 50;     // intervale between norm outputs

  // Doubles
  table["dt"] = 0.01;      // time step
  table["Lx"] = 4.0;       // domain length
  table["alpha"] = 1.0;    // wavespeed in x
  table["beta"] = 0.0;     // wavespeed in y
  table["vis"] = 0.0;      // viscosity coefficient

  // Strings
  table["root"] = "run";   // root of the input file names

  // print out
  // cout << table << endl;

  // read from a file
  table.read("foo");

  // print out
  // cout << table << endl;

  // parse an argument list
  table.parse(argc,argv);

  // print out
  cout << table << endl;

  string root = table["root"];
  double dt = table["dt"];
  int Nt = table["Nt"];

  cout << "Nt = " << Nt << endl;
  cout << "dt = " << dt << endl;
  cout << "root = " << root << endl;
  cout << "imesh = " << table["imesh"] << endl;
}



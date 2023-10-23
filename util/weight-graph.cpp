/** \file   weight-graph.cpp
    \brief  Convert input graph and weight files into weighted graph file
    \author Scott Collis
 **/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  bool verb(false);
  int ne, w;
  int num_nodes, num_edges;
  string buffer;
  if (argc < 2) {
    cout << "Usage: weight-graph root" << endl;
    exit(-1);
  }
  string root(argv[1]);
  string igraph(root); igraph += ".grf";
  cout << "Reading input graph file:   " << igraph << endl;
  ifstream graph(igraph.c_str());
  string iweight(root); iweight += ".wgt";
  cout << "Using input weight file:    " << iweight << endl;
  ifstream weight( iweight.c_str() );
  string ograph(root);
  cout << "Output weighted graph file: " << ograph << endl;
  ofstream wgraph( ograph.c_str() );
  if (graph && weight) {
    graph >> num_nodes >> num_edges;
    getline(graph,buffer);
    if (verb) cout << num_nodes << " " << num_edges << " 10" << endl;
    wgraph << num_nodes << " " << num_edges << " 10" << endl;
    weight >> ne;
    for (int e=0; e<ne; e++) {
      weight >> w;
      getline(graph,buffer);
      if (verb) cout << w << " " << buffer << endl;
      wgraph << w << " " << buffer << endl;
    }
  }
  graph.close();
  weight.close();
  wgraph.close();
}

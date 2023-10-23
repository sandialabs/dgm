
/**
   \file   con2wgraph.cpp
   \brief  Convert DGM connectivity to METIS weighted graph
   \author Guoquan Chen
 **/

//===============================================================
//  g++(icc) con2wgraph.cpp -o con2wgraph
//================================================================
//
//   Purpose:
//      This is a utility for DGM to translate DGM standard connectivity
//      root+.con
//     into general METIS weighted graph file, considering the different
//     element weights.
//
//     weights_file + root.con => root.wgraph( weighted graph file)
//
//     then you can use kmetis/pmetis from METIS to partition it
//
//   Author:  Guoquan Chen
//   Date:    05/19/2004
//


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {

  int ne,ne1,nsides,nbc;
  string buffer;
  char type;
  int eid, sid, leid, lsid;
  int w;
  vector< vector<int> > en_con;

  if (argc < 3) {
    cout << "Usage:  weights-file root" << endl;
    exit(-1);
  }

  string weights(argv[1]);
  //  weights += ".wgt";
  ifstream weight(weights.c_str());

  string fcon(argv[2]);
  fcon +=".con";
  ifstream connectivity(fcon.c_str());

  string fbc(argv[2]);
  fbc += ".bc";
  ifstream bc(fbc.c_str());

  string wgraph(argv[2]);
  wgraph += ".wgraph";
  ofstream ograph( wgraph.c_str() );

  cout << "Reading weights file:         " << weights << endl;
  cout << "Reading connectivity file:    " << fcon << endl;
  cout << "Reading boundary file:        " << fbc << endl;

  cout << "Output weighted graph file: " << wgraph << endl;


  if (connectivity&& weight && bc) {
    getline(connectivity,buffer);

    connectivity>>ne1;
    getline(connectivity,buffer);

    weight>>ne;
    getline(weight,buffer);

    if(ne!=ne1){
      cerr << "Element number different in Weights file and Connectivity "
           << "file" << endl;
      exit(-1);
    }

    // Read boundary information
    getline(bc,buffer);
    bc>>nbc;
    getline(bc,buffer);

    // Read connectivity file
    en_con.resize(ne);
    int n=0;
    while(connectivity>> type >> eid >> sid >> leid >> lsid) {
      getline(connectivity,buffer);
      if (leid!=-1)
	en_con[eid].push_back(leid);
      n++;
    }
    // Compute total edge numbers
    nsides = n/2;
    ograph <<ne << " " << nsides << " 10" << endl;

    for(int e=0;e<ne;e++){
      weight>>w; getline(weight,buffer);
      ograph << w << " ";
      for(int le=0;le<en_con[e].size();le++)
	ograph<<en_con[e][le]+1<<" ";
      ograph<<endl;
    }
  }

  ograph.close();
  weight.close();
  connectivity.close();
  bc.close();
}


/** \file   modelweight.cpp
    \brief  Generate new weights based on element model types
    \author Guoquan Chen
 **/

//===============================================================
//  g++(icc) modelweight.cpp -o modelweight
//================================================================
//
//   Purpose:
//      This is a utility for DGM to produce the new weights file
//       considering the element model types.
//
//     weights_file + root.model => root.mwgt( modelled weighted file)
//
//
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

  int ne;
  string buffer;
  int eid, meid;
  int w;
  vector<int> w_en;

  if (argc < 3) {
    cout << "Usage:  weights-file root" << endl;
    exit(-1);
  }

  string weights(argv[1]);
  //  weights += ".wgt";
  ifstream weight(weights.c_str());

  string fmod(argv[2]);
  fmod +=".mod";
  ifstream model(fmod.c_str());

  string mweights(argv[2]);
  mweights += ".mwgt";
  ofstream mweight( mweights.c_str() );

  cout << "Reading weights file:         " << weights << endl;
  cout << "Reading model file:           " << fmod << endl;

  cout << "Output weighted model file: " << mweights << endl;


  if (model&& weight) {
    getline(model,buffer);

    weight>>ne;
    getline(weight,buffer);

    //read connectivity file
    w_en.resize(ne);

    for(int i=0;i<ne;i++){
      model>>eid>>meid;
      getline(model,buffer);
      switch(meid){
      case 0: //ADV_DIFF
	w_en[i] = 10;
	break;
      case 1: //Euler
	w_en[i] = 10;
	break;
      case 2: //Navier_Stokes
	w_en[i] = 20;
	break;
      case 3: //Wave
	w_en[i] = 3;
	break;
      case 4: //LinEuler
	w_en[i] = 9;
	break;
      default:
	cerr<<"Illegal model type in model file"<<endl;
	exit(-1);
      }
    }


    mweight <<ne<< endl;

    for(int e=0;e<ne;e++){
      weight>>w; getline(weight,buffer);
      mweight <<w*w_en[e] <<endl;
    }
  }

  mweight.close();
  weight.close();
  model.close();
}

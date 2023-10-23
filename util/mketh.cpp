/*****************************************************************************
  Title:      Make Earth

  Author:     Thomas M. Smith

  Date:        01/13/10

  Copyright:  (c) Sandia National Laboratories

  NOTE: Only works with 4 node quad and 8 node hex elements and expects
        layer boundaries to match element boundaries (i.e., Cartesian).

******************************************************************************/

/** \file   mketh.cpp
    \brief  Creates an earth model for a DGM mesh
    \author Tom Smith
**/

// system libraries
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  int ne, nsd, nl, i, e, l;
  int nverts;
  double rho = 0.0;
  double Vp  = 0.0;
  double Vs  = 0.0;
  double rhoref, Vpref, Vsref;
  double xmin,xmax,ymin,ymax,zmin,zmax;
  char *fname_mesh, *fname_layers, *fname_eth;
  string buffer;
  FILE * fp;

  // Parse command line arguments
  switch(argc) {
  case 4:
    fname_mesh   = argv[1];
    fname_layers = argv[2];
    fname_eth    = argv[3];
    break;
  default:
    cerr<<"Usage: mketh meshfile layersfile earthfile"<<endl;
  }

  fp = fopen(fname_eth,"w");

  ifstream lf(fname_layers);
  if (!lf) {
    cerr << "Could not open layers file " << fname_layers << endl;
  }

  lf >> nl >> nsd;
  cout << "Number of layers = " << nl << " Dimension = " << nsd << endl;
  getline(lf, buffer);
  cout << buffer << endl;
  lf >> rhoref >> Vpref >> Vsref;
  getline(lf, buffer);
  cout << "rhoref = " << rhoref << " Vpref = " << Vpref << " Vsref = "
       << Vsref << endl;

  vector<double> xminLay(nl), xmaxLay(nl);
  vector<double> yminLay(nl), ymaxLay(nl);
  vector<double> zminLay(nl), zmaxLay(nl);
  vector<double> rhoLay(nl), VpLay(nl), VsLay(nl);

  if (nsd == 2) {
    for (i=0; i<nl; i++) {
      lf >> xminLay[i] >> xmaxLay[i]
         >> yminLay[i] >> ymaxLay[i]
         >> rhoLay[i] >> VpLay[i] >> VsLay[i];
      getline(lf, buffer);
    }
    for (i=0; i<nl; i++) {
      cout << xminLay[i] << " " << xmaxLay[i] << " "
           << yminLay[i] << " " << ymaxLay[i] << " "
           << rhoLay[i] << " " << VpLay[i] << " " << VsLay[i] << endl;
    }
  } else if (nsd == 3) {
    for (i=0; i<nl; i++) {
      lf >> xminLay[i] >> xmaxLay[i]
         >> yminLay[i] >> ymaxLay[i]
         >> zminLay[i] >> zmaxLay[i]
         >> rhoLay[i] >> VpLay[i] >> VsLay[i];
      getline(lf, buffer);
    }
    for (i=0; i<nl; i++) {
      cout << xminLay[i] << " " << xmaxLay[i] << " "
           << yminLay[i] << " " << ymaxLay[i] << " "
           << zminLay[i] << " " << zmaxLay[i] << " "
           << rhoLay[i] << " " << VpLay[i] << " " << VsLay[i] << endl;
    }
  }

  // Get the mesh file
  ifstream mf(fname_mesh);
  if (!mf) {
    cerr << "Could not open mesh file " << fname_mesh << endl;
  }

  getline(mf, buffer); // skip this line
  cout << buffer << endl;

  mf >> ne >> nsd;
  getline(mf, buffer); // First element id and type
  cout << buffer << endl;

  cout << "Number of elements = " << ne << " Dimension = "<<nsd<< endl;

  fprintf(fp,"**EARTH MODEL**\n");
  fprintf(fp,"elementwise\n");
  fprintf(fp,"%d\n",ne);
  fprintf(fp,"%16.9e %16.9e  %16.9e\n",rhoref, Vpref, Vsref);

  vector <double> x(8);
  vector <double> y(8);
  vector <double> z(8);

  if (nsd == 2) {
    nverts = 4;
    for (e=0; e<ne; e++) {
      getline(mf,buffer);  // get element coordinates
      for (i=0; i<nverts; i++) mf >> x[i];
      getline(mf,buffer);
      for (i=0; i<nverts; i++) mf >> y[i];
      getline(mf,buffer);
      xmin = xmax = x[0];
      ymin = ymax = y[0];
      for (i=1; i<nverts; i++){
        if (x[i] < xmin) xmin = x[i];
        if (x[i] > xmax) xmax = x[i];
        if (y[i] < ymin) ymin = y[i];
        if (y[i] > ymax) ymax = y[i];
      }

      bool efound = false;
      for (l=0; l<nl; l++) {
       if ( xmin >= xminLay[l] && xmax <= xmaxLay[l] &&
            ymin >= yminLay[l] && ymax <= ymaxLay[l]    ) {
          rho = rhoLay[l];
          Vp  = VpLay[l];
          Vs  = VsLay[l];
          efound = true;
        }
        if (efound) break;
      }

      fprintf(fp,"%d %16.9e %16.9e %16.9e\n",e, rho, Vp, Vs);
    }
  } else if (nsd == 3) {
    nverts = 8;
    for (e=0; e<ne; e++) {
      getline(mf,buffer);  // get element coordinates
      for (i=0; i<nverts; i++) mf >> x[i];
      getline(mf,buffer);
      for (i=0; i<nverts; i++) mf >> y[i];
      getline(mf,buffer);
      for (i=0; i<nverts; i++) mf >> z[i];
      getline(mf,buffer); // element id and type
      xmin = xmax = x[0];
      ymin = ymax = y[0];
      zmin = zmax = z[0];
      for (i=1; i<nverts; i++){
        if (x[i] < xmin) xmin = x[i];
        if (x[i] > xmax) xmax = x[i];
        if (y[i] < ymin) ymin = y[i];
        if (y[i] > ymax) ymax = y[i];
        if (z[i] < zmin) zmin = z[i];
        if (z[i] > zmax) zmax = z[i];
      }

      bool efound = false;
      for (l=0; l<nl; l++) {
       if ( xmin >= xminLay[l] && xmax <= xmaxLay[l] &&
            ymin >= yminLay[l] && ymax <= ymaxLay[l] &&
            zmin >= zminLay[l] && zmax <= zmaxLay[l]    ) {
          rho = rhoLay[l];
          Vp  = VpLay[l];
          Vs  = VsLay[l];
          efound = true;
        }
        if (efound) break;
      }

      fprintf(fp,"%d %16.9e %16.9e %16.9e\n",e, rho, Vp, Vs);
    }
  }

  fclose(fp);
}

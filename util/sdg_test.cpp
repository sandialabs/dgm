// Author: K. Noel Belcourt

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <SubdomainGrouping.hpp>

// compile using
// g++ -g -I ../src sdg_test.cpp

using std::cout;
using std::endl;

// takes 4 optional arguments
// argv[1] == angle to rotate box through
// argv[2] == box size
// argv[3] == x coordinate of box origin
// argv[4] == y coordinate of box origin
int main(int argc, char** argv) {
  using boost::lexical_cast;
  using DGM::box_2d;
  // 2d test
  double angle = 2 <= argc ? lexical_cast<double>(argv[1]) : 10;
  double pi = 4.0*atan(1.0);  // rotate box this many degrees clockwise
  double theta = angle * pi / 180.;  // rotate box this many degrees clockwise
  double size = 3 <= argc ? lexical_cast<double>(argv[2]) : 5;
  double ll[] = { 0.0, 0.0 };
  if (5 <= argc) {
    ll[0] = lexical_cast<double>(argv[3]);
    ll[1] = lexical_cast<double>(argv[4]);
  }
  double lr[] = { ll[0]+size, ll[1] };
  double ur[] = { lr[0], lr[1]+size };
  double ul[] = { ll[0], ll[1]+size };
  // rotate points by theta
  // lower left
  double llx = ll[0]*cos(theta)-ll[1]*sin(theta);
  double lly = ll[0]*sin(theta)+ll[1]*cos(theta);
  // lower right
  double lrx = lr[0]*cos(theta)-lr[1]*sin(theta);
  double lry = lr[0]*sin(theta)+lr[1]*cos(theta);
  // upper right
  double urx = ur[0]*cos(theta)-ur[1]*sin(theta);
  double ury = ur[0]*sin(theta)+ur[1]*cos(theta);
  // upper left
  double ulx = ul[0]*cos(theta)-ul[1]*sin(theta);
  double uly = ul[0]*sin(theta)+ul[1]*cos(theta);
  // coordinates of rotated box passed in
  cout << "Rotated coordinates" << endl;
  cout << "box(llx,lly) = " << llx << "," << lly << endl;
  cout << "box(lrx,lry) = " << lrx << "," << lry << endl;
  cout << "box(ulx,uly) = " << ulx << "," << uly << endl;
  cout << "box(urx,ury) = " << urx << "," << ury << endl;
  // construct 2d subdomain box
  box_2d<double, int> test(1, llx, lly, lrx, lry, ulx, uly, urx, ury);
  cout << "Unrotated coordinates" << endl;
  cout << "xmin,xmax = [" << test.xmin << "," << test.xmax << "]" << endl;
  cout << "ymin,ymax = [" << test.ymin << "," << test.ymax << "]" << endl;
  // check the rotation angle
  return 0;
}

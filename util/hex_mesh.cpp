/*=============================================================================
  Title:      Refine2D 

  Contact:    S. Scott Collis
              Sandia National Laboratories
              Albuquerque, NM 87175
              (505) 284-1123
              sscoll@sandia.gov

  Copyright:  (c)2016 Sandia National Laboratories
=============================================================================*/


#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <array>
#include <ctime>
#include <map>
#include <set>

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/numeric/conversion/cast.hpp>



typedef unsigned long long UInt;
typedef long double        Real;

struct options {
  const bool pause;
  const bool sanity_check;
  const bool ascii;
  const bool binary;
  const bool spectral;
  const std::string root;
  const std::array<UInt,3> N;
  const std::array<Real,3> L;
  const std::array<Real,3> O;
  options (const bool p, const bool c, 
           const bool a, const bool b, 
           const bool s, const std::string r,
           const std::array<UInt,3> n,
           const std::array<Real,3> l, 
           const std::array<Real,3> o) 
    : pause(p), sanity_check(c), ascii(a), binary(b), spectral(s),
      root(r), N(n), L(l), O(o) {}
};


namespace {
options parse_command_line(int argc, char *argv[]) {
  using namespace boost::program_options;

  options_description desc(std::string("Allowed options"));
  desc.add_options()
    ("help", "product help message")
    ("pause", "Pause until keyboard input.")
    ("r", value<std::string>()->default_value("ref"), "Base name of mesh files")
    ("nsd", value<UInt>()->default_value(3),"Ignored. Spatial dimension, only valid value is 3.")
    ("nx", value<UInt>()->default_value(2), "Elements in x")
    ("ny", value<UInt>()->default_value(2), "Elements in x")
    ("nz", value<UInt>()->default_value(2), "Elements in x")
    ("Lx", value<Real>()->default_value(2), "Length in x")
    ("Ly", value<Real>()->default_value(2), "Length in y")
    ("Lz", value<Real>()->default_value(2), "Length in z")
    ("x0", value<Real>()->default_value(0), "x offset")
    ("y0", value<Real>()->default_value(0), "y offset")
    ("z0", value<Real>()->default_value(0), "z offset")
    ("ascii", value<bool>()->default_value(true), "ASCII mesh output") 
    ("binary",value<bool>()->default_value(true),  "Binary mesh output.")
    ("spectral", "Output spectral elements.")
    ("non-periodic", "Ignored.  Only kind supported.")
    ("low-memory", "Ignored.  Only kind supported.");
  positional_options_description p;
  p.add("root", -1);

  variables_map vm;
  store(command_line_parser(argc, argv)
        .options(desc)
        .style(command_line_style::unix_style|
               command_line_style::allow_long_disguise|
               command_line_style::unix_style)
        .positional(p)
        .run(), vm);
  notify(vm);
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    exit(0);
  }
  if (vm.count("sanity_check"))
   std::cout<<" sanity_check flag set."<<std::endl;


  if (vm.count("spectral"))
   std::cout<<" spectral flag set."<<std::endl;

  const std::string root = vm["r"].as<std::string>();
  const UInt         nsd = vm["nsd"].as<UInt>();
  const UInt          nx = vm["nx"].as<UInt>();
  const UInt          ny = vm["ny"].as<UInt>();
  const UInt          nz = vm["nz"].as<UInt>();
  const Real          Lx = vm["Lx"].as<Real>();
  const Real          Ly = vm["Ly"].as<Real>();
  const Real          Lz = vm["Lz"].as<Real>();
  const Real          x0 = vm["x0"].as<Real>();
  const Real          y0 = vm["y0"].as<Real>();
  const Real          z0 = vm["z0"].as<Real>();
  const std::array<UInt,3> N={nx,ny,nz};
  const std::array<Real,3> L={Lx,Ly,Lz};
  const std::array<Real,3> O={x0,y0,z0};
  const bool ascii = vm["ascii"].as<bool>();
  const bool binary= vm["binary"].as<bool>();
  options opt(vm.count("pause"),
              vm.count("sanity_check"),
              ascii, binary,
              vm.count("spectral"),
              root,N,L,O);
  std::cout<<" Command line options, with defaults:"
    <<" -r "<<root
    <<" -nx "<<nx
    <<" -ny "<<ny
    <<" -nz "<<nz
    <<" -Lx "<<Lx
    <<" -Ly "<<Ly
    <<" -Lz "<<Lz
    <<" -ascii "<<ascii
    <<" -binary "<<binary
    <<std::endl;
  if (nsd!=3) std::cerr<<" Only -ssd 3 is currently supported"<<std::endl;
  return opt;
}

struct Gid {
  const std::array<UInt,3> L;
  Gid (const std::array<UInt,3> &l) : L(l) {}
  UInt operator()(const UInt i, const UInt j, const UInt k) const {
    const UInt gid = i + L[0]*j + L[0]*L[1]*k;
    return gid;
  } 
};

std::string form_header(const std::string  &mesh_file, 
                        const UInt nelem) { 
  std::time_t rawtime;
  std::time (&rawtime);
  boost::property_tree::ptree pt;
  pt.put("Date", std::ctime(&rawtime));
  pt.put("Name", mesh_file);
  pt.put("Nel", nelem);
  pt.put("Nsd", 2);
  pt.put("Types.ByteOrder",  "LittleEndian");
  pt.put("Types.GlobalSize", "int32");
  pt.put("Types.LocalSize",  "int32");
  pt.put("Types.Scalar",     "float64");
  pt.put("Version", 1.0);
  std::ostringstream ostr;
  boost::property_tree::json_parser::write_json(ostr, pt, true);
  const std::string header = ostr.str(); 
  return header;
}
}

int main(int argc, char *argv[]) {
  
  std::clock_t timer = clock();

  namespace po=boost::program_options;

  options opt = parse_command_line(argc, argv);
  if (opt.pause) {
    std::cout << "Press enter to continue ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }   


  const std::string element_type= opt.spectral ? "SPECTRALHEX" : "HEX";

  const UInt nx = opt.N[0];
  const UInt ny = opt.N[1];
  const UInt nz = opt.N[2];
  const Real Lx = opt.L[0];
  const Real Ly = opt.L[1];
  const Real Lz = opt.L[2];
  const Real x0 = opt.O[0];
  const Real y0 = opt.O[1];
  const Real z0 = opt.O[2];
  const std::array<Real,3> Xinc={Lx/nx, Ly/ny, Lz/nz};

  const UInt nelem = nx*ny*nz;
  const Gid gid(opt.N);
  static const std::array<Real,8> Px = {0,1,1,0,0,1,1,0};
  static const std::array<Real,8> Py = {0,0,1,1,0,0,1,1};
  static const std::array<Real,8> Pz = {0,0,0,0,1,1,1,1};
  static const std::array<std::array<Real,8>,3> P =  {Px, Py, Pz};


  if (opt.ascii) {
    const std::string mesh_file = opt.root+".msh";
    std::ofstream msh_out(mesh_file);
    msh_out <<"# MESH DATA "<<"\n";
    msh_out <<nelem<<" "<<3<<" NE NSD\n";

    std::array<std::array<Real,8>,3> X;
    std::array<Real,3> Xo;
    for (UInt iz=0; iz<nz; ++iz) {
      Xo[2] = z0 + iz*Lz/nz;
      for (UInt iy=0; iy<ny; ++iy) {
        Xo[1] = y0 + iy*Ly/ny;
        for (UInt ix=0; ix<nx; ++ix) {
          Xo[0] = x0 + ix*Lx/nx;
          for (UInt i=0; i<3; ++i) {
            for (UInt j=0; j<8; ++j) {
              X[i][j] = Xo[i] + P[i][j]*Xinc[i];
            }
          }
          msh_out << "ELEMENT "<< gid(ix,iy,iz)<<" "<<element_type<<'\n';
          for (UInt i=0; i<3; ++i) {
            for (UInt j=0; j<8; ++j) {
              msh_out << std::setprecision(16) << X[i][j] <<" ";
            }
            msh_out <<'\n';
          }
        }
      }
    } 
    msh_out.close();

    const std::string con_file = opt.root+".con";
    std::ofstream con_out(con_file);
    con_out <<"# CONNECTIVITY DATA "<<"\n";
    con_out <<nx*ny*nz<<" ne\n";

    for (UInt iz=0; iz<nz; ++iz) {
      for (UInt iy=0; iy<ny; ++iy) {
        for (UInt ix=0; ix<nx; ++ix) {
          if (iz)      con_out << "E "<< gid(ix,iy,iz)<<" 0 "<<gid(ix,iy,iz-1)<<" 5\n";
          if (iy)      con_out << "E "<< gid(ix,iy,iz)<<" 1 "<<gid(ix,iy-1,iz)<<" 3\n";
          if (ix<nx-1) con_out << "E "<< gid(ix,iy,iz)<<" 2 "<<gid(ix+1,iy,iz)<<" 4\n";
          if (iy<ny-1) con_out << "E "<< gid(ix,iy,iz)<<" 3 "<<gid(ix,iy+1,iz)<<" 1\n";
          if (ix)      con_out << "E "<< gid(ix,iy,iz)<<" 4 "<<gid(ix-1,iy,iz)<<" 2\n";
          if (iz<nz-1) con_out << "E "<< gid(ix,iy,iz)<<" 5 "<<gid(ix,iy,iz+1)<<" 0\n";
        }
      }
    } 
    con_out.close();
  }

  if (opt.binary) {
    const std::string grid_file = opt.root+".grd";
    const std::string grid_header = form_header(grid_file, nelem);
    std::ofstream grd_header_out(grid_file);
    grd_header_out << grid_header;
    grd_header_out.close();

    const int int_nelem = boost::numeric_cast<int>(nelem);
    const int       dim = 3;
    const int    ncoord = 8*nelem;
    const int      type = opt.spectral ?  13 : 3;;
    std::ofstream grd_out(grid_file,
                          std::ios::out | std::ios::app | std::ios::binary);
    grd_out.write(reinterpret_cast<const char*>(&nelem),  sizeof(int));
    grd_out.write(reinterpret_cast<const char*>(&dim),    sizeof(int));
    grd_out.write(reinterpret_cast<const char*>(&ncoord), sizeof(int));
    for (UInt i=0; i<nelem; ++i) 
      grd_out.write(reinterpret_cast<const char*>(&type), sizeof(int));
    for (int disp=0,i=0; i<nelem; ++i, disp+=8)
      grd_out.write(reinterpret_cast<const char*>(&disp), sizeof(int));

    std::array<Real,3> Xo;
    std::vector<double> C(8*nx*ny);
    for (UInt iz=0,k=0; iz<nz; ++iz) {
      for (UInt iy=0; iy<ny; ++iy) {
        for (UInt ix=0; ix<nx; ++ix) {
          Xo[0] = x0 + ix*Lx/nx;
          for (UInt j=0; j<8; ++j,++k) {
            C[k] = Xo[0] + P[0][j]*Xinc[0];
          }
        }
      }
      grd_out.write(reinterpret_cast<const char*>(C.data()), 8*nx*ny*sizeof(double));
      k=0;
    }
    for (UInt iz=0,k=0; iz<nz; ++iz) {
      for (UInt iy=0; iy<ny; ++iy) {
        Xo[1] = y0 + iy*Ly/ny;
        for (UInt ix=0; ix<nx; ++ix) {
          for (UInt j=0; j<8; ++j,++k) {
            C[k] = Xo[1] + P[1][j]*Xinc[1];
          }
        }
      }
      grd_out.write(reinterpret_cast<const char*>(C.data()), 8*nx*ny*sizeof(double));
      k=0;
    }
    for (UInt iz=0,k=0; iz<nz; ++iz) {
      Xo[2] = z0 + iz*Lz/nz;
      for (UInt iy=0; iy<ny; ++iy) {
        for (UInt ix=0; ix<nx; ++ix) {
          for (UInt j=0; j<8; ++j,++k) {
            C[k] = Xo[2] + P[2][j]*Xinc[2];
          }
        }
      }
      grd_out.write(reinterpret_cast<const char*>(C.data()), 8*nx*ny*sizeof(double));
      k=0;
    }
    grd_out.close();
    C.clear();
   
    const std::string con_file = opt.root+".cn";
    const std::string con_header = form_header(con_file, nelem);
    std::ofstream con_header_out(con_file);
    con_header_out << con_header;
    con_header_out.close();

    std::ofstream con_out(con_file,
                          std::ios::out | std::ios::app | std::ios::binary);
    std::vector<int> L(nelem,0);
    std::vector<int> D(nelem,0);

    for (UInt iz=0,k=0; iz<nz; ++iz) {
      for (UInt iy=0; iy<ny; ++iy) {
        for (UInt ix=0; ix<nx; ++ix,++k) {
          if (iz)      ++L[k];
          if (iy)      ++L[k]; 
          if (ix<nx-1) ++L[k]; 
          if (iy<ny-1) ++L[k]; 
          if (ix)      ++L[k]; 
          if (iz<nz-1) ++L[k]; 
        }
      }
    }
    for (UInt i=1; i<L.size(); ++i) D[i] = D[i-1] + L[i-1];
    con_out.write(reinterpret_cast<const char*>(D.data()), nelem*sizeof(int));
    con_out.write(reinterpret_cast<const char*>(L.data()), nelem*sizeof(int));
    D.clear();
    L.clear();
    
    std::vector<int> GID[3][2];
    for (UInt i=0; i<3; ++i) for (UInt j=0; j<2; ++j) GID[i][j].resize(nx*ny);
    std::array<int,5> to_file;
    UInt cur_gid=0;
    for (UInt iz=0,k=0; iz<nz; ++iz) {
      for (UInt iy=0; iy<ny; ++iy) {
        for (UInt ix=0; ix<nx; ++ix,++k) {
          to_file[0] = gid(ix,iy,iz);
          if (iz) {
            to_file[2] = gid(ix,iy,iz-1);
            to_file[1] = 0; to_file[3] = 5;             
            to_file[4] = GID[0][0][ix + iy*nx];
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
          if (iy) {
            to_file[2] = gid(ix,iy-1,iz);
            to_file[1] = 1; to_file[3] = 3;             
            to_file[4] = GID[1][1][ix + (iy-1)*nx];
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
          if (ix<nx-1) {
            to_file[2] = gid(ix+1,iy,iz);
            to_file[1] = 2;  to_file[3] = 4;             
            to_file[4] = cur_gid;
            GID[2][1][ix + iy*nx] = cur_gid;
            ++cur_gid;
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
          if (iy<ny-1) {
            to_file[2] = gid(ix,iy+1,iz);
            to_file[1] = 3; to_file[3] = 1;             
            to_file[4] = cur_gid;
            GID[1][1][ix + iy*nx] = cur_gid;
            ++cur_gid;
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
          if (ix) {
            to_file[2] = gid(ix-1,iy,iz);
            to_file[1] = 4; to_file[3] = 2;             
            to_file[4] = GID[2][1][ix-1 + iy*nx];
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
          if (iz<nz-1) {
            to_file[2] = gid(ix,iy,iz+1);
            to_file[1] = 5; to_file[3] = 0;             
            to_file[4] = cur_gid;
            GID[0][1][ix + iy*nx] = cur_gid;
            ++cur_gid;
            con_out.write(reinterpret_cast<const char*>(to_file.data()), 5*sizeof(int));
          }
        }
      }
      GID[0][0].swap(GID[0][1]);
      GID[1][0].swap(GID[1][1]);
      GID[2][1].swap(GID[2][1]);
    }
  }

  timer = clock() - timer;
  std::cout <<std::endl
            <<" Total run time in seconds: "
            << static_cast<double>(timer)/CLOCKS_PER_SEC << std::endl;
}


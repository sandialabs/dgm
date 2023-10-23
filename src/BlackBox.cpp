/** \file BlackBox.cpp
    \brief Black box interface implementation to the DGM Optimizer
    \author Scott Collis
*/

// System includes
#include <ctime>

// DGM includes
#include "Comm.hpp"
#include "BlackBox.hpp"
#include "Format.hpp"
#include "Info.hpp"

#ifdef DGM_DOXYGEN
/// Define if the system does not support the strftime command
#define DGM_NO_TIME
#endif

namespace DGM {

/// Blackbox constructor
/** This is the simpliest black-box type interface to the DGM::Optimizer
    \param[in] state_ The state object
    \param[in] adjoint_ The adjoint object
    \param[in] control_ The control object
    \param[in] comm_ The communicator
*/
BlackBox::BlackBox(State* state_, Adjoint* adjoint_,
                   Control::Ptr control_, const DGM::Comm::Ptr comm_) :
  Optimizer(state_, adjoint_, control_, comm_), asv(0),
  total_g(0.0) {

  comm->cout()<<"BlackBox() construction..."<<endl;

  gradient.reset(control->clone());
  gradient->control_type(Control::GRADIENT);
  gradient->zero();

#ifdef DGM_USE_TIME_REG
  gt_control.reset(control->clone());
  gt_control->control_type(Control::GRADIENT);
  gt_control->zero();
#endif

  // set default values
  params["asv"] = Ordinal(1);  // active set vector (evaluate function)
  params["npredict"] = Ordinal(100);    // predictive steps
  params["nadvance"] = Ordinal(100);    // after-control advance step

  // read parameters from an input file
  root = control->root;
  params.read( root+".inp" );

  // override parameters from the argument list
  parse_args( state->domain()->get_args() );

  // initilization from parameter table
  asv      = params["asv"];
  npredict = params["npredict"];
  nadvance = params["nadvance"];

  // prepare optimization history file
  if (comm->Master()) {
    string objname = root+".ocs";
    if (opt_stat==NULL)
      opt_stat = fopen(objname.c_str(),"a+");
  }

  state->initialize();
  control->initialize();
  adjoint->initialize();
}

/// Override parameters from the argument list
void BlackBox::parse_args( ArgList &args ) {
  string name, value;

  // get basic information from argument list
  const string code = args.front();
  if (args.size() < 2) {
    showUsage(code);
    exit(DGM::SUCCESS);
  }
  const string root = args.back();

  list< DGM::ArgList::iterator > li;
  for ( DGM::ArgList::iterator a = args.begin(); a != args.end(); a++ ) {
    if ( (*a)[0] == '-' ) {
      name = *a;
      if (name == "-help") {
        params["showUsage"] = 1;
        showUsage(code);
      } else if (name == "-asv") {
        li.push_back(a);
        value = *(++a);
        li.push_back(a);
        params["asv"] = atoi(value.c_str());
      }
    }
  }
#ifdef DGM_REMOVE_ARGUMENTS
  // remove tagged arguments
  for ( list< DGM::ArgList::iterator >::iterator a=li.begin();
        a!=li.end(); a++) args.erase(*a);
#endif
}

/// Output the usage for this object
void BlackBox::showUsage(const string &code) const {
  comm->cerr()
    << "BlackBox Optimizer Class Options \n"
    << "---------------------------------------------------------------\n"
    << "-asv " << '\t' << "Active set vector                           \n"
    << "---------------------------------------------------------------\n";
}

/** There is no gradient check implement for this optimizer. */
void BlackBox::check_grad() {
  comm->cout()<<"BlackBox::check_grad() is not supported"<<endl;
}

/** Evalute the objective function, gradient, and Hessian based on the
    value of the active set vector
    \param[in] asv_ Active Set Vector
*/
void BlackBox::optimize(const Ordinal asv_) {

  if (asv_) asv = asv_;

  static Format sci(8); sci.scientific().width(15);

  comm->cout()<<"BlackBox::optimize() with ASV = " << asv << endl;

  timer.start();

  if ((asv & 1) || (asv & 2)) {
    //state->initialize();
    //control->initialize();
    state->set_initial_condition();
    if ((asv & 2) || (asv & 4))
      state->save();
    else
      state->no_save();
    total_j = state->compute(npredict, control);
    if (asv & 1)
      if (comm->Master()) {
        fprintf(opt_stat,"%23.16e\n", total_j);
        fflush(opt_stat);
      }
  }
  if (asv & 2) {
    //adjoint->initialize();
    adjoint->set_end_condition();
    adjoint->compute( npredict, control, gradient, 1 );
    total_g = gradient->norm();
    comm->cout()<<"||Grad(J)|| = "<<sci(total_g)<<endl;
    gradient_norms.resize(numeric_cast<Ordinal>(gradient->num_ctrl()));
    gradient_norms = gradient->norms();
    vector<string> names(gradient->names());
    for (Ordinal i=0; i<gradient_norms.size(); ++i)
      comm->cout()<<"  ||dJ/d(" << names[i] << ")|| = "
                  <<sci(gradient_norms[i])<<endl;
    dVector gphi(gradient->get_glen());
    gradient->gather( gphi );
    if (comm->Master()) {
      fprintf(opt_stat,  "[ %23.16e ", gphi[0]);
      for (dVector::size_type i=1; i<gphi.size(); ++i)
        fprintf(opt_stat,"  %23.16e ", gphi[i]);
      fprintf(opt_stat,"]\n");
      fflush(opt_stat);
    }
  }
  if (asv & 4) {
    comm->cout()<<"BlackBox:  Hessian not supported"<<endl;
  }
  // write the control restart file
  writeRestart();
  iter++;
  comm->cout()<<"BlackBox::optimize() completed with ASV = "<<asv<<endl;
}

/** This is a null-op for now. */
Scalar BlackBox::advance(const Ordinal outer) {
  return 0.0;
}

//==============================================================================
//                     Original Optimization Headers
//==============================================================================

/// Write the optimization restart file header
streamoff BlackBox::writeHeader(const string &fname) const {
  const int verb=0;
  streamoff disp=0;
#ifndef DGM_NO_CONTROL_HEADER
  const int width = 40;
  if (comm->Master()) {
    // get the current date and time from <time.h>
    char now[128]="Time is not available";
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
    time_t tp = time(0);
    strftime(now,128,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
    ofstream res_out(fname.c_str());
    res_out.setf(ios::left);
    res_out<<setw(width)<<now<<" Created"<<endl;
    res_out<<setw(width)<<fname.c_str()<<" Name"<<endl;
    res_out<<setw(width)<<iter<<" Iteration"<<endl;
    res_out<<setw(width)<<"<unused>"<<endl;
    res_out<<setw(width)<<total_g<<" Gradient L2 norm"<<endl;
    res_out<<setw(width)<<(npredict+1)<<" Time steps"<<endl;
    res_out<<setw(width)<<asv<<" Active set vector"<<endl;
    res_out<<setw(width)<<"<unused>"<<endl;  // make header 10 lines
    res_out<<setw(width)<<"<unused>"<<endl;
    res_out<<setw(width)<<"BlackBox"<<" Optimizer"<<endl;
    disp = res_out.tellp();     // get the header length (in bytes)
    res_out.close();
  }
  const int stat = comm->Broadcast(&disp);
  if (stat)
    comm->error("Blackbox::writeHeader: Error in broadcast of skip");
  if (verb)
    comm->cout()<<"Wrote control restart header of length "<<disp<<endl;
#else
  disp = 0;
#endif
  return disp;
}

/// Read the optimization restart file header
streamoff BlackBox::readHeader(const string &fname, Ordinal &riter,
                               Ordinal &rasv) {
  const int verb=0;
  streamoff skip;
#ifndef DGM_NO_CONTROL_HEADER
  ifstream res_in(fname.c_str());
  if (!res_in) {
    timer.reset();
    riter = 0;
    return 0;
  }
  string buf;
  getline(res_in,buf);
  if (!(res_in>>buf)) error("Cannot read restart name");
  getline(res_in,buf);
  if (!(res_in>>riter)) error("Cannot read iteration number");
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  if (!(res_in>>rasv)) error("Cannot read the active set vector");
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  getline(res_in,buf);
  skip = res_in.tellg();                 // get the header length (in bytes)
  if (verb)
    comm->cout() << "Read control restart header of length = " <<skip<<endl;
#else
  riter = 1;
  skip = 0;
#endif
  return skip;
}

/// This is the new version of writeHeader
streamoff BlackBox::outputHeader(const string &fname) const {
  return writeJsonHeader(fname);
}

//==============================================================================
//                       JSON Optimization Headers
//==============================================================================

/// Write a Json header
streamoff BlackBox::writeJsonHeader(const string &fname) const {
  const int verb=comm->verbosity();
  if (verb) comm->cout()<<"BlackBox::writeJsonHeader("<<fname<<")"<<endl;
  streamoff disp=0;
  const int buflen=128;
  char now[buflen] = "Time is not available";
  if (comm->Master()) {
    ofstream fs(fname.c_str());
    if (!fs) throw DGM::exception("BlackBox::writeJsonHeader could not "
                                  "open file name "+fname);
#if !defined(DGM_REDSTORM) && !defined(DGM_NO_TIME)
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %H:%M:%S %Y", localtime(&tp));
#endif
    Json::Value header;
    header["File created"] = now;
    header["Root file name"] = root;
    header["Number of processors"] = comm->NumProc();
    header["Restart file name"] = fname;
    header["Executable"] = control->code;

    header["DGM library"] = Json::Value(Json::objectValue);
    header["DGM library"]["Version"] = DGM::Comm::information.version();
    header["DGM library"]["Build date"] = DGM::Comm::information.date();
    header["DGM library"]["Build time"] = DGM::Comm::information.time();
    header["DGM library"]["Compiler"] = DGM::Comm::information.compiler();
    header["DGM library"]["Host name"] = DGM::Comm::information.hostname();
    header["DGM library"]["System"] = DGM::Comm::information.system();

    header["Iteration"] = iter;
    header["Wall time"] = timer.read();
    header["Objective function"] = total_j;
    if (asv & 2)
      header["Norm of the gradient"] = total_g;
    header["Npredict"] = npredict;
    header["Time steps"] = npredict + 1;
    header["Number of State solves"] = state->num();
    header["Number of Adjoint solves"] = adjoint->num();

    header["BlackBox"] = Json::Value(Json::objectValue);
    header["BlackBox"]["Active set vector"] = asv;
    if ((asv & 1) || (asv & 2))
      header["BlackBox"]["J"] = total_j;
    if (asv & 2) {
      header["BlackBox"]["||Grad(J)||"] = total_g;
      header["BlackBox"]["||dJ/dphi_i||"] = Json::Value(Json::arrayValue);
      header["BlackBox"]["||dJ/dphi_i||"].resize(
        numeric_cast<Json::ArrayIndex>(gradient_norms.size()));
      for (Ordinal i=0; i<gradient_norms.size(); ++i) {
        const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(i);
        header["BlackBox"]["||dJ/dphi_i||"][m] = gradient_norms[i];
      }
    }

    // control information
    header["Control"] = Json::Value(Json::objectValue);
    header["Control"]["Number"] = control->num_ctrl();
    vector<string> names = control->names();
    header["Control"]["Names"] = Json::Value(Json::arrayValue);
    header["Control"]["Names"].resize(
      numeric_cast<Json::ArrayIndex>(names.size()));
    for (size_t i=0; i<names.size(); ++i) {
      const Json::ArrayIndex m = numeric_cast<Json::ArrayIndex>(i);
      header["Control"]["Names"][m] = names[i];
    }
    header["Control"]["Global control length"] = control->global_size();

    // type information
    header["Types"] = Json::Value(Json::objectValue);
    header["Types"]["GlobalSize"] = type<DGM::Size>();
    header["Types"]["LocalSize"] = type<DGM::Ordinal>();
    header["Types"]["Scalar"] = type<DGM::Scalar>();
    DGM::ByteOrder byteOrder;
    header["Types"]["ByteOrder"] = byteOrder.asString();

    Json::StyledWriter writer;
    string output = writer.write(header);
    if (!fs)
      throw DGM::exception("BlackBox::writeJsonHeader file stream in bad "
                           "state for restart file "+fname);
    fs << output;
    if (!fs) throw DGM::exception("BlackBox::writeJsonHeader could not "
                                  "write header to restart file "+fname);
    disp = fs.tellp();
  }
  const int stat = comm->Broadcast(&disp);
  if (stat) throw DGM::exception("BlackBox::writeJsonHeader: error in "
                                 "broadcast of displacement");
  if (verb>2)
    comm->cout() << "BlackBox::writeJsonHeader("<<fname
                 <<") completed with disp = " << disp <<" bytes" << endl;
  return disp;
}

/// Read a Json header
streamoff BlackBox::readJsonHeader(const string &fname, Ordinal &riter,
                                   Ordinal &rasv) {
  const int verb=0;
  if (verb>1) comm->cout()<<"BlackBox::readJsonHeader("<<fname<<")"<<endl;
  ifstream fs(fname.c_str());
  if (!fs) {
    timer.reset();
    riter = 0;
    return 0;
  }
  char c = fs.peek();
  if (!fs) throw DGM::exception("Cannot read Json header from "+fname);
  if (c!='{') {
    return readHeader(fname,riter,rasv);
  } else {
    string token;
    if (!(fs >> token))
      throw DGM::exception("Error reading Json header from "+fname);
  }
  Json::Value header;
  string buffer = read_block(fs);
  const int status = scan_rb(fs);
  if (status) comm->error("Could not find closing bracket for Json header "
                          " on file "+fname);
  if (verb>2)
    comm->cout() << "Read header from " << fname << "\n" << buffer << endl;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse( buffer, header, true );
  if (!parsingSuccessful)
    comm->error("BlackBox readJsonHeader could not parse input from "+
                fname+"\n"+reader.getFormattedErrorMessages());
  getline(fs,buffer);
  if (fs.fail())
    throw DGM::exception("Could not read Json data from file "+fname);
  if (fs.bad())
    throw DGM::exception("Stream is bad when reading Json data "
                         "from file "+fname);
  if (fs.eof())
    throw DGM::exception("End of file encountered when reading from "+fname);

  // extract information from Json header
  if (!header.isMember("Iteration"))
    throw DGM::exception("Header is missing \"Iteration\" from file "+fname);
  riter = numeric_cast<Ordinal>(header["Iteration"].asUInt64());

  if (!header.isMember("Wall time"))
    throw DGM::exception("Header is missing \"Wall time\" from file "+fname);
  timer.reset(header["Wall time"].asDouble());

  if (!header.isMember("Number of State solves"))
    state->num(0);
  else
    state->num(numeric_cast<Ordinal>(
               header["Number of State solves"].asUInt64()));

  if (!header.isMember("Number of Adjoint solves"))
    adjoint->num(0);
  else
    adjoint->num(numeric_cast<Ordinal>(
               header["Number of Adjoint solves"].asUInt64()));

  if (!header.isMember("Objective function"))
    throw DGM::exception("Header is missing \"Objective function\" "
                         "from file "+fname);
  total_j = numeric_cast<Scalar>(header["Objective function"].asDouble());

  // BlackBox block
  if (!header.isMember("BlackBox"))
    throw DGM::exception("Header missing \"BlackBox\" block from file "+fname);
  Json::Value &blackbox = header["BlackBox"];
  if (!blackbox.isMember("Active set vector"))
    throw DGM::exception("Header is missing \"Active set vector\""
                         " from file "+fname);
  rasv = numeric_cast<Ordinal>(blackbox["Active set vector"].asInt());

  // Types block
  if (!header.isMember("Types"))
    throw DGM::exception("Header missing \"Types\" block from "
                         "file "+fname);
  Json::Value &types = header["Types"];
  if (!types.isMember("GlobalSize"))
    throw DGM::exception("Header is missing \"GlobalSize\""
                         " from file "+fname);
#if 0
  if (types["GlobalSize"].asString() != type<DGM::Size>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "GlobalSize = "+types["GlobalSize"].asString()+
                         "\n  while code expects "+type<DGM::Size>());
#endif
  if (!types.isMember("LocalSize"))
    throw DGM::exception("Header is missing \"LocalSize\""
                         " from file "+fname);
#if 0
  if (types["LocalSize"].asString() != type<DGM::Ordinal>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "LocalSize = "+types["LocalSize"].asString()+
                         "\n  while code expects "+type<DGM::Ordinal>());
#endif
  if (!types.isMember("Scalar"))
    throw DGM::exception("Header is missing \"Scalar\""
                         " from file "+fname);
  if (types["Scalar"].asString() != type<DGM::Scalar>() )
    throw DGM::exception("Control restart file "+fname+" is incompatible: "
                         "Scalar = "+types["Scalar"].asString()+
                         "\n  while code expects "+type<DGM::Scalar>());
  // check the byte order
  if (types.isMember("ByteOrder")) {
    DGM::ByteOrder byteOrder;
    if (!byteOrder.is(types["ByteOrder"].asString())) {
      throw DGM::exception("Control restart file "+fname+" is incompatible: "
                           "ByteOrder = "+types["ByteOrder"].asString()+
                           "\n  while code expects "+byteOrder.asString());
    }
  }

  streamoff disp = fs.tellg();
  if (verb>2) comm->cout()<<"BlackBox::readJsonHeader("<<fname<<") with "
    "displacement = "<<disp<<endl;
  return disp;
}

//==============================================================================
//                            Restart file I/O
//==============================================================================

/// Make the JSON header the default
#define DGM_USE_JSON_CTL_HEADER

/// Write the optimization restart file
void BlackBox::writeRestart(const string *ctl) const {
  streamoff skip;
  string fname;
  if (ctl)
    fname = *ctl;
  else {
    char tmp[80];
    sprintf(tmp,".%lld",(long long)iter);
    fname = root+tmp+".ctl";
  }
  comm->cout()<<"Writing control restart file "<<fname<<"."<<endl;
#ifdef DGM_USE_JSON_CTL_HEADER
  skip = writeJsonHeader(fname);
#else
  skip = writeHeader(fname);
#endif
  skip = control->write(fname,skip);
  if (asv & 2) skip = gradient->write(fname,skip);
  // might want to return skip here
  if (skip==0) comm->error("BlackBox::writeRestart zero skip");
}

/// Read the optimization restart file
/** In an effort to piggy back this routine for more sophisticated restart
    files, we return the position of the file pointer after
    an initial reading is completed.  This allows us to add information
    to the end of this file and know where it is. */
Ordinal BlackBox::readRestart(streamoff &skip, const string *ctl) {
  Ordinal rasv;
  Ordinal riter;
  string buf, format, fname;
  if (ctl)
    fname = *ctl;
  else
    fname = root+".ctl";
#ifdef DGM_USE_JSON_CTL_HEADER
  skip = readJsonHeader(fname,riter,rasv);
#else
  skip = readHeader(fname,riter,rasv);
#endif
  if (riter==0) return 0;
  comm->cout()<<"Restarting control from "<<fname<<endl;
  skip = control->read(fname,skip);
  if (rasv & 2) skip = gradient->read(fname,skip);
  return riter;
}

/// Read the optimization restart file (original interface)
/** This function preserves the original functionality of the readRestart
    routine where it is called without returning the location
    of the file pointer when complete. */
Ordinal BlackBox::readRestart(const string *ctl) {
  streamoff skip(0);
  return readRestart(skip,ctl);
}

void BlackBox::plotControl(const Ordinal ntout, const Ordinal riter) const {
  control->plot(ntout, riter);
}

void BlackBox::plotGradient(const Ordinal ntout, const Ordinal riter) const {
  string ext("grd");
  gradient->plot(ntout, riter, &ext);
}

int BlackBox::diff(const string& ctl1, const string& ctl2,
                   const Scalar aeps, const Scalar reps) {
  Ordinal riter1 = 0, riter2 = 0;
  streamoff skip1 = 0, skip2 = 0;
  Ordinal rasv1 = 0, rasv2 = 0;
#ifdef DGM_USE_JSON_CTL_HEADER
  skip1 = readJsonHeader(ctl1, riter1, rasv1);
  skip2 = readJsonHeader(ctl2, riter2, rasv2);
#else
  skip1 = readHeader(ctl1, riter1, rasv1);
  skip2 = readHeader(ctl2, riter2, rasv2);
#endif
  // second control
  Control::Ptr control_2(control->clone());
  // read first control
  control->read(ctl1, skip1);
  // read second control
  control_2->read(ctl2, skip2);
  // compute diff
  return control->diff(*control_2, aeps, reps);
}

int BlackBox::sum(const double mult,
                  const vector<Size> &sub_to_mstr, Optimizer *sum_from) {

  BlackBox *optimizer2 = dynamic_cast<BlackBox*>(sum_from);
  if (!optimizer2) 
     throw DGM::exception("BlackBox::sum could not dynamic "
        "cast Optimizer to BlackBox.");

  // second control
  Control* control_2 = optimizer2->getControl();
  // compute sum
  return control->sum(*control_2, mult, sub_to_mstr);
}

int BlackBox::sum(const double mult) {
  const vector<Size> sub_to_mstr;
  // second control
  Control* control_2 = this->getDirControl();
  // compute sum
  return control->sum(*control_2, mult, sub_to_mstr);
}

int BlackBox::ext(const vector<Size> &sub_to_mstr, Optimizer *ext_to) {

  BlackBox *optimizer2 = dynamic_cast<BlackBox*>(ext_to);
  if (!optimizer2) 
     throw DGM::exception("BlackBox::ext could not dynamic "
        "cast Optimizer to BlackBox.");

  // second control
  Control* control_2 = optimizer2->getControl();
  // compute ext
  return control->ext(*control_2, sub_to_mstr);
}

} // namespace DGM

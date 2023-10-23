/** \file Utilities.cpp
    \brief DGM utilities implementation

    There are two versions of this protected tremain_ routine.  The first
    uses the shell command "qstat" while the second uses the PBS-API, and
    therefore must be linked with the libpbs.a library.

    Currently, I prefer the "qstat" version since it doesn't require any
    change to the makefiles or inclusion of the additional library.
*/

// system includes
#include <cstdio>
#include <cstdlib>
#include <cstring>

// system includes
#include <sys/stat.h>
#include <unistd.h>

// DGM includes
#include "Utilities.hpp"

using std::ifstream;
using std::string;
using std::ws;

namespace DGM {

  // readable and size greater than zero
  bool file_exists(string s, bool allow_zero_sized) {
    struct stat buf;
    bool exists = false;
    if (0 == lstat(s.c_str(), &buf)) {
      if (allow_zero_sized) {
        exists = buf.st_mode & S_IFREG || buf.st_mode & S_IFLNK;
      }
      else {
        exists = 0 < buf.st_size && (buf.st_mode & S_IFREG || buf.st_mode & S_IFLNK);
      }
    }
    return exists;
  }

  // readable 
  bool directory_exists(string s) {
    struct stat buf;
    bool exists = false;
    if (0 == stat(s.c_str(), &buf))
      exists = buf.st_mode & (S_IFDIR | S_IRUSR);
    return exists;
  }

  /// Scan for a left curly bracket
  string scan_lb(ifstream &in, string s) {
    using std::streampos;
    streampos sp_in = in.tellg();
    string token;
    in >> token;
    while (in.good() && !in.eof() && token != "{" ) {
      if (!(in >> token)) error(s + " syntax error:  Cannot find \"{\"");
    }
    // return the scanned string
    streampos sp_out = in.tellg();
    string t;
    t.resize(sp_out - sp_in - 1);
    // position stream back to beginning location
    in.seekg(sp_in);
    // skip the {
    in.read(&t[0], sp_out - sp_in - 1);
    // position stream back to correct location
    in.seekg(sp_out);
    // return the string
    return t;
  }

  /// Scan for a right curly bracket
  void scan_rb(ifstream &in, string s) {
    string token;
    while (token != "}" )
      if (!(in >> token)) error(s + " syntax error:  Cannot find \"}\"");
  }
 
  // return code and tag
  string scan_tag(ifstream &in, string &code, string s) {
    using DGM::Comm;
    string tag;
    code.clear();
    if (!(in >> code)) {
      Comm::World->error(s + ": Cannot read Json header code and tag");
    }
    while (code[0]=='#') {        // eat comment lines
      string buffer;
      getline(in,buffer);
      if (!(in >> code)) {
        Comm::World->error(s + ": Cannot read Json header tag for code " + code);
      }
    }
    if (!(in >> tag)) {
      Comm::World->error(s + ": Cannot read Json header tag for code " + code);
    }
    return tag;
  }

  // extract block of nested { }
  void scan_block(ifstream &in, string s) {
    int nesting_level = 1;
    string token;
    scan_lb(in, s);
    while (nesting_level && in.good() && !in.eof()) {
      in >> token;
      if ('{' == token[0]) 
        ++nesting_level;
      else if ('}' == token[0]) 
        --nesting_level;
      // skip whitespace, trigger EOF
      in >> ws;
    }
  }

  /// Find search string value in block, backup to find start of block,
  /// prepend prefix to each occurence of tag's value in this block
  void prepend(string& block, string search, string tag, string prefix) {
    // find tag in this json block
    string::size_type loc = block.find(search);
    if (loc == string::npos) return;
    // find start of this nested block
    string::size_type loc2 = block.rfind("{", loc);
    // from start of this nested block, find tag
    loc = block.find(tag, loc2);
    // prepend to each string listed in array
    loc = block.find("[", loc+1);
    loc2 = block.find("]", loc+1);
    // prepend prefix to each quoted string
    while (loc < loc2) {
      // start of first string
      loc = block.find('"', loc);
      // insert before this location
      block.insert(loc+1, prefix);
      // check if a comma, indicating another string
      if (loc2 <= block.find(',', loc+prefix.size()+1)) break;
      // find end of this string
      loc = block.find('"', loc+prefix.size()+1);
      // move past end of this string
      ++loc;
    }
  }

  /// Find tag in block, prepend prefix to tag's value
  /// Note, doesn't work with an array type, just single string values
  void prepend(string& block, string tag, string prefix) {
    // find tag in this block
    string::size_type tag_loc = block.find(tag);
    if (tag_loc == string::npos) return;
    // search for colon (skip last quote)
    string::size_type loc = tag_loc + tag.size() + 1;
    // find first quote of tag value
    loc = block.find('"', loc);
    // insert before this location
    block.insert(loc+1, prefix);
  }

  /// Get the time from master and broadcast
  string dateTime() {
    const int buflen = 256;
    char now[buflen] = "Time is not available";
    time_t tp = ::time(0);
    strftime(now,buflen,"%a %b %d %Y at %H:%M:%S", localtime(&tp));
    return now;
  }

#ifndef DGM_USE_PBS_API

  /// This version uses the PBS qstat shell command and it is slow...
  void JobStatus::tremain_(int *walltime , int *cputime) {
    using namespace std;
    int VERBOSE = 0;
    char *jobid , *run_cmd , *text;
    char buffer[BUFSIZ];
    int asked_walltime , asked_cput;
    int used_walltime , used_cput;
    FILE *ptr;
    asked_walltime = asked_cput = used_walltime = used_cput = -1;
    if ( VERBOSE ) {
      fprintf(stderr,"Incoming variables: (%d) (%d)\n",*walltime,*cputime);
      fprintf(stderr,"About to get PBS Jobid.\n");
    }
    jobid = getenv("PBS_JOBID");
    if ( VERBOSE ) fprintf(stderr,"The current Jobid is: %s\n",jobid);
    if ( jobid == NULL ) {
      *walltime = -1;
      *cputime = -1;
      return;
    }
    if ( VERBOSE ) fprintf(stderr,"Setting up to run qstat -f..\n");
    run_cmd = new char[100];
    sprintf(run_cmd,"/usr/local/pbs/bin/qstat -f %s",jobid);
    if ( VERBOSE ) fprintf(stderr,"Running: %s\n",run_cmd);
    ptr = popen(run_cmd,"r");
    if ( ptr == NULL ) {
      *walltime = -1;
      *cputime = -1;
      return;
    }
    while (fgets(buffer, BUFSIZ, ptr) != NULL) {
      buffer[strlen(buffer)-1] = '\0';
      if ( VERBOSE ) fprintf(stderr,"Buffer line: (%s)\n",buffer);
      if ( strstr(buffer,"resources_used.cput") != NULL ) {
        text = (char *)strtok(buffer,"=");
        text = (char *)strtok(NULL,"=");
        if ( VERBOSE ) fprintf(stderr,"The cput used string is:%s\n",text);
        used_cput = 0;
        used_cput += 3600 * atoi((char *)strtok(text,":"));
        used_cput += 60 * atoi((char *)strtok(NULL,":"));
        used_cput += atoi((char *)strtok(NULL,"."));
      }
      if ( strstr(buffer,"resources_used.walltime") != NULL ) {
        text = (char *)strtok(buffer,"=");
        text = (char *)strtok(NULL,"=");
        if ( VERBOSE ) fprintf(stderr,"The walltime used string is:%s\n",text);
        used_walltime = 0;
        used_walltime += 3600 * atoi(strtok(text,":"));
        used_walltime += 60 * atoi(strtok(NULL,":"));
        used_walltime += atoi(strtok(NULL,":"));
      }
      if ( strstr(buffer,"Resource_List.cput") != NULL ) {
        text = (char *)strtok(buffer,"=");
        text = (char *)strtok(NULL,"=");
        if ( VERBOSE ) fprintf(stderr,"The cput asked string is:%s\n",text);
        asked_cput = 0;
        asked_cput += 3600 * atoi(strtok(text,":"));
        asked_cput += 60 * atoi(strtok(NULL,":"));
        asked_cput += atoi(strtok(NULL,":"));
      }
      if ( strstr(buffer,"Resource_List.walltime") != NULL ) {
        text = (char *)strtok(buffer,"=");
        text = (char *)strtok(NULL,"=");
        if ( VERBOSE ) fprintf(stderr,"The walltime asked string is:%s\n",text);
        asked_walltime = 0;
        asked_walltime += 3600 * atoi(strtok(text,":"));
        asked_walltime += 60 * atoi(strtok(NULL,":"));
        asked_walltime += atoi(strtok(NULL,":"));
      }
    }
    pclose(ptr);
    if ( VERBOSE ) {
      fprintf(stderr,"We have the values of:\n");
      fprintf(stderr,"   Asked walltime: %d\n",asked_walltime);
      fprintf(stderr,"   Asked cputime : %d\n",asked_cput);
      fprintf(stderr,"   Used  walltime: %d\n",used_walltime);
      fprintf(stderr,"   Used  cputime : %d\n",used_cput);
    }
    if ( asked_walltime != -1 )
      *walltime = asked_walltime - used_walltime;
    else
      *walltime = -1;
    if ( asked_cput != -1 )
      *cputime = asked_cput - used_cput;
    else
      *cputime = -1;
    delete [] run_cmd;
    if ( VERBOSE ) fprintf(stderr,"All done in tremain.\n");
    return;
  }

#else   // DGM_USE_PBS_API

  /// This version uses the PBS-API and it is fast, but must link with libpbs.a
  void JobStatus::tremain_(int *walltime, int *cputime) {
    using namespace std;
    int asked_walltime, asked_cput, used_walltime, used_cput;
    asked_walltime = asked_cput = used_walltime = used_cput = -1;
    // return if PBS is inactive
    if ( jobid == NULL || server == NULL ) {
      // cout << "PBS not active" << endl;
      *walltime = -1;
      *cputime = -1;
      return;
    }
    // cout << "about to call pbs_statjob" << endl;
    pstat = pbs_statjob(connect, jobid, attrib, extend);
    attrl *pat = pstat->attribs;
    while (pat) {
      // cout << pat->name << endl;
      if ( strcmp(pat->name,ATTR_used) == 0 ) {
        // cout << "  " << pat->resource << endl;
        if (strcmp(pat->resource, "walltime") == 0) {
          used_walltime = 0;
          used_walltime += 3600 * atoi(strtok(pat->value,":"));
          used_walltime += 60 * atoi(strtok(NULL,":"));
          used_walltime += atoi(strtok(NULL,":"));
        } else if (strcmp(pat->resource, "cput") == 0) {
          used_cput = 0;
          used_cput += 3600 * atoi(strtok(pat->value,":"));
          used_cput += 60 * atoi(strtok(NULL,":"));
          used_cput += atoi(strtok(NULL,":"));
        }
      } else if ( strcmp(pat->name,ATTR_l) == 0 ) {
        // cout << "  " << pat->resource << endl;
        if (strcmp(pat->resource, "walltime") == 0) {
          asked_walltime = 0;
          asked_walltime += 3600 * atoi(strtok(pat->value,":"));
          asked_walltime += 60 * atoi(strtok(NULL,":"));
          asked_walltime += atoi(strtok(NULL,":"));
        } else if (strcmp(pat->resource, "cput") == 0) {
          asked_cput = 0;
          asked_cput += 3600 * atoi(strtok(pat->value,":"));
          asked_cput += 60 * atoi(strtok(NULL,":"));
          asked_cput += atoi(strtok(NULL,":"));
        }
      }
      pat = pat->next;
    }
    pbs_statfree(pstat);

    if ( asked_walltime != -1 )
      *walltime = asked_walltime - used_walltime;
    else
      *walltime = -1;
    if ( asked_cput != -1 )
      *cputime = asked_cput - used_cput;
    else
      *cputime = -1;

    return;
  }

#endif  // DGM_USE_PBS_API

} // namespace DGM

#include <ext/hash_map>
#include <string>
#include <iostream>
using namespace std;

#if 1
struct eqstr
{
  bool operator()(const string& s1, const string& s2) const
  {
    return s1 == s2;
  }
};

// A hash function is needed to use strings
namespace std {
  template<> struct hash<string> {
    size_t operator()(const string& str) const {
      unsigned long h = 0;
      const string::value_type* s = str.data();
      for (size_t len = str.length(); len > 0; --len, ++s)
	h = 5*h + (unsigned long)(*s);
      return size_t(h);
    }
  };
}

int main()
{
  hash_map<string, int, hash<string>, eqstr> months;
  
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  cout << "september -> " << months["september"] << endl;
  cout << "april     -> " << months["april"] << endl;
  cout << "june      -> " << months["june"] << endl;
  cout << "november  -> " << months["november"] << endl;
}

#else
struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

int main()
{
  hash_map<const char*, int, hash<const char*>, eqstr> months;
  
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  cout << "september -> " << months["september"] << endl;
  cout << "april     -> " << months["april"] << endl;
  cout << "june      -> " << months["june"] << endl;
  cout << "november  -> " << months["november"] << endl;
}
#endif

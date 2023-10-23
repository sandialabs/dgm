#ifndef DGM_TABLE_HPP
#define DGM_TABLE_HPP

/** \file Table.hpp
    \brief DGM parameter table and support classes.
    \author Scott Collis
    \author James Overfelt
*/

// System includes
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <typeinfo>

// Boost includes
#ifdef DGM_USE_BOOST_FS
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#endif
#include "boost/numeric/conversion/cast.hpp"
using boost::numeric_cast;

// DGM includes
#include "Comm.hpp"
#include "Types.hpp"

// Json includes
#if defined(DGM_TABLE_USE_JSON) || defined(DGM_JSON_TO_TABLE)
#ifdef DGM_USE_JSON
#include <json/value.h>
#include <json/writer.h>
#endif
#endif

namespace DGM {

/// turns on comment support in Table input
#define DGM_TABLE_USE_COMMENTS

/// Template class that can hold any type but is not currently used
class Any {
public:
  /// base class to hold data
  class placeholder {
  public:
    virtual ~placeholder() {}
    virtual const std::type_info & type() const = 0;
    virtual placeholder * clone() const = 0;
    virtual void print(std::ostream & os) const = 0;
  };
  /// derived class to hold data
  template<typename ValueType>
  class holder : public placeholder {
  public:
    holder(const ValueType & value) : held(value) {}
    virtual const std::type_info & type() const {
      return typeid(ValueType); }
    virtual placeholder * clone() const {
      return new holder(held); }
    virtual void print(std::ostream & os) const {
      os << held; }
    ValueType held;
  };

  Any() : content(0) { }

  template<typename ValueType>
  Any(const ValueType &value) :
    content( new holder<ValueType>(value) ) { }

  Any(const Any &other) :
    content(other.content ? other.content->clone() : 0 ) { }

  ~Any() { delete content; }

  Any & swap(Any &rhs) {
    std::swap(content, rhs.content);
    return *this;
  }

  template<typename ValueType>
  Any & operator=(const ValueType &rhs) {
    Any(rhs).swap(*this);
    return *this;
  }

  Any & operator=(const Any &rhs) {
    Any(rhs).swap(*this);
    return *this;
  }

  bool empty() const {
    return !content;
  }

  const std::type_info & type() const {
    return content ? content->type() : typeid(void);
  }

  void print(std::ostream& os) const {
    if (content && content->type() != typeid(Any) ) content->print(os);
  }

  placeholder *access_content() { return content; }
  const placeholder *access_content() const { return content; }

  template<typename ValueType>
  operator ValueType() {
    if ( this->type() != typeid(ValueType) ) {
      cerr<<std::string("Illegal cast from type ")+this->type().name()+
        std::string(" to ")+typeid(ValueType).name()<<endl;
      ::exit(EXIT_FAILURE);
    }
    Any::holder<ValueType> *dyn_cast_content =
      dynamic_cast<Any::holder<ValueType>*>(this->access_content());
    return dyn_cast_content->held;
  }

  /// cast an Any type to a concrete type
  template<typename ValueType>
  static ValueType & cast(Any &operand) {
    // test to make sure that type match
    Any::holder<ValueType> *dyn_cast_content =
      dynamic_cast<Any::holder<ValueType>*>(operand.access_content());
    // test to make sure that cast worked
    return dyn_cast_content->held;
  }

  /// constant version of Any_cast
  template<typename ValueType>
  static const ValueType & cast(const Any &operand) {
    return cast<ValueType>(const_cast<Any&>(operand));
  }

private:

  placeholder *content;

};

//===========================================================================
//        Testing of a New Parameter Entry based on the Any Class
//===========================================================================

/// Parameter entry class using the Any Class
/** \todo Complete testing of the new parameter entry class. */
class ParameterEntry {
public:
  /// Default Constructor
  ParameterEntry() {};
  /// Constructor
  ParameterEntry(const ParameterEntry &source) {
    operator=(source);
  }
  /// Templated construction
  template<typename T>
  explicit ParameterEntry(T val) : value(val) {}
  /// Operator equals
  ParameterEntry& operator=(const ParameterEntry &source) {
    if (&source == this) return *this;
    value = source.value;
    return *this;
  }
  Any value;  ///< Value for this entry that can be any type
};

/// Output a ParameterEntry to stream
inline ostream& operator<<(ostream& os, const ParameterEntry &e) {
  e.value.print(os);
  return os;
}

//===========================================================================

/// Hold a value of arbitrary type
class Value {

  /// verbosity level
  const int verb;

public:

  /// types of data that this Value can store
  enum Value_type {
    NONE,      ///< no value is stored
    DOUBLE,    ///< a Scalar is stored
    INT,       ///< an integer is stored
    UNSIGNED,  ///< an unsigned integer is stored
    ULONG,     ///< an unsigned long
    ULONGLONG, ///< an unsigned 64bit integer
    STRING,    ///< a string is stored
    BOOL       ///< a boolean is stored
  };

  Value_type type;  ///< type of data in this Value
  void *val;        ///< storage for the data

  /// Types of status 
  enum Status {
    DEFAULT=0, 
    REDEFINED=1,
    UNDEFINED=2,
    USED=3
  };
  Status status;    ///< status of this value

  typedef DGM::Shared<Value>::Ptr Ptr;  ///< shared pointer to Value

  /// Default constructor
  Value() : verb(0), type(NONE), val(0), status(DEFAULT) {}

  /// destructor
  ~Value() {
    Value_type t(type);
    if (verb) cout <<"  ~Value() " << type2string() << ", &val = " << val;
    if (t==DOUBLE) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<Scalar*>(val) << endl;
        delete static_cast<Scalar*>(val);
      }
    } else if (t==INT) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<int*>(val) << endl;
        delete static_cast<int*>(val);
      }
    } else if (t==UNSIGNED) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<unsigned*>(val) << endl;
        delete static_cast<unsigned*>(val);
      }
    } else if (t==ULONG) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<unsigned long*>(val)
                       << endl;
        delete static_cast<unsigned long*>(val);
      }
    } else if (t==ULONGLONG) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<unsigned long long*>(val)
                       << endl;
        delete static_cast<unsigned long long*>(val);
      }
    } else if (t==STRING) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<std::string*>(val) << endl;
        delete static_cast<std::string*>(val);
      }
    } else if (t==BOOL) {
      if (val) {
        if (verb) cout << " val = " << *static_cast<bool*>(val) << endl;
        delete static_cast<bool*>(val);
      }
    } else if (t==NONE) {
      // do nothing
    } else {
      std::cout << "  Illegal Value type = " << type 
                << ", &val = " << val <<endl;
      ::exit(EXIT_FAILURE);
    }
  }

  /// Double constructor
  Value(const Scalar v) : verb(0), type(DOUBLE), status(DEFAULT) {
    val = new Scalar;
    copy( &v, &v+1, static_cast<Scalar*>(val) );
  }
  /// Int constructor
  Value(const int v) : verb(0), type(INT), status(DEFAULT) {
    val = new int;
    copy( &v, &v+1, static_cast<int*>(val) );
  }
  /// Unsigned long constructor
  Value(const unsigned long v) : verb(0), type(ULONG), status(DEFAULT) {
    val = new unsigned long;
    copy( &v, &v+1, static_cast<unsigned long*>(val) );
  }
  /// Unsigned long long constructor
  Value(const unsigned long long v) : verb(0), type(ULONGLONG), status(DEFAULT)
  {
    val = new unsigned long long;
    copy( &v, &v+1, static_cast<unsigned long long*>(val) );
  }
  /// String constructor
  Value(const std::string v) : verb(0), type(STRING), status(DEFAULT) {
    val = new std::string;
    *(static_cast<std::string*>(val)) = v;
  }
  /// Char* constructor
  Value(const char* v) : verb(0), type(STRING), status(DEFAULT) {
    val = new std::string;
    *(static_cast<std::string*>(val)) = v;
  }
  /// Boolean constructor
  Value(const bool v) : verb(0), type(BOOL), status(DEFAULT) {
    val = new bool;
    copy( &v, &v+1, static_cast<bool*>(val) );
  }

  /// clear the value and return it to NONE
  void clear() {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);break;}
      case INT      :{delete static_cast<int*>               (val);break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);break;}
      case STRING   :{delete static_cast<std::string*>       (val);break;}
      case BOOL     :{delete static_cast<bool*>              (val);break;}
    }
    val = 0;
    status = DEFAULT;
    type = NONE;
  }

  /// tell me the type
  std::string type2string() const {
    switch (type) {
    case NONE:      return "NONE";
    case DOUBLE:    return "DOUBLE";
    case INT:       return "INT";
    case UNSIGNED:  return "UNSIGNED";
    case ULONG:     return "ULONG";
    case ULONGLONG: return "ULONGLONG";
    case STRING:    return "STRING";
    case BOOL:      return "BOOL";
    }
    return "UNDEFINED";
  }

  //===========================================================================
  //                            Type tests
  //===========================================================================
  bool isNone()      const { return type==NONE      ;}
  bool isDouble()    const { return type==DOUBLE    ;}
  bool isInt()       const { return type==INT       ;}
  bool isUnsigned()  const { return type==UNSIGNED  ;}
  bool isUlong()     const { return type==ULONG     ;}
  bool isUlonglong() const { return type==ULONGLONG ;}
  bool isString()    const { return type==STRING    ;}
  bool isBool()      const { return type==BOOL      ;}

  //===========================================================================
  //                            Cast operators
  //===========================================================================
  operator Scalar() {
    switch (type) {
    case DOUBLE: {
      return *(static_cast<Scalar*>(val));
      break; }
    case INT: {
      const int *p = static_cast<int*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<unsigned*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<unsigned long*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<unsigned long long*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return atof(p->c_str());
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+" to Scalar");
    }
    return 0;
  }
  operator int() {
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<Scalar*>(val);
      return numeric_cast<int>(*p);
      break; }
    case INT: {
      const int *p = static_cast<int*>(val);
      return numeric_cast<int>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<unsigned*>(val);
      return numeric_cast<int>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<unsigned long*>(val);
      return numeric_cast<int>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<unsigned long long*>(val);
      return numeric_cast<int>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return std::atoi(p->c_str());
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+" to int");
    }
    return 0;
  }
  operator unsigned() {
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<Scalar*>(val);
      return numeric_cast<unsigned>(*p);
      break; }
    case INT: {
      const int *p = static_cast<int*>(val);
      return numeric_cast<const unsigned>(*p);
      break; }
    case UNSIGNED: {
      return *(static_cast<unsigned*>(val));
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<unsigned long*>(val);
      return numeric_cast<unsigned>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<unsigned long long*>(val);
      return numeric_cast<unsigned>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return numeric_cast<unsigned>(std::atoi(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to unsigned");
     }
     return 0;
  }
  operator unsigned long() {
    //cout << "Cast "<<type2string()<<" to unsigned long: " << *this << endl;
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<Scalar*>(val);
      return numeric_cast<unsigned long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<int*>(val);
      return numeric_cast<unsigned long>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<unsigned*>(val);
      return numeric_cast<unsigned long>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<unsigned long*>(val);
      return numeric_cast<unsigned long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<unsigned long long*>(val);
      return numeric_cast<unsigned long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return numeric_cast<unsigned long>(std::atol(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to unsigned long");
     }
     return 0;
  }
  operator unsigned long long() {
    // cout << "Cast "<<type2string()<<" to unsigned long long: "
    //      << *this << endl;
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<Scalar*>(val);
      return numeric_cast<unsigned long long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<int*>(val);
      return numeric_cast<unsigned long long>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<unsigned*>(val);
      return numeric_cast<unsigned long long>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<unsigned long*>(val);
      return numeric_cast<unsigned long long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<unsigned long long*>(val);
      return numeric_cast<unsigned long long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return numeric_cast<unsigned long long>(std::atol(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to unsigned long long");
    }
    return 0;
  }
  operator std::string() {
    if (type != STRING)
      throw DGM::exception("Unsupported cast from "+type2string()+" to string");
    return *(static_cast<std::string*>(val));
  }
  operator bool() {
    switch (type) {
    case DOUBLE: {
      Scalar *p = static_cast<Scalar*>(val);
      return *p == 0 ? false : true;
      break; }
    case INT: {
      int *p = static_cast<int*>(val);
      return *p == 0 ? false : true;
      break; }
    case BOOL: {
      return *(static_cast<bool*>(val));
      break; }
    case STRING: {
      const std::string *p = static_cast<std::string*>(val);
      return std::atoi(p->c_str());
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+" to bool");
    }
    return 0;
  }

  //===========================================================================
  //                           Const cast operators
  //===========================================================================
  operator Scalar() const {
    switch (type) {
    case DOUBLE: {
      return *(static_cast<const Scalar*>(val));
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<const unsigned*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<Scalar>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return atof(p->c_str());
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const Scalar");
    }
    return 0;
  }
  operator int() const {
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const int>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const int>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<const unsigned*>(val);
      return numeric_cast<const int>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const int>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const int>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const int>(std::atoi(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const int");
    }
    return 0;
  }
  operator long() const {
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const long>(*p);
      break; }
    case UNSIGNED: {
      return *(static_cast<const long*>(val));
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const long>(std::atoi(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const long");
     }
     return 0;
  }
  operator unsigned() const {
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const unsigned>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const unsigned>(*p);
      break; }
    case UNSIGNED: {
      return *(static_cast<const unsigned*>(val));
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const unsigned>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const unsigned>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const unsigned>(std::atoi(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const unsigned");
     }
     return 0;
  }
  operator long long() const {
    //cout << "Cast "<<type2string()<<" to const long long: "
    //     << *this << endl;
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const long long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const long long>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<const unsigned*>(val);
      return numeric_cast<const long long>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const long long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const long long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const long long>(std::atol(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const unsigned long");
     }
     return 0;
  }
  operator unsigned long() const {
    //cout << "Cast "<<type2string()<<" to const unsigned long: "
    //     << *this << endl;
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const unsigned long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const unsigned long>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<const unsigned*>(val);
      return numeric_cast<const unsigned long>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const unsigned long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const unsigned long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const unsigned long>(std::atol(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const unsigned long");
     }
     return 0;
  }
  operator unsigned long long () const {
    //cout << "Cast "<<type2string()<<" to const unsigned long long: "
    //     << *this << endl;
    switch (type) {
    case DOUBLE: {
      const Scalar *p = static_cast<const Scalar*>(val);
      return numeric_cast<const unsigned long long>(*p);
      break; }
    case INT: {
      const int *p = static_cast<const int*>(val);
      return numeric_cast<const unsigned long long>(*p);
      break; }
    case UNSIGNED: {
      const unsigned *p = static_cast<const unsigned*>(val);
      return numeric_cast<const unsigned long long>(*p);
      break; }
    case ULONG: {
      const unsigned long *p = static_cast<const unsigned long*>(val);
      return numeric_cast<const unsigned long long>(*p);
      break; }
    case ULONGLONG: {
      const unsigned long long *p = static_cast<const unsigned long long*>(val);
      return numeric_cast<const unsigned long long>(*p);
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return numeric_cast<const unsigned long long>(std::atol(p->c_str()));
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const unsigned long long");
     }
     return 0;
  }
  operator std::string() const {
    if (type != STRING)
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const string");
    return *(static_cast<const std::string*>(val));
  }
  operator bool() const {
    switch (type) {
    case DOUBLE: {
      Scalar *p = static_cast<Scalar*>(val);
      return *p == 0 ? false : true;
      break; }
    case INT: {
      int *p = static_cast<int*>(val);
      return *p == 0 ? false : true;
      break; }
    case BOOL: {
      return *(static_cast<const bool*>(val));
      break; }
    case STRING: {
      const std::string *p = static_cast<const std::string*>(val);
      return std::atoi(p->c_str());
      break; }
    default:
      throw DGM::exception("Unsupported cast from "+type2string()+
                           " to const bool");
    }
    return 0;
  }

  //===========================================================================
  //                           Equals operators
  //===========================================================================
  Value& operator= (const Scalar v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new Scalar; type = DOUBLE; }
    if (type != DOUBLE) {
      cerr << "Illegal type: " << type << " should be " << DOUBLE << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<Scalar*>(val) );
    return *this;
  }

  Value& operator= (const int v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new int; type = INT; }
    if (type != INT) {
      cerr << "Illegal type: " << type << " should be " << INT << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<int*>(val) );
    return *this;
  }

  Value& operator= (const unsigned v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new unsigned; type = UNSIGNED; }
    if (type != UNSIGNED) {
      cerr << "Illegal type: " << type << " should be " << UNSIGNED << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<unsigned*>(val) );
    return *this;
  }

  Value& operator= (const unsigned long v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new unsigned long; type = ULONG; }
    if (type != ULONG) {
      cerr << "Illegal type: " << type << " should be " << ULONG << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<unsigned long*>(val) );
    return *this;
  }

  Value& operator= (const unsigned long long v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new unsigned long long; type = ULONGLONG; }
    if (type != ULONGLONG) {
      cerr << "Illegal type: " << type << " should be " << ULONGLONG << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<unsigned long long*>(val) );
    return *this;
  }

  Value& operator= (const char* v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{break;}
      case BOOL     :{delete static_cast<bool*>              (val);val=0;break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new std::string; type = STRING; }
    if (type != STRING) {
      cerr << "Illegal type: " << type << " should be " << STRING << endl;
      ::exit(EXIT_FAILURE);
    }
    *(static_cast<std::string*>(val)) = v;
    return *this;
  }

  Value& operator= (const std::string v) {
    bool b;
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new std::string; type = STRING; }
    switch (type) {
    case STRING:
      *(static_cast<std::string*>(val)) = v;
      break;
    case DOUBLE:
      *this = atof(v.c_str());
      break;
    case INT:
      *this = std::atoi(v.c_str());
      break;
    case UNSIGNED:
      *this = static_cast<unsigned>(std::atoi(v.c_str()));
      break;
    case ULONG:
      *this = static_cast<unsigned long>(std::atol(v.c_str()));
      break;
    case ULONGLONG:
      *this = static_cast<unsigned long long>(std::atol(v.c_str()));
      break;
    case BOOL:
      b = std::atoi(v.c_str());
      *this = b;
      break;
    default:
      cerr << "Unsupported value type " << type2string() << endl;
      ::exit(EXIT_FAILURE);
    }
    return *this;
  }

  Value& operator= (const bool v) {
    switch (type) {
      case NONE     :{break;}
      case DOUBLE   :{delete static_cast<Scalar*>            (val);val=0;break;}
      case INT      :{delete static_cast<int*>               (val);val=0;break;}
      case UNSIGNED :{delete static_cast<unsigned*>          (val);val=0;break;}
      case ULONG    :{delete static_cast<unsigned long*>     (val);val=0;break;}
      case ULONGLONG:{delete static_cast<unsigned long long*>(val);val=0;break;}
      case STRING   :{delete static_cast<std::string*>       (val);val=0;break;}
      case BOOL     :{break;}
    }
    if (type!=NONE) status = REDEFINED;
    if (val==0) { val=new bool; type = BOOL; }
    if (type != BOOL) {
      cerr << "Illegal type: " << type << " should be " << BOOL << endl;
      ::exit(EXIT_FAILURE);
    }
    copy( &v, &v+1, static_cast<bool*>(val) );
    return *this;
  }

  /// Convert status to a string value for output
  std::string statusToString() const {
    std::string result;
    switch(status) {
      case DEFAULT: {result=""; break;}
      case REDEFINED: {result="[REDEFINED]"; break;}
      case UNDEFINED: {result="[UNDEFINED]"; break;}
      case USED: {result="[USED]"; break;}
      default: {throw DGM::exception("Undefined status"); break;}
    }
    return result;
  } 

#ifdef DGM_JSON_TO_TABLE
  inline void insert_into_json(const std::vector<std::string> &K,
                               const DGM::Comm::Ptr comm,
                               Json::Value *V) const;
#endif

  inline friend std::ostream& operator<<(std::ostream&, const Value&);
};

/// output method
inline std::ostream& operator<<(std::ostream& os, const Value& P) {
  switch (P.type) {
  case Value::DOUBLE:
    os << *(static_cast<Scalar*>(P.val));
    break;
  case Value::INT:
    os << *(static_cast<int*>(P.val));
    break;
  case Value::ULONG:
    os << *(static_cast<unsigned long*>(P.val));
    break;
  case Value::ULONGLONG:
    os << *(static_cast<unsigned long long*>(P.val));
    break;
  case Value::STRING:
    os << *(static_cast<std::string*>(P.val));
    break;
  case Value::BOOL:
    os << *(static_cast<bool*>(P.val));
    break;
  default:
    break;
  }
  os << P.statusToString();
  return os;
}

//=============================================================================

/// Table of parameters (used to manage input options)
class Table {
  /// This is the actual storage for the table
  map<std::string,Value::Ptr> table;
  /// Communicator for this Table
  DGM::Comm::Ptr comm;
  /// This defines the type of comment supported
  std::string comment;
#ifdef DGM_TABLE_USE_ANY
  /// Test of the Any class (experimental)
  map<std::string,Any> new_table;
#endif
  /// Template for const element access to table with default
  /** \note We don't expose this template for general use as we don't want
      to instantiate it on unsupported types.  Therefore, we only explose
      explicit get signatures that are supported and others will generate a
      compile-time error. */
  template <typename T>
  const Value& _get(const std::string &key, const T v) {
    if (!defined(key)) {
      (*this)[key] = v;
    } else {
      // These machinations are to make sure that the stored type is correct
      const T t = (*this)[key];
      (*this)[key] = t;
      (*this)[key].status = Value::REDEFINED;
    }
    return get(key);
  }
 protected:
  /// Iterator
  typedef map<std::string,Value::Ptr>::iterator TI;
  /// Constant iterator
  typedef map<std::string,Value::Ptr>::const_iterator CTI;
 public:
  /// Constructor
  Table(const DGM::Comm::Ptr _comm = DGM::Comm::World) : 
    comm(_comm), comment("#") { };
  /// Destructor
  ~Table() {
    int output = 0;
    const char *tmp = getenv("DGM_OUTPUT_TABLE");
    if (tmp != NULL) output = std::atoi(tmp);
    if (output) comm->cout()<<*this;
  }

  // methods
  inline void parse(int argc, char *argv[]);
  inline bool exists(const std::string fname) const;
  inline Table & read(const std::string &fname);
  inline Table & read_all(const std::string &fname);
  inline Value & read(const std::string &fname, const std::string &param);
  inline size_t size() {return table.size(); }

  /// Element access to table
  /** If key is not found, adds the key to the table. */
  Value& operator[] (const std::string key) {
#ifdef DGM_USE_TEUCHOS_RCP
    // would be nice to get rid of this.  Have asked Ross about this...
    if ( table[key].get() == 0 ) {
#else
    if ( table[key] == 0 ) {
#endif
      table[key].reset( new Value() );
    }
    return *(table[key]);
  }

  /// Const element access to table
  /** If key is not found, the method generates an error. */
  const Value& get(const std::string &key) const {
    CTI entry = table.find(key);
    if (entry == table.end()) {
      cerr << "key '" + key + "' not found in table" << endl;
      ::exit(EXIT_FAILURE);
    }
#ifdef DGM_USE_TEUCHOS_RCP
    // would be nice to get ride of this.  Have asked Ross about this...
    if ( entry->second.get() == NULL ) {
#else
    if ( entry->second == NULL ) {
#endif
      cerr << "no value for key '" + key + "' found in table" << endl;
      ::exit(EXIT_FAILURE);
    }
    const Value &a = *(entry->second);
    return a;
  }
    
  // Note:  we only allow certain types of get methods with default so that
  // we have explicit control of the types of data casts allowed

  /// Const element access to table with default value
  const Value& get(const std::string &key, const double v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const int v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const unsigned int v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const unsigned long v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const unsigned long long v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const bool v) {
    return _get(key,v);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const char *v) {
    const std::string tv = std::string(v);
    return _get(key,tv);
  }
  /// Const element access to table with default value
  const Value& get(const std::string &key, const std::string v) {
    return _get(key,v);
  }

  /// Check, whether key exists in table
  bool defined(const std::string &key) const {
    return table.find(key) == table.end() ? false : true;
  }

#ifdef DGM_TABLE_USE_JSON
#ifdef DGM_USE_JSON
  /// Convert to Json::Value
  inline void convert(Json::Value &json);
#endif
#endif

#ifdef DGM_JSON_TO_TABLE
  /// Insert JSON values into DGM::Table
  inline void insert_json_into(const Json::Value &J,
                               const std::vector<std::string> &K,
                               const std::string &t,
                               const DGM::Comm::Ptr comm);
  /// SSC:  I don't quite understand what this is doing?
  static void insert_into_json(const std::vector<std::string> &K,
                               const std::string &T,
                               Json::Value &J) {
    bool is_member = true;
    Json::Value *V = &J;
    for (size_t j = 0; j!=K.size()-1 && is_member; ++j) {
      is_member = V->isMember(K[j]);
      if (is_member) {
        V = &(*V)[K[j]];
        //cout << K[j] << endl;
      }
    }
    if (is_member && V->isMember(T)) {
      (*V)[K.back()] = (*V)[T];
      //cout << K.back() << ": " << T << endl;
    }
  }
  /// Make a JSON table and DGM::Table consistent through a map
  void convert(Json::Value &json,
    const std::map< std::string,std::vector<std::string> > &tbl_to_json) {
    Table &table = *this;
    typedef std::vector<std::string> PATH;
    typedef std::map<std::string,PATH> TBL_MAP;
    for (TBL_MAP::const_iterator i = tbl_to_json.begin();
                                 i!= tbl_to_json.end(); ++i) {
      insert_into_json(i->second, i->first, json);
      table.insert_json_into(json, i->second, i->first, comm);
      if (table.defined(i->first)) {
        const Value &T = table.get(i->first);
        T.insert_into_json(i->second, comm, &json);
      }
    }
  }
#endif

  inline friend std::ostream& operator<<(std::ostream&, const Table&);
};

/// Extract parameters from an argument list
inline void Table::parse(int argc, char *argv[]) {
  std::string name, value, code=argv[0];
  while ( --argc && (*++argv)[0] == '-') {
    name = *argv;
    name.erase(0,1);          // remove the minus
    CTI p = table.find(name);
    if ( p != table.end() ) {
      value = *(++argv);      // extract the value
      argc--;
      (*this)[name] = value;
    } else {
      cerr << "\"" << name << "\" not found in table." << endl;
      goto showUsage;
    }
  }
  return;
 showUsage:
  cerr << "=================================\n"
       << "Usage:   " << code << " [Options]\n"
       << "=================================\n"
       << "Options: " << '\t' << "Defaults  \n"
       << "=================================\n";
  cerr << *this;
  ::exit(EXIT_FAILURE);
}

/// Check to see if parameter file exists
/** This uses boost::filesystem to check if a file exists. */
inline bool Table::exists(const std::string fname) const {
#ifndef DGM_USE_BOOST_FS
  #warning DGM::Table requires that DGM_USE_BOOST_FS is defined
  return true;
#else
  boost::filesystem::path p(fname);
#ifdef DGM_TEST_TABLE_EXISTS
  cout << "base = " << boost::filesystem::current_path()<<endl;
  char *buf=0;
  buf = getwd(buf);
  cout << "Current directory "<<buf<<endl;
  boost::filesystem::path cwd((std::string(buf)));
  free(buf);
  cout << "cwd  " << cwd << endl;
  cwd /= p; p = cwd;
  cout << "path " << p << endl;
  cout << "exists " << boost::filesystem::exists(p) << endl;
  cout << "is_directory " << boost::filesystem::is_directory(p) << endl;
#endif
  return (boost::filesystem::exists(p) &&
         !boost::filesystem::is_directory(p));
#endif
}

/// Read parameters from an input file
inline Table &Table::read( const std::string &fname ) {
  // The default is to not check if the parameter is valid
#ifdef DGM_TABLE_USE_COMMENTS
  // This version ignores comments
  std::string name, token, value, buffer;
  ifstream fp(fname.c_str());
  if ( fp ) {
    // try implementing a new parser that ignores comments
    while ( getline(fp,buffer) ) {
      size_t loc=buffer.find(comment);
      if (loc != std::string::npos) buffer.erase(loc);
      //cout << "Read line:  " << buffer << endl;
      istringstream ist(buffer);
      if ( ist >> name >> token >> value ) {
        TI p = table.find(name);
        if ( p != table.end() ) {
          (*this)[name] = value;
          (*this)[name].status = Value::REDEFINED;
        }
#ifdef DGM_TABLE_REPORT_ERROR
        else
          cerr << "Parameter \"" << name << "\" not found in table"<< endl;
#endif
      }
    }
  }
#else
  // This version just reads triplets from the input stream
  std::string name, token, value;
  ifstream fp(fname.c_str());
  if ( fp ) {
    while ( fp >> name >> token >> value ) {
      // cout << "Table::read " << name << token << value << endl;
      TI p = table.find(name);
      if ( p != table.end() ) {
        (*this)[name] = value;
        (*this)[name].status = Value::REDEFINED;
      }
#ifdef DGM_TABLE_REPORT_ERROR
      else
        cerr << "Parameter \"" << name << "\" not found in table"<< endl;
#endif
    }
  }
#endif
  return *this;
}

/// Read all parameters from a file
/** This explicitly keeps track of the status of the parameters */
inline Table &Table::read_all( const std::string &fname ) {
  std::string name, token, value, buffer;
  ifstream fp(fname.c_str());
  if ( fp ) {
    while ( getline(fp,buffer) ) {
      size_t loc=buffer.find(comment);
      if (loc != std::string::npos) buffer.erase(loc);
      istringstream ist(buffer);
      if ( ist >> name >> token >> value ) {
        if (defined(name)) {
          (*this)[name] = value;
          (*this)[name].status = Value::REDEFINED;
        } else {
          (*this)[name] = value;
          (*this)[name].status = Value::UNDEFINED;
        }
      }
    }
  }
  return *this;
}

/// Read a particular parameter from the input file
/** \warning This is really inefficient in that it has to stream through
 *  the entire file to find a single parameter.  Clearly this is not very
 *  scalable for large input files. */
inline Value &Table::read(const std::string &fname, const std::string &param) {
  if ( table.find(param) == table.end() ) {
    cerr<<"Table::read(...) Tried to read an undefined parameter, "
        <<param<<" from file "<<fname<<"."<<endl;
    ::exit(EXIT_FAILURE);
  }
#ifdef DGM_TABLE_USE_COMMENTS
  // This version ignores comments
  std::string name, token, value, line;
  ifstream fp(fname.c_str());
  if ( fp ) {
    // try implementing a new parser that ignores comments
    while ( getline(fp,line) ) {
      size_t loc=line.find(comment);
      if (loc != std::string::npos) line.erase(loc);
      //cout << "Read line:  " << line << endl;
      istringstream ist(line);
      if ( ist >> name >> token >> value ) {
        if (name==param) {
          (*this)[name] = value;
        }
      }
    }
  }
#else
  std::string name, token, value;
  ifstream fp(fname.c_str());
  if ( fp ) {
    while ( fp >> name >> token >> value ) {
      if (name==param) (*this)[name] = value;
    }
  }
#endif
  return (*this)[param];
}

#ifdef DGM_TABLE_USE_JSON
#ifdef DGM_USE_JSON
/// Convert to Json::Value
void Table::convert(Json::Value &json) {
  for (Table::CTI p = table.begin(); p != table.end(); ++p) {
    std::string first = p->first;
    DGM::Value::Value_type type = p->second->type;
    if (p->second->status==Value::UNDEFINED) continue;
    DGM::Value &second = *(p->second);
    if (type == DGM::Value::DOUBLE) {
      json[first] = (double)second;
    } else if (type == DGM::Value::INT) {
      json[first] = (int)second;
    } else if (type == DGM::Value::STRING) {
      json[first] = (std::string)second;
    } else if (type == DGM::Value::BOOL) {
      json[first] = (bool)second;
    } else {
      throw(logic_error("Unknown DGM::Value type"));
    }
  }
}
#endif
#endif

#ifdef DGM_JSON_TO_TABLE

void Value::insert_into_json(
    const std::vector<std::string> &K,
    const DGM::Comm::Ptr comm,
    Json::Value *V
) const {
  const Value &T = *this;
  for (size_t j = 0; j!=K.size()-1; ++j) {
    if (!V->isMember(K[j])) (*V)[K[j]] = Json::Value(Json::objectValue);
    V = &(*V)[K[j]];
  }
  if (!V->isMember(K.back())) (*V)[K.back()] = Json::Value();
  V = &(*V)[K.back()];
  switch (T.type) {
  case Value::DOUBLE:    *V = static_cast<Scalar            >(T); break;
  case Value::INT:       *V = static_cast<int               >(T); break;
  case Value::UNSIGNED:  *V = static_cast<unsigned          >(T); break;
  case Value::ULONG:     *V = static_cast<unsigned long     >(T); break;
  case Value::ULONGLONG: *V = static_cast<unsigned long long>(T); break;
  case Value::STRING:    *V = static_cast<std::string       >(T); break;
  case Value::BOOL:      *V = static_cast<bool              >(T); break;
  default:
    comm->error("Error in conversion of DGM::Value to Json::Value");
  }
}

void Table::insert_json_into(
    const Json::Value &J,
    const std::vector<std::string> &K,
    const std::string &t,
    const DGM::Comm::Ptr comm
) {
  Table &T = *this;
  bool is_member = true;
  const Json::Value *V = &J;
  for (size_t j = 0; j!=K.size() && is_member; ++j) {
    is_member = V->isMember(K[j]);
    if (is_member) V = &(*V)[K[j]];
  }
  if (is_member) {
    T[t].clear();
    switch (V->type()) {
    case Json::realValue:    T[t] = V->asDouble(); break;
    case Json::intValue:     T[t] = V->asInt();    break;
    case Json::uintValue:    T[t] = V->asUInt();   break;
    case Json::stringValue:  T[t] = V->asString(); break;
    case Json::booleanValue: T[t] = V->asBool();   break;
    default:
      comm->error("Error in conversion of Json::Value to DGM::Table");
    }
  }
}

#endif

/// Templated Table helper function
/** Added templated helper function to
    - put a given default parameter into a table,
    - read the parameter from the input file (*.inp), and
    - return either the default variable (if string is not found in input)
      or the read value.
    - it also returns the updated table.
    - Reading variables from file and registering it in the table can be
      a one-liner

   possible improvement:
    - add warning (maybe in a verbose mode) to let the user know,
      if the variable has not been found in *.inp file
*/
template <typename T>
inline T read_from_input(
    Table  &params,            ///< table, where the param should be inserted
    const std::string &file,   ///< input file
    const std::string &key,    ///< parameter name in input file
    const T &defaultval        ///< default value
    )
{
  params[key] = defaultval;
  return params.read(file, key);
}

/// Output method
inline std::ostream& operator<<(std::ostream& os, const Table& P) {
  for (Table::CTI p = P.table.begin(); p != P.table.end(); ++p) {
    os << setw(18) << p->first << " = " ;
    os.setf(std::ios::left);
#ifdef DGM_USE_TEUCHOS_RCP
    if (p->second.get())
#else
    if (p->second)
#endif
      os << setw(30) << std::left << *(p->second) << std::right << std::endl;
    else
      os << "WARNING: Value not defined" << std::endl;
  }
  const char fill = os.fill('=');
  os.width(64); os<<'='<<std::endl; os.fill(fill);
  return os;
}

} // namespace DGM

#endif  // DGM_TABLE_HPP

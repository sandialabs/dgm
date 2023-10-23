/*! \file DTK_Composite.hpp
 *  \brief Enables integration of composite functions using DTK::TimeIntegrate
 *  \author Scott Collis
 */

#ifndef DTK_COMPOSITE_HPP
#define DTK_COMPOSITE_HPP

namespace DTK {

/// Composite of two Data objective 
template< typename Data1, typename Data2 >
class CompositeData {
public:
  Data1 U;
  Data2 J;
  CompositeData() {}
  CompositeData(Data1 &u, const Data2 &j) : U(u), J(j) {}
  CompositeData(CompositeData *in) : U(in->U), J(in->J) {}
  void clone(const CompositeData &in) { U.clone(in.U); J.clone(in.J); }
  void zero() { U.zero(); J.zero(); }
  void reset(Data2 &j) { J.alias(j); }
};

/*!
In general you will need to define these type of operations for the
composite data objects that you instantiate
\verbatim
/// Scale and add
template< typename Scalar, typename CompositeData >
void axpy(const Scalar a, const CompositeData & X, const CompositeData & Y,
          CompositeData & Z) {
  axpy(a,X.U,Y.U,Z.U);
  axpy(a,X.J,Y.J,Z.J);
}

/// Scale and add
template< typename Scalar, typename CompositeData >
void axpy(const Scalar a, const CompositeData & X, CompositeData & Y) {
  axpy(a,X.U,Y.U);
  axpy(a,X.J,Y.J);
}

/// Scale
template< typename Scalar, typename CompositeData >
void scale(const Scalar a, CompositeData & X) {
  scale(a,X.U);
  scale(a,X.J);
}
\endverbatim
*/

/// General Function interface
template< typename Scalar, typename Ordinal, typename Data >
class Function {
public:
  virtual ~Function() {}
  virtual Scalar timeStep() const=0;
  virtual Ordinal stepNumber() const=0;
  virtual Scalar time() const=0;
  virtual void time(Scalar t)=0;
  virtual Data & getU() =0;
  virtual Data & getUt() =0;
  virtual void time_derivative(Data &F, Data &R)=0;
  virtual void prestep(Data &F, Ordinal step, Ordinal sstep, Scalar t)=0;
  virtual void poststep(Data &F, Ordinal step, Ordinal sstep, Scalar t)=0;
};

/// Composite Function of a VectorField and ObjFunc
/*! \note that the ObjFunc::time_derivative syntax is a little different */
template< typename Scalar, typename Ordinal, typename Data1, typename Data2,
          typename Func1, typename Func2 >
class CompositeFunc : public Function< Scalar, Ordinal, 
                                       CompositeData< Data1, Data2 > > {
private:
  typedef CompositeData<Data1,Data2> Data;
  Func1 *domain;
  Func2 *J;
  Data U;
  Data Ut;
public:
  CompositeFunc(Func1 *d, Func2 *j) : domain(d), J(j),
    U(domain->getU(),J->getU()), Ut(domain->getUt(),J->getUt()) {}
  Scalar timeStep() const { return domain->timeStep(); }
  Ordinal stepNumber() const { return domain->stepNumber(); }
  Scalar time() const { return domain->time(); }
  void time(Scalar t) { domain->time(t); }
  Data & getU() { return U; }
  Data & getUt() { return Ut; }
  /*! \note that the time derivative on J depends only on U */
  void time_derivative(Data &F, Data &R) {
    domain->time_derivative(F.U,R.U);
    J->time_derivative(F.U,R.J);
  }
  void prestep(Data &F, Ordinal step, Ordinal sstep, Scalar t) {
    domain->prestep( F.U, step, sstep, t );
    J->prestep( F.J, step, sstep, t );
  }
  void poststep(Data &F, Ordinal step, Ordinal sstep, Scalar t) {
    domain->poststep(F.U, step, sstep, t);
    J->poststep(F.J, step, sstep, t);
  }
  /// Do not allow reset of first function
  void reset(Func1 *d) { throw DTK::exception("May not reset Func1"); }
  /// Need to be able to reset the underlying objective function
  void reset(Func2 *j) { J=j; U.reset(J->getU()); Ut.reset(J->getUt()); }
};

} // namespace DTK

#endif // DTK_COMPOSITE_HPP

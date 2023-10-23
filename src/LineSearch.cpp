/** \file LineSearch.cpp
    \brief DGM line search class implementation
    \author Scott Collis
*/

// system includes
#include <iostream>
#include <cmath>
using namespace std;

// DGM includes
#include "Constants.hpp"
#include "LineSearch.hpp"
#include "Color.hpp"
#include "Format.hpp"

namespace DGM {

  /// Constructor
  LineSearch::LineSearch(Eval<Scalar> &eval_, const DGM::Comm::Ptr comm_,
                         const OutputLevel outputLevel_) :
    comm(comm_),
    outputLevel(outputLevel_),
    eval(eval_),
    useOriginalBrents(true)
  { }

  /// Bracket a minimum
  Ordinal LineSearch::bracket(Scalar &xa, Scalar &xb, Scalar &xc,
                              Scalar &fa, Scalar &fb, Scalar &fc) {
    using std::endl;
    using std::fabs;

    static Color cyan(Color::CYAN);
    static Color magenta(Color::MAGENTA);
    static Color def(Color::DEFAULT);
    static DGM::Format sci(5,13,'e');

    // comm->cout() << "DGM::LineSearch::bracket(...)" << endl;

    // reset the evaluator count
    eval.reset();

    if (outputLevel == TEST_OUTPUT) {
      comm->cout() << cyan << "Initial Bracket:   ["
          <<sci(xa)<<", "<<sci(xb)<<", " <<sci(xc)<<"]"<< def << endl;
      comm->cout() << cyan << "Initial Functions: ["
          <<sci(fa)<<", "<<sci(fb)<<", " <<sci(fc)<<"]"<< def << endl;
    }

    // Repeatedly evaluate the function along the search direction until
    // we know we've bracketed a minimum.

    const Scalar GOLDEN_RATIO = 1.618033988749895;
    const Scalar SMALL_DIV = sqrt(epsM);
    const Scalar MAX_EXTRAP_FACTOR = 100.0;
    const Ordinal MAX_BACKTRACK = 8;
    Scalar tmp, q, r, xm, xlim, fm;

    // This does a simple backtracking
    xc = 0.0;
    const Scalar goldinv = 1.0/(1.0+GOLDEN_RATIO);
    Ordinal icount = 0;
    while (fb > fa) {
      if (icount <= MAX_BACKTRACK) {
        comm->cout() <<"Taking a smaller step in direction of gradient.\n";
        xc = xb;
        fc = fb;
        xb = goldinv * (xc + GOLDEN_RATIO*xa);
        fb = eval(xb);
      } else {
        comm->cout() <<"Oops - it appears as if I am proceeding uphill.\n";
        comm->cout() <<"I will now use a safer bracketing procedure.\n";
        comm->cout() << "xa = " << xa << ", xb = " << xb << ", xc = "
             << xc << endl;
        tmp = xa;
        xa = xb;
        xb = tmp;
        tmp = fb;
        fb = fa;
        fa = tmp;
        xc = 0.0;
        comm->cout()<<"xa = "<<xa<<", xb = "<<xb<<", xc = "<<xc<<endl;
      }
      icount++;
    }
    if (xc == 0.) {
      // the following factor of gold was reduced to (GOLDEN_RATIO-1) to save
      // one function evaluation near convergence.
      xc = xb + (GOLDEN_RATIO-1.0) * (xb-xa);
      fc = eval(xc);
#ifdef DGM_USE_ISNAN_ISINF
      int icount = 1;
      while ( (std::isnan(fc) || std::isinf(fc)) &&
              (icount <= MAX_BACKTRACK) ) {
        xc = xb + pow(0.5,icount)*(GOLDEN_RATIO-1.0)*(xb-xa);
        fc = eval(xc);
        icount++;
      }
#endif
    }

    if (outputLevel >= DEBUG_OUTPUT) {
      comm->cout() << "Bracket:   ["
        <<sci(xa)<<", "<<sci(xb)<<", " <<sci(xc)<<"]" << endl;
      comm->cout() << "Functions: ["
        <<sci(fa)<<", "<<sci(fb)<<", " <<sci(fc)<<"]" << endl;
    }

    while (fb >= fc) {

      if (outputLevel >= DEBUG_OUTPUT) {
        comm->cout() << "Bracket:   ["
          <<sci(xa)<<", "<<sci(xb)<<", " <<sci(xc)<<"]" << endl;
        comm->cout() << "Functions: ["
          <<sci(fa)<<", "<<sci(fb)<<", " <<sci(fc)<<"]" << endl;
      }

      // find the extremum xm of a quadratic model interpolating a, b, c
      q = (fb-fa)*(xb-xc);
      r = (fb-fc)*(xb-xa);
      // avoid division by small (q-r) by bounding with signed minimum
      tmp = fabs(q-r);
      tmp = (tmp > SMALL_DIV ? tmp : SMALL_DIV);
      tmp = (q-r >= 0  ? tmp : -tmp);
      xm = xb - (q*(xb-xc) - r*(xb-xa))/(2.0*tmp);

      // maximum point for which we trust the interpolation
      xlim = xb + MAX_EXTRAP_FACTOR * (xc-xb);

      // now detect which interval xm is in and act accordingly
      if ( (xb-xm)*(xm-xc) > 0.0 ) {            // [xb, xc]
        fm = eval(xm);
        if (fm < fc) {                          // use points [b, xm, c]
          xa = xb;
          fa = fb;
          xb = xm;
          fb = fm;
          continue;
        } else if (fm > fb) {                   // use points [a, b, xm]
          xc = xm;
          fc = fm;
          continue;
        }
        xm = xc + GOLDEN_RATIO*(xc-xb);
        fm = eval(xm);
      } else if ((xc-xm)*(xm-xlim) > 0.0) {     // [xc, xlim]
        fm = eval(xm);
        if (fm < fc) {
          xb = xc;
          xc = xm;
          xm = xc + GOLDEN_RATIO*(xc-xb);
          fb = fc;
          fc = fm;
          fm = eval(xm);
        }
      } else if ((xm-xlim)*(xlim-xc) >= 0.0 ) { // [xlim, inf]
        xm = xlim;
        fm = eval(xm);
      } else {                                  // [0,xb]
        xm = xc + GOLDEN_RATIO*(xc-xb);
        fm = eval(xm);
      }
      // shift to newest 3 points before loop
      xa = xb;
      fa = fb;
      xb = xc;
      fb = fc;
      xc = xm;
      fc = fm;
    }  // end while loop

    if (outputLevel == TEST_OUTPUT) {
      comm->cout() << magenta << "Final Bracket:   ["
          <<sci(xa)<<", "<<sci(xb)<<", " <<sci(xc)<<"]"<< def << endl;
      comm->cout() << magenta << "Final Functions: ["
          <<sci(fa)<<", "<<sci(fb)<<", " <<sci(fc)<<"]"<< def << endl;
    }
    return eval.count();
  }

  /* JR_KEEP_TWO_BRENTS_IMPLS

     There are 2 implementations of Brents - one that existed before
     mid-February, 2016 (Original Version) and one that Drew Kouri
     modified around mid-February 2016. We keep both around for testing.

     See LineSearch.hpp to see how to use one implementation versus the
     other. It's done through root.inp. Also see NonlinearCG.cpp.

     Remove the section in useOriginalBrents == true when we find that
     the two implementations are the same.

     Jaideep Ray, 2016-02-29 */

  /** Uses Brent's method.  For reference see Richard Brent, 1973, Algorithms
      for Minimization without Derivatives (Englewood Cliffs, N.J.,
      Prentice-Hall), Chapter 5.  As well as the function fmin available from
      NetLib.  Given a valid bracket, Brent's method uses inverse parabolic
      interpolation to find the minimum.  */
  Ordinal LineSearch::brents_fmin( Scalar &xa, Scalar &xb, Scalar &xc,
                                   Scalar &fa, Scalar &fb, Scalar &fc,
                                   Scalar tol, Ordinal itmax) {
    if (useOriginalBrents) {
      return brents_fmin_old(xa,xb,xc,fa,fb,fc,tol,itmax);
    } else {
      return brents_fmin_new(xa,xb,xc,fa,fb,fc,tol,itmax);
    }
  }

  /** Uses Brent's method.  For reference see Richard Brent, 1973, Algorithms
      for Minimization without Derivatives (Englewood Cliffs, N.J.,
      Prentice-Hall), Chapter 5.  As well as the function fmin available from
      NetLib.  Given a valid bracket, Brent's method uses inverse parabolic
      interpolation to find the minimum.

      This is the original DGM version that was modified to improve performance
  */
  Ordinal LineSearch::brents_fmin_old( Scalar &xa, Scalar &xb, Scalar &xc,
                                       Scalar &fa, Scalar &fb, Scalar &fc,
                                       Scalar tol, Ordinal itmax) {
    using std::endl;
    using std::fabs;

    eval.reset();

    static Color yellow(Color::YELLOW);
    static Color def(Color::DEFAULT);

    if (outputLevel == TEST_OUTPUT) {
      comm->cout() << yellow << "LineSearch::brents_fmin_old called with tol = "
          << tol <<", itmax = " << itmax << def << std::endl;
    }

    const Scalar INV_GOLD2 = 0.3819660112501051518; // (1/golden-ratio)^2
    const Scalar TINY = sqrt(epsM);

    Ordinal iteration;
    Scalar a, b, d=0, e=0, etemp, fu, fv, fw, fx, p, q, r;
    Scalar u, v, w, x, xm;

    //comm->cout() << "DGM::LineSearch::brents_fmin(...)" << endl;

    fw=(fa<fc? fa : fc ); // min(fa,fc);
    if(fw == fa){
      w  = xa;
      v  = xc;
      fv = fc;
    } else {
      w  = xc;
      v  = xa;
      fv = fa;
    }
    x = xb;
    fx = fb;
    a =(xa<xc? xa : xc);  // min(xa,xc);
    b =(xa>xc? xa : xc);  // max(xa,xc);

#define DGM_LINESEARCH_USE_OLD_BRENTS

    for(iteration=1; iteration<=itmax; iteration++) {
      if (outputLevel == TEST_OUTPUT) {
        comm->cout() << yellow << "Brent's iteration: (" << iteration << "/"
            << itmax << ")" << def << std::endl;
      }
      if(iteration<=2) e=2.*(b-a);
      xm=0.5*(a+b);
#ifdef DGM_LINESEARCH_USE_OLD_BRENTS
      // This is what I have used for a long time
      const Scalar tol1 = tol*fabs(x)+TINY;
#else
      // This is what is used at
      // http://www.smallwaters.com/software/cpp/UNCMIN_doc/Fmin_8h.html
      const Scalar tol3 = tol/3.0;
      const Scalar tol1 = TINY*fabs(x) + tol3;
#endif
      const Scalar tol2 = 2.0*tol1;
#ifdef DGM_LINESEARCH_BRENTS_DEBUG
      // Try a different stopping criteria
      std::cout<<"fabs(x-xm) <= tol*(b-a) = "
          <<fabs(x-xm)<<"<="<<tol*(b-a)<<" = "
          <<(fabs(x-xm) <= tol*(b-a))<<std::endl;
      if(fabs(x-xm) <= (tol*(b-a))) {
        xb=x;
        fb=fx;
        return eval.count();
        //return iteration;
      }
      std::cout<<"fabs(x-xm) <= (tol2-0.5*(b-a)) = "
          <<fabs(x-xm)<<"<="<<(tol2-0.5*(b-a))<<" = "
          <<(fabs(x-xm) <= (tol2-0.5*(b-a)))<<std::endl;
#endif
      if(fabs(x-xm) <= (tol2-0.5*(b-a))) {
        xb=x;
        fb=fx;
        return eval.count();
        //return iteration;
      }
      if(fabs(e) > tol1 || iteration <= 2){
        r=(x-w)*(fx-fv);
        q=(x-v)*(fx-fw);
        p=(x-v)*q-(x-w)*r;
        q=2.*(q-r);
        if(q > 0.0) p=-p;
        q=fabs(q);
        etemp=e;
        e=d;
        if(fabs(p)>= fabs(.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x) )
          d=INV_GOLD2*(e=( x>=xm ? a-x : b-x ));
        else {
          d=p/q;
          u=x+d;
          if(u-a < tol2 || b-u < tol2)
            d=( xm-x > 0.0 ? fabs(tol1) : -fabs(tol1) ); // sign(tol1,xm-x)
        }
      } else {
        d=INV_GOLD2*(e=(x>=xm ? a-x : b-x));
      }

      u=(fabs(d)>=tol1 ? x+d : x+(d>=0 ? fabs(tol1) : -fabs(tol1)) );

      fu=eval(u);
      if(fu<=fx) {
        if(u>=x) a=x; else b=x;
        v=w;
        fv=fw;
        w=x;
        fw=fx;
        x=u;
        fx=fu;
      } else {
        if(u<x) a=u; else b=u;
        if(fu <= fw || w==x){
          v=w;
          fv=fw;
          w=u;
          fw=fu;
        } else if(fu <= fv || v==x || v==w) {
          v=u;
          fv=fu;
        }
      }
    }
    comm->cout() <<"Line minimization algorithm did not converge "
        <<"to prescribed\n";
    comm->cout() <<"tolerance in "<<itmax<<" iterations.\n";
    comm->cout() << "x = " << x << ", fx = " << fx << endl;
    xb=x;
    fb=fx;
    //return iteration;
    return eval.count();
  }

  /** Uses Brent's method.  For reference see Richard Brent, 1973, Algorithms
      for Minimization without Derivatives (Englewood Cliffs, N.J.,
      Prentice-Hall), Chapter 5.  As well as the function fmin available from
      NetLib.  Given a valid bracket, Brent's method uses inverse parabolic
      interpolation to find the minimum.

      This is the version coded by Drew Kouri that is more faithful to
      Brent's original implementation.
  */
  Ordinal LineSearch::brents_fmin_new( Scalar &xa, Scalar &xb, Scalar &xc,
                                       Scalar &fa, Scalar &fb, Scalar &fc,
                                       Scalar tol, Ordinal itmax) {

    static Color yellow(Color::YELLOW);
    static Color green(Color::GREEN);
    static Color def(Color::DEFAULT);

    eval.reset();

    if (outputLevel == TEST_OUTPUT) {
      comm->cout() << yellow << "LineSearch::brents_fmin_new called with tol = "
          << tol <<", itmax = " << itmax << def << std::endl;
    }
    const Scalar INV_GOLD2 = 0.3819660112501051518; // (1/golden-ratio)^2
    const Scalar TINY = std::sqrt(epsM);

    Ordinal iteration = 0;
    Scalar d = 0, e = 0, etemp = 0, fu = 0, p = 0, q = 0, r = 0;
    Scalar u = 0, xm = 0;

    xb = xa + INV_GOLD2*(xc-xa); fb = eval(xb);

    // comm->cout() << "DGM::LineSearch::brents_fmin(...)" << std::endl;

    Scalar v = xb, fv = fb;
    Scalar w = xb, fw = fb;
    Scalar x = xb, fx = fb;
    Scalar a = xa, b = xc;

    for ( iteration = 1; iteration <= itmax; iteration++ ) {
      if (outputLevel == TEST_OUTPUT) {
        comm->cout() << green << "Brent's iteration: (" << iteration << "/"
            << itmax << ")" << def << std::endl;
      }
      xm = 0.5*(a+b);
      const Scalar tol1 = TINY*std::abs(x)+tol;
      const Scalar tol2 = 2.0*tol1;

      if ( std::abs(x-xm) <= (tol2-0.5*(b-a)) ) {
        xb = x; fb = fx;
        return eval.count();
        //return iteration;
      }

      if ( std::abs(e) > tol1 ) {
        r = (x-w)*(fx-fv);   q = (x-v)*(fx-fw);
        p = (x-v)*q-(x-w)*r; q = 2.*(q-r);
        if (q > 0.0) {
          p = -p;
        }
        q = std::abs(q);
        etemp = e;
        e = d;
        if ( std::abs(p)>= std::abs(.5*q*etemp) || p <= q*(a-x) ||
            p >= q*(b-x) )
          d = INV_GOLD2*(e = ( x>=xm ? a-x : b-x ));
        else {
          d = p/q;
          u = x+d;
          if ( u-a < tol2 || b-u < tol2 )
            d = ( x < xm ? tol1 : -tol1 ); // sign(tol1,xm-x)
        }
      }
      else {
        d = INV_GOLD2*(e = (x >= xm ? a-x : b-x));
      }
      u = (std::abs(d) >= tol1 ? x+d : x+(d > 0 ? std::abs(tol1) :
          -std::abs(tol1)) );
      fu = eval(u);
      if ( fu <= fx ) {
        if( u >= x ) {
          a = x;
        }
        else {
          b = x;
        }
        v = w; fv = fw;
        w = x; fw = fx;
        x = u; fx = fu;
      }
      else {
        if ( u < x ) {
          a = u;
        }
        else {
          b = u;
        }
        if ( fu <= fw || w == x ){
          v = w; fv = fw;
          w = u; fw = fu;
        }
        else if ( fu <= fv || v==x || v==w ) {
          v = u; fv = fu;
        }
      }
    }
    comm->cout() << "Line minimization algorithm did not converge "
        << "to prescribed\n";
    comm->cout() << "tolerance in " << itmax << " iterations.\n";
    comm->cout() << "x = " << x << ", fx = " << fx << std::endl;
    xb = x; fb = fx;
    //return iteration;
    return eval.count();
  }

} // namespace DGM

/** \file Quadpack.hpp
    \brief Implements a C++ interface to QAGS integrator
    \author S. Scott Collis
    \copyright (c)2003 Rice University
    \copyright (c)2014 Sandia National Laboratories
*/

#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace CMC {

/// Simple C++ interface to Quadpack::qags integrator
/** QUADPACK is a FORTRAN subroutine package for the numerical computation of
    definite one-dimensional integrals. It originated from a joint project of
    R. Piessens and E. de Doncker (Appl.  Math. and Progr. Div.- K.U.Leuven,
    Belgium), C. Ueberhuber (Inst.  Fuer Math.- Techn.U.Wien, Austria), and
    D. Kahaner (Nation. Bur.  of Standards- Washington D.C., U.S.A.).

    QAGS : Is an integrator based on globally adaptive interval
           subdivision in connection with extrapolation (de Doncker,
           1978) by the Epsilon algorithm (Wynn, 1956).

    This C++ class wraps a C version of the Quadpack QAGS routine templated
    on scalar type.

    The original QUADPACK routines were part of SLATEC and are in the PUBLIC
    DOMAIN.

    I started with the C port found at www.crbond.com where it is stated "This
    website contains a variety of materials related to technology and
    engineering. Downloadable software, much of it original, is available from
    some of the pages. All downloadable software is offered freely and without
    restriction -- although in most cases the files should be considered as
    works in progress (alpha or beta level)."

    S. Scott Collis
    Wed Jan  2 09:45:21 MST 2013

    I templated on scalar type, used numeric_limits for the values of
    constants and use std::vector instead of stack allocated storage.  I had
    to also add a few semicolons to get to compile with Clang since a goto
    must go to an actual statement and, of course, wrapped everything in a
    handy class.
*/
template <typename Function, typename Scalar>
class Quadpack {
  const int LIMIT;             /// Maximum number adaptive intervals
  Function &f;                 /// Function to be integrated
  const Scalar epsabs;         /// absolute tolerance
  const Scalar epsrel;         /// relative tolerance
  const Scalar epmach;         /// Machine epsilon
  const Scalar uflow;          /// Underflow limit
  const Scalar oflow;          /// Overflow limit
  Scalar _abserr;              /// Absolute error in most recent integral
  int _neval;                  /// Number of evaluations
  int _ier;                    /// Internal error code
public:
  Quadpack(Function &func, const Scalar _epsabs, const Scalar _epsrel,
           const int limit=500) :
    LIMIT(limit), f(func), epsabs(_epsabs), epsrel(_epsrel),
    epmach(std::numeric_limits<Scalar>::epsilon()),
    uflow(std::numeric_limits<Scalar>::min()),
    oflow(std::numeric_limits<Scalar>::max()),
    _abserr(0), _neval(0), _ier(0)
  {
    //std::cout << "Constructing Quadpack class: " << epsabs
    //          << ", limit = " << LIMIT << std::endl;
  }
  Scalar integrate(const Scalar a, const Scalar b) {
    const Scalar result = qags(a, b, &_abserr, &_neval, &_ier);
    if (_ier) {
      std::stringstream ss;  ss<<"Quadpack runtime error = "<<_ier;
      throw std::runtime_error(ss.str());
    }
    return result;
  }
  Scalar abserr() const { return _abserr; }
  int neval() const { return _neval; }
  int ier() const { return _ier; }
private:
  Scalar qags(Scalar a,Scalar b,Scalar *abserr,int *neval,int *ier);
  Scalar qext(int *n,std::vector<Scalar> &epstab,Scalar *abserr,
              Scalar res3la[],int *nres);
  void qsort(int limit,int last,int *maxerr,Scalar *ermax,
             std::vector<Scalar> &elist,std::vector<int> &iord,int *nrmax);
  Scalar G_K21(Scalar a,Scalar b,Scalar *abserr,Scalar *resabs,Scalar *resasc);
};

/* QAGS - Integration over finite intervals. (From QUADPACK)
 *
 *      Adaptive integration routine which handles functions to be integrated
 *      between two finite bounds.
 *
 *      The adaptive strategy compares results of integration over the given
 *      interval with the sum of results obtained from integration over a
 *      bisected interval. Since error estimates are available from each
 *      regional integration, the region with the largest error is bisected
 *      and new results are computed. This bisection process is continued
 *      until the error is less than the prescribed limit or convergence
 *      failure is determined.
 *
 * PARAMETERS:
 *
 *      f() - function to be integrated.
 *
 *      a - lower limit of integration.
 *
 *      b - upper limit of integration.
 *
 *      epsabs - absolute accuracy requested.
 *
 *      epsrel - relative accuracy requested.
*/
template <typename Function, typename Scalar>
Scalar Quadpack<Function,Scalar>::qags(Scalar a,Scalar b,
                                       Scalar *abserr,int *neval,int *ier)
{
  std::vector<Scalar> alist(LIMIT), blist(LIMIT), elist(LIMIT), rlist(LIMIT);
  Scalar abseps,area,area1,area12,area2;
  Scalar a1,a2,b1,b2,correc(0),defabs,defab1;
  Scalar defab2,dres,erlarg(0),erlast,errbnd;
  Scalar errmax(0),error1,error2,erro12,errsum,ertest(0);
  Scalar resabs,reseps,result,res3la[3];
  std::vector<Scalar> rlist2(LIMIT);
  Scalar small(0);

  std::vector<int> iord(LIMIT);
  int id,ierro,iroff1,iroff2,iroff3,jupbnd,k,ksgn;
  int ktmin,last,maxerr,nres,nrmax,numrl2;
  int limit;
  bool extrap,noext;

  limit = LIMIT - 1;
  /* Test validity of parameters. */
  *ier = 0;
  *neval = 0;
  result = 0.0;
  *abserr = 0.0;
  alist[0] = a;
  blist[0] = b;
  rlist[0] = 0.0;
  elist[0] = 0.0;
  if ((epsabs < 0.0) && (epsrel < 0.0)) *ier = 6;
  if (*ier == 6) return result;

  /* First approximation to the integral. */
  ierro = 0;
  result = G_K21(a,b,abserr,&defabs,&resabs);

  /* Test on accuracy. */
  dres = fabs(result);
  errbnd = std::max(epsabs,epsrel*dres);
  last = 1;
  rlist[0] = result;
  elist[0] = *abserr;
  iord[0] = 0;
  if ((*abserr <= 100.0 * epmach * defabs) && (*abserr > errbnd))
    *ier = 2;
  if (limit == 0) *ier = 1;
  if ((*ier != 0) || ((*abserr <= errbnd) && (*abserr != resabs)) ||
      (*abserr == 0.0)) goto _140;

  /* Initialization. */
  rlist2[0] = result;
  errmax = *abserr;
  maxerr = 0;        /* maxerr = 1 */
  area = result;
  errsum = *abserr;
  *abserr = oflow;
  nrmax = 0;
  nres = 0;          /* nres = 0 */
  numrl2 = 1;        /* numrl2 = 2 */
  ktmin = 0;
  extrap = false;
  noext = false;
  ierro = 0;
  iroff1 = 0;
  iroff2 = 0;
  iroff3 = 0;
  ksgn = -1;
  if (dres > (1.0 - 50.0 * epmach) * defabs) ksgn = 1;

  /* Main loop. */
  for (last = 1; last <= limit; last++) {

    /* Bisect the interval with the nrmax-th largest error estimate. */
    a1 = alist[maxerr];
    b1 = 0.5 * (alist[maxerr] + blist[maxerr]);
    a2 = b1;
    b2 = blist[maxerr];
    erlast = errmax;
    area1 = G_K21(a1,b1,&error1,&resabs,&defab1);
    area2 = G_K21(a2,b2,&error2,&resabs,&defab2);

    /* Improve previous approxminations to integral and error
       and test for accuracy. */
    area12 = area1 + area2;
    erro12 = error1 + error2;
    errsum = errsum + erro12 - errmax;
    area = area + area12 - rlist[maxerr];
    if ((defab1 == error1) || (defab2 == error2)) goto _15;
    if ((fabs(rlist[maxerr] - area12) > 1.0e-5 * fabs(area12))
        || (erro12 < .99 * errmax)) goto _10;
    if (extrap) iroff2++;
    else iroff1++;
  _10:
    if ((last > 9) && (erro12 > errmax))    /* last > 10 */
      iroff3++;
  _15:
    rlist[maxerr] = area1;
    rlist[last] = area2;
    errbnd = std::max(epsabs,epsrel * fabs(area));

    /* Test for roundoff error and eventually set error flag. */
    if (((iroff1 + iroff2) >= 10) || (iroff3 >= 20))
      *ier = 2;
    if (iroff2 > 5)
      *ier = 3;

    /* Set error flag in the case that the number of subintervals
       equals limit. */
    if (last == limit) { /* last == limit */
      *ier = 1;
    }

    /* Set error flag in the case of bad integrand behavior at some
       points in the integration range. */
    if (std::max(fabs(a1),fabs(b2)) <= (1.0 +1000.0 * epmach) *
        (fabs(a2) + 1000.0*uflow))
      *ier = 4;

    /* Append the newly-created intervals to the list. */
    if (error2 > error1) goto _20;
    alist[last] = a2;
    blist[maxerr] = b1;
    blist[last] = b2;
    elist[maxerr] = error1;
    elist[last] = error2;
    goto _30;
  _20:
    alist[maxerr] = a2;
    alist[last] = a1;
    blist[last] = b1;
    rlist[maxerr] = area2;
    rlist[last] = area1;
    elist[maxerr] = error2;
    elist[last] = error1;

    /* Call dqsort to maintain the descending ordering in the list of error
       estimates and select the subinterval with nrmax-th largest error
       estimate (to be bisected next). */
  _30:
    qsort(limit,last,&maxerr,&errmax,elist,iord,&nrmax);
    if (errsum <= errbnd) goto _115;
    if (*ier != 0) goto _100;
    if (last == 1) goto _80;            /* last == 2 */
    if (noext) goto _90;
    erlarg -= erlast;
    //std::cout << "0:small = " << small << std::endl;
    if (fabs(b1-a1) > small)
      erlarg += erro12;
    if (extrap) goto _40;

    /* Test whether the interval to be bisected next is the smallest
       interval. */
    //std::cout << "1:small = " << small << std::endl;
    if ((fabs(blist[maxerr] - alist[maxerr])) > small)
      goto _90;
    extrap = true;
    nrmax = 1;                          /* nrmax = 2 */
  _40:
    if ((ierro == 3) || (erlarg <= ertest)) goto _60;

    /* The smallest interval has the largest error. Before bisecting, decrease
       the sum of the erors over the larger intervals (erlarg) and perform
       extrapolation.) */
    id = nrmax;
    jupbnd = last;
    if (last > (2 + limit/2))
      jupbnd = limit + 3 - last;
    for (k = id;k <= jupbnd; k++) {
      maxerr = iord[nrmax];
      errmax = elist[maxerr];
      //std::cout << "2:small = " << small << std::endl;
      if (fabs(blist[maxerr] - alist[maxerr]) > small)
        goto _90;
      nrmax++;
    }

    /* Perform extrapolation. */
  _60:
    numrl2++;
    rlist2[numrl2] = area;
    reseps=qext(&numrl2,rlist2,&abseps,res3la,&nres);
    ktmin++;
    if ((ktmin > 5) && (*abserr < 1.0e-3 * errsum)) *ier = 5;
    if (abseps >= *abserr) goto _70;
    ktmin = 0;
    *abserr = abseps;
    result = reseps;
    correc = erlarg;
    ertest = std::max(epsabs,epsrel * fabs(reseps));
    if (*abserr <= ertest) goto _100;

    /* Prepare bisection of the smallest interval. */
  _70:
    if (numrl2 == 0) noext = true;
    if (*ier == 5) goto _100;
    maxerr = iord[0];
    errmax = elist[maxerr];
    nrmax = 0;
    extrap = false;
    //std::cout << "3:small = " << small << std::endl;
    small = small * 0.5;
    erlarg = errsum;
    goto _90;
  _80:
    //std::cout << "4:small = " << small << std::endl;
    small = fabs(b-a)*0.375;
    erlarg = errsum;
    ertest = errbnd;
    rlist2[1] = area;
  _90:
    ;
  }
 _100:
  if (*abserr == oflow) goto _115;
  if ((*ier + ierro) == 0) goto _110;
  if (ierro == 3) *abserr += correc;
  if (*ier == 0) *ier = 3;
  if ((result != 0.0) && (area != 0.0)) goto _105;
  if (*abserr > errsum) goto _115;
  if (area == 0.0) goto _130;
  goto _110;
 _105:
  if (*abserr/fabs(result) > errsum/fabs(area)) goto _115;

  /* Test on divergence. */
 _110:
  if ((ksgn == -1) && (std::max(fabs(result),fabs(area)) <= defabs * .01))
    goto _130;
  if ((0.01 > result/area) || (result/area > 100.0) ||
      (errsum > fabs(area))) *ier = 6;
  goto _130;

  /* Compute global integral. */
 _115:
  result = 0.0;
  for (k = 0; k <= last; k++)
    result += rlist[k];
  *abserr = errsum;
 _130:
  if (*ier > 2) (*ier)--;
 _140:
  *neval = 42 * last - 21;
  return result;
}

template <typename Function, typename Scalar>
Scalar Quadpack<Function,Scalar>::qext(int *n,std::vector<Scalar> &epstab,
                                       Scalar *abserr,Scalar res3la[],
                                       int *nres)
{
  Scalar delta1,delta2,delta3,epsinf;
  Scalar error,err1,err2,err3,e0,e1,e1abs,e2,e3;
  Scalar res,result,ss,tol1,tol2,tol3;
  int NN,i,ib,ib2,ie,indx,k1,k2,k3,limexp,newelm,num;

  (*nres)++;
  NN = *n;
  NN++;                                 /* make NN a FORTRAN array index */
  *abserr = oflow;
  result = epstab[*n];
  if (NN < 3) goto _100;                /* N < 3 */
  limexp = 50;                          /* limexp = 50 */
  epstab[*n+2] = epstab[*n];
  newelm = (*n)/2;                      /* (n-1)/2 */
  epstab[*n] = oflow;
  num = NN;
  k1 = NN;
  for (i = 1; i <= newelm; i++) {
    k2 = k1 - 1;
    k3 = k1 - 2;
    res = epstab[k1+1];
    e0 = epstab[k3-1];
    e1 = epstab[k2-1];
    e2 = res;
    e1abs = fabs(e1);
    delta2 = e2 - e1;
    err2 = fabs(delta2);
    tol2 = std::max(fabs(e2),e1abs) * epmach;
    delta3 = e1 - e0;
    err3 = fabs(delta3);
    tol3 = std::max(e1abs,fabs(e0)) * epmach;
    if ((err2 > tol2) || (err3 > tol3)) goto _10;
    result = res;
    *abserr = err2 + err3;
    goto _100;
  _10:
    e3 = epstab[k1-1];
    epstab[k1-1] = e1;
    delta1 = e1 - e3;
    err1 = fabs(delta1);
    tol1 = std::max(e1abs,fabs(e3)) * epmach;
    if ((err1 <= tol1) || (err2 <= tol2) || (err3 <= tol3)) goto _20;
    ss = 1.0/delta1 + 1.0/delta2 - 1.0/delta3;
    epsinf = fabs(ss*e1);
    if (epsinf > 1.0e-4) goto _30;
  _20:
    NN = i + i - 1;
    goto _50;
  _30:
    res = e1 + 1.0 / ss;
    epstab[k1-1] = res;
    k1 -= 2;
    error = err2 + fabs(res - e2) + err3;
    if (error > (*abserr)) goto _40;
    *abserr = error;
    result = res;
  _40:
    ;
  }
 _50:
  if (NN == limexp) NN = 2 * (limexp/2) - 1;
  ib = 1;                                       /* ib = 1 */
  if (((num/2) * 2 ) == num) ib = 2;            /* ib = 2 */
  ie = newelm + 1;
  for (i = 1;i <= ie; i++) {
    ib2 = ib + 2;
    epstab[ib-1] = epstab[ib2-1];
    ib = ib2;
  }
  if (num == NN) goto _80;
  indx = num - NN + 1;
  for (i = 1;i <= NN; i++) {
    epstab[i-1] = epstab[indx-1];
    indx++;
  }
 _80:
  if (*nres > 3) goto _90;                      /* nres >= 4 */
  res3la[(*nres)-1] = result;
  *abserr = oflow;
  goto _100;
 _90:
  *abserr = fabs(result - res3la[2]) + fabs(result - res3la[1]) +
    fabs(result - res3la[0]);
  res3la[0] = res3la[1];
  res3la[1] = res3la[2];
  res3la[2] = result;
 _100:
  *abserr = std::max(*abserr,5.0 * epmach * fabs(result));
  *n = NN - 1;
  return result;
}

template <typename Function, typename Scalar>
void Quadpack<Function,Scalar>::qsort(int limit,int last,
                                      int *maxerr,Scalar *ermax,
                                      std::vector<Scalar> &elist,
                                      std::vector<int> &iord,int *nrmax)
{
  Scalar errmax,errmin;
  int i,ibeg,ido,isucc,j,jbnd,jupbn,k;

  if (last > 1) goto _10;
  iord[0] = 0;
  iord[1] = 1;
  goto _90;
 _10:
  errmax = elist[*maxerr];
  if (*nrmax == 0) goto _30;
  ido = (*nrmax) - 1;
  for (i = 0;i <= ido; i++) {
    isucc = iord[*nrmax-1];
    if (errmax <= elist[isucc]) goto _30;
    iord[*nrmax] = isucc;
    (*nrmax)--;
  }
 _30:
  jupbn = last;
  if (last > (limit/2 + 2))
    jupbn = limit + 3 - last;
  errmin = elist[last];
  jbnd = jupbn - 1;
  ibeg = *nrmax + 1;
  if (ibeg > jbnd) goto _50;
  for (i = ibeg; i <= jbnd; i++) {
    isucc = iord[i];
    if (errmax >= elist[isucc]) goto _60;
    iord[i-1] = isucc;
  }
 _50:
  iord[jbnd] = *maxerr;
  iord[jupbn] = last;
  goto _90;
 _60:
  iord[i-1] = *maxerr;
  k = jbnd;
  for (j = i;j <= jbnd; j++) {
    isucc = iord[k];
    if (errmin < elist[isucc]) goto _80;
    iord[k+1] = isucc;
    k--;
  }
  iord[i] = last;
  goto _90;
 _80:
  iord[k+1] = last;
 _90:
  *maxerr = iord[*nrmax];
  *ermax = elist[*maxerr];
  return;
}

template <typename Function,typename Scalar>
Scalar Quadpack<Function,Scalar>::G_K21(Scalar a,Scalar b,
                                        Scalar *abserr,Scalar *resabs,
                                        Scalar *resasc)
{
  static Scalar XGK21[11] = {
    0.99565716302580808074,
    0.97390652851717172008,
    0.93015749135570822600,
    0.86506336668898451073,
    0.78081772658641689706,
    0.67940956829902440623,
    0.56275713466860468334,
    0.43339539412924719080,
    0.29439286270146019813,
    0.14887433898163121088,
    0.00000000000000000000};
  static Scalar WGK21[11] = {
    0.01169463886737187428,
    0.03255816230796472748,
    0.05475589657435199603,
    0.07503967481091995277,
    0.09312545458369760554,
    0.10938715880229764190,
    0.12349197626206585108,
    0.13470921731147332593,
    0.14277593857706008080,
    0.14773910490133849137,
    0.14944555400291690566};
  static Scalar WG10[5] = {
    0.06667134430868813759,
    0.14945134915058059315,
    0.21908636251598204400,
    0.26926671930999635509,
    0.29552422471475287017};
  Scalar fv1[10],fv2[10];
  Scalar absc,centr,dhlgth;
  Scalar fc,fsum,fval1,fval2,hlgth;
  Scalar resg,resk,reskh,result;
  int j,jtw,jtwm1;

  centr = 0.5 * (a + b);
  hlgth = 0.5 * (b - a);
  dhlgth = fabs(hlgth);

  resg = 0.0;
  fc=f(centr);
  resk = fc * WGK21[10];
  *resabs = fabs(resk);
  for (j = 0; j < 5; j++) {
    jtw = 2 * j + 1;
    absc = hlgth * XGK21[jtw];
    fval1 = f(centr-absc);
    fval2 = f(centr+absc);
    fv1[jtw] = fval1;
    fv2[jtw] = fval2;
    fsum = fval1 + fval2;
    resg += WG10[j] * fsum;
    resk += WGK21[jtw] * fsum;
    *resabs = *resabs + WGK21[jtw] * (fabs(fval1) + fabs(fval2));
  }
  for (j = 0; j < 5; j++) {
    jtwm1 = j * 2;
    absc = hlgth * XGK21[jtwm1];
    fval1 = f(centr-absc);
    fval2 = f(centr+absc);
    fv1[jtwm1] = fval1;
    fv2[jtwm1] = fval2;
    fsum = fval1 + fval2;
    resk = resk + WGK21[jtwm1] * fsum;
    *resabs = (*resabs) + WGK21[jtwm1] * (fabs(fval1) + fabs(fval2));
  }
  reskh = resk * 0.5;
  *resasc = WGK21[10] * fabs(fc - reskh);
  for (j = 0; j < 10; j++ )
    *resasc = (*resasc) + WGK21[j] * (fabs(fv1[j] - reskh) +
                                      fabs(fv2[j] - reskh));
  result = resk * hlgth;
  *resabs = (*resabs) * dhlgth;
  *resasc = (*resasc) * dhlgth;
  *abserr = fabs((resk - resg) * hlgth);
  if ((*resasc != 0.0) && (*abserr != 0.0))
    *abserr = (*resasc) * std::min(1.0,pow((200.0 * (*abserr)/(*resasc)),1.5));
  if (*resabs > uflow/(50.0 * epmach))
    *abserr = std::max(epmach * 50.0 * (*resabs),(*abserr));
  return result;
}

} // namespace CMC

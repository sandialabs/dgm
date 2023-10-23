/* Original sample function */
void f(double *x, double *y) {
  *y = sin(*x);
}

/* Original rk3 function */
void func(double *x, double *y) {
 double u, ut, r0, r1;
 double b0 = 1.0;
 double b1 = 1.0/4.0;
 double b2 = 2.0/3.0;
 double dt = 1.0;
 double a10 = 3.0/4.0;
 double a11 = 1.0/4.0;
 double a20 = 1.0/3.0;
 double a22 = 2.0/3.0; 

 u = *x;

 f(&u,&ut);
 r0 = u + b0*dt*ut;
 f(&r0,&r1);
 r1 *= b1*dt;
 r1 += a10*u;
 r1 += a11*r0;

 f(&r1,&ut);
 ut *= b2*dt;
 ut += a20*u;
 u  = ut + a22*r1;

 *y = u;
}

/*
  Differentiation of f in reverse (adjoint) mode:
   gradient     of useful results: *x *y
   with respect to varying inputs: *x
   Plus diff mem management of: x:in y:in
*/
void f_b(double *x, double *xb, double *y, double *yb) {
    *xb = *xb + cos(*x)*(*yb);
}

/*
  Differentiation of func in reverse (adjoint) mode:
   gradient     of useful results: *y
   with respect to varying inputs: *x *y
   RW status of diff variables: *x:out *y:in-zero
   Plus diff mem management of: x:in y:in
*/
void func_b(double *x, double *xb, double *y, double *yb) {
    double u, ut, r0, r1;
    double ub, utb, r0b, r1b;
    double b0 = 1.0;
    double b1 = 1.0/4.0;
    double b2 = 2.0/3.0;
    double dt = 1.0;
    double a10 = 3.0/4.0;
    double a11 = 1.0/4.0;
    double a20 = 1.0/3.0;
    double a22 = 2.0/3.0;
    u = *x;
    f(&u, &ut);
    r0 = u + b0*dt*ut;
    f(&r0, &r1);
    r1 = r1*(b1*dt);
    r1 = r1 + a10*u;
    r1 = r1 + a11*r0;
    ub = *yb;
    utb = ub;
    r1b = a22*ub;
    ub = a20*utb;
    utb = b2*dt*utb;
    f_b(&r1, &r1b, &ut, &utb);
    r0b = a11*r1b;
    ub = ub + a10*r1b;
    r1b = b1*dt*r1b;
    f_b(&r0, &r0b, &r1, &r1b);
    ub = ub + r0b;
    utb = b0*dt*r0b;
    f_b(&u, &ub, &ut, &utb);
    *xb = ub;
    *yb = 0.0;
}

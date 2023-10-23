// random.hpp

#ifndef RANDOM_H
#define RANDOM_H

// see http://www.thecodingforums.com/threads/re-rngs-a-double-kiss.720512/


class Random
{

public:

  // sets the seed
  void initiate_random_generator(unsigned long x = 1391722129);

  // u in [0,1]
  double generate_a_random_number();

  // pick uniformly from A to B
  double random_uniform(double A, double B);

  Random() { initiate_random_generator(); }

// provided one a global, so we can set the seed just once
// but this is not required
  static Random random_instance;

private:
  // variables for Random number generator
	double Q[1220];
	int indx;
	double cc;
	double c; /* current CSWB */
	double zc;	/* current SWB `borrow` */
	double zx;	/* SWB seed1 */
	double zy;	/* SWB seed2 */
//	size_t qlen;/* length of Q array */
  
};

#endif
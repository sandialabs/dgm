/** \file test_matrix_operations.cpp
    \brief Matrix operations test case
    \author N. Belcourt

    Cases testing matrix operations

    clang++ -mavx -O3 -std=c++11 -I $DGM_TPL/atlas/include -I $DGM_DIST/src
      -I $DGM_TPL/boost/include test_matrix_operations.cpp
*/


#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

typedef double Scalar;

#define DGM_USE_COMPILETIMEQUAD

#include "MatrixOperations.hpp"

using std::array;
using std::begin;
using std::copy;
using std::cout;
using std::end;
using std::endl;
using std::equal;
using std::iota;
using std::ostream_iterator;
using std::runtime_error;
using std::string;
using std::vector;

template <typename Iterator>
void initialize(Iterator it, Iterator end, int N) {
  for (int i=0; i<N; ++i, it+=N) {
    iota(it, it+N, 1);
  }
}

template <typename Iterator>
void initialize(Iterator it, Iterator end) {
  iota (it, end, 1);
}

template <typename Iterator>
void inverse_initialize(Iterator it, Iterator end, int N) {
  for (int i=0; i<N; ++i) {
    for (int j=0; j<N; ++j, ++it) {
      *it = 1.0 /(i+1);
    }
  }
}

template <typename Iterator>
void inverse_initialize(Iterator it, Iterator end) {
  initialize(it, end);
  for (; it != end; ++it) {
    *it = 1.0 / *it;
  }
}

// fill with sequential values starting from zero in layout order
template <typename Iterator>
void fill(Iterator it, Iterator end) {
  for (int k=0; it != end; ++it, ++k) {
    *it = k;
  }
}

template <int I, int J, typename Iterator, typename Stream>
void output(string label, Iterator it, Stream& s) {
  typedef typename iterator_traits<Iterator>::value_type value_type;
  s << label << endl;
  for (int i=0; i<I; ++i) {
    copy(it, it+J, ostream_iterator<value_type>(s, " "));
    cout << endl;
    it += J;
  }
  s << endl;
}

int main(int, char**) {
  try {
  cout.precision(std::numeric_limits<double>::max_digits10);

  // call implementation for number not divisible by avx_size
  constexpr int N = 17;
  array<double, N> a, b;
  array<double, N> r1;
  fill(begin(r1), end(r1), 1);
  initialize(begin(a), end(a));
  inverse_initialize(begin(b), end(b));
  DGM::multiply<N>(begin(a), end(a), begin(b));
  if (!equal(begin(a), end(a), begin(r1))) {
    throw runtime_error("Error: computed wrong vector product result.");
  }

  // call implementation for number evenly divisible by avx_size
  constexpr int M = 16;
  array<double, M> c, d;
  array<double, M> r2;
  fill(begin(r2), end(r2), 1);
  initialize(begin(c), end(c));
  inverse_initialize(begin(d), end(d));
  DGM::multiply<M>(begin(c), end(c), begin(d));
  if (!equal(begin(c), end(c), begin(r2))) {
    throw runtime_error("Error: computed wrong matrix product result.");
  }

  // small [4,4] matrix multiply
  array<double, 16> simd_aresult = {
    { 56, 62, 68, 74, 152, 174, 196, 218, 248, 286, 324, 362, 344, 398, 452, 506 }
  };
  array<double, 16> as, bs, cs;
  fill(begin(as), end(as));
  fill(begin(bs), end(bs));
  DGM::multiply<4,4,4>(begin(cs), begin(as), begin(bs));
  if (!equal(begin(simd_aresult), end(simd_aresult), begin(cs))) {
    throw runtime_error("Error: computed wrong matrix product result.");
  }

  // cache line size [8,8] matrix multiply
  array<double, 64> r3;
  array<double, 64> at, bt, ct;
  fill(begin(r3), end(r3), 8);
  initialize(begin(at), end(at), 8);
  inverse_initialize(begin(bt), end(bt), 8);
  DGM::multiply<8,8,8>(begin(ct), begin(at), begin(bt));
  if (!equal(begin(ct), end(ct), begin(r3))) {
    throw runtime_error("Error: computed wrong matrix product result.");
  }

  // cache line size [16,16] matrix multiply
  array<double, 256> r4;
  array<double, 256> ar, br, cr;
  fill(begin(r4), end(r4), 16);
  initialize(begin(ar), end(ar), 16);
  inverse_initialize(begin(br), end(br), 16);
  DGM::multiply<16,16,16>(begin(cr), begin(ar), begin(br));
  if (!equal(begin(cr), end(cr), begin(r4))) {
    throw runtime_error("Error: computed wrong matrix product result.");
  }

  // cache line size [256,256] matrix multiply
  array<double, 65536> r5;
  array<double, 65536> aq, bq, cq;
  fill(begin(r5), end(r5), 256);
  initialize(begin(aq), end(aq), 256);
  inverse_initialize(begin(bq), end(bq), 256);
  DGM::multiply<256,256,256>(begin(cq), begin(aq), begin(bq));
  if (!equal(begin(cq), end(cq), begin(r5))) {
    throw runtime_error("Error: computed wrong matrix product result.");
  }

  // test cases for non-square matrices
  // a[6,7]
  array<double, 42> a_init = {{
      0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548
    , -1.22474487139159, -1.01681245907392, -0.574220155261392, 0, 0.574220155261392, 1.01681245907392, 1.22474487139159
    , 1.58113883008419, 0.844182001556939, -0.26922242698087, -0.790569415042095, -0.26922242698087, 0.844182001556939, 1.58113883008419
    , -1.87082869338697, -0.346643573228285, 0.833675471702112, -0, -0.833675471702112, 0.346643573228285, 1.87082869338697
    , 2.12132034355964, -0.278372647949334, -0.504704283282048, 0.795495128834866, -0.504704283282048, -0.278372647949334, 2.12132034355964
    , -2.34520787991171, 0.807538898284277, -0.365166265456773, 0, 0.365166265456773, -0.807538898284277, 2.34520787991171
  }};
  array<double, 42> A(a_init);

  array<double, 42> b_init = {{
      0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548, 0.707106781186548
    , -1.22474487139159, -1.01681245907392, -0.574220155261392, 0, 0.574220155261392, 1.01681245907392, 1.22474487139159
    , 1.58113883008419, 0.844182001556939, -0.26922242698087, -0.790569415042095, -0.26922242698087, 0.844182001556939, 1.58113883008419
    , -1.87082869338697, -0.346643573228285, 0.833675471702112, -0, -0.833675471702112, 0.346643573228285, 1.87082869338697
    , 2.12132034355964, -0.278372647949334, -0.504704283282048, 0.795495128834866, -0.504704283282048, -0.278372647949334, 2.12132034355964
    , -2.34520787991171, 0.807538898284277, -0.365166265456773, 0, 0.365166265456773, -0.807538898284277, 2.34520787991171
  }};
  array<double, 42> B(b_init);
  // transpose<matrix<6,7>,edr::column_major> bT(b);

  array<double, 49> f, fT;
  // transpose<matrix<7,7,edr::row_major>, edr::column_major> fT(f);
  fill(begin(f), end(f), 0.454545454545455);
  fill(begin(fT), end(fT), 0.454545454545455);

  array<double, 49> wJ = {{
      5.66893424036281
    , 32.9554818287579
    , 51.3982596678408
    , 58.0498866213152
    , 51.3982596678408
    , 32.9554818287579
    , 5.66893424036281
    , 32.9554818287579
    , 191.58165124457
    , 298.795918367347
    , 337.464133926481
    , 298.795918367347
    , 191.58165124457
    , 32.9554818287579
    , 51.3982596678408
    , 298.795918367347
    , 466.010185490124
    , 526.31817899869
    , 466.010185490124
    , 298.795918367347
    , 51.3982596678408
    , 58.0498866213152
    , 337.464133926481
    , 526.31817899869
    , 594.430839002268
    , 526.31817899869
    , 337.464133926481
    , 58.0498866213152
    , 51.3982596678408
    , 298.795918367347
    , 466.010185490124
    , 526.31817899869
    , 466.010185490124
    , 298.795918367347
    , 51.3982596678408
    , 32.9554818287579
    , 191.58165124457
    , 298.795918367347
    , 337.464133926481
    , 298.795918367347
    , 191.58165124457
    , 32.9554818287579
    , 5.66893424036281
    , 32.9554818287579
    , 51.3982596678408
    , 58.0498866213152
    , 51.3982596678408
    , 32.9554818287579
    , 5.66893424036281
  }};
  // output weighted Jacobian
  output<7,7>("wJ", begin(wJ), cout);
  // f before applying weight Jacobian
  output<7,7>("f", begin(f), cout);
  // f *= wJ
  DGM::multiply<42>(begin(f), end(f), begin(wJ));
  output<7,7>("f *= wJ", begin(f), cout);
  // tmp[6,7]=A[6,7]*fT[7,7]
  array<double, 42> tmp;
  array<double, 42>::iterator it = begin(tmp);
  DGM::multiply<6,7,7>(begin(tmp), begin(A), begin(f));
  output<6,7>("a * f", begin(tmp), cout);

#if 0
Index    DGM                               Noel
[0]        76.5267079206221         76.526707920622201
[1]        444.876307496436        444.87630749643665
[2]        693.84110636242         693.84110636242133
[3]        783.63348910717         783.6334891071715
[4]        693.84110636242         693.84110636242133
[5]        444.876307496436        444.87630749643665
[6]        76.526707920622          76.526707920622201

[7]       -4.21450338513525e-15     4.4408920985006262e-16
[8]       -6.1357785656618e-15     -1.0658141036401503e-14
[9]        3.04080298113068e-14     1.0658141036401503e-14
[10]      -5.01470949930762e-14    -1.4210854715202004e-14
[11]       3.04080298113068e-14     1.0658141036401503e-14
[12]      -6.1357785656618e-15     -1.0658141036401503e-14
[13]      -4.44089209850063e-15     4.4408920985006262e-16

[14]       2.23606283402035e-14     1.5099033134902129e-14
[15]       1.16585619502093e-13    -1.2434497875801753e-13
[16]       1.6289220481115e-13     -1.2079226507921703e-13
[17]       2.43098929332842e-13     1.8474111129762605e-13
[18]       1.6289220481115e-13     -1.2079226507921703e-13
[19]       1.16585619502093e-13    -1.2434497875801753e-13
[20]       2.22044604925031e-14     1.5099033134902129e-14

[21]      -1.63814828326956e-15    -8.8817841970012523e-16
[22]      -7.287184076269e-15       3.5527136788005009e-15
[23]       1.26027395228301e-14     7.1054273576010019e-15
[24]       9.10808606730746e-15     7.1054273576010019e-15
[25]      -1.60811519237191e-15     7.1054273576010019e-15
[26]      -1.81756718668e-16        3.5527136788005009e-15
[27]       0                       -8.8817841970012523e-16

[28]       1.43314041899793e-14     1.0658141036401503e-14
[29]       6.90966601638085e-14     4.2632564145606011e-13
[30]       1.64325681308578e-13     3.979039320256561e-13
[31]       1.77465758230408e-13     1.7763568394002505e-13
[32]       1.50114826593376e-13     3.979039320256561e-13
[33]       7.62020875214095e-14     4.2632564145606011e-13
[34]       1.4210854715202e-14      1.0658141036401503e-14

[35]      -1.27469651573211e-15     0
[36]       3.11246483690244e-15     0
[37]      -2.96303456391077e-15     0
[38]       5.55669768554016e-15     0
[39]      -2.96303456391077e-15     0
[40]       3.11246483690244e-15     0
[41]       0                        0
#endif

#if 0
  cout << "b" << bT << endl;
  cout << "a * f = \n" << tmp << endl;
  result = tmp * bT;
  cout << "result = \n" << result << endl;
#endif
  }
  catch (runtime_error& e) {
    cout << e.what() << endl;
  }

  return 0;
}

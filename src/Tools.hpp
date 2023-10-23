#ifndef DGM_TOOLS_HPP
#define DGM_TOOLS_HPP

/** \file Tools.hpp
    \brief Functions used to sort arrays and methods needed for p-Refinement.
    \author Scott Collis
*/

// system includes
#include <fstream>
#include <cmath>

namespace DGM {

  /// Quick sort tools
  template <class T>
  class QuickSort {
    T *A;
  public:
    QuickSort(T *a) : A(a) {}
    void Sort(int, int);
  private:
    void Swap(int, int);
    int  Partition(int, int);
  };

  template <class T>
  void QuickSort<T>::Swap(int a, int b) {
    T x = A[a];
    A[a] = A[b];
    A[b] = x;
  }

  template <class T>
  int QuickSort<T>::Partition (int low, int hi) {
    const int pivotIndex = (hi + low) / 2;
    const T pivot = A[pivotIndex];
    A[pivotIndex] = A[hi];
    A[hi] = pivot;
    int below = low - 1;
    int above = hi;
    while(below < above) {
      do below++; while (A[below] < pivot);
      do above--; while ( (above > low) && (A[above] > pivot));
      if(below < above)
        swap(above,below);
    }
    A[hi] = A[below];
    A[below] = pivot;
    return below;
  }

  template <class T>
  void QuickSort<T>::Sort(int first, int last) {
    if (first >= last) return;
    int pivot = Partition(first, last);
    Sort(first, pivot-1);
    Sort(pivot+1, last);
  }

  // Tools for p-refinement

  /// Information for element-based error estimation
  class ErrorElmtInfo {
  public:
    int elementNumber;       ///< The element number (perhaps a bit obsolete)
    Scalar error;            ///< Error estimate on each element
    bool marked, output;     ///< Used to determine if marked for refinement
    unsigned int pElmt;      ///< Order of element
    /// match element info
    static inline int match(Scalar val, ErrorElmtInfo *elmt_info, int length);
  };

  /** This function goes through the list of unsorted element errors
      contained in 'elmt_info' and attempts to match an error value with
      that of 'val'. If a match is found, the 'marked' flag is toggled so
      that the same element cannot be used again in the event that multiple
      elements have the same error. 'length' is the total length of the
      array 'elmt_info'.
*/
  inline int ErrorElmtInfo::match(Scalar val, ErrorElmtInfo *elmt_info,
                                  int length) {
    for (unsigned int i = 0; i < length; i++) {
      using std::fabs;
      if ((val == fabs(elmt_info[i].error)) && (!elmt_info[i].marked)) {
        /* An element is marked here if it has been matched (i.e. refined).  We
           mark it in here to prevent elements with identical errors from being
           refined more than once. */
        elmt_info[i].marked = true;
        return elmt_info[i].elementNumber;
      }
    }
    return -1;
  }

} // namespace DGM

#endif  // DGM_TOOLS_HPP

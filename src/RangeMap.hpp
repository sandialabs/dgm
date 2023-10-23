/** \file RangeMap.hpp
    \brief A range map for use with boost
    \author K. Noel Belcourt
*/

#ifndef RangeMap_hpp
#define RangeMap_hpp

#include <cassert>
#include <map>
#include <utility>

namespace DGM {

template <typename Range>
struct strict_weak_range : Range {

  // range is pair<T,T> delimiting contiguous closed interval [r1,r2]

  template <typename Index1, typename Index2>
  strict_weak_range(Index1 i1, Index2 i2) : Range(i1,i2) {
  }

  strict_weak_range(Range arg) : Range(arg) {
  }

  bool operator<(strict_weak_range<Range> r) const {
    // return true if first range is less than second, false ow
    return Range::second < r.first;
  }
};

template <typename ElementId, typename ProcessorId>
struct range_map {

  typedef                       ElementId  element_id;
  typedef std::pair<ElementId, ElementId>  range;
  typedef ProcessorId                      value;

  typedef std::map<strict_weak_range<range>,value>         container;
  typedef typename container::key_type                     key_type;
  typedef typename container::value_type                   value_type;
  typedef typename container::iterator                     iterator;
  typedef typename container::const_iterator               const_iterator;
  typedef std::pair<iterator, bool>                        container_pib;

  // invariant: closed contiguous range of element ids map to owning processor

  // elements all owned by one processor
  template <typename ElemIterator>
  void insert(ElemIterator it, ElemIterator end, ProcessorId p_id);
  void insert(ElementId eid, ProcessorId p_id);

  iterator find(key_type kt) { return index_map.find(kt); }
  iterator begin() { return index_map.begin(); }
  iterator end() { return index_map.end(); }
  bool empty() const { return index_map.empty(); }
  void clear() { index_map.clear(); }

  // return associated processor
  ProcessorId proc(ElementId id) const {
    const_iterator it = index_map.find(key_type(id,id));
    assert(it != index_map.end());
    return (*it).second;
  }

  template <typename Stream>
  void print(Stream& s);

  container index_map;
};

// member functions

template <typename ElementId, typename ProcessorId>
template <typename Stream>
void range_map<ElementId,ProcessorId>::print(Stream& s) {
  s << "range_map contents" << endl;
  iterator it = index_map.begin();
  iterator end = index_map.end();
  for (; it != end; ++it) {
    s << "  range [" << (*it).first.first << "," << (*it).first.second 
      << "] = " << (*it).second << endl;
  }
}

// invariant doesn't currently permit changing the processor
// id of an entry already in the map
template <typename ElementId, typename ProcessorId>
void range_map<ElementId,ProcessorId>::insert(ElementId eid, ProcessorId pid)
{
  key_type k(eid, eid);
  value v = pid;
  container_pib pib;
  pib.first = index_map.find(k);
  if (index_map.end() != pib.first) {
    // ensure element rank matches
    assert((*pib.first).second == pid);
    return;
  }

  // see if adjacent value already in map, check if processors match
  iterator ub = index_map.find(key_type(eid-1, eid-1));
  if (index_map.end() != ub && (*ub).second == v) {
    // this element abuts existing range upper bound, processors match
    key_type kt = (*ub).first;
    ++(kt.second);
    index_map.erase(ub);
    pib = index_map.insert(value_type(kt, v));
    assert(pib.second /* insert failed */);
  }
  else {
    iterator lb = index_map.find(key_type(eid+1, eid+1));
    if (index_map.end() != lb && (*lb).second == v) {
      // this element abuts existing range lower bound, processors match
      key_type kt = (*lb).first;
      --(kt.first);
      index_map.erase(lb);
      pib = index_map.insert(value_type(kt, v));
      assert(pib.second /* insert failed */);
    }
    else {
      // normal insert (discontiguous range)
      pib = index_map.insert(value_type(k, v));
      assert(pib.second /* insert failed */);
    }
  }
}

// all elements owned by pid
// ElemIterator dereference must be convertible to ElementId
template <typename ElementId, typename ProcessorId>
template <typename ElemIterator>
void range_map<ElementId,ProcessorId>::insert(ElemIterator it, ElemIterator end, ProcessorId pid)
{
  for (; it != end; ++it)
    insert(*it, pid);
}

} // namespace DGM

#endif

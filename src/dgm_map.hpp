#ifndef DGM_MAP_HPP
#define DGM_MAP_HPP

/** \file dgm_map.hpp
    \brief Simple implementation of a Map for platforms that do not support it

    This is likly no longer needed as the STL is now mature.  We've left it in
    just in case.
*/

namespace DGM {

/// DGM Map was developed for systems without an STL map
/** This was required on some system but is likely no longer needed. */
template<class Key, class T>
class Map {
public:
  typedef Key key_type;                                    ///< key type
  typedef T mapped_type;                                   ///< mapped type
  typedef std::pair<Key,T> value_type;                     ///< value type
  typedef std::list<value_type> list_t;                    ///< list type
  typedef typename list_t::iterator iterator;              ///< iterator
  typedef typename list_t::const_iterator const_iterator;  ///< const iterator

  //@{ \name Constructor/Destructor.

    //! Default Constructor
    Map() {}

    //! Copy Constructor
    Map( const Map<Key,T>& map_in ) : list_( map_in.list_ ) {}

    //! Destructor
    virtual ~Map() {}

  //@}

  //@{ \name Accessor methods.

    //! Return an iterator that points to the first pair in the Map.
    iterator begin() { return list_.begin(); }

    //! Return a const iterator that points to the first pair in the Map.
    const_iterator begin() const { return list_.begin(); }

    //! Return an iterator that points to the last pair in the Map.
    iterator end() { return list_.end(); }

    //! Return a const iterator that points to the last pair in the Map.
    const_iterator end() const { return list_.end(); }

    //! Return a reference to the mapped value that belongs to the key \c k.
    /*! \param k - The key for which data should be retrieved.
      If this key doesn't exist then the key is inserted into the Map and a
      reference to the mapped value is returned.
    */
    mapped_type& operator[]( const key_type& k )
    {
      iterator itr = find(k);
      if(itr != end()) return (*itr).second;
      list_.push_back( value_type( k, T() ) );
      return list_.back().second;
    }

  //@}

  //@{ \name Search methods.

    //! Locate element in the map with key_type \c k.
    /*! \param k - The key for which an iterator should be returned.
      \return An iterator that points to the element with key_type \c k, else
      return end().
    */
    iterator find(const key_type& k)
    {
      for( iterator itr = begin(); itr != end(); ++itr ) {
        if( (*itr).first == k ) {
          return itr;
        }
      }
      return end();
    }

    //! Locate element in the map with key_type \c k.
    /*! \param k - The key for which a constant iterator should be returned.
      \return A constant iterator that points to the element with key_type
        \c k, else return end().
    */
    const_iterator find(const key_type& k) const
    {
      for( const_iterator itr = begin(); itr != end(); ++itr ) {
        if( (*itr).first == k ) {
          return itr;
        }
      }
      return end();
    }

    //! indicates whether the map is empty
    bool empty() const { return list_.empty(); }

  //@}

private:
  list_t list_;   ///< the actual storage for the map
};

}  // namespace DGM

#endif

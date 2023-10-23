#ifndef DGM_NODEBLOCK_HPP
#define DGM_NODEBLOCK_HPP

/** \file NodeBlock.hpp
    \brief DGM node block and element-node block class
    \author James Overfelt
    \author Scott Collis
*/

// system includes
#include <utility>
#include <vector>

// DGM includes
#include "Types.hpp"

namespace DGM {

/// And element - node pair
template <typename ElementType, typename NodeType=Ordinal>
struct ElementNode : public std::pair<ElementType,NodeType> {
  /// Default constructors
  ElementNode() : std::pair<ElementType,NodeType>(){}

  /// Normal constructor
  ElementNode( const ElementType element, const NodeType node)
    : std::pair<ElementType,NodeType>(element,node){}

  /// Copy constructor
  ElementNode( const ElementNode& en ) : std::pair<ElementType,NodeType>(en){}

  /// Destructor
  ~ElementNode(){}

  // methods
  ElementType element() const {return this->first;}
  NodeType node() const {return this->second;}
  ElementNode &operator=( const ElementNode& en ) {
    return *this = en;
  }
};

/// Block of node points
template <typename ElementType, typename NodeType=Ordinal>
struct NodeBlock : public std::vector< ElementNode<ElementType,NodeType> > {
  /// Constructor
  NodeBlock() : std::vector< ElementNode<ElementType> >(){}

  /// Destructor
  ~NodeBlock(){}

  // methods
  void push_back( const ElementType element, const NodeType node) {
    const ElementNode<ElementType,NodeType> n(element,node);
    this->std::vector< ElementNode<ElementType,NodeType> >::push_back(n);
  }
private :
  /// Copy constructor
  NodeBlock( const NodeBlock& n );
};

} // namespace DGM

#endif  // DGM_NODEBLOCK_HPP

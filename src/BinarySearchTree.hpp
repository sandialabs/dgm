/** \file BinarySearchTree.hpp
    \brief Binary search
    \author K. Noel Belcourt
*/

#ifndef DGM_BinarySearchTree_hpp
#define DGM_BinarySearchTree_hpp

// standard libraries
#include <iostream>

// DGM libraries
#include "Point.hpp"

namespace DGM {

template <typename T>
struct node {
  T key;
  node<T> *parent, *left, *right;
  node(T& s) : key(s), parent(0), left(0), right(0) {}
  node(const node& n) : key(n.key), parent(n.parent),
    left(n.left), right(n.right) {}
};

template <typename T>
void clear(node<T>* x) {
  // remove all nodes starting here
  if (0 != x) {
    clear(x->left);
    clear(x->right);
  }
  delete x;
}

template <typename T>
void remove(node<T>* n, node<T>* root)
{
  // throw exception if node not found
}

template <typename T>
node<T>* insert_left(T& t, node<T>** root) {
  typedef node<T> node_t;
  assert(0 != root);
  node_t *x = *root;
  x->left = new node_t(t);
  return x->left;
}

template <typename T>
node<T>* insert_right(T& t, node<T>** root) {
  typedef node<T> node_t;
  assert(0 != root);
  node_t *x = *root;
  x->right = new node_t(t);
  return x->right;
}

template <typename T>
node<T>* insert(T& t, node<T>** root)
{
  typedef node<T> node_t;
  node_t *z = new node_t(t);
  node_t *y = 0;
  node_t *x = *root;
  while (0 != x) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (0 == y)
    *root = z;  // tree was empty
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  return z;
}

// requires parent so not general
template <typename T>
node<T>* successor(const node<T>* x)
{
  typedef node<T>* node_t;
  if (x->right)
    return tree_minimum(x->right);
  node_t y = x->parent;
  while (0 != y && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

// requires parent, not general
template <typename T>
node<T>* predecessor(const node<T>* x)
{
  typedef node<T> node_t;
  if (x->left)
    return tree_maximum(x->left);
  node_t y = x->left;
  while (0 != y && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename T>
void inorder_tree_walk(const node<T>* x) {
  using std::cout;
  using std::endl;
  if (0 != x) {
    inorder_tree_walk(x->left);
    cout << x->key << endl;
    inorder_tree_walk(x->right);
  }
}

template <typename T>
node<T>* tree_search(const T& k, node<T>* x) {
  while (0 != x && k != x->key) {
    if (k < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}

template <typename Scalar, typename Space, typename T>
node<T>* tree_search(const DGM::point<Scalar,Space>& p, node<T>* x) {
  node<T>* y = 0;
  while (0 != x && p != x->key) {
    y = x;
    if (p < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return y;
}

template <typename T>
node<T>* tree_minimum(node<T>* x) {
  while (x->left) x = x->left;
  return x;
}

template <typename T>
node<T>* tree_maximum(node<T>* x) {
  while (x->right) x = x->right;
  return x;
}

}  // namespace DGM

#endif

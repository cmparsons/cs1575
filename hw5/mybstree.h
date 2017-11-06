/*
 * @author: Christian Parsons
 *
 * @section: B
 *
 * @due: November 8, 2017
 *
 * @description: Implementation of templated binary search tree ADT.
 *
 * @file: mybstree.h
 *
 * @C - Galaxy Express Software
 *
 * Version 17.3.0
 */

#ifndef MYBSTREE_H
#define MYBSTREE_H

#include "abstractbstree.h"

template <class T>
class TreeNode
{
public:
  T m_data;
  TreeNode *m_right;
  TreeNode *m_left;

  TreeNode(const T &value, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL)
      : m_data(value), m_left(left), m_right(right) {}
};

template <class T>
class MyBSTree : public AbstractBSTree<T>
{
private:
  TreeNode<T> *m_root;
  int m_size;

  // Recursive helper to clear BST.
  void clear_helper(TreeNode<T> *node);

  // Recursive helper to print BST structure using backwards in-order traversal.
  void print_helper(TreeNode<T> *node, string indent) const;

  // Recursive helper to find minimum value in BST.
  TreeNode<T> *get_min_helper(TreeNode<T> *node) const;

  // Recursive helper to find maximum value in BST.
  const T &get_max_helper(TreeNode<T> *node) const;

  // Recurisve helper to print BST using a pre-order traversal.
  void print_preorder_helper(TreeNode<T> *node) const;

  // Recursive helper to print BST using a post-order traversal.
  void print_postorder_helper(TreeNode<T> *node) const;

  // Recursive helper to insert a value into the BST if it DNE already.
  void insert_helper(TreeNode<T> *&node, const T &value);

  // Recursive helepr to remove a value from the BST, if it exists.
  // Return the new subtree.
  TreeNode<T> *remove_helper(TreeNode<T> *root, const T &value);

  // Recursive helper to find the height of the BST.
  int height_helper(TreeNode<T> *node) const;

  // Recursive helper to find a value in the BST.
  // Returns level of value N or -N if value DNE in BST.
  int find_helper(TreeNode<T> *node, const T &value, int level) const;

  // Recursive helper to copy a tree.
  TreeNode<T> *clone(const TreeNode<T> *t);

public:
  MyBSTree() : m_size(0), m_root(NULL) {}

  MyBSTree(const MyBSTree<T> &rhs);

  const MyBSTree<T> &operator=(const MyBSTree<T> &rhs);

  ~MyBSTree() { clear(); }

  int size() const { return m_size; }

  bool isEmpty() const { return m_size == 0 && m_root == NULL; }

  int height() const { return height_helper(m_root); }

  const T &getMax() const throw(Oops);

  const T &getMin() const throw(Oops);

  int find(const T &value) const { return find_helper(m_root, value, 1); }

  void clear();

  void insert(const T &value);

  void remove(const T &value);

  void print() const { print_helper(m_root, ""); }

  void printPreOrder() const { print_preorder_helper(m_root); }

  void printPostOrder() const { print_postorder_helper(m_root); }
};

#include "mybstree.hpp"
#endif

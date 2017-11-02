/*
 * @author: Christian Parsons
 *
 * @section: B
 *
 * @due: November 8, 2017
 *
 * @description: Definition of templated binary search tree class.
 *
 * @file: mybstree.h
 *
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
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

  TreeNode(const T &value) : m_data(value), m_right(NULL), m_left(NULL) {}
};

template <class T>
class MyBSTree : public AbstractBSTree<T>
{
private:
  TreeNode<T> *m_root;
  int m_size;

  void clear_helper(TreeNode<T> *node);

  void print_helper(TreeNode<T> *node, string indent) const;

  const T &get_min_helper(TreeNode<T> *node) const;

  const T &get_max_helper(TreeNode<T> *node) const;

  void print_preorder_helper(TreeNode<T> *node) const;

  void print_postorder_helper(TreeNode<T> *node) const;

  void insert_helper(TreeNode<T> * &node, const T &value);

public:
  MyBSTree(): m_size(0), m_root(NULL) {}

  ~MyBSTree() { clear(); }

  int size() const { return m_size; }

  bool isEmpty() const { return m_size == 0 && m_root == NULL; }

  const T &getMax() const throw(Oops);

  const T &getMin() const throw(Oops);

  void clear();

  void insert(const T &value);

  void print() const { print_helper(m_root, ""); }

  void printPreOrder() const { print_preorder_helper(m_root); }

  void printPostOrder() const { print_postorder_helper(m_root); }
};

#include "mybstree.hpp"
#endif

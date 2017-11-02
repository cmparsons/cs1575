/*
 * @author: Christian Parsons
 *
 * @section: B
 *
 * @due: November 8, 2017
 *
 * @description: Implementation of tempated binary search tree class.
 *
 * @file: mybstree.hpp
 *
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

#ifndef MYBSTREE_HPP
#define MYBSTREE_HPP

#include <iostream>
using namespace std;

const string SPACES = "    ";
const string EMPTY_ERR = "OOPS ! : Tree is Empty !!";

template <class T>
const T &MyBSTree<T>::get_min_helper(TreeNode<T> *node) const
{
  if (node->m_left == NULL)
    return node->m_data;

  return get_min_helper(node->m_left);
}

template <class T>
const T &MyBSTree<T>::get_max_helper(TreeNode<T> *node) const
{
  if (node->m_right == NULL)
    return node->m_data;

  return get_max_helper(node->m_right);
}

template <class T>
void MyBSTree<T>::insert_helper(TreeNode<T> *&node, const T &value)
{
  if (node == NULL)
  {
    node = new TreeNode<T>(value);
    return;
  }

  if (value == node->m_data)
    return;

  if (value < node->m_data)
    insert_helper(node->m_left, value);
  else if (value > node->m_data)
    insert_helper(node->m_right, value);

  return;
}

template <class T>
void MyBSTree<T>::clear_helper(TreeNode<T> *node)
{
  if (node != NULL)
  {
    clear_helper(node->m_left);
    clear_helper(node->m_right);
    delete node;
  }

  return;
}

template <class T>
void MyBSTree<T>::print_helper(TreeNode<T> *node, string indent) const
{
  if (node == NULL)
  {
    cout << endl;
    return;
  }

  print_helper(node->m_right, indent + SPACES);
  cout << indent << node->m_data << endl;
  print_helper(node->m_left, indent + SPACES);

  return;
}

template <class T>
void MyBSTree<T>::print_preorder_helper(TreeNode<T> *node) const
{
  if (node != NULL)
  {
    cout << node->m_data << " ";
    print_preorder_helper(node->m_left);
    print_preorder_helper(node->m_right);
  }

  return;
}

template <class T>
void MyBSTree<T>::print_postorder_helper(TreeNode<T> *node) const
{
  if (node != NULL)
  {
    print_postorder_helper(node->m_left);
    print_postorder_helper(node->m_right);
    cout << node->m_data << " ";
  }

  return;
}

template <class T>
const T &MyBSTree<T>::getMax() const throw(Oops)
{
  if (isEmpty())
    throw Oops(EMPTY_ERR);

  return get_max_helper(m_root);
}

template <class T>
const T &MyBSTree<T>::getMin() const throw(Oops)
{
  if (isEmpty())
    throw Oops(EMPTY_ERR);

  return get_min_helper(m_root);
}

template <class T>
void MyBSTree<T>::clear()
{
  clear_helper(m_root);
  m_size = 0;
  m_root = NULL;

  return;
}

template <class T>
void MyBSTree<T>::insert(const T &value)
{
  insert_helper(m_root, value);
  m_size++;

  return;
}

#endif

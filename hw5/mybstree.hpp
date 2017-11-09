/*
 * @author: Christian Parsons
 *
 * @section: B
 *
 * @due: November 8, 2017
 *
 * @description: Member functions of templated binary search tree.
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
const MyBSTree<T> &MyBSTree<T>::operator=(const MyBSTree<T> &rhs)
{
  if (this != &rhs)
  {
    clear();
    m_size = rhs.m_size;
    m_root = clone(rhs.m_root);
  }

  return *this;
}

template <class T>
MyBSTree<T>::MyBSTree(const MyBSTree<T> &rhs)
{
  m_size = rhs.m_size;
  m_root = clone(rhs.m_root);
}

template <class T>
TreeNode<T> *MyBSTree<T>::clone(const TreeNode<T> *t)
{
  if (t == NULL)
    return NULL;

  return new TreeNode<T>(t->m_data, clone(t->m_left), clone(t->m_right));
}

template <class T>
int MyBSTree<T>::find_helper(TreeNode<T> *node, const T &value, int level) const
{
  if (node == NULL) // Did not find value
    return (-1 * level);
  else if (value > node->m_data)
    return find_helper(node->m_right, value, level + 1);
  else if (value < node->m_data)
    return find_helper(node->m_left, value, level + 1);

  return level; // Found value
}

template <class T>
int MyBSTree<T>::height_helper(TreeNode<T> *node) const
{
  if (node == NULL)
    return 0;

  int left_height = height_helper(node->m_left);
  int right_height = height_helper(node->m_right);

  return (left_height > right_height ? left_height + 1 : right_height + 1);
}

template <class T>
TreeNode<T> *MyBSTree<T>::get_min_helper(TreeNode<T> *node) const
{
  if (node->m_left == NULL)
    return node;

  return get_min_helper(node->m_left);
}

template <class T>
TreeNode<T> *MyBSTree<T>::get_max_helper(TreeNode<T> *node) const
{
  if (node->m_right == NULL)
    return node;

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
TreeNode<T>* MyBSTree<T>::remove_helper(TreeNode<T> *root, const T &value)
{
  if (root == NULL)
    return root;

  if (value < root->m_data)
    root->m_left = remove_helper(root->m_left, value);

  else if (value > root->m_data)
    root->m_right = remove_helper(root->m_right, value);

  else // Found value
  {
    if (root->m_left == NULL) // Only right child or no children
    {
      TreeNode<T> *temp = root->m_right;
      delete root;
      return temp;
    }
    else if (root->m_right == NULL) // Only left child
    {
      TreeNode<T> *temp = root->m_left;
      delete root;
      return temp;
    }
    else // Both children
    {
      // Swap nodes with minimum in right subtree
      TreeNode<T> *temp = get_min_helper(root->m_right);
      root->m_data = temp->m_data;
      root->m_right = remove_helper(root->m_right, temp->m_data);
    }
  }

  return root;
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

  // Backwards In-Order Traversal
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

  TreeNode<T> *max = get_max_helper(m_root);
  return max->m_data;
}

template <class T>
const T &MyBSTree<T>::getMin() const throw(Oops)
{
  if (isEmpty())
    throw Oops(EMPTY_ERR);

  TreeNode<T> *min = get_min_helper(m_root);
  return min->m_data;
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

template <class T>
void MyBSTree<T>::remove(const T &value)
{
  m_root = remove_helper(m_root, value);
  m_size--;
  return;
}

#endif

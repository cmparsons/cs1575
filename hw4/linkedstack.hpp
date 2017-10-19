/*
 * @author: Christian Parsons
 * @section: B
 * @due: October 23, 2017
 * @description: Functions for templated linked stack.
 * @file: linkedstack.hpp
 * Implementing A.D.T. Stack
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

// Mark: Constructor
template <class T>
LinkedStack<T>::LinkedStack()
{
  m_head = NULL;
  m_size = 0;
}

// MARK: Big 3 Member Functions
template <class T>
LinkedStack<T>::~LinkedStack()
{
  clear();
}

template <class T>
const LinkedStack<T>& LinkedStack<T>::operator= (const LinkedStack<T>& rhs)
{
  // check for self-assignment
  if (this == &rhs)
    return *this;

  clear();
  m_size = rhs.m_size;
  m_head = new Node<T>();
  Node<T> *temp = rhs.m_head; // track location in rhs
  Node<T> *temp2 = m_head; // track location in this

  // Deep copy stack
  while (temp != NULL)
  {
    temp2->m_data = temp->m_data;
    temp = temp->m_next;
    if (temp != NULL)
    {
      temp2->m_next = new Node<T>();
      temp2 = temp2->m_next;
    }
  }

  return *this;
}

template <class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& rhs)
{
  m_size = rhs.m_size;
  m_head = new Node<T>();
  Node<T> *temp = rhs.m_head; // track location in rhs
  Node<T> *temp2 = m_head; // track location in this

  // Deep copy stack
  while (temp != NULL)
  {
    temp2->m_data = temp->m_data;
    temp = temp->m_next;
    if (temp != NULL)
    {
      temp2->m_next = new Node<T>();
      temp2 = temp2->m_next;
    }
  }
}

// MARK: Basic Accessor Operations
template <class T>
bool LinkedStack<T>::isEmpty() const
{
  return m_size == 0;
}

template <class T>
const T& LinkedStack<T>::top() const throw ( Oops )
{
  if (isEmpty())
     throw Oops("Stack is empty!");

   return m_head->m_data;
}

 // MARK: Basic Mutator Operations
template <class T>
void LinkedStack<T>::push(const T& x)
{
  m_head = new Node<T>(x, m_head);
  m_size++;

  return;
}

template <class T>
void LinkedStack<T>::pop()
{
  if (isEmpty())
    return;

  Node<T> *temp = m_head;
  m_head = m_head->m_next;
  delete temp;
  m_size--;

  return;
}

template <class T>
void LinkedStack<T>::clear()
{
  Node<T> *temp = m_head;
  while (m_head != NULL)
  {
    temp = m_head;
    m_head = m_head->m_next;
    delete temp;
  }
  m_size = 0;

  return;
}

#endif

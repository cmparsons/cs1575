/* @file: arraylist.hpp
 * Implementation of templated class ArrayList
 * Implementation of the List ADT
 * @C - Galaxy Express Softworks
 *
 * Version 17.3.0
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

using namespace std;

// MARK : Constructors/Destructors
template <class T>
ArrayList<T>::~ArrayList()
{
  clear();
}

template <class T>
ArrayList<T>::ArrayList(int s, const T& x)
{
  m_size = m_max = s;
  m_data = new T[m_size];

  for (int i = 0; i < m_size; i++)
    m_data[i] = x;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  // check for self-assignment
  if (this == &rhs)
    return *this;

  delete[] m_data;

  // shallow copy non-pointers
  m_size = rhs.m_size;
  m_max = rhs.m_max;
  m_errobj = rhs.m_errobj;

  // deep copy pointer if non-null
  if (rhs.m_data)
  {
    m_data = new T[m_size];

    for (int i = 0; i < m_size; i++)
      m_data[i] = rhs.m_data[i];
  }
  else
    m_data = 0;

  return *this;
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy)
{
  // shallow copy for non-pointers
  m_size = cpy.m_size;
  m_max = cpy.m_max;
  m_errobj = cpy.m_errobj;

  // deep copy for pointer if non-null
  if (cpy.m_data)
  {
    m_data = new T[m_size];

    for (int i = 0; i < m_size; i++)
      m_data[i] = cpy.m_data[i];
  }
  else
    m_data = 0;
}

// MARK: Basic Accessor Operations
template <class T>
int ArrayList<T>::size() const
{
  return m_size;
}

template <class T>
const T& ArrayList<T>::first() const
{
  if (m_size == 0)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST.first()!!  (List is empty)" << endl;
    return m_errobj;
  }

  return m_data[0];
}

template <class T>
const T& ArrayList<T>::operator[](int i) const
{
  if (i < 0 || i > m_size || i > m_max)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST!!.[]  (index out of bounds)"
         << endl;
    return m_errobj;
  }

  return m_data[i];
}

template <class T>
int ArrayList<T>::find(const T& x) const
{
  for (int i = 0; i < m_size; i++)
    if (m_data[i] == x)
      return i;

  return -1;
}

// MARK: Basic Mutator Operations
template <class T>
void ArrayList<T>::clear()
{
  m_size = m_max = 0;
  delete[] m_data;
  m_data = NULL;
}

#endif

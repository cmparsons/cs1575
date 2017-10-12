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
  m_size = m_max = 0;
  delete[] m_data;
  m_data = NULL;
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
  m_size = cpy.m_size;
  m_max = cpy.m_max;
  m_errobj = cpy.m_errobj;


  if (cpy.m_data)
  {
    m_data = new T[m_size];

    for (int i = 0; i < m_size; i++)
      m_data[i] = cpy.m_data[i];
  }
  else
    m_data = 0;
}

#endif

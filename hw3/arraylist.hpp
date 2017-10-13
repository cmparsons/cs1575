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

// MARK: Auxiliary Functions
template <class T>
void ArrayList<T>::grow()
{
  m_max *= 2;
  T *new_list = new T[m_max];

  for (int i = 0; i < m_size; i++)
    new_list[i] = m_data[i];

  delete[] m_data;
  m_data = new_list;
}

template <class T>
void ArrayList<T>::shrink()
{
  m_max /= 2;
  T *new_list = new T[m_max];

  for (int i = 0; i < m_size; i++)
    new_list[i] = m_data[i];

  delete[] m_data;
  m_data = new_list;
}

// MARK: Constructors/Destructors
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
T& ArrayList<T>::operator[](int i)
{
  if (i < 0 || i >= m_size)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST!!.[]  (index out of bounds)"
         << endl;
    return m_errobj;
  }

  return m_data[i];
}

template <class T>
const T& ArrayList<T>::operator[](int i) const
{
  if (i < 0 || i >= m_size)
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

template <class T>
void ArrayList<T>::insert_back(const T& x)
{
  // Special case if list is not allocated
  if (m_size == 0 && m_max == 0)
    m_data = new T[++m_max];

  m_data[m_size++] = x;

  if (m_size == m_max)
    grow();

  return;
}

template <class T>
void ArrayList<T>::insert(const T& x, int i)
{
  if (i < 0 || i >= m_size)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST!!.insert()  (index out of bounds)"
         << endl;
    return;
  }

  // Check before shifting to prevent accessing unallocated memory
  if (++m_size == m_max)
    grow();

  // Shift elements right of i
  for (int j = m_size - 2; j >= i; j--)
    m_data[j + 1] = m_data[j];

  m_data[i] = x;

  return;
}

template <class T>
void ArrayList<T>::remove(int i)
{
  if (m_size == 0)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST.remove()!!  (List is empty)"
         << endl;
    return;
  }
  if (i < 0 || i >= m_size)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST!!.remove()  (index out of bounds)"
         << endl;
    return;
  }

  // Don't shift elements if removing from the end
  if (i < m_size - 1)
  {
    // Shift elements left of i
    for (int j = i; j < m_size; j++)
      m_data[j] = m_data[j + 1];
  }
  m_size--;

  if (m_size < 0.25 * m_max)
    shrink();

  return;
}

// MARK: Complex Mutator Operations
template <class T>
void ArrayList<T>::swap(int i, int k)
{
  if (i < 0 || k < 0 || i >= m_size || k >= m_size)
  {
    cout << "!-- ERROR : PANIC in ARRAYLIST!!.swap()  (index out of bounds)"
         << endl;
    return;
  }

  T temp = m_data[i];
  m_data[i] = m_data[k];
  m_data[k] = temp;

  return;
}

template <class T>
void ArrayList<T>::append(const ArrayList<T>& alist)
{
  int new_length = m_size + alist.size();
  T *new_list = new T[new_length];

  for (int i = 0; i < m_size; i++)
    new_list[i] = m_data[i];

  for (int j = m_size; j < new_length; j++)
    new_list[j] = alist[j - m_size];

  m_max = m_size = new_length;
  delete[] m_data;
  m_data = new_list;

  return;
}

template <class T>
void ArrayList<T>::purge()
{
  T val;
  for (int i = 0; i < m_size; i++)
  {
    val = m_data[i];
    for (int j = i; j < m_size; j++)
      if (m_data[j] == val)
        remove(j);
  }

  return;
}

#endif

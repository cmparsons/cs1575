/*
 * @author: Christian Parsons
 *
 * @section: B
 *
 * @due: November 17, 2017
 *
 * @description: Member functions for implementation of string map.
 *
 * @file: mystringmap.hpp
 *
 */

#ifndef MYSTRINGMAP_HPP
#define MYSTRINGMAP_HPP

#include <string>

template <class T>
MyStringMap<T>::MyStringMap()
{
  EMPTY = "-1";
  TOMB = "-2";
  m_size = 0;
  m_max = 8;
  m_hash_table = new KVPair<T>[m_max];
  for (int i = 0; i < m_max; i++)
    m_hash_table[i].set_key(EMPTY);
}

template <class T>
void MyStringMap<T>::grow()
{
  int old_max = m_max;
  m_max = (m_max << 1) + 1;
  KVPair<T> *new_hash_table = new KVPair<T>[m_max]();
  string key;
  int home, pos, j;

  for (int i = 0; i < m_max; i++)
    new_hash_table[i].set_key(EMPTY);

  for (int i = 0; i < old_max; i++)
  {
    key = m_hash_table[i].key();

    // Rehash records in new hash table
    if (key != EMPTY && key != TOMB)
    {
      pos = home = hash(key);
      j = 1;
      while (new_hash_table[pos].key() != EMPTY)
      {
        pos = (home + double_hash(key, j)) % m_max;
        j++;
      }
      KVPair<T> new_record(key, m_hash_table[i].value());
      new_hash_table[pos] = new_record;
    }
  }

  delete[] m_hash_table;
  m_hash_table = new_hash_table;
  return;
}

template <class T>
void MyStringMap<T>::clear()
{
  delete[] m_hash_table;
  m_hash_table = NULL;
  m_size = 0;
  return;
}

template <class T>
int MyStringMap<T>::hash(const string &key) const
{
  unsigned int hash = 0;
  for (int i = 0; i < key.length(); i++)
    hash = 31 * hash + key[i];

  return hash % m_max;
}

template <class T>
void MyStringMap<T>::insert(const string &key, const T &val)
{
  int home;
  int pos = home = hash(key);
  int i = 1;

  // If key already exists, override the value
  if (m_hash_table[pos].key() == key)
  {
    m_hash_table[pos].set_value(val);
    return;
  }

  while (
      m_hash_table[pos].key() != EMPTY &&
      m_hash_table[pos].key() != TOMB &&
      m_hash_table[pos].key() != key)
  {
    pos = (home + double_hash(key, i)) % m_max;
    i++;
  }
  KVPair<T> new_record(key, val);
  m_hash_table[pos] = new_record;

  // Increase size of hash table if size reaches past load factor 3/4 max
  if (++m_size >= 0.75 * m_max)
    grow();

  return;
}

template <class T>
void MyStringMap<T>::print() const
{
  string key;
  for (int i = 0; i < m_max; i++)
  {
    key = m_hash_table[i].key();
    if (key != EMPTY && key != TOMB)
      cout << "< " << key << ", " << m_hash_table[i].value() << " >" << endl;
  }
  return;
}

#endif

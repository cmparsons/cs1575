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

const string KEY_NOT_FOUND = "Key Not Found !!";

template <class T>
MyStringMap<T>::MyStringMap()
{
  EMPTY = "-1";
  TOMB = "-2";
  m_size = m_num_tomb = 0;
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
  KVPair<T> *new_hash_table = rehash(m_hash_table, old_max);

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
  long hash = 0;
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

template <class T>
int MyStringMap<T>::search(const string &key) const
{
  int home;
  int pos = home = hash(key);
  int i = 1;

  while (m_hash_table[pos].key() != EMPTY && m_hash_table[pos].key() != key)
  {
    pos = (home + double_hash(key, i)) % m_max;
    i++;
  }

  return (m_hash_table[pos].key() == EMPTY ? -1 : pos);
}

template <class T>
const T &MyStringMap<T>::valueOf(const string &key) const throw(Oops)
{
  int pos = search(key);

  if (pos == -1)
    throw Oops(KEY_NOT_FOUND);

  return m_hash_table[pos].value();
}

template <class T>
void MyStringMap<T>::remove(const string &key)
{
  int pos = search(key);

  if (pos != -1)
  {
    m_hash_table[pos].set_key(TOMB);
    m_size--;
    m_num_tomb++;
  }

  // Clean up tombstones if too many accumulate
  if (m_num_tomb >= 0.25 * m_max)
    cleanup();

  return;
}

template <class T>
void MyStringMap<T>::cleanup()
{
  for (int i = 0; i < m_max; i++)
    if (m_hash_table[i].key() == TOMB)
      m_hash_table[i].set_key(EMPTY);

  KVPair<T> *new_hash_table = rehash(m_hash_table, m_max);
  delete[] m_hash_table;
  m_hash_table = new_hash_table;
  m_num_tomb = 0;
  return;
}

template <class T>
KVPair<T> *MyStringMap<T>::rehash(const KVPair<T> *ht, const int size)
{
  int home, pos, j;
  KVPair<T> *new_ht = new KVPair<T>[m_max]();
  string key;

  for (int i = 0; i < m_max; i++)
    new_ht[i].set_key(EMPTY);

  for (int i = 0; i < size; i++)
  {
    key = ht[i].key();

    if (key != EMPTY)
    {
      pos = home = hash(key);
      j = 1;
      while (new_ht[pos].key() != EMPTY)
      {
        pos = (home + double_hash(key, j)) % m_max;
        j++;
      }
      KVPair<T> new_record(key, ht[i].value());
      new_ht[pos] = new_record;
    }
  }
  return new_ht;
}

#endif

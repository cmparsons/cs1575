/*
* @author: Christian Parsons
*
* @section: B
*
* @due: November 17, 2017
*
* @description: Implementation of an templated string map ADT.
*
* @file: mystringmap.h
*
*/

#ifndef MYSTRINGMAP_H
#define MYSTRINGMAP_H

#include "abstractstringmap.h"

template <class T>
class KVPair
{
private:
  string m_key;
  T m_val;

public:
  KVPair() {}

  KVPair(const string key, const T val) : m_key(key), m_val(val) {}

  KVPair(const KVPair<T> &rhs)
  {
    m_key = rhs.m_key;
    m_val = rhs.m_val;
  }

  void operator=(const KVPair<T> &rhs)
  {
    m_key = rhs.m_key;
    m_val = rhs.m_val;
  }

  string key() const { return m_key; }

  const T &value() const { return m_val; }

  void set_key(const string &key) { m_key = key; }

  void set_value(const T &value) { m_val = value; }

  // Search for key inside hash table.
  // Returns position of key, if found. Otherwise, returns -1
  int search(const string &key) const;
};

template <class T>
class MyStringMap : public AbstractStringMap<T>
{
private:
  int m_size;
  int m_max;
  KVPair<T> *m_hash_table;

  string EMPTY;
  string TOMB;

  int m_num_tomb; // track number of tombstones--used for cleanup

  int hash(const string &key) const;

  int double_hash(const string &key, const int i) const
  {
    return i * hash(key);
  }

  // Increase the size of the hash table and rehash records.
  void grow();

  // Remove all tombstones within hash table. Set TOMB to EMPTY
  void cleanup();

  // Find position of key in the hash table. Returns -1 if key is not found.
  int search(const string &key) const;

public:
  MyStringMap();

  ~MyStringMap() { clear(); }

  void clear();

  int size() const { return m_size; }

  int max() const { return m_max; }

  bool isEmpty() const { return m_size == 0; }

  void insert(const string &key, const T &val);

  const T &valueOf(const string &key) const throw(Oops);

  void remove(const string &key);

  void print() const;
};

#include "mystringmap.hpp"
#endif

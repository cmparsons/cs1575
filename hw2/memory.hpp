/*
* @author: Christian Parsons
* @file: memory.hpp
* @description: File contains template functions to manage memory for dynamic
*               2D arrays.
*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

// Description: Allocates memory for a 2D array
// pre:         rows > 0
//              cols > 0
// post:        A rows-by-cols 2D array with memory allocated is returned
template <class T>
T **allocate_dynamic_2d_array(const int rows, const int cols)
{
  T **array = new T *[rows];

  for (int i = 0; i < rows; i++)
    array[i] = new T[cols];

  return array;
}

// Description: Deallocates memory for a 2D array
// pre:         2D array has row count of rows in memory
// post:        Memory is deallocated for 2D array
template <class T>
void deallocate_2d_array(T **array, const int rows)
{
  for (int i = 0; i < rows; i++)
    delete[] array[i];

  delete[] array;
  array = NULL;

  return;
}

#endif

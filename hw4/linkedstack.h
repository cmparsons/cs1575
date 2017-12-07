/* @file: linkedstack.h
 * Definition of templated linked stack
 * Implementing A.D.T. Stack
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

/* ____________________
  /                    \
  | LinkedStack Class  |
  \____________________/

    Purpose: Implements a Stack ADT.

    Error Handling: Whenever a function is given invalid parameter values
        the function should THROW an 'Oops' object.

*/
#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <string>

using namespace std;

/* ---------------  Class 'Oops' ---------------
Class "thrown" when an error is encountered.
Member 'm_msg' stores an error message.
*/
class Oops
{
	string m_errormsg;
public:
	Oops(const string &msg) : m_errormsg(msg) {}
	const string& getMsg() const
	{
		return m_errormsg;
	}
};


/* --------------- Class Node ---------------
   A Node storing one element of the Linked Stack
*/
template <class T>
class Node
{
public:
  T m_data;            // Data to be stored
  Node<T>* m_next;     // Pointer to the next element in the list


  // Purpose: Default constructor
  // Postconditions: next pointer set to NULL
  // ---INLINE---
  Node() : m_next(NULL) {}

  // Purpose: Auxiliaty constructor, construct from parameters
  // Postconditions: data and next pointer set to parameters
  // ---INLINE---
  Node(const T& x, Node<T>* p)
             : m_data(x), m_next(p) {}
};


// --------------- Class LinkedStack ---------------
template <class T>
class LinkedStack
{

  Node<T>* m_head;     // Pointer to the top of the stack
  int m_size;          // The number of elements in the stack

public:
  // Purpose: Default constructor
  // Postconditions: this stack represents the empty Stack
  LinkedStack();


  // -------------
  // --------- Big 3 Member Functions ---
  // -------------

  // Purpose: Destructor
  ~LinkedStack();

  // Purpose: performs a deep copy of the data from rhs into this linked stack
  // Parameters: rhs is linked stack to be copied
  // Returns: *this
  // Postconditions: this stack contains same data values (in the same order)
  //     as are in rhs; any memory previously used by this stack has been
  //     deallocated.
  const LinkedStack<T>&  operator= (const LinkedStack<T>& rhs);

  // Purpose: copy constructor
  // Parameters: rhs is the LinkedStack that is to be copied
  // Postconditions: this stack contains same data values (in same order)
  //      as in rhs.
  LinkedStack(const LinkedStack<T>& rhs);


  // -------------
  // --------- Basic Accessor Operations ---
  // -------------

  // Purpose: Checks if a stack is empty
  // Returns: 'true' if the stack is empty
  //     'false' otherwise
  bool isEmpty() const;

  // Purpose: looks at the top of the stack
  // Returns: a const reference to the element currently on top of the stack
  // Exception: if the stack is empty, THROW a 'Oops' object with an error message!!!
  const T& top() const throw ( Oops );


  // -------------
  // --------- Basic Mutator Operations ---
  // -------------

  // Purpose: push an element into the stack
  // Parameters: x is the value to push into the stack
  // Postconditions: x is now the element at the top of the stack,
  void push(const T& x);

  // Purpose: pop the stack
  // Postconditions: the element formerly at the top of the stack has
  // been removed
  // Note: Poping an empty stack results in an empty stack.
  void pop();


  // Purpose: clears the stack
  // Postconditions: the stack is now empty
  void clear();

};

#include "linkedstack.hpp"
#endif

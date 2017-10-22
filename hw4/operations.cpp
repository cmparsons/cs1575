/*
 * @author: Christian Parsons
 * @section: B
 * @due: October 23, 2017
 * @description: Functions to parse and calculate expressions.
 * @file: operations.cpp
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

#include "operations.h"
#include "constants.h"
#include "linkedstack.h"

bool is_open_parenthesis(const string &s)
{
  return s == "(" || s == "[" || s == "{";
}

bool is_operator(const string &s)
{
  return s == ADD || s == SUB || s == MUL || s == DIV || s == MOD;
}

bool is_close_parenthesis(const string &s)
{
  return s == ")" || s == "]" || s == "}";
}

bool valid_parenthesis(const string &p1, const string &p2)
{
  if (p1 == "(")
    return p2 == ")";
  else if (p1 == "[")
    return p2 == "]";
  else
    return p2 == "}";
}

int perform_operation(const int operand1, const int operand2, const string op)
{
  if (op == ADD)
    return operand1 + operand2;
  else if (op == SUB)
    return operand1 - operand2;
  else if (op == MUL)
    return operand1 * operand2;
  else
  {
    if (operand2 == 0)
      throw Oops("Division/Mod by 0!");

    if (op == DIV)
      return operand1 / operand2;
    else
      return operand1 % operand2;
  }
}

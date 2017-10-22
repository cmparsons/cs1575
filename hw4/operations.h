/*
 * @author: Christian Parsons
 * @section: B
 * @due: October 23, 2017
 * @description: Functions to parse and calculate expressions.
 * @file: operations.h
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
using namespace std;

// Description: Check if parenthesis represent a matching set.
// params: p1 is an opening parenthesis
//         p2 is a closing parenthesis
// returns: true, if p1 and p2 are matching set
//          false, otherwise
bool valid_parenthesis(const string &p1, const string &p2);

// Description: Check if s is a closing parenthesis
// param: s: any string value
// returns: true, if s = ), ], or }
//          false, otherwise
bool is_close_parenthesis(const string &s);

// Description: Checks if s is an opening parenthesis
// param: s: any string value
// returns: true, if s = (, [, or {
//          false, otherwise
bool is_open_parenthesis(const string &s);

// Description: Check if s is a binary arithmetic operator
// param: s: any string value
// returns: true, if s = +, -, *, /, or %
//          false, otherwise
bool is_operator(const string &s);

// Description: Perform operator on passed operands with passed operator
// param: operand1, operand2: operands of operation
//        op: operator
// returns: return result of operation if Oops is not thrown
//          throws Oops if operand2 is 0 and op is / or % (Division/Mod by 0)
int perform_operation(const int operand1, const int operand2, const string op);

#endif

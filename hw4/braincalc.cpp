/*
 * @author: Christian Parsons
 * @section: B
 * @due: October 23, 2017
 * @description: Main function that performs order of operators using linked
 *               stack.
 * @file: braincalc.cpp
 * @C - Galaxy Express Software
 *
 * Version 17.3.1
 */

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "constants.h"
#include "operations.h"
#include "linkedstack.h"
using namespace std;

int main()
{
  LinkedStack<string> parenthesis;
  LinkedStack<string> operators;
  LinkedStack<int> operands;

  int operand1, operand2, result;
  int count = 1; // Count iterations for ouput
  string op;     // operator
  bool valid_exp = true;

  string expression, input;
  stringstream ss;
  getline(cin, expression);

  while (expression != END)
  {
    valid_exp = true;

    // Clear the current string stream
    ss.clear();
    ss.str("");
    ss << expression; // Load the string stream with the expression

    while (ss >> input && valid_exp)
    {
      if (is_close_parenthesis(input))
      {
        // Check if the parenthesis are matching pair
        valid_exp = valid_parenthesis(parenthesis.top(), input);

        // Perform the calculation if there's have a matching pair of parenthesis
        if (valid_exp)
        {
          try
          {
            parenthesis.pop();

            operand2 = operands.top();
            operands.pop();

            operand1 = operands.top();
            operands.pop();

            op = operators.top();
            operators.pop();
          }
          catch (const Oops &e)
          {
            // Catch attempt to read from an empty stack
            cerr << "ERROR: " << e.getMsg() << endl;
            valid_exp = false;
          }

          try
          {
            result = perform_operation(operand1, operand2, op);
            operands.push(result);
          }
          catch (const Oops &e)
          {
            // Catch division/mod by 0
            cerr << "ERROR: " << e.getMsg() << endl;
            valid_exp = false;
          }
        }
      }
      else if (is_open_parenthesis(input))
        parenthesis.push(input);

      else if (is_operator(input))
        operators.push(input);
      else
      {
        operand1 = atoi(input.c_str());
        operands.push(operand1);
      }
    }

    // Print results
    if (valid_exp && parenthesis.isEmpty() && operators.isEmpty())
      cout << "#" << count << " : " << result << endl;
    else
      cout << "#" << count << " : "
           << "INVALID!" << endl;

    // Reinitialize for next expression
    parenthesis.clear();
    operands.clear();
    operators.clear();

    getline(cin, expression);
    count++;
  }

  return 0;
}

/*
* @author: Christian Parsons
* @file: hivemind.cpp
* @section: B
* @due: September 8, 2017
* @description:
*
*/

#include <iostream>
using namespace std;

int main ()
{
  int num_test_cases = 0;
  int num_rows = 0;
  int num_columns = 0;
  int **grid = NULL;

  cout << "getting number of test cases...\n";
  cin >> num_test_cases;
  cout << "\ttest cases: " << num_test_cases << "\n";

  for (int i = 0; i < num_test_cases; i++)
  {
    cout << "getting number of rows and columns...\n";
    cin >> num_rows >> num_columns;

    cout << "\trows:\t" << num_rows << endl;
    cout << "\tcols:\t" << num_columns << endl;

    // Allocate memory for grid
    cout << "allocating rows of grid...\n";
    grid = new int *[num_rows];
    for (int j = 0; j < num_rows; j++)
    {
      cout << "\tallocating row " << j+1 << endl;
      grid[j] = new int[num_columns];
    }

    // Place data into grid
    cout << "placing data into grid...\n";
    for (int j = 0; j < num_rows; j++)
    {
      for (int k = 0; k < num_columns; k++)
      {
        cin >> grid[j][k];
      }
    }

    // Print out grid
    cout << "printing out grid...\n";
    for (int j = 0; j < num_rows; j++)
    {
      cout << "\t";
      for (int k = 0; k < num_columns; k++)
      {
        cout << grid[j][k] << " ";
      }
      cout << "\n";
    }

    // Deallocate mmemory from grid
    cout << "deallocating memory from grid...\n";
    for (int j = 0; j < num_rows; j++)
    {
      cout << "\tdeallocating memory for row " << j+1 << "\n";
      delete[] grid[j];
    }
    cout << "\tdeallocating memory for grid\n";
    cout << "***********************************************************************" << endl;
    delete[] grid;
    grid = NULL;
  }
  return 0;
}

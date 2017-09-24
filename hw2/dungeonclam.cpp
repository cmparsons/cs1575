/*
* @author: Christian Parsons
* @assignment: HW #2
* @file: dungeonclam.cpp
* @section: B
* @due: September 25, 2017
* @description: Help Zoidberg exit a dungeon using recursive backtracking.
*/

#include <iostream>
#include "memory.hpp"
#include "constants.h"
using namespace std;

// Description: Print dungeon 2D grid.
// pre: row > 0
//      col > 0
//      dungeon[row][col] points to allocated memory
// post: 2D dungeon grid is printed on screen
void print_dungeon(char **const dungeon, const int row, const int col);

// Description: Find Zoidberg's position in dungeon.
// pre: num_rows > 0
//      num_cols > 0
// post: If Zoidberg is in the grid, row and col are updated to his position.
//       Otherwise, row = num_rows - 1 and col = num_cols - 1
void find_zoidberg(char **const dungeon,
                   int &row,
                   int &col,
                   const int num_rows,
                   const int num_cols);

// Description: Get data for dungeon from keyboard input.
// pre: num_rows > 0
//      num_cols > 0
//      num_rows and num_cols point to allocated memory for dungeon
// post: dungeon has data stored
void get_dungeon_data(char **dungeon, const int num_rows, const int num_cols);

// Description: Find path for Zoidberg to escape dungeon.
// pre: num_rows > 0
//      num_cols > 0
//      dungeon[row][col] points to allocated memory
// post: Returns true if Zoidberg able to escape dungeon. Otherwise, returns
//       false. CRUMB and ACCESSED characters left in spaces visited by Zoidberg
bool exit_dungeon(char **dungeon,
                  int row,
                  int col,
                  const int num_rows,
                  const int num_cols);

// Description: Shows breadcrumb path from Zoidberg to exit.
// pre:         num_rows > 0
//              num_cols > 0
//              num_rows and num_cols point to allocated memory for dungeon
// post:        Removes all ACCESSED characters in dungeon and leaves only
//              CRUMB characters.
void show_path(char **dungeon, const int num_rows, const int num_cols);

int main()
{
  char **dungeon = NULL;
  int num_rows, num_cols, start_row, start_col;
  int count = 0; // track number of test cases

  cin >> num_cols >> num_rows;
  cin.ignore(); // ignore new line

  while (num_rows != 0 && num_cols != 0)
  {
    dungeon = allocate_dynamic_2d_array<char>(num_rows, num_cols);

    get_dungeon_data(dungeon, num_rows, num_cols);
    find_zoidberg(dungeon, start_row, start_col, num_rows, num_cols);

    // If Zoidberg escaped the dungeon, show his path
    if (exit_dungeon(dungeon, start_row, start_col, num_rows, num_cols))
    {
      show_path(dungeon, num_rows, num_cols);

      // Print results
      cout << "Map : " << count++ << endl;
      print_dungeon(dungeon, num_rows, num_cols);
    }

    deallocate_2d_array<char>(dungeon, num_rows);

    // Get next data set
    cin >> num_cols >> num_rows;
    cin.ignore(); // ignore new line
  }

  return 0;
}

void show_path(char **dungeon, const int num_rows, const int num_cols)
{
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      if (dungeon[i][j] == ACCESSED)
        dungeon[i][j] = OPEN;

  return;
}

bool exit_dungeon(char **dungeon,
                  int row,
                  int col,
                  const int num_rows,
                  const int num_cols)
{
  // Base case: Reached exit
  if (dungeon[row][col] == EXIT)
    return true;

  // Made wrong move
  if (dungeon[row][col] != OPEN && dungeon[row][col] != ZOIDBERG)
    return false; // backtrack

  if (dungeon[row][col] != ZOIDBERG)
    dungeon[row][col] = ACCESSED;

  // North
  if (exit_dungeon(dungeon, row - 1, col, num_rows, num_cols))
  {
    if (dungeon[row][col] != ZOIDBERG)
      dungeon[row][col] = CRUMB;

    return true;
  }
  // East
  if (exit_dungeon(dungeon, row, col + 1, num_rows, num_cols))
  {
    if (dungeon[row][col] != ZOIDBERG)
      dungeon[row][col] = CRUMB;

    return true;
  }
  // South
  if (exit_dungeon(dungeon, row + 1, col, num_rows, num_cols))
  {
    if (dungeon[row][col] != ZOIDBERG)
      dungeon[row][col] = CRUMB;

    return true;
  }
  // West
  if (exit_dungeon(dungeon, row, col - 1, num_rows, num_cols))
  {
    if (dungeon[row][col] != ZOIDBERG)
      dungeon[row][col] = CRUMB;

    return true;
  }

  return false; // No possible movies -- backtrack
}

void get_dungeon_data(char **dungeon, const int num_rows, const int num_cols)
{
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_cols; j++)
      cin.get(dungeon[i][j]);

    cin.ignore(); // ignore new line
  }

  return;
}

void print_dungeon(char **const dungeon, const int row, const int col)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
      cout << dungeon[i][j] << ' ';

    cout << endl;
  }

  return;
}

void find_zoidberg(char **const dungeon,
                   int &row,
                   int &col,
                   const int num_rows,
                   const int num_cols)
{
  for (row = 0; row < num_rows; row++)
    for (col = 0; col < num_cols; col++)
      if (dungeon[row][col] == ZOIDBERG)
        return;

  return;
}

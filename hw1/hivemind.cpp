/*
* @author: Christian Parsons
* @file: hivemind.cpp
* @section: B
* @due: September 8, 2017
* @description: Find number of robots experiencing robot anxiety disorder in a
*               given hive.
*/

#include <iostream>
#include <cmath>
using namespace std;

// minimum number of robots to be considered "not isolated"
const int NOT_ISOLATED_MIN = 2;

/*
* @description: allocates memory for a 2D array
* @pre: num_rows and num_cols are > 0
* @post: memory is allocated for num_rows x num_cols 2D array
*/
int ** allocate_grid(int **grid, const int num_rows, const int num_cols);

/*
* @description: dellocates memory of a 2D array
* @pre: num_rows > 0
* @post: memory of a num_rows x num_cols 2D array is deallocated
*/
int ** deallocate_grid(int **grid, const int num_rows);

/*
* @description: finds number of robots surrounding passed point
* @pre:
* @post: returns true if there are fewer than 2 robots within radius. Otherwise,
*        returns false
*/
bool is_isolated(
  int **grid,
  const int point_row,
  const int point_col,
  const int max_row,
  const int max_col,
  const int radius
);

/*
* @description: calculate distance between two points
* @pre: none
* @post: the distance between (x_1, y_2) and (x_2, y_2) is returned
*/
double get_distance(const int x_1, const int y_1, const int x_2, const int y_2);

int main()
{
  int num_test_cases = 0;
  int num_rows = 0;
  int num_columns = 0;
  int **grid = NULL;
  int radius = 0; // robot's signal strength
  int num_rad_robots = 0; // number of isolated hive members

  cin >> num_test_cases;

  for (int i = 0; i < num_test_cases; i++)
  {
    num_rad_robots = 0;
    cin >> num_rows >> num_columns;

    // Allocate memory for grid
    grid = allocate_grid(grid, num_rows, num_columns);

    // Place data into grid
    for (int j = 0; j < num_rows; j++)
    {
      for (int k = 0; k < num_columns; k++)
      {
        cin >> grid[j][k];
      }
    }

    // Count number of robots experiencing symptoms of RAD
    for (int j = 0; j < num_rows; j++)
    {
      for (int k = 0; k < num_columns; k++)
      {
        radius = grid[j][k];
        if (radius != 0)
        {
          if (is_isolated(grid, j, k, num_rows, num_columns, radius))
          {
            num_rad_robots++;
          }
        }
      }
    }

    // Print results
    cout << "Hive mind " << i + 1 << " has " << num_rad_robots
         << " isolated members." << endl;

    // Deallocate memory from grid
    grid = deallocate_grid(grid, num_rows);
  }

  return 0;
}

int ** allocate_grid(int ** grid, const int num_rows, const int num_cols)
{
  for (int i = 0; i < num_rows; i++)
  {
    grid = new int *[num_rows];
    for (int j = 0; j < num_rows; j++)
    {
      grid[j] = new int[num_cols];
    }
  }

  return grid;
}

int ** deallocate_grid(int **grid, const int num_rows)
{
  for (int i = 0; i < num_rows; i++)
  {
    delete[] grid[i];
  }
  delete[] grid;
  grid = NULL;

  return grid;
}

bool is_isolated(
  int **grid,
  const int point_row,
  const int point_col,
  const int max_row,
  const int max_col,
  const int radius
)
{
  int count = 0; // number of robots within radius
  double distance = 0;

  // Check surrounding area within the radius of the point of interest
  for (int i = point_row - radius; i <= point_row + radius; i++)
  {
    for (int j = point_col - radius; j <= point_col + radius; j++)
    {
      // Only access memory allocated for the grid
      if (i >= 0 && j >= 0 && i < max_row && j < max_col)
      {
        if (grid[i][j] != 0 && (i != point_row || j != point_col))
        {
          distance = get_distance(point_col, point_row, j, i);
          if (distance <= radius)
          {
            count++;
          }
        }
        if (count >= NOT_ISOLATED_MIN)
        {
          return false;
        }
      }
    }
  }

  return true;
}

double get_distance(const int x_1, const int y_1, const int x_2, const int y_2)
{
  return sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
}

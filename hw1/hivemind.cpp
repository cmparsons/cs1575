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
int ** allocate_grid(const int num_rows, const int num_cols);

/*
* @description: insert data into a 2d array
* @pre: num_rows and num_cols > 0
* @post: data is set in each member of the 2D array
*/
void insert_grid_data(int **grid, const int num_rows, const int num_cols);

/*
* @description: count number of robots experiencing RAD
* @pre: num_rows and num_cols > 0
*       grid should have meaningful data
* @post: returns number of robots experiencing RAD in the passed grid
*/
int count_rad_robots(int **const grid, const int num_rows, const int num_cols);

/*
* @description: dellocates memory of a 2D array
* @pre: num_rows > 0
* @post: memory of a num_rows x num_cols 2D array is deallocated
*/
void deallocate_grid(int ** grid, const int num_rows);

/*
* @description: finds number of robots surrounding passed point
* @pre: point_row, point_col, max_row, max_col should be greater than 0
* @post: returns true if there are fewer than 2 robots within radius. Otherwise,
*        returns false
*/
bool is_isolated(
  int **const grid,
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
  int num_rad_robots = 0; // number of isolated hive members

  cin >> num_test_cases;

  for (int i = 0; i < num_test_cases; i++)
  {
    num_rad_robots = 0;
    cin >> num_rows >> num_columns;

    grid = allocate_grid(num_rows, num_columns);

    insert_grid_data(grid, num_rows, num_columns);

    num_rad_robots = count_rad_robots(grid, num_rows, num_columns);

    // Print results
    cout << "Hive mind " << i + 1 << " has " << num_rad_robots
         << " isolated members." << endl;

    deallocate_grid(grid, num_rows);
  }

  return 0;
}

int ** allocate_grid(const int num_rows, const int num_cols)
{
  int **grid = new int *[num_rows];
  for (int i = 0; i < num_rows; i++)
  {
    grid[i] = new int[num_cols];
  }

  return grid;
}

void deallocate_grid(int ** grid, const int num_rows)
{
  for (int i = 0; i < num_rows; i++)
  {
    delete[] grid[i];
  }
  delete[] grid;
  grid = NULL;

  return;
}

void insert_grid_data(int **grid, const int num_rows, const int num_cols)
{
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_cols; j++)
    {
      cin >> grid[i][j];
    }
  }

  return;
}

int count_rad_robots(int **const grid, const int num_rows, const int num_cols)
{
  int num_rad_robots = 0;
  int radius = 0; // robot's signal strength

  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_cols; j++)
    {
      radius = grid[i][j];
      if (radius != 0)
      {
        if (is_isolated(grid, i, j, num_rows, num_cols, radius))
        {
          num_rad_robots++;
        }
      }
    }
  }

  return num_rad_robots;
}

bool is_isolated(
  int **const grid,
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

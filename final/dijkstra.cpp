#include <iostream>
#include <fstream>
#include "graph_matrix.h"
using namespace std;

int main()
{
  GraphMatrix city(5);

  city.set_edge(0, 1, 7);
  city.set_edge(0, 2, 10);
  city.set_edge(1, 3, 8);
  city.set_edge(2, 3, 5);

  for (int i = 0; i < city.get_num_edge(); i++)
  {
    for (int j = 0; j < city.get_num_edge(); j++)
    {
      cout << city.weight(i, j) << " ";
    }
    cout << "\n";
  }

  return 0;
}

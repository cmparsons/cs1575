#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <queue>
#include <vector>
using namespace std;

#include "graph_matrix.h"

#define INFINITY 999999
#define START "airport"
#define END "hospital"

struct Edge
{
  int vertex;
  int distance;

  Edge(int v, int d) : vertex(v), distance(d) {}

  bool operator>(const Edge &rhs) const
  {
    return distance > rhs.distance;
  }
};

struct Results
{
  int trash_cans;
  int path_cost;

  Results() : trash_cans(0), path_cost(INFINITY) {}

  Results(int tc, int pc) : trash_cans(tc), path_cost(pc) {}

  Results &operator=(Results &rhs)
  {
    trash_cans = rhs.trash_cans;
    path_cost = rhs.path_cost;
    return *this;
  }
};

Results dijkstra(GraphMatrix &G, const string start, const string end);

#endif
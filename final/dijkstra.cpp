#include <iostream>
#include "graph_matrix.h"
#include "dijkstra.h"
using namespace std;

void create_graph(GraphMatrix &G, const int size);
void print_graph(GraphMatrix &G);
void print_verts(GraphMatrix &G);
int get_total_trash_cans(GraphMatrix &G, Vertex *const verts, int *const parents, int total_trash_cans, int idx);
int get_path_cost(GraphMatrix &G, int *const parents, int path_cost, int parent_idx, int idx);

int main()
{
  int num_test_cases, num_locations;
  string city_name;

  cin >> num_test_cases;

  for (int i = 0; i < num_test_cases; i++)
  {
    cin >> city_name >> num_locations;

    GraphMatrix city(num_locations);
    create_graph(city, num_locations);
    Results results = dijkstra(city, START, END);

    if (results.path_cost == INFINITY && results.trash_cans == 0)
      cout << "No path found" << endl;
    else
      cout << "#" << i + 1 << " : " << city_name << ", " << results.path_cost << " tokens, " << results.trash_cans << " snacks." << endl;
  }

  return 0;
}

void print_verts(GraphMatrix &G)
{
  Vertex *verts = G.get_verts();
  for (int i = 0; i < G.get_num_verts(); i++)
  {
    cout << "i = " << i << " (" << verts[i].name << ", " << verts[i].val << "), ";
  }
  cout << endl;
  return;
}

void print_graph(GraphMatrix &G)
{
  for (int i = 0; i < G.get_num_verts(); i++)
  {
    for (int j = 0; j < G.get_num_verts(); j++)
    {
      cout << G.weight(i, j) << " ";
    }
    cout << endl;
  }
  print_verts(G);
  return;
}

void create_graph(GraphMatrix &G, const int size)
{
  string location_name;
  int num_trash_cans, weight, num_neighbors, vertex_idx, neighbor_idx;

  for (int i = 0; i < size; i++)
  {
    cin >> location_name >> num_trash_cans >> num_neighbors;
    vertex_idx = G.add_vertex(location_name, num_trash_cans);

    // Add neighbors
    for (int j = 0; j < num_neighbors; j++)
    {
      cin >> location_name >> weight;

      neighbor_idx = G.get_index_vertex(location_name);

      if (neighbor_idx == G.get_num_verts())
        neighbor_idx = G.add_vertex(location_name);

      G.set_edge(vertex_idx, neighbor_idx, weight);
    }
  }
  return;
}

Results dijkstra(GraphMatrix &G, const string start, const string end)
{
  int num_verts = G.get_num_verts();
  int *distances = new int[num_verts];
  int *parents = new int[num_verts]; // The vertex where you came from
  int vertex = G.get_index_vertex(start);
  Vertex *verts = G.get_verts();

  priority_queue<Edge, vector<Edge>, greater<Edge> > unvisited;

  Edge temp = Edge(vertex, 0);
  unvisited.push(temp);

  for (int i = 0; i < num_verts; i++)
    distances[i] = INFINITY;

  distances[vertex] = 0; // Start
  parents[vertex] = -1;  // -1 represents the start vertex

  for (int i = 0; i < num_verts; i++)
  {
    do
    {
      if (unvisited.empty())
        return Results(); // Nothing to remove

      temp = unvisited.top();
      unvisited.pop();
      vertex = temp.vertex;
    } while (G.get_mark(vertex) == VISITED);

    G.set_mark(vertex, VISITED);

    if (distances[vertex] == INFINITY)
      return Results(); // Unreachable vertex

    // Calculate distances for all neighbors
    for (int j = G.first(vertex); j < num_verts; j = G.next(vertex, j))
    {
      int new_distance = distances[vertex] + G.weight(vertex, j);

      // If path cost is equal, update route with path that gets more trash cans
      if (distances[j] == new_distance)
      {
        int old_path_trash_cans = get_total_trash_cans(G, verts, parents, 0, j);
        int new_path_trash_cans = get_total_trash_cans(G, verts, parents, verts[j].val, vertex);

        if (old_path_trash_cans < new_path_trash_cans)
        {
          distances[j] = distances[vertex] + G.weight(vertex, j);
          temp.distance = distances[j];
          temp.vertex = j;
          parents[j] = vertex; // Update with path that visits more trashcans

          unvisited.push(temp); // Insert new distance in heap
        }
      }
      else if (distances[j] > new_distance)
      {
        distances[j] = distances[vertex] + G.weight(vertex, j);
        temp.distance = distances[j];
        temp.vertex = j;
        parents[j] = vertex; // Update with faster route

        unvisited.push(temp); // Insert new distance in heap
      }
    }
  }

  int end_idx = G.get_index_vertex(end);
  int total_trash_cans = get_total_trash_cans(G, verts, parents, 0, end_idx);
  int total_cost = get_path_cost(G, parents, 0, parents[end_idx], end_idx);

  delete[] distances;
  delete[] parents;
  distances = NULL;
  parents = NULL;

  return Results(total_trash_cans, total_cost);
}

int get_total_trash_cans(GraphMatrix &G, Vertex *const verts, int *const parents, int total_trash_cans, int idx)
{
  // Reached Start vertex
  if (idx == -1)
    return total_trash_cans;

  return get_total_trash_cans(G, verts, parents, total_trash_cans + verts[idx].val, parents[idx]);
}

int get_path_cost(GraphMatrix &G, int *const parents, int path_cost, int parent_idx, int idx)
{
  // Reached Start vertex
  if (parent_idx == -1)
    return path_cost;

  return get_path_cost(G, parents, path_cost + G.weight(parent_idx, idx), parents[parent_idx], parent_idx);
}

#include <iostream>
#include <fstream>
#include "graph_matrix.h"
using namespace std;

void create_graph(GraphMatrix &G, const int size, ifstream &fin);
void print_graph(GraphMatrix &G);
void print_verts(GraphMatrix &G);

int main()
{
  int num_test_cases, num_locations, num_trash_cans, weight, num_neighbors;
  string city_name, location_name;
  ifstream fin("sampleinput.txt");

  fin >> num_test_cases;

  for (int i = 0; i < num_test_cases; i++)
  {
    fin >> city_name >> num_locations;

    GraphMatrix city(num_locations);
    cout << city_name << ":" << endl;
    create_graph(city, num_locations, fin);
    print_graph(city);
  }

  fin.close();

  return 0;
}

void print_verts(GraphMatrix &G)
{
  Vertex *verts = G.get_verts();
  for (int i = 0; i < G.get_num_verts(); i++)
  {
    cout << "i = " << i << "\t(" << verts[i].name << ", " << verts[i].val << "), ";
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

void create_graph(GraphMatrix &G, const int size, ifstream &fin)
{
  string location_name;
  int num_trash_cans, weight, num_neighbors, vertex_idx, neighbor_idx;

  for (int i = 0; i < size; i++)
  {
    fin >> location_name >> num_trash_cans >> num_neighbors;
    vertex_idx = G.add_vertex(location_name, num_trash_cans);

    // Add neighbors
    for (int j = 0; j < num_neighbors; j++)
    {
      fin >> location_name >> weight;

      neighbor_idx = G.get_index_vertex(location_name);

      if (neighbor_idx == G.get_num_verts())
        neighbor_idx = G.add_vertex(location_name);

      G.set_edge(vertex_idx, neighbor_idx, weight);
    }
  }
  return;
}
#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#define UNVISITED false
#define VISITED true

class GraphMatrix
{
private:
  int m_num_vertex, m_num_edge;
  int **m_matrix;
  bool *m_mark;

public:
  GraphMatrix(const int size);

  ~GraphMatrix();

  int get_num_verts() const { return m_num_vertex; }

  int get_num_edge() const { return m_num_edge; }

  int first(const int vertex) const;

  int next(const int, const int) const;

  void set_edge(const int v1, const int v2, const int wt);

  void del_edge(const int v1, const int v2);

  bool is_edge(const int v1, const int v2) const { return m_matrix[v1][v2] != 0; }

  int weight(int v1, int v2) const { return m_matrix[v1][v2]; }

  int get_mark(int vertex) const { return m_mark[vertex]; }

  void set_mark(int vertex, bool val) { m_mark[vertex] = val; }
};

#include "graph_matrix.hpp"

#endif

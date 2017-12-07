#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include "graph_matrix.h"

GraphMatrix::GraphMatrix(const int size)
{
  m_num_vertex = size;
  m_num_edge = 0;
  m_mark = new bool[size];

  for (int i = 0; i < m_num_vertex; i++)
  {
    m_mark[i] = UNVISITED;
  }

  m_matrix = new int *[m_num_vertex];

  for (int i = 0; i < m_num_vertex; i++)
  {
    m_matrix[i] = new int[m_num_vertex];
  }

  for (int i = 0; i < m_num_vertex; i++)
  {
    for (int j = 0; j < m_num_vertex; j++)
    {
      m_matrix[i][j] = 0;
    }
  }
}

GraphMatrix::~GraphMatrix()
{
  delete[] m_mark;

  for (int i = 0; i < m_num_vertex; i++)
  {
    delete[] m_matrix[i];
  }
  delete[] m_matrix;
}

int GraphMatrix::first(const int vertex) const
{
  for (int i = 0; i < m_num_vertex; i++)
  {
    if (m_matrix[vertex][i] != 0)
    {
      return i;
    }
  }
  return m_num_vertex;
}

int GraphMatrix::next(const int vertex, const int weight) const
{
  for (int i = weight + 1; i < m_num_vertex; i++)
  {
    if (m_matrix[vertex][i] != 0)
      return i;
  }
  return m_num_vertex;
}

void GraphMatrix::set_edge(const int v1, const int v2, const int wt)
{
  if (m_matrix[v1][v2] == 0)
    m_num_edge++;

  m_matrix[v1][v2] = wt;
  return;
}

void GraphMatrix::del_edge(int v1, int v2)
{
  if (m_matrix[v1][v2] != 0)
    m_num_edge--;

  m_matrix[v1][v2] = 0;
  return;
}

#endif

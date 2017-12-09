#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

GraphMatrix::GraphMatrix(const int size)
{
  m_num_vertex = size;
  m_num_edge = 0;
  m_mark = new bool[size];
  m_verts = new Vertex[size];

  for (int i = 0; i < m_num_vertex; i++)
  {
    m_mark[i] = UNVISITED;
    m_verts[i].name = "";
    m_verts[i].val = 0;
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
  delete[] m_verts;

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
      return i;
  }
  return m_num_vertex;
}

int GraphMatrix::next(const int vertex, const int current) const
{
  for (int i = current + 1; i < m_num_vertex; i++)
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

int GraphMatrix::get_index_vertex(const string key) const
{
  for (int i = 0; i < m_num_vertex; i++)
  {
    if (key == m_verts[i].name)
      return i;
  }
  return m_num_vertex; // key not found
}

int GraphMatrix::add_vertex(const string key, const int val)
{
  for (int i = 0; i < m_num_vertex; i++)
  {
    if (key == m_verts[i].name || m_verts[i].name == "")
    {
      m_verts[i].name = key;
      m_verts[i].val = val;
      return i;
    }
  }
  return m_num_vertex - 1; // This should never happen
}

#endif

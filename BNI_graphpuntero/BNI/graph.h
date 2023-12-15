#pragma once

#include "structs.h"
#define initial_index 0

class Graph
{
private:
  std::vector<vertice> vertices_;
  int number_of_vertices_;
public:
  Graph();
  Graph(std::string file_name);
  ~Graph();

  void InsertVerticesToGraph();

  //debug
  void DebugFunction();
  vertice get_vertice(int id);
  void set_vertice(vertice to_insert);
};


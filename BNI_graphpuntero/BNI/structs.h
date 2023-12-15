#pragma once

#include "libraries.h"
struct vertice;
struct edge;
struct node;

struct vertice
{
  int id;
  bool visited;
  std::vector<edge> edges;

  vertice& operator=(const vertice& other) {
    id = other.id;
    visited = other.visited;
    edges = other.edges;

    return *this;
  }
};

struct edge
{
  vertice origin;
  float cost;
  vertice destination;

  edge& operator=(const edge& other) {
      origin = other.origin;
      cost = other.cost;
      destination = other.destination;
    return *this;
  }
};

/*struct node 
{
  vertice vertice_rep;
  node *father;
  int depth;
  float cost;
  std::string name;  
};*/


#pragma once

#include "graph.h"
#include "node.h"

class Tree {
  private:
    std::vector<Node> generated_;
    std::vector<Node> inspected_;
    Node root_;
    int check_destination_id_;
    Graph info_graph_;
    Node father_root;

  public:
    Tree();
    Tree(Graph read_graph, int origin_id, int destination_id, int operation);
    ~Tree();
    //algoritmo --> escoge, pregunta, genera
    //funcion de busqueda en amplitud
    void UniformedBreathSearch();
    //funcion de busqueda en profundidad                      
    void UninformedDepthSearch();

    //nuevo
    void showResult(Node result);
};
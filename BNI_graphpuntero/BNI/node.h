#pragma once

#include "structs.h"

class Node {
  private:
    vertice vertice_rep_;
    Node* father_ = nullptr;
    int depth_;
    float cost_;
    std::string name_; 
  
  public:
  std::vector<Node> fathers_;

    Node();
    Node(vertice to_rep, Node* father, int depth, float cost);
    ~Node();

    //esto es nuevo
    //Node(const Node& other);

    void set_node_name();
    void set_father(Node father);
    void set_depth(int new_depth);
    void set_cost(float new_cost);
    

    vertice get_vertice();
    Node* get_father();
    int get_depth();
    float get_cost();
    std::string get_name();

    /*bool operator==(const Node& other) const {
      return vertice_rep_ == other.get_vertice();
    }*/
    Node& operator=(const Node& other) {
      vertice_rep_ = other.vertice_rep_;
      father_ = other.father_;
      depth_ = other.depth_;
      cost_ = other.cost_;
      name_ = other.name_;

    return *this;
  }

};

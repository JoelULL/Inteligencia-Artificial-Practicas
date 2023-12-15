#include "node.h"

Node::Node() {}

Node::Node(vertice to_rep, Node* father,int depth, float cost) {
  vertice_rep_ = to_rep;
  father_ = father;
  depth_ = depth;
  cost_ = cost;

  set_node_name();
}

Node::~Node() {}

void Node::set_node_name() {
  name_ = std::to_string(vertice_rep_.id) + "_" + std::to_string(depth_);
}

void Node::set_father(Node father) {
  father_ = &father;
}

void Node::set_depth(int new_depth) {
  depth_ = new_depth;
}

void Node::set_cost(float new_cost) {
  cost_ = new_cost;
}

vertice Node::get_vertice() { 
  return vertice_rep_;
}

Node* Node::get_father() {
  return father_;
}

int Node::get_depth() {
  return depth_;
}

float Node::get_cost() {
  return cost_;
}

std::string Node::get_name() {
  return name_;
}

#include "Astar.hpp"
using namespace std::placeholders;

bool Coordinates::operator == (const Coordinates& coordinates_) {
  return (x == coordinates_.x && y == coordinates_.y);
}

Node::Node(Coordinates coordinates_, Node *parent_){
  parent = parent_;
  coordinates = coordinates_;
  G = H = 0;
}

uint Node::getF() {
  return G + H;
}

AStar::AStar() {
  directions = 8;
  setHeuristic(&Heuristic::manhattan);
  direction = {
    {0,1}, {1,0}, {0,-1}, {-1,0},
    {-1,-1}, {1,1}, {-1,1},{1,-1}
  };
}

void AStar::setWorldSize(Coordinates worldSize_) {
  worldSize = worldSize_;
}

void AStar::setHeuristic(HeuristicFunction heuristic_) {
  heuristic = std::bind(heuristic_, _1, _2);
}

void AStar::addCollision(Coordinates coordinates_) {
  walls.push_back(coordinates_);
}

void AStar::clearCollisions() {
  walls.clear();
}
/*Algoritmo principal*/
CoordinateList AStar::findPath(Coordinates source_, Coordinates target_) {
  Node *current = nullptr;
  NodeSet openSet, closeSet;
  openSet.reserve(100);
  closeSet.reserve(100);
  openSet.push_back(new Node(source_));
  //para el resultado
  uint G_final, H_final, F_final = 0;
  (void)G_final;
  (void)H_final;
  (void)F_final;
  //
  /*Modi*/
  int counter = 0;

  while(!openSet.empty()) {
    //ordenar el vector de abiertos para que siempre se escoja el de menor coste
    sortOpenSet(openSet);
    //
    auto current_it = openSet.begin();
    current = *current_it;
    if (counter == 1) {
      std::random_device rd;
      std::mt19937 gen(rd());
      int min_index = 0;
      int max_index = openSet.size() - 1;
      std::uniform_int_distribution<int> distribution(min_index, max_index);
      int randNum = distribution(gen);
      int check = 0;
    for (auto it = openSet.begin(); it != openSet.end(); it++) {
      auto node = *it;
      if (check == randNum) {
        current = node;
        current_it = it;
        break;
      }
      check++;
    }    
    std::cout << randNum<<"\n";
    std::cout << openSet.size()<<"\n";
    std::cout << current->coordinates.x << ", " << current->coordinates.y<<"\n";  
    }
    if (counter!= 1) {
      for (auto it = openSet.begin(); it != openSet.end(); it++) {
        auto node = *it;
        if (node->getF() <= current->getF()) {
          current = node;
          current_it = it;
        }
      }
    }
    counter++; //modi
    if (current->coordinates == target_) {
      H_final = current->H;
      G_final = current->G;
      F_final = current->getF();
      break;
    }

    closeSet.push_back(current);
    openSet.erase(current_it);

    for (uint i = 0; i < directions; ++i) {
      Coordinates newCoordinates(current->coordinates + direction[i]);
      if (detectCollision(newCoordinates) || findNodeOnList(closeSet, newCoordinates)) {
        continue;
      }

      uint totalCost = current->G + ((i < 4) ? 5 : 10); /*mov diagonal = 10, en otro caso = 5*/

      Node *successor = findNodeOnList(openSet, newCoordinates);
      if (successor == nullptr) {
        successor = new Node(newCoordinates, current);
        successor->G = totalCost;
        successor->H = heuristic(successor->coordinates, target_);
        openSet.push_back(successor);
      }
      else if (totalCost < successor->G) {
        successor->parent = current;
        successor->G = totalCost;
      }
    }
  }

  CoordinateList path;
  while(current != nullptr) {
    path.push_back(current->coordinates);
    current = current->parent;
  }

  generateResult(openSet, closeSet, target_, path, G_final, H_final, F_final);

  releaseNodes(openSet);
  releaseNodes(closeSet);
  
  return path;
}

Node* AStar::findNodeOnList(NodeSet& nodes_, Coordinates coordinates_) {
  for (auto node : nodes_) {
    if(node->coordinates == coordinates_) {
      return node;
    }
  }
  return nullptr;
}

void AStar::releaseNodes(NodeSet& nodes_) {
  for (auto it = nodes_.begin(); it != nodes_.end();) {
    delete *it;
    it = nodes_.erase(it);
  }
}

bool AStar::detectCollision(Coordinates coordinates_) {
  if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
    coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
    std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
      return true;
    }
    return false;
}

void AStar::debug() {
  std::cout << "El world size es de {"<<worldSize.x << ", " << worldSize.y << "}\n";
  std::cout << "Las coordenadas donde hay colisiones son: \n";
  for (size_t i = 0; i < walls.size(); i++) {
    std::cout << "(" << walls[i].x <<  ", " << walls[i].y << "}\n";
  }
  std::cout << "la heuristica con las coordenadas de prueba es: " << heuristic({0,3},{4,1}) << "\n";
}

/**
 * @brief Metodo de ordenacion usando el algoritmo
 * de la burbuja, permite la ordenacion de un vector de nodos
 * en funcion de su F(n)
 * @param set set de nodos a ordenar pasado como referencia
 */
void AStar::sortOpenSet(NodeSet& set) {
  bool swapped;
  for (size_t i = 0; i < set.size() - 1; ++i) {
    swapped = false;
    for (size_t j = 0; j <set.size()-i-1;++j) {
      if(set[j]->getF() > set[j+1]->getF()) {
          std::swap(set[j],set[j+1]);
          swapped = true;
      }
    }
    if (swapped == false)
      break;
  }
}

void AStar::generateResult(NodeSet& openSet, NodeSet& closeSet, Coordinates target_, 
    CoordinateList& path, uint G_final, uint H_final, uint F_final) {
  
  std::ofstream outputFile("resultado.txt");
  if (path[0] == target_) {
    outputFile << "- Lista de nodos abiertos (nombres en base a sus coordenadas): ";
    for (auto it = openSet.begin(); it != openSet.end(); it++) {
      auto node = *it;
      outputFile <<"(" << node->coordinates.x << ", "<< node->coordinates.y << ") ";
    }
    outputFile << "\n";
    outputFile << "- Lista de nodos cerrados (nombres en base a sus coordenadas): ";
    for (auto it = closeSet.begin(); it != closeSet.end(); it++) {
      auto node = *it;
      outputFile <<"(" << node->coordinates.x << ", "<< node->coordinates.y << ") ";
    }
    outputFile << "\n- Costes del destino: G: "<< G_final << " H: "<< H_final 
      << " F: " << F_final << "\n";
    
  } else {
    unrecheable_ = true;
    outputFile << "No se encontro el camino";
  }
  outputFile.close();
}

Coordinates Heuristic::getDelta(Coordinates source_, Coordinates target_){
  return {abs(source_.x - target_.x), abs(source_.y - target_.y)};
}
uint Heuristic::manhattan(Coordinates source_, Coordinates target_){
  auto delta = std::move(getDelta(source_, target_));
  return static_cast<uint>(3*(delta.x + delta.y));
}

uint Heuristic::euclidean(Coordinates source_, Coordinates target_) {
  auto delta = std::move(getDelta(source_, target_));
  return static_cast<uint>(3*std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)));
}
uint Heuristic::octogonal(Coordinates source_, Coordinates target_) {
  auto delta = std::move(getDelta(source_, target_));
  return 3 *(delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
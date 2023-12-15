#include "graph.h"

Graph::Graph() {}
Graph::Graph(std::string file_name) {
  std::ifstream my_file;
  my_file.open(file_name);

  if (!my_file.is_open()) {
    perror("Error couldn't open the file!");
    exit(EXIT_FAILURE);
  }
  std::string line;
  //obtencion de las distancias
  int line_counter = 0;
  int id_origin = 0; //i
  int id_destination = id_origin + 1; //j
  edge to_insert;
  std::string no_edge = "-1";
  while (std::getline(my_file, line)) {
    if (line_counter == 0) {
      number_of_vertices_ = std::stoi(line);
      line.clear();
      InsertVerticesToGraph();
      line_counter++;
    }
    else {
      if (std::stof(line) != -1) {
        //(i,j)
        to_insert.origin = vertices_[id_origin];
        to_insert.cost = std::stof(line);
        to_insert.destination = vertices_[id_destination];
        vertices_[id_origin].edges.push_back(to_insert);
        //(j,i)
        to_insert.origin = vertices_[id_destination];
        to_insert.destination = vertices_[id_origin];
        vertices_[id_destination].edges.push_back(to_insert);
        //std::cout << "se mete aqui leyendo: "<< line << "\n";
        line.clear();
 
      }
      id_destination++;

      if (id_destination == number_of_vertices_) {
        id_origin++;
        id_destination = id_origin + 1;
      }
    }
    //line.clear();
  }
  my_file.close();
  //DebugFunction();
    
}
Graph::~Graph() {}

void Graph::InsertVerticesToGraph() {
  for (int i = 0; i < number_of_vertices_; i++) {
    vertice to_insert;
    to_insert.id = i;
    to_insert.visited = false;
    vertices_.push_back(to_insert);
  }
}

vertice Graph::get_vertice(int id) {
  return vertices_[id];
}

//debug function
void Graph::DebugFunction() {
  std::cout << "El numero de vertices es: " << number_of_vertices_ << "\n";
  std::cout << "Los vertices son: ";
  for (size_t i = 0; i < vertices_.size()-1; i++) {
    std::cout << vertices_[i].id << " - ";
  }
  std::cout << vertices_[vertices_.size()-1].id << "\n";
  for (size_t i = 0; i < vertices_.size(); i++) {
    std::cout << "Para el vertice " << vertices_[i].id << " hay las siguientes aristas: \n";
    for (size_t j = 0; j < vertices_[i].edges.size(); j++) {
      std::cout << vertices_[i].edges[j].origin.id << " <- " << vertices_[i].edges[j].cost << " -> " << vertices_[i].edges[j].destination.id << "\n";
    }
    std::cout << "----------------------------\n";
  }
}

void Graph::set_vertice(vertice to_insert) {
  vertices_.push_back(to_insert);
}
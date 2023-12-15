#include "tree.h"

Tree::Tree() {}

Tree::Tree(Graph read_graph, int origin_id, int destination_id, int operation) {
  info_graph_ = read_graph;
  Node to_equal_root((info_graph_).get_vertice(origin_id),&father_root, 0, 0);
  root_ = to_equal_root;
  check_destination_id_ = destination_id;
  generated_.push_back(root_);
  if (origin_id != destination_id) {
    switch (operation)
    {
      case 1: {
            UniformedBreathSearch();
        break;
      }
      case 2: {
            UninformedDepthSearch();
        break;
      }
    
      default: {
        std::cout << "Error\n"; //comletar
        break;
      }
        
    }
  }
  else {
    std::cout << "el nodo inicial es el destino\n";
  }
}
Tree::~Tree() {}


void Tree::UninformedDepthSearch() {
  int limit = 1; //empieza en 1 porque ya se sabe si root contiene el destino o no
  // si la profundidad coincide con el limite no se puede generar un nuevo nodo hijo
  bool founded = false;
  bool check_exist = false;
  bool child_have_been_generated = false;
  Node* actual_node = &generated_[0]; //el comienzo es root

  do {
      for (size_t i = 0; i < actual_node->get_vertice().edges.size(); i++) { //recorrido de los hijos del nodo al que apunta el nodo actual
      // pregunta: ¿El nodo actual ya tiene a este hijo?
      if (actual_node->get_vertice().edges[i].destination.visited) {
            check_exist = true;
            break;
      }

  
      for (size_t j = 0; j < actual_node->fathers_.size(); j++) { //recorrido de los padres del vertice actual
        // pregunta: ¿ya esta el vertice ANTERIORMENTE en la rama?
        if (actual_node->fathers_[j].get_vertice().id == actual_node->get_vertice().edges[i].destination.id) { 
            check_exist = true;
            break;
        }
      }

        if (!check_exist) {
          
          actual_node->get_vertice().edges[i].destination.visited = true; // se marca como hijo

          Node new_node((info_graph_).get_vertice(actual_node->get_vertice().edges[i].destination.id), actual_node,
            actual_node->get_depth() + 1, actual_node->get_cost() + actual_node->get_vertice().edges[i].cost);

            
          new_node.fathers_ = new_node.get_father()->fathers_;
          new_node.fathers_.push_back(*new_node.get_father());
         
          child_have_been_generated = true; // se ha generado un hijo
          generated_.push_back(new_node);

          //como he generado un nuevo hijo ahora tengo que analizar a ese hijo
          actual_node = &new_node;

          //std::cout << "esto lo hace"<< actual_node->get_name() << "\n"; es capaz de generarlo
          if (new_node.get_vertice().id == check_destination_id_) {
            founded = true;
            std::cout << "lo encontro\n";
            std::cout << "se llama " << new_node.get_name() << "\n";
            break;
          }
          break;
        }
      }
      check_exist = false;
      child_have_been_generated = false;
      if (actual_node->get_depth() == limit || !child_have_been_generated) { //se ha alcanzado el limite o no se han generado mas hijos
        actual_node = actual_node->get_father();
      }
       
      /*si llega a la raiz y no puede generar mas hijos se limpia el vector*/
      if (actual_node->get_name() == "") {
        generated_.clear();
        generated_.push_back(root_);
        limit++;
      }
      
    //generar hijos del nodo 
    //si llego a la raiz y ni he encontrado el destino ni me quedan hijos por generar, aumentar limite
    //limpiar vector de generados (menos a root) y repetir el proceso hasta que lo encuentre

    //cambiar de padre se hara cuando no se pueda generar mas hijos o bien porque ya estan todas las
    //posibilidades o bien porque ya se llego al limite
  }while(!founded);
}


void Tree::UniformedBreathSearch() {

  bool founded = false;
  bool check_exist = false;
  size_t iterator = 0;
  Node foundednode;
  do {
    //bucle for que recorre las aristas del vertice al que representa el nodo
     for (size_t i = 0; i < generated_[iterator].get_vertice().edges.size();i++) {

      ////bucle for que busca si el hijo ya esta representado en la rama (vector de padres)
      for (size_t j = 0; j < generated_[iterator].fathers_.size(); j++) {
        if (generated_[iterator].fathers_[j].get_vertice().id == generated_[iterator].get_vertice().edges[i].destination.id) {
          check_exist = true; //esta en la lista de padres (en la rama)
          break;
        }
      }
      ///////
        if (!check_exist) {
          Node new_node((info_graph_).get_vertice(generated_[iterator].get_vertice().edges[i].destination.id),
            &generated_[iterator], generated_[iterator].get_depth() + 1, generated_[iterator].get_cost() + generated_[iterator].get_vertice().edges[i].cost);

          new_node.fathers_ = new_node.get_father()->fathers_;
          new_node.fathers_.push_back(*new_node.get_father());
          
          //std::cout << new_node.fathers_.size()<<"\n";
          generated_.push_back(new_node);
          std::cout <<"tamanio: "<< generated_.size() <<" El contenido de generated es \n";
          for (size_t i = 0; i < generated_.size(); i++)
            std::cout << generated_[i].get_name() << "\n";
          //debug
          //std::cout << "new_node es: " << new_node.get_name() << " y su padre es " << new_node.get_father()->get_name() << "\n";
          //
          if (new_node.get_vertice().id == check_destination_id_) {
            founded = true;
            //foundednode = new_node;
            //showResult(new_node);
            std::cout << "el nombre del que encontro es " << new_node.get_name() <<"\n";
            break;
          }
        }
        check_exist = false; 
    }
    
    inspected_.push_back(generated_[iterator]);
    if (!founded)
      iterator++;
  } while(!founded);
  if (founded)
   //showResult(foundednode);
   std::cout << "lo encontro\n";
}

void Tree::showResult(Node result) {
  std::vector<int> showit;
  showit.push_back(result.get_vertice().id);
  //std::cout << showit[0]<<"\n";

  do {
    showit.push_back(result.get_father()->get_vertice().id);
    result = *result.get_father();
    if (result.get_name() == "")
      showit.push_back(result.get_vertice().id);
  }while(result.get_name() == "");

  //std::cout << showit.size() << "\n";
  for (size_t i = 0; i < showit.size(); i++)
    std::cout << showit[i] << "\n";
}

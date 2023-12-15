//#include "tree.h"
#include "tree.h"

int main (int argc, char* argv[]) {
  // manejo de errores (a completar)
  /*if (argc == 1)
    return 1;*/

  /*std::string file_name = argv[1];
  Graph test(file_name);
 
  Tree graph_tree(test, 0, 1, 1);*/
 //Tree(Graph read_graph, int origin_id, int destination_id, int operation);
  /* prueba de la clase nodo
  vertice pepe;
  pepe.id = 0;
  pepe.visited = false;
  Node father;
  Node test(pepe,father,1,2);
  Node have_father(pepe,test,2,3);
  Node other_child(pepe,test,2,4);

  if(other_child.get_father()->get_name().size() == 0) {
    std::cout << "se trata del nodo raiz\n";
  } else {
    std::cout <<"soy have_father y mi padre se llama: " << have_father.get_father()->get_name()<<"\n";
    std::cout << "soy other_child y mi padre se llama: " << other_child.get_father()->get_name()<<"\n";
  }*/
 
  std::string file_name = argv[1];
  Graph test(file_name);
  //test.DebugFunction();
  //tree -> Graph read_graph, int origin_id, int destination_id, int operation
  Tree graph_tree(test, 0, 5, 2);
  //graph_tree.testFunction();
  //graph_tree.UniformedBreathSearch();
  //graph_tree.debugFunction();


  return 0;
}
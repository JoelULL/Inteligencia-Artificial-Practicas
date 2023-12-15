/**
 * @file main.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Declaracion del programa principal. En el el usuario puede
 * decidir si mantiene la entrada y la salida definida por defecto
 * en el archivo del laberinto dado, o si quiere cambiarlos. Para
 * ello por pantalla saldran los mensajes necesarios. Si el usuario escribe una Y 
 * y presiona enter podra cambiar dichos parametros en caso de que escriba cualquier
 * otra letra, se mantendran por defecto. Es obligatorio que se de por linea de 
 * comandos un fichero de entrada con un laberinto.
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Astar.hpp"

bool check_error(int user_value, int system_value) {
  return (user_value < system_value && user_value >= 0);
}
std::string dimensionError = "Error dimension incorrecta\n";

int main(int argc, char* argv[]) {
  int s_r, s_c, e_r, e_c;

  if(argc == 1) {
    std::cout << "Se debe especificar nombre de fichero\n";
    return 1;
  }
  std::string file_name = argv[1];
  MatrixInfo get_matrix_info(file_name);

  std::cout << "Para cambiar la entrada y la salida escribe la letra \"y\" para dejarlo por defecto escribe otra letra\n";
  char not_default;
  std::cin >> not_default;
  if (not_default == 'y') {
    std::cout << "Las filas van de la 0 al al " << get_matrix_info.rows_ - 1;
    std::cout << " y las columnas van del 0 al "<< get_matrix_info.columns_ - 1;

    std::cout << "\nFila de la entrada: ";
    std::cin >> s_r;
    if(!check_error(s_r, get_matrix_info.rows_)) {
      std::cout << dimensionError;
      return 1;
    }
    std::cout << "\nColumna de la entrada: ";
    std::cin >> s_c;
    if(!check_error(s_c, get_matrix_info.columns_)) {
      std::cout << dimensionError;
      return 1;
    }
    std::cout << "\n\nFila de la salida: ";
    std::cin >> e_r;
    if(!check_error(e_r, get_matrix_info.rows_)) {
      std::cout << dimensionError;
      return 1;
    }
    std::cout << "\nColumna de la salida: ";
    std::cin >> e_c;
    if(!check_error(e_c, get_matrix_info.columns_)) {
      std::cout << dimensionError;
      return 1;
    }
    std::cout << "\n";
    get_matrix_info.changeEntrance(s_r,s_c);
    get_matrix_info.changeOut(e_r, e_c);
  }
 
  AStar astar_method;
  /*Tamaño del mundo*/
  astar_method.setWorldSize({get_matrix_info.rows_, get_matrix_info.columns_});
  /*Añadir colisiones*/
  for (int i = 0; i < get_matrix_info.rows_; i++) {
    for (int j = 0; j < get_matrix_info.columns_; j++) {
      if (get_matrix_info.matrix_[i][j] == "1") {
        astar_method.addCollision({i,j});
      }
    }
  }
  //std::cout << "Generate path... \n";
  //astar_method.setHeuristic(Heuristic::euclidean);
  auto path = astar_method.findPath({get_matrix_info.start_.first,get_matrix_info.start_.second},
    {get_matrix_info.end_.first,get_matrix_info.end_.second});

  /*for (auto& coordinate : path){
    std::cout << coordinate.x << " " << coordinate.y << "\n";
  }*/
  //std::cout << "La primera coordenada es: "<< path[0].x << " " << path[0].y << "\n";
  //debug
  //astar_method.debug();
  if(!astar_method.unrecheable_) {
    std::ofstream file("resultado.txt",std::ios::app);
    if (!file.is_open()) {
      std::cout << "Error al abri el archivo\n";
      return 1;
    }
    std::vector<std::vector<std::string>> result;
    result = get_matrix_info.matrix_;
    for (auto& coordinate : path){
      result[coordinate.x][coordinate.y] = "2";
    }
    result[get_matrix_info.start_.first][get_matrix_info.start_.second] = "3";
    result[get_matrix_info.end_.first][get_matrix_info.end_.second] = "4";
    file << "\nEl camino encontrado mostrado graficamente:\n";
    for (int i = 0; i < get_matrix_info.rows_; ++i) {
      for (int j = 0; j < get_matrix_info.columns_; ++j) {
        file << result[i][j] << " ";
      }
      file << "\n";
    }

    file.close();
  }
  else {
    std::cout << "No se encontro el camino\n";
  }
  return 0;
}

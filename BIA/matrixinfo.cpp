#include "matrixinfo.hpp"

MatrixInfo::MatrixInfo() {}

MatrixInfo::~MatrixInfo() {}

MatrixInfo::MatrixInfo(std::string maze_file) {
  bool error = false;
  std::ifstream file(maze_file);

  if (!file.is_open()) {
    std::cout << "No se ha podido abrir el archivo.\n";
    error = true;
  }
  if (!error) {

    file >> rows_;
    file >> columns_;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    matrix_.resize(rows_, std::vector<std::string>(columns_));

    for (int i = 0; i < rows_; ++i) {
      std::string line;
      std::getline(file, line);

      std::istringstream ss(line);
      for (int j = 0; j < columns_; ++j) {
        ss >> matrix_[i][j];
      }
    }
    file.close();
  }
  set_start_coordinates();
  set_end_coordinates();
}

void MatrixInfo::showMatrixInfo() {
  std::cout << "Numero de filas: " << rows_ << "\n";
  std::cout << "Numero de columnas: " << columns_ << "\n";
  std::cout << "Hay " << matrix_[0].size() << " columnas\n";
  std::cout << "Hay " << matrix_.size() << " filas\n";

  std::cout << "El contenido de la matriz leida es:\n";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\nLas coordenadas del inicio son: ( "<< start_.first <<", "<< start_.second << " ).\n";
  std::cout << "Las coordenadas del final son: ( "<< end_.first <<", "<< end_.second << " ).\n";
}

void MatrixInfo::changeEntrance(int row, int column) {
  bool founded = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (matrix_[i][j] == "3") {
        matrix_[i][j] = "0";
        founded = true;
        break;
      }
    }
    if (founded)
      break;
  }
  matrix_[row][column] = "3";
  start_.first = row; //fila
  start_.second = column; //columna
}
void MatrixInfo::changeOut(int row, int column) {
  bool founded = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (matrix_[i][j] == "4") {
        matrix_[i][j] = "0";
        founded = true;
        break;
      }
    }
    if (founded)
      break;
  }
  matrix_[row][column] = "4";
  end_.first = row;
  end_.second = column;
}

void MatrixInfo::set_start_coordinates() {
  bool founded = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (matrix_[i][j] == "3") {
        start_.first = i; //fila
        start_.second = j; //columna
        founded = true;
        break;
      }
    }
    if (founded)
      break;
  } 
}
void MatrixInfo::set_end_coordinates() {
  bool founded = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (matrix_[i][j] == "4") {
        end_.first = i; //fila
        end_.second = j; //columna
        founded = true;
        break;
      }
    }
    if (founded)
      break;
  } 
}
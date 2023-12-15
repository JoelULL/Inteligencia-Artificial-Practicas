/**
 * @file Astar.cpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Definicion de la clase MatrixInfo. En ella se definen los metodos y
 * atributos necearios a desarrollar que permitiran obtener la informacion
 * necesaria del fichero que contiene el laberinto. Esto es el numero de filas
 * el numero de columnas, cual es la entrada, la salida y en que coordenadas existen
 * obstaculos. El nombre de los metodos y atributos han sido escogidos de
 * tal manera que sean autoexplicativos. Se ha comentado aquellas partes del codigo que 
 * asi requieran de una explicacion extra.
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "libraries.hpp"

class MatrixInfo {
  public: 
    std::vector<std::vector<std::string>> matrix_;
    int rows_;
    int columns_;
    std::pair<int, int> start_;
    std::pair<int,int> end_;

    MatrixInfo();
    ~MatrixInfo();
    MatrixInfo(std::string maze_file);
    void showMatrixInfo();

    void changeEntrance(int row, int column);
    void changeOut(int row, int column);
    void set_start_coordinates();
    void set_end_coordinates();
};


/**
 * @file Astar.hpp
 * ESIT, Universidad de la Laguna
 * Grado en Ingenieria Informatica
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * @author Joel Aday Dorta Hernández (alu0100987584@ull.edu.es)
 * @brief Definicion de las estructuras y clases necesarias para el
 * desarrollo de esta practica. En orden nos encontramos: una estructura
 * coordenadas, una estructura que permite representar a los nodos, una clase principal
 * la cual permitira la busqueda A* llamada AStar y una clase que contiene la heuristica
 * necesaria para la busqueda. El nombre de los metodos y atributos han sido escogidos de
 * tal manera que sean autoexplicativos. Se ha comentado aquellas partes del codigo que 
 * asi requieran de una explicacion extra.
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "matrixinfo.hpp"

/**
 * @brief Estructura que permite representar las coordenadas
 * asociadas con cada posicion del laberinto dado.
 */
struct Coordinates {
  int x; //row
  int y; //column

  bool operator == (const Coordinates& coordinates_);
  friend Coordinates operator + (const Coordinates& left_, const Coordinates& right_) {
    return {left_.x + right_.x, left_.y + right_.y};
  }
};

using uint = unsigned int;
using HeuristicFunction = std::function<uint(Coordinates, Coordinates)>;
using CoordinateList = std::vector<Coordinates>;
/**
 * @brief Estructura que permite representar los nodos que se utilizaran
 * para aplicar el algoritmo de busqueda A* a implementar.
 */
struct Node {
  uint G, H; /*Costes G(n) y H(n)*/
  Coordinates coordinates; /*Coordenadas asociadas al nodo, que aparte se usaran para su representacion*/
  Node *parent; /*Puntero al Nodo padre*/

  Node(Coordinates coord_, Node *parent_ = nullptr);
  uint getF(); /*Devolvera el coste de F(n)*/
};

using NodeSet = std::vector<Node*>;
/**
 * @brief Clase principal del programa. En ella se definen los 
 * metodos y atributos necesarios para poder implementar el 
 * algoritmo de busqueda A*.
 */
class AStar { 

    bool detectCollision(Coordinates coordinates_);
    Node* findNodeOnList(NodeSet& nodes_, Coordinates coordinates_);
    void releaseNodes(NodeSet& nodes_); //limpiar memoria

  public:
    bool unrecheable_ = false;
    AStar();
    void setWorldSize(Coordinates worldSize_);
    void setHeuristic(HeuristicFunction heuristic_);
    CoordinateList findPath(Coordinates source_, Coordinates target_);
    void addCollision(Coordinates coordinates_);
    void clearCollisions();
    void debug(); /*Metodo debug*/
    //esto es nuevo
    void sortOpenSet(NodeSet& set);
    void generateResult(NodeSet& openSet, NodeSet& closeSet, Coordinates target_, 
      CoordinateList& path, uint G_final, uint H_final, uint F_final);
    //
  private:
    HeuristicFunction heuristic; /*Heuristica utilizada (Manhattan)*/
    CoordinateList direction, walls; /*direction: direcciones posibles que se pueden tomar 
                                       walls: coordenadas del laberinto donde existe un obstaculo*/
    Coordinates worldSize; /*Dimensiones del laberinto*/
    uint directions; /*Cantidad de direcciones posibles a tomar(habilitado el movimiento diagonal)*/
};
/**
 * @brief Clase Heuristic. Permite definir la heuristica necesaria a utilizar
 * en el algoritmo A*. Por peticion de la practica se ha implementado su uso con
 * manhattan aunque tambien podria haber sido posible con otro tipo de heuristicas
 * como la distancia euclidea u octogonal.
 */
class Heuristic {
  static Coordinates getDelta(Coordinates source_, Coordinates target_);

  public:
    static uint manhattan(Coordinates source_, Coordinates target_);
    static uint euclidean(Coordinates source_, Coordinates target_);
    static uint octogonal(Coordinates source_, Coordinates target_);
};
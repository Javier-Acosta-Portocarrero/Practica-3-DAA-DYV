// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo funciones.h: fichero de declaración.
// Contiene la declaración de las funciones del programa.

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <vector>

/**
  * @brief Función que recibe las dimensiones de un vector
  *        y lo genera, rellenando todas sus componentes
  *        con valores aleatorios.
  * 
  * @param dimension Longitud del vector.
  */
std::vector<float> GenerarVectorAleatorio(size_t dimension);

#endif
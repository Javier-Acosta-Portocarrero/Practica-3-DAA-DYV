// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo funciones.cc: fichero de definición.
// Contiene la definición de las funciones del programa.

#include "funciones.h"

#include <cstdlib>
#include <stdexcept>

std::vector<float> GenerarVectorAleatorio(size_t dimension) {
  if (dimension <= 0) {
    throw std::invalid_argument("El vector a generar debe tener al menos un elemento.");
  } 
  // Generamos el vector con elementos aleatorios.
  std::vector<float> vector_aleatorio(dimension, 0);
  for (size_t i{0}; i < dimension; i++) {
    vector_aleatorio[i] = static_cast<float>(std::rand() % 100);
  }
  return vector_aleatorio;
}
// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo escritor_solucion_vector.cc: fichero de definición.
// Contiene la definición de la clase EscritorSolucionVector.

#include "escritor_solucion_vector.h"
#include <iostream>

void EscritorSolucionVector::Escribir() const {
  std::cout << "[";
  size_t index{0};
  for (; index < solucion_.GetLongitud() - 1; ++index) {
    std::cout << solucion_.GetElemento(index) << ", ";
  }
  if (solucion_.GetLongitud() > 0) {
    std::cout << solucion_.GetElemento(index);
  }
  std::cout << "]";
}                

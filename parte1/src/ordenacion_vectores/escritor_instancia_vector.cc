// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo escritor_instancia_vector.cc: fichero de definición.
// Contiene la definición de la clase EscritorInstanciaVector.

#include "escritor_instancia_vector.h"
#include <iostream>

void EscritorInstanciaVector::Escribir() const {
  std::cout << "[";
  size_t index{0};
  for (; index < instancia_.GetLongitud() - 1; ++index) {
    std::cout << instancia_.GetElemento(index) << ", ";
  }
  if (instancia_.GetLongitud() > 0) {
    std::cout << instancia_.GetElemento(index);
  }
  std::cout << "]";
}                

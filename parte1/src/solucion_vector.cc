// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo solucion_vector.cc: fichero de definicion.
// Contiene la definicion de la clase SolucionVector.

#include "solucion_vector.h"
#include <stdexcept>

SolucionVector::SolucionVector(const InstanciaVector& instancia) {
  for (size_t i{0}; i < instancia.GetLongitud(); ++i) {
    vector_.emplace_back(instancia.GetElemento(i));
  }
}

float SolucionVector::GetElemento(size_t index) const {
  if (index >= vector_.size()) {
    throw std::out_of_range("Index out of range");
  }
  return vector_[index];
}
  
size_t SolucionVector::GetLongitud() const {
  return vector_.size();
}
  
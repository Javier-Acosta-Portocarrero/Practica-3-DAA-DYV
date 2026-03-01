// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo solucion_vector.h: fichero de declaración.
// Contiene la declaración de la clase SolucionSVector.

#ifndef SOLUCION_VECTOR_H_
#define SOLUCION_VECTOR_H_

#include "../lib/algoritmo.h"
#include "instancia_vector.h"
#include <vector>

/**
  * @class SolucionVector
  * @brief Clase que representa una solución de un algoritmo que consiste en un vector 
  *        de decimales.  
  */
class SolucionVector : public Solucion {
 public:
  SolucionVector() = default;
  SolucionVector(const std::vector<float>& vector) : vector_(vector) {}
  SolucionVector(const InstanciaVector& instancia);
  ~SolucionVector() = default;

  float GetElemento(size_t index) const;
  size_t GetLongitud() const;

  void AddElemento(float nuevo_elemento) { vector_.emplace_back(nuevo_elemento);}

 private:
  std::vector<float> vector_;
};


#endif
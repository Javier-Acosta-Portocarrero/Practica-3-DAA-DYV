// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo escritor_solucion_vector.h: fichero de declaración.
// Contiene la declaración de la clase EscritorSolucionVector.

#ifndef ESCRITOR_INSTANCIA_VECTOR_VECTOR_H_
#define ESCRITOR_INSTANCIA_VECTOR_VECTOR_H_

#include "solucion_vector.h"
#include <vector>
#include <string>

class EscritorSolucionVector {
 public:
  EscritorSolucionVector() = default;
  EscritorSolucionVector(SolucionVector solucion) : solucion_{solucion} {}

  void SetSolucion(const SolucionVector& nueva_solucion) { solucion_ = nueva_solucion;}
  void Escribir() const;                

 private:
  SolucionVector solucion_;
};

#endif
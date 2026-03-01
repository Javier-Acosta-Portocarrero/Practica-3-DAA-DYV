// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo escritor_instancia_vector.h: fichero de declaración.
// Contiene la declaración de la clase EscritorInstanciaVector.

#ifndef ESCRITOR_SOLUCION_VECTOR_VECTOR_H_
#define ESCRITOR_SOLUCION_VECTOR_VECTOR_H_

#include "instancia_vector.h"
#include <vector>
#include <string>

class EscritorInstanciaVector {
 public:
  EscritorInstanciaVector() = default;
  EscritorInstanciaVector(InstanciaVector solucion) : instancia_{solucion} {}

  void SetInstancia(const InstanciaVector& nueva_instancia) { instancia_ = nueva_instancia;}
  void Escribir() const;                

 private:
  InstanciaVector instancia_;
};

#endif
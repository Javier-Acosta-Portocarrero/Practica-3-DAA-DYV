// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo merge_sort.h: fichero de declaración.
// Contiene la declaración de la clase MergeSort.

#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "./lib/algoritmo_divide_y_venceras.h"
#include "instancia_vector.h"
#include <vector>

class MergeSort : public AlgoritmoDivideYVenceras {
 public:
  MergeSort() = default;
  ~MergeSort() = default;
  
 protected:
  std::vector<Instancia*> Divide(Instancia* entrada) override;
  Solucion* Combine(std::vector<Solucion*> soluciones) override;
  Solucion* SolveSmall(Instancia* entrada) override;
  bool IsSmall(Instancia* entrada) override;
};

#endif
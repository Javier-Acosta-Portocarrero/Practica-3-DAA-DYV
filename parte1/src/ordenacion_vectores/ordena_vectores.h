// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 08/03/2026
// Archivo ordena_vectores.h: fichero de declaración.
// Contiene la declaración de la clase OrdenaVectores.

#ifndef ORDENA_VECTORES_H_
#define ORDENA_VECTORES_H_

#include "../lib/algoritmo.h"
#include "instancia_vector.h"
#include "solucion_vector.h"
#include <vector>

class OrdenaVectores {
 public:
  OrdenaVectores(Algoritmo* estrategia) : estrategia_ordenacion_(estrategia) {}
  ~OrdenaVectores() { delete estrategia_ordenacion_;}

  void SetEstrategía(Algoritmo* estrategia);
  SolucionVector* Ordenar(InstanciaVector* instancia);
  
 private:
  Algoritmo* estrategia_ordenacion_ = nullptr;
};

#endif
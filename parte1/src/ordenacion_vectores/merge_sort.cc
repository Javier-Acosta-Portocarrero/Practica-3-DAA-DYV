// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo quick_sort.cc: fichero de definición.
// Contiene la definición de la clase MergeSort.

#include "merge_sort.h"
#include "instancia_vector.h"
#include "solucion_vector.h"
#include <vector>

std::vector<Instancia*> MergeSort::Divide(Instancia* entrada) {
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  std::vector<Instancia*> instancias;
  InstanciaVector* instancia_izquierda = new InstanciaVector();
  InstanciaVector* instancia_derecha = new InstanciaVector();

  for (size_t i{0}; i <= (entrada_procesada -> GetLongitud()) / 2; ++i) {
    instancia_izquierda -> AddElemento(entrada_procesada -> GetElemento(i));
  }
  for (size_t i{((entrada_procesada -> GetLongitud()) / 2) + 1}; i < entrada_procesada -> GetLongitud(); ++i) {
    instancia_derecha -> AddElemento(entrada_procesada -> GetElemento(i));
  }

  instancias.emplace_back(instancia_izquierda);
  instancias.emplace_back(instancia_derecha);
  return instancias;
}

Solucion* MergeSort::Combine(std::vector<Solucion*> soluciones) {
  SolucionVector* solucion_izquierda = dynamic_cast<SolucionVector*>(soluciones[0]);
  SolucionVector* segunda_derecha = dynamic_cast<SolucionVector*>(soluciones[1]);
  size_t longitud_solucion_izquierda{solucion_izquierda -> GetLongitud()};
  size_t longitud_solucion_derecha{segunda_derecha -> GetLongitud()};
  size_t primer_iterador{0};
  size_t segundo_iterador{0};
  SolucionVector* solucion_final = new SolucionVector();
  
  while (primer_iterador < longitud_solucion_izquierda && segundo_iterador < longitud_solucion_derecha) {
    float elemento_primera_solucion{solucion_izquierda -> GetElemento(primer_iterador)};
    float elemento_segunda_solucion{segunda_derecha -> GetElemento(segundo_iterador)};
    if (elemento_primera_solucion < elemento_segunda_solucion) {
      solucion_final -> AddElemento(elemento_primera_solucion);
      ++primer_iterador;
    } else {
      solucion_final -> AddElemento(elemento_segunda_solucion);
      ++segundo_iterador;
    }
  }

  if (primer_iterador < longitud_solucion_izquierda) {
    for (size_t i{primer_iterador}; primer_iterador < longitud_solucion_izquierda; ++i) {
      solucion_final -> AddElemento(solucion_izquierda -> GetElemento(i));
    }
  } else {
    for (size_t i{segundo_iterador}; segundo_iterador < longitud_solucion_derecha; ++i) {
      solucion_final -> AddElemento(segunda_derecha -> GetElemento(i));
    }
  }
  
  return solucion_final;
}

Solucion* MergeSort::SolveSmall(Instancia* entrada) {
  Solucion* solucion = new SolucionVector(*dynamic_cast<InstanciaVector*>(entrada));
  return solucion;
}

bool MergeSort::IsSmall(Instancia* entrada) {
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  return (entrada_procesada -> GetLongitud() == 1);
}
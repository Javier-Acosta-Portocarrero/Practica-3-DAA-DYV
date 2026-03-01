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
// Contiene la definición de la clase QuickSort.

#include "quick_sort.h"
#include "instancia_vector.h"
#include "solucion_vector.h"
#include <vector>

#include <iostream>

std::vector<Instancia*> QuickSort::Divide(Instancia* entrada) {
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  std::vector<Instancia*> instancias;
  InstanciaVector* instancia_menor = new InstanciaVector();
  InstanciaVector* instancia_mayor = new InstanciaVector();
  InstanciaVector* instancia_pivote = new InstanciaVector();
  // El último elemento es el pivote.
  float pivote = entrada_procesada -> GetElemento(entrada_procesada -> GetLongitud() - 1);
  instancia_pivote -> AddElemento(pivote);
  // Recorremos todos menos el pivote, dividiendo la instancia en dos, una con los elementos
  // mayores al pivote y otra con los demás, ignorando el pivote.
  for (size_t i{0}; i < (entrada_procesada -> GetLongitud()) - 1; ++i) {
    float elemento_actual = entrada_procesada -> GetElemento(i);
    if (elemento_actual > pivote) {
      instancia_mayor -> AddElemento(elemento_actual);
    } else {
      instancia_menor -> AddElemento(elemento_actual);
    }
  }

  instancias.emplace_back(instancia_menor);
  instancias.emplace_back(instancia_pivote);
  instancias.emplace_back(instancia_mayor);
  return instancias;
}

Solucion* QuickSort::Combine(std::vector<Solucion*> soluciones) {
  SolucionVector* solucion_menor_procesada = dynamic_cast<SolucionVector*>(soluciones[0]);
  SolucionVector* solucion_pivote_procesada = dynamic_cast<SolucionVector*>(soluciones[1]);
  SolucionVector* solucion_mayor_procesada = dynamic_cast<SolucionVector*>(soluciones[2]);
  // Admite pasarle por el constructor una instancia para convertirla en una solución
  SolucionVector* solucion_final = new SolucionVector();
  // Añadimos de forma ordenada los elementos de las soluciones.
  for (size_t i{0}; i < solucion_menor_procesada -> GetLongitud(); ++i) {
    solucion_final -> AddElemento(solucion_menor_procesada -> GetElemento(i));
  }
  for (size_t i{0}; i < solucion_pivote_procesada -> GetLongitud(); ++i) {
    solucion_final -> AddElemento(solucion_pivote_procesada -> GetElemento(i));
  }
  for (size_t i{0}; i < solucion_mayor_procesada -> GetLongitud(); ++i) {
    solucion_final -> AddElemento(solucion_mayor_procesada -> GetElemento(i));
  }
  // Liberamos memoria
  for (size_t i{0}; i < soluciones.size(); ++i) {
    delete soluciones[i];
  }
  return solucion_final;
}

Solucion* QuickSort::SolveSmall(Instancia* entrada) {
  Solucion* solucion = new SolucionVector(*dynamic_cast<InstanciaVector*>(entrada));
  //delete entrada;
  return solucion;
}

bool QuickSort::IsSmall(Instancia* entrada) {
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  return (entrada_procesada -> GetLongitud() <= 1);
}
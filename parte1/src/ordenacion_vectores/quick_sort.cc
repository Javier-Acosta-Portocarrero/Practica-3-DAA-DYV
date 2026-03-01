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
  std::cout << "1\n";
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  float pivote = EncontrarPivote(*entrada_procesada);
  std::vector<Instancia*> instancias;
  InstanciaVector* instancia_menor_igual = new InstanciaVector();
  InstanciaVector* instancia_mayor = new InstanciaVector();
  for (size_t i{0}; i < entrada_procesada -> GetLongitud(); ++i) {
    float elemento_actual = entrada_procesada -> GetElemento(i);
    if (elemento_actual > pivote) {
      instancia_mayor -> AddElemento(elemento_actual);
    } else {
      instancia_menor_igual -> AddElemento(elemento_actual);
    }
  }
  instancias.emplace_back(instancia_menor_igual);
  instancias.emplace_back(instancia_mayor);
  return instancias;
}

Solucion* QuickSort::Combine(std::vector<Solucion*> soluciones) {
  std::cout << "2\n";
  SolucionVector* primera_solucion_procesada = dynamic_cast<SolucionVector*>(soluciones[0]);
  SolucionVector* segunda_solucion_procesada = dynamic_cast<SolucionVector*>(soluciones[1]);
  // Admite pasarle por el constructor una instancia para convertirla en una solución
  SolucionVector* solucion_final = new SolucionVector();

  for (size_t i{0}; i < primera_solucion_procesada -> GetLongitud(); ++i) {
    solucion_final -> AddElemento(primera_solucion_procesada -> GetElemento(i));
  }
  for (size_t i{0}; i < segunda_solucion_procesada -> GetLongitud(); ++i) {
    solucion_final -> AddElemento(segunda_solucion_procesada -> GetElemento(i));
  }

  for (size_t i{0}; i < soluciones.size(); ++i) {
    delete soluciones[i];
  }
  return solucion_final;
}

Solucion* QuickSort::SolveSmall(Instancia* entrada) {
  Solucion* solucion = new SolucionVector(*dynamic_cast<InstanciaVector*>(entrada));
  return solucion;
}

bool QuickSort::IsSmall(Instancia* entrada) {
  InstanciaVector* entrada_procesada = dynamic_cast<InstanciaVector*>(entrada);
  return (entrada_procesada -> GetLongitud() <= 1);
}

float QuickSort::EncontrarPivote(const InstanciaVector& instancia) const {
  if (instancia.GetLongitud() == 0) {
    return 0;
  }
  float mayor_elemento{instancia.GetElemento(0)};
  float menor_elemento{instancia.GetElemento(0)};
  for (size_t i{1}; i < instancia.GetLongitud(); ++i) {
    if (instancia.GetElemento(i) > mayor_elemento) {
      mayor_elemento = instancia.GetElemento(i);
    } else if (instancia.GetElemento(i) < menor_elemento) {
      menor_elemento = instancia.GetElemento(i);    
    }
  }
  return (mayor_elemento + menor_elemento) / 2;
}
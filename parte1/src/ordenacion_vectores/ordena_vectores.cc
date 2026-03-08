// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 08/03/2026
// Archivo ordena_vectores.cc: fichero de definición.
// Contiene la definición de la clase OrdenaVectores.

#include "ordena_vectores.h"
#include <stdexcept>

void OrdenaVectores::SetEstrategía(Algoritmo* estrategia) {
  if (estrategia_ordenacion_ != nullptr) {
    delete estrategia_ordenacion_;
  }
  estrategia_ordenacion_ = estrategia;
}

SolucionVector* OrdenaVectores::Ordenar(InstanciaVector* instancia) {
  SolucionVector* solucion = dynamic_cast<SolucionVector*>(estrategia_ordenacion_->Solve(instancia));
  if (!solucion) {
    throw std::runtime_error("La estrategia elegida no es capaz de resolver la ordenación.");
  }
  return solucion;
}

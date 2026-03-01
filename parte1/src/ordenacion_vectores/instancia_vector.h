// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo instancia_vector.h: fichero de declaración.
// Contiene la declaración de la clase InstanciaVector.

#ifndef INSTANCIA_VECTOR_H_
#define INSTANCIA_VECTOR_H_

#include "../lib/algoritmo.h"
#include <vector>

/**
  * @class InstanciaVector
  * @brief Clase que representa una instancia concreta de un algoritmo que recibe un vector de decimales.  
  */
class InstanciaVector : public Instancia {
 public:
  InstanciaVector() = default;
  InstanciaVector(const std::vector<float>& vector) : vector_(vector) {}
  ~InstanciaVector() = default;

  float GetElemento(size_t index) const;
  size_t GetLongitud() const;

  void AddElemento(float nuevo_elemento) { vector_.emplace_back(nuevo_elemento);}
 
 private:
  std::vector<float> vector_;
};


#endif
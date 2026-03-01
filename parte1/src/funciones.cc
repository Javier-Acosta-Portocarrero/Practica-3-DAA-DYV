#include "funciones.h"

#include <cstdlib>
#include <stdexcept>

std::vector<float> GenerarVectorAleatorio(size_t dimension) {
  if (dimension <= 0) {
    throw std::invalid_argument("El vector a generar debe tener al menos un elemento.");
  } 
  // Generamos el vector con elementos aleatorios.
  std::vector<float> vector_aleatorio(dimension, 0);
  for (size_t i{0}; i < dimension; i++) {
    vector_aleatorio[i] = static_cast<float>(std::rand());
  }
  return vector_aleatorio;
}
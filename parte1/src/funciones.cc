#include "funciones.h"

#include <cstdlib>
#include <stdexcept>

std::vector<std::vector<double>> GenerarMatrizAleatoria(size_t filas, size_t columnas) {
  if (filas <= 0 || columnas <= 0) {
    throw std::invalid_argument("La matriz a generar debe tener al menos una fila y una columna");
  } 
  // Generamos la matriz con valores aleatorios
  std::vector<std::vector<double>> matriz_aleatoria(filas, std::vector<double>(columnas, 0.0));
  for (size_t i{0}; i < filas; i++) {
    for (size_t j{0}; j < columnas; j++) {
      matriz_aleatoria[i][j] = static_cast<double>(std::rand());
    }
  }
  return matriz_aleatoria;
}
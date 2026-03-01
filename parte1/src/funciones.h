#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <vector>

/**
  * @brief Función que recibe las dimensiones de una matriz
  *        y la genera, rellenando todas sus componentes
  *        con valores aleatorios.
  * 
  * @param filas Cantidad de filas de la matriz.
  * @param columnas Cantidad de columnas de la matriz. 
  */
std::vector<std::vector<double>> GenerarMatrizAleatoria(size_t filas, size_t columnas);

#endif
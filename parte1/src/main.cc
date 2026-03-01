#include "funciones.h"
#include "lib/algoritmo.h"
#include "matrices/instancia_mult_matriz.h"
#include "matrices/solucion_mult_matriz.h"
#include "matrices/multiplicacion_columna.h"
#include "matrices/multiplicacion_fila.h"
#include "matrices/operacion_matriz.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

int main() {
  // Inicializamos la semilla con la hora actual del ordenador
  std::srand(time(0));
  // Usamos el contexto de operación de matrices que utiliza los diferentes algoritmos
  OperacionMatriz multiplicacion_matrices{new MutiplicacionMatricesFila()};
  Instancia* entrada_aux = nullptr;
  Solucion* solucion_aux = nullptr;
  // Pruebas
  std::vector<size_t> dimensiones{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 
                                  300, 400, 500, 600 ,700, 800, 900, 1000};
  std::cout << "Dimensiones A    Dimensiones B     Tiempo A*B por filas    Tiempo A*B por columnas\n";
  // Bucle para cada dimensión a probar
  for (size_t dimension : dimensiones) {
    entrada_aux = new InstanciaMultMatrices(GenerarMatrizAleatoria(dimension, dimension), 
                                            GenerarMatrizAleatoria(dimension, dimension));
    double duracion_total_fila{0.0};
    double duracion_total_col{0.0};
    int num_iteraciones{5};
    // Calculo del tiempo total de las num_iteraciones ejecuciones para cada 
    // algoritmo para posteriormente calcular la media y tener unos resultados más estables
    for (int i{0}; i < num_iteraciones; i ++) {
      // Tiempo de ejecución del algoritmo por filas
      auto inicio = std::chrono::high_resolution_clock::now();
      solucion_aux = multiplicacion_matrices.EjecutarOperacion(entrada_aux);
      auto fin = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duracion_fila = fin - inicio;
      duracion_total_fila += duracion_fila.count();

      // Libreamos memoria antes de relocalizar el puntero
      delete solucion_aux;

      // Cambiamos la estrategia del contexto a multiplicación por columnas
      multiplicacion_matrices.SetOperacion(new MutiplicacionMatricesColumna());
      // Tiempo de ejecución del algoritmo por columnas
      auto inicio2 = std::chrono::high_resolution_clock::now();
      solucion_aux = multiplicacion_matrices.EjecutarOperacion(entrada_aux);
      auto fin2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duracion_col = fin2 - inicio2;
      duracion_total_col += duracion_col.count();
      
      // Liberamos memoria de nuevo
      delete solucion_aux;
      // Volvemos a cambiar la estrategia del contexto a multiplicación por filas
      multiplicacion_matrices.SetOperacion(new MutiplicacionMatricesFila());
    }
    // Imprimir resultados para estas dimensiones, promediando los tiempos obtenidos
    std::cout << "  " << dimension << 'x' << dimension << "           "  
              << dimension << 'x' << dimension << "                 " 
              << duracion_total_fila / num_iteraciones << "                " 
              << duracion_total_col / num_iteraciones << '\n';
    // Liberamos la memoria
    delete entrada_aux;
  }
  return 0;
}
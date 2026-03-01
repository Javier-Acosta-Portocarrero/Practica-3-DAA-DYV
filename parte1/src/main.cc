// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 28/02/2024
// Archivo main.cc: fichero con la función principal del programa.
// Se encarga de usar las clases de la librería de algoritmos de ordenación 
// implementada para experimentar con tiempos de ejecución o simplemente
// ordenar vectores eligiendo la dimensión de los mismos.

#include "funciones.h"
#include "lib/algoritmo.h"
#include "ordenacion_vectores/escritor_solucion_vector.h"
#include "ordenacion_vectores/escritor_instancia_vector.h"
#include "ordenacion_vectores/instancia_vector.h"
#include "ordenacion_vectores/merge_sort.h"
#include "ordenacion_vectores/quick_sort.h"
#include "ordenacion_vectores/solucion_vector.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

int main() {
  // Inicializamos la semilla con la hora actual del ordenador
  std::srand(time(0));
  // Usamos el contexto de ordenación de vector que utiliza los diferentes algoritmos
  AlgoritmoDivideYVenceras* ordenacion_vectores = nullptr;
  Instancia* entrada_aux = nullptr;
  Solucion* solucion_aux = nullptr;

  std::cout << "Elija modo de ejecución, normal (1) o debug (2): ";
  unsigned opcion{0};
  std::cin >> opcion;

  std::cout << "\nElija algoritmo de ordenación, MergeSort (1) o QuickSort (2): ";
  unsigned opcion_algoritmo{0};
  std::cin >> opcion_algoritmo;
  std::string nombre_algoritmo{"default"};
  if (opcion_algoritmo == 1) {
    ordenacion_vectores = new MergeSort();
    nombre_algoritmo = "MergeSort";
  } else if (opcion_algoritmo == 2) {
    ordenacion_vectores = new QuickSort();
    nombre_algoritmo = "QuickSort";
  } else {
    std::cerr << "Algoritmo no válido, abortando ejecución.";
    return 1;
  }

  if (opcion == 1) {
    // Pruebas
    std::vector<size_t> dimensiones{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 
                                    300, 400, 500, 600 ,700, 800, 900, 1000};
    std::cout << "Dimension     Tiempo " << nombre_algoritmo << "\n";
    // Bucle para cada dimensión a probar.
    for (size_t dimension : dimensiones) {
      entrada_aux = new InstanciaVector(GenerarVectorAleatorio(dimension));
      double duracion_total_algoritmo{0.0};
      int num_iteraciones{5};
      // Calculo del tiempo total de las num_iteraciones ejecuciones para posteriormente calcular 
      // la media y tener unos resultados más estables.
      for (int i{0}; i < num_iteraciones; i ++) {
        // Tiempo de ejecución del algoritmo.
        auto inicio = std::chrono::high_resolution_clock::now();
        solucion_aux = ordenacion_vectores -> Solve(entrada_aux);
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duracion_algoritmo = fin - inicio;
        duracion_total_algoritmo += duracion_algoritmo.count();

        // Liberamos memoria
        delete solucion_aux;
      }
      // Imprimir resultados para estas dimensiones, promediando los tiempos obtenidos
      std::cout << "  " << dimension <<  "           "   << duracion_total_algoritmo / num_iteraciones << '\n';
      
      // Liberamos la memoria de nuevo
      delete entrada_aux;
    } 
  } else if (opcion == 2) {
    std::cout << "\nIntroduzca la dimensión de la instancia: ";
    size_t dimension{0};
    std::cin >> dimension;
    entrada_aux = new InstanciaVector(GenerarVectorAleatorio(dimension));
    std::cout << "\nInstancia generada: ";
    EscritorInstanciaVector imprime_instancias(*dynamic_cast<InstanciaVector*>(entrada_aux)); 
    imprime_instancias.Escribir();

    std::cout << "\n\nSolución obtenida con " << nombre_algoritmo << ":\n";
    solucion_aux = ordenacion_vectores -> Solve(entrada_aux);
    EscritorSolucionVector imprime_soluciones(*dynamic_cast<SolucionVector*>(solucion_aux));
    imprime_soluciones.Escribir();
    std::cout << std::endl;
    // Liberamos memoria
    delete entrada_aux;
    delete solucion_aux;
  } else {
    std::cerr << "Opción no válida, abortando ejecución.";
    return 1;
  }
  return 0;
}
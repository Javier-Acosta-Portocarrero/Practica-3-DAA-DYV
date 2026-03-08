// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 2: Máquina RAM
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo algoritmo_voraz_planificacion_dia.cc: fichero de definicion.
// Contiene la definicion de la clase AlgoritmoVorazPlanificacionDia.


#include "../lib/algoritmo.h"
#include "algoritmo_voraz_planificacion_dia.h"

#include <limits>
#include <stdexcept>
#include <iostream>

Solucion* AlgoritmoVorazPlanificacionDia::Solve(Instancia* entrada) {
  //std::cout << "Resolviendo\n";
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  if (entrada_procesada->GetCantidadDias() > 1) {
    throw std::logic_error("Este algoritmo solo se puede usar para instancias de tamaño 1.");
  }
  //std::cout << "Resolviendo: " << entrada_procesada->GetCantidadDias() << std::endl;
  SolucionPlanificacionEmpleados* solucion_dia = new SolucionPlanificacionEmpleados(*entrada_procesada);
  size_t cantidad_empleados = solucion_dia->GetCantidadEmpleados();
  size_t cantidad_turnos = solucion_dia->GetCantidadTurnos();
  //std::cout << "empleados: " << cantidad_empleados << " " << "turnos: " << cantidad_turnos << std::endl;

  // Primera pasada para cubrir empleados mínimos por turno.
  for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
    //std::cout << "a";
    const unsigned minimo_empleados{solucion_dia->GetMinimoEmpleados(0, turno)};
    while (solucion_dia->EmpleadosTurno(0, turno) < minimo_empleados) {
      // 0 porque solo hay un día, por lo que es el primero.
      //std::cout << "3";
      int mejor_empleado_disponible{EncontrarMejorEmpleadoDisponible(solucion_dia, 0, turno)};
      // Si no había ningún empleado dispobile, el método devolvería -1.
      if (mejor_empleado_disponible == -1) {
        break;
      }
      solucion_dia->NuevoTrabajoTurno(0, turno, static_cast<size_t>(mejor_empleado_disponible));
      //std::cout << "2";
    }
  }
  // Ahora simplemente asignamos los empleados sobrantes maximizando la satisfacción.
  for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
    //std::cout << "b";
    while (true) {
      //std::cout << "4";
      int mejor_empleado_disponible = EncontrarMejorEmpleadoDisponible(solucion_dia, 0, turno);
      if (mejor_empleado_disponible == -1) {
        break;
      }
      // Si la satisfacción es negativa no compensa asignarlo
      if (solucion_dia->GetSatisfaccion(mejor_empleado_disponible, 0, turno) <= 0) {
        break;
      }
      solucion_dia->NuevoTrabajoTurno(0, turno, static_cast<size_t>(mejor_empleado_disponible));
      //std::cout << "1";
    }
  }
  return solucion_dia;  
}

int AlgoritmoVorazPlanificacionDia::EncontrarMejorEmpleadoDisponible(SolucionPlanificacionEmpleados* solucion, 
                                                                          size_t dia, 
                                                                          size_t turno) {
  int satisfaccion_mejor_empleado_disponible{std::numeric_limits<int>::min()};
  // Si se devuelve -1 es que no hay ningún empleado disponible.
  int mejor_empleado_disponible{-1};
  size_t cantidad_empleados = solucion->GetCantidadEmpleados();
  // Se busca el empleado disponible con mayor satisfacción para ese turno y día.
  for (size_t empleado{0}; empleado < cantidad_empleados; ++empleado) {
    if (!solucion->TrabajaEmpleadoDia(empleado, dia) && 
        solucion->GetSatisfaccion(empleado, dia, turno) > satisfaccion_mejor_empleado_disponible) {
      satisfaccion_mejor_empleado_disponible = solucion->GetSatisfaccion(empleado, dia, turno);
      mejor_empleado_disponible = empleado;
    } 
  }
  std::cout << "Mejor: " << mejor_empleado_disponible << std::endl;
  return mejor_empleado_disponible;
}

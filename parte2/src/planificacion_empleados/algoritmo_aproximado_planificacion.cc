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
// Contiene la definición de la clase AlgoritmoAproximadoPlanificacion.

#include "algoritmo_aproximado_planificacion.h"
#include "solucion_planificacion_empleados.h"

#include <iostream>
#include <limits>

std::vector<Instancia*> AlgoritmoAproximadoPlanificacion::Divide(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  const size_t cantidad_turnos = entrada_procesada->GetCantidadTurnos();
  const size_t cantidad_empleados = entrada_procesada->GetCantidadEmpleados();
  // Primero completamos toda la información de la parte izquierda de la planificación
  const unsigned dias_izquierda{entrada_procesada->GetCantidadDias() / 2};
  std::vector<std::vector<std::vector<int>>> satisfaccion_izq(
      cantidad_empleados,
      std::vector<std::vector<int>>(
          dias_izquierda,
          std::vector<int>(cantidad_turnos, 0)));
    
  std::vector<std::vector<unsigned>> min_empleados_izq(dias_izquierda, std::vector<unsigned>(cantidad_turnos, 0));
  
  for (size_t dia{0}; dia < dias_izquierda; ++dia) {
    for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
      min_empleados_izq[dia][turno] = entrada_procesada->GetMinimoEmpleados(dia, turno);
    }
  }
  for (size_t empleado{0}; empleado < cantidad_empleados; ++empleado) {
    for (size_t dia{0}; dia < dias_izquierda; ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
        satisfaccion_izq[empleado][dia][turno] = entrada_procesada->GetSatisfaccion(empleado, dia, turno);
      }
    }
  }
  // Después completamos toda la información de la parte derecha de la planificación.
  const unsigned dias_derecha{entrada_procesada->GetCantidadDias() - dias_izquierda};
  std::vector<std::vector<std::vector<int>>> satisfaccion_dcha(
      cantidad_empleados,
      std::vector<std::vector<int>>(
          dias_derecha,
          std::vector<int>(cantidad_turnos, 0)));

  std::vector<std::vector<unsigned>> min_empleados_dcha(dias_derecha, std::vector<unsigned>(cantidad_turnos, 0));
  // Es importante destacar que al acceder a la parte derecha, debemos ajustar el índice del 
  // día para reflejar su posición real en la planificación completa.
  for (size_t dia{0}; dia < dias_derecha; ++dia) {
    for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
      const unsigned dia_real = dias_izquierda + dia;
      min_empleados_dcha[dia][turno] = entrada_procesada->GetMinimoEmpleados(dia_real, turno);
    }
  }
  for (size_t empleado{0}; empleado < cantidad_empleados; ++empleado) {
    for (size_t dia{0}; dia < dias_derecha; ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos; ++turno) {
        const unsigned dia_real = dias_izquierda + dia;
        satisfaccion_dcha[empleado][dia][turno] = entrada_procesada->GetSatisfaccion(empleado, dia_real, turno);
      }
    }
  }
  // Finalmente, creamos las dos instancias con la información que hemos recopilado, las 
  // partes comunes, como los nombres de empleados, turnos y descansos, se pasan a ambas instancias.
  const std::vector<std::string>& nombres_empleados = entrada_procesada->GetNombresEmpleados();
  const std::vector<std::string>& nombres_turnos = entrada_procesada->GetNombresTurnos();
  const std::vector<unsigned>& descansos = entrada_procesada->GetDescansoEmpleados();
  InstanciaPlanificacionEmpleados* primera_instancia = new InstanciaPlanificacionEmpleados(
      nombres_empleados,
      nombres_turnos, 
      dias_izquierda,
      satisfaccion_izq,
      min_empleados_izq,
      descansos);
  InstanciaPlanificacionEmpleados* segunda_instancia = new InstanciaPlanificacionEmpleados(
      nombres_empleados,
      nombres_turnos, 
      dias_derecha,
      satisfaccion_dcha,
      min_empleados_dcha,
      descansos);
  // Devolvemos las dos instancias resultantes de la división.
  std::vector<Instancia*> instancias;
  instancias.emplace_back(primera_instancia);
  instancias.emplace_back(segunda_instancia);
  return instancias;
}

Solucion* AlgoritmoAproximadoPlanificacion::Combine(std::vector<Solucion*> soluciones) {
  SolucionPlanificacionEmpleados* solucion_izq = dynamic_cast<SolucionPlanificacionEmpleados*>(soluciones[0]);
  SolucionPlanificacionEmpleados* solucion_dcha = dynamic_cast<SolucionPlanificacionEmpleados*>(soluciones[1]);
  // Inicializamos los componentes de la solución, teniendo en cuenta que la cantidad de días es la suma de 
  // las partes izquierda y derecha, mientras que la cantidad de empleados y turnos se mantiene igual.
  const unsigned cantidad_dias_fusion{solucion_izq->GetCantidadDias() + solucion_dcha->GetCantidadDias()};
  const size_t cantidad_empleados_fusion{solucion_izq->GetCantidadEmpleados()};
  const size_t cantidad_turnos_fusion{solucion_izq->GetCantidadTurnos()};
  std::vector<std::vector<std::vector<int>>> satisfaccion_fusion(
      cantidad_empleados_fusion,
      std::vector<std::vector<int>>(
          cantidad_dias_fusion,
          std::vector<int>(cantidad_turnos_fusion, 0)));
  
  std::vector<std::vector<std::vector<bool>>> trabajados_fusion(
      cantidad_empleados_fusion,
      std::vector<std::vector<bool>>(
          cantidad_dias_fusion,
          std::vector<bool>(cantidad_turnos_fusion, false)));

  std::vector<std::vector<unsigned>> min_empleados_fusion(
      cantidad_dias_fusion, 
      std::vector<unsigned>(cantidad_turnos_fusion, 0));

  // Ahora asignamos los valores correspondientes a cada parte de la planificación, 
  // teniendo cuidado de ajustar los índices de los días para la parte derecha.
  std::vector<unsigned> dias_trabajados_empleado_fusion(cantidad_empleados_fusion, 0);
  size_t dias_izq = solucion_izq->GetCantidadDias();
  // Comenzamos por asignar los mínimos de empleados.
  for (size_t dia{0}; dia < cantidad_dias_fusion; ++dia) {
    for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
      if (dia < dias_izq) {
        min_empleados_fusion[dia][turno] = solucion_izq->GetMinimoEmpleados(dia, turno);
      } else {
        const unsigned dia_real = dia - dias_izq;
        min_empleados_fusion[dia][turno] = solucion_dcha->GetMinimoEmpleados(dia_real, turno);
      }
    }
  }
  // Después asignamos las satisfacciones y los turnos trabajados.
  for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
    for (size_t dia{0}; dia < cantidad_dias_fusion; ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
        if (dia < dias_izq) {
          satisfaccion_fusion[empleado][dia][turno] = solucion_izq->GetSatisfaccion(empleado, dia, turno);
          if (solucion_izq->TrabajaEmpleadoDiaTurno(empleado, dia, turno)) {
            trabajados_fusion[empleado][dia][turno] = true;
            ++dias_trabajados_empleado_fusion[empleado];
          }
        } else {
          const unsigned dia_real = dia - dias_izq;
          satisfaccion_fusion[empleado][dia][turno] = solucion_dcha->GetSatisfaccion(empleado, dia_real, turno);
          if (solucion_dcha->TrabajaEmpleadoDiaTurno(empleado, dia_real, turno)) {
            trabajados_fusion[empleado][dia][turno] = true;
            ++dias_trabajados_empleado_fusion[empleado];
          }
        } 
      }
    }
  }
  // Creamos la solución resulatnte con los componentes calculados.
  SolucionPlanificacionEmpleados* solucion_fusionada = new SolucionPlanificacionEmpleados(
      solucion_izq->GetNombresEmpleados(),
      trabajados_fusion,
      dias_trabajados_empleado_fusion,
      solucion_izq->GetNombresTurnos(),
      cantidad_dias_fusion,
      satisfaccion_fusion,
      min_empleados_fusion,
      solucion_izq->GetDescansosEmpleados());
  // Restauramos las reestricciones globales, que son los días mínimos de descanso de cada empleado.
  for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
    unsigned cantidad_dias_descanso = cantidad_dias_fusion - solucion_fusionada->DiasTrabajadosEmpleado(empleado);
    unsigned dias_minimos = solucion_fusionada->DiasMinimosDescansoEmpleado(empleado);
    while (cantidad_dias_descanso < dias_minimos) {
      // Eliminamos el día con peor satisfacción del empleado, esto no es tan bueno
      // porque podemos romper la cantidad mínima de empleados por turno.
      std::pair<unsigned, unsigned> peor_turno_empleado = EncontrarPeorDiaTrabajado(empleado, solucion_fusionada);
      solucion_fusionada->LiberarTrabajoTurno(peor_turno_empleado.first, peor_turno_empleado.second, empleado);
      std::cout << "Desansados: " << cantidad_dias_descanso << "  Minimos: " << dias_minimos << std::endl;
      std::cout << peor_turno_empleado.first << " " << peor_turno_empleado.second << " " << empleado << "\n";
      ++cantidad_dias_descanso;
    }
  }

  // Liberamos memoria
  for (size_t i{0}; i < soluciones.size(); ++i) {
    delete soluciones[i];
  }
  return solucion_fusionada;
}

std::pair<unsigned, unsigned> AlgoritmoAproximadoPlanificacion::EncontrarPeorDiaTrabajado(unsigned empleado, 
                                                                     SolucionPlanificacionEmpleados* solucion) {
  // Se podria hacer que devolviera un vector con los dias-turno ordenados de peor a mejor,
  // de esta forma se podria priorizar quitar los peores días que sí que tengan la cantidad
  // mínima de empleados, pero complicaría el combine.
  std::pair<unsigned, unsigned> peor_dia_turno{0, 0};
  float peor_satisfaccion{std::numeric_limits<float>::infinity()};

  for (size_t dia{0}; dia < solucion->GetCantidadDias(); ++dia) {
    for (size_t turno{0}; turno < solucion->GetCantidadTurnos(); ++turno) {
      if (solucion->TrabajaEmpleadoDiaTurno(empleado, dia, turno)) {
        if (solucion->GetSatisfaccion(empleado, dia, turno) < peor_satisfaccion) {
          peor_satisfaccion = solucion->GetSatisfaccion(empleado, dia, turno);
          peor_dia_turno = std::pair<unsigned, unsigned>(dia, turno);
        }
        // No puede trabajar más de un turno en un día así que no tiene sentido seguir buscando aquí.
        break;
      }
    }
  }
  return peor_dia_turno;
}

Solucion* AlgoritmoAproximadoPlanificacion::SolveSmall(Instancia* entrada) {
  Solucion* solucion = algoritmo_small_->Solve(entrada);
  return solucion;
}

bool AlgoritmoAproximadoPlanificacion::IsSmall(Instancia* entrada) {
  InstanciaPlanificacionEmpleados* entrada_procesada = dynamic_cast<InstanciaPlanificacionEmpleados*>(entrada);
  // Lo consideramos pequeño cuando la cantidad de días es 1 o menos,
  return (entrada_procesada->GetCantidadDias() <= 1);
}
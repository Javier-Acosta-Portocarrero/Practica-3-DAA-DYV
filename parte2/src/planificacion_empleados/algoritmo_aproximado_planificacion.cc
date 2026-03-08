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

  const unsigned dias_izquierda{entrada_procesada->GetCantidadDias() / 2};
  std::vector<std::vector<std::vector<int>>> satisfaccion_izq(
      entrada_procesada->GetCantidadEmpleados(),
      std::vector<std::vector<int>>(
          dias_izquierda,
          std::vector<int>(entrada_procesada->GetCantidadTurnos(), 0)));
    
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
  const unsigned dias_derecha{entrada_procesada->GetCantidadDias() - dias_izquierda};
  std::vector<std::vector<std::vector<int>>> satisfaccion_dcha(
      entrada_procesada->GetCantidadEmpleados(),
      std::vector<std::vector<int>>(
          dias_derecha,
          std::vector<int>(entrada_procesada->GetCantidadTurnos(), 0)));

  std::vector<std::vector<unsigned>> min_empleados_dcha(dias_derecha, std::vector<unsigned>(cantidad_turnos, 0));
  
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
  const std::vector<std::string>& nombres_empleados = entrada_procesada->GetNombresEmpleados();
  const std::vector<std::string>& nombres_turnos = entrada_procesada->GetNombresTurnos();
  const std::vector<unsigned>& descansos = entrada_procesada->GetDescansoEmpleados();
  InstanciaPlanificacionEmpleados* primera_instancia = new InstanciaPlanificacionEmpleados(nombres_empleados,
      nombres_turnos, 
      dias_izquierda,
      satisfaccion_izq,
      min_empleados_izq,
      descansos);
  InstanciaPlanificacionEmpleados* segunda_instancia = new InstanciaPlanificacionEmpleados(nombres_empleados,
      nombres_turnos, 
      dias_derecha,
      satisfaccion_dcha,
      min_empleados_dcha,
      descansos);
      
  std::vector<Instancia*> instancias;
  instancias.emplace_back(primera_instancia);
  instancias.emplace_back(segunda_instancia);
  return instancias;
}

Solucion* AlgoritmoAproximadoPlanificacion::Combine(std::vector<Solucion*> soluciones) {
  SolucionPlanificacionEmpleados* solucion_izq = dynamic_cast<SolucionPlanificacionEmpleados*>(soluciones[0]);
  SolucionPlanificacionEmpleados* solucion_dcha = dynamic_cast<SolucionPlanificacionEmpleados*>(soluciones[1]);
  
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

  std::vector<unsigned> dias_trabajados_empleado_fusion(cantidad_empleados_fusion, 0);

  for (size_t dia{0}; dia < cantidad_dias_fusion; ++dia) {
    for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
      if (dia < cantidad_dias_fusion / 2) {
        min_empleados_fusion[dia][turno] = solucion_izq->GetMinimoEmpleados(dia, turno);
      } else {
        const unsigned dia_real = dia - cantidad_dias_fusion / 2;
        min_empleados_fusion[dia][turno] = solucion_dcha->GetMinimoEmpleados(dia_real, turno);
      }
    }
  }
  for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
    for (size_t dia{0}; dia < cantidad_dias_fusion; ++dia) {
      for (size_t turno{0}; turno < cantidad_turnos_fusion; ++turno) {
        if (dia < cantidad_dias_fusion / 2) {
          satisfaccion_fusion[empleado][dia][turno] = solucion_izq->GetSatisfaccion(empleado, dia, turno);
          if (solucion_izq->TrabajaEmpleadoDiaTurno(empleado, dia, turno)) {
            trabajados_fusion[empleado][dia][turno] = true;
            ++dias_trabajados_empleado_fusion[empleado];
          }
        } else {
          const unsigned dia_real = dia - cantidad_dias_fusion / 2;
          satisfaccion_fusion[empleado][dia][turno] = solucion_dcha->GetSatisfaccion(empleado, dia_real, turno);
          if (solucion_dcha->TrabajaEmpleadoDiaTurno(empleado, dia_real, turno)) {
            trabajados_fusion[empleado][dia][turno] = true;
            ++dias_trabajados_empleado_fusion[empleado];
          }
        } 
      }
    }
  }
   
  SolucionPlanificacionEmpleados* solucion_fusionada = new SolucionPlanificacionEmpleados(
      solucion_izq->GetNombresEmpleados(),
      trabajados_fusion,
      dias_trabajados_empleado_fusion,
      solucion_izq->GetNombresTurnos(),
      cantidad_dias_fusion,
      satisfaccion_fusion,
      min_empleados_fusion,
      solucion_izq->GetDescansosEmpleados());
  
  for (size_t empleado{0}; empleado < cantidad_empleados_fusion; ++empleado) {
    unsigned cantidad_dias_descanso = cantidad_dias_fusion - solucion_fusionada->DiasTrabajadosEmpleado(empleado);
    while (cantidad_dias_descanso > solucion_fusionada->DiasMinimosDescansoEmpleado(empleado)) {
      std::pair<unsigned, unsigned> peor_turno_empleado = EncontrarPeorDiaTrabajado(empleado, solucion_fusionada);
      solucion_fusionada->LiberarTrabajoTurno(peor_turno_empleado.first, peor_turno_empleado.second, empleado);
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
  return (entrada_procesada->GetCantidadDias() <= 1);
}
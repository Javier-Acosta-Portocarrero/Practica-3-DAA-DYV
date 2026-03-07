// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2024
// Archivo solucion-planificacion-empleados.h: fichero de declaración.
// Contiene la declaración de la clase SolucionPlanificacionEmpleados.

#ifndef SOLUCION_PLANIFICACION_EMPLEADOS_H_
#define SOLUCION_PLANIFICACION_EMPLEADOS_H_

#include "../lib/algoritmo.h"
#include "instancia_planificacion_empleados.h"
#include <vector>
#include <string>

class SolucionPlanificacionEmpleados: public Solucion {
 public:
  SolucionPlanificacionEmpleados(const InstanciaPlanificaciónEmpleados& instancia_base);
  SolucionPlanificacionEmpleados(const std::vector<std::string>& empleados,
                            const std::vector<std::vector<std::vector<bool>>>& trabaja_empleado_dia_turno,
                            const std::vector<unsigned>& dias_trabajados_empleado,
                            const std::vector<std::string>& turnos_,
                            unsigned dias_a_planificar, const std::vector<std::vector<std::vector<int>>>& satisfaccion,
                            const std::vector<std::vector<unsigned>>& minimo_empleados, 
                            const std::vector<unsigned>& descansos);
  ~SolucionPlanificacionEmpleados() = default;

  inline const std::vector<std::string>& GetNombresEmpleados() const { return empleados_;}
  inline const std::vector<std::string>& GetNombresTurnos() const { return turnos_;}
  inline unsigned GetCantidadDias() const { return dias_a_planificar_;}
  inline size_t GetCantidadTurnos() const { return turnos_.size();} 
  inline size_t GetCantidadEmpleados() const { return empleados_.size();}
  inline int GetSatisfaccion(size_t empleado, size_t dia, size_t turno) const;
  inline unsigned GetMinimoEmpleados(size_t dia, size_t turno) const;

  inline bool TrabajaEmpleadoDia(size_t empleado, size_t dia) const;
  inline unsigned DiasTrabajadosEmpleado(size_t empleado) const;
  unsigned EmpleadosTurno(size_t dia, size_t turno) const;

  void NuevoTrabajoTurno(size_t dia, size_t turno, size_t empleado);

  float GetValorObjetivo() const;

 private:
  std::vector<std::vector<std::vector<bool>>> trabaja_empleado_dia_turno_;
  std::vector<unsigned> dias_trabajados_empleado_;

  std::vector<std::string> empleados_;
  std::vector<std::string> turnos_;
  unsigned dias_a_planificar_ = 0;
  std::vector<std::vector<std::vector<int>>> satisfaccion_por_empleado_dia_turno_;
  std::vector<std::vector<unsigned>> minimo_empleados_por_dia_turno;
  std::vector<unsigned> descanso_minimo_empleado;
};

#endif
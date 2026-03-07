// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica 3: Divide y Vencerás
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2024
// Archivo instancia-planificacion-empleados.h: fichero de declaración.
// Contiene la declaración de la clase InstanciaPlanificacionEmpleados.

#ifndef INSTANCIA_PLANIFICACION_EMPLEADOS_H_
#define INSTANCIA_PLANIFICACION_EMPLEADOS_H_

#include "../lib/algoritmo.h"
#include <vector>
#include <string>

class InstanciaPlanificaciónEmpleados: public Instancia {
 public:
  InstanciaPlanificaciónEmpleados(const std::vector<std::string>& empleados, const std::vector<std::string>& turnos_,
                                  unsigned dias_a_planificar, 
                                  const std::vector<std::vector<std::vector<int>>>& satisfaccion,
                                  const std::vector<std::vector<unsigned>>& minimo_empleados, 
                                  const std::vector<unsigned>& descansos);
  ~InstanciaPlanificaciónEmpleados() = default;

  inline const std::vector<std::string>& GetNombresEmpleados() const { return empleados_;}
  inline const std::vector<std::string>& GetNombresTurnos() const { return turnos_;}
  inline const std::vector<unsigned>& GetDescansoEmpleados() const { return descanso_minimo_empleado;}
  inline unsigned GetCantidadDias() const { return dias_a_planificar_;}
  inline size_t GetCantidadTurnos() const { return turnos_.size();}
  inline size_t GetCantidadEmpleados() const { return empleados_.size();}
  inline int GetSatisfaccion(size_t empleado, size_t dia, size_t turno) const;
  inline unsigned GetMinimoEmpleados(size_t dia, size_t turno) const;

 private:
  std::vector<std::string> empleados_;
  std::vector<std::string> turnos_;
  unsigned dias_a_planificar_ = 0;
  std::vector<std::vector<std::vector<int>>> satisfaccion_por_empleado_dia_turno_;
  std::vector<std::vector<unsigned>> minimo_empleados_por_dia_turno;
  std::vector<unsigned> descanso_minimo_empleado;
};

#endif
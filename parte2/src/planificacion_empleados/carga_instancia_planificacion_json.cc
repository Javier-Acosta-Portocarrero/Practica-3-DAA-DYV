// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Diseño y Analisis de Algoritmos
// Curso: 3º
// Practica: Planificación de empleados
// Autor: Javier Acosta Portocarrero
// Autor: Gabriel Gallardo Noda
// Fecha: 07/03/2026
// Archivo carga_instancia_planificacion_json.cc

#include "carga_instancia_planificacion_json.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

void DebugNumber(const std::string& label,const std::string& value){
  std::cout<<"[DEBUG] "<<label<<" = '"<<value<<"'"<<std::endl;
}

std::string CargaInstanciaPlanificacionJson::ReadFile(){
  std::ifstream file(json_path_);
  if(!file.is_open()){
    throw std::runtime_error("Error abriendo fichero JSON");
  }
  std::stringstream buffer;
  buffer<<file.rdbuf();
  return buffer.str();
}

std::vector<unsigned> CargaInstanciaPlanificacionJson::ParseEmployeeFreeDays(const std::string& data){
  std::vector<unsigned> free_days;
  size_t pos=data.find("\"employees\"");
  pos=data.find("[",pos);

  while(true){
    size_t free_pos=data.find("\"freeDays\"",pos);
    if(free_pos==std::string::npos){
      break;
    }

    size_t colon=data.find(":",free_pos);
    size_t end=data.find_first_of(",}",colon);

    std::string value_str=data.substr(colon+1,end-colon-1);
    DebugNumber("freeDays",value_str);

    unsigned value=std::stoi(value_str);
    free_days.push_back(value);

    pos=end;
  }

  return free_days;
}

void CargaInstanciaPlanificacionJson::ParseSatisfaction(
  const std::string& data,
  std::vector<std::vector<std::vector<int>>>& satisfaccion) {

  //size_t pos = data.find("\"satisfaction\"");
  //if (pos == std::string::npos) return;

  //pos = data.find("[", pos);
  //if (pos == std::string::npos) return;

  size_t start = data.find("\"satisfaction\"");
  size_t array_start = data.find("[", start);
  size_t array_end = data.find("]", array_start); // <-- Fin del array
  size_t pos = array_start + 1;

  while (pos < array_end) {
      // Buscar próximo objeto
      size_t obj_start = data.find("{", pos);
      if (obj_start == std::string::npos) break;

      size_t obj_end = data.find("}", obj_start);
      if (obj_end == std::string::npos) break;

      // Extraer shift
      size_t shift_pos = data.find("\"shift\"", obj_start);
      size_t colon = data.find(":", shift_pos);
      size_t comma = data.find_first_of(",}", colon);
      int t = std::stoi(data.substr(colon + 1, comma - colon - 1));
      DebugNumber("shift", std::to_string(t));

      // Extraer employee
      size_t employee_pos = data.find("\"employee\"", obj_start);
      colon = data.find(":", employee_pos);
      comma = data.find_first_of(",}", colon);
      int e = std::stoi(data.substr(colon + 1, comma - colon - 1));
      DebugNumber("employee", std::to_string(e));

      // Extraer day
      size_t day_pos = data.find("\"day\"", obj_start);
      colon = data.find(":", day_pos);
      comma = data.find_first_of(",}", colon);
      int d = std::stoi(data.substr(colon + 1, comma - colon - 1));
      DebugNumber("day", std::to_string(d));

      // VALUE
      size_t value_pos = data.find("\"value\"", comma);
      colon = data.find(":", value_pos);
      size_t end = data.find_first_of(",}", colon);
      if (end == std::string::npos) end = data.size(); // <-- CORREGIDO
      std::string value_str = data.substr(colon+1, end-colon-1);
      int v = std::stoi(value_str);
      std::cout << "[DEBUG] guardar [" << e << "][" << d << "][" << t << "] = " << v << std::endl;
      satisfaccion[e][d][t] = v;

      pos = data.find("}", value_pos);
      if (pos == std::string::npos) break;
      std::cout <<  "MON:" << pos << " " << array_end << std::endl;
      pos = data.find("{", pos); // avanzar al siguiente objeto
  }
  std::cout << "\nMONDONGO\n";
}

void CargaInstanciaPlanificacionJson::ParseRequiredEmployees(
  const std::string& data,
  std::vector<std::vector<unsigned>>& minimo_empleados){

  std::cout << "\nCOMENZANDO REQUIERED EMPLYES\n";
  size_t pos=data.find("\"requiredEmployees\"");
  if(pos==std::string::npos){
    return;
  }
  
  size_t array_start = data.find("[", pos);
  size_t array_end = data.find("]", array_start); // <-- Fin del array
  pos = array_start + 1;

  while(pos < array_end){

    size_t shift_pos=data.find("\"shift\"",pos);
    if(shift_pos==std::string::npos){
      break;
    }

    size_t colon=data.find(":",shift_pos);
    size_t comma=data.find(",",colon);

    std::string shift_str=data.substr(colon+1,comma-colon-1);
    DebugNumber("required_shift",shift_str);
    unsigned shift=std::stoi(shift_str);

    size_t day_pos=data.find("\"day\"",comma);
    colon=data.find(":",day_pos);
    comma=data.find(",",colon);

    std::string day_str=data.substr(colon+1,comma-colon-1);
    DebugNumber("required_day",day_str);
    unsigned day=std::stoi(day_str);

    size_t value_pos=data.find("\"value\"",comma);
    colon=data.find(":",value_pos);
    size_t end=data.find_first_of(",}",colon);

    std::string value_str=data.substr(colon+1,end-colon-1);
    DebugNumber("required_value",value_str);
    unsigned value=std::stoi(value_str);

    minimo_empleados[day][shift]=value;

    pos=data.find("}",value_pos);
    if(pos==std::string::npos){
      break;
    }

    if(pos+1<data.size() && data[pos+1]==']'){
      break;
    }

    pos = data.find("{", pos); // avanzar al siguiente objeto
    if (pos == std::string::npos) {
      break;
    }
  }
}

InstanciaPlanificacionEmpleados* CargaInstanciaPlanificacionJson::Load(){

  std::string data=ReadFile();

  // -------- PARSE SHIFTS CORREGIDO --------

  std::vector<std::string> turnos;

  size_t start=data.find("\"shifts\"");
  size_t open=data.find("[",start);
  size_t close=data.find("]",open);

  size_t pos=open;

  while(true){

    size_t q1=data.find("\"",pos);
    if(q1==std::string::npos||q1>close){
      break;
    }

    size_t q2=data.find("\"",q1+1);

    std::string turno=data.substr(q1+1,q2-q1-1);
    std::cout<<"[DEBUG] turno = "<<turno<<std::endl;
    turnos.push_back(turno);

    pos=q2+1;
  }

  std::vector<std::string> empleados;
  std::vector<unsigned> free_days;

  pos = data.find("\"employees\"");
  pos = data.find("[", pos);

  while (true) {
      // Buscar próximo "freeDays" dentro del array de empleados
      size_t free_pos = data.find("\"freeDays\"", pos);
      if (free_pos == std::string::npos) break;

      size_t colon = data.find(":", free_pos);
      size_t end = data.find_first_of(",}", colon);
      if (colon == std::string::npos || end == std::string::npos) break;

      std::string fd_str = data.substr(colon + 1, end - colon - 1);
      DebugNumber("freeDays", fd_str);
      unsigned fd = std::stoi(fd_str);
      free_days.push_back(fd);

      // Buscar el "name" correspondiente
      size_t name_pos = data.find("\"name\"", free_pos);
      if (name_pos == std::string::npos) break;

      colon = data.find(":", name_pos);
      size_t q1 = data.find("\"", colon);
      size_t q2 = data.find("\"", q1 + 1);
      if (q1 == std::string::npos || q2 == std::string::npos) break;

      std::string nombre = data.substr(q1 + 1, q2 - q1 - 1);
      std::cout << "[DEBUG] empleado = " << nombre << std::endl;
      empleados.push_back(nombre);

      // Avanzar posición al final del objeto del empleado
      pos = data.find("}", name_pos);
      if (pos == std::string::npos) break;
      pos++; // para evitar estancarse
  }

  size_t num_empleados=empleados.size();
  size_t num_turnos=turnos.size();

  size_t horizon_pos=data.find("\"planningHorizon\"");
  size_t colon=data.find(":",horizon_pos);
  size_t comma=data.find_first_of(",}",colon);

  std::string dias_str=data.substr(colon+1,comma-colon-1);
  DebugNumber("planningHorizon",dias_str);

  size_t dias=std::stoi(dias_str);

  std::vector<std::vector<std::vector<int>>> satisfaccion(
    num_empleados,
    std::vector<std::vector<int>>(dias,std::vector<int>(num_turnos,0)));

  ParseSatisfaction(data,satisfaccion);

  std::vector<std::vector<unsigned>> minimo_empleados(
    dias,std::vector<unsigned>(num_turnos,0));

  ParseRequiredEmployees(data,minimo_empleados);

  return new InstanciaPlanificacionEmpleados(
    empleados,
    turnos,
    dias,
    satisfaccion,
    minimo_empleados,
    free_days
  );
}
#ifndef EVENTO
#define EVENTO

#include "Paciente.hpp"
#include "Estado.hpp"



class Evento{
    
    Estado m_estado;
    Paciente* m_paciente;
    Data m_horario;

    public:
    Evento(){ m_paciente = nullptr; }
    Evento(Paciente* Paciente, Data horario, Estado estado){ m_paciente = Paciente; m_horario = horario; m_estado=estado;}
    ~Evento(){m_paciente = nullptr;}
    Data getHorario() const { return m_horario;}
    Estado getEstado() const { return m_estado;}
    Paciente* getPaciente() const { return m_paciente;}
  

};

#endif
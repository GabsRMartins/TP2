#ifndef UNIDADE
#define UNIDADE

#include "Escalonador.hpp"
#include "Paciente.hpp"
#include "Fila.hpp"
#include "Vetor.hpp"


class Unidade{

    bool m_estado; // 0 para vazio, 1 para ocupado
    float m_tempo_exec;
    int qnt_atendentes;
    int qnt_pacientes;
    Vetor<Paciente*> pacientes;

public:
    bool ocupar(Paciente* Paciente);
    void retirar(Paciente* Paciente);
    Unidade();
    Unidade(int atendentes, float tempo_exec);
    ~Unidade();

    int getQtdAtendentes() const;
    bool getEstado() const;
    float getTemp() const;
    int getQntPaciente() const { return  qnt_pacientes;}

    Paciente* getPacienteSaida();

    

    void avaliaFilas();
    void alterarStatus(Paciente* paciente);
    bool atender(Fila& fila, Escalonador& escalonador , Paciente* paciente);
    void atenderTriagem(Fila& fila, Escalonador& escalonador);
};

#endif
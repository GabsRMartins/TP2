#include "../include/Unidade.hpp"
#include <cassert>
#include <complex.h>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>


  Unidade::Unidade(){
    m_estado = 0;
    qnt_atendentes = 0;
    qnt_pacientes = 0;
    m_tempo_exec = 0;
  }   

  
  Unidade::Unidade(int atendentes, float tempo_exec){
    m_estado = 0;
    qnt_atendentes = atendentes;
    m_tempo_exec = tempo_exec;
    qnt_pacientes = 0;
  }    
 


  Unidade::~Unidade() {
       
    }

  bool Unidade::ocupar(Paciente* novoPaciente) {
    if (qnt_pacientes >= qnt_atendentes) {
        std::cerr << "Unidade já está cheia!" << std::endl;
        return false;
    }
    
    if (novoPaciente == nullptr) {
        std::cerr << "Erro: ponteiro de paciente é nulo!" << std::endl;
        return false;
    }

    // Adicionando paciente ao vetor
    pacientes.push_back(novoPaciente);
    qnt_pacientes++;


    // Atualizar o estado da unidade caso atinja a capacidade máxima
    if (qnt_pacientes == qnt_atendentes) {
        m_estado = true;
    }

    return true;
}



void Unidade::retirar(Paciente* Paciente) {
    if (qnt_pacientes == 0) {
        std::cerr << "Erro: Nenhum paciente na fila para remover." << std::endl;
        return;
    }

    // Obter o primeiro paciente
    int indicePacienteRemovido;
    for (int i = 0; i < qnt_pacientes; ++i) {
        if (pacientes[i]->getId() == Paciente->getId()) {
            indicePacienteRemovido = i;
        
        }
    
    }


    // Remover o primeiro paciente da lista
    pacientes.erase(indicePacienteRemovido);  

    // Reduzir a contagem de pacientes
    qnt_pacientes--;

    // Atualizar o estado da unidade
    m_estado = false;

}




    int Unidade::getQtdAtendentes() const { return qnt_atendentes; }
    float Unidade::getTemp() const { return m_tempo_exec; }
    bool Unidade::getEstado() const { return m_estado; }


void  Unidade::alterarStatus(Paciente* paciente){
switch (paciente->getStatus()) {

                    case Estado::FILA_TRIAGEM:{
                            paciente->setStatus(Estado::SENDO_TRIADO);
                            break;
                    }
                    case Estado::FILA_ATENDIMENTO:{
                            paciente->setStatus(Estado::SENDO_ATENDIDO);
                             break;
                    }
                    case Estado::FILA_MH:{
                            paciente->setStatus(Estado::R_MH);
                             break;
                    }
                    case Estado::FILA_TL:{
                            paciente->setStatus(Estado::R_TL);
                             break;
                    }
                    case Estado::FILA_EI:{
                            paciente->setStatus(Estado::R_EI);
                             break;
                    }
                    case Estado::FILA_IM:{
                            paciente->setStatus(Estado::R_IM);
                            break;
                    }
                }
}





bool Unidade::atender(Fila& fila, Escalonador& escalonador, Paciente* paciente) {
    if (!m_estado) {  
        if (fila.getFirst() != paciente) {  return false;
        }
        Paciente* proximoPacienteAtendido = fila.Desenfileira();
        assert(paciente == proximoPacienteAtendido);
        if (proximoPacienteAtendido != nullptr) {  
            ocupar(proximoPacienteAtendido);  
            return true;
        } 
    }
    return false;
}



Paciente* Unidade::getPacienteSaida() {
    if (qnt_pacientes == 0) {
        return nullptr; // Nenhum paciente na unidade
    }

    Paciente* primeiroSaida = pacientes[0]; // Inicializa com o primeiro paciente

    for (int i = 1; i < qnt_pacientes; ++i) {
        if (pacientes[i]->getData() < primeiroSaida->getData()) {
            primeiroSaida = pacientes[i];
        }
    }
    return primeiroSaida;
}






        

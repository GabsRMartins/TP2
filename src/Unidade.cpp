#include "../include/Unidade.hpp"
#include <cassert>
#include <complex.h>
#include <cstddef>
#include <iostream>


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

  bool  Unidade::ocupar(Paciente* novoPaciente) {
      if (qnt_pacientes >= qnt_atendentes) {
            std::cerr << "Unidade já está cheia!" << std::endl;
            return false;
        }
        if (novoPaciente == nullptr) {
        std::cerr << "Erro: ponteiro de paciente é nulo!" << std::endl;
        return false;;
    }
    pacientes.push_back(novoPaciente);
    qnt_pacientes++;
    // Atualiza o estado caso atinja a capacidade máxima
    if (qnt_pacientes == qnt_atendentes) {
        m_estado = true;
    }
    return true;
}


    void Unidade::esvaziar() {
        if (!m_estado) {
            std::cerr << "Unidade já está vazia!" << std::endl;
            return;
        }

        pacientes.pop();
        qnt_pacientes--;
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






void Unidade::atenderTriagem(Fila& fila, Escalonador& escalonador) {
    Evento eventoNovo; 
    Paciente* pacienteAtual = fila.Desenfileira(); // Remove o próximo paciente da fila
    ocupar(pacienteAtual); // Associa o paciente à unidad
    alterarStatus(pacienteAtual);
    pacienteAtual->adicionarTempo(m_tempo_exec, pacienteAtual->getStatus()) ;   
    eventoNovo = Evento(pacienteAtual,pacienteAtual->getData(), pacienteAtual->getStatus()); 
    escalonador.insereEvento(eventoNovo);   
                 
        if (fila.getTamanho() > 0){
            fila.adicionaTempoEspera(m_tempo_exec);
        }
        
            esvaziar();
}

void Unidade::atender(Fila& fila, Escalonador& escalonador, Paciente* paciente) {
   

    if (!m_estado) { // Verifica se a unidade está desocupada
        Paciente* proximoPacienteAtendido = fila.Desenfileira();
        if (proximoPacienteAtendido != nullptr) { // Verifica se o paciente é válido
            ocupar(proximoPacienteAtendido); // Marca a unidade como ocupada
            alterarStatus(proximoPacienteAtendido); // Altera o status do paciente
            proximoPacienteAtendido->adicionarTempo(m_tempo_exec, proximoPacienteAtendido->getStatus());
            
            // Cria e insere o evento no escalonador
            Evento eventoNovo = Evento(proximoPacienteAtendido, 
                                        proximoPacienteAtendido->getData(), 
                                        proximoPacienteAtendido->getStatus());
            escalonador.insereEvento(eventoNovo);
            
            // Após concluir o atendimento, esvazia a unidade
            esvaziar();
        }
    }
    fila.adicionaTempoEspera(m_tempo_exec);

}


  /*   // Verifica se há pacientes na fila
    if (fila.getTamanho() > 0) {
        Evento eventoNovo;

        if (!m_estado) { // Verifica se a unidade está desocupada
            Paciente* proximoPacienteAtendido = fila.Desenfileira();
            if (proximoPacienteAtendido != nullptr) { // Verifica se o paciente é válido
                ocupar(proximoPacienteAtendido); // Marca a unidade como ocupada
                alterarStatus(proximoPacienteAtendido); // Altera o status do paciente
                proximoPacienteAtendido->adicionarTempo(m_tempo_exec, proximoPacienteAtendido->getStatus());   
                eventoNovo = Evento(proximoPacienteAtendido, proximoPacienteAtendido->getData(), proximoPacienteAtendido->getStatus()); 
                escalonador.insereEvento(eventoNovo); // Insere o evento de atendimento no escalonador
                
               
                
            }
        } else { // Se a unidade está ocupada
            // Adiciona tempo de espera ao paciente que está esperando na fila
            esvaziar();
            // Cria evento para o paciente que está esperando e insere no escalonador
            eventoNovo = Evento(paciente, paciente->getData(), paciente->getStatus()); 
            escalonador.insereEvento(eventoNovo);   
            
        }
        
        // Atualiza o tempo de espera do paciente na fila
        fila.adicionaTempoEspera(m_tempo_exec);
    } */




        

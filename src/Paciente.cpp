#include "../include/Paciente.hpp"
#include <string>

Paciente::Paciente()
    : m_id(0), alta_atendimento(false), m_ano(0), m_mes(0), m_dia(0), m_hora(0),
      m_urgencia(0), qnt_mh(0), qnt_tl(0), qnt_ei(0), qnt_im(0) {}


Paciente::Paciente(unsigned long id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int mh, int tl, int ei, int im){
    m_id = id;
    alta_atendimento = alta;
    m_ano = ano;
    m_mes = mes;
    m_dia = dia;
    m_hora = hora;
    m_data = Data(ano, mes, dia, hora);
    m_urgencia = urgencia;
    qnt_mh = mh;
    qnt_tl = tl;
    qnt_ei = ei;
    qnt_im = im;
    m_tempo_atendimento = 0;
    m_tempo_ocioso = 0;

};

unsigned long Paciente::getId() const { return m_id; }
int Paciente::getMH() const { return qnt_mh; }
int Paciente::getTL() const { return qnt_tl; }
int Paciente::getEI() const { return qnt_ei; }
int Paciente::getIM() const { return qnt_im; }
int Paciente::getUrgencia() const { return m_urgencia; }
Data Paciente::getData() const{return m_data;}
Estado Paciente::getStatus() const { return  m_status;}
bool Paciente::getAlta() const { return alta_atendimento;}


void Paciente::print() const {
    std::cout<< m_id << " ";
    Data dataChegada = Data(m_ano,m_mes,m_dia,m_hora);
    dataChegada.print();
    m_data.print();
    std::cout<<m_tempo_total_hospital << " "  << m_tempo_atendimento << " " << m_tempo_ocioso << std::endl;
}
void Paciente::adicionarTempo(float tempo, Estado estado) {
    if (estado == Estado::FILA_TRIAGEM || estado == Estado::FILA_ATENDIMENTO || 
        estado == Estado::FILA_IM || estado == Estado::FILA_EI || 
        estado == Estado::FILA_MH || estado == Estado::FILA_TL) {
        m_tempo_ocioso += tempo; // Atualiza tempo ocioso
    } else if (estado == Estado::SENDO_TRIADO || estado == Estado::SENDO_ATENDIDO) {
        m_tempo_atendimento += tempo; // Atualiza tempo de atendimento
    } else {
        float multiplicador = 1;
        switch (estado) {
            case Estado::R_EI:
                multiplicador = qnt_ei;
                break;
            case Estado::R_IM:
                multiplicador = qnt_im;
                break;
            case Estado::R_MH:
                multiplicador = qnt_mh;
                break;
            case Estado::R_TL:
                multiplicador = qnt_tl;
                break;
            default:
                std::cout << "Estado desconhecido: " << static_cast<int>(estado) << std::endl;
                break;
        }
        tempo *= multiplicador;
        m_tempo_atendimento += tempo;
    }

    // Atualiza a data com o tempo ajustado
    m_tempo_total_hospital = m_tempo_atendimento + m_tempo_ocioso; 
    m_data.adicionarHoras(tempo);
}

    

std::string Paciente::estadoParaString(Estado estado) const {
    switch (estado) {
        case Estado::CHEGOU: return "Chegou";
        case Estado::FILA_TRIAGEM: return "Fila de Triagem";
        case Estado::SENDO_TRIADO: return "Sendo Triado";
        case Estado::FILA_ATENDIMENTO: return "Fila de Atendimento";
        case Estado::SENDO_ATENDIDO: return "Sendo Atendido";
        case Estado::FILA_MH: return "Fila MH";
        case Estado::R_MH: return "Realizando MH";
        case Estado::FILA_TL: return "Fila TL";
        case Estado::R_TL: return "Realizando TL";
        case Estado::FILA_EI: return "Fila EI";
        case Estado::R_EI: return "Realizando EI";
        case Estado::FILA_IM: return "Fila IM";
        case Estado::R_IM: return "Realizando IM";
        case Estado::Alta: return "Alta";
        default: return "Estado Desconhecido";
    }
}

void Paciente::printHeap() const {
    std::cout << m_id <<" ";
    m_data.print();
    std::cout << estadoParaString(m_status);
    std::cout<<std::endl;
}

  

void Paciente::setStatus(Estado status){
    m_status = status;
}

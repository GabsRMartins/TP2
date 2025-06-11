#include "../include/TipoCelula.hpp"

TipoCelula::TipoCelula(){
    m_paciente = nullptr;
    prox = nullptr;

}

TipoCelula::TipoCelula(Paciente* p){
    m_paciente = p;
    prox = nullptr;
}

TipoCelula::~TipoCelula(){
    m_paciente = nullptr;
    prox = nullptr;

}
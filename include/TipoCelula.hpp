#ifndef TIPOCELULA
#define TIPOCELULA

#include "Paciente.hpp"
class TipoCelula{
    Paciente* m_paciente;
    TipoCelula* prox;
public:
    TipoCelula();
    TipoCelula(Paciente* p);
    ~TipoCelula();
    friend class Fila;

};

#endif
#ifndef FILA
#define FILA

#include "Paciente.hpp"
#include "TipoCelula.hpp"

class Fila{

TipoCelula* m_inicio;
TipoCelula* m_fim;
int m_tamanho;

public:
Fila();
~Fila();

void Enfileirar(Paciente* Paciente);
Paciente* Desenfileira();

Paciente*getFirst();

void Limpa();
int getTamanho() const;
void print() const;
void adicionaTempoEspera(float tempo);



};

#endif
#ifndef PROCEDIMENTO
#define PROCEDIMENTO


#include "Estado.hpp"
#include "Paciente.hpp"
#include "Vetor.hpp"
#include "Unidade.hpp"
#include "Fila.hpp"
#include <string>

constexpr int QNT_UNIDADES = 6;

using std::string;

class Procedimento{

int* m_triagem;
int m_tempo_total_exec;
int qnt_unidades;
int qnt_pacientes;

Fila fila_triagem;


Fila fila_atendimentoVerde;
Fila fila_atendimentoAmarelo;
Fila fila_atendimentoVermelho;

Fila fila_mhVerde;
Fila fila_mhAmarelo;
Fila fila_mhVermelho;

Fila fila_tlVerde;
Fila fila_tlAmarelo;
Fila fila_tlVermelho;


Fila fila_eiVerde;
Fila fila_eiAmarelo;
Fila fila_eiVermelho;

Fila fila_imVerde;
Fila fila_imAmarelo;
Fila fila_imVermelho;




Vetor<Unidade> unidades;
Vetor<Paciente*> pacientes;

public:
Procedimento(const string &filename);
~Procedimento();
void print() const;
void simular();

Fila& getFilaPorEstadoEurgencia(Estado estado, int urgencia);
void processarFila(Estado estadoAtual, Estado proximoEstado, Escalonador& escalonador, Paciente* paciente);
void defineFila(Paciente* paciente, Estado estado);
bool avaliaFilas(Estado estado, Escalonador& escalonador, Paciente* paciente); 

void processarEvento(Estado estadoAtual, Estado proximoEstado, int unidadeIndex, Fila& fila, Escalonador& escalonador, Paciente* paciente);
void criarEvento(Paciente* paciente, Escalonador& escalonador);
void processarEspera(int unidadeIndex, Escalonador& escalonador, Paciente* paciente);
void processarAtendimento(Estado proximoEstado, int unidadeIndex, Escalonador& escalonador, Paciente* paciente);
bool unidadeDisponivel(int unidadeIndex);

 Vetor<Fila*> getFilasPorEstado(Estado estado);

void estatisticas();
};

#endif
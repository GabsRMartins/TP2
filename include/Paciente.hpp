#ifndef PACIENTE
#define PACIENTE

#include "Data.hpp"
#include "Estado.hpp"



class Paciente{

Estado m_status;
float m_tempo_ocioso;
float m_tempo_atendimento; 
float m_tempo_total_hospital;

unsigned long m_id;
bool alta_atendimento;
int m_urgencia;

int m_ano;
int m_mes;
int m_dia;
int m_hora;

Data m_data;


int qnt_mh;
int qnt_tl;
int qnt_ei;
int qnt_im;

public:
Paciente();
Paciente(unsigned long	 id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int mh, int tl, int ei, int im);
unsigned long getId() const;
int getUrgencia() const;
Data getData() const;
Estado getStatus() const;
bool getAlta() const;
int getMH() const;
int getTL() const;
int getEI() const;
int getIM() const;
void print() const;

void printHeap() const;


std::string estadoParaString(Estado estado) const;

void adicionarTempo(float tempo, Estado estado);

void setStatus(Estado status); 

};

#endif
#include "../include/Fila.hpp"

#include <cassert>
#include <cstdio>
#include <stdexcept>

Fila::Fila()
{
    m_inicio = nullptr;
    m_fim = m_inicio;
    m_tamanho = 0;
}

void Fila::Limpa()
{
    while (m_inicio != nullptr) {
        TipoCelula* temp = m_inicio;
        m_inicio = m_inicio->prox;
        delete temp;
    }
    m_inicio = nullptr;
    m_fim = nullptr;
}

Fila::~Fila()
{
    Limpa();
    delete m_inicio;
}

void Fila::Enfileirar(Paciente* paciente)
{
  //std::cout << "Inserindo paciente na fila: " << paciente->getId() << std::endl;
    if (paciente == nullptr) {
        throw std::invalid_argument("Tentativa de enfileirar um paciente nulo.");
    }

    TipoCelula* novaCelula = new TipoCelula(paciente);

    if (m_fim == nullptr) {   // Fila vazia
        m_inicio = novaCelula;
    } else {
        m_fim->prox = novaCelula;
    }
    m_fim = novaCelula;
    ++m_tamanho;
}

Paciente* Fila::Desenfileira() {
    if (m_tamanho == 0) {
        std::cerr << "Erro: Tentativa de desenfileirar uma fila vazia!" << std::endl;
        return nullptr;  // Retorna nullptr em vez de lançar uma exceção para evitar travamentos inesperados
    }

    TipoCelula* p = m_inicio;                  // Ponteiro para a célula a ser removida
    Paciente* aux = m_inicio->m_paciente;       // Obtém o ponteiro para o paciente

    m_inicio = m_inicio->prox;                 // Atualiza o início da fila

    if (m_inicio == nullptr) {                  // Se a fila ficou vazia
        m_fim = nullptr;                        // Atualiza o ponteiro para o fim
    }

    delete p;                                   // Libera a memória da célula removida
    m_tamanho--;                                // Decrementa o tamanho da fila

   // std::cout << "Paciente removido da fila: " << aux->getId() << std::endl;

    return aux;                                 // Retorna o paciente removido
}



Paciente* Fila::getFirst() {
    if (m_tamanho == 0) {
        std::cerr << "Erro: Tentativa de desenfileirar uma fila vazia!" << std::endl;
        return nullptr;  // Retorna nullptr em vez de lançar uma exceção para evitar travamentos inesperados
    }

    TipoCelula* p = m_inicio;                  // Ponteiro para a célula a ser removida
    Paciente* aux = m_inicio->m_paciente;       // Obtém o ponteiro para o paciente


    return aux;                             
}





int Fila::getTamanho() const
{
    return m_tamanho;
}

void Fila::print() const
{
    if (m_tamanho == 0) {
        std::cout << "A fila está vazia." << std::endl;
        return;
    }

    TipoCelula* atual = m_inicio;
    int posicao = 1;

    std::cout << "Conteúdo da fila:" << std::endl;
    while (atual != nullptr) {
        std::cout << "Paciente " << posicao << ": ";
        if (atual->m_paciente != nullptr) {   // Verificação de ponteiro nulo
            atual->m_paciente->print();
        } else {
            std::cout << "Paciente nulo." << std::endl;
        }
        atual = atual->prox;
        ++posicao;
    }
}

void Fila::adicionaTempoEspera(float tempo){
    if (m_tamanho == 0) 
        return;
    TipoCelula* atual = m_inicio;

    while (atual != nullptr) {
        atual->m_paciente->adicionarTempo(tempo, atual->m_paciente->getStatus());
        atual = atual->prox;
    }
}
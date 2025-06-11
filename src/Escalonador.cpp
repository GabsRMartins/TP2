#include "../include/Escalonador.hpp"

#include <iostream>

Escalonador::Escalonador() {}

Escalonador::~Escalonador() {}

void Escalonador::heapifyUp(int index)
{
    while (index > 0) {
        int parentIndex = getParentIndex(index);
        if (compareEventos(heap[index], heap[parentIndex])) {
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}


bool Escalonador::ordemDeEventos(const Evento& a, const Evento& b) {
    Estado estado = a.getEstado();
    switch (estado) {
        case Estado::SENDO_TRIADO:
        case Estado::SENDO_ATENDIDO:
        case Estado::R_MH:
        case Estado::R_TL:
        case Estado::R_EI:
        case Estado::R_IM:
            return true; // Quando o estado corresponder a esses, retorna true
        default:
            return false; // Para os outros estados, retorna false
    }
}

bool Escalonador::compareEventos(const Evento& a, const Evento& b) {
    if (a.getHorario() != b.getHorario()) {
        return a.getHorario() < b.getHorario();
    } else if(a.getEstado() != b.getEstado()) {
        return ordemDeEventos(a,b);
    } else { 
    return a.getPaciente()->getId() < b.getPaciente()->getId();
    }
}


void Escalonador::heapifyDown(int index) {

   // this->print();
    int menor = index;
    int esquerdo = getLeftChildIndex(index);
    int direito = getRightChildIndex(index);

    if (esquerdo < heap.size() && compareEventos(heap[esquerdo], heap[menor])) {
        menor = esquerdo;
 
    }

    if (direito < heap.size() && compareEventos(heap[direito], heap[menor])) {
        menor = direito;
    }

    if (menor != index) {
        std::swap(heap[index], heap[menor]);
        heapifyDown(menor);
    }
}





void Escalonador::insereEvento(Evento novoEvento)
{
    heap.push_back(novoEvento);
    heapifyUp(heap.size() - 1);
}

Evento Escalonador::retiraEvento() {
    if (heap.size() == 0) {
        throw std::out_of_range("Escalonador vazio");
    }

    Evento min = heap[0];
    heap[0] = heap.back();
    heap.pop();  // Reduz tamanho lógico e remove último elemento
    if (heap.size() != 0) {
        heapifyDown(0);
    }
    
    return min;
}

Evento Escalonador::getMin() const
{
    if (heap.size() == 0) {
        throw std::out_of_range("Escalonador vazio");
    }
    return heap[0];
}

bool Escalonador::isEmpty() const
{
    if (heap.size() == 0) return true;
    return false;
}

void Escalonador::print() const
{
     
    int level = 0;
    int count = 1;

    for (size_t i = 0; i < heap.size(); ++i) {

        heap[i].getPaciente()->printHeap();
        if (i + 1 == count) {
            std::cout << std::endl;   // Novo nível
            ++level;
            count += (1 << level);   // 2^level
        }
    }
    std::cout << "Acabou aqui" << std::endl;
}

#include "../include/Escalonador.hpp"

#include <iostream>

Escalonador::Escalonador() {}

Escalonador::~Escalonador() {}

void Escalonador::heapifyUp(int index)
{
    while (index > 0) {
        int parentIndex = getParentIndex(index);

        // Critério principal: Comparar horários
        if (heap[index].getHorario() < heap[parentIndex].getHorario()) {
            std::swap(heap[index], heap[parentIndex]);
        }
        // Critério secundário: Comparar IDs se os horários forem iguais
        else if (heap[index].getHorario() == heap[parentIndex].getHorario() &&
                 heap[index].getPaciente()->getUrgencia() > heap[parentIndex].getPaciente()->getUrgencia()) {
            std::swap(heap[index], heap[parentIndex]);
        } else if (heap[index].getHorario() == heap[parentIndex].getHorario() &&
                   heap[index].getPaciente()->getUrgencia() == heap[parentIndex].getPaciente()->getUrgencia() &&
                   heap[index].getPaciente()->getId() < heap[parentIndex].getPaciente()->getId()) {
            std::swap(heap[index], heap[parentIndex]);
        } else {
            break;
        }
        // Subir na hierarquia do heap
        index = parentIndex;
    }
}

void comparaValores(Paciente a, Paciente b) {}

void Escalonador::heapifyDown(int index)
{
    int size = heap.size();
    while (true) {
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);
        int smallest = index;

        // Verificar o filho esquerdo
        if (leftChildIndex < size && (heap[leftChildIndex].getHorario() < heap[smallest].getHorario() ||
                                      (heap[leftChildIndex].getHorario() == heap[smallest].getHorario() &&
                                       heap[leftChildIndex].getPaciente()->getUrgencia() > heap[smallest].getPaciente()->getUrgencia()) ||
                                      (heap[leftChildIndex].getHorario() == heap[smallest].getHorario() &&
                                       heap[leftChildIndex].getPaciente()->getId() < heap[smallest].getPaciente()->getId() &&
                                       heap[leftChildIndex].getPaciente()->getUrgencia() == heap[smallest].getPaciente()->getUrgencia()))) {
            smallest = leftChildIndex;
        }

        // Verificar o filho direito
        if (rightChildIndex < size && (heap[rightChildIndex].getHorario() < heap[smallest].getHorario() ||
                                       (heap[rightChildIndex].getHorario() == heap[smallest].getHorario() &&
                                        heap[rightChildIndex].getPaciente()->getUrgencia() > heap[smallest].getPaciente()->getUrgencia()) ||
                                       (heap[rightChildIndex].getHorario() == heap[smallest].getHorario() &&
                                        heap[rightChildIndex].getPaciente()->getId() < heap[smallest].getPaciente()->getId() &&
                                        heap[rightChildIndex].getPaciente()->getUrgencia() == heap[smallest].getPaciente()->getUrgencia()))) {
            smallest = rightChildIndex;
        }

        // Se o menor elemento não é o nó atual, faça a troca
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;   // Continue no novo índice
        } else {
            break;   // O heap está ordenado
        }
    }
}

void Escalonador::insereEvento(Evento evento)
{
    heap.push_back(evento);
    heapifyUp(heap.size() - 1);
}

Evento Escalonador::retiraEvento()
{
    if (heap.size() == 0) {
        throw std::out_of_range("Escalonador vazio");
    }

    Evento min = heap[0];
    heap[0] = heap.back();
    heap.pop();
    heapifyDown(0);
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
        // std::cout << heap[i].getHorario().toTimestamp() << " ";
        if (i + 1 == count) {
            std::cout << std::endl;   // Novo nível
            ++level;
            count += (1 << level);   // 2^level
        }
    }
    std::cout << "Acabou aqui" << std::endl;
}

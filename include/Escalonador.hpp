#ifndef ESCALONADOR
#define ESCALONADOR
#include "Evento.hpp"
#include "Vetor.hpp"
#include <cstddef>

enum class Atributo{Data, Urgencia};




class Escalonador{

private:
    Vetor<Evento> heap;


    int getParentIndex(int index) { return index - 1; }
    int getLeftChildIndex(int index) { return  index + 1; }
    int getRightChildIndex(int index) { return index + 2; }

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Escalonador();
    ~Escalonador();

    void insereEvento(Evento evento);
    Evento retiraEvento();
    Evento getMin() const;
    bool ordemDeEventos(const Evento& a, const Evento& b);
    bool isEmpty() const;
    void print() const;
    int size() const { return heap.size();}
    bool compareEventos(const Evento& a, const Evento& b);

};

#endif
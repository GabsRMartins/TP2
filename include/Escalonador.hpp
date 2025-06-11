#ifndef ESCALONADOR
#define ESCALONADOR
#include "Evento.hpp"
#include "Vetor.hpp"

enum class Atributo{Data, Urgencia};




class Escalonador{

private:
    Vetor<Evento> heap;

    int getParentIndex(int index) { return (index - 1) ; }
    int getLeftChildIndex(int index) { return 2 * index + 1; }
    int getRightChildIndex(int index) { return 2 * index + 2; }

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Escalonador();
    ~Escalonador();

    void insereEvento(Evento evento);
    Evento retiraEvento();
    Evento getMin() const;
    bool isEmpty() const;
    void print() const;
    int size() const { return heap.size();}

};

#endif
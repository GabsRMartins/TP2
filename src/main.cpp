#include "../include/Procedimento.hpp"
#include <cassert>


int main(int argc, char *argv[]) {
   

    string file = argv[1];
    Procedimento teste =  Procedimento(file);
    //teste.estatisticas();
    teste.simular();
    teste.estatisticas();
 
    return 0;
}

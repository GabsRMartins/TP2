#include "../include/Procedimento.hpp"
#include <iostream>
#include <chrono>
#include <string>

template <typename Func, typename Obj>
void measureExecutionTime(Func func, Obj& obj) {
    auto start = std::chrono::high_resolution_clock::now();

    (obj.*func)();  // Chamada correta para função-membro

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>" << std::endl;
        return 1;
    }

    std::string file = argv[1];
    Procedimento teste(file);

    teste.simular();
   
    measureExecutionTime(&Procedimento::simular, teste);
    //teste.estatisticas();

    return 0;
}

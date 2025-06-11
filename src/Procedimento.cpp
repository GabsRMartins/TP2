#include "../include/Procedimento.hpp"

#include "../include/Escalonador.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

Procedimento::Procedimento(const string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);
    }

    std::string line;

    // Lê as unidades
    for (int i = 0; i < QNT_UNIDADES; ++i) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Erro ao ler linha das unidades.");
        }

        std::istringstream ss(line);
        float aux_tempo;
        int aux_atendentes;

        // Lê os valores inteiros da linha
        ss >> aux_tempo >> aux_atendentes;
        // Cria a unidade com os valores lidos
        Unidade u = Unidade(aux_atendentes, aux_tempo);
        unidades.push_back(u);
    }

    // Lê a quantidade de pacientes
    if (!std::getline(file, line)) {
        throw std::runtime_error("Erro ao ler linha com a quantidade de pacientes.");
    }
    qnt_pacientes = std::stoi(line);   // Lê a quantidade de pacientes
    // Lê os dados de cada paciente
    for (int i = 0; i < qnt_pacientes; ++i) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Erro ao ler linha dos pacientes.");
        }
        // std::cout << line << std::endl;
        std::istringstream ss(line);
        unsigned long id;
        bool alta;
        int ano, mes, dia, hora, urgencia, mh, tl, ei, im;

        // Lê os valores da linha
        ss >> id >> alta >> ano >> mes >> dia >> hora >> urgencia >> mh >> tl >> ei >> im;

        // Cria o paciente com os valores lidos
        Paciente* p = new Paciente(id, alta, ano, mes, dia, hora, urgencia, mh, tl, ei, im);

        pacientes.push_back(p);
    }
}

Procedimento::~Procedimento()
{
    for (int i = 0; i < qnt_pacientes; ++i) {
        delete pacientes[i];
    }
}



void Procedimento::processarFila(Estado estadoAtual, Estado proximoEstado, Escalonador& escalonador, Paciente* paciente) {
    // Define a fila apropriada para o estado atual
    if (proximoEstado != Estado::Alta) {
    defineFila(paciente, proximoEstado);
    } else {
        //std::cout<<"Recebeu alta" << std::endl;
    }
    // Atualiza o estado do paciente
    paciente->setStatus(proximoEstado);
    // Cria um novo evento com o próximo estado
    Evento eventoNovo(paciente, paciente->getData(), proximoEstado);
    // Insere o evento no escalonador
    escalonador.insereEvento(eventoNovo);
}




void Procedimento::avaliaFilas(Estado estado, Escalonador& escalonador, Paciente* paciente)
{
    switch (estado) {
        case Estado::FILA_ATENDIMENTO: {
            if (fila_atendimentoVermelho.getTamanho() > 0) {      
                unidades[1].atender(fila_atendimentoVermelho, escalonador,paciente);
                fila_atendimentoAmarelo.adicionaTempoEspera(unidades[1].getTemp());
                fila_atendimentoVerde.adicionaTempoEspera(unidades[1].getTemp());
            } else if (fila_atendimentoAmarelo.getTamanho() > 0) {
                 while (fila_atendimentoAmarelo.getTamanho() > 0) {
                unidades[1].atender(fila_atendimentoAmarelo, escalonador,paciente);
                fila_atendimentoVerde.adicionaTempoEspera(unidades[1].getTemp());
                }
            } else {
                while (fila_atendimentoVerde.getTamanho()> 0) {
                
                unidades[1].atender(fila_atendimentoVerde, escalonador,paciente);
                }
            }
            break;
        }
        case Estado::FILA_EI: {
            if (fila_eiVermelho.getTamanho() > 0) {
                unidades[4].atender(fila_eiVermelho, escalonador,paciente);
                fila_eiAmarelo.adicionaTempoEspera(unidades[4].getTemp());
                fila_eiVerde.adicionaTempoEspera(unidades[4].getTemp());
            } else if (fila_eiAmarelo.getTamanho() > 0) {
                unidades[4].atender(fila_eiAmarelo, escalonador,paciente);
                fila_eiVerde.adicionaTempoEspera(unidades[4].getTemp());

            } else {
                unidades[4].atender(fila_eiVerde, escalonador,paciente);
            }
            break;
        }

        case Estado::FILA_IM: {
            if (fila_imVermelho.getTamanho() > 0) {
                unidades[5].atender(fila_imVermelho, escalonador,paciente);
                fila_imAmarelo.adicionaTempoEspera(unidades[5].getTemp());
                fila_imVerde.adicionaTempoEspera(unidades[5].getTemp());
            } else if (fila_imAmarelo.getTamanho() > 0) {
                unidades[5].atender(fila_imAmarelo, escalonador,paciente);
                fila_imVerde.adicionaTempoEspera(unidades[5].getTemp());

            } else {
                unidades[5].atender(fila_imVerde, escalonador,paciente);
            }
            break;
        }
        case Estado::FILA_MH: {
            if (fila_mhVermelho.getTamanho() > 0) {
                unidades[2].atender(fila_mhVermelho, escalonador,paciente);
                fila_mhAmarelo.adicionaTempoEspera(unidades[2].getTemp());
                fila_mhVerde.adicionaTempoEspera(unidades[2].getTemp());
            } else if (fila_mhAmarelo.getTamanho() > 0) {
                unidades[2].atender(fila_mhAmarelo, escalonador,paciente);
                fila_mhVerde.adicionaTempoEspera(unidades[2].getTemp());

            } else {
                unidades[2].atender(fila_mhVerde, escalonador,paciente);
            }
            break;
        }

        case Estado::FILA_TL: {
            if (fila_tlVermelho.getTamanho() > 0) {
                unidades[3].atender(fila_tlVermelho, escalonador,paciente);
                fila_tlAmarelo.adicionaTempoEspera(unidades[3].getTemp());
                fila_tlVerde.adicionaTempoEspera(unidades[3].getTemp());
            } else if (fila_tlAmarelo.getTamanho() > 0) {
                unidades[3].atender(fila_tlAmarelo, escalonador,paciente);
                fila_tlVerde.adicionaTempoEspera(unidades[3].getTemp());

            } else {
                unidades[3].atender(fila_tlVerde, escalonador,paciente);
            }
            break;
        }
    }
}





Fila& Procedimento::getFilaPorEstadoEurgencia(Estado estado, int urgencia) {
    if(estado == Estado::FILA_TRIAGEM){
       // std::cout << "Foi para triagem" << std::endl;
        return fila_triagem;
    }
    if (estado == Estado::FILA_ATENDIMENTO) {
       // std::cout << "Foi para Atendimento" << std::endl;
        if (urgencia == 0) return fila_atendimentoVerde;
        if (urgencia == 1) return fila_atendimentoAmarelo;
        return fila_atendimentoVermelho;
    } else if (estado == Estado::FILA_EI) {
        // std::cout << "Foi para EI" << std::endl;
        if (urgencia == 0) return fila_eiVerde;
        if (urgencia == 1) return fila_eiAmarelo;
        return fila_eiVermelho;
    } else if (estado == Estado::FILA_IM) {
       // std::cout << "Foi para IM" << std::endl;
        if (urgencia == 0) return fila_imVerde;
        if (urgencia == 1) return fila_imAmarelo;
        return fila_imVermelho;
    } else if (estado == Estado::FILA_MH) {
        if (urgencia == 0) return fila_mhVerde;
        if (urgencia == 1) return fila_mhAmarelo;
        return fila_mhVermelho;
    } else if (estado == Estado::FILA_TL) {
        if (urgencia == 0) return fila_tlVerde;
        if (urgencia == 1) return fila_tlAmarelo;
        return fila_tlVermelho;
    }
    throw std::invalid_argument("Estado inválido");
}

void Procedimento::defineFila(Paciente* paciente, Estado estado) {
    int urgencia = paciente->getUrgencia();
    Fila& fila = getFilaPorEstadoEurgencia(estado, urgencia);
    fila.Enfileirar(paciente);
}


void Procedimento::simular()
{
    bool fimSimulação = false;
    Escalonador* escalonador = new Escalonador();
    ;
    for (int i = 0; i < qnt_pacientes; ++i) {
        if (!(pacientes.get(i))) {
            throw std::runtime_error("Paciente inválido na posição " + std::to_string(i));
        }
        Paciente* aux = pacientes.get(i);
        Data aux_tempo = aux->getData();
        Evento event = Evento(aux, aux_tempo, Estado::CHEGOU);
        escalonador->insereEvento(event);
    }

    while (!fimSimulação) {
        // std::cout<< escalonador->size() <<std::endl;

        escalonador->print();
        Evento eventoAvaliado = escalonador->retiraEvento();
        Evento eventoNovo;
        Paciente* aux = eventoAvaliado.getPaciente();
        switch (eventoAvaliado.getEstado()) {

            case Estado::CHEGOU: {
                processarFila(Estado::CHEGOU, Estado::FILA_TRIAGEM, *escalonador, aux);
                break;
            }
            case Estado::FILA_TRIAGEM: {
                
                unidades[0].atender(fila_triagem, *escalonador,aux);
                break;
            }
            case Estado::SENDO_TRIADO: {
                processarFila(Estado::SENDO_TRIADO, Estado::FILA_ATENDIMENTO, *escalonador, aux);
                break;
            }
            case Estado::FILA_ATENDIMENTO: {
                // std::cout<< "Atendendo Fila 2" <<std::endl;
                avaliaFilas(Estado::FILA_ATENDIMENTO, *escalonador,aux);
                break;
            }
            case Estado::SENDO_ATENDIDO: {
                if (aux->getAlta()) {
                     processarFila(Estado::SENDO_ATENDIDO, Estado::Alta, *escalonador, aux);
                } else {
                    processarFila(Estado::SENDO_ATENDIDO, Estado::FILA_MH, *escalonador, aux);
                }
                break;
            }
            case Estado::FILA_MH: {
                 //std::cout<< "Atendendo Fila 3"<<std::endl;
                avaliaFilas(Estado::FILA_MH, *escalonador, aux);
                break;
            }
            case Estado::R_MH: {
                processarFila(Estado::R_MH, Estado::FILA_TL, *escalonador, aux);
                break;
            }
            case Estado::FILA_TL: {
                // std::cout<< "Atendendo Fila 4" <<std::endl;
                avaliaFilas(Estado::FILA_TL, *escalonador, aux);
                break;
            }
            case Estado::R_TL: {
                processarFila(Estado::R_TL, Estado::FILA_EI, *escalonador, aux);
                break;
            }
            case Estado::FILA_EI: {
                // std::cout<< "Atendendo Fila 5"<<std::endl;
                avaliaFilas(Estado::FILA_EI, *escalonador,aux);
                break;
            }
            case Estado::R_EI: {
                processarFila(Estado::R_EI, Estado::FILA_IM, *escalonador, aux);
                break;
            }
            case Estado::FILA_IM: {
                // std::cout<< "Atendendo Fila 6"<<std::endl;
                avaliaFilas(Estado::FILA_IM, *escalonador,aux);
                break;
            }
            case Estado::R_IM: {
                processarFila(Estado::R_IM, Estado::Alta, *escalonador, aux);
                break;
            }
            case Estado::Alta: {
                break;
            }
        }

        if (escalonador->isEmpty()) {
            fimSimulação = true;
            delete escalonador;
        }
    }
}

void Procedimento::estatisticas()
{
    for (int i = 0; i < qnt_pacientes; ++i) {
        pacientes[i]->print();
    }
}

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




bool Procedimento::avaliaFilas(Estado estado, Escalonador& escalonador, Paciente* paciente) {
    bool foiAtendido;
    Fila* filaVermelho;
    Fila* filaAmarelo;
    Fila* filaVerde;
    int unidadeIndex;

    switch (estado) {
        case::Estado::FILA_TRIAGEM: 
                unidadeIndex = 0;
                break;
        case Estado::FILA_ATENDIMENTO:
            filaVermelho = &fila_atendimentoVermelho;
            filaAmarelo = &fila_atendimentoAmarelo;
            filaVerde = &fila_atendimentoVerde;
            unidadeIndex = 1;
            break;

        case Estado::FILA_EI:
            filaVermelho = &fila_eiVermelho;
            filaAmarelo = &fila_eiAmarelo;
            filaVerde = &fila_eiVerde;
            unidadeIndex = 4;
            break;

        case Estado::FILA_IM:
            filaVermelho = &fila_imVermelho;
            filaAmarelo = &fila_imAmarelo;
            filaVerde = &fila_imVerde;
            unidadeIndex = 5;
            break;

        case Estado::FILA_MH:
            filaVermelho = &fila_mhVermelho;
            filaAmarelo = &fila_mhAmarelo;
            filaVerde = &fila_mhVerde;
            unidadeIndex = 2;
            break;

        case Estado::FILA_TL:
            filaVermelho = &fila_tlVermelho;
            filaAmarelo = &fila_tlAmarelo;
            filaVerde = &fila_tlVerde;
            unidadeIndex = 3;
            break;

        default:
            return false; // Estado inválido
    }

    if(estado ==  Estado::FILA_TRIAGEM){
        foiAtendido = unidades[0].atender(fila_triagem, escalonador, paciente);
    }else{
    if (filaVermelho->getTamanho() > 0) {
       foiAtendido = unidades[unidadeIndex].atender(*filaVermelho, escalonador, paciente);
    } else if (filaAmarelo->getTamanho() > 0) {
           foiAtendido =  unidades[unidadeIndex].atender(*filaAmarelo, escalonador, paciente);
    } else {
           foiAtendido =  unidades[unidadeIndex].atender(*filaVerde, escalonador, paciente);
    }
    }
    return foiAtendido;
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


void Procedimento::processarEvento(Estado estadoAtual, Estado proximoEstado, int unidadeIndex, Fila& fila, Escalonador& escalonador, Paciente* paciente) {
    if (unidadeIndex < 0 || unidadeIndex >= unidades.size()) {
        std::cerr << "Erro: Índice de unidade inválido: " << unidadeIndex << std::endl;
        return;
    }

    if (unidadeDisponivel(unidadeIndex)) {
        processarAtendimento(proximoEstado, unidadeIndex, escalonador, paciente);
    } else {
        processarEspera(unidadeIndex, escalonador, paciente);
    }
}

bool Procedimento::unidadeDisponivel(int unidadeIndex) {
    return !unidades[unidadeIndex].getEstado();
}

void Procedimento::processarAtendimento(Estado proximoEstado, int unidadeIndex, Escalonador& escalonador, Paciente* paciente) {
    bool avaliado = avaliaFilas(paciente->getStatus(), escalonador, paciente);

    if (avaliado) {
        paciente->setStatus(proximoEstado);
        paciente->adicionarTempo(unidades[unidadeIndex].getTemp(), paciente->getStatus());
    } else {
        paciente->adicionarTempo(0.001, paciente->getStatus());
       
       
    }

    criarEvento(paciente, escalonador);
}


void Procedimento::processarEspera(int unidadeIndex, Escalonador& escalonador, Paciente* paciente) {
    if (!paciente) return;
    // Obtemos o paciente que está saindo da unidade (se houver)
    Paciente* pacienteAnterior = unidades[unidadeIndex].getPacienteSaida();  // Supondo que a unidade tenha acesso ao paciente atual
    if (pacienteAnterior) {
        Data tempoDeSaida = pacienteAnterior->getData();
        
        float tempoEspera = paciente->getData().calcularDiferencaEmHoras(tempoDeSaida);  // Tempo total de hospital do paciente anterior
        paciente->adicionarTempo(tempoEspera, paciente->getStatus());

    } else {
       // std::cout << "Nenhum paciente anterior para calcular tempo de espera." << std::endl;
    }

    criarEvento(paciente, escalonador);
}



void Procedimento::criarEvento(Paciente* paciente, Escalonador& escalonador) {
    Evento eventoNovo(paciente, paciente->getData(), paciente->getStatus());
    escalonador.insereEvento(eventoNovo);
}



void Procedimento::simular()
{
    bool fimSimulacao = false;
    Escalonador* escalonador = new Escalonador();

    for (int i = 0; i < qnt_pacientes; ++i) {
        if (!(pacientes.get(i))) {
            throw std::runtime_error("Paciente invalido na posicao " + std::to_string(i));
        }
        Paciente* aux = pacientes.get(i);
        Data aux_tempo = aux->getData();
        Evento event = Evento(aux, aux_tempo, Estado::CHEGOU);
        escalonador->insereEvento(event);
    }

    while (!fimSimulacao) {
        Evento eventoAvaliado = escalonador->retiraEvento();
        Paciente* aux = eventoAvaliado.getPaciente();

        switch (eventoAvaliado.getEstado()) {
            case Estado::CHEGOU:
                processarFila(Estado::CHEGOU, Estado::FILA_TRIAGEM, *escalonador, aux);
                break;

            case Estado::FILA_TRIAGEM:
                processarEvento(Estado::FILA_TRIAGEM, Estado::SENDO_TRIADO, 0, fila_triagem, *escalonador, aux);
                break;

            case Estado::SENDO_TRIADO:
                unidades[0].retirar(aux);
                processarFila(Estado::SENDO_TRIADO, Estado::FILA_ATENDIMENTO, *escalonador, aux);
                break;

            case Estado::FILA_ATENDIMENTO:
                processarEvento(Estado::FILA_ATENDIMENTO, Estado::SENDO_ATENDIDO, 1, getFilaPorEstadoEurgencia(aux->getStatus(), aux->getUrgencia()), *escalonador, aux);
                break;

            case Estado::SENDO_ATENDIDO:
            unidades[1].retirar(aux);
                if (aux->getAlta()) {
                    processarFila(Estado::SENDO_ATENDIDO, Estado::Alta, *escalonador, aux);
                } else {
                    processarFila(Estado::SENDO_ATENDIDO, Estado::FILA_MH, *escalonador, aux);
                }
                break;

            case Estado::FILA_MH:
                processarEvento(Estado::FILA_MH, Estado::R_MH, 2, getFilaPorEstadoEurgencia(aux->getStatus(), aux->getUrgencia()), *escalonador, aux);
                break;

            case Estado::R_MH:
                unidades[2].retirar(aux);
                processarFila(Estado::R_MH, Estado::FILA_TL, *escalonador, aux);
                break;

            case Estado::FILA_TL:
                processarEvento(Estado::FILA_TL, Estado::R_TL, 3, getFilaPorEstadoEurgencia(aux->getStatus(), aux->getUrgencia()), *escalonador, aux);
                break;

            case Estado::R_TL:
                unidades[3].retirar(aux);
                processarFila(Estado::R_TL, Estado::FILA_EI, *escalonador, aux);
                break;

            case Estado::FILA_EI:
                processarEvento(Estado::FILA_EI, Estado::R_EI, 4, getFilaPorEstadoEurgencia(aux->getStatus(), aux->getUrgencia()), *escalonador, aux);
                break;

            case Estado::R_EI:
                unidades[4].retirar(aux);
                processarFila(Estado::R_EI, Estado::FILA_IM, *escalonador, aux);
                break;

            case Estado::FILA_IM:
                processarEvento(Estado::FILA_IM, Estado::R_IM, 5, getFilaPorEstadoEurgencia(aux->getStatus(), aux->getUrgencia()), *escalonador, aux);
                break;

            case Estado::R_IM:
                unidades[5].retirar(aux);
                processarFila(Estado::R_IM, Estado::Alta, *escalonador, aux);
                break;

            case Estado::Alta:
                break;
        }

        if (escalonador->isEmpty()) {
            fimSimulacao = true;
        }
    }
    delete escalonador;
}

void Procedimento::estatisticas()
{
    for (int i = 0; i < qnt_pacientes; ++i) {
        pacientes[i]->print();
    }
}

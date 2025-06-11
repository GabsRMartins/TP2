#include <ctime>
#include <iostream>

struct Data {
    std::tm tm_data{}; // Estrutura de tempo da biblioteca padrão

    Data() {
        tm_data = {};
    }

    Data(int ano, int mes, int dia, int hora) {
        tm_data = {};
        tm_data.tm_year = ano - 1900; // Ano desde 1900
        tm_data.tm_mon = mes - 1;    // Mês: 0 = janeiro
        tm_data.tm_mday = dia;       // Dia do mês
        tm_data.tm_hour = hora;      // Hora
        tm_data.tm_min = 0;          // Minuto (fixo em 0)
        tm_data.tm_sec = 0;          // Segundo (fixo em 0)
    
    }

    // Obtém o timestamp da data
    time_t toTimestamp() const {
        std::tm tm_copy = tm_data; // Faz uma cópia local de tm_data
        return mktime(&tm_copy);   // Usa a cópia para criar o timestamp
    }

    // Comparação usando timestamps
    bool operator<(const Data& other) const {
        return toTimestamp() < other.toTimestamp();
    }

    bool operator>(const Data& other) const {
        return toTimestamp() > other.toTimestamp();
    }

    bool operator<=(const Data& other) const {
        return toTimestamp() <= other.toTimestamp();
    }

    bool operator>=(const Data& other) const {
        return toTimestamp() >= other.toTimestamp();
    }

    bool operator==(const Data& other) const {
        return toTimestamp() == other.toTimestamp();
    }

    bool operator!=(const Data& other) const {
        return toTimestamp() != other.toTimestamp();
    }

   void print() const {
    // Array com os nomes dos dias da semana
    const char* diasSemana[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    // Array com os nomes dos meses
    const char* meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Obtém o dia da semana
    time_t timestamp = toTimestamp();
    std::tm* tempo = localtime(&timestamp);

    std::cout << diasSemana[tempo->tm_wday] << " "           // Dia da semana
              << meses[tempo->tm_mon] << " "                // Nome do mês
              << (tm_data.tm_mday < 10 ? "0" : "")          // Dia do mês com zero à esquerda
              << tm_data.tm_mday << " " 
              << (tm_data.tm_hour < 10 ? "0" : "")          // Hora com zero à esquerda
              << tm_data.tm_hour << ":"
              << (tm_data.tm_min < 10 ? "0" : "")           // Minuto com zero à esquerda
              << tm_data.tm_min << ":"
              << (tm_data.tm_sec < 10 ? "0" : "")           // Segundo com zero à esquerda
              << tm_data.tm_sec << " " 
              << (tm_data.tm_year + 1900) <<" ";                // Ano
}

void adicionarHoras(float horas) {
    try {
        int segundos = static_cast<int>(horas * 3600);
        time_t timestamp = toTimestamp();
        timestamp += segundos;
        std::tm* novoTempo = localtime(&timestamp);
        if (novoTempo == nullptr) {
            throw std::runtime_error("Erro ao calcular nova data/hora.");
        }
        tm_data = *novoTempo;
    } catch (const std::exception& e) {
        std::cerr << "Erro em adicionarHoras: " << e.what() << "\n";
    }
}



};

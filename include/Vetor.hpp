#ifndef VETOR
#define VETOR

#include <cassert>
#include <cstddef>
#include <stdexcept>
template <typename T>

class Vetor {
private:
  T *m_buf = nullptr;
  size_t m_size = 0;
  size_t m_capacity = 0;

public:
  Vetor() = default; //quem cria pela primeira vez é o push_back
  ~Vetor(){
    if (m_buf) delete[] m_buf;
  };

  Vetor(const Vetor<T> &rhs){
if (rhs.m_buf == nullptr) {
        m_buf = nullptr;
        m_capacity = 0;
        m_size = 0;
    } else {

        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_buf = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {   // size_t tamanho para o sistema operacional ser mais proximo da
                                                // arquitetura do compilador.
            m_buf[i] = rhs.m_buf[i];
        }
    }
  }
   // Construtor de copia
  Vetor<T>& operator=(const Vetor<T> &rhs){
       // Verifica se o objeto é igual ao outro
    if (this != &rhs) {
      //Verifica se o objeto esta preenchido
        if (m_buf != nullptr) {
            delete[] m_buf;
        }
        if (rhs.m_buf == nullptr) {
            m_buf = nullptr;
            m_capacity = 0;
            m_size = 0;
        } else {
            m_capacity = rhs.m_capacity;
            m_size = rhs.m_size;
            m_buf = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {   // size_t tamanho para o sistema operacional ser mais proximo da arquitetura do compilador.
                m_buf[i] = rhs.m_buf[i];
            }
        }
    }
    return *this;
  } // Operador de assingment copy




Vetor(size_t capacidadeInicial, size_t tamanhoInicial, T valorInicial) {
    if (tamanhoInicial > capacidadeInicial) {
        throw std::invalid_argument("Tamanho inicial não pode ser maior que a capacidade.");
    }
    m_capacity = capacidadeInicial;
    m_size = tamanhoInicial;
    m_buf = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_buf[i] = valorInicial;
    }
}




  // Implementando move e assingment
  Vetor(Vetor<T> &&rhs){
     m_buf = rhs.m_buf;
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;   // passando o ownership do rhs para o objeto
    // movendo o conteudo pois o ponteiro sera destruido
    rhs.m_buf = nullptr;
  }

  Vetor<T>& operator=(Vetor<T> &&rhs){
    // Verifica se o objeto é igual ao outro
    if (this != &rhs) {
        m_buf = rhs.m_buf;
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;   // passando o ownership do rhs para o objeto
        // movendo o conteudo pois o ponteiro sera destruido
        rhs.m_buf = nullptr;
    }
    return *this;
  };

  void push_back(const T& e) {
    if (m_buf == nullptr) {
        m_capacity = 2;   // Capacidade inicial arbitrária
        m_buf = new T[m_capacity];
        m_size = 0;
    }

    if (m_size >= m_capacity) {
        m_capacity *= 2;
        T* newbuf = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i) {
            newbuf[i] = std::move(m_buf[i]);  // Movimentando elementos para evitar cópias
        }

        delete[] m_buf;
        m_buf = newbuf;
    }

    m_buf[m_size++] = e;
}

  size_t size() const {return m_size;}
  T get(size_t pos){ assert(pos < m_size); return m_buf[pos];  }
  //retorna o endereço da posição
  T& operator[](size_t index){ assert(index < m_size); return m_buf[index]; }

 const T& operator[](size_t index) const{ assert(index < m_size); return m_buf[index]; }

void pop() {
    if (m_size == 0) {
        throw std::runtime_error("Erro: Tentativa de realizar pop em um vetor vazio.");
    }
    m_buf[m_size - 1] = T();  // Define o último elemento como valor padrão
    --m_size;  // Apenas reduz o tamanho lógico
}


T& at(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index fora dos limites.");
    }
    return m_buf[index];
}




T& back() {
    assert(m_size > 0 && "Tentativa de acessar back em um vetor vazio.");
    return m_buf[m_size - 1];
}

const T& back() const {
    assert(m_size > 0 && "Tentativa de acessar back em um vetor vazio.");
    return m_buf[m_size - 1];
}



// Retorna um ponteiro para o primeiro elemento do vetor
T* begin() {
    return m_buf;  // Retorna o ponteiro para o início do array
}

// Remove o elemento na posição especificada
void erase(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index fora dos limites");
    }
    
    // Deslocando elementos para a esquerda
    for (size_t i = index; i < m_size - 1; ++i) {
        m_buf[i] = std::move(m_buf[i + 1]);
    }

    // Definir o último elemento para um valor padrão para evitar lixo de memória
    m_buf[m_size - 1] = T();

    --m_size;
}



// Versão const para begin
const T* begin() const {
    return m_buf;
}




};

#endif
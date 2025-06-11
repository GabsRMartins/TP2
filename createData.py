import random
import os
from datetime import datetime, timedelta

def gerar_dados_sinteticos(num_pacientes=20, pasta_saida="test_input"):
    # Criar a pasta de saída se não existir
    os.makedirs(pasta_saida, exist_ok=True)

    # Gerar tempos médios e quantidades de procedimentos
    tempos_procedimentos = [
        (0.2, 3),  # Triagem
        (0.5, 5),  # Atendimento
        (0.1, 10), # Medidas hospitalares
        (0.05, 5), # Testes laboratoriais
        (0.5, 20),# Exames de imagem
        (0.05, 5), # Instrumentos/medicamentos
    ]

    # Configuração inicial de tempo
    data_inicial = datetime(2017, 3, 21, 2, 0)  # Começa em 21 de março de 2017 às 2h
    pacientes = []
    
    for i in range(num_pacientes):
        id_paciente = f"{9600008+i}"
        
        # Definir alta: 65% não recebem alta (0), 35% recebem alta (1)
        alta = 0 if random.random() < 0.65 else 1  

        # Determinar a chegada com um avanço de até 3 horas do último paciente
        incremento = timedelta(hours=random.randint(0, 3))


        data_atual = data_inicial + incremento
        data_inicial = data_atual  # Atualizar para a próxima iteração
        
        # Se passar de um certo limite de dias no mês, avança o mês/ano
        if data_atual.day > 28:  # Evita problemas com fevereiro
            novo_mes = data_atual.month + 1
            novo_ano = data_atual.year
            if novo_mes > 12:
                novo_mes = 1
                novo_ano += 1
            data_inicial = datetime(novo_ano, novo_mes, 1, 2, 0)

        ano, mes, dia, hora = data_atual.year, data_atual.month, data_atual.day, data_atual.hour
        grau_urgencia = random.randint(0, 2)  # Verde (0), Amarelo (1), Vermelho (2)

        medidas_hospitalares = random.randint(0, 10)
        testes_laboratorio = random.randint(0, 20)
        exames_imagem = random.randint(0, 7)
        instrumentos_medicamentos = random.randint(0, 50)

        pacientes.append(
            f"{id_paciente} {alta} {ano} {mes} {dia} {hora} {grau_urgencia} "
            f"{medidas_hospitalares} {testes_laboratorio} {exames_imagem} {instrumentos_medicamentos}"
        )

    # Criar saída formatada
    saida = "\n".join([f"{t[0]} {t[1]}" for t in tempos_procedimentos])
    saida += f"\n{num_pacientes}\n"
    saida += "\n".join(pacientes)

    # Criar o nome do arquivo e salvar na pasta
    nome_arquivo = os.path.join(pasta_saida, f"input_{num_pacientes}.txt")
    with open(nome_arquivo, "w") as f:
        f.write(saida)

    print(f"Arquivo salvo: {nome_arquivo}")

# Exemplo de uso

gerar_dados_sinteticos(10000)

for j in range(25000, 1000001, 25000):
    gerar_dados_sinteticos(j)

# 🐧 Linux Resource Monitor

![Language](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

Um monitor de recursos de sistema leve, eficiente e modular, desenvolvido puramente em **C** para ambientes Linux. 

Este projeto interage diretamente com o **Kernel Space** através do sistema de arquivos virtual `/proc`, realizando a extração, parsing e cálculo de métricas em tempo real sem dependências de bibliotecas externas.

---

## 📸 Demonstração

O monitor executa diretamente no terminal (TUI), detectando automaticamente o número de núcleos do processador e exibindo tráfego de rede em tempo real.

```text
=== SYSTEM MONITOR (Cores: 4) ===

CPU Global:  18.5% [###                 ]

--- Cores ---
Core 0:  12.0%      Core 1:  24.5%
Core 2:   5.0%      Core 3:  32.0%

--- Memória ---
RAM: 45.2% [#########           ] (7232/16000 MB)

--- Rede (Total) ---
Download:   1250.45 KB/s
Upload:      350.20 KB/s

🚀 Funcionalidades

    Monitoramento Multi-Core: Detecção automática de núcleos (via sysconf) e monitoramento individual de carga por thread de hardware.

    Estatísticas de Rede: Cálculo de velocidade de Download/Upload em tempo real lendo /proc/net/dev.

    Algoritmo de CPU Preciso: Cálculo de utilização baseado em deltas de tempo (Jiffies) entre leituras do kernel.

    Gerenciamento de Memória: Parsing de /proc/meminfo para categorizar memória total, disponível e em uso.

    Interface Otimizada: Atualização de tela sem "flicker" utilizando códigos de escape ANSI e buffer de saída.

    Zero Dependências: Funciona em qualquer distribuição Linux moderna apenas com a biblioteca padrão (libc).

🧠 Arquitetura e Decisões Técnicas

Este projeto demonstra conceitos avançados de Systems Programming:
1. Filosofia "Tudo é um Arquivo"

O software não utiliza APIs de alto nível, mas sim a interface direta do Kernel:

    /proc/stat: Métricas de CPU (Global e por núcleo).

    /proc/meminfo: Paginação e memória física.

    /proc/net/dev: Bytes transmitidos e recebidos pelas interfaces de rede.

2. Gerenciamento de Memória Dinâmica

Para suportar o monitoramento individual de núcleos ("Per-core monitoring"), o programa não utiliza arrays fixos.

    O número de núcleos é consultado em tempo de execução via sysconf(_SC_NPROCESSORS_ONLN).

    Estruturas de dados são alocadas dinamicamente (malloc) para armazenar os estados anteriores e atuais de cada núcleo, garantindo escalabilidade de um Raspberry Pi a um Servidor Xeon.

3. Estrutura Modular

O código segue padrões de organização para facilitar a manutenção:
Snippet de código

.
├── include/        # Contratos e definições (.h)
│   ├── cpu.h       # Estruturas de CPU
│   ├── memory.h    # Estruturas de Memória
│   ├── network.h   # Estruturas de Rede
│   └── monitor.h   # Utils gerais
├── src/            # Implementação da lógica (.c)
│   ├── main.c      # Loop principal e orquestração
│   ├── cpu.c       # Lógica de parsing e cálculo de deltas
│   ├── memory.c    # Leitura de memória
│   └── network.c   # Cálculo de throughput de rede
├── obj/            # Arquivos objeto compilados (.o)
├── bin/            # Executável final
└── Makefile        # Automação de build

🛠️ Instalação e Execução
Pré-requisitos

    GCC (GNU Compiler Collection)

    Make

Como rodar

Clone o repositório e utilize o Makefile incluído:
Bash

# 1. Compilar o projeto (Gera o executável na pasta bin/)
make

# 2. Rodar o monitor
make run

# (Opcional) Limpar arquivos temporários
make clean

👨‍💻 Autor

Desenvolvido por André Luis. Projeto criado para fins de estudo aprofundado em Estrutura de Dados, Ponteiros e Linux Internals.
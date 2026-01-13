# 🐧 Linux Resource Monitor

![Language](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

Um monitor de recursos de sistema leve, eficiente e modular, desenvolvido em **C** para ambientes Linux. 

Este projeto interage diretamente com o **Kernel** através do sistema de arquivos virtual `/proc`, realizando a extração e cálculo de métricas em tempo real sem dependências de bibliotecas externas pesadas.

---

## 📸 Demonstração

O monitor executa diretamente no terminal (TUI - Text User Interface), com atualização em tempo real e visualização gráfica via caracteres ASCII.

```text
=== MONITOR DE RECURSOS LINUX (Ctrl+C para sair) ===

[CPU] Uso: 12.50%
[#####               ]

[MEMORIA] Uso: 45.20% 
   Total: 16000 MB
   Usado: 7232 MB
   Livre: 8768 MB
🚀 Funcionalidades
Monitoramento de CPU: Algoritmo preciso que calcula a utilização baseada em deltas de tempo lidos de /proc/stat.

Gerenciamento de Memória: Parsing eficiente de /proc/meminfo para categorizar memória total, disponível e em uso.

Interface Limpa: Atualização de tela sem "flicker" utilizando códigos de escape ANSI.

Zero Dependências: Funciona em qualquer distribuição Linux com a libc padrão.

Build System Profissional: Automação via Makefile com gerenciamento de dependências e separação de objetos.

🧠 Arquitetura e Decisões Técnicas
Este projeto foi desenvolvido com foco em Systems Programming e performance.

1. Filosofia "Tudo é um Arquivo"
Ao invés de usar APIs de alto nível, o software lê diretamente os arquivos virtuais do Kernel:

/proc/stat: Para métricas brutas do processador.

/proc/meminfo: Para estatísticas de paginação e memória física.

2. Algoritmo de Cálculo da CPU
O Linux não fornece a porcentagem de CPU pronta. O cálculo é feito matematicamente:

Leitura dos contadores de ciclos (user, nice, system, idle) no tempo T0.

Sleep (intervalo de amostragem).

Leitura dos contadores no tempo T1.

Cálculo do Delta (Diferença) entre T1 e T0 para determinar a porcentagem de tempo que a CPU passou processando vs ociosa.

3. Organização Modular
O código segue padrões de mercado para facilitar a manutenção e escalabilidade:

Snippet de código

.
├── include/        # Contratos e definições (.h)
│   ├── cpu.h
│   ├── memory.h
│   └── monitor.h
├── src/            # Implementação da lógica (.c)
│   ├── main.c      # Loop principal e orquestração
│   ├── cpu.c       # Lógica de parsing da CPU
│   ├── memory.c    # Lógica de parsing de Memória
│   └── utils.c     # Helpers de UI
├── obj/            # Arquivos objeto compilados (.o)
├── bin/            # Executável final
└── Makefile        # Script de automação de build
🛠️ Instalação e Execução
Pré-requisitos
GCC (GNU Compiler Collection)

Make

Como rodar
Clone este repositório e execute os comandos abaixo na raiz do projeto:

Bash

# 1. Compilar o projeto (Gera o executável na pasta bin/)
make

# 2. Rodar o monitor
make run

# (Opcional) Limpar arquivos temporários e binários
make clean
🔮 Roadmap (Próximos Passos)
[ ] Implementar monitoramento individual por núcleo (Multi-core parsing).

[ ] Adicionar estatísticas de Rede (Bytes enviados/recebidos).

[ ] Adicionar suporte a argumentos de linha de comando (ex: ./monitor --refresh 2).

[ ] Criar modo daemon para execução em background.

👨‍💻 Autor
Desenvolvido por André Luis. Projeto criado para fins de estudo aprofundado em Estrutura de Dados, C e Linux Internals.


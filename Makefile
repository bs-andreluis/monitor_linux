# --- Variáveis de Compilação ---
# CC: O compilador que vamos usar
CC = gcc

# CFLAGS: Flags de compilação
# -Wall -Wextra: Habilita avisos (warnings) para ajudar a achar bugs.
# -g: Adiciona informações de debug (essencial para usar o gdb ou valgrind depois).
# -Iinclude: Diz ao gcc para procurar arquivos .h na pasta 'include'.
CFLAGS = -Wall -Wextra -g -Iinclude

# --- Estrutura de Pastas ---
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# --- Arquivos ---
# TARGET: O nome do nosso executável final
TARGET = $(BIN_DIR)/monitor_linux

# SRCS: Encontra todos os arquivos .c dentro da pasta src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# OBJS: Substitui a pasta src pela obj e a extensão .c por .o
# Exemplo: src/main.c vira obj/main.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Regras (Targets) ---

# Regra padrão: ao digitar apenas 'make', ele executa essa regra
all: directories $(TARGET)

# Regra de Linkagem: Junta todos os .o para criar o executável final
$(TARGET): $(OBJS)
	@echo "Linkando o executável: $@"
	$(CC) $(OBJS) -o $@
	@echo "Sucesso! Execute com: ./$(TARGET)"

# Regra de Compilação: Transforma cada .c em .o
# $< é o arquivo de entrada (.c), $@ é o arquivo de saída (.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Cria os diretórios bin e obj se não existirem
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Limpeza: Apaga os arquivos compilados (útil para recompilar do zero)
clean:
	@echo "Limpando arquivos temporários..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Atalho para rodar o programa
run: all
	@./$(TARGET)

.PHONY: all clean run directories
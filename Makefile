# Define o compilador que vamos usar (GNU C Compiler)
CC = gcc

# Define as flags de compilação:
# -g = Inclui símbolos de debug (para usar com gdb)
# -Wall = Ativa "todos" os avisos (Warnings)
# -Isrc = Diz ao compilador para procurar arquivos .h (headers) dentro da pasta src/
CFLAGS = -g -Wall -Isrc

# O nome do nosso programa executável final
TARGET = simcon

# Lista de todos os arquivos .c que compõem o nosso programa
# (conforme a estrutura do seu documento)
SRCS = src/main.c src/contact.c src/storage.c src/utils.c

# A regra "all" é a regra padrão (o que acontece quando você digita "make")
# Ela diz que nosso objetivo é construir o TARGET
all: $(TARGET)

# Esta é a regra de compilação
# Ela diz: "Para construir o $(TARGET), você precisa dos arquivos $(SRCS)"
# O comando abaixo é o que será executado:
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Uma regra "clean" (limpeza) para apagar o executável
# Você pode rodar com "make clean"
clean:
	rm -f $(TARGET)
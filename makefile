# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRC = agrotec.c funcoes.c

# Output binary
OUT = saida

EXEC = saida.exe

RELATORIO = relatorio.txt

# Default rule
all: $(OUT)
	./$(OUT)

# Link object files to create the final binary
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean rule to remove the compiled binary
clean:
	@if exist $(EXEC) del /Q $(EXEC)
	@if exist $(RELATORIO) del /Q $(RELATORIO)
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRC = agrotec.c funcoes.c

# Output binary
OUT = saida

# Default rule
all: $(OUT)
	./$(OUT)

# Link object files to create the final binary
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean rule to remove the compiled binary
clean:
	del /f /q $(OUT).exe 2>nul || exit 0
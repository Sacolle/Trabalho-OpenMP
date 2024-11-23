COMPILER=gcc

# Flags
CFLAGS=-O3 -Wall -std=gnu11 -pedantic -lm -fopenmp

# Files to compile
OBJECTS=est_matriz_seq_original.c


% : %.c
	$(COMPILER) $< $(CFLAGS) -o $@

#all: $(OBJECTS)
# $(COMPILER) $(OBJECTS) $(CFLAGS) -o $(EXE)

run: 
	./$(EXE)

clean:
	rm $(EXE)

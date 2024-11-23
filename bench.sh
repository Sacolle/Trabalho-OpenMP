#!/bin/bash

# Input files
inputs=("500x500input" "1kx1kinput" "2kx2kinput" "4kx4kinput" "6kx6kinput" "8kx8kinput" "10kx10kinput")

# Number of threads to test for paralelo.c
threads=(1 2 4 8 12 16 32)

# Compile the programs
gcc original.c -o original -lm
gcc otimizado.c -o otimizado -lm
gcc paralelizado.c -o paralelo -fopenmp -lm

# Create a results folder
mkdir -p results

# Run benchmarks
for input in "${inputs[@]}"; do
    echo "Running for input file: $input"

    # Benchmark original.c
    echo "Benchmarking original.c with $input..."
    { time ./original < "$input" > /dev/null; } 2>> "results/original_$input.log"

    # Benchmark otimizado.c
    echo "Benchmarking otimizado.c with $input..."
    { time ./otimizado < "$input" > /dev/null; } 2>> "results/otimizado_$input.log"

    # Benchmark paralelo.c
    echo "Benchmarking paralelizado.c with $input (various threads)..."
    
    # Without specifying threads (default behavior)
    echo "Default thread count:" >> "results/paralelo_$input.log"
    { time ./paralelo < "$input" > /dev/null; } 2>> "results/paralelo_$input.log"

    # With specified thread counts
    for t in "${threads[@]}"; do
        echo "Threads: $t" >> "results/paralelo_$input.log"
        OMP_NUM_THREADS=$t bash -c "{ time ./paralelo < \"$input\" > /dev/null; } 2>> \"results/paralelo_$input.log\""
    done
done

echo "Benchmarking completed. Results are in the 'results' folder."

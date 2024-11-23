#!/bin/bash
#SBATCH --job-name=generate_and_benchmark   # Job name
#SBATCH --partition=draco                  # Partition name
#SBATCH --nodes=1                          # Number of nodes
#SBATCH --ntasks=1                         # Number of tasks
#SBATCH --time=02:00:00                    # Maximum time
#SBATCH --output=%x_%j.out                 # Standard output file
#SBATCH --error=%x_%j.err                  # Standard error file

chmod +x gen_input.sh
chmod +x bench.sh

bash gen_input.sh
bash bench.sh

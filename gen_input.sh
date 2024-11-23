#!/bin/bash

# Function to generate a random matrix of specified size
generate_matrix() {
    local rows=$1
    local cols=$2
    local filename=$3

    echo "$rows $cols" > "$filename"
    awk -v rows="$rows" -v cols="$cols" 'BEGIN {
        srand();
        for (i = 1; i <= rows; i++) {
            for (j = 1; j <= cols; j++) {
                printf "%.2f ", rand() * 100;
            }
            printf "\n";
        }
    }' >> "$filename"
}

# Define matrix sizes and corresponding filenames
sizes=(500 1000 2000 4000 6000 8000 10000)
filenames=("500x500input" "1kx1kinput" "2kx2kinput" "4kx4kinput" "6kx6kinput" "8kx8kinput" "10kx10kinput")

# Generate files
for ((i = 0; i < ${#sizes[@]}; i++)); do
    rows=${sizes[i]}
    cols=${sizes[i]}
    filename=${filenames[i]}

    echo "Generating $filename with size ${rows}x${cols}..."
    generate_matrix "$rows" "$cols" "$filename"
done

echo "All input files generated successfully."

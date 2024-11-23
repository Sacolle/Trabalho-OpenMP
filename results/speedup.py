import os
import re
import matplotlib.pyplot as plt

# Define the input sizes you have data for
input_sizes = ['500x500', '1kx1k', '2kx2k', '4kx4k']

# Initialize dictionaries to store times
original_times = {}
optimized_times = {}
parallel_times = {}

# Regular expression to extract time in seconds
time_regex = re.compile(r'real\s+(\dm)?(\d+\.\d+)s')

for size in input_sizes:
    # Read original implementation time
    with open(f'original_{size}input.log', 'r') as f:
        content = f.read()
        match = time_regex.search(content)
        if match:
            minutes = match.group(1)
            seconds = float(match.group(2))
            total_time = seconds + (float(minutes.strip('m')) * 60 if minutes else 0)
            original_times[size] = total_time

    # Read optimized implementation time
    with open(f'otimizado_{size}input.log', 'r') as f:
        content = f.read()
        match = time_regex.search(content)
        if match:
            minutes = match.group(1)
            seconds = float(match.group(2))
            total_time = seconds + (float(minutes.strip('m')) * 60 if minutes else 0)
            optimized_times[size] = total_time

    # Read parallel implementation times with different thread counts
    parallel_times[size] = {}
    with open(f'paralelo_{size}input.log', 'r') as f:
        lines = f.readlines()
        thread_count = 1  # Default thread count
        for i, line in enumerate(lines):
            if 'Threads:' in line:
                thread_count_line = line.strip()
                thread_count = int(thread_count_line.split(':')[1].strip())
                # Next line should be 'real' time
                match = time_regex.search(lines[i - 3])
                if match:
                    minutes = match.group(1)
                    seconds = float(match.group(2))
                    total_time = seconds + (float(minutes.strip('m')) * 60 if minutes else 0)
                    parallel_times[size][thread_count] = total_time
            elif 'Default thread count:' in line:
                # Handle default thread count
                match = time_regex.search(lines[i + 1])
                if match:
                    minutes = match.group(1)
                    seconds = float(match.group(2))
                    total_time = seconds + (float(minutes.strip('m')) * 60 if minutes else 0)
                    parallel_times[size][thread_count] = total_time

# Calculate speedups
speedups_optimized = {size: original_times[size] / optimized_times[size] for size in input_sizes}
speedups_parallel = {}
for size in input_sizes:
    speedups_parallel[size] = {}
    for threads, time in parallel_times[size].items():
        speedups_parallel[size][threads] = original_times[size] / time

# Plotting
for size in input_sizes:
    plt.figure(figsize=(10, 6))
    threads = sorted(speedups_parallel[size].keys())
    speedups = [speedups_parallel[size][t] for t in threads]

    plt.plot(threads, speedups, marker='o', label='Parallel Implementation', color='blue')
    plt.axhline(y=speedups_optimized[size], color='green', linestyle='--', label='Optimized Implementation')
    plt.axhline(y=1, color='red', linestyle='--', label='Original Implementation')

    plt.title(f'Speedup Comparison for Input Size {size}')
    plt.xlabel('Number of Threads')
    plt.ylabel('Speedup')
    plt.legend()
    plt.grid(True)
    plt.xticks(threads)
    plt.savefig(f'speedup_{size}.png')
    plt.show()

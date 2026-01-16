#!/bin/bash

# Edit these to your liking
JSON_TARGET="results.json"
NUM_ROUNDS=20

# Update build with most recent changes
cmake --build build --config Release

# Run benchmark
if [ "$1" == "json" ]; then
    ./build/tsp_bench --benchmark_repetitions=$NUM_ROUNDS --benchmark_format=json > $JSON_TARGET
    echo "Exported results to $JSON_TARGET."
else
    ./build/tsp_bench --benchmark_repetitions=$NUM_ROUNDS
fi

#!/bin/bash

JSON_TARGET="results.json"

# Update build with most recent changes
cmake --build build --config Release

# Run benchmark
if [ "$1" == "json" ]; then
    ./build/tsp_bench --benchmark_format=json > $JSON_TARGET
    echo "Exported results to $JSON_TARGET."
else
    ./build/tsp_bench
fi

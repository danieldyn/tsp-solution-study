#!/bin/bash

# Update build with most recent changes
cmake --build build --config Release

# Run benchmark
./build/tsp_bench

#!/bin/bash

# Generate files to be compared
./build/generate_refs
./build/generate_outs

# Run the comparator program
./build/compare_results


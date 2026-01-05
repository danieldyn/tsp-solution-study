#!/bin/bash

echo "Setting up environment..."

# Make sure CMake is installed for the real actions
echo "Making sure you have CMake installed..."
if ! [ -x "$(command -v cmake)" ]; then
    echo "CMake not found. Installing..."
    sudo apt update && sudo apt install -y cmake
fi

echo "Creating the 'build' directory with Google Benchmark..."

# Start the build directory from zero
rm -rf build

# Build Google Benchmark
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

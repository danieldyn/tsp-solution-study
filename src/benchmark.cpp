#include <benchmark/benchmark.h>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "brute_force_tsp.hpp"
#include "held_karp_tsp.hpp"
#include "greedy_tsp.hpp"

#define TOTAL_TESTS 25
#define BRUTE_FORCE_NMAX 13

// Global cache to avoid reloading files for every iteration
std::map<int, std::vector<std::vector<int>>> data_cache;

std::vector<std::vector<int>>& load_test_file(int file_num) {
    // Check cache first
    if (data_cache.find(file_num) != data_cache.end()) {
        return data_cache[file_num];
    }

    // Construct path using the CMake macro
    std::stringstream ss;
    // TEST_DATA_DIR is defined by CMake
    ss << TEST_DATA_DIR << "test" << std::setw(2) << std::setfill('0') << file_num << ".in";
    std::string path = ss.str();

    std::ifstream file(path);
    if (!file.is_open()) {
        std::string err = "Could not open file: " + path;
        throw std::runtime_error(err);
    }

    int n, m;
    if (!(file >> n >> m)) { 
        throw std::runtime_error("Invalid file format in " + path);
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
    for (int i = 0; i < n; ++i) matrix[i][i] = 0;

    for (int k = 0; k < m; ++k) {
        int u, v, c;
        file >> u >> v >> c;
        // Basic bounds check to prevent segfaults
        if (u >= 0 && u < n && v >= 0 && v < n) {
            matrix[u][v] = c;
            matrix[v][u] = c; // Assuming undirected graph
        }
    }
    
    // Store in cache
    data_cache[file_num] = matrix;
    return data_cache[file_num];
}

// BENCHMARKS

static void BM_BruteForce(benchmark::State& state) {
    try {
        auto& data = load_test_file(state.range(0));

        // Skip if N > BRUTE_FORCE_NMAX to prevent wasting time
        if (data.size() > BRUTE_FORCE_NMAX) {
            state.SkipWithError("Skipped: Brute Force too slow for N > 13");
            return;
        }

        for (auto _ : state) {
            benchmark::DoNotOptimize(brute_force_tsp(data));
        }
        state.SetLabel("N=" + std::to_string(data.size()));
    } catch (const std::exception& e) {
        state.SkipWithError(e.what());
    }
}
BENCHMARK(BM_BruteForce)->DenseRange(1, TOTAL_TESTS);

static void BM_Greedy(benchmark::State& state) {
    try {
        auto& data = load_test_file(state.range(0));
        for (auto _ : state) {
            benchmark::DoNotOptimize(greedy_tsp(data));
        }
        state.SetLabel("N=" + std::to_string(data.size()));
    } catch (const std::exception& e) {
        state.SkipWithError(e.what());
    }
}
BENCHMARK(BM_Greedy)->DenseRange(1, TOTAL_TESTS);

static void BM_HeldKarp(benchmark::State& state) {
    try {
        auto& data = load_test_file(state.range(0));
        for (auto _ : state) {
            benchmark::DoNotOptimize(held_karp_tsp(data));
        }
        state.SetLabel("N=" + std::to_string(data.size()));
    } catch (const std::exception& e) {
        state.SkipWithError(e.what());
    }
}
BENCHMARK(BM_HeldKarp)->DenseRange(1, TOTAL_TESTS);

BENCHMARK_MAIN();

#include <benchmark/benchmark.h>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include "brute_force_tsp.hpp"
#include "held_karp_tsp.hpp"
#include "greedy_tsp.hpp"

std::map<int, std::vector<std::vector<int>>> data_cache;

std::vector<std::vector<int>>& load_test_file(int file_num) {
    if (data_cache.find(file_num) == data_cache.end()) {
        std::stringstream ss;
        ss << "tests/in/test" << std::setw(2) << std::setfill('0') << file_num << ".in";
        
        std::ifstream file(ss.str());
        if (!file.is_open()) {
            throw std::runtime_error("Could not open " + ss.str());
        }

        int n, m;
        if (!(file >> n >> m)) { 
            throw std::runtime_error("Invalid file format in " + ss.str());
        }

        // Initialize with SAFE_INT 
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
        for (int i = 0; i < n; ++i) matrix[i][i] = 0;

        // Load Edges
        for (int k = 0; k < m; ++k) {
            int u, v, c;
            file >> u >> v >> c;
            if (u < n && v < n) {
                matrix[u][v] = c;
                matrix[v][u] = c;
            }
        }
        
        data_cache[file_num] = matrix;
    }
    return data_cache[file_num];
}

// Benchmark Brute Force
static void BM_BruteForce(benchmark::State& state) {
    auto& data = load_test_file(state.range(0));
    
    // Bruteforce limitation
    if (data.size() > 12) {
        state.SkipWithError("Brute force too slow for N > 12");
        return;
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(brute_force_tsp(data));
    }
    state.SetLabel("N=" + std::to_string(data.size()));
}
// TRY to Run Brute Force on all 25 tests
BENCHMARK(BM_BruteForce)->DenseRange(1, 25);


// Benchmark Greedy (Nearest Neighbor)
static void BM_Greedy(benchmark::State& state) {
    auto& data = load_test_file(state.range(0));
    
    // Greedy is extremely fast, no limitation needed
    for (auto _ : state) {
        benchmark::DoNotOptimize(greedy_tsp(data));
    }
    state.SetLabel("N=" + std::to_string(data.size()));
}
// Run Greedy on all 25 tests
BENCHMARK(BM_Greedy)->DenseRange(1, 25);


// Benchmark Held-Karp
static void BM_HeldKarp(benchmark::State& state) {
    auto& data = load_test_file(state.range(0));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(held_karp_tcp(data));
    }
    state.SetLabel("N=" + std::to_string(data.size()));
}
// Run Held-Karp on all 25 tests
BENCHMARK(BM_HeldKarp)->DenseRange(1, 25);

BENCHMARK_MAIN();
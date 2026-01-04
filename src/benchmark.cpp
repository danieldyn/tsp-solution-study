#include <benchmark/benchmark.h>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include "brute_force_tsp.hpp"
#include "held_karp_tsp.hpp"

std::map<int, std::vector<std::vector<int>>> data_cache;

std::vector<std::vector<int>>& load_test_file(int file_num) {
    if (data_cache.find(file_num) == data_cache.end()) {
        std::stringstream ss;
        ss << "tests/in/test" << std::setw(2) << std::setfill('0') << file_num << ".in";
        
        std::ifstream file(ss.str());
        if (!file.is_open()) {
            throw std::runtime_error("Could not open " + ss.str());
        }

        int n;
        file >> n;
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                file >> matrix[i][j];
        
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
        benchmark::DoNotOptimize(bf_tcp(data));
    }
    state.SetLabel("N=" + std::to_string(data.size()));
}
// TRY to Run Brute Force on all 25 tests
BENCHMARK(BM_BruteForce)->DenseRange(1, 25);

// Benchmark Held-Karp
static void BM_HeldKarp(benchmark::State& state) {
    auto& data = load_test_file(state.range(0));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(hk_tcp(data));
    }
    state.SetLabel("N=" + std::to_string(data.size()));
}
// Run Held-Karp on all 25 tests
BENCHMARK(BM_HeldKarp)->DenseRange(1, 25);

BENCHMARK_MAIN();
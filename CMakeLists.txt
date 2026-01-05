cmake_minimum_required(VERSION 3.15)
project(TSP_Benchmark)

# Disable Google Benchmark's internal tests
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppress benchmark testing" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Suppress benchmark gtest" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "Download dependencies" FORCE)

# Dependencies
include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
FetchContent_MakeAvailable(googlebenchmark)

# Shared Library (Algorithms)
add_library(tsp_core 
    src/brute_force_tsp.cpp 
    src/greedy_tsp.cpp 
    src/held_karp_tsp.cpp
)
target_include_directories(tsp_core PUBLIC src/include)

# Main Benchmark
add_executable(tsp_bench src/benchmark.cpp)
target_link_libraries(tsp_bench PRIVATE tsp_core benchmark::benchmark)
target_compile_definitions(tsp_bench PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/in/")

# Utility Tools
# 1. Generate References
add_executable(generate_refs tests/generate_refs.cpp)
target_link_libraries(generate_refs PRIVATE tsp_core)
target_compile_definitions(generate_refs PRIVATE 
    TEST_IN_DIR="${CMAKE_SOURCE_DIR}/tests/in/"
    TEST_REF_DIR="${CMAKE_SOURCE_DIR}/tests/ref/"
)

# 2. Generate Outputs
add_executable(generate_outs tests/generate_outs.cpp)
target_link_libraries(generate_outs PRIVATE tsp_core)
target_compile_definitions(generate_outs PRIVATE 
    TEST_IN_DIR="${CMAKE_SOURCE_DIR}/tests/in/"
    TEST_OUT_DIR="${CMAKE_SOURCE_DIR}/tests/out/"
)

# 3. Compare Results
add_executable(compare_results tests/compare_results.cpp)
target_compile_definitions(compare_results PRIVATE 
    TEST_OUT_DIR="${CMAKE_SOURCE_DIR}/tests/out/"
    TEST_REF_DIR="${CMAKE_SOURCE_DIR}/tests/ref/"
)

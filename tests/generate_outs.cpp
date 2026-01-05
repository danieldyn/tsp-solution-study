#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <string>

#include "greedy_tsp.hpp"

#define TOTAL_TESTS 25

void populate_out(int test_num) {
    // Construct paths safely
    std::stringstream ss_id;
    ss_id << std::setw(2) << std::setfill('0') << test_num;
    std::string id = ss_id.str();

    std::string in_path = std::string(TEST_IN_DIR) + "test" + id + ".in";
    std::string out_path = std::string(TEST_OUT_DIR) + "test" + id + ".out";

    std::ifstream fin(in_path);
    if (!fin) {
        std::cerr << "Skipping missing file: " << in_path << std::endl;
        return;
    }

    int n, m;
    if (!(fin >> n >> m)) return;
    
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
    for(int i = 0; i < n; i++) matrix[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        fin >> u >> v >> c;
        if (u < n && v < n) matrix[u][v] = matrix[v][u] = c;
    }

    // Run Greedy
    int greedy_result = greedy_tsp(matrix);

    // Ensure directory exists
    std::filesystem::create_directories(TEST_OUT_DIR);

    std::ofstream fout(out_path);
    fout << greedy_result;
    
    std::cout << "Generated: " << out_path << " | Cost: " << greedy_result << std::endl;
}

int main() {
    for (int i = 1; i <= TOTAL_TESTS; i++) {
        populate_out(i);
    }
    return 0;
}

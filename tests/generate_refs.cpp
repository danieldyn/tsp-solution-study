#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem>
#include <sstream>

#include "held_karp_tsp.hpp" 

#define TOTAL_TESTS 25

void make_reference(int test_num) {
    std::stringstream ss_id;
    ss_id << std::setw(2) << std::setfill('0') << test_num;
    std::string id = ss_id.str();

    std::string in_path = std::string(TEST_IN_DIR) + "test" + id + ".in";
    std::string ref_path = std::string(TEST_REF_DIR) + "test" + id + ".ref";

    std::ifstream fin(in_path);
    if (!fin) {
        std::cerr << "Skipping missing file: " << in_path << std::endl;
        return;
    }

    int n, m;
    fin >> n >> m;
    
    if (n > 22) {
        std::cout << "Skipping test" << id << " (N=" << n << ") - Too large for Held-Karp ref generation." << std::endl;
        return;
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
    for(int i = 0; i < n; i++) matrix[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        fin >> u >> v >> c;
        if (u < n && v < n) matrix[u][v] = matrix[v][u] = c;
    }

    // Solve
    int result = held_karp_tsp(matrix);

    // Ensure directory exists
    std::filesystem::create_directories(TEST_REF_DIR);

    std::ofstream fout(ref_path);
    fout << result;
    
    std::cout << "Generated: " << ref_path << " | Cost: " << result << std::endl;
}

int main() {
    for (int i = 1; i <= TOTAL_TESTS; i++) {
        make_reference(i);
    }
    return 0;
}

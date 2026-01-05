#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "greedy_tsp.hpp"

void populate_out(int test_num) {
    std::string id = (test_num < 10 ? "0" : "") + std::to_string(test_num);
    std::ifstream fin("in/test" + id + ".in");
    if (!fin) return;

    int n, m;
    fin >> n >> m;
    
    // Matrix initialized with SAFE_INT
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
    for(int i = 0; i < n; i++) matrix[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        fin >> u >> v >> c;
        if (u < n && v < n) matrix[u][v] = matrix[v][u] = c;
    }

    // Run Greedy Algorithm
    int greedy_result = greedy_tsp(matrix);

    // Save to out/ folder
    std::ofstream fout("out/test" + id + ".out");
    fout << greedy_result;
    
    std::cout << "Populated out/test" << id << ".out | Greedy Cost: " << greedy_result << std::endl;
}

int main() {
    for (int i = 1; i <= 25; i++) {
        populate_out(i);
    }
    return 0;
}
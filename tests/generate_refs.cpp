#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "held_karp_tsp.hpp"

void make_reference(int test_num) {
    std::stringstream ss_in, ss_ref;
    ss_in << "in/test" << std::setw(2) << std::setfill('0') << test_num << ".in";
    ss_ref << "ref/test" << std::setw(2) << std::setfill('0') << test_num << ".ref";

    std::ifstream fin(ss_in.str());
    if (!fin) return;

    int n, m;
    fin >> n >> m;
    
    // Initialize matrix with SAFE_INT for non-existent edges
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, SAFE_INT));
    for(int i = 0; i < n; i++) matrix[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        fin >> u >> v >> c;
        if (u < n && v < n) matrix[u][v] = matrix[v][u] = c;
    }

    // Solve using the Exact Algorithm
    int result = held_karp_tcp(matrix);

    // Save to the corresponding .ref file
    std::ofstream fout(ss_ref.str());
    fout << result;
    
    std::cout << "Generated: " << ss_ref.str() << " | Cost: " << result << std::endl;
}

int main() {
    for (int i = 1; i <= 25; i++) {
        make_reference(i);
    }
    return 0;
}
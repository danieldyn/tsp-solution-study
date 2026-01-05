#include <climits>
#include "greedy_tsp.hpp"

int greedy_tsp(std::vector<std::vector<int>>& tsp) {
    int n = tsp.size();
    if (n <= 1) return 0;

    int sum = 0;
    int current_city = 0;
    std::vector<bool> visited(n, false);
    visited[0] = true;

    // Visit N-1 cities
    for (int counter = 0; counter < n - 1; counter++) {
        int min_edge = SAFE_INT;
        int next_city = -1;

        // Find the nearest unvisited neighbor
        for (int j = 0; j < n; j++) {
            if (!visited[j] && tsp[current_city][j] < min_edge) {
                min_edge = tsp[current_city][j];
                next_city = j;
            }
        }

        if (next_city != -1) {
            sum += min_edge;
            visited[next_city] = true;
            current_city = next_city;
        } else {
            // Dead End
            return SAFE_INT; 
        }
    }

    if (tsp[current_city][0] >= SAFE_INT) {
        return SAFE_INT; // Return "Infinity" to signify no valid tour found
    }
    
    sum += tsp[current_city][0];

    return sum;
}
#include <iostream>
#include <climits>
#include "recursion_tsp.hpp"

int totalCost(int mask, int pos, std::vector<std::vector<int>>& cost) {
    
    int n = cost.size();
    
    // Base case: if all cities are visited, return the
    // cost to return to the starting city (0)
    if (mask == (1 << n) - 1) {
        return cost[pos][0];
    }
    int ans = INT_MAX;

    // Try visiting every city that 
    // has not been visited yet
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
              
            // If city i is not visited, visit it and
            // update the mask
            ans = std::min(ans, cost[pos][i]
                           + totalCost(mask | (1 << i), i, cost));
        }
    }
    return ans;
}

int rec_tcp(std::vector<std::vector<int>>& cost) {
        
    // Start from city 0, and only city 0 is
    // visited initially (mask = 1)
    int mask = 1, pos = 0;
    
    return totalCost(mask, pos, cost);  
}
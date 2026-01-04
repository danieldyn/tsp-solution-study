#include <iostream>
#include <algorithm>
#include <climits>
#include "held_karp_tsp.hpp"

int totalCost(int mask, int curr, std::vector<std::vector<int>>& cost, std::vector<std::vector<int>>& dp) {
    
    int n = cost.size();
    
    // Base case: if all cities are visited, return the
    // cost to return to the starting city (0)
    if (mask == (1 << n) - 1) {
        return cost[curr][0];
    }

    // If the value has already been computed, return it
    // from the dp table
    if (dp[curr][mask] != -1) {
        return dp[curr][mask];
    }

    int ans = INT_MAX;

    // Try visiting every city that has not been visited yet
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {

            // If city i is not visited 
            // Visit city i and update the mask
            ans = std::min(ans, cost[curr][i] + totalCost(mask | (1 << i), i, cost, dp));
        }
    }
    
    return dp[curr][mask] = ans;
}

int hk_tcp(std::vector<std::vector<int>>& cost) {
    int n = cost.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(1 << n, -1));
    
    // Start from city 0, with only city 0
    // visited initially (mask = 1)
    int mask = 1, curr = 0;
    
    return totalCost(mask, curr, cost, dp);
}

// C++ program to find the shortest possible route
// that visits every city exactly once and returns to
// the starting point

#include <bits/stdc++.h>
#include "brute_force_tsp.hpp"

int bf_tcp(std::vector<std::vector<int>> &cost) {

    // Number of nodes
    int numNodes = cost.size();
    std::vector<int> nodes;

    // Initialize the nodes excluding the fixed 
    // starting point (node 0)
    for (int i = 1; i < numNodes; i++)
        nodes.push_back(i);

    int minCost = INT_MAX;

    // Generate all permutations of the remaining nodes
    do {
        int currCost = 0;

        // Start from node 0
        int currNode = 0;

        // Calculate the cost of the current permutation
        for (int i = 0; i < nodes.size(); i++) {
            currCost += cost[currNode][nodes[i]];
            currNode = nodes[i];
        }

        // Add the cost to return to the starting node
        currCost += cost[currNode][0];

        // Update the minimum cost if the current cost 
        // is lower
        minCost = std::min(minCost, currCost);

    } while (next_permutation(nodes.begin(), nodes.end()));

    return minCost;
}
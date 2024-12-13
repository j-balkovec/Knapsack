/**
 * @file BranchAndBound.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Branch and Bound algorithm for the knapsack problem.
 *         TC: O(2^n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>

#include "../main.h"

/**
 * Calculates the upper bound of the profit for a given node in the branch and bound algorithm.
 * 
 * @param u The node for which the upper bound is calculated.
 * @param n The total number of items.
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items with their weights and values.
 * @return The upper bound of the profit for the given node.
 */
int bound(Node& u, int n, int capacity, const std::vector<Item>& items) {
    if (u.weight >= capacity) return 0;

    int profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    if (j < n) {
        profitBound += (capacity - totalWeight) * items[j].value / items[j].weight;
    }

    return profitBound;
}

/**
 * Calculates the maximum profit that can be obtained by solving the Knapsack problem using the Branch and Bound algorithm.
 *
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their weights and values.
 * @return The maximum profit that can be obtained.
 */
inline int knapsackBranchAndBound(int capacity, const std::vector<Item>& items) {
    int n = items.size();

    std::vector<Item> sortedItems = items;
    std::sort(sortedItems.begin(), sortedItems.end(), compareByRatio);

    std::vector<Node> queue;
    Node u;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = 0;

    queue.push_back(u);
    int maxProfit = 0;

    while (!queue.empty()) {
        u = queue.back();
        queue.pop_back();

        if (u.level == n - 1) continue;

        Node v;
        v.level = u.level + 1;

        v.weight = u.weight + sortedItems[v.level].weight;
        v.profit = u.profit + sortedItems[v.level].value;

        if (v.weight <= capacity && v.profit > maxProfit) {
            maxProfit = v.profit;
        }

        v.bound = bound(v, n, capacity, sortedItems);
        if (v.bound > maxProfit) {
            queue.push_back(v);
        }

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, capacity, sortedItems);
        if (v.bound > maxProfit) {
            queue.push_back(v);
        }
    }

    return maxProfit;
}


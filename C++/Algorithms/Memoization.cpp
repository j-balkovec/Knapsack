/**
 * @file Memoization.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Memoization algorithm for the knapsack problem.
 *         TC: O(n * W), where n is the number of items, and W is the capacity of the knapsack.
 * 
*/

#include <iostream>
#include <vector>
#include <unordered_map>

#include "../Tools/Item.h"
#include "../main.h"

/**
 * @brief Helper function for solving the knapsack problem using memoization.
 * 
 * This function recursively calculates the maximum value that can be obtained by selecting items 
 * from a given list, considering the weight capacity of the knapsack. It uses memoization to 
 * store previously computed results and avoid redundant calculations.
 * 
 * @param capacity The remaining capacity of the knapsack.
 * @param items The list of items available for selection.
 * @param n The index of the current item being considered.
 * @param memo A map to store previously computed results.
 * @return The maximum value that can be obtained.
 */
int knapsackMemoHelper(int capacity, const std::vector<Item>& items, int n, std::unordered_map<std::string, int>& memo) {
    if (n == 0 || capacity == 0) {
        return 0;
    }

    std::string key = std::to_string(n) + "-" + std::to_string(capacity);
    
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
 
    if (items[n - 1].weight > capacity) {
        memo[key] = knapsackMemoHelper(capacity, items, n - 1, memo);
        return memo[key];
    } else {
        int includeItem = items[n - 1].value + knapsackMemoHelper(capacity - items[n - 1].weight, items, n - 1, memo);
        int excludeItem = knapsackMemoHelper(capacity, items, n - 1, memo);
        
        memo[key] = std::max(includeItem, excludeItem);
        return memo[key];
    }
}

// Wrapper
int knapsackMemoization(int capacity, const std::vector<Item>& items) {
    std::unordered_map<std::string, int> memo;
    return knapsackMemoHelper(capacity, items, items.size(), memo);
}

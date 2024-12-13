/**
 * @file DP.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Dynamic Programming algorithm for the knapsack problem.
 *         TC: O(n * W), where n is the number of items, and W is the capacity of the knapsack.
 * 
*/

#include <iostream>
#include <vector>

#include "../Tools/Item.h"
#include "../main.h"

/**
 * Calculates the maximum value that can be obtained by filling a knapsack of given capacity
 * with a given set of items using the Dynamic Programming approach.
 *
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items, where each item has a weight and a value.
 * @return The maximum value that can be obtained.
 */
int knapsackDP(int capacity, const std::vector<Item>& items) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

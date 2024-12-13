/**
 * @file Recursive.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Brute-force recursive algorithm for the knapsack problem.
 *         TC: O(2^n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>

#include "../Tools/Item.h"
#include "../main.h"

/**
 * Calculates the maximum value that can be obtained by filling a knapsack of given capacity using a recursive approach.
 * 
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items The vector of items available for selection.
 * @param n The number of items in the vector.
 * @return The maximum value that can be obtained by filling the knapsack.
 */
int knapsackRecursive(int capacity, const std::vector<Item>& items, int n) {
    if (n == 0 || capacity == 0) {
        return 0;
    }

    if (items[n - 1].weight > capacity) {
        return knapsackRecursive(capacity, items, n - 1);
    } else {
        int includeItem = items[n - 1].value + knapsackRecursive(capacity - items[n - 1].weight, items, n - 1);
        int excludeItem = knapsackRecursive(capacity, items, n - 1);
        
        return std::max(includeItem, excludeItem);
    }
}

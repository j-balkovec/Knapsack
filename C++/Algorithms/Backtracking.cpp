/**
 * @file Backtracking.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Backtracking algorithm for the knapsack problem.
 *         TC: O(2^n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>

#include "../Tools/Item.h"
#include "../main.h"

/**
 * @brief Solves the knapsack problem using backtracking.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The items to choose from.
 * @param n The number of items.
 * @param currentWeight The current weight of the knapsack.
 * @param currentValue The current value of the knapsack.
 * @param index The current index of the item.
 * @return The maximum value that can be obtained.
 */
int knapsackBacktracking(int capacity, const std::vector<Item>& items, int n, int currentWeight, int currentValue, int index) {
    if (index == n) {
        return currentValue;
    }

    int includeItem = 0;
    if (currentWeight + items[index].weight <= capacity) {
        includeItem = knapsackBacktracking(capacity, items, n, currentWeight + items[index].weight, currentValue + items[index].value, index + 1);
    }
    int excludeItem = knapsackBacktracking(capacity, items, n, currentWeight, currentValue, index + 1);

    return std::max(includeItem, excludeItem);
}

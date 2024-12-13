/**
 * @file DefensiveGreedy.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Defensive Greedy heuristic for the Knapsack problem.
 *         TC: O(n log n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>

#include "../Tools/Item.h"
#include "../Tools/Utility.h"
#include "../main.h"

/**
 * Calculates the maximum value that can be obtained by selecting items for a knapsack using the Defensive Greedy algorithm.
 *
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their respective weights and values.
 * @return The maximum value that can be obtained by selecting items for the knapsack.
 */
int defensiveGreedyKnapsack(int capacity, const std::vector<Item>& items) {
    std::vector<Item> sortedItems = items;
    std::sort(sortedItems.begin(), sortedItems.end(), compareByWeight);

    int totalValue = 0;
    int currentWeight = 0;
    std::vector<int> selectedItems;

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (currentWeight + sortedItems[i].weight <= capacity) {
            currentWeight += sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i); // Track item index
        } else {
            break;
        }
    }

    return totalValue;
}

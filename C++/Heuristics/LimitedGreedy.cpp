/**
 * @file LimitedGreedy.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Limited Greedy heuristic for the Knapsack problem.
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
 * Calculates the maximum value that can be obtained by selecting items for a knapsack using the Limited Greedy algorithm.
 * 
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their weights and values.
 * @return The maximum value that can be obtained by selecting items for the knapsack.
 */
int limitedGreedyKnapsack(int capacity, const std::vector<Item>& items) {
    std::vector<Item> sortedItems = items;
    std::sort(sortedItems.begin(), sortedItems.end(), compareByValue);

    int totalValue = 0;
    int remainingCapacity = capacity;
    std::vector<int> selectedItems;

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (remainingCapacity > 0.4 * capacity && sortedItems[i].weight <= 0.8 * remainingCapacity) {
            remainingCapacity -= sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i); // Track item index

        } else if (remainingCapacity <= 0.4 * capacity && sortedItems[i].weight <= remainingCapacity) {
            remainingCapacity -= sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i); // Track item index
        }
    }

    return totalValue;
}

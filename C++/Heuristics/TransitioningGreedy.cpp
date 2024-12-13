/**
 * @file TransitioningGreedy.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Transitioning Greedy heuristic for the Knapsack problem.
 *         TC: O(n log n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

#include "../Tools/Item.h"
#include "../Tools/Utility.h"
#include "../main.h"

/**
 * Calculates the maximum value that can be obtained by selecting items for a knapsack using the Transitioning Greedy algorithm.
 *
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their weights and values.
 * @return The maximum value that can be obtained by selecting items for the knapsack.
 */
int transitioningGreedyKnapsack(int capacity, const std::vector<Item>& items) {
    std::vector<Item> sortedItems = items;
    int totalValue = 0;
    int currentWeight = 0;
    std::vector<int> selectedItems;

    std::sort(sortedItems.begin(), sortedItems.end(), compareByValue);

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (currentWeight + sortedItems[i].weight <= 0.4 * capacity) {
            currentWeight += sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i);
            sortedItems.erase(sortedItems.begin() + i);
            --i; //<bug>: i-- won't work here
        }
    }

    std::sort(sortedItems.begin(), sortedItems.end(), compareByScore);

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (currentWeight + sortedItems[i].weight <= capacity) {
            currentWeight += sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i);
        }
    }

    return totalValue;
}

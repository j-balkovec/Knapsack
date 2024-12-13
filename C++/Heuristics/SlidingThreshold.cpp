/**
 * @file SlidingThreshold.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Sliding Threshold heuristic for the Knapsack problem.
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
 * Calculates the maximum value that can be obtained by selecting items for a knapsack
 * using the Sliding Threshold heuristic.
 *
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items The vector of items available for selection.
 * @return The maximum value that can be obtained by selecting items for the knapsack.
 */
int slidingThresholdKnapsack(int capacity, const std::vector<Item>& items) {
    int totalValue = 0;
    int currentWeight = 0;
    std::vector<int> selectedItems;
    std::vector<Item> sortedItems = items;
    std::sort(sortedItems.begin(), sortedItems.end(), compareByRatio);

    double threshold = static_cast<double>(sortedItems[0].value) / sortedItems[0].weight;

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (currentWeight + sortedItems[i].weight <= capacity) {
            currentWeight += sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i);
        }

        if (i > sortedItems.size() / 4 && selectedItems.size() <= sortedItems.size() / 4) {
            threshold *= 0.8;
        } else if (i > sortedItems.size() / 2 && selectedItems.size() <= sortedItems.size() / 8) {
            threshold *= 0.8;
        }

        if (currentWeight > capacity || static_cast<double>(sortedItems[i].value) / sortedItems[i].weight <= threshold) {
            currentWeight -= sortedItems[i].weight;
            totalValue -= sortedItems[i].value;
            selectedItems.erase(std::remove(selectedItems.begin(), selectedItems.end(), i), selectedItems.end());
        }

        if (currentWeight == capacity) {
            break;
        }
    }

    return totalValue;
}

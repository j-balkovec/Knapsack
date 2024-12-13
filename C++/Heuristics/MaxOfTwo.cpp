/**
 * @file MaxOfTwo.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Max of Two heuristic for the Knapsack problem.
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
 * Calculates the maximum value that can be obtained from a knapsack problem using two different heuristics.
 * 
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their respective values and weights.
 * @return The maximum value that can be obtained from the knapsack using the two heuristics.
 */
int maxOfTwoKnapsack(int capacity, const std::vector<Item>& items) {
    std::vector<Item> sortedItemsByValue = items;
    std::sort(sortedItemsByValue.begin(), sortedItemsByValue.end(), compareByValue);

    int totalValue1 = 0;
    int currentWeight1 = 0;
    std::vector<int> selectedItems1;

    for (size_t i = 0; i < sortedItemsByValue.size(); ++i) {
        if (currentWeight1 + sortedItemsByValue[i].weight <= capacity) {
            currentWeight1 += sortedItemsByValue[i].weight;
            totalValue1 += sortedItemsByValue[i].value;
            selectedItems1.push_back(i);
        }
    }

    std::vector<Item> sortedItemsByRatio = items;
    std::sort(sortedItemsByRatio.begin(), sortedItemsByRatio.end(), compareByRatio);

    int totalValue2 = 0;
    int currentWeight2 = 0;
    std::vector<int> selectedItems2;

    for (size_t i = 0; i < sortedItemsByRatio.size(); ++i) {
        if (currentWeight2 + sortedItemsByRatio[i].weight <= capacity) {
            currentWeight2 += sortedItemsByRatio[i].weight;
            totalValue2 += sortedItemsByRatio[i].value;
            selectedItems2.push_back(i);
        }
    }

    if (totalValue1 > totalValue2) {
        return totalValue1;
    } else {
        return totalValue2;
    }
}

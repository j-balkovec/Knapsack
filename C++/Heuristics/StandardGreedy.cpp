/**
 * @file StandardGreedy.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief The Standard Greedy heuristic for the Knapsack problem.
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
 * Calculates the maximum value that can be obtained by selecting items for a knapsack using the standard greedy algorithm.
 * 
 * @param capacity The maximum weight capacity of the knapsack.
 * @param items A vector of Item objects representing the available items with their respective weights and values.
 * @return The maximum value that can be obtained by selecting items for the knapsack.
 */
int standardGreedyKnapsack(int capacity, const std::vector<Item>& items) {
    std::vector<Item> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), compareByRatio);

    int totalValue = 0;
    int currentWeight = 0;
    std::vector<int> selectedItems;

    for (size_t i = 0; i < sortedItems.size(); ++i) {
        if (currentWeight + sortedItems[i].weight <= capacity) {
            currentWeight += sortedItems[i].weight;
            totalValue += sortedItems[i].value;
            selectedItems.push_back(i);
        }
    }

    return totalValue;
}

// Driver code for testing
// int main() {
//     int capacity = 50;
//     std::vector<Item> items = {
//         {60, 10}, {100, 20}, {120, 30} // {value, weight}
//     };

//     auto [maxValue, selectedItems] = standardGreedyKnapsack(capacity, items);

//     cout << "Maximum Value: " << maxValue << endl;
//     cout << "Selected Items (indices): ";
//     for (int idx : selectedItems) {
//         cout << idx << " ";
//     }
//     cout << endl;

//     return 0;
// }

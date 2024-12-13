/**
 * @file Utility.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief This file holds the utility functions used for sorting (think of them as lambdas).
 * 
*/
#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#include "Item.h"

/**
 * @brief Compare two items by their score in ascending order.
 * 
 * The score of an item is calculated using the formula: 
 * score = (value^3) / (weight^1.5)
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the score of item a is less than the score of item b, false otherwise.
 */
bool compareByScoreAscending(const Item& a, const Item& b) {
    double scoreA = std::pow(a.value, 3) / std::pow(a.weight, 1.5);
    double scoreB = std::pow(b.value, 3) / std::pow(b.weight, 1.5);
    return scoreA < scoreB; // Lower score comes first
}

/**
 * @brief Compares two items by their value.
 * 
 * This function is used as a comparator for sorting items in descending order of value.
 * The item with a higher value will be placed before the item with a lower value.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return True if the value of item a is greater than the value of item b, false otherwise.
 */
bool compareByValue(const Item& a, const Item& b) {
    return a.value > b.value; // Higher value comes first
}

/**
 * @brief Compares two items based on their weights.
 * 
 * This function is used as a comparator for sorting items in ascending order of weight.
 * Lighter items will come first in the sorted order.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the weight of item a is less than the weight of item b, false otherwise.
 */
bool compareByWeight(const Item& a, const Item& b) {
    return a.weight < b.weight; // Lighter items come first
}

/**
 * @brief Compare two items by their value-to-weight ratio.
 * 
 * This function calculates the value-to-weight ratio for two items and compares them.
 * The item with the higher ratio is considered to come first.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return True if the ratio of item a is greater than the ratio of item b, false otherwise.
 */
bool compareByRatio(const Item& a, const Item& b) {
    double ratioA = static_cast<double>(a.value) / a.weight;
    double ratioB = static_cast<double>(b.value) / b.weight;
    return ratioA > ratioB; // Higher ratio comes first
}

/**
 * @brief Compare two items based on their scores.
 * 
 * This function calculates the score of two items using the formula:
 * score = (value^3) / (weight^1.5)
 * The item with the higher score will be placed first.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the score of item a is greater than the score of item b, false otherwise.
 */
bool compareByScore(const Item& a, const Item& b) {
    double scoreA = std::pow(a.value, 3) / std::pow(a.weight, 1.5);
    double scoreB = std::pow(b.value, 3) / std::pow(b.weight, 1.5);
    return scoreA > scoreB; // Higher score comes first
}

#endif // UTILITY_H
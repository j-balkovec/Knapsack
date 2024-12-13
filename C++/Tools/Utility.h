/**
 * @file Utility.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief This header file holds the definitions for the utility functions used for sorting (think of them as lambdas).
 * 
*/

#ifndef UTILITY_H
#define UTILITY_H

#include "Item.h"
#include <vector>

extern bool compareByWeight(const Item& a, const Item& b);
extern bool compareByValue(const Item& a, const Item& b);
extern bool compareByScore(const Item& a, const Item& b);
extern bool compareByRatio(const Item& a, const Item& b);
extern bool compareByScoreAscending(const Item& a, const Item& b);

#endif // UTILITY_H
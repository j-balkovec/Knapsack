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
#define FMT_HEADER_ONLY

#include <chrono>
#include <utility> //pair
#include <spdlog/spdlog.h>
#include <vector>
#include <typeinfo>
#include <string>

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

#include "Item.h"

extern bool compareByWeight(const Item& a, const Item& b);
extern bool compareByValue(const Item& a, const Item& b);
extern bool compareByScore(const Item& a, const Item& b);
extern bool compareByRatio(const Item& a, const Item& b);
extern bool compareByScoreAscending(const Item& a, const Item& b);

extern std::vector<Item> parseCSVItems(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger);
extern int parseCSVCapacity(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger);

extern void displayMessage(const std::string& message, const char& type);

// ------- <C++ templates :\> ------- //
// Since they need to be visible to the compiler at compile time, they are defined in the header file

template <typename Func, typename... Args>
std::pair<std::__1::chrono::system_clock::rep, int> measureExecutionTime(Func&& func, Args&&... args) {

    auto start = std::chrono::high_resolution_clock::now();
    [[maybe_unused]]auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return std::make_pair(duration, result);
}

// ------- <C++ templates :\> ------- //

#endif // UTILITY_H
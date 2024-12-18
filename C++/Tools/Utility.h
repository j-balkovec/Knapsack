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
#include <utility>
#include <map>

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

#include "Item.h"

// log files
// const std::string_view MAIN_LOG_FILE = "../Logs/main_log.log";
// const std::string_view EXEC_TIME_LOG_FILE = "../Logs/exec_time.log";

const std::string_view MAIN_LOG_FILE = "/Users/jbalkovec/Desktop/Knapsack/Logs/main_log.log";
const std::string_view EXEC_TIME_LOG_FILE = "/Users/jbalkovec/Desktop/Knapsack/Logs/exec_time.log";
const std::string_view MIN_EXEC_TIME_LOG_FILE = "/Users/jbalkovec/Desktop/Knapsack/Logs/min_exec_time.log";

// -- <IMPORTANT> --
const unsigned int RUN_TIMES = 1;

// types of messages
const char INFO = 'I';
const char WARNING = 'W';
const char ERROR = 'E';
const char SUCCESS = 'S';
const char DEBUG = 'D';

// enum for the keys
enum DataKey {
    ITEM_1,
    ITEM_2,
    ITEM_3,
    ITEM_4,
    ITEM_5,
    ITEM_6,
    ITEM_7,
    ITEM_8,
    ITEM_9,
    ITEM_10
};

/**
* a map linking enum keys to file paths
*
* --- <note> ---
* These need to be updated every time <input_generator.py> is run
*/
const std::map<DataKey, std::string> DATA_MAP = {
    {ITEM_1, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_1_12_12_2024.csv"},
    {ITEM_2, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_2_12_12_2024.csv"},
    {ITEM_3, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_3_12_12_2024.csv"},
    {ITEM_4, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_4_12_12_2024.csv"},
    {ITEM_5, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_5_12_12_2024.csv"},
    {ITEM_6, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_6_12_12_2024.csv"},
    {ITEM_7, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_7_12_12_2024.csv"},
    {ITEM_8, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_8_12_12_2024.csv"},
    {ITEM_9, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_9_12_12_2024.csv"},
    {ITEM_10, "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_10_12_12_2024.csv"}
};

/**
* path for capacity
* --- <note> ---
* This needs to be updated every time <input_generator.py> is run
*/
const std::string_view CAPACITY = "/Users/jbalkovec/Desktop/Knapsack/Data/Capacity/Capacity_12_12_2024.csv";

extern bool compareByWeight(const Item& a, const Item& b);
extern bool compareByValue(const Item& a, const Item& b);
extern bool compareByScore(const Item& a, const Item& b);
extern bool compareByRatio(const Item& a, const Item& b);
extern bool compareByScoreAscending(const Item& a, const Item& b);

extern std::vector<Item> parseCSVItems(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger);
extern int parseCSVCapacity(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger);

extern void displayMessage(const std::string& message, const char& type);
extern std::string getFilePath(DataKey key, const std::shared_ptr<spdlog::logger>& logger);

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
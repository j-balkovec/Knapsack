/**
 * @file SimulatedAnnealing.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Entry point of the program
 * 
*/

/** --------- <prototypes> ----------
 *  --- <ALGORITHMS> ---
 * 
 * C: capacity <int>
 * I: items <const std::vector>
 * 
 * int knapsackACO(C, I) <make_object>
 * int knapsackBacktracking(C, I, int n, int currentWeight, int currentValue, int index)
 * int knapsackBranchAndBound(C, I)
 * int knapsackDP(C, I)
 * int knapsackMemoHelper(C, I, int n, std::unordered_map<std::string, int>& memo)
 * int knapsackRecursive(C, I, int n)
 * int knapsackSimulatedAnnealing(C, I, double initialTemperature, double coolingRate)
 * 
 *  --- <HEURISTICS> ---
 * 
 * C: capacity <int>
 * I: items <const std::vector>
 * 
 * int dealStingyKnapsack(C, I)
 * int defensiveGreedyKnapsack(C, I)
 * int heavyGreedyKnapsack(C, I)
 * int limitedGreedyKnapsack(C, I)
 * int maxOfTwoKnapsack(C, I)
 * int scoredGreedyKnapsack(C, I)
 * int slidingThresholdKnapsack(C, I)
 * int standardGreedyKnapsack(C, I)
 * int transitioningGreedyKnapsack(C, I)
 * int weightStingyKnapsack(C, I)
*/


#include "Tools/Item.h"
#include "Tools/Utility.h"

#include "main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

const std::string MAIN_LOG = "../Logs/main_log.log";

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
const std::string CAPACITY = "/Users/jbalkovec/Desktop/Knapsack/Data/Capacity/Capacity_12_12_2024.csv";

/**
 * @brief Retrieves the file path corresponding to a given DataKey.
 *
 * This function retrieves the file path associated with the specified DataKey
 * from the DATA_MAP. It uses the spdlog library to log messages and errors.
 * If the logger is not initialized, it creates a logger named "main_log" with
 * a basic logger configuration. Logs errors in case of invalid key access.
 *
 * @param key The DataKey enumeration value for which the file path is requested.
 * @return The file path corresponding to the given key.
 * @throws std::out_of_range if the key does not exist in the map.
 *
 * Example usage:
 * @code
 * std::string path = getFilePath(ITEM_3);
 * std::cout << "File path: " << path << std::endl;
 * @endcode
 */
std::string getFilePath(DataKey key) {
    auto logger = spdlog::get("main_log");
    if (!logger) {
        logger = spdlog::basic_logger_mt("main_log", MAIN_LOG);
        logger->set_level(spdlog::level::info); 
    }
    try {
        auto it = DATA_MAP.find(key);
        if (it != DATA_MAP.end()) {
            return it->second;
        }
        throw std::out_of_range("Invalid key");
    } catch (const std::out_of_range &e) {
        logger->error("Error: {}", e.what());   
    }
}



int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
    auto logger = spdlog::get("main_log");
    if (!logger) {
        logger = spdlog::basic_logger_mt("main_log", MAIN_LOG);
        logger->set_level(spdlog::level::info); 
    }

    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1)); //works
    int capacity = parseCSVCapacity(CAPACITY);

    std::cout << knapsackDP(capacity, items) << std::endl;
    int time = measureExecutionTime(knapsackDP, capacity, items);
}

/*
#include <future>
#include <vector>
#include <iostream>

void executeAndLog(const std::string& name, int (*algorithm)(int, const std::vector<Item>&), int capacity, const std::vector<Item>& items) {
    int result = algorithm(capacity, items);
    std::cout << name << " result: " << result << std::endl;
}

int main() {
    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1));
    int capacity = parseCSVCapacity(CAPACITY);

    // Algorithms to run
    std::vector<std::pair<std::string, int(*)(int, const std::vector<Item>&)>> algorithms = {
        {"Knapsack DP", knapsackDP},
        {"Knapsack Branch-and-Bound", knapsackBranchAndBound},
        {"Knapsack Backtracking", knapsackBacktracking},
        {"Knapsack Recursive", knapsackRecursive},
        {"Standard Greedy", standardGreedyKnapsack},
        {"Weight Stingy", weightStingyKnapsack},
        {"Sliding Threshold", slidingThresholdKnapsack},
        {"Scored Greedy", scoredGreedyKnapsack}
    };

    // Launch threads for each algorithm
    std::vector<std::future<void>> futures;
    for (const auto& algo : algorithms) {
        futures.emplace_back(std::async(std::launch::async, executeAndLog, algo.first, algo.second, capacity, items));
    }

    // Wait for all threads to finish
    for (auto& future : futures) {
        future.get();
    }

    return 0;
}
*/
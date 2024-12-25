/**
 * @file Benchmark.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the function implementations used for execution of the wrappers
 * 
*/

// DOC

#include "Item.h"
#include "Utility.h"
#include "Logger.h"       //-- <new> --
#include "Benchmark.h"    //-- <new> --

#include "main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <unistd.h>
#include <climits>
#include <cmath>
#include <functional>
#include <thread>

/** --------- <prototypes - copy> ----------
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

/**
 * @brief Function to setup the Ant Colony.
 * 
 * This function initializes and returns an instance of the AntColony class with the specified parameters.
 * 
 * @return An instance of the AntColony class.
 * @note thoroughly tested and found the optimal parameters for my use case
 */
AntColony setupColony() {
    constexpr int numAnts = 50;
    constexpr int numIterations = 1500;
    constexpr double alpha = 1.5;
    constexpr double beta = 4;
    constexpr double evaporationRate = 0.7;

    return AntColony(numAnts, numIterations, alpha, beta, evaporationRate);
}

/**
 * @brief Parses the items and capacity from a CSV file.
 * 
 * This function reads the items from a CSV file using the parseCSVItems() function and sets the capacity using the parseCSVCapacity() function.
 * 
 * @param mainLogger A shared pointer to the logger object.
 * @param capacity The capacity of the knapsack.
 * @return A vector of Item objects representing the parsed items.
 */
std::vector<Item> parseItemsAndCapacity(std::shared_ptr<spdlog::logger>& mainLogger, int& capacity) {
    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1, mainLogger), mainLogger);
    capacity = parseCSVCapacity(CAPACITY.data(), mainLogger);
    return items;
}

/** -- <make better> --
 * @brief Executes various algorithms and heuristics for the knapsack problem.
 * 
 * This function executes multiple algorithms and heuristics for solving the knapsack problem.
 * It takes a vector of items, knapsack capacity, a map to store the minimum execution times,
 * and a logger for logging the execution times.
 * 
 * @param items The vector of items to be considered for the knapsack problem.
 * @param capacity The capacity of the knapsack.
 * @param minExecutionTimes A map to store the minimum execution times for each algorithm/heuristic.
 * @param execTimeLogger A shared pointer to the logger for logging the execution times.
 * @return A pair of booleans indicating whether the algorithms and heuristics were successfully logged.
 */
std::pair<bool, bool> executeAlgorithmsAndHeuristics(const std::vector<Item>& items, 
                                                     int capacity, 
                                                     std::map<std::string, double>& minExecutionTimes, 
                                                     std::shared_ptr<spdlog::logger>& execTimeLogger) {

    logSeparator(execTimeLogger, 'A'); // TO BE REMOVED

    AntColony colony = setupColony();

    bool log_aco = knapsackACOWrapper(colony, capacity, items, minExecutionTimes, execTimeLogger);
    bool log_dp = knapsackDPWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_memo = knapsackMemoizationWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_annealing = knapsackSimulatedAnnealingWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    //bool log_recursive = knapsackRecursiveWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    //bool log_backtracking = knapsackBacktrackingWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_branch_and_bound = knapsackBranchAndBoundWrapper(capacity, items, minExecutionTimes, execTimeLogger);

    logSeparator(execTimeLogger, 'H'); // TO BE REMOVED

    bool log_deal_stingy = knapsackDealStingyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_defensive = knapsackDefensiveGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_heavy = knapsackHeavyGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_limited = knapsackLimitedGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_max_of_two = knapsackMaxOfTwoWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_scored = knapsackScoredGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_sliding_threshold = knapsackSlidingThresholdWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_standard_greedy = knapsackStandardGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_transitioning_greedy = knapsackTransitioningGreedyWrapper(capacity, items, minExecutionTimes, execTimeLogger);
    bool log_weight_stingy = knapsackWeightStingyWrapper(capacity, items, minExecutionTimes, execTimeLogger);

    bool logged_algorithms = log_aco && 
                             log_dp && 
                             log_memo && 
                             log_annealing && 
                             log_branch_and_bound;
                             //log_recursive && 
                             //log_backtracking;
    bool logged_heuristics = log_deal_stingy && 
                             log_defensive && 
                             log_heavy && 
                             log_limited && 
                             log_max_of_two &&
                             log_scored && 
                             log_sliding_threshold && 
                             log_standard_greedy && 
                             log_transitioning_greedy &&
                             log_weight_stingy;

    return std::make_pair(logged_algorithms, logged_heuristics);   
}

/**
 * @brief Benchmark the functions for solving the knapsack problem.
 * 
 * This function benchmarks the algorithms and heuristics for solving the knapsack problem.
 * It initializes the loggers, sets up the minimum execution times, parses the items and capacity,
 * executes the algorithms and heuristics, and logs the execution results.
 */
void BenchmarkFunctions() {
    std::shared_ptr<spdlog::logger> execTimeLogger, mainLogger, minExecTimeLogger;
    initializeLoggers(execTimeLogger, mainLogger, minExecTimeLogger);

    std::map<std::string, double> minExecutionTimes = setupMinExecutionTimes();

    int capacity;
    std::vector<Item> items = parseItemsAndCapacity(mainLogger, capacity);

    std::pair<bool, bool> logged = executeAlgorithmsAndHeuristics(items, capacity, minExecutionTimes, execTimeLogger);
    logExecutionResults(logged, minExecutionTimes);
}
/**
 * @file Benchmark.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the functions used for benchmarking.
 * 
*/

#include "Item.h"
#include "Utility.h"
#include "Logger.h"       //-- <new> --
#include "Benchmark.h"    //-- <new> --

#include "../main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <unistd.h>
#include <climits>
#include <cmath>
#include <functional>

// --- <funcs> <algorithms> ---

/**
 * @brief Wrapper function for the Ant Colony Optimization algorithm for the Knapsack problem.
 * 
 * This function uses the Ant Colony Optimization (ACO) algorithm to solve the Knapsack problem.
 * It measures the execution time of the algorithm and logs the results.
 * 
 * @param colony The AntColony object representing the ant colony.
 * @param capacity The capacity of the knapsack.
 * @param items The vector of Item objects representing the available items.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackACOWrapper(AntColony& colony, 
                        int capacity, 
                        const std::vector<Item>& items,
                        std::map<std::string, double>& minExecutionTime,
                        std::shared_ptr<spdlog::logger> logger) {

    const std::string _NAME_ = "<a> Ant Colony Optimization";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(
            [&colony](int capacity, const std::vector<Item>& items) {
                return colony.knapsackACO(capacity, items);
            },
            capacity, items);
            auto time = pair.first;
            auto solution = pair.second;

            minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}

/**
 * @brief Wrapper function for the knapsack backtracking algorithm.
 * 
 * This function calculates the minimum execution time of the knapsackBacktracking function
 * and logs the results using the provided logger.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackBacktrackingWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                 std::map<std::string, double>& minExecutionTime,
                                 std::shared_ptr<spdlog::logger> logger) {
                                  
    const std::string _NAME_ = "<a> Backtracking";
    size_t items_size = items.size(); 

    int currentIndex = 0;
    int currentValue = items[0].value;
    int currentWeight = items[0].weight;

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for (unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackBacktracking, 
                                     capacity, 
                                     items, 
                                     items_size,
                                     currentWeight,
                                     currentValue,
                                     currentIndex); 

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    
        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);       
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;                                                                               
}

// --- <fix> ---
/**
 * @brief Wrapper function for the Branch and Bound algorithm for the Knapsack problem.
 * 
 * This function takes the capacity of the knapsack, a vector of items, a map to store the minimum execution time,
 * and a logger for logging the results. It measures the execution time of the Branch and Bound algorithm for the
 * given capacity and items, and logs the results. It repeats this process for a specified number of times and stores
 * the minimum execution time in the map.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items A vector of items.
 * @param minExecutionTime A map to store the minimum execution time.
 * @param logger A shared pointer to a logger for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackBranchAndBoundWrapper(int capacity, 
                                   const std::vector<Item>& items,
                                   std::map<std::string, double>& minExecutionTime,
                                   std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<a> Branch and Bound";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime([](int capacity, const std::vector<Item>& items) {
                return knapsackBranchAndBound(capacity, items);
            },
            capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;                         
}
// --- <fix> ---

/**
 * @brief Wrapper function for solving the knapsack problem using Dynamic Programming.
 * 
 * This function measures the execution time of the knapsackDP function and logs the results.
 * It also keeps track of the minimum execution time and updates the minExecutionTime map.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to choose from.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results were successfully logged, false otherwise.
 */
bool knapsackDPWrapper(int capacity, 
                       const std::vector<Item>& items,
                       std::map<std::string, double>& minExecutionTime,
                       std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<a> Dynamic Programming";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackDP, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    
        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @file Benchmark.cpp
 * @brief Contains the implementation of the knapsackMemoizationWrapper function.
 */

/**
 * @brief Wrapper function for the knapsackMemoization function.
 * 
 * This function measures the execution time of the knapsackMemoization function
 * and logs the results. It uses memoization technique to solve the knapsack problem.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackMemoizationWrapper(int capacity, 
                                const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger) {

    const std::string _NAME_ = "<a> Memoization";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    
    double time = 0;
    int solution = 0;
    bool logged = true;
    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackMemoization, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    
        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);
    }

    minExecutionTime[_NAME_] = minTime;
    
    return logged; 
}

/**
 * @brief Wrapper function for the recursive implementation of the knapsack algorithm.
 * 
 * This function measures the execution time of the knapsackRecursive function and logs the results.
 * It also keeps track of the minimum execution time and updates the minExecutionTime map.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to choose from.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackRecursiveWrapper(int capacity,     
                              const std::vector<Item>& items, 
                              std::map<std::string, double>& minExecutionTime,
                              std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<a> Recursive";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackRecursive, capacity, items, items.size());

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    
        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);  
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;     
}

// --- <fix> ---
/**
 * @brief Wrapper function for the knapsack problem using Simulated Annealing algorithm.
 * 
 * This function calculates the minimum execution time for the knapsack problem using the Simulated Annealing algorithm.
 * It iterates multiple times to find the best solution and logs the results.
 * 
 * @param capacity The maximum capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack problem.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackSimulatedAnnealingWrapper(int capacity, 
                                       const std::vector<Item>& items,
                                       std::map<std::string, double>& minExecutionTime,
                                       std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<a> Simulated Annealing";
    size_t items_size = items.size(); 
    
    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    double intialTemp = 65;
    double coolingRate = 0.73;
    
    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackSimulatedAnnealing, capacity, items, intialTemp, coolingRate);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);
    
        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}
// -- <fix> -- 
// --- <funcs> <algorithms> ---

// --- <funcs> <heuristics> ---

/**
 * @brief Wrapper function for the "Deal Stingy" knapsack algorithm.
 * 
 * This function measures the execution time of the "Deal Stingy" knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time and stores
 * it in the provided map.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results were successfully logged, false otherwise.
 */
bool knapsackDealStingyWrapper(int capacity, 
                               const std::vector<Item>& items,
                               std::map<std::string, double>& minExecutionTime,
                               std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Deal Stingy";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(dealStingyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function for the defensive greedy knapsack algorithm.
 * 
 * This function measures the execution time of the defensive greedy knapsack algorithm
 * and logs the results. It then updates the minimum execution time in the provided
 * map and returns whether the results were successfully logged.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return True if the results were successfully logged, false otherwise.
 */
bool knapsackDefensiveGreedyWrapper(int capacity, 
                                    const std::vector<Item>& items,
                                    std::map<std::string, double>& minExecutionTime,
                                    std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Defensive Greedy";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(defensiveGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function for the heavy greedy knapsack algorithm.
 * 
 * This function measures the execution time of the heavy greedy knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time among
 * multiple runs and updates the `minExecutionTime` map accordingly.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns `true` if the results are successfully logged, `false` otherwise.
 */
bool knapsackHeavyGreedyWrapper(int capacity, 
                                const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Heavy Greedy";
    size_t items_size = items.size(); 

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(heavyGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function for the limited greedy knapsack algorithm.
 * 
 * This function measures the execution time of the limited greedy knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time and stores
 * it in the provided map.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object used for logging the results.
 * @return Returns true if the results were successfully logged, false otherwise.
 */
bool knapsackLimitedGreedyWrapper(int capacity, 
                                  const std::vector<Item>& items,
                                  std::map<std::string, double>& minExecutionTime,
                                  std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Limited Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(limitedGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);  
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function to benchmark the MaxOfTwo Greedy algorithm for the knapsack problem.
 * 
 * This function measures the execution time of the MaxOfTwo Greedy algorithm for the knapsack problem
 * and logs the results. It runs the algorithm multiple times and keeps track of the minimum execution time.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackMaxOfTwoWrapper(int capacity, 
                             const std::vector<Item>& items,
                             std::map<std::string, double>& minExecutionTime,
                             std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> MaxOfTwo Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(maxOfTwoKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function for the scored greedy knapsack algorithm.
 * 
 * This function measures the execution time of the scored greedy knapsack algorithm
 * and logs the results. It runs the algorithm multiple times and keeps track of the 
 * minimum execution time. The results are stored in a map with the algorithm name as 
 * the key.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackScoredGreedyWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                 std::map<std::string, double>& minExecutionTime,
                                 std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Scored Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(scoredGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged; 
}

/**
 * @brief Wrapper function for the Sliding Threshold Greedy algorithm for the Knapsack problem.
 * 
 * This function calculates the minimum execution time of the Sliding Threshold Greedy algorithm
 * for the Knapsack problem with the given capacity and items. It also logs the results using the
 * provided logger.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackSlidingThresholdWrapper(int capacity, 
                                     const std::vector<Item>& items,
                                     std::map<std::string, double>& minExecutionTime,
                                     std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Sliding Threshold Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(slidingThresholdKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}

/**
 * @brief Wrapper function for the standard greedy knapsack algorithm.
 * 
 * This function measures the execution time of the standard greedy knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time among multiple runs.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackStandardGreedyWrapper(int capacity, 
                                   const std::vector<Item>& items,
                                   std::map<std::string, double>& minExecutionTime,
                                   std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Standard Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;
    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(standardGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}

/**
 * @brief Wrapper function for the transitioning greedy knapsack algorithm.
 * 
 * This function measures the execution time of the transitioning greedy knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time among multiple runs.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime A map to store the minimum execution time for each algorithm.
 * @param logger A shared pointer to the logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackTransitioningGreedyWrapper(int capacity, 
                                        const std::vector<Item>& items,
                                        std::map<std::string, double>& minExecutionTime,
                                        std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Transitioning Greedy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;
    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(transitioningGreedyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger);  
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}

/**
 * @brief Wrapper function for the weight stingy knapsack algorithm.
 * 
 * This function measures the execution time of the weight stingy knapsack algorithm
 * and logs the results. It also keeps track of the minimum execution time and updates
 * the provided map with the minimum time for the weight stingy algorithm.
 * 
 * @param capacity The capacity of the knapsack.
 * @param items The vector of items to be considered for the knapsack.
 * @param minExecutionTime The map to store the minimum execution time for each algorithm.
 * @param logger The logger object for logging the results.
 * @return Returns true if the results are successfully logged, false otherwise.
 */
bool knapsackWeightStingyWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger) {
    const std::string _NAME_ = "<h> Weight Stingy";
    size_t items_size = items.size();

    double minTime = INT64_MAX;
    double time = 0;
    int solution = 0;
    bool logged = true;

    std::__1::pair<std::__1::chrono::system_clock::rep, int> pair;

    for(unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(weightStingyKnapsack, capacity, items);

        auto time = pair.first;
        auto solution = pair.second;

        minTime = std::min((double)time, minTime);

        bool logged = logResults(time, 
                                capacity, 
                                solution,
                                items_size, 
                                _NAME_,
                                logger); 
    }

    minExecutionTime[_NAME_] = minTime;
    return logged;
}
// --- <funcs> <heuristics> ---

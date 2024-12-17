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

    double intialTemp = 100;
    double coolingRate = 0.2;
    
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
// --- <funcs> <heuristics> ---

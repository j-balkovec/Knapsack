/**
 * @file main.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Entry point of the program
 * 
*/

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

// -- find a new way to do this, it's incredibly slow! [BenchmarkFunctions took 81.5683 seconds.]

#include "../Tools/Item.h"
#include "../Tools/Utility.h"
#include "../Tools/Logger.h"       //-- <new> --
#include "../Tools/Benchmark.h"    //-- <new> --

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

constexpr int NUM_THREADS = 8;

void initializeLoggers(std::shared_ptr<spdlog::logger>& exec_time_logger, std::shared_ptr<spdlog::logger>& main_logger) {
    exec_time_logger = getExecTimeLogger();
    main_logger = getMainLogger();
    main_logger->info("Main logger created. Using '{}' threads", NUM_THREADS);
}

std::map<std::string, double> setupMinExecutionTimes() {
    return {
        {"<a> Ant Colony Optimization", 0},
        {"<a> Backtracking", 0},
        {"<a> Branch And Bound", 0},
        {"<a> Dynamic Programming", 0},
        {"<a> Memoization", 0},
        {"<a> Recursive", 0},
        {"<a> Simulated Annealing", 0},
        {"<h> Deal Stingy", 0},
        {"<h> Defensive Greedy", 0},
        {"<h> Heavy Greedy", 0},
        {"<h> Limited Greedy", 0},
        {"<h> MaxOfTwo Greedy", 0},
        {"<h> Scored Greedy", 0},
        {"<h> Sliding Threshold Greedy", 0},
        {"<h> Standard Greedy", 0},
        {"<h> Transitioning Greedy", 0},
        {"<h> Weight Stingy", 0},
    };
}

AntColony setupColony() {
    constexpr int numAnts = 100;
    constexpr int numIterations = 500;
    constexpr double alpha = 1.0;
    constexpr double beta = 3.0;
    constexpr double evaporationRate = 0.5;

    return AntColony(numAnts, numIterations, alpha, beta, evaporationRate);
}

std::vector<Item> parseItemsAndCapacity(std::shared_ptr<spdlog::logger>& main_logger, int& capacity) {
    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1, main_logger), main_logger);
    capacity = parseCSVCapacity(CAPACITY.data(), main_logger);
    return items;
}

std::pair<bool, bool> executeAlgorithmsAndHeuristics(const std::vector<Item>& items, 
                                                     int capacity, 
                                                     std::map<std::string, double>& minExecutionTimes, 
                                                     std::shared_ptr<spdlog::logger>& exec_time_logger) {

    // Create threads for concurrent execution
    std::vector<std::thread> threads;

    logSeparator(exec_time_logger, 'A'); // Algorithm separator

    AntColony colony = setupColony();

    // Create booleans to track success
    bool log_aco = false;
    bool log_dp = false;
    bool log_memo = false;
    bool log_annealing = false;
    bool log_branch_and_bound = false;
    bool log_backtracking = false;
    bool log_recursive = false;

    bool log_deal_stingy = false;
    bool log_defensive = false;
    bool log_heavy = false;
    bool log_limited = false;
    bool log_max_of_two = false;
    bool log_scored = false;
    bool log_sliding_threshold = false;
    bool log_standard_greedy = false;
    bool log_transitioning_greedy = false;
    bool log_weight_stingy = false;

    // Running algorithms in separate threads
    threads.push_back(std::thread([&]() {
        log_aco = knapsackACOWrapper(colony, capacity, items, minExecutionTimes, exec_time_logger);
        log_dp = knapsackDPWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_memo = knapsackMemoizationWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_annealing = knapsackSimulatedAnnealingWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_recursive = knapsackRecursiveWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_backtracking = knapsackBacktrackingWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_branch_and_bound = knapsackBranchAndBoundWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_deal_stingy = knapsackDealStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_heavy = knapsackHeavyGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_limited = knapsackLimitedGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_max_of_two = knapsackMaxOfTwoWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_scored = knapsackScoredGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_sliding_threshold = knapsackSlidingThresholdWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_standard_greedy = knapsackStandardGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        log_transitioning_greedy = knapsackTransitioningGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        log_weight_stingy = knapsackWeightStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    
    // Wait for all threads to finish
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join(); 
        }
    }

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

void logExecutionResults(std::pair<bool, bool> loggedFunction, std::map<std::string, double>& minExecutionTimes) {
    displayMessage("Execution Completed!", SUCCESS); //jank

    displayMessage("-- [min_exec_times] --\n\n", INFO);

    // Log to console or a separate log file
    for (auto key : minExecutionTimes) {
        std::cout << "[name]: " << key.first << ", " << "[min_time]: " << key.second << std::endl;
    }

    if (loggedFunction.first) {
        displayMessage("Logged Algorithms.", SUCCESS);
    } else {
        displayMessage("Something went wrong <algorithms>.", ERROR);
    }

    if (loggedFunction.second) {
        displayMessage("Logged Heuristics.", SUCCESS);
    } else {
        displayMessage("Something went wrong <heuristics>.", ERROR);
    }

    if (loggedFunction.first && loggedFunction.second) {
        displayMessage("Logged both. Check logs: [" + std::string(EXEC_TIME_LOG_FILE.data()) + "]", SUCCESS);
    } else {
        displayMessage("Something went wrong <all>.", ERROR);
    }
}

void BenchmarkFunctionsNew() {
    // Initialize loggers
    std::shared_ptr<spdlog::logger> exec_time_logger, main_logger;
    initializeLoggers(exec_time_logger, main_logger);

    // Setup execution time map
    std::map<std::string, double> minExecutionTimes = setupMinExecutionTimes();

    // Parse items and capacity
    int capacity;
    std::vector<Item> items = parseItemsAndCapacity(main_logger, capacity);

    // Execute algorithms and heuristics concurrently
    std::pair<bool, bool> logged = executeAlgorithmsAndHeuristics(items, capacity, minExecutionTimes, exec_time_logger);

    // Log the execution results
    logExecutionResults(logged, minExecutionTimes);  // Modify based on actual conditions
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // Measure the execution time of BenchmarkFunctionsNew
    auto startNew = std::chrono::high_resolution_clock::now();
    BenchmarkFunctionsNew();
    auto endNew = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationNew = endNew - startNew;
    std::cout << "BenchmarkFunctionsNew took " << durationNew.count() << " seconds.\n";

    return 0;
}
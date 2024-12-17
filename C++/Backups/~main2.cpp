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

constexpr int NUM_THREADS = 7;

void BenchmarkFunctionsNew() {
    auto exec_time_logger = getExecTimeLogger();
    auto main_logger = getMainLogger();

    main_logger -> info("Main logger created. Using '{}' threads", NUM_THREADS);

    // Map that stores min execution times
    std::map<std::string, double> minExecutionTimes = {
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

    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1, main_logger), main_logger);
    int capacity = parseCSVCapacity(CAPACITY.data(), main_logger);
    size_t item_size = items.size();


    // --------- <work_bench> ---------

    // --- <algorithms> --- <START>

    constexpr int numAnts = 100;
    constexpr int numIterations = 500;
    constexpr double alpha = 1.0;
    constexpr double beta = 3.0;
    constexpr double evaporationRate = 0.5;

    AntColony colony(numAnts, numIterations, alpha, beta, evaporationRate);

    std::vector<std::thread> threads;

    logSeparator(exec_time_logger, 'A');


    threads.push_back(std::thread([&]() { 
        knapsackACOWrapper(colony, capacity, items, minExecutionTimes, exec_time_logger);
        knapsackDPWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() { 
        knapsackMemoizationWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackSimulatedAnnealingWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() { 
        knapsackBranchAndBoundWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackDealStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() { 
        knapsackHeavyGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackLimitedGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));
    
    threads.push_back(std::thread([&]() { 
        knapsackMaxOfTwoWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackScoredGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    threads.push_back(std::thread([&]() {
        knapsackSlidingThresholdWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackStandardGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
     }));

    threads.push_back(std::thread([&]() { 
        knapsackTransitioningGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
        knapsackWeightStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    }));

    // wait for all to finish
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join(); 
        }
    }

    bool log_aco = knapsackACOWrapper(colony, capacity, items, minExecutionTimes, exec_time_logger);
    bool log_dp = knapsackDPWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_memo = knapsackMemoizationWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_annealing = knapsackSimulatedAnnealingWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    //bool log_recursive = knapsackRecursiveWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    //bool log_backtracking = knapsackBacktrackingWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_branch_and_bound = knapsackBranchAndBoundWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    
    // --- <algorithms> --- <END>


    // --- <heuristics> --- <START>

    logSeparator(exec_time_logger, 'H');
    bool log_deal_stingy = knapsackDealStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_defensive = knapsackDealStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_heavy = knapsackHeavyGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_limited = knapsackLimitedGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_max_of_two = knapsackMaxOfTwoWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_scored = knapsackScoredGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_sliding_threshold = knapsackSlidingThresholdWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_standard_greedy = knapsackStandardGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_transitioning_greedy = knapsackTransitioningGreedyWrapper(capacity, items, minExecutionTimes, exec_time_logger);
    bool log_weight_stingy = knapsackWeightStingyWrapper(capacity, items, minExecutionTimes, exec_time_logger);

    // --- <heuristics> --- <END>   
    // --------- <work_bench> ---------

    bool logged_algorithms_long_expr = log_aco &&
                                       log_dp &&
                                       log_memo &&
                                       log_annealing &&
                                       //log_recursive &&
                                       //log_backtracking &&
                                       log_branch_and_bound;

    bool logged_heuristics_long_expr = log_deal_stingy &&
                                       log_defensive &&
                                       log_limited &&
                                       log_max_of_two &&
                                       log_scored &&
                                       log_sliding_threshold &&
                                       log_standard_greedy &&
                                       log_transitioning_greedy &&
                                       log_weight_stingy;

    displayMessage("Execution Completed!", SUCCESS); //jank

    // --- <debug only, not meant for production> ---
    displayMessage("-- [min_exec_times] --\n\n", INFO);

    // -- <log to a separate log file + csv format> -- 
    for(auto key: minExecutionTimes) {
        std::cout << "[name]: " << key.first << ", " << "[min_time]: " << key.second << std::endl;
    }
    // -- <log to a separate log file + csv format> -- 

    if (logged_algorithms_long_expr) {
        displayMessage("Logged Algorithms.", SUCCESS);
    } else {
        displayMessage("Something went wrong <algorithms>.", ERROR);
    }

    if(logged_heuristics_long_expr) {
        displayMessage("Logged Heuristics.", SUCCESS);
    } else {
        displayMessage("Something went wrong <heuristics>.", ERROR);
    }

    if (logged_algorithms_long_expr && logged_heuristics_long_expr) {
        displayMessage("Logged both. Check logs: [" + std::string(EXEC_TIME_LOG_FILE.data()) + "]", SUCCESS);
    } else {
        displayMessage("Something went wrong <all>.", ERROR);
    }
    // --- <debug only, not meant for production> ---
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
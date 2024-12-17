/**
 * @file main.cpp
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

// #include "../Tools/Item.h"
// #include "../Tools/Utility.h"
// #include "../Tools/Logger.h"

// -- <remove "../" to fix include errors> --
#include "../Tools/Item.h"
#include "../Tools/Utility.h"
#include "../Tools/Logger.h"

#include "main.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <unistd.h>
#include <climits>
#include <cmath>

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
// --- <fix> ---
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
                                 std::shared_ptr<spdlog::logger> logger){
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

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    auto exec_time_logger = getExecTimeLogger();
    auto main_logger = getMainLogger();

    main_logger -> info("Main logger created");

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

    logSeparator(exec_time_logger, 'A');
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

    if(logged_algorithms_long_expr) {
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
    return 0;
}
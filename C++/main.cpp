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
#include <chrono>
#include <unistd.h>
#include <climits>
#include <cmath>

// log files
const std::string_view MAIN_LOG = "../Logs/main_log.log";
const std::string_view EXEC_TIME_LOG_FILE = "../Logs/exec_time.log";
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

/**
 * @brief Retrieves the main logger instance.
 * 
 * This function returns a shared pointer to the main logger, which is responsible for logging messages in the application.
 * If the logger does not exist, it creates a new logger with the name "main_log" and sets its log level to "info".
 * 
 * @return A shared pointer to the main logger.
 * @throws std::runtime_error if the logger creation fails.
 */
std::shared_ptr<spdlog::logger> getMainLogger() {
    constexpr std::string_view main_log_name = "main_log";
    auto main_logger = spdlog::get(main_log_name.data());

    if (!main_logger) {
        try {
            main_logger = spdlog::basic_logger_mt(main_log_name.data(), MAIN_LOG.data());
            main_logger->set_level(spdlog::level::info);
        } catch (const std::exception& e) {
            displayMessage("Error: Failed to create logger <main_log>. Exception: " + std::string(e.what()), ERROR);
            throw std::runtime_error("Logger creation failed <main_log>");
        }
    }

    return main_logger;
}

/**
 * @brief Retrieves the logger for measuring execution time.
 * 
 * This function returns a shared pointer to the logger used for measuring execution time.
 * If the logger does not exist, it creates a new one with the name "exec_time" and sets its level to "info".
 * 
 * @return A shared pointer to the execution time logger.
 * @throws std::runtime_error if the logger creation fails.
 */
std::shared_ptr<spdlog::logger> getExecTimeLogger() {
    constexpr std::string_view exec_time_log_name = "exec_time";
    auto exec_time_log = spdlog::get(exec_time_log_name.data());

    if (!exec_time_log) {
        try {
            exec_time_log = spdlog::basic_logger_mt(exec_time_log_name.data(), MAIN_LOG.data());
            exec_time_log->set_level(spdlog::level::info);
        } catch (const std::exception& e) {
            displayMessage("Error: Failed to create logger <exec_time>. Exception: " + std::string(e.what()), ERROR);
            throw std::runtime_error("Logger creation failed <exec_time>");
        }
    }

    return exec_time_log;
}

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
 * @note Empty string means wrong file path. The return statements are unreachable but are there,
 *       so that the compiler is not complaining
 *
 * Example usage:
 * @code
 * std::string path = getFilePath(ITEM_3);
 * std::cout << "File path: " << path << std::endl;
 * @endcode
 */
std::string getFilePath(DataKey key, const std::shared_ptr<spdlog::logger>& logger) {

    try {
        auto it = DATA_MAP.find(key);
        if (it != DATA_MAP.end()) {
            return it->second;
        }
        throw std::out_of_range("Invalid key");
    } catch (const std::out_of_range &e) {
        logger->error("Error: {}", e.what());   
        return "\0"; // to fix warning
    }
    return "\0"; // to fix the warning
}

/**
 * @brief Recursively logs additional arguments passed to the function.
 * 
 * This function logs all arguments passed to it, starting with the first one,
 * and then recursively logs the remaining arguments (if any).
 * It uses the spdlog library to log the values at the info level.
 * 
 * @tparam T The type of the first argument.
 * @tparam Args The types of the remaining arguments.
 * 
 * @param logger A shared pointer to the logger object, used for logging.
 * @param first The first argument to log.
 * @param rest The remaining arguments to log.
 * 
 * @note The function uses recursion to log each argument individually. The logging
 * is done at the info level using the spdlog::logger::info method.
 */
template <typename T, typename... Args>
void logAdditionalArgs(std::shared_ptr<spdlog::logger> logger, T first, Args... rest) {
    logger->info("{}", first); // Log the first additional argument
    if constexpr (sizeof...(rest) > 0) {
        logAdditionalArgs(logger, rest...); // Recursively log the rest
    }
}

/**
 * @brief A base case function that ends the recursion for logging additional arguments.
 * 
 * This function serves as the terminating condition for the recursive logging function,
 * ensuring that no further arguments are logged when there are no more arguments left.
 * 
 * @param logger A shared pointer to the logger object, which is used to log the arguments.
 * 
 * @note This function does not log any data; it simply ends the recursion process.
 */
inline void logAdditionalArgs(std::shared_ptr<spdlog::logger> logger) {}

/**
 * @brief Logs the execution time and other relevant parameters to a log file.
 * 
 * This function logs the execution time, knapsack capacity, item size, and function name,
 * along with any additional arguments provided. It uses the spdlog library to log the 
 * values at the info level, appending them to the specified log file.
 * 
 * @tparam Args The types of the additional arguments that can be logged.
 * 
 * @param execution_time The time it took to execute the knapsack algorithm, in microseconds.
 * @param solution The maximum value that can be obtained by selecting items.
 * @param capacity The maximum capacity of the knapsack.
 * @param item_size <size_t> The number of items considered in the knapsack problem.
 * @param func_name The name of the function being logged.
 * @param extra_args Any additional arguments that are passed to be logged.
 * @param logger A logger instance to log the data.
 * 
 * @return true if the logging operation was successful.
 * 
 * @note The function will create or retrieve a logger named "exec_time" and log the 
 * fixed arguments first. Then, it will recursively log any extra arguments passed to it
 * via the logAdditionalArgs function.
 * 
 * -- <TODO> -- Add time of execution (dd-mm-yyyy, time hh::mm::ss)
 */
template <typename... Args>
bool logResults(double execution_time, 
                int capacity, 
                int solution, 
                size_t item_size, 
                std::string func_name, 
                Args... extra_args,
                const std::shared_ptr<spdlog::logger>& logger) {

    // Log fixed arguments
    logger->info("[name]: {}", func_name);
    logger->info("[execution_time]: {}", execution_time);
    logger->info("[capacity]: {}", capacity);
    logger->info("[solution]: {}", solution);
    logger->info("[items_size]: [{}]", item_size); // log item size

    logAdditionalArgs(logger, extra_args...);

    logger->info("\n");
    return true;
}

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

/**
 * @brief Logs a separator message based on the given type.
 * 
 * This function logs a separator message to the provided logger based on the given type.
 * If the type is 'h' or 'H', it logs a separator message for the heuristic.
 * If the type is 'a' or 'A', it logs a separator message for the algorithm.
 * 
 * @param logger The logger to log the separator message.
 * @param type The type of separator message to log ('h' for heuristic, 'a' for algorithm).
 */
void logSeparator(const std::shared_ptr<spdlog::logger>& logger, char type) {
    if(type == 'h' || type == 'H') {
        logger->info("\n\n\n");
        logger->info("**************** -- <running> - <heuristic> -- ****************");
        logger->info("\n\n\n");
    } else if(type == 'a' || type == 'A') {
        logger->info("\n\n\n");
        logger->info("**************** -- <running> - <algo> -- ****************");
        logger->info("\n\n\n");
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    // auto exec_time_logger = nullptr;
    // auto main_logger = nullptr;

    auto exec_time_logger = getExecTimeLogger();
    auto main_logger = getMainLogger();

    main_logger -> info("Main logger created");

    // try {
    //     auto exec_time_logger = getExecTimeLogger();
    //     auto main_logger = getMainLogger();
    // } catch (const std::runtime_error &e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     std::cout << "<debug>: <exec_time> -> " << exec_time_logger << ", <main_log> -> " << main_logger << std::endl;
    //     return 1;
    // }

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

    // --- <debug only, not meant for production> ---
    displayMessage("-- [min_exec_times] --\n\n", INFO);

    // -- <log to a separae log file + csv format> -- 
    for(auto key: minExecutionTimes) {
        std::cout << "[name]: " << key.first << ", " << "[min_time]: " << key.second << std::endl;
    }
    // -- <log to a separae log file + csv format> -- 

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
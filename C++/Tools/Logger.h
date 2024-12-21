/**
 * @file Logger.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the function definitions associated with the loggers used throughout the program.
 * 
*/

#ifndef LOGGER_H
#define LOGGER_H
#define FMT_HEADER_ONLY

#include "Item.h"
#include "Utility.h"

#include <memory>
#include <string>
#include <chrono>
#include <utility> //pair

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

// -- <defined in Utility.h> --
// const std::string_view MAIN_LOG = "../Logs/main_log.log";
// const std::string_view EXEC_TIME_LOG_FILE = "../Logs/exec_time.log";

extern std::shared_ptr<spdlog::logger> getMainLogger();
extern std::shared_ptr<spdlog::logger> getExecTimeLogger();
extern std::shared_ptr<spdlog::logger> getMinExecTimeLogger();
extern std::shared_ptr<spdlog::logger> getTestLogger(const std::string_view& logFile);

void initializeLoggers(std::shared_ptr<spdlog::logger>& execTimeLogger, 
                       std::shared_ptr<spdlog::logger>& mainLogger, 
                       std::shared_ptr<spdlog::logger>& minExecTimeLogger);

extern void logSeparator(const std::shared_ptr<spdlog::logger>& logger, char type);
void logExecutionResults(std::pair<bool, bool> loggedFunction, std::map<std::string, double>& minExecutionTimes);
void logMinExecutionTimes(const std::map<std::string, double>& minExecutionTimes);
std::map<std::string, double> setupMinExecutionTimes();

// ------- <C++ templates :\> ------- //
// Since they need to be visible to the compiler at compile time, they are defined in the header file

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

// ------- <C++ templates :\> ------- //

#endif // LOGGER_H
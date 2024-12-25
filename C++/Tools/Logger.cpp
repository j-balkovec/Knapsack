/**
 * @file logger.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the functions associated with the loggers used throughout the program.
 * 
*/

#include "Logger.h"

#include <memory>
#include <string>
#include <iostream>
#include <filesystem>

const std::string_view SEPARATOR = "==================================================";

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
            main_logger = spdlog::basic_logger_mt(main_log_name.data(), MAIN_LOG_FILE.data());
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
            exec_time_log = spdlog::basic_logger_mt(exec_time_log_name.data(), EXEC_TIME_LOG_FILE.data());
            exec_time_log->set_level(spdlog::level::info);
        } catch (const std::exception& e) {
            displayMessage("Error: Failed to create logger <exec_time>. Exception: " + std::string(e.what()), ERROR);
            throw std::runtime_error("Logger creation failed <exec_time>");
        }
    }

    return exec_time_log;
}

/**
 * @brief Retrieves the logger for minimum execution time.
 *
 * This function returns a shared pointer to the logger object that is used to log minimum execution time.
 * If the logger does not exist, it creates a new logger with the name "min_exec_time" and sets the log level to info.
 * The logger is created using the spdlog library.
 *
 * @return A shared pointer to the logger object for minimum execution time.
 * @throws std::runtime_error if the logger creation fails.
 */
std::shared_ptr<spdlog::logger> getMinExecTimeLogger() {
    constexpr std::string_view min_exec_time_log_name = "min_exec_time";
    auto min_exec_time_log = spdlog::get(min_exec_time_log_name.data());

    if (!min_exec_time_log) {
        try {
            min_exec_time_log = spdlog::basic_logger_mt(min_exec_time_log_name.data(), MIN_EXEC_TIME_LOG_FILE.data());
            min_exec_time_log->set_level(spdlog::level::info);
        } catch (const std::exception& e) {
            displayMessage("Error: Failed to create logger <min_exec_time>. Exception: " + std::string(e.what()), ERROR);
            throw std::runtime_error("Logger creation failed <min_exec_time>");
        }
    }

    return min_exec_time_log;
}

/**
 * @brief Retrieves a shared pointer to a logger for testing purposes.
 * 
 * This function returns a shared pointer to a logger object that can be used for logging test-related information.
 * If the logger does not exist, it creates a new logger with the name "test_time" and sets the log level to "info".
 * The logger is created using the spdlog library.
 * 
 * @return A shared pointer to the test logger.
 * @throws std::runtime_error if the logger creation fails.
 */
std::shared_ptr<spdlog::logger> getTestLogger(const std::string_view& logFile = TEST_LOG_FILE) {

    std::string test_log_name = "test_time_" + std::filesystem::path(logFile).filename().string();

    auto test_log = spdlog::get(test_log_name.data());

    if (!test_log) {
        try {
            test_log = spdlog::basic_logger_mt(test_log_name.data(), logFile.data());
            test_log->set_level(spdlog::level::info);
        } catch (const std::exception& e) {
            displayMessage("Error: Failed to create logger <test_log>. Exception: " + std::string(e.what()), ERROR);
            throw std::runtime_error("Logger creation failed <test_log>");
        }
    }

    return test_log;
}

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

/**
 * @brief Initializes the loggers for execution time, main, and minimum execution time.
 * 
 * This function assigns the loggers to the provided shared pointers and logs the creation of each logger.
 * The loggers are flushed every 1 second.
 * 
 * @param execTimeLogger A shared pointer to the execution time logger.
 * @param mainLogger A shared pointer to the main logger.
 * @param minExecTimeLogger A shared pointer to the minimum execution time logger.
 */
void initializeLoggers(std::shared_ptr<spdlog::logger>& execTimeLogger, std::shared_ptr<spdlog::logger>& mainLogger, std::shared_ptr<spdlog::logger>& minExecTimeLogger) {
    execTimeLogger = getExecTimeLogger();
    mainLogger = getMainLogger();
    minExecTimeLogger = getMinExecTimeLogger();

    mainLogger->info("Main logger created. Using 1 thread");
    mainLogger->info(SEPARATOR.data());

    execTimeLogger->info("Execution Time logger created. Using 1 thread");
    execTimeLogger->info(SEPARATOR.data());

    minExecTimeLogger->info("Minumum Execution Time logger created. Using 1 thread");
    minExecTimeLogger->info(SEPARATOR.data());

    spdlog::flush_every(std::chrono::seconds(1));
}

/**
 * @brief Logs the minimum execution times for different tasks.
 * 
 * This function logs the minimum execution times for different tasks
 * using the provided logger. It iterates over the given map of task names
 * and their corresponding minimum execution times, and logs them using
 * the logger.
 * 
 * @param minExecutionTimes A map containing task names as keys and their
 *                          corresponding minimum execution times as values.
 */
void logMinExecutionTimes(const std::map<std::string, double>& minExecutionTimes) {

    auto min_exec_time_logger = getMinExecTimeLogger();

    min_exec_time_logger->info("\0\n"); // better readability
    min_exec_time_logger->info(SEPARATOR.data());

    for (auto key : minExecutionTimes) {
        min_exec_time_logger->info("[name]: {}, [min_time]: {}", key.first, key.second);
    }
    min_exec_time_logger->info(SEPARATOR.data());
    min_exec_time_logger->info("\0\n"); // better readability
}

/**
 * @brief Sets up the minimum execution times for different algorithms.
 * 
 * This function initializes a map where the keys represent the names of the algorithms
 * and the values represent their corresponding minimum execution times.
 * 
 * @return A map containing the algorithm names and their minimum execution times.
 */
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

// -- <debug only> -- 
/**
 * @brief Logs the execution results and displays messages based on the logged function and minimum execution times.
 * 
 * @param loggedFunction A pair of booleans indicating whether the algorithms and heuristics were successfully logged.
 * @param minExecutionTimes A reference to a map containing the minimum execution times for different functions.
 */
void logExecutionResults(std::pair<bool, bool> loggedFunction, std::map<std::string, double>& minExecutionTimes) {
    std::cout << std::endl;
    displayMessage("Execution Completed!", SUCCESS); //jank

    logMinExecutionTimes(minExecutionTimes);

    std::cout << std::endl;

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
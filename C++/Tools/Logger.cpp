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
/**
 * @file Utility.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief This header file holds the definitions for the utility functions used for sorting (think of them as lambdas).
 * 
*/

#ifndef UTILITY_H
#define UTILITY_H
#define FMT_HEADER_ONLY

#include <chrono>
#include <utility>
#include <spdlog/spdlog.h>
#include <vector>
#include <typeinfo>

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

#include "Item.h"

const std::string EXEC_TIME_LOG_FILE = "../Logs/exec_time.log";

extern bool compareByWeight(const Item& a, const Item& b);
extern bool compareByValue(const Item& a, const Item& b);
extern bool compareByScore(const Item& a, const Item& b);
extern bool compareByRatio(const Item& a, const Item& b);
extern bool compareByScoreAscending(const Item& a, const Item& b);

extern std::vector<Item> parseCSVItems(const std::string& filepath);
extern int parseCSVCapacity(const std::string& filepath);

// ------- <C++ templates :\> ------- //
// Since they need to be visible to the compiler at compile time, they are defined in the header file

template <typename T>
auto getSize(const T& arg) -> decltype(arg.size(), std::string("[size]: ") + std::to_string(arg.size())) {
    return "[size]: " + std::to_string(arg.size());
}

template <typename T>
std::string getSize(const T&) {
    return "[size]: Unknown";
}

template <typename Func, typename... Args>
decltype(auto) measureExecutionTime(Func&& func, Args&&... args) {
    auto logger = spdlog::get("time_logger");
    if (!logger) {
        logger = spdlog::basic_logger_mt("time_logger", EXEC_TIME_LOG_FILE);
        logger->set_level(spdlog::level::info);
    }

    logger->info("[executing_function]: {}", typeid(func).name());
    ((logger->info("[argument_type]: {}, [size]: {}", typeid(Args).name(), sizeof(args))), ...);

    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    logger->info("[exec_time]: {} ms", duration);

    return result;
}
// ------- <C++ templates :\> ------- //

#endif // UTILITY_H
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
#include <string>

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

// Idea, have a function that logs the parameters passed in, and have a separate function to log the execution time

// -- <bug> --
template <typename T>
std::string getSize(const T& arg) {
    // Attempt to call .size() for containers
    if constexpr (requires { arg.size(); }) {
        return "[size]: " + std::to_string(arg.size());
    } else {
        return "[size]: Unknown";
    }
}

template <typename T>
std::string getValue(const T& arg) {
    if constexpr (std::is_arithmetic_v<T>) {
        return "[value]: " + std::to_string(arg);
    } else if constexpr (requires { arg.begin(); arg.end(); }) {
        std::string values = "[values]: ";
        for (const auto& elem : arg) {
            values += getValue(elem) + " ";
            if (values.size() > 50) {
                values += "...";
                break;
            }
        }
        return values;
    } else {
        return "[value]: Unsupported type";
    }
}

template <typename Func, typename... Args>
decltype(auto) measureExecutionTime(Func&& func, Args&&... args) {
    auto logger = spdlog::get("time_logger");
    if (!logger) {
        logger = spdlog::basic_logger_mt("time_logger", EXEC_TIME_LOG_FILE);
        logger->set_level(spdlog::level::info);
    }

    logger->info("[executing_function]: {}", typeid(func).name());

    // Log arguments: type, size, and value
    int arg_index = 1;
    ([&] {
        logger->info("[argument_{}]: [type]: {}, {}", arg_index++, typeid(Args).name(), getSize(args));
        logger->info("[argument_{}]: {}", arg_index - 1, getValue(args));
    }(), ...);

    // Measure execution time
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    logger->info("[exec_time]: {} ms", duration);

    return result;
}

// ------- <C++ templates :\> ------- //

#endif // UTILITY_H
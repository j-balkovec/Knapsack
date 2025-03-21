/**
 * @file Utility.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief This file holds the utility functions used for sorting (think of them as lambdas).
 * 
*/

#define FMT_HEADER_ONLY // took 4 hours of debugging

#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <string>
#include <functional>
#include <chrono>
#include <typeinfo>

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

#include "Item.h"
#include "Utility.h"

const std::string_view RESET_COLOR = "\033[0m";
const std::string_view SUCCESS_COLOR = "\033[32m";
const std::string_view DEBUG_COLOR = "\033[33m";
const std::string_view WARNING_COLOR = "\033[35m";
const std::string_view ERROR_COLOR = "\033[31m";

/**
 * @brief Compare two items by their score in ascending order.
 * 
 * The score of an item is calculated using the formula: 
 * score = (value^3) / (weight^1.5)
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the score of item a is less than the score of item b, false otherwise.
 */
bool compareByScoreAscending(const Item& a, const Item& b) {
    double scoreA = std::pow(a.value, 3) / std::pow(a.weight, 1.5);
    double scoreB = std::pow(b.value, 3) / std::pow(b.weight, 1.5);
    return scoreA < scoreB; // Lower score comes first
}

/**
 * @brief Compares two items by their value.
 * 
 * This function is used as a comparator for sorting items in descending order of value.
 * The item with a higher value will be placed before the item with a lower value.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return True if the value of item a is greater than the value of item b, false otherwise.
 */
bool compareByValue(const Item& a, const Item& b) {
    return a.value > b.value; // Higher value comes first
}

/**
 * @brief Compares two items based on their weights.
 * 
 * This function is used as a comparator for sorting items in ascending order of weight.
 * Lighter items will come first in the sorted order.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the weight of item a is less than the weight of item b, false otherwise.
 */
bool compareByWeight(const Item& a, const Item& b) {
    return a.weight < b.weight; // Lighter items come first
}

/**
 * @brief Compare two items by their value-to-weight ratio.
 * 
 * This function calculates the value-to-weight ratio for two items and compares them.
 * The item with the higher ratio is considered to come first.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return True if the ratio of item a is greater than the ratio of item b, false otherwise.
 */
bool compareByRatio(const Item& a, const Item& b) {
    double ratioA = static_cast<double>(a.value) / a.weight;
    double ratioB = static_cast<double>(b.value) / b.weight;
    return ratioA > ratioB; // Higher ratio comes first
}

/**
 * @brief Compare two items based on their scores.
 * 
 * This function calculates the score of two items using the formula:
 * score = (value^3) / (weight^1.5)
 * The item with the higher score will be placed first.
 * 
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return true if the score of item a is greater than the score of item b, false otherwise.
 */
bool compareByScore(const Item& a, const Item& b) {
    double scoreA = std::pow(a.value, 3) / std::pow(a.weight, 1.5);
    double scoreB = std::pow(b.value, 3) / std::pow(b.weight, 1.5);
    return scoreA > scoreB; // Higher score comes first
}

/**
 * @brief Parses a CSV file to extract a list of items with weight and value attributes.
 * 
 * This function reads a CSV file specified by the filepath parameter and 
 * extracts items represented by weight and value. Each line in the file is 
 * expected to follow the format: <weight>,<value>. Lines that do not conform 
 * to this format are logged as warnings. The function also logs various events 
 * such as file opening, parsing progress, and errors, using the spdlog logger.
 * 
 * @param filepath The path to the CSV file containing item data.
 * 
 * @return A vector of Item objects parsed from the file. If the file cannot 
 *         be opened or is empty, an empty vector is returned.
 * 
 * @note 
 * - Requires an existing Item structure with weight and value attributes.
 * - A logger named file_logger is initialized if it does not already exist.
 * - Logs are written to logs/utility.log by default.
 * 
 * @warning 
 * - Malformed lines in the CSV file are skipped and logged as warnings.
 * - Ensure the file exists and has appropriate read permissions before calling this function.
 * 
 * Example usage:
 * @code
 * std::vector<Item> items = parseCSVItems("data/items.csv");
 * for (const auto& item : items) {
 *     std::cout << "Weight: " << item.weight << ", Value: " << item.value << '\n';
 * }
 * @endcode
 * 
 * @bug Log says the first line is malformed. The issue is benign and not worth fixing
 */
std::vector<Item> parseCSVItems(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger) {

    std::vector<Item> items;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        logger->error("Error: Unable to open file {}", filepath);
        std::exit(EXIT_FAILURE); // exit on failure
    }

    logger->info("Opened file: {}", filepath);

    std::string line;
    long int lineNumber = 0;

    while (std::getline(file, line)) {
        
        // trim whitespace from the line
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        std::stringstream ss(line);
        Item item;
        char comma; // skip the comma
        lineNumber++;

        if (ss >> item.weight >> comma >> item.value) {
            items.push_back(item);
        } else {
            logger->warn("Malformed line in file: {}, {}", lineNumber, line); //line does not show
        }
    }

    file.close();
    logger->info("Successfully parsed {} items from file {}", items.size(), filepath);
    return items;
}

/**
 * @brief Parses a CSV file to extract a list of capacities and returns a random capacity.
 * 
 * This function reads a CSV file specified by the `filepath` parameter, expecting the 
 * first line to contain the header `Capacity`. It processes subsequent lines to extract 
 * integer capacities. If the file is successfully parsed, a random capacity from the 
 * list is returned. Logs are generated for various events and errors.
 * 
 * @param filepath The path to the CSV file containing capacity data.
 * 
 * @return 
 * - A randomly selected capacity from the file if parsing is successful.
 * - `-1` if the file cannot be opened or the header is incorrect.
 * - `-2` if no valid capacities are found in the file.
 * 
 * @note 
 * - The file must contain a header `Capacity` as the first line.
 * - The logger `file_logger` is initialized if it does not already exist.
 * - Logs are written to `logs/utility.log` by default.
 * - The function uses `std::uniform_int_distribution` to randomly select a capacity.
 * 
 * @warning 
 * - Malformed lines that cannot be converted to integers are skipped and logged as warnings.
 * - If the file contains no valid capacities, an error is logged, and the function returns `-2`.
 * 
 * Example CSV File:
 * @code
 * Capacity
 * 100
 * 200
 * 300
 * @endcode
 * 
 * Example usage:
 * @code
 * int capacity = parseCSVCapacity("data/capacities.csv");
 * if (capacity < 0) {
 *     std::cerr << "Error: Failed to fetch capacity. Error code: " << capacity << '\n';
 * } else {
 *     std::cout << "Selected Capacity: " << capacity << '\n';
 * }
 * @endcode
 * 
 * Error Codes:
 * - `<error_code: -1>` Unable to open file or incorrect header.
 * - `<error_code: -2>` Unable to fetch capacity due to missing valid entries.
 */
int parseCSVCapacity(const std::string& filepath, const std::shared_ptr<spdlog::logger>& logger) {

    std::vector<int> capacities;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        logger->error("Error: Unable to open file {}", filepath);
        return -1; // Error code
    }

    logger->info("Opened file: {}", filepath);

    std::string line;
    long int lineNumber = 0;
    bool isHeader = true; // skip header

    while (std::getline(file, line)) {
        
        // trim whitespace from the line
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        lineNumber++;

        if (isHeader) {
            if (line != "Capacity") {
                logger->error("Error: Expected header 'Capacity' but found '{}'", line);
                return -1;
            }
            isHeader = false;
            continue; // move cursor
        }

        try {
            int capacity = std::stoi(line);
            capacities.push_back(capacity);
        } catch (const std::exception& e) {
            logger->warn("Malformed line: '{}', '{}'. Error: {}", line, lineNumber, e.what());
        }
    }

    file.close();

    if (capacities.empty()) {
        logger->warn("No valid capacities found in file {}", filepath);
        return -2; // Error code
    }

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(0, capacities.size() - 1);
    int randomIndex = dist(gen);

    int randomCapacity = capacities[randomIndex];
    logger->info("Selected random capacity: {}", randomCapacity);
    return randomCapacity;
}

/**
 * @brief Displays a message with a specified type.
 * 
 * This function displays a message with a specified type. The type can be one of the following:
 * - 'W': Warning
 * - 'I': Info
 * - 'S': Success
 * - 'E': Error
 * - 'D': Debug
 * 
 * The message is printed to the console with the corresponding type prefix and color.
 * 
 * @param message The message to be displayed.
 * @param type The type of the message.
 */
void displayMessage(const std::string& message, const char& type) {

    switch (type) {
        case 'W':
            std::cout << WARNING_COLOR << "<WARNING>: " << RESET_COLOR << message << std::endl;
            break;

        case 'I':
            std::cout << "<INFO>: " << message << std::endl;
            break;

        case 'S':
            std::cout << SUCCESS_COLOR << "<SUCCESS>: " << RESET_COLOR << message << std::endl;
            break;

        case 'E':
            std::cerr << ERROR_COLOR << "<ERROR>: " << RESET_COLOR << message << std::endl; // print to cerr
            break;

        case 'D':
            std::cout << DEBUG_COLOR << "<DEBUG>: " << RESET_COLOR << message << std::endl;
            break;

        default:
            std::cout << message << std::endl;
            break;
    }
}

/** -- <MOVE TO UTILITY> --
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
/**
 * @file Executor.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the function definitions used for execution of the wrappers
 * 
*/

#ifndef EXECUTOR_H
#define EXECUTOR_H

#define FMT_HEADER_ONLY

#include "Item.h"
#include "Utility.h"
#include "Logger.h"       //-- <new> --
#include "Benchmark.h"    //-- <new> --

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

// -- <initializes both of the logger objects>
void initializeLoggers(std::shared_ptr<spdlog::logger>& execTimeLogger, std::shared_ptr<spdlog::logger>& mainLogger);

// -- <map, used to track min execution times>
std::map<std::string, double> setupMinExecutionTimes();

// -- <creates an AntColony object>
AntColony setupColony();

// -- <parses the items and capacity from the input file>
std::vector<Item> parseItemsAndCapacity(std::shared_ptr<spdlog::logger>& mainLogger, int& capacity);

// -- <executes the algorithms and heuristics>
std::pair<bool, bool> executeAlgorithmsAndHeuristics(const std::vector<Item>& items, 
                                                     int capacity, 
                                                     std::map<std::string, double>& minExecutionTimes, 
                                                     std::shared_ptr<spdlog::logger>& execTimeLogger);

// -- <logs the execution results>
void logExecutionResults(std::pair<bool, bool> loggedFunction, std::map<std::string, double>& minExecutionTimes);

// -- <logs the minimum execution times>
void logMinExecutionTimes(const std::map<std::string, double>& minExecutionTimes);

// -- <benchmarks the functions>
void BenchmarkFunctions();

#endif //EXECUTOR_H
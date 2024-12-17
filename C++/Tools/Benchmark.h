/**
 * @file Benchmark.h
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief File contains all the function definitions used for benchmarking
 * 
*/

#ifndef BENCHMARK_H
#define BENCHMARK_H

#define FMT_HEADER_ONLY

#include <vector>
#include <memory>
#include <unordered_map>


#include "Item.h"

#include "../main.h"

#include <fmt/format.h> // For formatting strings
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // For file logging

// **************************************** <funcs> <algorithms> *********************************************
// --- <funcs> <algorithms> <START> ---
extern bool knapsackACOWrapper(AntColony& colony, 
                        int capacity, 
                        const std::vector<Item>& items,
                        std::map<std::string, double>& minExecutionTime,
                        std::shared_ptr<spdlog::logger> logger);

extern bool knapsackBacktrackingWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                 std::map<std::string, double>& minExecutionTime,
                                 std::shared_ptr<spdlog::logger> logger);

// --- <fix> ---
extern bool knapsackBranchAndBoundWrapper(int capacity, 
                                   const std::vector<Item>& items,
                                   std::map<std::string, double>& minExecutionTime,
                                   std::shared_ptr<spdlog::logger> logger);
// --- <fix> ---

extern bool knapsackDPWrapper(int capacity, 
                       const std::vector<Item>& items,
                       std::map<std::string, double>& minExecutionTime,
                       std::shared_ptr<spdlog::logger> logger);

extern bool knapsackMemoizationWrapper(int capacity, 
                                const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger);

extern bool knapsackRecursiveWrapper(int capacity,     
                              const std::vector<Item>& items, 
                              std::map<std::string, double>& minExecutionTime,
                              std::shared_ptr<spdlog::logger> logger);

// --- <fix> ---
extern bool knapsackSimulatedAnnealingWrapper(int capacity, 
                                       const std::vector<Item>& items,
                                       std::map<std::string, double>& minExecutionTime,
                                       std::shared_ptr<spdlog::logger> logger);
// -- <fix> -- 
// --- <funcs> <algorithms> <END> ---

// **************************************** <funcs> <heuristics> *********************************************

// --- <funcs> <heuristics> <START> ---
extern bool knapsackDealStingyWrapper(int capacity, 
                               const std::vector<Item>& items,
                               std::map<std::string, double>& minExecutionTime,
                               std::shared_ptr<spdlog::logger> logger);

extern bool knapsackDefensiveGreedyWrapper(int capacity, 
                                    const std::vector<Item>& items,
                                    std::map<std::string, double>& minExecutionTime,
                                    std::shared_ptr<spdlog::logger> logger);

extern bool knapsackHeavyGreedyWrapper(int capacity, 
                                const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger);

extern bool knapsackLimitedGreedyWrapper(int capacity, 
                                  const std::vector<Item>& items,
                                  std::map<std::string, double>& minExecutionTime,
                                  std::shared_ptr<spdlog::logger> logger);

extern bool knapsackMaxOfTwoWrapper(int capacity, 
                             const std::vector<Item>& items,
                             std::map<std::string, double>& minExecutionTime,
                             std::shared_ptr<spdlog::logger> logger);

extern bool knapsackScoredGreedyWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                 std::map<std::string, double>& minExecutionTime,
                                 std::shared_ptr<spdlog::logger> logger);

extern bool knapsackSlidingThresholdWrapper(int capacity, 
                                     const std::vector<Item>& items,
                                     std::map<std::string, double>& minExecutionTime,
                                     std::shared_ptr<spdlog::logger> logger);

extern bool knapsackStandardGreedyWrapper(int capacity, 
                                   const std::vector<Item>& items,
                                   std::map<std::string, double>& minExecutionTime,
                                   std::shared_ptr<spdlog::logger> logger);

extern bool knapsackTransitioningGreedyWrapper(int capacity, 
                                        const std::vector<Item>& items,
                                        std::map<std::string, double>& minExecutionTime,
                                        std::shared_ptr<spdlog::logger> logger);

extern bool knapsackWeightStingyWrapper(int capacity, 
                                 const std::vector<Item>& items,
                                std::map<std::string, double>& minExecutionTime,
                                std::shared_ptr<spdlog::logger> logger);
// --- <funcs> <heuristics> <END> ---


#endif //BENCHMARK_H
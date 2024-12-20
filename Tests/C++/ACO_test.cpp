/**
 * @file ACO_test.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-18
* @brief Testing for the best parameters for the ant colony optimization algorithm.
 * 
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <thread>
#include <string>
#include <atomic>

#include "../../C++/main.h"

#include "../../C++/Tools/Utility.h"
#include "../../C++/Tools/Logger.h"
#include "../../C++/Tools/Item.h"
#include "../../C++/Tools/Benchmark.h"

const std::string_view SEPARATOR = "==================================================\n";

// Define multiple test parameters
constexpr int CAPACITY_FIXED = 100;

constexpr int NUM_ANTS[] = {50, 100, 150};
constexpr int NUM_ITER[] = {500, 1000, 1500};
constexpr double ALPHA[] = {1.0, 1.5, 2.0};
constexpr double BETA[] = {2.0, 3.0, 4.0};
constexpr double EVAPORATION_RATE[] = {0.3, 0.5, 0.7};

// For logging
std::shared_ptr<spdlog::logger> test_logger = getTestLogger();

// -- <debug only> --
std::atomic<bool> stopFlag(false);

/** -- <debug only> --
 * @brief Displays a stopwatch that measures elapsed time.
 * 
 * This function starts a stopwatch and continuously displays the elapsed time in minutes, seconds, and milliseconds.
 * The stopwatch can be stopped by pressing Ctrl+C.
 */
void displayStopwatch() {

    auto startTime = std::chrono::steady_clock::now();
    std::cout << "\033[33m[RUNNING]\033[0m: Stopwatch is running...\n\n";

    while (!stopFlag) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = duration_cast<std::chrono::milliseconds>(currentTime - startTime);

        auto minutes = elapsedTime.count() / 60000;
        auto seconds = (elapsedTime.count() / 1000) % 60;
        auto milliseconds = elapsedTime.count() % 1000;

        std::cout << "\rElapsed Time: " 
                  << std::setw(2) << std::setfill('0') << minutes << "m:" 
                  << std::setw(2) << std::setfill('0') << seconds << "s:" 
                  << std::setw(3) << std::setfill('0') << milliseconds << "ms"
                  << std::flush;
 
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << "\n\033[31m[STOP]:\033[0m Stopwatch stopped.\n\n";
}

// Function to create an AntColony with specific parameters
AntColony createColony(int NUM_ANTS, int NUM_ITER, double ALPHA, double BETA, double EVAPORATION_RATE) {
    return AntColony(NUM_ANTS, NUM_ITER, ALPHA, BETA, EVAPORATION_RATE);
}

// Function to test Ant Colony Optimization using the provided knapsackACOWrapper
bool Test_ACO(int capacity, const std::vector<Item>& items, std::shared_ptr<spdlog::logger> logger, 
              int numAnts, int numIter, double alpha, double beta, double evaporationRate) {
    const std::string _NAME_ = "<a> Ant Colony Optimization";
    size_t items_size = items.size(); 
    
    bool logged = true;

    // Create the AntColony object
    AntColony colony(numAnts, numIter, alpha, beta, evaporationRate);

    // Define map to store minimum execution times
    std::map<std::string, double> minTimes;

    // Test execution with timing and logging the results using knapsackACOWrapper
    for (unsigned int i = 0; i < RUN_TIMES; i++) {
        logged = knapsackACOWrapper(colony, capacity, items, minTimes, logger);
    }

    return logged;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // Parse the items from CSV
    std::vector<Item> items = parseCSVItems(getFilePath(ITEM_1, test_logger), test_logger);

    // Define map to store minimum execution times
    std::map<std::string, double> minTimes = setupMinExecutionTimes();

    int run_number = 1;

    //BASELINE (Dynamic Programming)
    test_logger->info(SEPARATOR.data());
    test_logger->warn("BASELINE (Dynamic Programming)");
    knapsackDPWrapper(CAPACITY_FIXED, items, minTimes, test_logger);

    // Ant Colony Optimization Test
    // test_logger->info(SEPARATOR.data());
    // test_logger->warn("Ant Colony Optimization - Testing different parameters");

    std::thread stopwatchThread(displayStopwatch);

    // Loop through the different parameters (numAnts, numIter, alpha, beta, evaporationRate)
    for (int ants : NUM_ANTS) {
        for (int iter : NUM_ITER) {
            for (double alpha_val : ALPHA) {
                for (double beta_val : BETA) {
                    for (double evap_rate : EVAPORATION_RATE) {
                        test_logger->info(SEPARATOR.data());
                        test_logger->warn("Ant Colony Optimization, <run: {}> Num Ants: {} | Num Iter: {} | Alpha: {} | Beta: {} | Evaporation Rate: {}", 
                                           run_number, ants, iter, alpha_val, beta_val, evap_rate);

                        // Call the Test_ACO function with the current parameters
                        Test_ACO(CAPACITY_FIXED, items, test_logger, ants, iter, alpha_val, beta_val, evap_rate);
                        run_number++;
                    }
                }
            }
        }
    }

    stopFlag = true;

    if (stopwatchThread.joinable()) {
        stopwatchThread.join();
    }

    return 0;
}


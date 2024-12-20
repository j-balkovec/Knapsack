/**
 * @file SimulatedAnnealing_test.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Testing for the best parameters for the simulated annealing algorithm.
 *        
*/
#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include <iomanip>
#include <thread>
#include <string>
#include <atomic>

#include "../../C++/Tools/Utility.h"
#include "../../C++/Tools/Logger.h"
#include "../../C++/Tools/Item.h"
#include "../../C++/Tools/Benchmark.h"

const std::string_view SEPARATOR = "==================================================\n";

// Define multiple test parameters
constexpr int CAPACITY_FIXED = 100;

constexpr int INITIAL_TEMPERATURES[] = {50, 75, 100, 150, 200, 250};
constexpr double COOLING_RATES[] = {0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 
                                     0.8, 0.85, 0.9, 0.95, 0.99};

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

// Simulated Annealing testing function
bool Test_SA(int capacity, const std::vector<Item>& items, std::shared_ptr<spdlog::logger> logger, int initialTemp, double coolingRate) {
    const std::string _NAME_ = "<a> Simulated Annealing";
    size_t items_size = items.size(); 
    
    bool logged = true;

    // Test execution with timing and logging the results
    for (unsigned int i = 0; i < RUN_TIMES; i++) {
        auto pair = measureExecutionTime(knapsackSimulatedAnnealing, capacity, items, initialTemp, coolingRate);

        auto time = pair.first;
        auto solution = pair.second;
    
        logged = logResults(time, capacity, solution, items_size, _NAME_, logger); 
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

    // Simulated Annealing Test
    // test_logger->info(SEPARATOR.data());
    // test_logger->warn("Simulated Annealing - Testing different parameters");

    std::thread stopwatchThread(displayStopwatch);

    // Loop through the different parameters (initialTemp and coolingRate)
    for (int temp : INITIAL_TEMPERATURES) {
        for (double rate : COOLING_RATES) {
            test_logger->info(SEPARATOR.data());
            test_logger->warn("Simulated Annealing, <run: {}> Initial Temp: {} | Cooling Rate: {}", 
                               run_number, temp, rate);

            // Call the Test_SA function with the current parameters
            Test_SA(CAPACITY_FIXED, items, test_logger, temp, rate);
            run_number++;
        }
    }

    stopFlag = true;

    if (stopwatchThread.joinable()) {
        stopwatchThread.join();
    }

    return 0;
}


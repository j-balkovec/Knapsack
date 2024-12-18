/**
 * @file main.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Entry point of the program
 * 
*/
#include "../Tools/Executor.h" 
#include "../Tools/Logger.h"   //-- <new> --

#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <string>
#include <atomic>

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
    std::cout << "[RUNNING]: Stopwatch is running... Press Ctrl+C to stop.\n\n";

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

    std::cout << "\n[STOP]: Stopwatch stopped.\n";
}

/**
 * @brief The main function of the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int The exit status of the program.
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {

    std::shared_ptr<spdlog::logger> mainLogger = getMainLogger();

    try {
        mainLogger->info("[START]: Stopwatch started.");

        std::thread stopwatchThread(displayStopwatch);

        auto startNew = std::chrono::high_resolution_clock::now();
        BenchmarkFunctions();
        auto endNew = std::chrono::high_resolution_clock::now();

        stopFlag = true;

        if (stopwatchThread.joinable()) {
            stopwatchThread.join();
        }

        auto durationNew = std::chrono::duration_cast<std::chrono::milliseconds>(endNew - startNew);
        auto minutes = durationNew.count() / 60000;
        auto seconds = (durationNew.count() / 1000) % 60;
        auto milliseconds = durationNew.count() % 1000;

        // Print the formatted duration
        std::cout << "\nBenchmarkFunctionsNew took "
                  << std::setw(2) << std::setfill('0') << minutes << "m:"
                  << std::setw(2) << std::setfill('0') << seconds << "s:"
                  << std::setw(3) << std::setfill('0') << milliseconds << "ms.\n\n";

        std::string durationStr = std::to_string(durationNew.count());    


        mainLogger->info("[END]: Program completed, time: {}ms.", durationStr);
    } catch (...) {
        std::cout << "\n[ERROR]: An exception occurred. Stopping the stopwatch.\n";
        stopFlag = true;
    }

    return 0;
}
// #include "Algorithms/ACO.cpp"
// #include "Algorithms/Backtracking.cpp"
// #include "Algorithms/BranchAndBound.cpp"
// #include "Algorithms/DP.cpp"
// #include "Algorithms/Memoization.cpp"
// #include "Algorithms/Recursive.cpp"
// #include "Algorithms/SimulatedAnnealing.cpp"
// #include "Heuristics/DealStingy.cpp"
// #include "Heuristics/DefensiveGreedy.cpp"
// #include "Heuristics/HeavyGreedy.cpp"
// #include "Heuristics/LimitedGreedy.cpp"
// #include "Heuristics/MaxOfTwo.cpp"
// #include "Heuristics/ScoredGreedy.cpp"
// #include "Heuristics/SlidingThreshold.cpp"
// #include "Heuristics/StandardGreedy.cpp"
// #include "Heuristics/TransitioningGreedy.cpp"
// #include "Heuristics/WeightStingy.cpp"

#include "Tools/Item.h"
#include "Tools/Utility.h"

#include "main.h"

#include <iostream>
#include <vector>
#include <string>

//organize
const std::string DATA1 = "/Users/jbalkovec/Desktop/Knapsack/Data/Items/Items_1_12_12_2024.csv";
const std::string CAPACITY = "/Users/jbalkovec/Desktop/Knapsack/Data/Capacity/Capacity_12_12_2024.csv";

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {

    std::vector<Item> items = parseCSVItems(DATA1); //works
    int capacity = parseCSVCapacity(CAPACITY);

    std::cout << knapsackDP(capacity, items);
    int time = measureExecutionTime(knapsackDP, capacity, items);

    std::cout << "IT TOOK: " << time << "ms" << std::endl;
}

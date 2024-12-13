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

#include "Item.h"
#include "Utility.h"

#include "main.h"

#include <iostream>

[[maybe_unused]]int main(int argc, char* argv[]) {
    std::cout << "Solution: " << knapsackRecursive(50, std::vector<Item>{{60, 10}, {100, 20}, {120, 30}}, 3);
    return 0;
}

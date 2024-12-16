#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <unordered_map>
#include <iostream>

#include "Tools/Item.h"
#include "Tools/Utility.h"

// --------- <HEURISTICS> --------- //

// --- <Stingy Greedy> --- //
int dealStingyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Defensive Greedy> --- //
int defensiveGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Heavy Greedy> --- //
int heavyGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Limited Greedy> --- //
int limitedGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <MaxOfTwo Greedy> --- //
int maxOfTwoKnapsack(int capacity, const std::vector<Item>& items);

// --- <Random Greedy> --- //
int scoredGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Sliding Threshold Greedy> --- //
int slidingThresholdKnapsack(int capacity, const std::vector<Item>& items);

// --- <Standard Greedy> --- //
int standardGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Transitioning Greedy> --- //
int transitioningGreedyKnapsack(int capacity, const std::vector<Item>& items);

// --- <Weight Stingy Greedy> --- //
int weightStingyKnapsack(int capacity, const std::vector<Item>& items);

// --------- </HEURISTICS> --------- //

// --------- <ALGORITHMS> --------- //

// --- <Ant Colony> --- //
/**
 * @class AntColony
 * @brief Represents an Ant Colony Optimization algorithm for solving the Knapsack problem.
 */
class AntColony {
public:
    /**
     * @brief Constructs an AntColony object.
     * @param numAnts The number of ants in the colony.
     * @param numIterations The number of iterations to run the algorithm.
     * @param alpha The importance of pheromone trails in the decision-making process.
     * @param beta The importance of heuristic information in the decision-making process.
     * @param evaporationRate The rate at which pheromone trails evaporate.
     */
    AntColony(int numAnts, int numIterations, double alpha, double beta, double evaporationRate)
        : numAnts(numAnts), numIterations(numIterations), alpha(alpha), beta(beta), evaporationRate(evaporationRate) {}

    // -- <debug> -- Display values
    void display() const {
        std::cout << "Number of Ants: " << numAnts << "\n"
                  << "Number of Iterations: " << numIterations << "\n"
                  << "Alpha: " << alpha << "\n"
                  << "Beta: " << beta << "\n"
                  << "Evaporation Rate: " << evaporationRate << "\n";
    }

    /**
     * @brief Solves the Knapsack problem using the Ant Colony Optimization algorithm.
     * @param capacity The maximum capacity of the knapsack.
     * @param items The list of items available for selection.
     * @return The maximum value that can be obtained by selecting items.
     */
    int knapsackACO(int capacity, const std::vector<Item>& items);

private:
    int numAnts;            /**< The number of ants in the colony. */
    int numIterations;      /**< The number of iterations to run the algorithm. */
    double alpha;           /**< The importance of pheromone trails in the decision-making process. */
    double beta;            /**< The importance of heuristic information in the decision-making process. */
    double evaporationRate; /**< The rate at which pheromone trails evaporate. */

    std::vector<std::vector<double>> pheromones; /**< The pheromone levels on each edge of the problem graph. */
    std::vector<int> bestSolution;               /**< The best solution found so far. */
    int bestValue;                               /**< The value of the best solution found so far. */

    /**
     * @brief Calculates the fitness of a solution.
     * @param solution The solution to evaluate.
     * @param items The list of items available for selection.
     * @param capacity The maximum capacity of the knapsack.
     * @return The fitness value of the solution.
     */
    double calculateFitness_ACO(const std::vector<int>& solution, const std::vector<Item>& items, int capacity);

    /**
     * @brief Updates the pheromone levels based on the solutions found by the ants.
     * @param solutions The solutions found by the ants.
     * @param fitness The fitness values of the solutions.
     */
    void updatePheromones(const std::vector<std::vector<int>>& solutions, const std::vector<int>& fitness);
};

// --- <Backtracking> --- //
int knapsackBacktracking(int capacity, const std::vector<Item>& items, int n, int currentWeight, int currentValue, int index);

// --- <Branch and Bound> --- //
// A class to represent the state of the knapsack at any point during branch and bound
class Node {
public:
    int level;      /**< Level of node in decision tree >*/
    int profit;     /**< Profit so far >*/
    int weight;     /**< Weight so far >*/
    int bound;      /**< Upper bound of maximum profit in subtree >*/
};
int bound(Node& u, int n, int capacity, const std::vector<Item>& items);
int knapsackBranchAndBound(int capacity, const std::vector<Item>& items);

// --- <Dynamic Programming> --- //
int knapsackDP(int capacity, const std::vector<Item>& items);

// --- <Memoization Algorithm> --- //
int knapsackMemoization(int capacity, const std::vector<Item>& items);
int knapsackMemoHelper(int capacity, const std::vector<Item>& items, int n, std::unordered_map<std::string, int>& memo);

// --- <Recursive Algorithm> --- //
int knapsackRecursive(int capacity, const std::vector<Item>& items, int n);

// --- <Simulated Annealing> --- //
int calculateFitness_SimA(const std::vector<int>& solution, const std::vector<Item>& items, int capacity);
std::vector<int> getNeighborSolution(const std::vector<int>& solution);
int knapsackSimulatedAnnealing(int capacity, const std::vector<Item>& items, double initialTemperature, double coolingRate);

// --------- </ALGORITHMS> --------- //
#endif // !MAIN_H


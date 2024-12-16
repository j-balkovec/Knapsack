/**
 * @file SimulatedAnnealing.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief Simulated Annealing algorithm for the knapsack problem.
 *         TC: O(n), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../main.h"
#include "../Tools/Item.h"

/**
 * Calculates the fitness of a solution for the knapsack problem.
 * The fitness is determined by the total value of the selected items in the solution.
 *
 * @param solution The binary representation of the solution, where 1 indicates an item is selected and 0 indicates it is not.
 * @param items The vector of Item objects representing the available items.
 * @param capacity The maximum weight capacity of the knapsack.
 * @return The fitness value of the solution, which is the total value of the selected items.
 *         If the total weight of the selected items exceeds the capacity, the fitness value is 0 (invalid solution).
 */
int calculateFitness_SimA(const std::vector<int>& solution, const std::vector<Item>& items, int capacity) {
    int totalWeight = 0;
    int totalValue = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i] == 1) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    if (totalWeight > capacity) {
        return 0; // Invalid solution (over the weight limit)
    }
    return totalValue;
}

/**
 * @brief Generates a neighbor solution by flipping a random element in the given solution.
 * 
 * @param solution The original solution.
 * @return The neighbor solution.
 */
std::vector<int> getNeighborSolution(const std::vector<int>& solution) {
    std::vector<int> newSolution = solution;
    int randomIndex = rand() % solution.size();
    newSolution[randomIndex] = 1 - newSolution[randomIndex]; // Flip the value
    return newSolution;
}

/**
 * @brief Solves the knapsack problem using the Simulated Annealing algorithm.
 * 
 * @param capacity The maximum capacity of the knapsack.
 * @param items A vector of Item objects representing the available items.
 * @param initialTemperature The initial temperature for the Simulated Annealing algorithm.
 * @param coolingRate The cooling rate for the Simulated Annealing algorithm.
 * @return The maximum fitness value achieved by the algorithm.
 */
int knapsackSimulatedAnnealing(int capacity, const std::vector<Item>& items, double initialTemperature, double coolingRate) {
    srand(time(NULL));

    size_t numItems = items.size();
    std::vector<int> currentSolution(numItems, 0);
    int currentFitness = calculateFitness_SimA(currentSolution, items, capacity);

    std::vector<int> bestSolution = currentSolution;
    int bestFitness = currentFitness;

    double temperature = initialTemperature;

    while (temperature > 1) {
        std::vector<int> newSolution = getNeighborSolution(currentSolution);
        int newFitness = calculateFitness_SimA(newSolution, items, capacity);

        if (newFitness > currentFitness || exp((newFitness - currentFitness) / temperature) > ((double) rand() / (RAND_MAX))) {
            currentSolution = newSolution;
            currentFitness = newFitness;
        }

        if (currentFitness > bestFitness) {
            bestSolution = currentSolution;
            bestFitness = currentFitness;
        }

        temperature *= coolingRate; // Reduce temperature
    }

    return bestFitness;
}

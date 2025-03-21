/**
 * @file ACO.cpp
 * 
 * @author Jakob Balkovec
 * @date 2024-12-12
 * @brief ACO - Ant Colony Optimization algorithm for the knapsack problem.
 *         TC: O(n^2), where n is the number of items.
 * 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "../Tools/Item.h"
#include "../main.h"

/**
 * @brief Calculates the fitness of a solution.
 * @param solution The solution to evaluate.
 * @param items The list of items available for selection.
 * @param capacity The maximum capacity of the knapsack.
 * @return The fitness value of the solution.
 */
double AntColony::calculateFitness_ACO(const std::vector<int>& solution, const std::vector<Item>& items, int capacity) {
    int totalWeight = 0;
    int totalValue = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i] == 1) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    if (totalWeight > capacity) {
        return 0; 
    }
    return totalValue;
}

/**
 * @brief Updates the pheromone levels based on the solutions found by the ants.
 * @param solutions The solutions found by the ants.
 * @param fitness The fitness values of the solutions.
 */
void AntColony::updatePheromones(const std::vector<std::vector<int>>& solutions, const std::vector<int>& fitness) {
    for (size_t i = 0; i < pheromones.size(); ++i) {
        for (size_t j = 0; j < pheromones[i].size(); ++j) {
            pheromones[i][j] *= (1 - evaporationRate); 
        }
    }

    // deposit new pheromones based on solutions
    for (size_t ant = 0; ant < (size_t)numAnts; ++ant) {
        for (size_t i = 0; i < solutions[ant].size(); ++i) {
            if (solutions[ant][i] == 1) {
                pheromones[i][i] += fitness[ant]; // increase pheromone level for the chosen item
            }
        }
    }
}

/**
 * @brief Solves the Knapsack problem using the Ant Colony Optimization algorithm.
 * @param capacity The maximum capacity of the knapsack.
 * @param items The list of items available for selection.
 * @return The maximum value that can be obtained by selecting items.
 */
int AntColony::knapsackACO(int capacity, const std::vector<Item>& items) {
    srand(time(0));

    size_t numItems = items.size();
    pheromones.resize(numItems, std::vector<double>(numItems, 1.0)); // initialize pheromone levels
    bestSolution.resize(numItems, 0);
    bestValue = 0;

    for (int iteration = 0; iteration < numIterations; ++iteration) {
        std::vector<std::vector<int>> solutions(numAnts, std::vector<int>(numItems, 0));
        std::vector<int> fitness(numAnts, 0);

        // each ant constructs a solution
        for (int ant = 0; ant < numAnts; ++ant) {
            for (size_t item = 0; item < numItems; ++item) {
                // calculate probability of including this item based on pheromones and heuristic
                double prob = pow(pheromones[item][item], alpha) * pow(1.0 / items[item].weight, beta);
                if ((rand() % 100) < prob * 100) {
                    solutions[ant][item] = 1;
                }
            }

            // calculate the fitness (value) of the solution
            fitness[ant] = static_cast<int>(calculateFitness_ACO(solutions[ant], items, capacity));
        }

        // find the best solution for this iteration
        for (int ant = 0; ant < numAnts; ++ant) {
            if (fitness[ant] > bestValue) {
                bestValue = fitness[ant];
                bestSolution = solutions[ant];
            }
        }

        // update pheromones based on the solutions
        updatePheromones(solutions, fitness);
    }

    return bestValue;
}


# Knapsack Problem Solver

## Project Overview
This repository contains implementations of various algorithms to solve the **Knapsack Problem**. The project includes both **exact** and **heuristic** approaches, implemented in **C++**. Additionally, Python scripts are used for data generation and analysis.

## Algorithms Implemented
### **Exact Approaches**
- **Backtracking** – Exhaustive search for optimal solutions.
- **Branch and Bound** – Efficient pruning to reduce search space.
- **Dynamic Programming (DP)** – Bottom-up table-filling approach.
- **Memoization** – Top-down recursive approach with caching.
- **Recursive Solution** – Brute force method using recursion.

### **Metaheuristic Approaches**
- **Ant Colony Optimization (ACO)** – Inspired by the behavior of ants to find near-optimal solutions.
- **Simulated Annealing (SA)** – Probabilistic optimization inspired by annealing in metallurgy.

### **Greedy Heuristics**
- **Standard Greedy** – Selects items based on the highest value-to-weight ratio.
- **Defensive Greedy** – Conservative selection approach.
- **Heavy Greedy** – Prioritizes heavier items.
- **Limited Greedy** – Restricts item choices to predefined criteria.
- **Scored Greedy** – Uses a scoring function for selection.
- **Sliding Threshold** – Adjusts selection criteria dynamically.
- **Transitioning Greedy** – Evolves selection strategy over iterations.
- **Weight Stingy** – Prefers lighter items to maximize count.
- **Deal Stingy** – Prefers high-value items with minimal weight.
- **Max of Two** – Chooses between two best strategies dynamically.

## Project Structure
```sh
# Obtained using "tree"
├── Analysis/                  # Performance and accuracy analysis
├── C++/
│   ├── Algorithms/            # Core algorithm implementations
│   ├── Heuristics/            # Greedy and heuristic methods
│   ├── Tools/                 # Benchmarking, execution, and logging utilities
│   ├── main.cpp               # Main program
│   ├── Makefile               # Compilation script
│   ├── bin/                   # Compiled executables
│   ├── obj/                   # Object files
├── Data/                      # Input datasets
│   ├── Capacity/              # Knapsack capacities
│   ├── Items/                 # Item lists
├── Logs/                      # Execution logs and results
├── Python/                    # Auxiliary Python scripts (data generation, cleanup)
├── Tests/                     # Unit tests for algorithms
│   ├── C++/                   # C++ tests
│   ├── Python/                # Python tests and analysis
├── docs/                      # Documentation
├── README.md                  # Project documentation
├── LICENSE                    # Licensing information
```
## How to Compile & Run
```sh
cd C++/
make                # Compile the project
./bin/main          # Run the main executable
```

## How to Test
```sh
cd Tests/C++
make                # Compile test binaries
./bin/ACO_test      # Run ACO test
./bin/SimulatedAnnealing_test
```

## Data Generation
To generate item and capacity datasets:
```sh
python Python/input_generator.py
```

## Logs & Benchmarking
- Execution logs stored in `Logs/`
- Benchmarking tools available in `C++/Tools/`

## References
- [Knapsack Problem](https://en.wikipedia.org/wiki/Knapsack_problem)

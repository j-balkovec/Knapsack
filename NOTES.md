# Notes
### **Project Title:**

**Performance Analysis of Knapsack Problem Solutions**

---

### **Objective**

The goal is to implement different solutions to the Knapsack problem (Recursive, a bunch of Greedy Heuristics) in C++, Then use a Python script to orchestrate their execution on separate threads, measure execution time, and analyze performance.

---

### **Overview:**

This project is supposed to demonstrate the differences in computational efficiency between three approaches to solving the Knapsack problem

1. C++ implementations
2. A Python script to generate input data, run the C++ programs in parallel, and measure execution time
3. Output logs/excel file/plots that compare the performance of the algorithms

---

### **Requirements:**

- Programming Languages: **C++** (for the algorithms), **Python** (for orchestration and data generation), and **R** (for data analysis).
- Knowledge of multithreading in Python and basic file handling in both C++ and Python

---

### **Components:**

### 1. **C++ Implementations**

Create 11 separate scripts:

1. **Algorithm** (`#.cpp`)
    - Implements a brute-force recursive approach.
    - Input: Number of items, weights, values, and capacity.
    - Output: Optimal value of the knapsack.
2. **Greedy Heuristics** (`heur#_knapsack.cpp`)
    - Implements the greedy method for the problem.
    - Input: Same as above.
    - Output: "Optimal" value of the knapsack.

**Input and Output Format**

- **Input:**
    
    A text file where the first line contains the number of items and the knapsack's capacity. Subsequent lines list the weight and value of each item (subject to change).
    
    Example:
    
    ```
    4 50
    10 60
    20 100
    30 120
    40 240
    
    ```
    
- **Output:**
    
    A single integer, representing the maximum value.
    

---

### 2. **Python Input Data Generator**

Python script to generate test cases. The script should:

- Take the number of items and value/weight ranges as inputs.
- Randomly generate weights and values within the specified range.
- Save data in a format compatible with the C++ scripts.

**Example Python Code**

```python
import random

def generate_knapsack_data(num_items, weight_range, value_range, capacity_range, filename):
    weights = [random.randint(1, weight_range) for _ in range(num_items)]
    values = [random.randint(1, value_range) for _ in range(num_items)]
    capacity = random.randint(1, capacity_range)

    with open(filename, "w") as f:
        f.write(f"{num_items} {capacity}\n")
        for w, v in zip(weights, values):
            f.write(f"{w} {v}\n")

if __name__ == "__main__":
    generate_knapsack_data(50, 100, 200, 1000, "input_data.txt")

```

---

### 3. **Python Orchestration Script**

- Execute the three C++ scripts using `subprocess`
- Run them in parallel using Python threads
- Measure their execution time
- Capture and save their output for comparison

**Example Python Code**

```python
import subprocess
import threading
import time

def run_cpp_script(script_path, input_file, output_file):
    start_time = time.time()
    process = subprocess.run([script_path, input_file, output_file], capture_output=True)
    end_time = time.time()
    if process.returncode != 0:
        print(f"Error running {script_path}: {process.stderr.decode()}")
        return None
    return end_time - start_time

if __name__ == "__main__":
    scripts = ["./rec_knapsack", "./dp_knapsack", "./memo_knapsack"]
    input_file = "input_data.txt"
    output_files = [f"output_{script.split('/')[-1]}.txt" for script in scripts]

    threads = []
    results = {}

    for script, output in zip(scripts, output_files):
        thread = threading.Thread(
            target=lambda s, i, o: results.update({s: run_cpp_script(s, i, o)}),
            args=(script, input_file, output)
        )
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("Results:")
    for script, exec_time in results.items():
        print(f"{script}: {exec_time:.4f} seconds")

```

---

### 4. **Output Logs and Comparison**

Each script should log:

1. Execution time
2. Input size (number of items)
3. Capacity
4. Solution (maximum value)

Python should consolidate these logs into a single report for analysis

---

### **Deliverables:**

1. **10 C++ programs**
2. **Python input generator**: Generates test cases for the algorithms
3. **Python orchestrator**: Runs the C++ programs in parallel, captures output, and measures execution time
4. **Analysis Report**: A consolidated log showing execution times and results for different inputs

---

### **Stretch Goals:**

1. Automate testing for multiple input sizes and configurations
2. Visualize the results (e.g., execution time vs. input size) using `R`
3. Analyze memory usage alongside execution time

# Potential Directory Structure

```
Knapsack/
├── C++
│   ├── rec_knapsack.cpp            # Recursive solution implementation
│   ├── heur1_knapsack.cpp          # Greedy heuristic 1: Value-to-Weight ratio
│   ├── heur2_knapsack.cpp          # Greedy heuristic 2: Minimum Weight
│   ├── heur3_knapsack.cpp          # Greedy heuristic 3: Maximum Value
│   ├── heur4_knapsack.cpp          # Hybrid: Value-to-Weight and Weight
│   ├── heur5_knapsack.cpp          # Hybrid: Value-to-Weight and Value
│   ├── heur6_knapsack.cpp          # Maximum Value per Item
│   ├── heur7_knapsack.cpp          # Minimum Weight per Item
│   ├── heur8_knapsack.cpp          # Random Item Selection
│   ├── heur9_knapsack.cpp          # Most Frequent Weight Range
│   ├── heur10_knapsack.cpp         # Least Frequent Weight Range
│   └── Makefile                    # Compile all C++ programs (optional)
├── Python/
│   ├── input_generator.py          # Script to generate test cases
│   ├── orchestrator.py             # Script to orchestrate execution
│   ├── logs/
│   │   ├── execution_log.log       # Consolidated execution logs
│   │   ├── output_heur1.txt        # Outputs for heuristic 1
│   │   ├── output_heur2.txt        # Outputs for heuristic 2
│   │   └── ...                     # Outputs for other heuristics
│   └── test_inputs/
│       ├── input1.txt              # Example test case 1
│       ├── input2.txt              # Example test case 2
│       └── ...                     # Additional test cases
├── Analysis/
│   ├── results_analysis.Rmd        # R notebook for performance analysis
│   ├── plots/
│   │   ├── execution_time.png      # Execution time vs input size visualization
│   │   ├── heur_comparison.png     # Comparison of heuristics
│   │   └── ...                     # Additional visualizations
├── docs/
│   ├── README.md                   # Project description and setup instructions
│   └── knapsack_report.pdf         # Final analysis report
├── .gitignore                      # Git ignore file for logs, binaries, etc.
└── LICENSE                         # License (if applicable)
```



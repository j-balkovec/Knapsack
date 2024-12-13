# Heuristics

This repository contains various heuristic algorithms for solving the 0/1 Knapsack problem. The following heuristics are implemented:

1. **DealStingy.cpp** - A greedy approach that removes the "worst deals" based on the score  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

2. **DefensiveGreedy.cpp** - Greedy algorithm that prioritizes lighter items to maximize the number of items in the knapsack  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

3. **HeavyGreedy.cpp** - Greedy algorithm that sorts items by value and selects the highest value items first  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

4. **LimitedGreedy.cpp** - Greedy algorithm with capacity limits that selects items based on a ratio of value-to-weight  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

5. **MaxOfTwo.cpp** - Combines the results of Standard Greedy and Heavy Greedy to select the best solution  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

6. **ScoredGreedy.cpp** - Greedy algorithm that uses a custom scoring function based on value and weight  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

7. **SlidingThreshold.cpp** - Greedy algorithm with a sliding threshold to adjust the selection of items  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

8. **StandardGreedy.cpp** - Standard greedy algorithm that selects items based on value-to-weight ratio  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

9. **TransitioningGreedy.cpp** - Greedy algorithm that transitions from a heavy greedy approach to a scored greedy approach  
   - **Time Complexity:** \(O(n \log n)\) due to sorting

10. **WeightStingy.cpp** - Greedy algorithm that prioritizes lighter items, removing the least weighty items when the knapsack is overfilled  
    - **Time Complexity:** \(O(n \log n)\) due to sorting

---

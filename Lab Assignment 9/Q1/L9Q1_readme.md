# DAA Lab Assignment 09 - Question 1

## Problem Statement
[Fractional Knapsack with Deterioration Rate] You have n items with base values vi, weights wi, and decay rates λi > 0. If an item is consumed at time t, its effective value density decays to (vi / wi) - λi * t. Knapsack capacity is W. Determine the optimal scheduling order and fractional choices to maximise total value. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The problem combines fractional knapsack selection with continuous time-dependent deterioration of item value densities.

Given n items, each with base value vi, weight wi, and decay rate λi, with knapsack capacity W:
1. Deterioration and Marginal Value:
   - If an item (or fraction of it) is packed starting at elapsed time t, its effective density is given by:
     `eff_density = (vi / wi) - λi * t`
   - Consuming a weight fraction `take_weight` contributes `take_weight * eff_density` to the total knapsack value.
2. Greedy Exchange Principle:
   - Items with a steeper deterioration rate λi lose marginal value density faster per unit of elapsed time.
   - By greedy exchange arguments, processing items with higher decay rates earlier strictly dominates any delayed alternative ordering, minimizing cumulative decay loss across the timeline.
3. Tie-Breaking Strategy:
   - If two items possess identical decay rates λi, ties are broken by sorting in descending order of their base value densities `(vi / wi)`.
4. Greedy Fractional Allocation:
   - Items are sorted according to this priority order.
   - We iterate through the sorted list, allocating as much weight as possible without exceeding the remaining knapsack capacity W.
   - The elapsed time t advances strictly by the weight of the items packed.
   - If at time t the effective density of an item becomes non-positive (`eff_density <= 0`), taking further portions of that item yields no positive value gain, and it is safely omitted.

---

## Algorithm
1. Read the number of items n and the knapsack capacity W.
2. For each item i from 0 to n - 1:
   - Read base value vi, weight wi, and decay rate λi.
   - Compute initial value density: `density = vi / wi`.
3. Sort items in descending order of decay rate λi; break ties by initial value density descending.
4. Initialize `current_weight = 0.0`, `current_time = 0.0`, and `total_value = 0.0`.
5. Iterate through each sorted item i from 0 to n - 1:
   - If `current_weight >= W`, terminate selection.
   - Compute allowable weight fraction: `take_weight = min(wi, W - current_weight)`.
   - Calculate effective density at current time:
     `eff_density = density - (λi * current_time)`.
   - If `eff_density > 0`:
     - Add `take_weight * eff_density` to `total_value`.
     - Print details of the selected item fraction, effective density, and gained value.
     - Increment `current_weight` by `take_weight`.
     - Increment `current_time` by `take_weight`.
   - Else:
     - Skip the item as its value density has decayed to non-positive.
6. Display the final packed weight and the maximum total value achieved.

---

## Pseudocode
Algorithm FractionalKnapsackWithDecay(items[], n, W):
    Input: Array of items with fields (v, w, lambda), total items n, knapsack capacity W
    Output: Maximum total accumulated value and optimal selection schedule

    For i <- 0 to n - 1 do
        items[i].density <- items[i].v / items[i].w
    End For

    Sort items descending by lambda (tie-breaker: descending density)

    current_weight <- 0.0
    current_time <- 0.0
    total_value <- 0.0

    For i <- 0 to n - 1 do
        If current_weight >= W then
            Break
        End If

        take_weight <- min(items[i].w, W - current_weight)
        eff_density <- items[i].density - (items[i].lambda * current_time)

        If eff_density > 0 then
            total_value <- total_value + (take_weight * eff_density)
            current_weight <- current_weight + take_weight
            current_time <- current_time + take_weight
        End If
    End For

    Print "Total weight packed: ", current_weight, " / ", W
    Print "Maximum total value achieved: ", total_value
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the input preprocessing, sorting, and linear greedy traversal:
1. Input reading and initial density computation:
   - Iterating over n items to compute `vi / wi` runs in O(n) time.
2. Sorting items:
   - Bubble sort performs comparisons across outer and inner loops:
     Sum over i from 0 to n - 2 of (n - i - 1) = n * (n - 1) / 2 comparisons, requiring Θ(n^2) time.
   - (Note: Implementing an optimal comparison sort such as MergeSort or QuickSort reduces this step to O(n log n)).
3. Greedy allocation loop:
   - The loop visits each candidate item at most once (n iterations).
   - In each iteration, fractional arithmetic and variable updates execute in O(1) constant time, yielding O(n) total time.

Total Time Complexity:
T(n) = O(n) + Θ(n^2) + O(n) = Θ(n^2) (or O(n log n) with standard optimal sorting).


---

## Sample Output
Enter number of items (n): 3
Enter knapsack capacity (W): 10
Enter base value (v), weight (w), and decay rate (lambda) for each item:
60 5 0.5
100 4 0.8
120 6 0.2

--- Optimal Scheduling & Selection Order ---
Item 2: Took weight = 4.00 / 4.00 (Fraction = 1.00) at time t = 0.00 | Eff. Density = 25.000 | Value Gained = 100.00
Item 1: Took weight = 5.00 / 5.00 (Fraction = 1.00) at time t = 4.00 | Eff. Density = 10.000 | Value Gained = 50.00
Item 3: Took weight = 1.00 / 6.00 (Fraction = 0.17) at time t = 9.00 | Eff. Density = 18.200 | Value Gained = 18.20

Total weight packed: 10.00 / 10.00
Maximum total value achieved: 168.20

---

## Conclusion
The algorithm optimally integrates greedy job scheduling with fractional knapsack packing. By prioritizing items with higher deterioration rates earlier, the greedy exchange property ensures that value loss due to time decay is systematically minimized. Allocating continuous fractions up to the capacity boundary guarantees maximum total value in polynomial time.

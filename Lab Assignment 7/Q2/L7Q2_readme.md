# DAA Lab Assignment 07 - Question 2

## Problem Statement
[Super egg testing experiment] A firm has invented a super-strong egg. For publicity purposes, it wants to determine the highest floor in a 100-storey building from which such an egg can fall without breaking. The firm has given a tester two identical eggs to experiment with. Of course, the same egg can be dropped multiple times unless it breaks. What is the minimum number of droppings that is guaranteed to determine the highest safe floor in all cases? Design a dynamic programming generalized solution for E eggs and F floors.

By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The problem requires finding the minimum number of trials needed in the worst-case scenario to identify the critical floor using E eggs and F floors. 

We apply dynamic programming using a 2D table `dp[i][j]`, where `i` denotes the number of available eggs (1 to E) and `j` denotes the number of remaining floors to test (0 to F):
- If an egg is dropped from the k-th floor (where 1 <= k <= j):
  1. The egg breaks: We now test the remaining (k - 1) floors below with (i - 1) eggs -> `dp[i - 1][k - 1]`.
  2. The egg does not break: We now test the remaining (j - k) floors above with all `i` eggs -> `dp[i][j - k]`.
- Since we must guarantee finding the threshold in the worst case, we take the maximum of these two outcomes:
  `worst_case = 1 + max(dp[i - 1][k - 1], dp[i][j - k])`
- To find the optimal drop strategy, we choose the floor k that minimizes this worst-case outcome:
  `dp[i][j] = min(1 + max(dp[i - 1][k - 1], dp[i][j - k]))` for all 1 <= k <= j.

Base Cases:
- `dp[i][0] = 0` (0 floors require 0 drops)
- `dp[i][1] = 1` (1 floor requires 1 drop)
- `dp[1][j] = j` (with 1 egg, we must test floors sequentially from 1 to j)

---

## Algorithm
1. Read the number of eggs (E) and number of floors (F).
2. If E <= 0 or F < 0, display an error message and terminate.
3. Initialize a 2D table `dp[E + 1][F + 1]`.
4. Initialize the base cases:
   - For every egg count i from 1 to E, set `dp[i][0] = 0` and `dp[i][1] = 1`.
   - For floor count j from 1 to F with 1 egg, set `dp[1][j] = j`.
5. For egg count i from 2 to E:
   - For floor count j from 2 to F:
     - Set min_drops to infinity.
     - For each trial floor k from 1 to j:
       - Compute `worst_case = 1 + max(dp[i - 1][k - 1], dp[i][j - k])`.
       - If `worst_case < min_drops`, update `min_drops = worst_case`.
     - Assign `dp[i][j] = min_drops`.
6. Print `dp[E][F]` as the guaranteed minimum number of drops.

---

## Pseudocode
Algorithm SuperEggDrop(E, F):
    Input: Number of eggs E, Number of floors F
    Output: Minimum number of droppings guaranteed in worst case

    If E <= 0 or F < 0 then
        Print "Invalid input."
        Return
    End If

    Declare dp[E + 1][F + 1]

    For i <- 1 to E do
        dp[i][0] <- 0
        dp[i][1] <- 1
    End For

    For j <- 1 to F do
        dp[1][j] <- j
    End For

    For i <- 2 to E do
        For j <- 2 to F do
            min_drops <- infinity
            For k <- 1 to j do
                worst_case <- 1 + max(dp[i - 1][k - 1], dp[i][j - k])
                If worst_case < min_drops then
                    min_drops <- worst_case
                End If
            End For
            dp[i][j] <- min_drops
        End For
    End For

    Print "Minimum number of droppings guaranteed: ", dp[E][F]
End Algorithm

---

## Complexity Analysis
The time complexity is derived by counting the nested iterations required to construct the DP table:
1. Base cases initialization:
   - Outer loop runs E times: O(E)
   - Loop for 1 egg runs F times: O(F)
2. Table filling:
   - The outer loop runs for eggs from i = 2 to E: (E - 1) iterations.
   - The intermediate loop runs for floors from j = 2 to F: (F - 1) iterations.
   - The inner loop iterates through all trial floors k from 1 to j: j iterations.
3. Total number of inner operations:
   Sum over i from 2 to E of (Sum over j from 2 to F of j)
   = (E - 1) * [ (F * (F + 1) / 2) - 1 ]
   = O(E * F^2)

Total Time Complexity:
T(E, F) = O(E + F) + O(E * F^2) = O(E * F^2)

---

## Sample Output
Enter number of eggs (E): 2
Enter number of floors (F): 100
Minimum number of droppings guaranteed: 14

---

## Conclusion
For a 100-storey building with 2 eggs, the minimum number of droppings guaranteed to determine the highest safe floor in all cases is 14. The dynamic programming formulation systematically evaluates every possible drop floor k and minimizes the worst-case branch, providing the exact optimal strategy for arbitrary values of eggs and floors.
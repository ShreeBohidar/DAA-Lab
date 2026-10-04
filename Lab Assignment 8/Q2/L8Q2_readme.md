# DAA Lab Assignment 08 - Question 2

## Problem Statement
[Coin Change: Total number of ways] Given an array of distinct positive integers representing coin denominations C = {c1, c2, ..., cn} and a target amount V, find the total number of distinct combinations of coins that sum up to V. You may assume an infinite supply of each coin denomination. The order of coins does not matter. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
To count distinct combinations (un-ordered selections), we must avoid counting permutations of the same set of coins:
1. Dynamic Programming Formulation:
   - Let `dp[j]` represent the total number of combinations to make sum `j` using a subset of coin denominations.
   - Base Case: `dp[0] = 1`, because there is exactly 1 way to make amount 0 (by choosing no coins).
   - Initialize all other entries `dp[1..V] = 0`.
2. Coin-by-Coin Progression:
   - By iterating over coins in the outer loop and target amount `j` in the inner loop, each coin is incorporated sequentially. This strictly maintains sorted coin order and prevents counting permutations (e.g., 1+2 and 2+1) as distinct configurations.
3. Recurrence Relation:
   - For a given coin:
     `dp[j] = dp[j] + dp[j - coin]` for all `coin <= j <= V`.

---

## Algorithm
1. Read the number of coin denominations (n).
2. Read the distinct coin values array `coins` of size n.
3. Read the target amount (V).
4. Initialize an array `dp` of size `V + 1` with 0.
5. Set `dp[0] = 1`.
6. Iterate over each denomination `i` from 0 to n - 1:
   - Let `coin = coins[i]`.
   - Iterate amount `j` from `coin` to V:
     - Update `dp[j] = dp[j] + dp[j - coin]`.
7. Output `dp[V]` as the total number of ways.

---

## Pseudocode
Algorithm CountCoinChangeWays(coins[], n, V):
    Input: Array coins of size n, target amount V
    Output: Total number of distinct coin combinations summing to V

    Declare dp[V + 1]
    dp[0] <- 1

    For j <- 1 to V do
        dp[j] <- 0
    End For

    For i <- 0 to n - 1 do
        coin <- coins[i]
        For j <- coin to V do
            dp[j] <- dp[j] + dp[j - coin]
        End For
    End For

    Return dp[V]
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the nested loop structure:
1. Initializing the DP array takes O(V) time.
2. The outer loop executes exactly n times (once for each denomination).
3. For denomination `coins[i]`, the inner loop executes (V - coins[i] + 1) times.
4. In the worst case where coin value is 1, the inner loop runs V times.
5. Total inner loop additions across all passes:
   Sum over i from 0 to n - 1 of [ V - coins[i] + 1 ] <= n * V

Total Time Complexity:
T(n, V) = O(V) + O(n * V) = O(n * V)

---

## Sample Output
Enter number of coin denominations: 3
Enter the 3 distinct coin denominations: 1 2 5
Enter target amount (V): 5
Total number of ways to make amount 5: 4

---

## Conclusion
The dynamic programming formulation solves the coin change combination counting problem efficiently. By placing the loop over coins as the exterior loop, it avoids duplicate permutations and accumulates combination frequencies in O(n * V) time while requiring only O(V) auxiliary space.
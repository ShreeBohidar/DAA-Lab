# DAA Lab Assignment 08 - Question 1

## Problem Statement
[Minimum Coin Change] Given an integer array of coin denominations C = {c1, c2, ..., cn} representing coins of different values, and an integer target amount V, find the minimum number of coins needed to make up that amount. You may assume an infinite supply of each coin denomination. If that amount of money cannot be made up by any combination of the coins, return -1. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The minimum coin change problem exhibits optimal substructure and overlapping subproblems:
1. Dynamic Programming Formulation:
   - Let `dp[i]` denote the minimum number of coins needed to make a total amount of `i`.
   - Base Case: `dp[0] = 0` (zero coins are needed to make an amount of 0).
   - For all other amounts `i` from 1 to V, initialize `dp[i]` with infinity (represented by `V + 1`).
2. Recurrence Relation:
   - For each amount `i` from 1 to V and each coin `c` in C:
     `dp[i] = min(dp[i], 1 + dp[i - c])` for all `c <= i`.
3. Order of Evaluation:
   - Compute `dp[i]` in ascending order of `i` from 1 up to V.
4. Feasibility Check:
   - If `dp[V] > V`, it implies that the amount cannot be formed using the given denominations, returning -1. Otherwise, return `dp[V]`.

---

## Algorithm
1. Read the number of denominations (n).
2. Read the coin values array `coins` of size n.
3. Read the target amount (V).
4. Initialize an array `dp` of size `V + 1`.
5. Set `dp[0] = 0`.
6. For each `i` from 1 to V:
   - Set `dp[i] = V + 1`.
7. For each `i` from 1 to V:
   - For each `j` from 0 to n - 1:
     - If `coins[j] <= i`:
       - Calculate `subResult = dp[i - coins[j]]`.
       - If `subResult != V + 1` and `subResult + 1 < dp[i]`:
         - Update `dp[i] = subResult + 1`.
8. If `dp[V] > V`, print that it is not possible to form the amount (-1). Otherwise, print `dp[V]`.

---

## Pseudocode
Algorithm MinCoinChange(coins[], n, V):
    Input: Array coins of size n, target amount V
    Output: Minimum number of coins to form V, or -1 if impossible

    Declare dp[V + 1]
    dp[0] <- 0

    For i <- 1 to V do
        dp[i] <- V + 1
    End For

    For i <- 1 to V do
        For j <- 0 to n - 1 do
            If coins[j] <= i then
                subResult <- dp[i - coins[j]]
                If subResult != V + 1 and subResult + 1 < dp[i] then
                    dp[i] <- subResult + 1
                End If
            End If
        End For
    End For

    If dp[V] > V then
        Return -1
    Else
        Return dp[V]
    End If
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the bottom-up table construction:
1. Base case and sentinel initialization from 1 to V takes O(V) time.
2. The outer loop runs for each monetary value from 1 to V: V iterations.
3. The inner loop evaluates every coin denomination: n iterations.
4. Inside the inner loop, all operations (subtraction, comparison, and update) run in O(1) constant time.
5. Total inner loop iterations:
   Sum over i from 1 to V of [ n ] = n * V

Total Time Complexity:
T(n, V) = O(V) + O(n * V) = O(n * V)

---

## Sample Output
Enter number of coin denominations: 3
Enter the coin values: 1 2 5
Enter target amount (V): 11
Minimum coins needed: 3

---

## Conclusion
The dynamic programming approach solves the minimum coin change problem by calculating optimal solutions for every sub-amount from 1 up to V. By reusing solutions of smaller subproblems, it eliminates redundant recursive recalculations, reducing an exponential brute-force search space down to O(n * V) polynomial time complexity.
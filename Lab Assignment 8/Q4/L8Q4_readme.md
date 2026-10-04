# DAA Lab Assignment 08 - Question 4

## Problem Statement
[Longest Increasing Subsequence] Given an integer array A = [a0, a1, ..., an-1], find the length of the longest subsequence such that all elements of the subsequence are strictly increasing. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
A subsequence is strictly increasing if each element is strictly greater than its predecessor:
1. Dynamic Programming Formulation:
   - Let `dp[i]` represent the length of the longest strictly increasing subsequence that ends specifically with element `arr[i]`.
   - Base Case: Every single isolated element forms an increasing subsequence of length 1, so initialize `dp[i] = 1` for all `0 <= i < n`.
2. Recurrence Relation:
   - For every element `arr[i]` from index 1 to n - 1, compare it against all preceding elements `arr[j]` (where `0 <= j < i`):
     `dp[i] = max(dp[i], dp[j] + 1)` whenever `arr[j] < arr[i]`.
3. Optimal Answer:
   - The global LIS is the maximum value present across the entire `dp` array:
     `LIS = max(dp[0], dp[1], ..., dp[n - 1])`.

---

## Algorithm
1. Read the number of elements (n).
2. Read the elements of array `arr`.
3. Initialize an array `dp` of size n with 1.
4. Initialize `maxLength = 1`.
5. For `i` from 1 to n - 1:
   - For `j` from 0 to i - 1:
     - If `arr[j] < arr[i]` and `dp[j] + 1 > dp[i]`:
       - Update `dp[i] = dp[j] + 1`.
   - If `dp[i] > maxLength`, update `maxLength = dp[i]`.
6. Print `maxLength` as the length of the Longest Increasing Subsequence.

---

## Pseudocode
Algorithm LongestIncreasingSubsequence(arr[], n):
    Input: Array arr of n integers
    Output: Length of the longest strictly increasing subsequence

    Declare dp[n]

    For i <- 0 to n - 1 do
        dp[i] <- 1
    End For

    maxLength <- 1

    For i <- 1 to n - 1 do
        For j <- 0 to i - 1 do
            If arr[j] < arr[i] and dp[j] + 1 > dp[i] then
                dp[i] <- dp[j] + 1
            End If
        End For
        If dp[i] > maxLength then
            maxLength <- dp[i]
        End If
    End For

    Return maxLength
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the nested loop comparisons:
1. Initializing the DP array of size n takes O(n) time.
2. The outer loop runs for index i from 1 to n - 1: (n - 1) iterations.
3. For each i, the inner loop iterates j from 0 to i - 1: exactly i comparisons.
4. Total comparisons across all iterations:
   Sum over i from 1 to n - 1 of [ i ] = (n * (n - 1)) / 2 = (n^2 - n) / 2
5. Each comparison and update operation runs in O(1) constant time.

Total Time Complexity:
T(n) = O(n) + (n^2 - n) / 2 = O(n^2)

---

## Sample Output
Enter number of elements: 8
Enter 8 integers: 10 22 9 33 21 50 41 60
Length of Longest Increasing Subsequence: 5

---

## Conclusion
The dynamic programming approach resolves the Longest Increasing Subsequence problem by caching the length of optimal subsequences terminating at each index. By comparing predecessors iteratively, it reduces an exponential O(2^n) subset generation search to an efficient O(n^2) execution time.
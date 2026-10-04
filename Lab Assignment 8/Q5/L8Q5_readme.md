# DAA Lab Assignment 08 - Question 5

## Problem Statement
[Maximum Sum Increasing Subsequence] Given an array of n positive integers A = [a0, a1, ..., an-1], find the maximum possible sum of a strictly increasing subsequence. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
This problem modifies the standard Longest Increasing Subsequence (LIS) formulation by optimizing cumulative element values rather than subsequence lengths:
1. Dynamic Programming Formulation:
   - Let `msis[i]` represent the maximum sum of an increasing subsequence ending with `arr[i]`.
   - Base Case: Initialize `msis[i] = arr[i]` for all `0 <= i < n` (each single element forms an increasing subsequence whose sum is the element itself).
2. Recurrence Relation:
   - For every element `i` from 1 to n - 1:
     - Compare with all previous elements `j` from 0 to i - 1:
       `msis[i] = max(msis[i], msis[j] + arr[i])` for all `j < i` such that `arr[j] < arr[i]`.
3. Finding the Global Maximum:
   - The result is obtained by taking the maximum value in `msis` array.

---

## Algorithm
1. Read the number of elements (n).
2. Read the elements of array `arr`.
3. Initialize an array `msis` of size n such that `msis[i] = arr[i]`.
4. For `i` from 1 to n - 1:
   - For `j` from 0 to i - 1:
     - If `arr[j] < arr[i]` and `msis[i] < msis[j] + arr[i]`:
       - Update `msis[i] = msis[j] + arr[i]`.
5. Iterate through `msis` from index 0 to n - 1 to find the maximum value `max_sum`.
6. Print `max_sum`.

---

## Pseudocode
Algorithm MaxSumIS(arr[], n):
    Input: Array arr of n positive integers
    Output: Maximum sum of an increasing subsequence

    Declare msis[n]

    For i <- 0 to n - 1 do
        msis[i] <- arr[i]
    End For

    For i <- 1 to n - 1 do
        For j <- 0 to i - 1 do
            If arr[j] < arr[i] and msis[i] < msis[j] + arr[i] then
                msis[i] <- msis[j] + arr[i]
            End If
        End For
    End For

    max_sum <- 0
    For i <- 0 to n - 1 do
        If msis[i] > max_sum then
            max_sum <- msis[i]
        End If
    End For

    Return max_sum
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the nested loops:
1. Initializing array `msis` takes n assignments: O(n).
2. The outer loop runs for index i from 1 to n - 1: (n - 1) iterations.
3. The inner loop evaluates every preceding index j from 0 to i - 1: i iterations.
4. Total inner loop iterations:
   Sum over i from 1 to n - 1 of [ i ] = (n * (n - 1)) / 2 = (n^2 - n) / 2
5. The final search loop scans all n values to locate the maximum sum: O(n).

Total Time Complexity:
T(n) = O(n) + (n^2 - n) / 2 + O(n) = O(n^2)

---

## Sample Output
Enter number of elements: 7
Enter 7 positive integers: 1 101 2 3 100 4 5
Maximum sum of an increasing subsequence: 106

---

## Conclusion
The Maximum Sum Increasing Subsequence problem effectively adapts the LIS principle using dynamic programming. By memoizing maximum prefix sums instead of counts, the algorithm computes the global maximum sum in O(n^2) running time, preventing exponential sub-sequence enumeration.
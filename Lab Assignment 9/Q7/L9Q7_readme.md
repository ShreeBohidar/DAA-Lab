# DAA Lab Assignment 09 - Question 7

## Problem Statement
[Minimise Deviation in Array (Two-Way Greedy with Max-Heap)] Given an array of positive integers, you can perform two operations: multiply any odd element by 2, or divide any even element by 2. The deviation is (max(A) - min(A)). Minimise the deviation after any number of operations. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## Approach
The problem permits two types of operations: doubling odd numbers and halving even numbers. Because an odd number becomes even when multiplied by 2, it can be doubled at most once.

1. Unidirectional Transformation:
   - To eliminate the bidirectional branching of operations (both doubling and halving), we first multiply every odd element in the array by 2.
   - After this initial step, all elements reach their maximum possible achievable values, converting the problem into a purely one-directional reduction where elements can only be divided by 2 while they are even.
2. Tracking Extremes:
   - We track the global minimum element across the array, initializing it during input preprocessing.
3. Greedy Shrinking Loop:
   - At each step, the deviation is computed as `current_max - current_min`, and the overall minimum deviation is updated.
   - To reduce the deviation, the upper bound must be decreased. We extract the current maximum element:
     - If the maximum element is even, we divide it by 2. The resulting value might be smaller than the current minimum, so `current_min` is updated accordingly.
     - If the maximum element is odd, it cannot be divided any further, nor can any element be increased without expanding the range. The process terminates immediately.
4. Input Representation:
   - An integer array stores the numbers, and linear scans dynamically track the maximum element and minimum element at each reduction step without dynamic heap allocations.

---

## Algorithm
1. Read the number of elements n.
2. Read all n positive integers into array a[].
3. For each element i from 0 to n - 1:
   - If a[i] is odd, set `a[i] = a[i] * 2`.
   - Update `current_min = min(current_min, a[i])`.
4. Initialize `min_deviation` to a large value.
5. In an iterative loop:
   - Scan array a[] to find the index `max_idx` of the maximum element `current_max`.
   - Compute `current_dev = current_max - current_min`.
   - Update `min_deviation = min(min_deviation, current_dev)`.
   - If `current_max` is odd:
     - Terminate the loop.
   - Else:
     - Divide `a[max_idx]` by 2: `a[max_idx] = a[max_idx] / 2`.
     - Update `current_min = min(current_min, a[max_idx])`.
6. Output the minimized deviation.

---

## Pseudocode
Algorithm MinimizeDeviation(a[], n):
    Input: Array a[] of n positive integers
    Output: Minimum deviation possible

    current_min <- infinity
    For i <- 0 to n - 1 do
        If a[i] mod 2 != 0 then
            a[i] <- a[i] * 2
        End If
        current_min <- min(current_min, a[i])
    End For

    min_deviation <- infinity

    While true do
        max_idx <- 0
        For i <- 1 to n - 1 do
            If a[i] > a[max_idx] then
                max_idx <- i
            End If
        End For

        current_max <- a[max_idx]
        min_deviation <- min(min_deviation, current_max - current_min)

        If current_max mod 2 != 0 then
            Break
        End If

        a[max_idx] <- a[max_idx] / 2
        current_min <- min(current_min, a[max_idx])
    End While

    Print "Minimum deviation possible: ", min_deviation
    Return min_deviation
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by the preprocessing pass and the iterative reduction of elements:
1. Preprocessing:
   - Scanning through n integers to double odd numbers and determine the initial minimum takes O(n) time.
2. Maximum Reduction Steps:
   - Each integer x can be divided by 2 at most O(log(max_val)) times before becoming odd.
   - Across all n elements, the while loop executes at most O(n * log(max_val)) times.
   - In each iteration, a linear scan of size n identifies the maximum element, requiring O(n) operations.
   - Total time spent across reductions: O(n^2 * log(max_val)).
   - (Note: If implemented with a binary max-heap, extraction and insertion take O(log n), reducing the loop to O(n * log(max_val) * log n)).

Total Time Complexity:
T(n) = O(n) + O(n^2 * log(max_val)) = O(n^2 * log(max_val)).

---

## Sample Output
Enter number of elements in the array (n): 4
Enter 4 positive integers:
4 1 5 20

--- Step-by-Step Reduction ---
Step 1: Current Max = 20, Current Min = 2 -> Deviation = 18 (Best: 18)
Step 2: Current Max = 10, Current Min = 2 -> Deviation = 8 (Best: 8)
Step 3: Current Max = 10, Current Min = 2 -> Deviation = 8 (Best: 8)
Step 4: Current Max = 5, Current Min = 2 -> Deviation = 3 (Best: 3)
Maximum element 5 is odd. Cannot reduce further.

Minimum deviation possible: 3

---

## Conclusion
By pre-doubling all odd numbers to their ceiling values, the two-way degree of freedom is consolidated into a single direction where numbers are systematically halved. Greedily reducing the current maximum element while adjusting the global minimum guarantees that the search space is exhaustively explored until an odd maximum is reached, returning the minimum deviation in polynomial time.
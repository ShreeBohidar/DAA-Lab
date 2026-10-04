# DAA Lab Assignment 08 - Question 9

## Problem Statement
[Collatz Conjecture] The Collatz Conjecture defines a recurrence relation for any strictly positive integer n:
T(n) = n / 2 if n is even, and 3n + 1 if n is odd.
The sequence repeatedly applies this function until n = 1. Write a modular C program to analyse the trajectory of a user-provided starting value n >= 1 and across an interval [a, b].

---

## Approach
The algorithm simulates the dynamical trajectory of positive integers under the Collatz map until the cycle reaches 1:
1. Functional Decomposition:
   - `computeTrajectory(n, print_path)`: Simulates the trajectory of an individual integer n, computes the total stopping time (number of steps to reach 1), records the peak integer value encountered, and conditionally prints the step path.
   - `analyzeInterval(a, b)`: Sweeps through all integers in range `[a, b]`, tabulates individual metrics, and determines which starting integer yields the maximum stopping time and highest intermediate peak.
2. Arithmetic Handling:
   - Unsigned 64-bit integers (`unsigned long long`) are utilized to accommodate arithmetic expansions arising from consecutive `3n + 1` odd steps.
3. Loop Termination:
   - The iterative simulation continues as long as `curr != 1`.

---

## Algorithm
1. Provide the user options to analyze either a single number or an interval `[a, b]`.
2. For single number n:
   - Set `curr = n`, `steps = 0`, `peak = n`.
   - While `curr != 1`:
     - If `curr % 2 == 0`, set `curr = curr / 2`.
     - Else, set `curr = 3 * curr + 1`.
     - If `curr > peak`, update `peak = curr`.
     - Increment `steps`.
   - Display full path, stopping time, and peak value.
3. For interval `[a, b]`:
   - Initialize trackers for maximum steps and highest peak.
   - For each integer `i` from a to b:
     - Invoke `computeTrajectory(i, 0)`.
     - Update running maximums.
   - Output summary table and extremes.

---

## Pseudocode
Algorithm CollatzTrajectory(n):
    Input: Positive integer n
    Output: Total stopping time and peak value

    curr <- n
    steps <- 0
    peak <- n

    While curr != 1 do
        If curr mod 2 = 0 then
            curr <- curr / 2
        Else
            curr <- 3 * curr + 1
        End If

        If curr > peak then
            peak <- curr
        End If
        steps <- steps + 1
    End While

    Return steps, peak
End Algorithm

Algorithm AnalyzeCollatzInterval(a, b):
    Input: Interval bounds a and b
    Output: Maximum steps and peak in range

    For i <- a to b do
        steps, peak <- CollatzTrajectory(i)
        Update interval max steps and max peak
    End For
End Algorithm

---

## Complexity Analysis
The time complexity depends on the trajectory length (stopping time) S(n) of each integer:
1. For a single number n, the while loop executes S(n) times. Each step performs parity check, division, or multiplication in O(1) machine arithmetic time.
   Time complexity for single integer: T(n) = O(S(n)).
2. For an interval [a, b], the procedure is invoked for each of the (b - a + 1) numbers.
   Total operations across the interval:
   Sum over i from a to b of [ S(i) ]

Total Time Complexity:
T(a, b) = O(Sum_{i=a}^{b} S(i))

---

## Sample Output
Collatz Conjecture Analysis
1. Single Number Trajectory
2. Interval Analysis [a, b]
Enter choice (1 or 2): 1
Enter a positive integer (n >= 1): 7

Trajectory for 7:
7 -> 22 -> 11 -> 34 -> 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

Total Stopping Time (Steps): 16
Peak Value: 52

---

## Conclusion
The modular C program simulates and analyzes the arithmetic trajectories of the Collatz Conjecture. By implementing functional decomposition and tracking intermediate maxima, it profiles the stopping times and peak expansions for individual numbers as well as across entire numerical intervals.
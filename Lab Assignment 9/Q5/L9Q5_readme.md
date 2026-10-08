# DAA Lab Assignment 09 - Question 5

## Problem Statement
[Candy Distribution Problem (Bi-directional Slope Greedy)] n children stand in a line, each assigned a rating. Each child must get at least one candy. Children with a higher rating than their immediate neighbours must get more candies than their neighbours. Find the minimum total number of candies needed. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The candy distribution problem imposes both a global lower bound (at least one candy per child) and local relative inequality constraints based on immediate neighbor ratings.

1. Constraint Decomposition:
   - Condition 1: `candies[i] >= 1` for all `0 <= i < n`.
   - Condition 2: If `ratings[i] > ratings[i - 1]`, then `candies[i] > candies[i - 1]`.
   - Condition 3: If `ratings[i] > ratings[i + 1]`, then `candies[i] > candies[i + 1]`.
2. Bi-directional Slope Greedy Strategy:
   - Instead of checking both neighbors simultaneously (which creates cyclic dependencies across peaks and valleys), we decompose the problem into two monotonic directional passes:
   - Base Initialization: Assign 1 candy to every child to satisfy Condition 1.
   - Left-to-Right Pass: Traverses from left to right. Whenever a child has a higher rating than their left neighbor (`ratings[i] > ratings[i - 1]`), greedily assign `candies[i] = candies[i - 1] + 1`. This guarantees Condition 2.
   - Right-to-Left Pass: Traverses from right to left. Whenever a child has a higher rating than their right neighbor (`ratings[i] > ratings[i + 1]`), update `candies[i] = max(candies[i], candies[i + 1] + 1)`. The use of the maximum operator ensures that Condition 3 is satisfied without violating the conditions already established during the first pass.
3. Optimality:
   - Each adjustment assigns the exact minimum integer increment necessary along rising and falling slopes, yielding the absolute minimum overall candy count.

---

## Algorithm
1. Read the number of children n.
2. Read the ratings of all n children into an array `ratings[]`.
3. Initialize an array `candies[]` of size n with every element set to 1.
4. Left-to-Right Pass:
   - Iterate index i from 1 to n - 1:
     - If `ratings[i] > ratings[i - 1]`, set `candies[i] = candies[i - 1] + 1`.
5. Right-to-Left Pass:
   - Iterate index i from n - 2 down to 0:
     - If `ratings[i] > ratings[i + 1]`:
       - If `candies[i] <= candies[i + 1]`, set `candies[i] = candies[i + 1] + 1`.
6. Compute total candies:
   - Initialize `total_candies = 0`.
   - Iterate i from 0 to n - 1, adding `candies[i]` to `total_candies`.
7. Output each child's candy count and print `total_candies`.

---

## Pseudocode
Algorithm CandyDistribution(ratings[], n):
    Input: Array ratings[] of children's ratings, total count n
    Output: Minimum total candies needed

    Declare candies[n]
    For i <- 0 to n - 1 do
        candies[i] <- 1
    End For

    For i <- 1 to n - 1 do
        If ratings[i] > ratings[i - 1] then
            candies[i] <- candies[i - 1] + 1
        End If
    End For

    For i <- n - 2 down to 0 do
        If ratings[i] > ratings[i + 1] then
            candies[i] <- max(candies[i], candies[i + 1] + 1)
        End If
    End For

    total_candies <- 0
    For i <- 0 to n - 1 do
        total_candies <- total_candies + candies[i]
    End For

    Print "Minimum total candies needed: ", total_candies
    Return total_candies
End Algorithm

---

## Complexity Analysis
The algorithm executes purely through sequential linear scans across the array:
1. Initialization:
   - Setting base values of 1 for all n children takes O(n) operations.
2. Left-to-Right Pass:
   - The loop runs for (n - 1) iterations. Each iteration performs one comparison and at most one assignment in O(1) time, taking O(n) time.
3. Right-to-Left Pass:
   - The loop runs for (n - 1) iterations from right to left. Each step performs comparison and maximum selection in O(1) time, taking O(n) time.
4. Total Summation and Output:
   - Summing all candy values performs n additions, taking O(n) time.

Total Time Complexity:
T(n) = O(n) + O(n) + O(n) + O(n) = O(n).

---

## Sample Output
Enter number of children (n): 5
Enter ratings of 5 children:
1 0 2 5 3

--- Candy Allocation per Child ---
Child 1 (Rating 1): 2 candies
Child 2 (Rating 0): 1 candies
Child 3 (Rating 2): 2 candies
Child 4 (Rating 5): 3 candies
Child 5 (Rating 3): 1 candies

Minimum total candies needed: 9

---

## Conclusion
The bi-directional slope greedy strategy decouples two-sided neighborhood constraints into two separate linear sweeps. By handling strictly increasing slopes in the forward pass and strictly decreasing slopes in the reverse pass while preserving the local maximum, the algorithm guarantees the global minimum candy allocation in optimal O(n) linear time.
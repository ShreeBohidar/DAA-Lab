# DAA Lab Assignment 09 - Question 4

## Problem Statement
[Minimum Cost to Connect Sticks] You have sticks of lengths L1, L2, ..., Ln. Connecting two sticks of lengths x and y costs x + y, resulting in a single stick of length x + y. Find the minimum total cost to connect all sticks into one. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The problem is mathematically equivalent to the optimal merge pattern problem and Huffman tree construction, where earlier merged stick lengths contribute repeatedly to the subsequent merge costs.

1. Cost Contribution:
   - When sticks are repeatedly merged, a stick connected earlier is included in all downstream merges, multiplying its length's contribution by its depth in the merge hierarchy.
   - To minimize the total cumulative cost, sticks with larger initial lengths must be merged as few times as possible (kept near the root/top), while sticks with smaller initial lengths should absorb the repeated additions.
2. Greedy Choice Property:
   - At each step, selecting and combining the two sticks with the minimum lengths produces the smallest immediate cost and keeps future additive terms as low as possible.
   - Replacing the two selected sticks with their sum reduces the problem size by one, demonstrating optimal substructure.
3. Array Representation:
   - We maintain stick lengths in a flat integer array.
   - At each iteration, the two smallest values are identified through a linear scan.
   - One element is replaced with the newly formed stick length (`x + y`), and the other is replaced with the last active element of the array while decreasing the effective size by 1.
   - This repeats until only one connected stick remains.

---

## Algorithm
1. Read the number of sticks n.
2. If n equals 1, return total cost 0 since no connections are required.
3. Read the initial lengths of all n sticks into an array `sticks[]`.
4. Initialize `total_cost = 0` and `current_size = n`.
5. Repeat for step 1 to n - 1:
   - Scan the array from index 0 to `current_size - 1` to find the indices of the two smallest elements, `min1` and `min2`.
   - Compute merge cost: `cost = sticks[min1] + sticks[min2]`.
   - Accumulate cost: `total_cost = total_cost + cost`.
   - Update the array:
     - Set `sticks[min1] = cost`.
     - Set `sticks[min2] = sticks[current_size - 1]`.
     - Decrement `current_size` by 1.
6. Print the accumulated minimum total cost.

---

## Pseudocode
Algorithm MinCostConnectSticks(sticks[], n):
    Input: Array sticks[] of lengths, number of sticks n
    Output: Minimum total cost to connect all sticks

    If n <= 1 then
        Return 0
    End If

    total_cost <- 0
    current_size <- n

    For step <- 1 to n - 1 do
        min1 <- -1
        min2 <- -1

        For i <- 0 to current_size - 1 do
            If min1 == -1 or sticks[i] < sticks[min1] then
                min2 <- min1
                min1 <- i
            Else If min2 == -1 or sticks[i] < sticks[min2] then
                min2 <- i
            End If
        End For

        cost <- sticks[min1] + sticks[min2]
        total_cost <- total_cost + cost

        sticks[min1] <- cost
        sticks[min2] <- sticks[current_size - 1]
        current_size <- current_size - 1
    End For

    Print "Minimum total cost: ", total_cost
    Return total_cost
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by repeated minimum selection across the merging phases:
1. Base check and input array population take O(n) time.
2. Iterative Merging:
   - The loop executes exactly (n - 1) iterations to merge n sticks into 1.
   - In iteration k (where array size decreases from n down to 2), finding the two smallest elements takes linear time proportional to the remaining elements: (n - k + 1) operations.
   - Total comparisons across all merge steps:
     Sum over k from 1 to n - 1 of (n - k + 1)
     = n + (n - 1) + ... + 2
     = [n(n + 1) / 2] - 1 = Θ(n^2).
3. In-place array updates and scalar additions execute in O(1) time per iteration.

Total Time Complexity:
T(n) = O(n) + Θ(n^2) = Θ(n^2) (or O(n log n) if implemented using a min-heap / priority queue).

---

## Sample Output
Enter number of sticks (n): 4
Enter the lengths of 4 sticks:
2 4 3 6

--- Step-by-Step Merging ---
Step 1: Connect sticks of lengths 2 and 3 -> Cost = 5, Total Cost = 5
Step 2: Connect sticks of lengths 4 and 5 -> Cost = 9, Total Cost = 14
Step 3: Connect sticks of lengths 6 and 9 -> Cost = 15, Total Cost = 29

All sticks connected into one!
Minimum total cost: 29

---

## Conclusion
The minimum cost stick connection problem is optimally solved by an optimal merge pattern greedy strategy. By continuously pairing the two smallest current stick lengths, smaller segments absorb the penalty of repeated summation while larger segments remain closer to the final merge, minimizing total cost in Θ(n^2) time.
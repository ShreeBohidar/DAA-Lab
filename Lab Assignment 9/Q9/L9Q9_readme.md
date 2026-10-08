# DAA Lab Assignment 09 - Question 9

## Problem Statement
[Hu-Tucker Greedy Simulation] Given an ordered sequence of weights w1, w2, ..., wn, construct an optimal alphabetic binary search tree or merge pattern that maintains the strict in-order sequence of indices while minimizing the sum of wi * depth(i). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
Constructing an optimal alphabetic binary tree requires preserving the strict left-to-right linear ordering of elements while minimizing the weighted external path length. Standard Huffman trees minimize path length but disregard order, whereas Dynamic Programming solutions take cubic or quadratic time. The Hu-Tucker algorithm accomplishes this via a three-phase greedy approach:

1. Compatibility Criterion:
   - In standard Huffman coding, any two nodes can be merged. In an alphabetic tree, two nodes u and v (where u appears before v) can only be combined if they are compatible.
   - Two nodes are defined to be compatible if they are immediately adjacent in the sequence, or if every node lying between them in the working sequence is already a compound (internal) node.
2. Phase 1 (Combination):
   - Among all currently compatible pairs (u, v), greedily choose the pair that minimizes the sum of weights (wu + wv).
   - In case of ties, choose the leftmost pair.
   - Replace the first node u with a new compound node of weight (wu + wv), link both children to this parent in an array-based representation, and delete node v by shifting the sequence left.
   - Repeat this combination step exactly n - 1 times until a single compound root remains.
3. Phase 2 (Level Assignment):
   - By traversing upward from each original leaf node i (0 <= i < n) along parent indices to the root, compute the exact level/depth of each leaf in the merged structure.
4. Phase 3 (Cost Evaluation):
   - The total weighted path cost for the optimal alphabetic tree is directly evaluated as the sum of orig_weights[i] * depth[i].

---

## Algorithm
1. Read the number of leaf weights n.
2. Read the sequence of n ordered weights into an array `orig_weights[]`.
3. If n == 1, print total cost 0 and exit.
4. Initialize the array-based tree tracking arrays:
   - For all nodes i from 0 to 2n - 1, set `parent[i] = -1`, `left[i] = -1`, and `right[i] = -1`.
5. Set up the working sequence arrays:
   - `node_idx[]` stores active tree indices (initialized to 0 to n - 1).
   - `weight[]` stores current weights (initialized to `orig_weights[]`).
   - `is_compound[]` flags internal nodes (initialized to 0 for all leaves).
   - `cur_len = n` and `next_node = n`.
6. Phase 1: Combination Loop (repeat step from 1 to n - 1):
   - Initialize `min_sum = infinity`, `best_i = -1`, `best_j = -1`.
   - For every pair (i, j) where 0 <= i < j < cur_len:
     - Check if nodes i and j are compatible (i.e., every intermediate node k between i and j has `is_compound[k] == 1`).
     - If compatible and `weight[i] + weight[j] < min_sum`:
       - Update `min_sum = weight[i] + weight[j]`, `best_i = i`, `best_j = j`.
   - Let `u = node_idx[best_i]`, `v = node_idx[best_j]`, and `parent_node = next_node++`.
   - Link parent and child nodes: `parent[u] = parent_node`, `parent[v] = parent_node`, `left[parent_node] = u`, `right[parent_node] = v`.
   - Update `node_idx[best_i] = parent_node`, `weight[best_i] = min_sum`, and `is_compound[best_i] = 1`.
   - Delete node `best_j` from the active working arrays by shifting elements left from `best_j + 1` to `cur_len - 1`.
   - Decrement `cur_len` by 1.
7. Phase 2: Depth Determination:
   - For each original leaf node i from 0 to n - 1:
     - Count hops from i up to the root using `parent[]` to determine `depth[i]`.
8. Phase 3: Total Cost Computation:
   - Compute `total_weighted_cost` as the sum of `orig_weights[i] * depth[i]`.
   - Print the depth of each leaf and the total weighted path cost.

---

## Pseudocode
Algorithm HuTuckerSimulation(orig_weights[], n):
    Input: Array orig_weights[] of n positive numbers
    Output: Minimum weighted path length preserving order

    If n <= 1 then
        Return 0
    End If

    Initialize parent[0..2n-1], left[0..2n-1], right[0..2n-1] to -1
    cur_len <- n
    next_node <- n

    For i <- 0 to n - 1 do
        node_idx[i] <- i
        weight[i] <- orig_weights[i]
        is_compound[i] <- 0
    End For

    For step <- 1 to n - 1 do
        min_sum <- infinity
        best_i <- -1
        best_j <- -1

        For i <- 0 to cur_len - 2 do
            For j <- i + 1 to cur_len - 1 do
                compatible <- true
                For k <- i + 1 to j - 1 do
                    If is_compound[k] == 0 then
                        compatible <- false
                        Break
                    End If
                End For

                If compatible == true and weight[i] + weight[j] < min_sum then
                    min_sum <- weight[i] + weight[j]
                    best_i <- i
                    best_j <- j
                End If
            End For
        End For

        u <- node_idx[best_i]
        v <- node_idx[best_j]
        parent_node <- next_node
        next_node <- next_node + 1

        parent[u] <- parent_node
        parent[v] <- parent_node
        left[parent_node] <- u
        right[parent_node] <- v

        node_idx[best_i] <- parent_node
        weight[best_i] <- min_sum
        is_compound[best_i] <- 1

        For k <- best_j to cur_len - 2 do
            node_idx[k] <- node_idx[k + 1]
            weight[k] <- weight[k + 1]
            is_compound[k] <- is_compound[k + 1]
        End For
        cur_len <- cur_len - 1
    End For

    total_cost <- 0
    For i <- 0 to n - 1 do
        d <- 0
        curr <- i
        While parent[curr] != -1 do
            d <- d + 1
            curr <- parent[curr]
        End While
        depth[i] <- d
        total_cost <- total_cost + orig_weights[i] * depth[i]
    End For

    Print "Total Weighted Cost: ", total_cost
    Return total_cost
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by the compatible pair evaluations, list shift operations, and depth extraction:
1. Combination Phase:
   - There are exactly (n - 1) combination steps.
   - In each step with m active elements (where m ranges from n down to 2):
     - Testing all pairs (i, j) involves O(m^2) candidate pairs.
     - For each pair, checking whether intervening elements are compound takes O(m) steps.
     - Finding the best pair takes O(m^3) operations.
     - Shifting the array elements after removing best_j takes O(m) time.
   - Summing across all steps:
     Sum over m from 2 to n of O(m^3) = O(n^4) in this basic array simulation.
     *(Note: Using priority queues and doubly linked lists reduces the combination phase of Hu-Tucker to O(n log n)).*
2. Level Assignment Phase:
   - For each of the n leaves, following parent links takes at most O(n) steps.
   - Total time for depth assignment: O(n^2).
3. Cost Summation:
   - Calculating the scalar sum over n elements takes O(n) time.

Total Time Complexity:
T(n) = O(n^4) + O(n^2) + O(n) = O(n^4) for this direct array-based simulation (or O(n log n) with advanced data structures).

---

## Sample Output
Enter number of leaf weights (n): 4
Enter 4 ordered weights:
10 3 4 20

--- Hu-Tucker Phase 1: Combination Steps ---
Step 1: Merged node 2 (wt: 3) and node 3 (wt: 4) -> New wt: 7
Step 2: Merged node 1 (wt: 10) and node 5 (wt: 7) -> New wt: 17
Step 3: Merged node 6 (wt: 17) and node 4 (wt: 20) -> New wt: 37

--- Leaf Depths & Cost Contribution ---
Leaf 1 (Weight: 10) -> Depth: 2 | Cost: 20
Leaf 2 (Weight: 3) -> Depth: 3 | Cost: 9
Leaf 3 (Weight: 4) -> Depth: 3 | Cost: 12
Leaf 4 (Weight: 20) -> Depth: 1 | Cost: 20

Optimal Alphabetic Tree Total Weighted Cost: 61

---

## Conclusion
The Hu-Tucker algorithm extends the greedy merge paradigm of Huffman coding to preserve strict linear ordering. By enforcing compatibility between adjacent nodes and through intermediate compound nodes, it forms an optimal alphabetic tree hierarchy, enabling calculation of minimal weighted search costs without exhaustive Dynamic Programming search.
# DAA Lab Assignment 08 - Question 8

## Problem Statement
[Optimal Binary Search Trees (OBST)] Given a set of n distinct sorted keys K = <k1, k2, ..., kn> with search probabilities p1, p2, ..., pn, and n+1 dummy keys d0, d1, ..., dn representing searches not in K with probabilities q0, q1, ..., qn, find the minimum expected search cost of a binary search tree. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## Approach
An optimal binary search tree minimizes the expected comparison cost of successful and unsuccessful lookups:
1. Dynamic Programming Formulation:
   - Let `e[i][j]` be the expected search cost of an optimal BST containing keys `ki..kj`.
   - Let `w[i][j]` be the cumulative probability sum:
     `w[i][j] = sum of p_k (for k=i..j) + sum of q_k (for k=i-1..j)`.
   - When a subtree becomes a child of another node, the depth of every element increases by 1, adding its weight `w[i][j]` to the total cost.
2. Base Cases:
   - Empty trees contain only dummy keys:
     `e[i][i - 1] = q[i - 1]` and `w[i][i - 1] = q[i - 1]` for all `1 <= i <= n + 1`.
3. Recurrence Relation:
   - For subtrees of length `l` from 1 to n:
     `e[i][j] = min { e[i][r - 1] + e[r + 1][j] + w[i][j] }` across all candidate roots `r` where `i <= r <= j`.
   - Maintain `root[i][j] = r` to record the root choice giving the minimal cost.

---

## Algorithm
1. Read the number of keys (n).
2. Read successful search probabilities `p[1..n]`.
3. Read dummy key probabilities `q[0..n]`.
4. Initialize tables `e`, `w`, and `root`.
5. Set base cases for `i` from 1 to n + 1:
   - `e[i][i - 1] = q[i - 1]`.
   - `w[i][i - 1] = q[i - 1]`.
6. Iterate over subtree lengths `l` from 1 to n:
   - Iterate over start index `i` from 1 to n - l + 1:
     - Compute end index `j = i + l - 1`.
     - Initialize `e[i][j] = infinity`.
     - Calculate `w[i][j] = w[i][j - 1] + p[j] + q[j]`.
     - Iterate candidate root `r` from i to j:
       - Compute `t = e[i][r - 1] + e[r + 1][j] + w[i][j]`.
       - If `t < e[i][j]`:
         - Update `e[i][j] = t` and `root[i][j] = r`.
7. Output `e[1][n]` as the minimum expected cost and `root[1][n]` as the root of the optimal tree.

---

## Pseudocode
Algorithm OptimalBST(p[], q[], n):
    Input: Probabilities p[1..n], q[0..n], total keys n
    Output: Minimum expected search cost and optimal tree root

    Declare e[n + 2][n + 2], w[n + 2][n + 2], root[n + 1][n + 1]

    For i <- 1 to n + 1 do
        e[i][i - 1] <- q[i - 1]
        w[i][i - 1] <- q[i - 1]
    End For

    For l <- 1 to n do
        For i <- 1 to n - l + 1 do
            j <- i + l - 1
            e[i][j] <- infinity
            w[i][j] <- w[i][j - 1] + p[j] + q[j]
            For r <- i to j do
                t <- e[i][r - 1] + e[r + 1][j] + w[i][j]
                If t < e[i][j] then
                    e[i][j] <- t
                    root[i][j] <- r
                End If
            End For
        End For
    End For

    Print "Minimum Expected Search Cost: ", e[1][n]
    Print "Optimal Root: Key ", root[1][n]
End Algorithm

---

## Complexity Analysis
The time complexity is governed by the three nested loops:
1. Base cases initialization loop runs n + 1 times: O(n).
2. The outer loop runs for chain length l from 1 to n: n iterations.
3. The middle loop runs for starting index i from 1 to n - l + 1: (n - l + 1) iterations.
4. The inner loop evaluates every candidate root r from i to j: exactly (j - i + 1) = l iterations.
5. Total inner loop iterations:
   Sum over l from 1 to n of [ (n - l + 1) * l ] = (n^3 + 3n^2 + 2n) / 6

Total Time Complexity:
T(n) = O(n) + O(n^3) = O(n^3)

---

## Sample Output
Enter number of keys (n): 5
Enter 5 probabilities for successful searches (p1 to p5):
0.15 0.10 0.05 0.10 0.20
Enter 6 probabilities for dummy keys / unsuccessful searches (q0 to q5):
0.05 0.10 0.05 0.05 0.05 0.10

--- Results ---
Minimum Expected Search Cost: 2.7500
Optimal Root: Key 2

---

## Conclusion
The optimal binary search tree problem minimizes lookup time across non-uniform key access distributions. By solving subtrees in order of increasing length and storing probability weights incrementally, the dynamic programming technique evaluates all candidate root configurations in O(n^3) time complexity.
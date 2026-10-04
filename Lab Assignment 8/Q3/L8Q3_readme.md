# DAA Lab Assignment 08 - Question 3

## Problem Statement
[Longest Common Subsequence (LCS)] Given two sequences X = <x1, x2, ..., xm> and Y = <y1, y2, ..., yn>, compute the length of their longest common subsequence and reconstruct the actual subsequence string. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
A common subsequence consists of characters appearing in the same relative order in both sequences, not necessarily contiguously:
1. Dynamic Programming Formulation:
   - Let `dp[i][j]` denote the length of the LCS of prefixes `X[0..i-1]` and `Y[0..j-1]`.
   - Base Case: `dp[i][0] = 0` and `dp[0][j] = 0` for all 0 <= i <= m and 0 <= j <= n.
2. Recurrence Relation:
   - If `X[i - 1] == Y[j - 1]`:
     `dp[i][j] = 1 + dp[i - 1][j - 1]`
   - If `X[i - 1] != Y[j - 1]`:
     `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`
3. Reconstruction:
   - Backtrack from `(m, n)` to `(0, 0)`.
   - If `X[i - 1] == Y[j - 1]`, add character `X[i - 1]` to the result string and move diagonally to `(i - 1, j - 1)`.
   - Otherwise, step towards the adjacent cell having the larger DP value.

---

## Algorithm
1. Read input strings X and Y; calculate lengths m and n.
2. Declare 2D array `dp[m + 1][n + 1]`.
3. For `i` from 0 to m:
   - For `j` from 0 to n:
     - If `i == 0` or `j == 0`, set `dp[i][j] = 0`.
     - Else if `X[i - 1] == Y[j - 1]`, set `dp[i][j] = 1 + dp[i - 1][j - 1]`.
     - Else, set `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`.
4. Store `lcsLength = dp[m][n]`.
5. Backtrack from `i = m`, `j = n` downward to reconstruct the sequence:
   - If `X[i - 1] == Y[j - 1]`, store character in `lcs` string and decrement both `i` and `j`.
   - Else if `dp[i - 1][j] > dp[i][j - 1]`, decrement `i`.
   - Else, decrement `j`.
6. Print `lcsLength` and the reconstructed LCS string.

---

## Pseudocode
Algorithm FindLCS(X, Y, m, n):
    Input: Strings X of length m, Y of length n
    Output: Length of LCS and reconstructed string

    Declare dp[m + 1][n + 1]

    For i <- 0 to m do
        For j <- 0 to n do
            If i = 0 or j = 0 then
                dp[i][j] <- 0
            Else If X[i - 1] = Y[j - 1] then
                dp[i][j] <- 1 + dp[i - 1][j - 1]
            Else
                dp[i][j] <- max(dp[i - 1][j], dp[i][j - 1])
            End If
        End For
    End For

    Print "Length: ", dp[m][n]

    i <- m, j <- n, index <- dp[m][n] - 1
    Declare lcs[dp[m][n] + 1]

    While i > 0 and j > 0 do
        If X[i - 1] = Y[j - 1] then
            lcs[index] <- X[i - 1]
            i <- i - 1
            j <- j - 1
            index <- index - 1
        Else If dp[i - 1][j] > dp[i][j - 1] then
            i <- i - 1
        Else
            j <- j - 1
        End If
    End While

    Print "LCS: ", lcs
End Algorithm

---

## Complexity Analysis
The time complexity is split into DP table filling and path traceback:
1. Outer loop runs (m + 1) times.
2. Inner loop runs (n + 1) times.
3. Table cell calculation takes O(1) comparison and addition.
4. Total steps for table construction: (m + 1) * (n + 1) = O(m * n).
5. The traceback loop decrements either i, j, or both at each step, executing at most (m + n) iterations: O(m + n).

Total Time Complexity:
T(m, n) = O(m * n) + O(m + n) = O(m * n)

---

## Sample Output
Enter first sequence (X): AGGTAB
Enter second sequence (Y): GXTXAYB
Length of Longest Common Subsequence: 4
Longest Common Subsequence: GTAB

---

## Conclusion
The longest common subsequence problem is solved in O(m * n) polynomial time via dynamic programming. By memoizing prefix alignment values in an (m + 1) x (n + 1) grid, the algorithm determines the optimal length and recovers the exact sequence using linear-time backtracking.
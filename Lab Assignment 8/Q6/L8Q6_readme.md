# DAA Lab Assignment 08 - Question 6

## Problem Statement
[Edit Distance with Traceback Information] Given two strings A of length m and B of length n, compute the minimum number of operations (insertions, deletions, or substitutions) required to transform A into B, and print the traceback result. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
Edit Distance (Levenshtein Distance) measures sequence dissimilarity by determining the minimal unit edits to transform string A into string B:
1. Dynamic Programming Formulation:
   - Let `dp[i][j]` represent the minimum edit operations to convert prefix `A[0..i-1]` to prefix `B[0..j-1]`.
   - Base Cases:
     - `dp[i][0] = i`: Converting prefix of length i to empty string requires i deletions.
     - `dp[0][j] = j`: Converting empty string to prefix of length j requires j insertions.
2. Recurrence Relation:
   - If `A[i - 1] == B[j - 1]`:
     `dp[i][j] = dp[i - 1][j - 1]` (no additional cost).
   - If characters differ:
     `dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])`
     Where:
     - `dp[i - 1][j]` represents Deletion of character from A.
     - `dp[i][j - 1]` represents Insertion of character into A.
     - `dp[i - 1][j - 1]` represents Substitution of character in A.
3. Traceback:
   - Starting from `dp[m][n]`, determine which operation produced each cell's optimal score until `(0, 0)` is reached, and display operations chronologically.

---

## Algorithm
1. Read input strings A and B; compute lengths m and n.
2. Initialize 2D array `dp[m + 1][n + 1]`.
3. Set base cases: `dp[i][0] = i` for all 0 <= i <= m; `dp[0][j] = j` for all 0 <= j <= n.
4. For `i` from 1 to m:
   - For `j` from 1 to n:
     - If `A[i - 1] == B[j - 1]`, set `dp[i][j] = dp[i - 1][j - 1]`.
     - Else, set `dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])`.
5. Output `dp[m][n]` as the minimum edit distance.
6. Traceback backwards from `i = m`, `j = n` to `(0, 0)`:
   - Match: if characters equal, record "Keep", decrement both i and j.
   - Substitution: if `dp[i][j] == dp[i - 1][j - 1] + 1`, record "Substitute", decrement both i and j.
   - Deletion: if `dp[i][j] == dp[i - 1][j] + 1`, record "Delete", decrement i.
   - Insertion: if `dp[i][j] == dp[i][j - 1] + 1`, record "Insert", decrement j.
7. Print recorded traceback steps in reverse (forward chronological order).

---

## Pseudocode
Algorithm EditDistance(A, B, m, n):
    Input: Strings A of length m, B of length n
    Output: Minimum edit distance and step-by-step transformation

    Declare dp[m + 1][n + 1]

    For i <- 0 to m do
        dp[i][0] <- i
    End For
    For j <- 0 to n do
        dp[0][j] <- j
    End For

    For i <- 1 to m do
        For j <- 1 to n do
            If A[i - 1] = B[j - 1] then
                dp[i][j] <- dp[i - 1][j - 1]
            Else
                dp[i][j] <- 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
            End If
        End For
    End For

    Print "Minimum Edit Distance: ", dp[m][n]

    Traceback from (m, n) down to (0, 0) and print operations.
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the grid construction and the traceback traversal:
1. Base cases initialization takes (m + 1) + (n + 1) operations: O(m + n).
2. The nested loops iterate over all prefixes: m * n iterations.
3. In each cell, minimum computation among three values takes O(1) constant time.
4. Total steps for table population: m * n operations.
5. Traceback path from (m, n) to (0, 0) visits at most (m + n) cells: O(m + n).

Total Time Complexity:
T(m, n) = O(m + n) + O(m * n) + O(m + n) = O(m * n)

---

## Sample Output
Enter source string A: kitten
Enter target string B: sitting
Minimum Edit Distance: 3

Traceback of Operations (from start to end):
- Substitute 'k' with 's'
- Keep 'i'
- Keep 't'
- Keep 't'
- Substitute 'e' with 'i'
- Keep 'n'
- Insert 'g'

---

## Conclusion
The dynamic programming formulation systematically resolves string conversion by modeling insertion, deletion, and substitution costs across prefix combinations. It avoids recalculating overlapping subproblems in O(m * n) time and reconstructs the precise transformation sequence via traceback.
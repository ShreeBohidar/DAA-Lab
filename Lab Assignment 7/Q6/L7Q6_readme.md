# DAA Lab Assignment 07 - Question 7

## Problem Statement
[Matrix Chain Multiplication (MCM) problem] Consider the matrix chain multiplication problem. Write a program in C to implement the dynamic programming solution of the MCM problem in order to find the minimum number of scalar multiplications involved and the corresponding ordering to obtain the final result.

---

## Approach
Matrix multiplication is associative, meaning that any parenthesization of a chain of matrices yields the same product, but the number of scalar multiplications required can vary drastically depending on the order of evaluation.

Given a chain of n matrices <A1, A2, ..., An>, where matrix Ai has dimensions p[i-1] x p[i]:
1. Dynamic Programming Formulation:
   - Let `m[i][j]` represent the minimum number of scalar multiplications needed to compute the product matrix Ai..j.
   - For a single matrix, no multiplications are required: `m[i][i] = 0`.
   - For a subchain of length L (from index i to j), we can split the product at any point k (where i <= k < j):
     `m[i][j] = min { m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j] }` across all i <= k < j.
2. Tracking the Optimal Split:
   - We maintain an auxiliary table `s[i][j]` to store the index k at which the optimal split occurs for subchain Ai..j.
3. Order of Evaluation:
   - We solve subproblems in order of increasing chain length L (from 2 up to n), ensuring that smaller subproblems `m[i][k]` and `m[k+1][j]` are computed before they are used.
4. Reconstruction:
   - A recursive helper function uses the split points in `s[i][j]` to construct and print the optimal parenthesization.

---

## Algorithm
1. Read the number of matrices (n).
2. Read the dimensions array p of size n + 1.
3. Initialize the base cases:
   - For all i from 1 to n, set `m[i][i] = 0`.
4. Iterate over chain lengths L from 2 to n:
   - Iterate over starting index i from 1 to (n - L + 1):
     - Calculate ending index j = i + L - 1.
     - Set `m[i][j]` to infinity.
     - Iterate over split point k from i to j - 1:
       - Compute cost `q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]`.
       - If `q < m[i][j]`, update `m[i][j] = q` and record `s[i][j] = k`.
5. Display the minimum scalar multiplication cost stored in `m[1][n]`.
6. Define recursive procedure `print_optimal_parens(i, j)`:
   - If i == j, print "Ai".
   - Else, print "(", recursively call for (i, s[i][j]), recursively call for (s[i][j] + 1, j), and print ")".
7. Execute `print_optimal_parens(1, n)` to print the optimal parenthesized ordering.

---

## Pseudocode
Algorithm MatrixChainOrder(p[], n):
    Input: Array p of dimensions where matrix i has size p[i-1] x p[i], total matrices n
    Output: Minimum scalar multiplications and optimal parenthesized ordering

    Declare m[n+1][n+1] and s[n+1][n+1]

    For i <- 1 to n do
        m[i][i] <- 0
    End For

    For L <- 2 to n do
        For i <- 1 to n - L + 1 do
            j <- i + L - 1
            m[i][j] <- infinity
            For k <- i to j - 1 do
                q <- m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]
                If q < m[i][j] then
                    m[i][j] <- q
                    s[i][j] <- k
                End If
            End For
        End For
    End For

    Print "Minimum number of scalar multiplications: ", m[1][n]
    Print "Optimal parenthesization ordering: "

    Procedure PrintOptimalParens(i, j):
        If i = j then
            Print "A", i
        Else
            Print "("
            PrintOptimalParens(i, s[i][j])
            PrintOptimalParens(s[i][j] + 1, j)
            Print ")"
        End If
    End Procedure

    PrintOptimalParens(1, n)
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the three nested loops used to populate the DP table:
1. Outer loop runs for chain length L from 2 to n: (n - 1) iterations.
2. Middle loop runs for starting index i from 1 to n - L + 1: (n - L + 1) iterations.
3. Inner loop tests all possible partition points k from i to j - 1: exactly (j - i) = (L - 1) iterations.
4. Total number of iterations across all loops:
   Sum over L from 2 to n of [ (n - L + 1) * (L - 1) ]
   = (n^3 - n) / 6
5. Reconstructing and printing the parenthesization via `print_optimal_parens` performs O(n) print steps.

Total Time Complexity:
T(n) = O(n^3) + O(n) = O(n^3)

---

## Sample Output
Enter number of matrices: 4
Enter dimensions array of size 5:
10 30 5 60 8

Minimum number of scalar multiplications: 4500
Optimal parenthesization ordering: ((A1(A2A3))A4)

---

## Conclusion
The dynamic programming approach computes the minimum number of scalar multiplications required to multiply a chain of matrices by systematically solving and storing solutions to overlapping subchains. By evaluating chains in increasing length order, it eliminates redundant recursive recalculations, reducing an exponential search space to O(n^3) time complexity while successfully recovering the exact parenthesization structure.
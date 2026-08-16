# DAA Lab Assignment - Question 5
# Special-Pattern Square Matrix Multiplication using Divide and Conquer

## 1. Problem Statement
Two `n x n` matrices `A` and `B` are given where `n = 2^k`[cite: 1]. Each matrix has a symmetric recursive block structure where the two diagonal blocks are identical and the two off-diagonal blocks are identical[cite: 1]:

M = [ M1  M2 ]
    [ M2  M1 ]

Each block itself recursively follows the same structure down to single elements[cite: 1]. The objective is to design a Divide and Conquer algorithm that multiplies two such structured matrices in `O(n^2)` time and validate its complexity[cite: 1].


## 2. Algorithm Overview

For two matrices `A` and `B` partitioned into sub-blocks:
A = [ A1  A2 ]        B = [ B1  B2 ]
    [ A2  A1 ]            [ B2  B1 ]

The product matrix `C = A * B` evaluates to:
C11 = A1*B1 + A2*B2 = C1
C12 = A1*B2 + A2*B1 = C2
C21 = A2*B1 + A1*B2 = C2
C22 = A2*B2 + A1*B1 = C1

Thus, `C` preserves the exact same structure:
C = [ C1  C2 ]
    [ C2  C1 ]

Instead of performing 4 recursive multiplications, we can compute `C1` and `C2` using only **2 recursive multiplications** by using algebraic identities:

1. **P** = (A1 + A2) * (B1 + B2) = A1*B1 + A1*B2 + A2*B1 + A2*B2
2. **Q** = (A1 - A2) * (B1 - B2) = A1*B1 - A1*B2 - A2*B1 + A2*B2

From `P` and `Q`:
* **C1** = (P + Q) / 2 = A1*B1 + A2*B2
* **C2** = (P - Q) / 2 = A1*B2 + A2*B1


## 3. Pseudocode

Algorithm: SPECIAL-MATRIX-MULTIPLY(A, B, n)
Input:  Square matrices A and B of size n x n with recursive block symmetry
Output: Resultant matrix C = A * B

1. if n == 1 then
2.      C[0][0] = A[0][0] * B[0][0]
3.      return C
4. end if

5. k = n / 2
6. Extract sub-blocks A1, A2 from A
7. Extract sub-blocks B1, B2 from B

8. sumA  = A1 + A2
9. sumB  = B1 + B2
10. diffA = A1 - A2
11. diffB = B1 - B2

12. P = SPECIAL-MATRIX-MULTIPLY(sumA, sumB, k)
13. Q = SPECIAL-MATRIX-MULTIPLY(diffA, diffB, k)

14. C1 = (P + Q) / 2
15. C2 = (P - Q) / 2

16. Construct matrix C:
    C[0 ... k-1][0 ... k-1]         = C1
    C[0 ... k-1][k ... n-1]         = C2
    C[k ... n-1][0 ... k-1]         = C2
    C[k ... n-1][k ... n-1]         = C1

17. return C


## 4. Recurrence Relation & Operation Count Analysis

Let `T(n)` be the running time for multiplying two `n x n` matrices of this special pattern:

T(n) = O(1)                     if n = 1
T(n) = 2 * T(n / 2) + O(n^2)    if n > 1

* **Recursive Multiplications**: `2` multiplications of size `(n / 2) x (n / 2)` (for computing `P` and `Q`).
* **Matrix Additions/Subtractions/Scalar Divisions**: Computing `sumA`, `sumB`, `diffA`, `diffB`, `C1`, and `C2` requires operations on `(n/2) x (n/2)` matrices, taking `O(n^2)` work.


## 5. Complexity Analysis

### Time Complexity
Using the Master Theorem on `T(n) = 2 * T(n / 2) + O(n^2)`:
* `a = 2, b = 2, f(n) = O(n^2)`
* `n^(log_b a) = n^(log_2 2) = n^1 = n`
* Since `f(n) = O(n^2)` and `2 > log_2(2) = 1`:
* `f(n) = Omega(n^(log_b(a) + e))` where `e = 1`
* Furthermore, regularity condition `2 * f(n/2) = 2 * (n/2)^2 = n^2 / 2 <= c * f(n)` holds for `c = 1/2 < 1`.
* By Case 3 of the Master Theorem:
* **Time Complexity = O(n^2)**



## 6. Performance Comparison

| Metric | Standard Multiplication | Strassen's Algorithm | Special-Pattern D&C |
| :--- | :--- | :--- | :--- |
| **Recursive Multiplications** | `8` | `7` | `2` |
| **Matrix Size Reduction** | `n/2` | `n/2` | `n/2` |
| **Time Complexity** | `O(n^3)` | `O(n^2.807)` | `O(n^2)` |



## 7. Compilation and Execution

### Compilation:
gcc -O2 special_matrix.c -o special_matrix.exe

### Execution:
./special_matrix.exe

### Sample Run:
Enter matrix dimension n (power of 2, e.g. 2, 4): 2

Enter Matrix A (2x2):
A[0][0]: 1
A[0][1]: 2
A[1][0]: 2
A[1][1]: 1

Enter Matrix B (2x2):
B[0][0]: 3
B[0][1]: 4
B[1][0]: 4
B[1][1]: 3


Resultant Matrix C (A x B):
11	10	
10	11	
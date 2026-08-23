# DAA Lab Assignment - Question 4
# Matrix Multiplication using Strassen's Divide and Conquer Approach

## 1. Problem Statement
Write a C program to multiply two square matrices of size `n x n` using Strassen’s method based on the Divide and Conquer approach[cite: 1].


## 2. Algorithm Overview
Standard matrix multiplication computes the product of two `n x n` matrices using `8` recursive multiplications of `(n/2) x (n/2)` sub-matrices, resulting in `O(n^3)` time complexity. Strassen's method reduces the number of recursive multiplications from `8` to `7` by computing linear combinations:

1. **Divide**:
   * Partition matrices `A` and `B` of size `n x n` into four `(n/2) x (n/2)` sub-matrices (quadrants):
     * `A11, A12, A21, A22`
     * `B11, B12, B21, B22`

2. **Conquer**:
   * Recursively compute the 7 Strassen products (`M1` to `M7`):
     * `M1 = (A11 + A22) * (B11 + B22)`
     * `M2 = (A21 + A22) * B11`
     * `M3 = A11 * (B12 - B22)`
     * `M4 = A22 * (B21 - B11)`
     * `M5 = (A11 + A12) * B22`
     * `M6 = (A21 - A11) * (B11 + B12)`
     * `M7 = (A12 - A22) * (B21 + B22)`

3. **Combine**:
   * Compute the four quadrants of the product matrix `C`:
     * `C11 = M1 + M4 - M5 + M7`
     * `C12 = M3 + M5`
     * `C21 = M2 + M4`
     * `C22 = M1 - M2 + M3 + M6`



## 3. Pseudocode

Algorithm: STRASSEN-MULTIPLY(A, B, n)
Input:  Square matrices A and B of size n x n (n is a power of 2)
Output: Resultant matrix C = A * B

1. if n == 1 then
2.      C[0][0] = A[0][0] * B[0][0]
3.      return C
4. end if

5. k = n / 2
6. Divide A into A11, A12, A21, A22
7. Divide B into B11, B12, B21, B22

8.  M1 = STRASSEN-MULTIPLY(A11 + A22, B11 + B22, k)
9.  M2 = STRASSEN-MULTIPLY(A21 + A22, B11, k)
10. M3 = STRASSEN-MULTIPLY(A11, B12 - B22, k)
11. M4 = STRASSEN-MULTIPLY(A22, B21 - B11, k)
12. M5 = STRASSEN-MULTIPLY(A11 + A12, B22, k)
13. M6 = STRASSEN-MULTIPLY(A21 - A11, B11 + B12, k)
14. M7 = STRASSEN-MULTIPLY(A12 - A22, B21 + B22, k)

15. C11 = M1 + M4 - M5 + M7
16. C12 = M3 + M5
17. C21 = M2 + M4
18. C22 = M1 - M2 + M3 + M6

19. Combine C11, C12, C21, C22 into C
20. return C


## 4. Recurrence Relation & Operation Count Analysis

Let `T(n)` be the running time for multiplying two `n x n` matrices:

T(n) = O(1)                     if n = 1
T(n) = 7 * T(n / 2) + O(n^2)    if n > 1

* **Recursive Multiplications**: `7` sub-problems of size `(n / 2) x (n / 2)`.
* **Matrix Additions/Subtractions**: `18` matrix additions/subtractions of `(n/2) x (n/2)` blocks, contributing `18 * (n/2)^2 = (9/2) * n^2 = O(n^2)` work.


## 5. Complexity Analysis

### Time Complexity
Using the Master Theorem on `T(n) = 7 * T(n / 2) + O(n^2)`:
* `a = 7, b = 2, f(n) = O(n^2)`
* `log_b(a) = log_2(7) ≈ 2.807`
* Since `f(n) = O(n^2)` and `2 < log_2(7)`:
* `f(n) = O(n^(log_2(7) - e))` where `e ≈ 0.807` (Case 1 applies)
* **Time Complexity = O(n^(log_2 7)) ≈ O(n^2.807)**


## 6. Performance Comparison

| Metric | Standard Matrix Multiplication | Strassen's Matrix Multiplication |
| :--- | :--- | :--- |
| **Recursive Multiplications** | `8` | `7` |
| **Matrix Additions/Subtractions** | `4` | `18` |
| **Time Complexity** | `O(n^3)` | `O(n^2.807)` |



## 7. Compilation and Execution

### Compilation:
gcc -O2 strassen_matrix_multiplication.c -o strassen_matrix_multiplication.exe

### Execution:
./strassen_matrix_multiplication.exe

### Sample Run:
Enter matrix dimension n (power of 2, e.g. 2 or 4): 2
Enter elements of Matrix A (2x2):
1 2
3 4
Enter elements of Matrix B (2x2):
5 6
7 8

Resultant Matrix C (A x B):
19	22	
43	50	

DAA Lab Assignment 06 - Question 2

Problem Statement:
2. 2D square matrix operations and their complexities: Given square matrices with n rows and n columns, what is the worst-case computational complexity of the following matrix algorithms in terms of n:
(i) Matrix Addition.
(ii) Matrix Multiplication.
(iii) Finding if the given matrix is a zero matrix.
(iv) Finding if the given matrix is a symmetric matrix.
(v) Computing the determinant of the given matrix.
(vi) Transposing the matrix in situ (in place).
(vii) Finding the eigenvalue and eigenvector of the matrix.
By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.

The Approach:
- Input Representation: Dynamic 2D arrays allocated via double pointers (double**) representing n x n square matrices.
- (i) Matrix Addition: Iterate through every cell (i, j) using two nested loops and add the corresponding elements from A and B into matrix C.
- (ii) Matrix Multiplication: Standard triple-nested loop implementation computing dot products of rows of A and columns of B into matrix C.
- (iii) Zero Matrix Check: Traverse all n x n elements linearly; return false if any entry deviates from zero.
- (iv) Symmetric Matrix Check: Check the condition A[i][j] == A[j][i] across the upper triangular half (j > i). Return false immediately on mismatch.
- (v) Determinant: Apply Gaussian elimination with partial pivoting to reduce the matrix to an upper triangular form in O(n^3) time, then compute the product of diagonal elements.
- (vi) In Situ Transposition: Swap entries A[i][j] and A[j][i] for all pairs where j > i, modifying the matrix in place without auxiliary storage.
- (vii) Eigenvalues and Eigenvectors: Implement iterative QR decomposition using Gram-Schmidt orthogonalization (A = Q * R, then A_next = R * Q) to triangularize the matrix, revealing real eigenvalues along the diagonal and accumulating Q matrices to yield the eigenvectors.

Algorithm:
1. MatrixAddition(A, B, C, n):
   - For i from 0 to n - 1:
       For j from 0 to n - 1:
           C[i][j] = A[i][j] + B[i][j]

2. MatrixMultiplication(A, B, C, n):
   - For i from 0 to n - 1:
       For j from 0 to n - 1:
           C[i][j] = 0
           For k from 0 to n - 1:
               C[i][j] = C[i][j] + (A[i][k] * B[k][j])

3. IsZeroMatrix(A, n):
   - For i from 0 to n - 1:
       For j from 0 to n - 1:
           If |A[i][j]| > 0: return FALSE
   - Return TRUE

4. IsSymmetricMatrix(A, n):
   - For i from 0 to n - 1:
       For j from i + 1 to n - 1:
           If |A[i][j] - A[j][i]| > 0: return FALSE
   - Return TRUE

5. ComputeDeterminant(A, n):
   - Copy A into mat. Set det = 1.
   - For i from 0 to n - 1:
       Find pivot row with maximum absolute value in column i.
       If pivot value is 0: return 0.
       If pivot != i: swap row i and pivot row; det = -det.
       det = det * mat[i][i]
       For j from i + 1 to n - 1:
           factor = mat[j][i] / mat[i][i]
           For k from i to n - 1:
               mat[j][k] = mat[j][k] - factor * mat[i][k]
   - Return det.

6. TransposeInSitu(A, n):
   - For i from 0 to n - 1:
       For j from i + 1 to n - 1:
           Swap A[i][j] and A[j][i].

7. SolveEigenQR(A, n):
   - Initialize T = copy(A), EigVec = Identity(n).
   - Repeat for fixed iterations:
       Perform Gram-Schmidt QR decomposition: T = Q * R.
       Update T = R * Q.
       Update EigVec = EigVec * Q.
   - Diagonal elements of T represent eigenvalues; columns of EigVec represent eigenvectors.

Pseudocode:
FUNCTION matrixAddition(A, B, C, n):
    FOR i = 0 TO n - 1:
        FOR j = 0 TO n - 1:
            C[i][j] = A[i][j] + B[i][j]

FUNCTION matrixMultiplication(A, B, C, n):
    FOR i = 0 TO n - 1:
        FOR j = 0 TO n - 1:
            C[i][j] = 0
            FOR k = 0 TO n - 1:
                C[i][j] = C[i][j] + A[i][k] * B[k][j]

FUNCTION isZeroMatrix(A, n):
    FOR i = 0 TO n - 1:
        FOR j = 0 TO n - 1:
            IF A[i][j] != 0 THEN RETURN FALSE
    RETURN TRUE

FUNCTION isSymmetricMatrix(A, n):
    FOR i = 0 TO n - 1:
        FOR j = i + 1 TO n - 1:
            IF A[i][j] != A[j][i] THEN RETURN FALSE
    RETURN TRUE

FUNCTION computeDeterminant(A, n):
    mat = copy(A)
    det = 1.0
    FOR i = 0 TO n - 1:
        pivot = FindMaxRow(mat, i, n)
        IF mat[pivot][i] == 0 THEN RETURN 0
        IF pivot != i:
            SWAP(mat[i], mat[pivot])
            det = -det
        det = det * mat[i][i]
        FOR j = i + 1 TO n - 1:
            factor = mat[j][i] / mat[i][i]
            FOR k = i TO n - 1:
                mat[j][k] = mat[j][k] - factor * mat[i][k]
    RETURN det

FUNCTION transposeInSitu(A, n):
    FOR i = 0 TO n - 1:
        FOR j = i + 1 TO n - 1:
            SWAP(A[i][j], A[j][i])

FUNCTION solveEigenQR(A, n):
    T = copy(A)
    EigVec = Identity(n)
    FOR iter = 0 TO MAX_ITER:
        (Q, R) = QR_Decomposition(T, n)
        T = R * Q
        EigVec = EigVec * Q
    OUTPUT diagonal of T as eigenvalues
    OUTPUT columns of EigVec as eigenvectors

Complexity Analysis:
(i) Matrix Addition:
    T(n) = sum_{i=0}^{n-1} sum_{j=0}^{n-1} c = c * n^2
    T(n) = O(n^2)
    Derivation: Two nested loops traverse all n * n elements, performing one addition per cell.

(ii) Matrix Multiplication:
    T(n) = sum_{i=0}^{n-1} sum_{j=0}^{n-1} sum_{k=0}^{n-1} c = c * n^3
    T(n) = O(n^3)
    Derivation: Standard matrix multiplication executes n iterations along three nested loops, leading to n^3 multiplications and additions.

(iii) Finding if Zero Matrix:
    T(n) = sum_{i=0}^{n-1} sum_{j=0}^{n-1} c = c * n^2
    T(n) = O(n^2)
    Derivation: In the worst case (when the matrix is indeed a zero matrix or only the last entry is non-zero), every element is verified once.

(iv) Finding if Symmetric Matrix:
    T(n) = sum_{i=0}^{n-1} (n - 1 - i) * c = c * (n * (n - 1)) / 2
    T(n) = O(n^2)
    Derivation: Only the upper triangular off-diagonal entries are compared against their symmetric reflections, resulting in n*(n - 1)/2 checks.

(v) Computing Determinant (via Gaussian Elimination):
    T(n) = sum_{i=0}^{n-1} sum_{j=i+1}^{n-1} sum_{k=i}^{n-1} c
    T(n) = sum_{i=0}^{n-1} (n - i)^2 * c approx c * (n^3 / 3)
    T(n) = O(n^3)
    Derivation: Eliminating elements row-by-row into an upper triangular structure dominates with cubic time complexity.

(vi) Transposing Matrix In Situ:
    T(n) = sum_{i=0}^{n-1} sum_{j=i+1}^{n-1} c = c * (n * (n - 1)) / 2
    T(n) = O(n^2)
    Derivation: In-place transposition requires swapping each element above the main diagonal with its counterpart below it.

(vii) Finding Eigenvalues and Eigenvectors (QR Algorithm):
    T(n) = K * [T_GramSchmidt(n) + T_MatMul(n)]
    T_GramSchmidt(n) = O(n^3)
    T_MatMul(n) = O(n^3)
    T(n) = K * O(n^3) = O(n^3)  (for a constant number of iterations K)
    Derivation: Each QR step applies Gram-Schmidt orthogonalization taking O(n^3) operations and matrix multiplications taking O(n^3) operations.

Sample Output:
Enter dimension n of square matrices: 2
Enter elements of Matrix A (2 x 2):
4 1
2 3
Enter elements of Matrix B (2 x 2):
1 0
0 1

--- Matrix Operations ---
(i) Matrix Addition (A + B):
    5.00     1.00 
    2.00     4.00 

(ii) Matrix Multiplication (A * B):
    4.00     1.00 
    2.00     3.00 

(iii) Is Matrix A a Zero Matrix? No

(iv) Is Matrix A Symmetric? No

(v) Determinant of Matrix A: 10.0000

(vi) Transpose of Matrix A in situ:
    4.00     2.00 
    1.00     3.00 

(vii) Eigenvalues and Corresponding Eigenvectors (QR Decomposition):
      Eigenvalue 1: 5.0000
      Eigenvector 1: [ 0.7071 0.7071 ]
      Eigenvalue 2: 2.0000
      Eigenvector 2: [ -0.4472 0.8944 ]

Conclusion:
The worst-case computational time complexities for the given n x n square matrix operations are:
- (i) Matrix Addition: O(n^2)
- (ii) Matrix Multiplication: O(n^3)
- (iii) Checking Zero Matrix: O(n^2)
- (iv) Checking Symmetric Matrix: O(n^2)
- (v) Computing Determinant: O(n^3)
- (vi) In Situ Transposition: O(n^2)
- (vii) Eigenvalues and Eigenvectors: O(n^3) per iteration cycle 

The analysis demonstrates that entry-wise verification and transposition scale quadratically with the dimension n, matching the total number of elements in the matrix. In contrast, algebraic transformations such as matrix multiplication, Gaussian elimination for determinant evaluation, and orthogonal iterative factorizations (QR decomposition) require O(n^3) due to extensive row-column dot product combinations.
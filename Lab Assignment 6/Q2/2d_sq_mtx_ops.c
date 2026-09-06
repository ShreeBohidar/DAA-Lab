#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matrixAddition(double **A, double **B, double **C, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrixMultiplication(double **A, double **B, double **C, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < n; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }
}

int isZeroMatrix(double **A, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (fabs(A[i][j]) > 1e-6) {
                return 0;
            }
        }
    }
    return 1;
}

int isSymmetricMatrix(double **A, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (fabs(A[i][j] - A[j][i]) > 1e-6) {
                return 0;
            }
        }
    }
    return 1;
}

void transposeInSitu(double **A, int n) {
    int i, j;
    double temp;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

double computeDeterminant(double **A, int n) {
    int i, j, k;
    double det = 1.0;
    double temp;
    
    double **mat = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        mat[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++) {
            mat[i][j] = A[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        int pivot = i;
        for (j = i + 1; j < n; j++) {
            if (fabs(mat[j][i]) > fabs(mat[pivot][i])) {
                pivot = j;
            }
        }

        if (fabs(mat[pivot][i]) < 1e-9) {
            for (k = 0; k < n; k++) free(mat[k]);
            free(mat);
            return 0.0;
        }

        if (pivot != i) {
            for (k = 0; k < n; k++) {
                temp = mat[i][k];
                mat[i][k] = mat[pivot][k];
                mat[pivot][k] = temp;
            }
            det = -det;
        }

        det = det * mat[i][i];

        for (j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i];
            for (k = i; k < n; k++) {
                mat[j][k] = mat[j][k] - (factor * mat[i][k]);
            }
        }
    }

    for (i = 0; i < n; i++) free(mat[i]);
    free(mat);
    return det;
}

void solveEigenQR(double **A, int n) {
    int i, j, k, iter;
    
    double **T = (double **)malloc(n * sizeof(double *));
    double **Q = (double **)malloc(n * sizeof(double *));
    double **R = (double **)malloc(n * sizeof(double *));
    double **EigVec = (double **)malloc(n * sizeof(double *));
    double **tempVec = (double **)malloc(n * sizeof(double *));
    
    for (i = 0; i < n; i++) {
        T[i] = (double *)malloc(n * sizeof(double));
        Q[i] = (double *)malloc(n * sizeof(double));
        R[i] = (double *)malloc(n * sizeof(double));
        EigVec[i] = (double *)malloc(n * sizeof(double));
        tempVec[i] = (double *)malloc(n * sizeof(double));
        for (j = 0; j < n; j++) {
            T[i][j] = A[i][j];
            if (i == j) EigVec[i][j] = 1.0;
            else EigVec[i][j] = 0.0;
        }
    }

    for (iter = 0; iter < 150; iter++) {
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++) {
                Q[i][j] = T[i][j];
            }
            for (k = 0; k < j; k++) {
                double dot = 0.0;
                for (i = 0; i < n; i++) {
                    dot = dot + (T[i][j] * Q[i][k]);
                }
                R[k][j] = dot;
                for (i = 0; i < n; i++) {
                    Q[i][j] = Q[i][j] - (dot * Q[i][k]);
                }
            }

            double norm = 0.0;
            for (i = 0; i < n; i++) {
                norm = norm + (Q[i][j] * Q[i][j]);
            }
            norm = sqrt(norm);
            R[j][j] = norm;

            if (norm > 1e-12) {
                for (i = 0; i < n; i++) {
                    Q[i][j] = Q[i][j] / norm;
                }
            }
            for (k = j + 1; k < n; k++) {
                R[k][j] = 0.0;
            }
        }

        matrixMultiplication(R, Q, T, n);

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                tempVec[i][j] = 0.0;
                for (k = 0; k < n; k++) {
                    tempVec[i][j] = tempVec[i][j] + (EigVec[i][k] * Q[k][j]);
                }
            }
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                EigVec[i][j] = tempVec[i][j];
            }
        }
    }

    printf("(vii) Eigenvalues and Corresponding Eigenvectors (QR Decomposition):\n");
    for (i = 0; i < n; i++) {
        printf("      Eigenvalue %d: %.4f\n", i + 1, T[i][i]);
        printf("      Eigenvector %d: [ ", i + 1);
        for (j = 0; j < n; j++) {
            printf("%.4f ", EigVec[j][i]);
        }
        printf("]\n");
    }

    for (i = 0; i < n; i++) {
        free(T[i]);
        free(Q[i]);
        free(R[i]);
        free(EigVec[i]);
        free(tempVec[i]);
    }
    free(T);
    free(Q);
    free(R);
    free(EigVec);
    free(tempVec);
}

void printMatrix(double **A, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, i, j;
    printf("Enter dimension n of square matrices: ");
    scanf("%d", &n);

    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(n * sizeof(double *));
    double **C = (double **)malloc(n * sizeof(double *));
    double **workA = (double **)malloc(n * sizeof(double *));

    for (i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        B[i] = (double *)malloc(n * sizeof(double));
        C[i] = (double *)malloc(n * sizeof(double));
        workA[i] = (double *)malloc(n * sizeof(double));
    }

    printf("Enter elements of Matrix A (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
            workA[i][j] = A[i][j];
        }
    }

    printf("Enter elements of Matrix B (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }

    printf("\n--- Matrix Operations ---\n");

    matrixAddition(A, B, C, n);
    printf("(i) Matrix Addition (A + B):\n");
    printMatrix(C, n);

    matrixMultiplication(A, B, C, n);
    printf("\n(ii) Matrix Multiplication (A * B):\n");
    printMatrix(C, n);

    printf("\n(iii) Is Matrix A a Zero Matrix? %s\n", isZeroMatrix(A, n) ? "Yes" : "No");

    printf("\n(iv) Is Matrix A Symmetric? %s\n", isSymmetricMatrix(A, n) ? "Yes" : "No");

    printf("\n(v) Determinant of Matrix A: %.4f\n", computeDeterminant(A, n));

    transposeInSitu(workA, n);
    printf("\n(vi) Transpose of Matrix A in situ:\n");
    printMatrix(workA, n);

    printf("\n");
    solveEigenQR(A, n);

    for (i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
        free(workA[i]);
    }
    free(A);
    free(B);
    free(C);
    free(workA);

    return 0;
}
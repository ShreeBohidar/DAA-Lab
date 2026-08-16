#include <stdio.h>


void add(int n, int A[16][16], int B[16][16], int res[16][16]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
}


void sub(int n, int A[16][16], int B[16][16], int res[16][16]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
}


void strassen(int n, int A[16][16], int B[16][16], int C[16][16]) {
    // Base Case: 1x1 matrix multiplication
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int a11[16][16], a12[16][16], a21[16][16], a22[16][16];
    int b11[16][16], b12[16][16], b21[16][16], b22[16][16];
    int c11[16][16], c12[16][16], c21[16][16], c22[16][16];
    int m1[16][16], m2[16][16], m3[16][16], m4[16][16], m5[16][16], m6[16][16], m7[16][16];
    int t1[16][16], t2[16][16];

    // Divide matrices A and B into 4 sub-blocks (quadrants)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(k, a11, a22, t1);
    add(k, b11, b22, t2);
    strassen(k, t1, t2, m1);

    // M2 = (A21 + A22) * B11
    add(k, a21, a22, t1);
    strassen(k, t1, b11, m2);

    // M3 = A11 * (B12 - B22)
    sub(k, b12, b22, t2);
    strassen(k, a11, t2, m3);

    // M4 = A22 * (B21 - B11)
    sub(k, b21, b11, t2);
    strassen(k, a22, t2, m4);

    // M5 = (A11 + A12) * B22
    add(k, a11, a12, t1);
    strassen(k, t1, b22, m5);

    // M6 = (A21 - A11) * (B11 + B12)
    sub(k, a21, a11, t1);
    add(k, b11, b12, t2);
    strassen(k, t1, t2, m6);

    // M7 = (A12 - A22) * (B21 + B22)
    sub(k, a12, a22, t1);
    add(k, b21, b22, t2);
    strassen(k, t1, t2, m7);

    // Combine 7 products to form C quadrants
    // C11 = M1 + M4 - M5 + M7
    add(k, m1, m4, t1);
    sub(k, t1, m5, t2);
    add(k, t2, m7, c11);

    // C12 = M3 + M5
    add(k, m3, m5, c12);

    // C21 = M2 + M4
    add(k, m2, m4, c21);

    // C22 = M1 - M2 + M3 + M6
    sub(k, m1, m2, t1);
    add(k, t1, m3, t2);
    add(k, t2, m6, c22);

    // Put quadrants back into the result matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = c11[i][j];
            C[i][j + k]     = c12[i][j];
            C[i + k][j]     = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
}

int main() {
    int n;
    int A[16][16], B[16][16], C[16][16];

    printf("Enter matrix dimension n (power of 2): ");
    if (scanf("%d", &n) != 1 || (n != 1 && n != 2 && n != 4 && n != 8 && n != 16)) {
        printf("Invalid dimension. Must be power of 2 (1, 2, 4, 8, 16).\n");
        return 1;
    }

    printf("Enter elements of Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    strassen(n, A, B, C);

    printf("\nResultant Matrix C (A x B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
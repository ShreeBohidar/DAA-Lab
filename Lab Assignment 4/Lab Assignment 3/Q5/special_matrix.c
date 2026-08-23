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

void specialMultiply(int n, int A[16][16], int B[16][16], int C[16][16]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A1[16][16], A2[16][16];
    int B1[16][16], B2[16][16];
    int sumA[16][16], sumB[16][16];
    int diffA[16][16], diffB[16][16];
    int P[16][16], Q[16][16];
    int C1[16][16], C2[16][16];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    add(k, A1, A2, sumA);
    add(k, B1, B2, sumB);
    specialMultiply(k, sumA, sumB, P);

    sub(k, A1, A2, diffA);
    sub(k, B1, B2, diffB);
    specialMultiply(k, diffA, diffB, Q);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C1[i][j];
            C[i][j + k]     = C2[i][j];
            C[i + k][j]     = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }
}

int main() {
    int n;
    int A[16][16];
    int B[16][16];
    int C[16][16];

    printf("Enter matrix dimension n (power of 2): ");
    if (scanf("%d", &n) != 1 || (n != 1 && n != 2 && n != 4 && n != 8 && n != 16)) {
        printf("Invalid dimension. Please enter a power of 2.\n");
        return 1;
    }

    printf("\nEnter Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    specialMultiply(n, A, B, C);

    printf("\nResultant Matrix C (A x B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

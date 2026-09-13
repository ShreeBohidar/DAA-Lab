#include <stdio.h>

int s[100][100];

void print_optimal_parens(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(i, s[i][j]);
        print_optimal_parens(s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    int p[100];
    int m[100][100];
    int i, j, k, L, q;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of matrices must be positive.\n");
        return 0;
    }

    printf("Enter dimensions array of size %d:\n", n + 1);
    for (i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = 1000000000;

            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications: %d\n", m[1][n]);
    printf("Optimal parenthesization ordering: ");
    print_optimal_parens(1, n);
    printf("\n");

    return 0;
}
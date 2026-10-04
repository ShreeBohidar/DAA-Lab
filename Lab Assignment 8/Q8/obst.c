#include <stdio.h>

#define MAX 100

void optimalBST(double p[], double q[], int n) {
    // e[i][j] stores optimal search cost for keys k_i to k_j
    double e[MAX + 2][MAX + 2];
    // w[i][j] stores the sum of probabilities for the subtree
    double w[MAX + 2][MAX + 2];
    // root[i][j] stores the root of optimal subtree
    int root[MAX + 1][MAX + 1];

    // Base cases: empty subtrees where j = i - 1 (only dummy key d_{i-1})
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // l is the length of the chain of keys being considered
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;

            // Initialize with a large number instead of using float.h
            e[i][j] = 999999.0;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Try every key k_r (from index i to j) as the subtree root
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\n--- Results ---\n");
    printf("Minimum Expected Search Cost: %.4lf\n", e[1][n]);
    printf("Optimal Root: Key %d\n", root[1][n]);
}

int main() {
    int n;

    printf("Enter number of keys (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    double p[MAX + 1];
    double q[MAX + 1];

    printf("Enter %d probabilities for successful searches (p1 to p%d):\n", n, n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }

    printf("Enter %d probabilities for dummy keys / unsuccessful searches (q0 to q%d):\n", n + 1, n);
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }

    optimalBST(p, q, n);

    return 0;
}

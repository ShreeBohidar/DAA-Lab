#include <stdio.h>
#include <string.h>

int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

void editDistance(char A[], char B[]) {
    int m = strlen(A);
    int n = strlen(B);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min3(dp[i - 1][j],     // Deletion
                                    dp[i][j - 1],     // Insertion
                                    dp[i - 1][j - 1]); // Substitution
            }
        }
    }

    printf("Minimum Edit Distance: %d\n", dp[m][n]);
    printf("\nTraceback of Operations (from start to end):\n");

    int i = m, j = n;
    char ops[200][100];
    int step = 0;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            sprintf(ops[step++], "Keep '%c'", A[i - 1]);
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            sprintf(ops[step++], "Substitute '%c' with '%c'", A[i - 1], B[j - 1]);
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            sprintf(ops[step++], "Delete '%c'", A[i - 1]);
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            sprintf(ops[step++], "Insert '%c'", B[j - 1]);
            j--;
        }
    }

    for (int k = step - 1; k >= 0; k--) {
        printf("- %s\n", ops[k]);
    }
}

int main() {
    char A[100], B[100];
    printf("Enter source string A: ");
    scanf("%s", A);
    printf("Enter target string B: ");
    scanf("%s", B);

    editDistance(A, B);

    return 0;
}
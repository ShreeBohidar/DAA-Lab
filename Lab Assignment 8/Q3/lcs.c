#include <stdio.h>
#include <string.h>

#define MAX 1000

// Utility function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);

    // dp[i][j] stores the length of LCS of X[0..i-1] and Y[0..j-1]
    int dp[m + 1][n + 1];

    // Build the DP table in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0; // Base case: LCS with empty string is 0
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcsLength = dp[m][n];
    printf("Length of Longest Common Subsequence: %d\n", lcsLength);

    // Reconstruct the actual LCS string by backtracking from dp[m][n]
    char lcs[lcsLength + 1];
    lcs[lcsLength] = '\0'; // Null terminator

    int i = m, j = n, index = lcsLength - 1;
    while (i > 0 && j > 0) {
        // If current characters match, it is part of LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        }
        // If not matching, move in the direction of the larger value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Longest Common Subsequence: %s\n", lcs);
}

int main() {
    char X[MAX], Y[MAX];

    printf("Enter first sequence (X): ");
    scanf("%s", X);

    printf("Enter second sequence (Y): ");
    scanf("%s", Y);

    findLCS(X, Y);

    return 0;
}

#include <stdio.h>

void cutRod(int price[], int n) {
    int dp[n + 1];
    int firstCut[n + 1];

    // Base case: revenue for length 0 is 0
    dp[0] = 0;
    firstCut[0] = 0;

    // Solve subproblems for lengths 1 to n
    for (int j = 1; j <= n; j++) {
        int maxVal = -1;
        int bestCut = 0;

        for (int i = 1; i <= j; i++) {
            int currentVal = price[i] + dp[j - i];
            if (currentVal > maxVal) {
                maxVal = currentVal;
                bestCut = i;
            }
        }

        dp[j] = maxVal;
        firstCut[j] = bestCut;
    }

    // (i) Maximum revenue
    printf("Maximum obtainable revenue: %d\n", dp[n]);

    // (ii) Reconstruction of optimal pieces
    printf("Optimal piece lengths: ");
    int temp = n;
    while (temp > 0) {
        printf("%d ", firstCut[temp]);
        temp -= firstCut[temp];
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the length of the rod (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid rod length.\n");
        return 1;
    }

    // 1-indexed price array: index i represents price of piece of length i
    int price[n + 1];
    printf("Enter the prices for lengths 1 to %d: ", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    cutRod(price, n);

    return 0;
}

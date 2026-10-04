#include <stdio.h>

/*
 * Function to find the total number of distinct combinations
 * to make amount V using given coin denominations.
 */
long long countWays(int coins[], int n, int V) {
    // dp[j] stores the number of combinations to form amount j
    long long dp[V + 1];

    // Base case: There is 1 way to make amount 0 (choose no coins)
    dp[0] = 1;

    // Initialize all other amounts to 0
    for (int j = 1; j <= V; j++) {
        dp[j] = 0;
    }

    // Outer loop picks coins one by one to avoid counting permutations
    for (int i = 0; i < n; i++) {
        int coin = coins[i];
        for (int j = coin; j <= V; j++) {
            dp[j] += dp[j - coin];
        }
    }

    return dp[V];
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for number of coins.\n");
        return 1;
    }

    int coins[n];
    printf("Enter the %d distinct coin denominations: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount (V): ");
    scanf("%d", &V);

    if (V < 0) {
        printf("Target amount cannot be negative.\n");
        return 1;
    }

    long long totalWays = countWays(coins, n, V);

    printf("Total number of ways to make amount %d: %lld\n", V, totalWays);

    return 0;
}

#include <stdio.h>

int minCoins(int coins[], int n, int V) {
    // dp[i] will store the minimum coins needed for amount i
    int dp[V + 1];

    // Base case: 0 coins needed to make amount 0
    dp[0] = 0;

    // Initialize all other amounts with a value larger than any possible solution
    // Since the maximum possible coins needed can never exceed V (using 1s), V + 1 acts as infinity.
    for (int i = 1; i <= V; i++) {
        dp[i] = V + 1;
    }

    // Fill the dp array from 1 to V
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int subResult = dp[i - coins[j]];
                if (subResult != V + 1 && subResult + 1 < dp[i]) {
                    dp[i] = subResult + 1;
                }
            }
        }
    }

    // If dp[V] was not updated, it's impossible to make amount V
    if (dp[V] > V) {
        return -1;
    }

    return dp[V];
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter the coin values: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount (V): ");
    scanf("%d", &V);

    int result = minCoins(coins, n, V);

    if (result == -1) {
        printf("Not possible to form the amount with given coins.\n");
    } else {
        printf("Minimum coins needed: %d\n", result);
    }

    return 0;
}

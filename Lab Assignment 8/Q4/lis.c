#include <stdio.h>

int longestIncreasingSubsequence(int arr[], int n) {
    if (n <= 0) return 0;

    int dp[n];

    // Initialize every index with length 1 (a single element)
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int maxLength = 1;

    // Fill the dp array
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    return maxLength;
}

int main() {
    int n;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = longestIncreasingSubsequence(arr, n);
    printf("Length of Longest Increasing Subsequence: %d\n", result);

    return 0;
}

#include <stdio.h>

int maxSumIS(int arr[], int n) {
    int msis[n];
    int i, j, max_sum = 0;

    for (i = 0; i < n; i++) {
        msis[i] = arr[i];
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && msis[i] < msis[j] + arr[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (msis[i] > max_sum) {
            max_sum = msis[i];
        }
    }

    return max_sum;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d positive integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = maxSumIS(arr, n);
    printf("Maximum sum of an increasing subsequence: %d\n", result);

    return 0;
}
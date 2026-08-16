#include <stdio.h>

int weigh_count = 0;

int weigh(int arr[], int l1, int r1, int l2, int r2) {
    weigh_count = weigh_count + 1;
    int sum_left = 0;
    int sum_right = 0;

    for (int i = l1; i <= r1; i = i + 1) {
        sum_left = sum_left + arr[i];
    }
    for (int i = l2; i <= r2; i = i + 1) {
        sum_right = sum_right + arr[i];
    }

    if (sum_left < sum_right) {
        return -1;
    } else if (sum_right < sum_left) {
        return 1;
    } else {
        return 0;
    }
}

int findDefective(int arr[], int low, int high, int genuine_idx) {
    if (low == high) {
        int res = weigh(arr, low, low, genuine_idx, genuine_idx);
        if (res < 0) {
            return low;
        }
        return -1;
    }

    int len = high - low + 1;
    int half = len / 2;

    int l1 = low;
    int r1 = low + half - 1;
    int l2 = low + half;
    int r2 = low + 2 * half - 1;

    int res = weigh(arr, l1, r1, l2, r2);

    if (res < 0) {
        return findDefective(arr, l1, r1, l2);
    } else if (res > 0) {
        return findDefective(arr, l2, r2, l1);
    } else {
        if (len % 2 != 0) {
            int rem_coin = high;
            int rem_res = weigh(arr, rem_coin, rem_coin, low, low);
            if (rem_res < 0) {
                return rem_coin;
            }
        }
        return -1;
    }
}

int validateInput(int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i = i + 1) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int lighter_count = 0;
    for (int i = 0; i < n; i = i + 1) {
        if (arr[i] < max_val) {
            lighter_count = lighter_count + 1;
        }
    }

    if (lighter_count > 1) {
        return 0;
    }
    return 1;
}

int main() {
    int n;
    int coins[100];
    int i;

    printf("Enter total number of coins (n <= 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid input. Please enter a valid positive integer for total coins.\n");
        return 1;
    }

    printf("Enter weights of %d coins:\n", n);
    for (i = 0; i < n; i = i + 1) {
        printf("Coin [%d] weight: ", i);
        if (scanf("%d", &coins[i]) != 1) {
            printf("\nError: Invalid input. Please enter the weight as a valid integer.\n");
            return 1;
        }
    }

    if (validateInput(coins, n) == 0) {
        printf("\nError: Problem allows at most ONE lighter coin with all others equal.\n");
        return 1;
    }

    weigh_count = 0;
    int defective_index = findDefective(coins, 0, n - 1, 0);

    if (defective_index != -1) {
        printf("\nStatus: Defective (Lighter) Coin Found at Index %d\n", defective_index);
        printf("Defective Coin Weight: %d\n", coins[defective_index]);
    } else {
        printf("\nStatus: All coins are PERFECT (No defective coin found)\n");
    }
    printf("Total Balance Scale Weighings Used: %d\n", weigh_count);

    return 0;
}

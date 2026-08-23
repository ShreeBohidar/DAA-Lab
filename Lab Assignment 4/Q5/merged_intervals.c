#include <stdio.h>

void merge(int start[], int end[], int left, int mid, int right) {
    int temp_s[1000], temp_e[1000];
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (start[i] <= start[j]) {
            temp_s[k] = start[i];
            temp_e[k] = end[i];
            i++;
        } else {
            temp_s[k] = start[j];
            temp_e[k] = end[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp_s[k] = start[i];
        temp_e[k] = end[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp_s[k] = start[j];
        temp_e[k] = end[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++) {
        start[i] = temp_s[i];
        end[i] = temp_e[i];
    }
}

void merge_sort(int start[], int end[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(start, end, left, mid);
        merge_sort(start, end, mid + 1, right);
        merge(start, end, left, mid, right);
    }
}

int main() {
    int n;
    int start[1000], end[1000];
    int res_start[1000], res_end[1000];

    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter %d intervals as (x_i y_i):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    // Step 1: Sort intervals by start time in O(n log n)
    merge_sort(start, end, 0, n - 1);

    // Step 2: Linear scan to merge overlapping intervals in O(n)
    int m = 0;
    res_start[m] = start[0];
    res_end[m] = end[0];

    for (int i = 1; i < n; i++) {
        if (start[i] <= res_end[m]) {
            if (end[i] > res_end[m]) {
                res_end[m] = end[i];
            }
        } else {
            m++;
            res_start[m] = start[i];
            res_end[m] = end[i];
        }
    }
    int total_merged = m + 1;

    printf("\nMerged Intervals:\n");
    for (int i = 0; i < total_merged; i++) {
        printf("(%d, %d) ", res_start[i], res_end[i]);
    }
    printf("\n");

    return 0;
}
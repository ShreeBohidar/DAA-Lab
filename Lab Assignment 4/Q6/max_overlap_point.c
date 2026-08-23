#include <stdio.h>

void merge_events(int val[], int type[], int left, int mid, int right) {
    int temp_val[2000], temp_type[2000];
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        // If coordinate is same, process start (+1) before end (-1) because endpoint counts as included
        if (val[i] < val[j] || (val[i] == val[j] && type[i] > type[j])) {
            temp_val[k] = val[i];
            temp_type[k] = type[i];
            i++;
        } else {
            temp_val[k] = val[j];
            temp_type[k] = type[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp_val[k] = val[i];
        temp_type[k] = type[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp_val[k] = val[j];
        temp_type[k] = type[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++) {
        val[i] = temp_val[i];
        type[i] = temp_type[i];
    }
}

void merge_sort_events(int val[], int type[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_events(val, type, left, mid);
        merge_sort_events(val, type, mid + 1, right);
        merge_events(val, type, left, mid, right);
    }
}

int main() {
    int n;
    int val[2000], type[2000]; // type: +1 for start, -1 for end

    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter %d intervals as (l_i r_i):\n", n);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        val[2 * i] = l;
        type[2 * i] = +1;     // Interval begins
        val[2 * i + 1] = r;
        type[2 * i + 1] = -1;  // Interval ends
    }

    int total_events = 2 * n;

    // Step 1: Sort 2n events in O(n log n)
    merge_sort_events(val, type, 0, total_events - 1);

    // Step 2: Sweep line across sorted events in O(n)
    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = val[0];

    for (int i = 0; i < total_events; i++) {
        current_overlap += type[i];
        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = val[i];
        }
    }

    printf("\nPoint in the largest number of intervals: %d\n", best_point);
    printf("Number of intervals overlapping at this point: %d\n", max_overlap);

    return 0;
}
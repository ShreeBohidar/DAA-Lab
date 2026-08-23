#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int temp[1000];
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    int entry[1000], exit_time[1000];

    printf("Enter number of persons (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter entry (a_i) and exit (b_i) times for %d persons:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &entry[i], &exit_time[i]);
    }

    // Sort both entry and exit arrays separately in O(n log n)
    merge_sort(entry, 0, n - 1);
    merge_sort(exit_time, 0, n - 1);

    // Two-pointer scan in O(n) to find peak occupancy
    int i = 0, j = 0;
    int current_people = 0;
    int max_people = 0;
    int peak_time = entry[0];

    while (i < n && j < n) {
        if (entry[i] < exit_time[j]) {
            current_people++;
            if (current_people > max_people) {
                max_people = current_people;
                peak_time = entry[i];
            }
            i++;
        } else {
            current_people--;
            j++;
        }
    }

    printf("\nMaximum people present simultaneously: %d\n", max_people);
    printf("Time when peak occurred: %d\n", peak_time);

    return 0;
}
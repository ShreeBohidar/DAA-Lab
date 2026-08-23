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

int binary_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return 1;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

int main() {
    int n, x;
    int S1[1000], S2[1000];

    printf("Enter size n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter %d elements for S1: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter %d elements for S2: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter target sum x: ");
    scanf("%d", &x);

    merge_sort(S2, 0, n - 1);

    int count = 0;
    printf("\nMatching pairs:\n");
    for (int i = 0; i < n; i++) {
        int complement = x - S1[i];
        if (binary_search(S2, n, complement)) {
            printf("%d (from S1) + %d (from S2) = %d\n", S1[i], complement, x);
            count++;
        }
    }

    if (count == 0) {
        printf("No pair found that adds up to %d.\n", x);
    } else {
        printf("Total pairs found: %d\n", count);
    }

    return 0;
}
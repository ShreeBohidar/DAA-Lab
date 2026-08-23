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

int binary_search(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return 1;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

int total_found = 0;

void find_k_sum(int S[], int n, int k, int current_k, int start_idx, int current_sum, int target_T, int chosen[]) {

    if (current_k == k - 1) {
        int complement = target_T - current_sum;
        if (binary_search(S, start_idx, n - 1, complement)) {
            total_found++;
            printf("Subset found: ");
            for (int i = 0; i < k - 1; i++) {
                printf("%d + ", chosen[i]);
            }
            printf("%d = %d\n", complement, target_T);
        }
        return;
    }

    for (int i = start_idx; i <= n - (k - current_k); i++) {
        chosen[current_k] = S[i];
        find_k_sum(S, n, k, current_k + 1, i + 1, current_sum + S[i], target_T, chosen);
    }
}

int main() {
    int n, k, T;
    int S[1000];
    int chosen[100];

    printf("Enter size of set S (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter %d integers for S: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    printf("Enter value of k: ");
    if (scanf("%d", &k) != 1 || k <= 0 || k > n) return 0;

    printf("Enter target sum T: ");
    scanf("%d", &T);

    merge_sort(S, 0, n - 1);

    printf("\nResults:\n");
    total_found = 0;
    find_k_sum(S, n, k, 0, 0, 0, T, chosen);

    if (total_found == 0) {
        printf("No %d elements in S add up to %d.\n", k, T);
    } else {
        printf("Total matching subsets found: %d\n", total_found);
    }

    return 0;
} 
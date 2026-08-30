#include <stdio.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    return i;
}

int quickSelect(int arr[], int low, int high, int target_idx) {
    if (low <= high) {
        int pi = partition(arr, low, high);

        if (pi == target_idx)
            return arr[pi];
        else if (pi > target_idx)
            return quickSelect(arr, low, pi - 1, target_idx);
        else
            return quickSelect(arr, pi + 1, high, target_idx);
    }
    return -1;
}

int main() {
    int n, k;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter K (1 to %d): ", n);
    scanf("%d", &k);

    if (k >= 1 && k <= n) {

        int ans = quickSelect(arr, 0, n - 1, k - 1);
        printf("The %d-th smallest element is: %d\n", k, ans);
    } else {
        printf("Invalid value of K!\n");
    }

    return 0;
}

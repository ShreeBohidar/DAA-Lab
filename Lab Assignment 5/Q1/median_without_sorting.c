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


int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);

        if (pi == k)
            return arr[pi];
        else if (pi > k)
            return quickSelect(arr, low, pi - 1, k);
        else
            return quickSelect(arr, pi + 1, high, k);
    }
    return -1;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (n % 2 != 0) {

        int median = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median: %d\n", median);
    } else {

        int m1 = quickSelect(arr, 0, n - 1, (n / 2) - 1);
        int m2 = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median: %.2f\n", (m1 + m2) / 2.0);
    }

    return 0;
}

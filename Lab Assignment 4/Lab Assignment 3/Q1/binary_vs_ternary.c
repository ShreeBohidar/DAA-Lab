#include <stdio.h>

int bin_comp = 0;
int tern_comp = 0;

int binarySearch(int arr[], int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        bin_comp = bin_comp + 1;
        if (arr[mid] == key) {
            return mid;
        }

        bin_comp = bin_comp + 1;
        if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int ternarySearch(int arr[], int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        tern_comp = tern_comp + 1;
        if (arr[mid1] == key) {
            return mid1;
        }

        tern_comp = tern_comp + 1;
        if (arr[mid2] == key) {
            return mid2;
        }

        tern_comp = tern_comp + 1;
        if (key < arr[mid1]) {
            high = mid1 - 1;
        } else if (key > arr[mid2]) {
            tern_comp = tern_comp + 1;
            low = mid2 + 1;
        } else {
            tern_comp = tern_comp + 1;
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main() {
    int n;
    int arr[100];
    int key;
    int i;

    printf("Enter number of elements (n <= 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d sorted elements:\n", n);
    for (i = 0; i < n; i = i + 1) {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search: ");
    scanf("%d", &key);

    bin_comp = 0;
    int bin_index = binarySearch(arr, n, key);

    tern_comp = 0;
    int tern_index = ternarySearch(arr, n, key);

    printf("SEARCH RESULTS:\n");

    if (bin_index != -1) {
        printf("Binary Search  : Found at index %d | Comparisons: %d\n", bin_index, bin_comp);
    } else {
        printf("Binary Search  : Element Not Found | Comparisons: %d\n", bin_comp);
    }

    if (tern_index != -1) {
        printf("Ternary Search : Found at index %d | Comparisons: %d\n", tern_index, tern_comp);
    } else {
        printf("Ternary Search : Element Not Found | Comparisons: %d\n", tern_comp);
    }

    if (bin_comp <= tern_comp) {
        printf("CONCLUSION: Binary Search used fewer/equal comparisons than Ternary Search.\n");
    } else {
        printf("CONCLUSION: Ternary Search used fewer comparisons in this instance.\n");
    }
    
    return 0;
}

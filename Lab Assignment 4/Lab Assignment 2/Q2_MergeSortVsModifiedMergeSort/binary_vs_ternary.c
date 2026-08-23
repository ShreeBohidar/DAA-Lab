#include <stdio.h>
#include <stdlib.h>

// 1. Binary Merge Sort

void merge_binary(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* L = (int*)malloc(sizeof(int) * n1);
    int* R = (int*)malloc(sizeof(int) * n2);

    if (!L || !R) {
        printf("Memory allocation failed in binary merge!\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, idx = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[idx++] = L[i++];
        } else {
            arr[idx++] = R[j++];
        }
    }

    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_binary(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort_binary(arr, low, mid);
        merge_sort_binary(arr, mid + 1, high);
        merge_binary(arr, low, mid, high);
    }
}

// 2. Modified or Ternary Merge Sort

void merge_ternary(int arr[], int low, int mid1, int mid2, int high) {
    int n1 = mid1 - low + 1;
    int n2 = mid2 - mid1;
    int n3 = high - mid2;

    int* L = (int*)malloc(sizeof(int) * n1);
    int* M = (int*)malloc(sizeof(int) * n2);
    int* R = (int*)malloc(sizeof(int) * n3);

    if (!L || !M || !R) {
        printf("Memory allocation failed in ternary merge!\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) M[j] = arr[mid1 + 1 + j];
    for (int k = 0; k < n3; k++) R[k] = arr[mid2 + 1 + k];

    int i = 0, j = 0, k = 0, idx = low;

    // Compare elements across all 3 non-empty subarrays
    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) {
            arr[idx++] = L[i++];
        } else if (M[j] <= L[i] && M[j] <= R[k]) {
            arr[idx++] = M[j++];
        } else {
            arr[idx++] = R[k++];
        }
    }

    // Compare elements across remaining 2 non-empty subarrays
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) arr[idx++] = L[i++];
        else arr[idx++] = M[j++];
    }
    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }
    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) arr[idx++] = L[i++];
        else arr[idx++] = R[k++];
    }

    // Copy any remaining elements from the single active subarray
    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = M[j++];
    while (k < n3) arr[idx++] = R[k++];

    free(L);
    free(M);
    free(R);
}

void merge_sort_ternary(int arr[], int low, int high) {
    if (high - low < 1) return;

    int mid1 = low + (high - low) / 3;
    int mid2 = low + 2 * (high - low) / 3;

    merge_sort_ternary(arr, low, mid1);
    merge_sort_ternary(arr, mid1 + 1, mid2);
    merge_sort_ternary(arr, mid2 + 1, high);

    merge_ternary(arr, low, mid1, mid2, high);
}


void print_array(int* arr, int size) {
    if (size <= 12) {
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("%d %d %d %d ... %d %d %d %d (Total: %d elements)\n",
               arr[0], arr[1], arr[2], arr[3],
               arr[size - 4], arr[size - 3], arr[size - 2], arr[size - 1],
               size);
    }
}

int main() {
    int n, choice;

    printf("Enter array size (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }

    int* arr1 = (int*)malloc(sizeof(int) * n);
    int* arr2 = (int*)malloc(sizeof(int) * n);

    if (!arr1 || !arr2) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nSelect Input Mode:\n");
    printf("1. Manual Input\n");
    printf("2. Auto Generate (Random Elements)\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr1[i]);
            arr2[i] = arr1[i]; 
        }
    } else {
        srand(42); 
        for (int i = 0; i < n; i++) {
            arr1[i] = rand() % 500;
            arr2[i] = arr1[i];
        }

        printf("\nGenerated Array: ");
        print_array(arr1, n);
    }

    // Execute Binary Merge Sort
    merge_sort_binary(arr1, 0, n - 1);

    // Execute Ternary Merge Sort
    merge_sort_ternary(arr2, 0, n - 1);

    printf("\n--- Results ---\n");
    printf("Binary Merge Sorted Output : ");
    print_array(arr1, n);

    printf("Modified(Ternary) Merge Sorted Output: ");
    print_array(arr2, n);

    free(arr1);
    free(arr2);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Helper function to check if an array is sorted in non-decreasing order
int is_sorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Unsorted
        }
    }
    return 1; // Sorted
}

// Comparator function for qsort
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Merges two sorted arrays A and B into a single sorted array
int* merge_two(int* A, int sizeA, int* B, int sizeB) {
    int* res = (int*)malloc(sizeof(int) * (sizeA + sizeB));
    if (!res) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    int i = 0, j = 0, k = 0;
    while (i < sizeA && j < sizeB) {
        if (A[i] <= B[j]) {
            res[k++] = A[i++];
        } else {
            res[k++] = B[j++];
        }
    }

    while (i < sizeA) res[k++] = A[i++];
    while (j < sizeB) res[k++] = B[j++];

    return res;
}

// Method 1: Sequential Merge - O(k^2 * n)
int* merge_sequential(int** arrays, int k, int n) {
    int* res = (int*)malloc(sizeof(int) * n);
    if (!res) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        res[i] = arrays[0][i];
    }

    int curr_size = n;
    for (int i = 1; i < k; i++) {
        int* temp = merge_two(res, curr_size, arrays[i], n);
        free(res);
        res = temp;
        curr_size += n;
    }

    return res;
}

// Method 2: Pairwise Merge - O(k * n * log k)
int* merge_pairwise(int** arrays, int k, int n) {
    int** curr_arrays = (int**)malloc(sizeof(int*) * k);
    int* sizes = (int*)malloc(sizeof(int) * k);

    if (!curr_arrays || !sizes) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < k; i++) {
        curr_arrays[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            curr_arrays[i][j] = arrays[i][j];
        }
        sizes[i] = n;
    }

    int count = k;
    while (count > 1) {
        int next_count = 0;

        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                int* temp = merge_two(curr_arrays[i], sizes[i], curr_arrays[i + 1], sizes[i + 1]);
                free(curr_arrays[i]);
                free(curr_arrays[i + 1]);

                curr_arrays[next_count] = temp;
                sizes[next_count] = sizes[i] + sizes[i + 1];
            } else {
                curr_arrays[next_count] = curr_arrays[i];
                sizes[next_count] = sizes[i];
            }
            next_count++;
        }
        count = next_count;
    }

    int* final_res = curr_arrays[0];
    free(curr_arrays);
    free(sizes);

    return final_res;
}

//Printing array elements
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
    int k, n, choice;

    printf("Enter number of arrays (k): ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        printf("Invalid value for k!\n");
        return 1;
    }

    printf("Enter size of each array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid value for n!\n");
        return 1;
    }

    int** arrays = (int**)malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++) {
        arrays[i] = (int*)malloc(sizeof(int) * n);
    }

    printf("\nSelect Input Mode:\n");
    printf("1. Manual Input\n");
    printf("2. Auto Generate (Random Sorted Elements)\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < k; i++) {
            printf("\nEnter %d elements for Array %d:\n", n, i + 1);
            for (int j = 0; j < n; j++) {
                scanf("%d", &arrays[i][j]);
            }

            // Check if input array is sorted
            if (!is_sorted(arrays[i], n)) {
                printf("[Notice] Array %d is not sorted. Automatically sorting it to satisfy precondition...\n", i + 1);
                qsort(arrays[i], n, sizeof(int), compare_ints);
                printf("Updated Sorted Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
        }
    } else {
        srand(42); 
        for (int i = 0; i < k; i++) {
            int val = rand() % 10;
            for (int j = 0; j < n; j++) {
                arrays[i][j] = val;
                val += 1 + (rand() % 5);
            }
        }

        printf("\nInput Arrays:\n");
        if (k <= 6) {
            for (int i = 0; i < k; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
        } else {
            printf("First 2 and last 2 arrays shown:\n");
            for (int i = 0; i < 2; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
            printf("...\n");
            for (int i = k - 2; i < k; i++) {
                printf("Array %d: ", i + 1);
                print_array(arrays[i], n);
            }
        }
    }

    // Execute Sequential Merge
    int* seq_out = merge_sequential(arrays, k, n);

    // Execute Pairwise Merge
    int* pair_out = merge_pairwise(arrays, k, n);

    printf("\n--- Results ---\n");
    printf("Sequential Result: ");
    print_array(seq_out, k * n);

    printf("Pairwise Result:   ");
    print_array(pair_out, k * n);

    // Free allocated memory
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);
    free(seq_out);
    free(pair_out);

    return 0;
}

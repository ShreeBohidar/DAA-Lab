#include <stdio.h>

int comp_count = 0;
int swap_count = 0;

void selectionSort(int arr[], int n) {
    int i;
    int j;
    int min_idx;
    int temp;

    for (i = 0; i < n - 1; i = i + 1) {
        min_idx = i;

        for (j = i + 1; j < n; j = j + 1) {
            comp_count = comp_count + 1;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            swap_count = swap_count + 1;
        }

        printf("After iteration %d (Placing smallest at index %d): ", i + 1, i);
        for (j = 0; j < n; j = j + 1) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int arr[100];
    int i;

    printf("Enter number of elements (n <= 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i = i + 1) {
        printf("Element [%d]: ", i);
        if (scanf("%d", &arr[i]) != 1) {
            printf("\nError: Invalid input. Please enter integers only.\n");
            return 1;
        }
    }

    comp_count = 0;
    swap_count = 0;

    selectionSort(arr, n);

    int theoretical_comps = (n * (n - 1)) / 2;

    printf("SORTING RESULTS:\n");
    printf("Sorted Array                       : ");
    for (i = 0; i < n; i = i + 1) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Actual Comparisons Used            : %d\n", comp_count);
    printf("Theoretical Comparisons [n(n-1)/2] : %d\n", theoretical_comps);
    printf("Total Swaps Performed              : %d\n", swap_count);

    return 0;
}

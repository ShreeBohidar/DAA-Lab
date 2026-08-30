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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of random elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size!\n");
        return 1;
    }

    // 1. Generate pseudo-random numbers and write to "input.txt"
    FILE *fout = fopen("input.txt", "w");
    if (fout == NULL) {
        printf("Error: Could not create input.txt\n");
        return 1;
    }

    unsigned int seed = 12345;
    for (int i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) % 2147483648;
        int random_val = seed % 1000;
        fprintf(fout, "%d ", random_val);
    }
    fclose(fout);
    printf("Generated %d random numbers into 'input.txt'.\n", n);

    // 2. Read back from "input.txt"
    FILE *fin = fopen("input.txt", "r");
    if (fin == NULL) {
        printf("Error: Could not open input.txt for reading\n");
        return 1;
    }

    int arr[n];
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
    }
    fclose(fin);

    // 3. Perform QuickSort
    quickSort(arr, 0, n - 1);

    // 4. Save to "sorted.txt"
    FILE *fout_sorted = fopen("sorted.txt", "w");
    if (fout_sorted == NULL) {
        printf("Error: Could not create sorted.txt\n");
        return 1;
    }

    printf("\nSorted Elements:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        fprintf(fout_sorted, "%d ", arr[i]);
    }
    printf("\n\nSorted data successfully saved to 'sorted.txt'.\n");

    fclose(fout_sorted);
    return 0;
}

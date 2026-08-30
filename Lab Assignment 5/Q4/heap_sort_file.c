#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // 1. Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter number of random elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size!\n");
        return 1;
    }

    // 1. Generate pseudo-random numbers and store into input.txt
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

    // 2. Read elements from input.txt into an array
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

    // 3. Sort using Heap Sort
    heapSort(arr, n);

    // 4. Save sorted output into sorted.txt and print to terminal
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

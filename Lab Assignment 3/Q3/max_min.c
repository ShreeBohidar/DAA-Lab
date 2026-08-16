#include <stdio.h>

int comp_count = 0;

struct Pair {
    int min;
    int max;
};

struct Pair findMaxMin(int arr[], int low, int high) {
    struct Pair result;
    struct Pair leftResult;
    struct Pair rightResult;
    int mid;

    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    if (high == low + 1) {
        comp_count = comp_count + 1;
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    mid = (low + high) / 2;

    leftResult = findMaxMin(arr, low, mid);
    rightResult = findMaxMin(arr, mid + 1, high);

    comp_count = comp_count + 1;
    if (leftResult.max > rightResult.max) {
        result.max = leftResult.max;
    } else {
        result.max = rightResult.max;
    }

    comp_count = comp_count + 1;
    if (leftResult.min < rightResult.min) {
        result.min = leftResult.min;
    } else {
        result.min = rightResult.min;
    }

    return result;
}

int main() {
    int n;
    int arr[100];
    int i;
    struct Pair finalResult;

    printf("Enter number of elements (n <= 100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i = i + 1) {
        printf("Element [%d]: ", i);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    comp_count = 0;
    finalResult = findMaxMin(arr, 0, n - 1);
    int theoretical_bound = (3 * n) / 2;

    printf("\n---------------------------------------------------\n");
    printf("RESULTS:\n");
    printf("Minimum Element          : %d\n", finalResult.min);
    printf("Maximum Element          : %d\n", finalResult.max);
    printf("Actual Comparisons Used  : %d\n", comp_count);
    printf("Theoretical Bound (3n/2): %d\n", theoretical_bound);
    printf("---------------------------------------------------\n");

    if (comp_count <= theoretical_bound) {
        printf("VALIDATION SUCCESSFUL: Actual comparisons <= 3n/2\n");
    } else {
        printf("VALIDATION FAILED.\n");
    }

    return 0;
}

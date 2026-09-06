#include <stdio.h>
#include <math.h>

int findMaximum(int a[], int n) {
    int maxVal = a[0];
    int i;
    for (i = 1; i < n; i++) {
        if (a[i] > maxVal) {
            maxVal = a[i];
        }
    }
    return maxVal;
}

void findFirstAndSecondLargest(int a[], int n) {
    int first = a[0];
    int second = -1000000;
    int i;

    for (i = 1; i < n; i++) {
        if (a[i] > first) {
            second = first;
            first = a[i];
        } else if (a[i] > second && a[i] != first) {
            second = a[i];
        }
    }

    printf("First Largest: %d\n", first);
    if (second == -1000000) {
        printf("Second Largest: Does not exist\n");
    } else {
        printf("Second Largest: %d\n", second);
    }
}

double findMean(int a[], int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        sum = sum + a[i];
    }
    return sum / n;
}

double findMedian(int a[], int n) {
    int temp[100];
    int i, j, t;

    for (i = 0; i < n; i++) {
        temp[i] = a[i];
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    if (n % 2 != 0) {
        return (double)temp[n / 2];
    } else {
        return (temp[(n / 2) - 1] + temp[n / 2]) / 2.0;
    }
}

double findStandardDeviation(int a[], int n) {
    double mean = findMean(a, n);
    double sumSq = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        sumSq = sumSq + ((a[i] - mean) * (a[i] - mean));
    }

    return sqrt(sumSq / n);
}

int findMode(int a[], int n) {
    int maxCount = 0;
    int modeVal = a[0];
    int i, j;

    for (i = 0; i < n; i++) {
        int count = 0;
        for (j = 0; j < n; j++) {
            if (a[j] == a[i]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            modeVal = a[i];
        }
    }

    return modeVal;
}

int removeDuplicates(int a[], int n) {
    int unique[100];
    int uniqueCount = 0;
    int i, j, isDuplicate;

    for (i = 0; i < n; i++) {
        isDuplicate = 0;
        for (j = 0; j < uniqueCount; j++) {
            if (a[i] == unique[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (isDuplicate == 0) {
            unique[uniqueCount] = a[i];
            uniqueCount++;
        }
    }

    for (i = 0; i < uniqueCount; i++) {
        a[i] = unique[i];
    }

    return uniqueCount;
}

void reverseArray(int a[], int n) {
    int start = 0;
    int end = n - 1;
    int temp;

    while (start < end) {
        temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
}

void partitionArray(int a[], int n, int pivot) {
    int temp[100];
    int index = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (a[i] >= pivot) {
            temp[index] = a[i];
            index++;
        }
    }

    for (i = 0; i < n; i++) {
        if (a[i] < pivot) {
            temp[index] = a[i];
            index++;
        }
    }

    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }
}

void printArray(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int n, i, pivot, isValid, newSize;
    int a[100];
    int workArr[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("\n--- Array Operations ---\n");

    printf("(i) Maximum Element: %d\n", findMaximum(a, n));

    printf("(ii) ");
    findFirstAndSecondLargest(a, n);

    printf("(iii) Mean: %.2f\n", findMean(a, n));

    printf("(iv) Median: %.2f\n", findMedian(a, n));

    printf("(v) Standard Deviation: %.2f\n", findStandardDeviation(a, n));

    printf("(vi) Mode: %d\n", findMode(a, n));

    for (i = 0; i < n; i++) workArr[i] = a[i];
    newSize = removeDuplicates(workArr, n);
    printf("(vii) Array after removing duplicates: ");
    printArray(workArr, newSize);

    for (i = 0; i < n; i++) workArr[i] = a[i];
    reverseArray(workArr, n);
    printf("(viii) Reversed Array: ");
    printArray(workArr, n);

    isValid = 0;
    while (isValid == 0) {
        printf("Enter pivot element for partitioning: ");
        scanf("%d", &pivot);

        for (i = 0; i < n; i++) {
            if (a[i] == pivot) {
                isValid = 1;
                break;
            }
        }

        if (isValid == 0) {
            printf("Invalid element! Pivot must exist in the array. Try again.\n");
        }
    }

    for (i = 0; i < n; i++) workArr[i] = a[i];
    partitionArray(workArr, n, pivot);
    printf("(ix) Partitioned Array (elements >= %d first, then < %d): ", pivot, pivot);
    printArray(workArr, n);

    return 0;
}

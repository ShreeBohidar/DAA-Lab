#include <stdio.h>

int reverseCount = 0;
int totalCost = 0;

void reverseSubarray(int p[], int i, int j) {
    int start = i;
    int end = j;
    int temp;

    if (i >= j) {
        return;
    }

    reverseCount++;
    totalCost = totalCost + (j - i + 1);

    while (start < end) {
        temp = p[start];
        p[start] = p[end];
        p[end] = temp;
        start++;
        end--;
    }
}

void printArray(int p[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
}

void sortLinearReversals(int p[], int n) {
    int curr;
    int i, maxIdx;

    reverseCount = 0;
    totalCost = 0;

    for (curr = n - 1; curr > 0; curr--) {
        maxIdx = 0;
        for (i = 1; i <= curr; i++) {
            if (p[i] > p[maxIdx]) {
                maxIdx = i;
            }
        }

        if (maxIdx == curr) {
            continue;
        }

        if (maxIdx > 0) {
            reverseSubarray(p, 0, maxIdx);
        }

        reverseSubarray(p, 0, curr);
    }
}

int binarySearchUpper(int p[], int low, int high, int val) {
    int ans = high + 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (p[mid] > val) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

void blockCyclicShift(int p[], int i, int mid, int j) {
    if (i > mid || mid >= j) {
        return;
    }
    reverseSubarray(p, i, mid);
    reverseSubarray(p, mid + 1, j);
    reverseSubarray(p, i, j);
}

void inPlaceReversalMerge(int p[], int l, int m, int r) {
    if (l >= m + 1 || m >= r) {
        return;
    }

    int len1 = m - l + 1;
    int len2 = r - m;

    if (len1 >= len2) {
        int mid1 = (l + m) / 2;
        int mid2 = binarySearchUpper(p, m + 1, r, p[mid1]);

        int k = mid2 - (m + 1);
        blockCyclicShift(p, mid1, m, mid1 + k);

        int newMid = mid1 + k;
        inPlaceReversalMerge(p, l, mid1 - 1, newMid - 1);
        inPlaceReversalMerge(p, newMid + 1, mid2 - 1, r);
    } else {
        int mid2 = (m + 1 + r) / 2;
        int mid1 = binarySearchUpper(p, l, m, p[mid2]);

        int k = mid2 - (m + 1);
        blockCyclicShift(p, mid1, m, mid1 + k);

        int newMid = mid1 + k;
        inPlaceReversalMerge(p, l, mid1 - 1, newMid - 1);
        inPlaceReversalMerge(p, newMid + 1, mid2, r);
    }
}

void sortReversalDivideConquer(int p[], int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) / 2;
    sortReversalDivideConquer(p, l, mid);
    sortReversalDivideConquer(p, mid + 1, r);
    inPlaceReversalMerge(p, l, mid, r);
}

int main() {
    int n, i;
    int p1[100];
    int p2[100];

    printf("Enter number of elements n: ");
    scanf("%d", &n);

    printf("Enter %d integers :\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &p1[i]);
        p2[i] = p1[i];
    }

    printf("\nOriginal Array: ");
    printArray(p1, n);

    sortLinearReversals(p1, n);
    printf("\n (1) Sorted using O(n) Reversals \n");
    printf("Result: ");
    printArray(p1, n);
    printf("Total Reversal Operations: %d (<= 2n = %d)\n", reverseCount, 2 * n);

    reverseCount = 0;
    totalCost = 0;
    sortReversalDivideConquer(p2, 0, n - 1);
    printf("\n (2) Sorted using Divide-and-Conquer Reversals \n");
    printf("Result: ");
    printArray(p2, n);
    printf("Total Reversals: %d\n", reverseCount);
    printf("Total Cost (sum of |j - i| + 1): %d\n", totalCost);

    return 0;
}

/*
 * DAA Lab-01, Q5: Find the partition point
 * --------------------------------------------
 * Array A has a run of 0's followed by a run of 1's, e.g.
 *   [0,0,0,0,1,1,1,1,1]  -> partition point is index 4 (first 1)
 *
 * NAIVE approach: scan left to right until you see a 1 -> O(n).
 *
 * BETTER approach: since the array is essentially SORTED
 * (monotonic: 0's then 1's), we can binary search for the boundary,
 * exactly like "first true in a sorted boolean array" -> O(log n).
 *
 * We implement both and compare comparisons made.
 */

#include <stdio.h>
#include <stdlib.h>

// O(n) linear scan
int linear_partition_point(int *A, int n, long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (A[i] == 1) return i;
    }
    return n; // all zeros, no partition point (all 0's)
}

// O(log n) binary search: find the first index where A[i] == 1
int binary_partition_point(int *A, int n, long *comparisons) {
    *comparisons = 0;
    int lo = 0, hi = n; // hi = n means "not found yet / all zeros"
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        (*comparisons)++;
        if (A[mid] == 1) {
            hi = mid;       // could be the answer, or answer is to the left
        } else {
            lo = mid + 1;   // A[mid] == 0, answer is strictly to the right
        }
    }
    return lo;
}

int main(void) {
    // Test case 1: manual small example
    int A1[] = {0, 0, 0, 0, 1, 1, 1, 1, 1};
    int n1 = sizeof(A1) / sizeof(A1[0]);
    long c1, c2;
    int p1 = linear_partition_point(A1, n1, &c1);
    int p2 = binary_partition_point(A1, n1, &c2);
    printf("Array: 0 0 0 0 1 1 1 1 1\n");
    printf("Linear search  -> partition index = %d (comparisons = %ld)\n", p1, c1);
    printf("Binary search  -> partition index = %d (comparisons = %ld)\n\n", p2, c2);

    // Test case 2: large randomly generated run-of-0s-then-1s array
    int n = 1000000;
    int *A = malloc(n * sizeof(int));
    int true_partition = n / 3; // pick some point, e.g. 1/3 of the way in
    for (int i = 0; i < n; i++) A[i] = (i < true_partition) ? 0 : 1;

    long lin_cmp, bin_cmp;
    int lin_result = linear_partition_point(A, n, &lin_cmp);
    int bin_result = binary_partition_point(A, n, &bin_cmp);

    printf("Large test: n = %d, true partition index = %d\n", n, true_partition);
    printf("Linear search  -> found %d, comparisons = %ld\n", lin_result, lin_cmp);
    printf("Binary search  -> found %d, comparisons = %ld\n\n", bin_result, bin_cmp);

    printf("Conclusion: linear scan takes O(n) comparisons in the worst\n");
    printf("case (partition point near the end). Binary search exploits\n");
    printf("the monotonic 0...0,1...1 structure to find the boundary in\n");
    printf("O(log n) comparisons -- a huge win for large n (here, %ld vs\n", lin_cmp);
    printf("%ld comparisons for n = %d).\n", bin_cmp, n);

    free(A);
    return 0;
}
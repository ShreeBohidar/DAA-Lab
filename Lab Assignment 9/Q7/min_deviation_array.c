#include <stdio.h>

int main() {
    int n;
    printf("Enter number of elements in the array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int a[200];
    int current_min = 2000000000;

    printf("Enter %d positive integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        /* Transform all odd numbers by multiplying by 2 once to establish upper bounds */
        if (a[i] % 2 != 0) {
            a[i] *= 2;
        }
        if (a[i] < current_min) {
            current_min = a[i];
        }
    }

    int min_deviation = 2000000000;

    printf("\n--- Step-by-Step Reduction ---\n");
    int step = 1;

    /* Repeatedly reduce the maximum element while it is even */
    while (1) {
        /* Find the index of the maximum element */
        int max_idx = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] > a[max_idx]) {
                max_idx = i;
            }
        }

        int current_max = a[max_idx];
        int current_dev = current_max - current_min;

        if (current_dev < min_deviation) {
            min_deviation = current_dev;
        }

        printf("Step %d: Current Max = %d, Current Min = %d -> Deviation = %d (Best: %d)\n",
               step++, current_max, current_min, current_dev, min_deviation);

        /* If the maximum element is odd, it cannot be divided further */
        if (current_max % 2 != 0) {
            printf("Maximum element %d is odd. Cannot reduce further.\n", current_max);
            break;
        }

        /* Divide the maximum even element by 2 */
        a[max_idx] /= 2;

        /* Update the minimum if the new value is smaller */
        if (a[max_idx] < current_min) {
            current_min = a[max_idx];
        }
    }

    printf("\nMinimum deviation possible: %d\n", min_deviation);

    return 0;
}

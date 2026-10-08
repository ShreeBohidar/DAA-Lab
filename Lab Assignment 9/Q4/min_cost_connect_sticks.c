#include <stdio.h>

int main() {
    int n;
    printf("Enter number of sticks (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of sticks.\n");
        return 0;
    }

    if (n == 1) {
        int length;
        printf("Enter length of stick: ");
        scanf("%d", &length);
        printf("\nOnly one stick present. No connections needed.\n");
        printf("Total minimum cost: 0\n");
        return 0;
    }

    int sticks[100];
    printf("Enter the lengths of %d sticks:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }

    int total_cost = 0;
    int current_size = n;

    printf("\n--- Step-by-Step Merging ---\n");

    /* Repeatedly connect the two smallest sticks */
    for (int step = 1; step < n; step++) {
        int min1 = -1, min2 = -1;

        /* Find the two smallest values in the active array */
        for (int i = 0; i < current_size; i++) {
            if (min1 == -1 || sticks[i] < sticks[min1]) {
                min2 = min1;
                min1 = i;
            } else if (min2 == -1 || sticks[i] < sticks[min2]) {
                min2 = i;
            }
        }

        int cost = sticks[min1] + sticks[min2];
        total_cost += cost;

        printf("Step %d: Connect sticks of lengths %d and %d -> Cost = %d, Total Cost = %d\n",
               step, sticks[min1], sticks[min2], cost, total_cost);

        /* Replace one stick with the combined stick, and overwrite the other with the last element */
        sticks[min1] = cost;
        sticks[min2] = sticks[current_size - 1];
        current_size--;
    }

    printf("\nAll sticks connected into one!\n");
    printf("Minimum total cost: %d\n", total_cost);

    return 0;
}

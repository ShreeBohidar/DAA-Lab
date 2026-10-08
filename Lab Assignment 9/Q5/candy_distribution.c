#include <stdio.h>

int main() {
    int n;
    printf("Enter number of children (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of children.\n");
        return 0;
    }

    int ratings[100];
    int candies[100];

    printf("Enter ratings of %d children:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
        candies[i] = 1; /* Requirement: each child gets at least 1 candy */
    }

    /* Pass 1: Left-to-Right greedy pass */
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    /* Pass 2: Right-to-Left greedy pass */
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] <= candies[i + 1]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    /* Calculate total candies */
    int total_candies = 0;
    printf("\n--- Candy Allocation per Child ---\n");
    for (int i = 0; i < n; i++) {
        printf("Child %d (Rating %d): %d candies\n", i + 1, ratings[i], candies[i]);
        total_candies += candies[i];
    }

    printf("\nMinimum total candies needed: %d\n", total_candies);

    return 0;
}

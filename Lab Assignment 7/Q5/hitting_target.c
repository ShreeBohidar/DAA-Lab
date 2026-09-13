#include <stdio.h>

int main() {
    int n;
    int i;
    int shot_count = 0;

    printf("Enter number of hiding spots (n): ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("Number of hiding spots must be greater than 1.\n");
        return 0;
    }

    if (n == 2) {
        printf("\nShooting sequence:\n");
        printf("Shot 1: Spot 2\n");
        printf("Shot 2: Spot 2\n");
        printf("Total shots guaranteed: 2\n");
        return 0;
    }

    printf("\nShooting sequence:\n");

    for (i = 2; i <= n - 1; i++) {
        shot_count++;
        printf("Shot %d: Spot %d\n", shot_count, i);
    }

    for (i = n - 1; i >= 2; i--) {
        shot_count++;
        printf("Shot %d: Spot %d\n", shot_count, i);
    }

    printf("\nTotal shots guaranteed: %d\n", shot_count);

    return 0;
}
#include <stdio.h>

int main() {
    int n;
    int total_coins;
    int min_moves;

    printf("Enter the number of rows in the coin triangle (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of rows must be positive.\n");
        return 0;
    }

    total_coins = (n * (n + 1)) / 2;
    min_moves = (n * (n + 1)) / 6;

    printf("Total number of coins: %d\n", total_coins);
    printf("Minimum moves required to invert the triangle: %d\n", min_moves);

    return 0;
}
#include <stdio.h>

int moves = 0;

void set_on(int k);

void set_off(int k) {
    if (k <= 0) {
        return;
    }
    if (k == 1) {
        moves++;
        printf("Move %d: Toggle switch 1\n", moves);
        return;
    }
    set_off(k - 2);
    moves++;
    printf("Move %d: Toggle switch %d\n", moves, k);
    set_on(k - 2);
    set_off(k - 1);
}

void set_on(int k) {
    if (k <= 0) {
        return;
    }
    if (k == 1) {
        moves++;
        printf("Move %d: Toggle switch 1\n", moves);
        return;
    }
    set_on(k - 1);
    set_off(k - 2);
    moves++;
    printf("Move %d: Toggle switch %d\n", moves, k);
    set_on(k - 2);
}

int main() {
    int n;

    printf("Enter number of switches (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of switches must be positive.\n");
        return 0;
    }

    printf("\nSolution moves:\n");
    set_off(n);

    printf("\nTotal moves: %d\n", moves);
    return 0;
}
#include <stdio.h>

int move_count = 0;

void hanoi3(int n, char from, char to, char aux) {
    if (n == 0) {
        return;
    }
    hanoi3(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    move_count++;
    hanoi3(n - 1, aux, to, from);
}

void reves(int n, int k, char from, char to, char aux1, char aux2) {
    if (n == 0) {
        return;
    }
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        move_count++;
        return;
    }

    int next_k = k - 1;
    if (next_k < 1) {
        next_k = 1;
    }

    reves(k, next_k, from, aux1, to, aux2);

    hanoi3(n - k, from, to, aux2);

    reves(k, next_k, aux1, to, from, aux2);
}

int main() {
    int n;
    int k;

    printf("Enter number of disks (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of disks must be positive.\n");
        return 0;
    }

    if (n == 8) {
        k = 4;
    } else {
           k = n / 2;
    }

    move_count = 0;
    printf("\nSequence of moves:\n");
    reves(n, k, 'A', 'D', 'B', 'C');

    printf("\nTotal moves: %d\n", move_count);

    return 0;
}

#include <stdio.h>

int main() {
    int n;
    int birth[100], death[100];
    int i, j, temp;
    int b_idx, d_idx;
    int current_alive, max_alive;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Enter birth and death year for each scientist:\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &birth[i], &death[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (birth[j] > birth[j + 1]) {
                temp = birth[j];
                birth[j] = birth[j + 1];
                birth[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (death[j] > death[j + 1]) {
                temp = death[j];
                death[j] = death[j + 1];
                death[j + 1] = temp;
            }
        }
    }

    /* Pass 1: Determine the maximum number of scientists alive */
    b_idx = 0;
    d_idx = 0;
    current_alive = 0;
    max_alive = 0;

    while (b_idx < n) {
        if (death[d_idx] <= birth[b_idx]) {
            current_alive--;
            d_idx++;
        } else {
            current_alive++;
            if (current_alive > max_alive) {
                max_alive = current_alive;
            }
            b_idx++;
        }
    }

    printf("\nMaximum number of scientists alive: %d\n", max_alive);
    printf("Year(s) when this maximum was reached:\n");

    b_idx = 0;
    d_idx = 0;
    current_alive = 0;

    while (b_idx < n) {
        if (death[d_idx] <= birth[b_idx]) {
            current_alive--;
            d_idx++;
        } else {
            current_alive++;
            if (current_alive == max_alive) {
                printf("%d\n", birth[b_idx]);
            }
            b_idx++;
        }
    }

    return 0;
}

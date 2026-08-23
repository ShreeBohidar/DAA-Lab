#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int num[1000];
    char col[1000][10];

    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter %d items as (number color):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &num[i], col[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        if (num[i] > num[i + 1]) {
            printf("Error: Input is not sorted by number.\n");
            return 0;
        }
    }

    printf("\nSorted output:\n");

    for (int i = 0; i < n; i++) {
        if (strcmp(col[i], "red") == 0) {
            printf("(%d, %s)\n", num[i], col[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (strcmp(col[i], "blue") == 0) {
            printf("(%d, %s)\n", num[i], col[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (strcmp(col[i], "yellow") == 0) {
            printf("(%d, %s)\n", num[i], col[i]);
        }
    }

    return 0;
}
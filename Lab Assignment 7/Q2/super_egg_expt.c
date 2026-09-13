#include <stdio.h>

int main() {
    int E, F;
    int dp[51][1001];
    int i, j, k;
    int min_drops;
    int worst_case;

    printf("Enter number of eggs (E): ");
    scanf("%d", &E);

    printf("Enter number of floors (F): ");
    scanf("%d", &F);

    if (E <= 0 || F < 0) {
        printf("Invalid input.\n");
        return 0;
    }

    for (i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }


    for (j = 1; j <= F; j++) {
        dp[1][j] = j;
    }


    for (i = 2; i <= E; i++) {
        for (j = 2; j <= F; j++) {
            min_drops = 1000000;

            for (k = 1; k <= j; k++) {

                if (dp[i - 1][k - 1] > dp[i][j - k]) {
                    worst_case = 1 + dp[i - 1][k - 1];
                } else {
                    worst_case = 1 + dp[i][j - k];
                }

                if (worst_case < min_drops) {
                    min_drops = worst_case;
                }
            }

            dp[i][j] = min_drops;
        }
    }

    printf("Minimum number of droppings guaranteed: %d\n", dp[E][F]);

    return 0;
}

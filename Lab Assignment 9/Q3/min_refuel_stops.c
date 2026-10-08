#include <stdio.h>

int main() {
    int n;
    int D, F;

    printf("Enter target distance (D) and initial fuel (F): ");
    if (scanf("%d %d", &D, &F) != 2 || D <= 0 || F < 0) {
        printf("Invalid target distance or initial fuel.\n");
        return 0;
    }

    printf("Enter number of refueling stations (n): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid number of stations.\n");
        return 0;
    }

    int dist[100];
    int fuel[100];

    printf("Enter distance and fuel for each station:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &dist[i], &fuel[i]);
    }

    /* Sort stations by distance ascending using simple bubble sort */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dist[j] > dist[j + 1]) {
                int temp_d = dist[j];
                dist[j] = dist[j + 1];
                dist[j + 1] = temp_d;

                int temp_f = fuel[j];
                fuel[j] = fuel[j + 1];
                fuel[j + 1] = temp_f;
            }
        }
    }

    /* Used flag to track which passed stations have been refueled from */
    int used[100] = {0};

    int current_fuel = F;
    int stops = 0;
    int idx = 0; /* Pointer to next station along the road */

    printf("\n--- Journey Simulation ---\n");

    /* Continue driving until current fuel can reach target D */
    while (current_fuel < D) {
        /* Check if any reachable station exists that we haven't refueled from */
        int best_station = -1;
        int max_fuel = -1;

        for (int i = 0; i < n; i++) {
            if (dist[i] <= current_fuel && !used[i]) {
                if (fuel[i] > max_fuel) {
                    max_fuel = fuel[i];
                    best_station = i;
                }
            }
        }

        /* If no reachable station is left to refuel from, target is unreachable */
        if (best_station == -1) {
            printf("Cannot reach the target D = %d with the given stations.\n", D);
            printf("Maximum reachable distance: %d\n", current_fuel);
            return 0;
        }

        /* Greedy choice: refuel at the station with the largest capacity */
        used[best_station] = 1;
        current_fuel += fuel[best_station];
        stops++;

        printf("Stop %d: Refueled at station %d (dist: %d, +%d fuel) -> New reach: %d\n",
               stops, best_station + 1, dist[best_station], fuel[best_station], current_fuel);
    }

    printf("\nTarget %d reached successfully!\n", D);
    printf("Minimum number of refueling stops required: %d\n", stops);

    return 0;
}
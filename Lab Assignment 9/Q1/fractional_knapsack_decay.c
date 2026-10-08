#include <stdio.h>

typedef struct {
    int id;
    double v;        /* base value */
    double w;        /* weight */
    double lambda;   /* decay rate */
    double density;  /* initial value density: v / w */
} Item;

/* Swap helper */
void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

/* Sort items primarily by decay rate lambda descending (greedy exchange order),
   breaking ties by initial value density descending */
void sort_items(Item arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].lambda < arr[j + 1].lambda ||
               (arr[j].lambda == arr[j + 1].lambda && arr[j].density < arr[j + 1].density)) {
                swap_items(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    double W;

    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of items.\n");
        return 0;
    }

    printf("Enter knapsack capacity (W): ");
    if (scanf("%lf", &W) != 1 || W <= 0) {
        printf("Invalid knapsack capacity.\n");
        return 0;
    }

    Item items[100];
    printf("Enter base value (v), weight (w), and decay rate (lambda) for each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
        items[i].density = items[i].v / items[i].w;
    }

    /* Greedy ordering */
    sort_items(items, n);

    double current_weight = 0.0;
    double current_time = 0.0;
    double total_value = 0.0;

    printf("\n--- Optimal Scheduling & Selection Order ---\n");
    for (int i = 0; i < n; i++) {
        if (current_weight >= W) {
            break;
        }

        double remaining_cap = W - current_weight;
        double take_weight = (items[i].w <= remaining_cap) ? items[i].w : remaining_cap;
        double fraction = take_weight / items[i].w;

        /* Effective density at current time */
        double effective_density = items[i].density - (items[i].lambda * current_time);

        /* Only take if effective value contribution remains non-negative */
        if (effective_density > 0.0) {
            double gained_value = take_weight * effective_density;
            total_value += gained_value;

            printf("Item %d: Took weight = %.2f / %.2f (Fraction = %.2f) at time t = %.2f | Eff. Density = %.3f | Value Gained = %.2f\n",
                   items[i].id, take_weight, items[i].w, fraction, current_time, effective_density, gained_value);

            current_weight += take_weight;
            current_time += take_weight; /* Consumption time progresses as capacity is filled */
        } else {
            printf("Item %d: Skipped because effective density decayed to <= 0 (%.3f) at t = %.2f\n",
                   items[i].id, effective_density, current_time);
        }
    }

    printf("\nTotal weight packed: %.2f / %.2f\n", current_weight, W);
    printf("Maximum total value achieved: %.2f\n", total_value);

    return 0;
}
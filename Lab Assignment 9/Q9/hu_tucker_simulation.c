#include <stdio.h>

int main() {
    int n;
    printf("Enter number of leaf weights (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of weights.\n");
        return 0;
    }

    if (n == 1) {
        int w;
        printf("Enter weight 1: ");
        scanf("%d", &w);
        printf("\nTotal Weighted Path Cost: 0\n");
        return 0;
    }

    int orig_weights[100];
    int parent[200];
    int left[200];
    int right[200];

    printf("Enter %d ordered weights:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &orig_weights[i]);
        parent[i] = -1;
        left[i] = -1;
        right[i] = -1;
    }

    /* Working sequence for Phase 1: Combination */
    int node_idx[100];
    int weight[100];
    int is_compound[100];
    int cur_len = n;

    for (int i = 0; i < n; i++) {
        node_idx[i] = i;
        weight[i] = orig_weights[i];
        is_compound[i] = 0;
    }

    int next_node = n;

    printf("\n--- Hu-Tucker Phase 1: Combination Steps ---\n");

    /* Repeat until single composite root is obtained */
    for (int step = 1; step < n; step++) {
        int best_i = -1, best_j = -1;
        int min_sum = 2000000000;

        /* Find compatible pair with minimum sum */
        for (int i = 0; i < cur_len - 1; i++) {
            for (int j = i + 1; j < cur_len; j++) {
                /* Nodes i and j are compatible if adjacent or all intervening nodes are compound */
                int compatible = 1;
                for (int k = i + 1; k < j; k++) {
                    if (!is_compound[k]) {
                        compatible = 0;
                        break;
                    }
                }

                if (compatible) {
                    int sum = weight[i] + weight[j];
                    if (sum < min_sum) {
                        min_sum = sum;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        /* Combine node best_i and node best_j */
        int u = node_idx[best_i];
        int v = node_idx[best_j];
        int parent_node = next_node++;

        parent[u] = parent_node;
        parent[v] = parent_node;
        left[parent_node] = u;
        right[parent_node] = v;

        printf("Step %d: Merged node %d (wt: %d) and node %d (wt: %d) -> New wt: %d\n",
               step, u + 1, weight[best_i], v + 1, weight[best_j], min_sum);

        /* Replace best_i with new compound node */
        node_idx[best_i] = parent_node;
        weight[best_i] = min_sum;
        is_compound[best_i] = 1;

        /* Remove best_j by shifting left */
        for (int k = best_j; k < cur_len - 1; k++) {
            node_idx[k] = node_idx[k + 1];
            weight[k] = weight[k + 1];
            is_compound[k] = is_compound[k + 1];
        }
        cur_len--;
    }

    /* Phase 2: Level Assignment (determine depth of each original leaf) */
    int depth[100];
    int total_weighted_cost = 0;

    printf("\n--- Leaf Depths & Cost Contribution ---\n");
    for (int i = 0; i < n; i++) {
        int d = 0;
        int curr = i;
        while (parent[curr] != -1) {
            d++;
            curr = parent[curr];
        }
        depth[i] = d;
        int leaf_cost = orig_weights[i] * depth[i];
        total_weighted_cost += leaf_cost;
        printf("Leaf %d (Weight: %d) -> Depth: %d | Cost: %d\n",
               i + 1, orig_weights[i], depth[i], leaf_cost);
    }

    printf("\nOptimal Alphabetic Tree Total Weighted Cost: %d\n", total_weighted_cost);

    return 0;
}

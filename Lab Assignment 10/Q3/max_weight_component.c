#include <stdio.h>

#define MAX_NODES 10005

int parent_node[MAX_NODES];
int comp_size[MAX_NODES];
long long comp_weight[MAX_NODES];

void initialize_dsu(int n, long long weights[]) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = i;
        comp_size[i] = 1;
        comp_weight[i] = weights[i];
    }
}

int find_root(int v) {
    if (parent_node[v] == v) {
        return v;
    }
    return parent_node[v] = find_root(parent_node[v]);
}

void union_sets(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);

    if (root_u != root_v) {
        if (comp_size[root_u] < comp_size[root_v]) {
            int temp = root_u;
            root_u = root_v;
            root_v = temp;
        }
        parent_node[root_v] = root_u;
        comp_size[root_u] += comp_size[root_v];
        comp_weight[root_u] += comp_weight[root_v];
    }
}

long long get_max_weight_under_k(int n, int k) {
    long long max_val = -1;
    for (int i = 1; i <= n; i++) {
        if (parent_node[i] == i) {
            if (comp_size[i] <= k) {
                if (max_val == -1 || comp_weight[i] > max_val) {
                    max_val = comp_weight[i];
                }
            }
        }
    }
    return max_val;
}

int main() {
    int n, m, k;
    long long weights[MAX_NODES];

    printf("Enter number of vertices (n), edges (m), and size threshold (K): ");
    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0;
    }

    printf("Enter weights of %d vertices:\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weights[i]);
    }

    initialize_dsu(n, weights);

    long long initial_max = get_max_weight_under_k(n, k);
    printf("Initial maximum component weight (size <= %d): %lld\n", k, initial_max);

    printf("Enter %d edges sequentially (u v):\n", m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        union_sets(u, v);
        long long current_max = get_max_weight_under_k(n, k);

        if (current_max == -1) {
            printf("After adding edge %d-%d: No component satisfies size <= %d\n", u, v, k);
        } else {
            printf("After adding edge %d-%d: Maximum component weight (size <= %d) = %lld\n", u, v, k, current_max);
        }
    }

    return 0;
}

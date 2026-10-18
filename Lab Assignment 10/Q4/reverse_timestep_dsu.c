#include <stdio.h>

#define MAX_V 10005
#define MAX_E 20005

int head[MAX_V];
int to_node[2 * MAX_E];
int next_edge[2 * MAX_E];
int edge_count;

int parent_node[MAX_V];
int rank_tree[MAX_V];
long long comp_weight[MAX_V];
int is_active[MAX_V];

void add_edge(int u, int v) {
    edge_count++;
    to_node[edge_count] = v;
    next_edge[edge_count] = head[u];
    head[u] = edge_count;

    edge_count++;
    to_node[edge_count] = u;
    next_edge[edge_count] = head[v];
    head[v] = edge_count;
}

void initialize_dsu(int n, long long weights[]) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = i;
        rank_tree[i] = 0;
        comp_weight[i] = weights[i];
        is_active[i] = 0;
        head[i] = 0;
    }
    edge_count = 0;
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
        if (rank_tree[root_u] < rank_tree[root_v]) {
            parent_node[root_u] = root_v;
            comp_weight[root_v] += comp_weight[root_u];
        } else {
            parent_node[root_v] = root_u;
            comp_weight[root_u] += comp_weight[root_v];
            if (rank_tree[root_u] == rank_tree[root_v]) {
                rank_tree[root_u]++;
            }
        }
    }
}

int main() {
    int v, e;
    long long weights[MAX_V];
    int deletion_order[MAX_V];
    long long ans[MAX_V];

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &v, &e) != 2) {
        return 0;
    }

    initialize_dsu(v, weights);

    printf("Enter weights of %d vertices:\n", v);
    for (int i = 1; i <= v; i++) {
        scanf("%lld", &weights[i]);
        comp_weight[i] = weights[i];
    }

    printf("Enter %d edges (u v):\n", e);
    for (int i = 0; i < e; i++) {
        int u, val;
        scanf("%d %d", &u, &val);
        add_edge(u, val);
    }

    printf("Enter the sequence of %d vertex deletions:\n", v);
    for (int i = 1; i <= v; i++) {
        scanf("%d", &deletion_order[i]);
    }

    long long current_max = 0;
    ans[v] = 0;

    for (int step = v; step >= 1; step--) {
        int node = deletion_order[step];
        is_active[node] = 1;

        if (comp_weight[node] > current_max) {
            current_max = comp_weight[node];
        }

        for (int edge = head[node]; edge != 0; edge = next_edge[edge]) {
            int neighbor = to_node[edge];
            if (is_active[neighbor]) {
                int root_node = find_root(node);
                int root_neighbor = find_root(neighbor);

                if (root_node != root_neighbor) {
                    union_sets(node, neighbor);
                    int new_root = find_root(node);
                    if (comp_weight[new_root] > current_max) {
                        current_max = comp_weight[new_root];
                    }
                }
            }
        }

        if (step > 1) {
            ans[step - 1] = current_max;
        }
    }

    printf("\nMaximum component sum after each deletion:\n");
    for (int i = 1; i <= v; i++) {
        printf("After deleting vertex %d: Maximum component sum = %lld\n", deletion_order[i], ans[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100005

int parent_node[MAX_VERTICES];
int parity_to_parent[MAX_VERTICES];
int rank_tree[MAX_VERTICES];

void initialize_dsu(int n) {
    for (int i = 0; i <= n; i++) {
        parent_node[i] = i;
        parity_to_parent[i] = 0;
        rank_tree[i] = 0;
    }
}

int find_root(int v) {
    if (parent_node[v] == v) {
        return v;
    }
    int original_parent = parent_node[v];
    parent_node[v] = find_root(parent_node[v]);
    parity_to_parent[v] ^= parity_to_parent[original_parent];
    return parent_node[v];
}

int add_edge_online(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);

    if (root_u == root_v) {
        if (parity_to_parent[u] == parity_to_parent[v]) {
            return 0;
        }
        return 1;
    }

    if (rank_tree[root_u] < rank_tree[root_v]) {
        parent_node[root_u] = root_v;
        parity_to_parent[root_u] = parity_to_parent[u] ^ parity_to_parent[v] ^ 1;
    } else {
        parent_node[root_v] = root_u;
        parity_to_parent[root_v] = parity_to_parent[u] ^ parity_to_parent[v] ^ 1;
        if (rank_tree[root_u] == rank_tree[root_v]) {
            rank_tree[root_u]++;
        }
    }
    return 1;
}

int main() {
    int vertices, edges;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &vertices, &edges) != 2) {
        return 0;
    }

    initialize_dsu(vertices);

    printf("Enter edges one by one:\n");
    for (int i = 1; i <= edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        int is_bipartite = add_edge_online(u, v);
        if (is_bipartite) {
            printf("Edge %d-%d: Accepted. Graph remains bipartite.\n", u, v);
        } else {
            printf("Edge %d-%d: Rejected. Introduces an odd cycle.\n", u, v);
        }
    }

    return 0;
}

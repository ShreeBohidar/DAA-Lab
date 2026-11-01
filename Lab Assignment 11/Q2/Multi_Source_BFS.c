#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, k, r;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    printf("Enter number of hubs (K) and radius threshold (R): ");
    if (scanf("%d %d", &k, &r) != 2) return 0;

    // Sized directly to n and k without hardcoded MAX defines
    int hubs[k + 1];
    printf("Enter the %d hub vertices (1 to %d):\n", k, n);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &hubs[i]);
    }

    // Adjacency matrix for simple, pointer-free graph representation
    int adj[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
    }

    printf("Enter %d undirected edges (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int dist[n + 1];
    int owner[n + 1];
    int queue[n + 1];
    int front = 0, rear = 0;

    const int INF = 1000000000;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        owner[i] = -1;
    }

    // Multi-source initialization: enqueue hubs in increasing index order
    for (int i = 1; i <= k; i++) {
        int h = hubs[i];
        if (dist[h] == INF) {
            dist[h] = 0;
            owner[h] = i;
            queue[rear++] = h;
        } else if (dist[h] == 0 && i < owner[h]) {
            owner[h] = i;
        }
    }

    // Multi-Source BFS
    while (front < rear) {
        int u = queue[front++];

        // If distance already reaches radius limit, no need to expand further
        if (dist[u] >= r) {
            continue;
        }

        for (int v = 1; v <= n; v++) {
            if (adj[u][v]) {
                if (dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    owner[v] = owner[u];
                    queue[rear++] = v;
                } else if (dist[u] + 1 == dist[v]) {
                    // Tie-breaking: choose smaller hub index
                    if (owner[u] < owner[v]) {
                        owner[v] = owner[u];
                    }
                }
            }
        }
    }

    // Output assignments based on radius threshold R
    printf("\n--- Voronoi Cell Partitioning (Radius R = %d) ---\n", r);
    printf("Vertex\tOwner Hub Index\tHub Vertex\tDistance\n");
    for (int v = 1; v <= n; v++) {
        if (dist[v] <= r && owner[v] != -1) {
            printf("%d\t%d\t\t%d\t\t%d\n", v, owner[v], hubs[owner[v]], dist[v]);
        } else {
            printf("%d\t-1\t\t-\t\t%s\n", v, (dist[v] >= INF ? "INF" : "> R"));
        }
    }

    return 0;
}

#include <stdio.h>

#define MAX_V 1005
#define MAX_E 20005
#define INF 1000000000

// Graph representation using flat arrays (no pointers)
int head[MAX_V];
int to[MAX_E];
int weight[MAX_E];
int next_edge[MAX_E];
int edge_count = 0;

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    weight[edge_count] = w;
    next_edge[edge_count] = head[u];
    head[u] = edge_count++;
}

// State representation for 0-1 BFS Deque
int deque_u[4 * MAX_V + 5];
int deque_p[4 * MAX_V + 5];
int front_idx, back_idx;

// dist[u][parity]: 0 for even weight count, 1 for odd
int dist[MAX_V][2];

int main() {
    int n, m;
    int source, C;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    printf("Enter source vertex (1 to %d) and penalty C: ", n);
    if (scanf("%d %d", &source, &C) != 2) return 0;

    // Initialize graph heads
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edge_count = 0;

    printf("Enter %d directed edges (u v weight) where weight is 0 or 1:\n", m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    // Initialize distances
    for (int i = 1; i <= n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    // Deque pointers: centered to allow push_front and push_back
    int mid = 2 * MAX_V;
    front_idx = mid;
    back_idx = mid;

    // Push source state (source, even parity = 0) with distance 0
    dist[source][0] = 0;
    deque_u[back_idx] = source;
    deque_p[back_idx] = 0;
    back_idx++;

    // 0-1 BFS Loop
    while (front_idx < back_idx) {
        int curr_u = deque_u[front_idx];
        int curr_p = deque_p[front_idx];
        front_idx++;

        int e = head[curr_u];
        while (e != -1) {
            int v = to[e];
            int w = weight[e];
            int next_p = (curr_p + w) % 2;

            if (dist[curr_u][curr_p] + w < dist[v][next_p]) {
                dist[v][next_p] = dist[curr_u][curr_p] + w;
                if (w == 0) {
                    // Push to front
                    front_idx--;
                    deque_u[front_idx] = v;
                    deque_p[front_idx] = next_p;
                } else {
                    // Push to back
                    deque_u[back_idx] = v;
                    deque_p[back_idx] = next_p;
                    back_idx++;
                }
            }
            e = next_edge[e];
        }
    }

    // Output results
    printf("\n--- Minimum Effective Cost from Source %d (Penalty C = %d) ---\n", source, C);
    printf("Vertex\tMin Cost\tDetails\n");
    for (int v = 1; v <= n; v++) {
        int best_cost = INF;
        int used_parity = -1;

        if (dist[v][0] < INF) {
            int cost_even = dist[v][0];
            if (cost_even < best_cost) {
                best_cost = cost_even;
                used_parity = 0;
            }
        }
        if (dist[v][1] < INF) {
            int cost_odd = dist[v][1] + C;
            if (cost_odd < best_cost) {
                best_cost = cost_odd;
                used_parity = 1;
            }
        }

        if (best_cost >= INF) {
            printf("%d\tUnreachable\t-\n", v);
        } else {
            if (used_parity == 0) {
                printf("%d\t%d\t\t(Even path weight = %d, penalty = 0)\n", v, best_cost, dist[v][0]);
            } else {
                printf("%d\t%d\t\t(Odd path weight = %d + penalty %d)\n", v, best_cost, dist[v][1], C);
            }
        }
    }

    return 0;
}

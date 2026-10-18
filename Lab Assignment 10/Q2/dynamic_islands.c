#include <stdio.h>

#define MAX_CELLS 40005

int parent_node[MAX_CELLS];
int rank_tree[MAX_CELLS];
int grid[205][205];

int get_flat_index(int r, int c, int cols) {
    return r * cols + c;
}

void initialize_dsu(int total_cells) {
    for (int i = 0; i < total_cells; i++) {
        parent_node[i] = i;
        rank_tree[i] = 0;
    }
}

int find_root(int v) {
    if (parent_node[v] == v) {
        return v;
    }
    return parent_node[v] = find_root(parent_node[v]);
}

int union_sets(int a, int b) {
    int root_a = find_root(a);
    int root_b = find_root(b);

    if (root_a == root_b) {
        return 0;
    }

    if (rank_tree[root_a] < rank_tree[root_b]) {
        parent_node[root_a] = root_b;
    } else {
        parent_node[root_b] = root_a;
        if (rank_tree[root_a] == rank_tree[root_b]) {
            rank_tree[root_a]++;
        }
    }
    return 1;
}

int main() {
    int rows, cols, k;
    printf("Enter grid dimensions R and C: ");
    if (scanf("%d %d", &rows, &cols) != 2) {
        return 0;
    }

    printf("Enter number of land additions (k): ");
    if (scanf("%d", &k) != 1) {
        return 0;
    }

    int total_cells = rows * cols;
    initialize_dsu(total_cells);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int island_count = 0;

    printf("Enter land coordinates sequentially (r c):\n");
    for (int step = 1; step <= k; step++) {
        int r, c;
        scanf("%d %d", &r, &c);

        if (grid[r][c] == 1) {
            printf("Operation %d at (%d, %d): Island count = %d\n", step, r, c, island_count);
            continue;
        }

        grid[r][c] = 1;
        island_count++;
        int current_flat = get_flat_index(r, c, cols);

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                int neighbor_flat = get_flat_index(nr, nc, cols);
                if (union_sets(current_flat, neighbor_flat)) {
                    island_count--;
                }
            }
        }

        printf("Operation %d at (%d, %d): Island count = %d\n", step, r, c, island_count);
    }

    return 0;
}

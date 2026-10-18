#include <stdio.h>

#define MAX_N 100005

int parent_node[MAX_N];
int rank_tree[MAX_N];
int arr[MAX_N];
int result[MAX_N];

int comp_indices[MAX_N];
int comp_values[MAX_N];

void initialize_dsu(int n) {
    for (int i = 1; i <= n; i++) {
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

void union_sets(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);

    if (root_u != root_v) {
        if (rank_tree[root_u] < rank_tree[root_v]) {
            parent_node[root_u] = root_v;
        } else {
            parent_node[root_v] = root_u;
            if (rank_tree[root_u] == rank_tree[root_v]) {
                rank_tree[root_u]++;
            }
        }
    }
}

void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int l_arr[n1];
    int r_arr[n2];

    for (int i = 0; i < n1; i++) {
        l_arr[i] = a[left + i];
    }
    for (int j = 0; j < n2; j++) {
        r_arr[j] = a[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (l_arr[i] <= r_arr[j]) {
            a[k++] = l_arr[i++];
        } else {
            a[k++] = r_arr[j++];
        }
    }

    while (i < n1) {
        a[k++] = l_arr[i++];
    }
    while (j < n2) {
        a[k++] = r_arr[j++];
    }
}

void merge_sort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main() {
    int n, m;
    printf("Enter size of permutation (n) and number of allowable swaps (m): ");
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    printf("Enter permutation of %d elements:\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    initialize_dsu(n);

    printf("Enter %d allowable swap pairs (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }

    int visited[MAX_N];
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int root = find_root(i);
            int count = 0;

            for (int j = i; j <= n; j++) {
                if (!visited[j] && find_root(j) == root) {
                    comp_indices[count] = j;
                    comp_values[count] = arr[j];
                    visited[j] = 1;
                    count++;
                }
            }

            merge_sort(comp_indices, 0, count - 1);
            merge_sort(comp_values, 0, count - 1);

            for (int k = 0; k < count; k++) {
                result[comp_indices[k]] = comp_values[k];
            }
        }
    }

    printf("\nLexicographically smallest permutation:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>

int main() {
    int n;
    printf("Enter number of symbols (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of symbols.\n");
        return 0;
    }

    char symbol[100];
    int freq[200];
    int parent[200];
    int left[200];
    int right[200];

    printf("Enter symbol (char) and frequency for each:\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &symbol[i], &freq[i]);
        parent[i] = -1;
        left[i] = -1;
        right[i] = -1;
    }

    /* Build Huffman Tree using array indices up to 2*n - 1 */
    int total_nodes = n;
    for (int step = 0; step < n - 1; step++) {
        int min1 = -1, min2 = -1;

        /* Find two nodes without parents that have the smallest frequencies */
        for (int i = 0; i < total_nodes; i++) {
            if (parent[i] == -1) {
                if (min1 == -1 || freq[i] < freq[min1]) {
                    min2 = min1;
                    min1 = i;
                } else if (min2 == -1 || freq[i] < freq[min2]) {
                    min2 = i;
                }
            }
        }

        /* Combine the two smallest nodes into a new parent node */
        int new_node = total_nodes;
        freq[new_node] = freq[min1] + freq[min2];
        parent[min1] = new_node;
        parent[min2] = new_node;
        left[new_node] = min1;
        right[new_node] = min2;
        parent[new_node] = -1;
        total_nodes++;
    }

    /* Find code length for each original symbol by walking up to root */
    int len[100];
    for (int i = 0; i < n; i++) {
        int count = 0;
        int curr = i;
        while (parent[curr] != -1) {
            count++;
            curr = parent[curr];
        }
        len[i] = (count == 0) ? 1 : count;
    }

    /* Sort symbols:
       1. Primary: Bit length ascending
       2. Secondary: Lexicographical character ascending */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (len[j] > len[j + 1] ||
               (len[j] == len[j + 1] && symbol[j] > symbol[j + 1])) {

                int temp_len = len[j];
                len[j] = len[j + 1];
                len[j + 1] = temp_len;

                char temp_sym = symbol[j];
                symbol[j] = symbol[j + 1];
                symbol[j + 1] = temp_sym;
            }
        }
    }

    /* Generate and display Canonical Huffman Codes */
    printf("\n--- Canonical Huffman Codebook ---\n");
    printf("%-8s %-12s %-16s\n", "Symbol", "Bit Length", "Canonical Code");
    printf("----------------------------------------\n");

    unsigned int code = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            code = (code + 1) << (len[i] - len[i - 1]);
        }

        /* Convert code integer to binary string directly */
        char code_str[33];
        code_str[len[i]] = '\0';
        unsigned int temp = code;
        for (int b = len[i] - 1; b >= 0; b--) {
            code_str[b] = (temp & 1) ? '1' : '0';
            temp >>= 1;
        }

        printf("%-8c %-12d %-16s\n", symbol[i], len[i], code_str);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Checks if two words differ by exactly 1 character (Hamming distance == 1)
int is_neighbor(char word1[], char word2[], int len) {
    int diff_count = 0;
    for (int i = 0; i < len; i++) {
        if (word1[i] != word2[i]) {
            diff_count++;
            if (diff_count > 1) return 0;
        }
    }
    return diff_count == 1;
}

int main() {
    int n, L;
    printf("Enter number of dictionary words (N) and word length (L): ");
    if (scanf("%d %d", &n, &L) != 2) return 0;

    char start_word[L + 1];
    char target_word[L + 1];

    printf("Enter starting word A: ");
    scanf("%s", start_word);

    printf("Enter target word B: ");
    scanf("%s", target_word);

    // If source and target are already identical
    if (strcmp(start_word, target_word) == 0) {
        printf("\nMinimum mutations required: 0\n");
        return 0;
    }

    // Allocate word storage to accommodate dictionary words plus start word
    int total_words = n + 2;
    char words[total_words][L + 1];

    printf("Enter %d dictionary words:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    // Check if target word exists in the dictionary
    int target_idx = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(words[i], target_word) == 0) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) {
        printf("\nTarget word B is not present in dictionary D.\n");
        printf("Minimum mutations required: -1\n");
        return 0;
    }

    // Check if start word exists in dictionary; if not, add it at index n
    int start_idx = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(words[i], start_word) == 0) {
            start_idx = i;
            break;
        }
    }

    int word_count = n;
    if (start_idx == -1) {
        start_idx = word_count;
        strcpy(words[start_idx], start_word);
        word_count++;
    }

    // Forward and Backward BFS distance trackers
    int dist_fwd[word_count];
    int dist_bwd[word_count];
    for (int i = 0; i < word_count; i++) {
        dist_fwd[i] = -1;
        dist_bwd[i] = -1;
    }

    // Forward Queue
    int q_fwd[word_count];
    int front_fwd = 0, rear_fwd = 0;

    // Backward Queue
    int q_bwd[word_count];
    int front_bwd = 0, rear_bwd = 0;

    // Initialize searches
    dist_fwd[start_idx] = 0;
    q_fwd[rear_fwd++] = start_idx;

    dist_bwd[target_idx] = 0;
    q_bwd[rear_bwd++] = target_idx;

    int min_mutations = -1;

    // Bidirectional BFS Loop: expand alternatingly
    while (front_fwd < rear_fwd && front_bwd < rear_bwd) {
        // Expand smaller frontier to keep search space optimal
        if ((rear_fwd - front_fwd) <= (rear_bwd - front_bwd)) {
            int level_size = rear_fwd - front_fwd;
            for (int s = 0; s < level_size; s++) {
                int u = q_fwd[front_fwd++];

                for (int v = 0; v < word_count; v++) {
                    if (is_neighbor(words[u], words[v], L)) {
                        // Check if backward search has visited this node
                        if (dist_bwd[v] != -1) {
                            min_mutations = dist_fwd[u] + 1 + dist_bwd[v];
                            goto SEARCH_COMPLETE;
                        }

                        if (dist_fwd[v] == -1) {
                            dist_fwd[v] = dist_fwd[u] + 1;
                            q_fwd[rear_fwd++] = v;
                        }
                    }
                }
            }
        } else {
            int level_size = rear_bwd - front_bwd;
            for (int s = 0; s < level_size; s++) {
                int u = q_bwd[front_bwd++];

                for (int v = 0; v < word_count; v++) {
                    if (is_neighbor(words[u], words[v], L)) {
                        // Check if forward search has visited this node
                        if (dist_fwd[v] != -1) {
                            min_mutations = dist_bwd[u] + 1 + dist_fwd[v];
                            goto SEARCH_COMPLETE;
                        }

                        if (dist_bwd[v] == -1) {
                            dist_bwd[v] = dist_bwd[u] + 1;
                            q_bwd[rear_bwd++] = v;
                        }
                    }
                }
            }
        }
    }

SEARCH_COMPLETE:
    printf("\n--- Result ---\n");
    if (min_mutations != -1) {
        printf("Shortest transformation sequence length (mutations k): %d\n", min_mutations);
    } else {
        printf("No valid transformation sequence exists (-1).\n");
    }

    return 0;
}

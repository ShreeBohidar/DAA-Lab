#include <stdio.h>
#include <string.h>

/* Compute maximum suffix-to-prefix overlap between string a and string b */
int compute_overlap(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_ov = (len_a < len_b) ? len_a : len_b;

    /* Start checking from maximum possible overlap down to 1 */
    for (int k = max_ov; k >= 1; k--) {
        int match = 1;
        for (int i = 0; i < k; i++) {
            if (a[len_a - k + i] != b[i]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return k;
        }
    }
    return 0;
}

int main() {
    int n;
    printf("Enter number of strings (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of strings.\n");
        return 0;
    }

    char str[50][1000];
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str[i]);
    }

    /* Step 1: Filter out strings that are already substrings of others */
    int active[50];
    for (int i = 0; i < n; i++) active[i] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && active[i] && active[j]) {
                if (strstr(str[j], str[i]) != NULL) {
                    active[i] = 0; /* str[i] is completely subsumed by str[j] */
                    break;
                }
            }
        }
    }

    /* Compact into a clean working array */
    char S[50][1000];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (active[i]) {
            strcpy(S[count++], str[i]);
        }
    }

    printf("\n--- Greedy Superstring Merge Iterations ---\n");
    int step = 1;

    /* Step 2: Repeatedly merge the pair with the maximum overlap */
    while (count > 1) {
        int best_i = -1, best_j = -1;
        int max_ov = -1;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (i != j) {
                    int ov = compute_overlap(S[i], S[j]);
                    if (ov > max_ov) {
                        max_ov = ov;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }

        /* Merge S[best_i] and S[best_j] into merged_str */
        char merged_str[2000];
        strcpy(merged_str, S[best_i]);
        strcat(merged_str, S[best_j] + max_ov);

        printf("Step %d: Merged \"%s\" + \"%s\" with overlap %d -> \"%s\"\n",
               step++, S[best_i], S[best_j], max_ov, merged_str);

        /* Replace S[best_i] with merged_str */
        strcpy(S[best_i], merged_str);

        /* Remove S[best_j] by shifting elements left */
        for (int k = best_j; k < count - 1; k++) {
            strcpy(S[k], S[k + 1]);
        }
        count--;
    }

    printf("\nFinal Resulting Greedy Superstring: %s\n", S[0]);
    printf("Length of Greedy Superstring: %lu\n", (unsigned long)strlen(S[0]));

    return 0;
}

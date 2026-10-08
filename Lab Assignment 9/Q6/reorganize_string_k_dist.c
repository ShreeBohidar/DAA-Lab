#include <stdio.h>
#include <string.h>

int main() {
    char s[200];
    int K;

    printf("Enter the string: ");
    if (scanf("%s", s) != 1) {
        printf("Invalid string input.\n");
        return 0;
    }

    printf("Enter distance K: ");
    if (scanf("%d", &K) != 1 || K < 0) {
        printf("Invalid distance K.\n");
        return 0;
    }

    int n = strlen(s);

    /* If K is 0 or 1, no rearrangement distance constraint is needed */
    if (K <= 1) {
        printf("\nReorganized String: %s\n", s);
        return 0;
    }

    /* Count frequency of each ASCII character */
    int freq[256] = {0};
    int last_pos[256];
    for (int i = 0; i < 256; i++) {
        last_pos[i] = -100000; /* Initialize with a far negative index */
    }

    for (int i = 0; i < n; i++) {
        freq[(unsigned char)s[i]]++;
    }

    char result[200];

    /* Greedily construct the string character by character */
    for (int pos = 0; pos < n; pos++) {
        int best_char = -1;
        int max_freq = 0;

        /* Find eligible character with maximum remaining frequency */
        for (int c = 0; c < 256; c++) {
            if (freq[c] > 0 && (pos - last_pos[c]) >= K) {
                if (freq[c] > max_freq) {
                    max_freq = freq[c];
                    best_char = c;
                }
            }
        }

        /* If no character is eligible to place at this index, rearrangement is impossible */
        if (best_char == -1) {
            printf("\nRearrangement impossible: \"\"\n");
            return 0;
        }

        /* Place character and update records */
        result[pos] = (char)best_char;
        freq[best_char]--;
        last_pos[best_char] = pos;
    }

    result[n] = '\0';

    printf("\nReorganized String (K = %d apart): %s\n", K, result);

    return 0;
}

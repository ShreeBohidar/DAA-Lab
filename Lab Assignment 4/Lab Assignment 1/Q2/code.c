/*
 * DAA Lab-01, Q2: Fair vs Biased coin
 * ------------------------------------
 * Approach:
 *   - Model a coin toss as: generate a random double r in [0,1).
 *     If r < p, call it HEAD, else TAIL. p = 0.5 gives a fair coin.
 *   - Run N trials, count heads, divide by N -> empirical P(HEAD).
 *   - By the Law of Large Numbers, as N grows this converges to p.
 *   - We sweep N across increasing powers of 10 to SHOW the
 *     convergence (small N is noisy, large N is close to p).
 *   - Then repeat with a biased coin (p != 0.5) for comparison.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// simulate n tosses of a coin with P(HEAD) = p, return fraction of heads
double simulate_coin(long n, double p) {
    long heads = 0;
    for (long i = 0; i < n; i++) {
        double r = (double)rand() / ((double)RAND_MAX + 1.0);
        if (r < p) heads++;
    }
    return (double)heads / (double)n;
}

int main(void) {
    srand((unsigned)time(NULL));

    long trial_sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    int num_trials = sizeof(trial_sizes) / sizeof(trial_sizes[0]);

    printf("=== Fair coin (p = 0.5) ===\n");
    printf("%-12s %-15s\n", "N (tosses)", "P(HEAD) observed");
    for (int i = 0; i < num_trials; i++) {
        double frac = simulate_coin(trial_sizes[i], 0.5);
        printf("%-12ld %-15.5f\n", trial_sizes[i], frac);
    }

    printf("\n=== Biased coin (p = 0.7) ===\n");
    printf("%-12s %-15s\n", "N (tosses)", "P(HEAD) observed");
    for (int i = 0; i < num_trials; i++) {
        double frac = simulate_coin(trial_sizes[i], 0.7);
        printf("%-12ld %-15.5f\n", trial_sizes[i], frac);
    }

    printf("\n=== Side-by-side comparison at N = 1,000,000 ===\n");
    double fair_p[] = {0.5};
    double biased_ps[] = {0.2, 0.3, 0.5, 0.7, 0.9};
    printf("%-10s %-15s\n", "True p", "Observed P(HEAD)");
    for (int i = 0; i < 5; i++) {
        double frac = simulate_coin(1000000, biased_ps[i]);
        printf("%-10.2f %-15.5f\n", biased_ps[i], frac);
    }

    printf("\nConclusion: the observed fraction of heads converges to the\n");
    printf("true probability p as N increases (Law of Large Numbers). The\n");
    printf("deviation |observed - p| shrinks roughly as O(1/sqrt(N)).\n");

    return 0;
}
/*
 * DAA Lab-01, Q1: Put them in Order
 * ----------------------------------
 * Goal: sort the 12 given functions by increasing order of growth
 * for sufficiently large n.
 *
 *
 *  n^(log2 n) and 3^n still become astronomically large for big n
 * (n^(log2 n) overflows a double past roughly n > 1500). The standard
 * technique to compare such huge quantities safely is to compare their
 * LOGARITHMS instead of the raw values, since log is a monotonically
 * increasing function -> log2(f(n)) < log2(g(n))  <=>  f(n) < g(n).
 *
 * So for every function f(n) we derive a closed form for log2(f(n))
 * analytically, then just sort those log2-values. This avoids overflow
 * completely and is the "right" way to reason about growth rates anyway.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_FUNCS 12

typedef struct {
    char name[32];
    double log2_value; // log base 2 of f(n), evaluated at some large n
} FuncEntry;

// log2(f(n)) for each function, given n and log2(n) precomputed
double log2_nlogn(double n, double log2n)      { return log2n + log2(log2n); }              // n log2 n
double log2_twelve_sqrt(double n, double log2n){ return log2(12.0) + 0.5 * log2n; }          // 12*sqrt(n)
double log2_inv_n(double n, double log2n)      { return -log2n; }                            // 1/n
double log2_n_pow_log2n(double n, double log2n){ return log2n * log2n; }                      // n^(log2 n)
double log2_quad_100(double n, double log2n)   { return log2(100.0*n*n + 6.0*n); }            // 100n^2+6n
double log2_n_051(double n, double log2n)      { return 0.51 * log2n; }                       // n^0.51
double log2_n2_minus(double n, double log2n)   { return log2(n*n - 324.0); }                  // n^2-324
double log2_fifty_sqrt(double n, double log2n) { return log2(50.0) + 0.5 * log2n; }           // 50*n^0.5
double log2_two_ncube(double n, double log2n)  { return 1.0 + 3.0 * log2n; }                  // 2n^3
double log2_three_pow_n(double n, double log2n){ return n * log2(3.0); }                      // 3^n
double log2_two32_times_n(double n, double log2n){ return 32.0 + log2n; }                     // 2^32 * n
double log2_log2n(double n, double log2n)      { return log2(log2n); }                        // log2 n

int cmp(const void *a, const void *b) {
    const FuncEntry *fa = (const FuncEntry *)a, *fb = (const FuncEntry *)b;
    if (fa->log2_value < fb->log2_value) return -1;
    if (fa->log2_value > fb->log2_value) return 1;
    return 0;
}

int main(void) {
    double n = 1e6;           // "sufficiently large n"
    double log2n = log2(n);

    FuncEntry funcs[NUM_FUNCS] = {
        {"n log2 n",        log2_nlogn(n, log2n)},
        {"12*sqrt(n)",      log2_twelve_sqrt(n, log2n)},
        {"1/n",             log2_inv_n(n, log2n)},
        {"n^(log2 n)",      log2_n_pow_log2n(n, log2n)},
        {"100n^2 + 6n",     log2_quad_100(n, log2n)},
        {"n^0.51",          log2_n_051(n, log2n)},
        {"n^2 - 324",       log2_n2_minus(n, log2n)},
        {"50*sqrt(n)",      log2_fifty_sqrt(n, log2n)},
        {"2n^3",            log2_two_ncube(n, log2n)},
        {"3^n",             log2_three_pow_n(n, log2n)},
        {"2^32 * n",        log2_two32_times_n(n, log2n)},
        {"log2 n",          log2_log2n(n, log2n)},
    };

    qsort(funcs, NUM_FUNCS, sizeof(FuncEntry), cmp);

    printf("Functions ranked by INCREASING order of growth (evaluated conceptually at n = %.0f)\n", n);
    printf("Comparison done via log2(f(n)) to avoid overflow for huge terms.\n\n");
    printf("%-4s %-16s %-15s\n", "Rank", "Function", "log2(f(n))");
    printf("-----------------------------------------\n");
    for (int i = 0; i < NUM_FUNCS; i++) {
        printf("%-4d %-16s %-15.4f\n", i + 1, funcs[i].name, funcs[i].log2_value);
    }

    FILE *fp = fopen("growth_order_data.csv", "w");
    if (fp) {
        fprintf(fp, "rank,function,log2_value\n");
        for (int i = 0; i < NUM_FUNCS; i++) {
            fprintf(fp, "%d,%s,%.4f\n", i + 1, funcs[i].name, funcs[i].log2_value);
        }
        fclose(fp);
        printf("\nData written to growth_order_data.csv\n");
    }

    return 0;
}

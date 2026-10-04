#include <stdio.h>
#include <stdlib.h>

// Structure to hold trajectory analysis metrics
typedef struct {
    unsigned long long start_val;
    int total_stopping_time;
    unsigned long long peak_val;
} CollatzMetrics;

// Computes the trajectory of a given integer n
CollatzMetrics computeTrajectory(unsigned long long n, int print_path) {
    CollatzMetrics metric;
    metric.start_val = n;
    metric.total_stopping_time = 0;
    metric.peak_val = n;

    unsigned long long curr = n;
    if (print_path) {
        printf("Trajectory for %llu:\n%llu", n, curr);
    }

    while (curr != 1) {
        if (curr % 2 == 0) {
            curr = curr / 2;
        } else {
            curr = 3 * curr + 1;
        }

        if (curr > metric.peak_val) {
            metric.peak_val = curr;
        }

        metric.total_stopping_time++;

        if (print_path) {
            printf(" -> %llu", curr);
        }
    }

    if (print_path) {
        printf("\n");
    }

    return metric;
}

// Analyzes the Collatz trajectories over a closed interval [a, b]
void analyzeInterval(unsigned long long a, unsigned long long b) {
    unsigned long long max_steps_num = a;
    int max_steps = 0;
    unsigned long long highest_peak_num = a;
    unsigned long long highest_peak = 0;

    printf("\n--- Interval Analysis [%llu, %llu] ---\n", a, b);
    printf("%-12s %-20s %-20s\n", "Number", "Total Steps", "Peak Value");

    for (unsigned long long i = a; i <= b; i++) {
        CollatzMetrics m = computeTrajectory(i, 0);
        printf("%-12llu %-20d %-20llu\n", m.start_val, m.total_stopping_time, m.peak_val);

        if (m.total_stopping_time > max_steps) {
            max_steps = m.total_stopping_time;
            max_steps_num = i;
        }

        if (m.peak_val > highest_peak) {
            highest_peak = m.peak_val;
            highest_peak_num = i;
        }
    }

    printf("\nSummary for range [%llu, %llu]:\n", a, b);
    printf("Number with maximum steps: %llu (%d steps)\n", max_steps_num, max_steps);
    printf("Number with highest peak:  %llu (Peak reached: %llu)\n", highest_peak_num, highest_peak);
}

int main() {
    int choice;
    printf("Collatz Conjecture Analysis\n");
    printf("1. Single Number Trajectory\n");
    printf("2. Interval Analysis [a, b]\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (choice == 1) {
        unsigned long long n;
        printf("Enter a positive integer (n >= 1): ");
        if (scanf("%llu", &n) != 1 || n < 1) {
            printf("Value must be a positive integer.\n");
            return 1;
        }

        CollatzMetrics m = computeTrajectory(n, 1);
        printf("\nTotal Stopping Time (Steps): %d\n", m.total_stopping_time);
        printf("Peak Value: %llu\n", m.peak_val);
    } else if (choice == 2) {
        unsigned long long a, b;
        printf("Enter start of interval (a >= 1): ");
        scanf("%llu", &a);
        printf("Enter end of interval (b >= a): ");
        scanf("%llu", &b);

        if (a < 1 || b < a) {
            printf("Invalid interval parameters.\n");
            return 1;
        }

        analyzeInterval(a, b);
    } else {
        printf("Invalid selection.\n");
    }

    return 0;
}
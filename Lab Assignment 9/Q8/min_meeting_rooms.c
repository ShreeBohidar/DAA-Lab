#include <stdio.h>

/* Simple bubble sort */
void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of meetings (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of meetings.\n");
        return 0;
    }

    int start[100];
    int end[100];

    printf("Enter start and end times for %d meetings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    /* Sort start and end arrays independently */
    sort_array(start, n);
    sort_array(end, n);

    int s_ptr = 0;
    int e_ptr = 0;
    int current_rooms = 0;
    int max_rooms = 0;

    printf("\n--- Timeline Simulation ---\n");

    /* Chronological sweep over start and end events */
    while (s_ptr < n) {
        if (start[s_ptr] < end[e_ptr]) {
            current_rooms++;
            if (current_rooms > max_rooms) {
                max_rooms = current_rooms;
            }
            printf("Time %d: Meeting starts -> Active rooms: %d (Max: %d)\n",
                   start[s_ptr], current_rooms, max_rooms);
            s_ptr++;
        } else {
            current_rooms--;
            printf("Time %d: Meeting ends   -> Active rooms: %d\n",
                   end[e_ptr], current_rooms);
            e_ptr++;
        }
    }

    printf("\nMinimum number of conference rooms required: %d\n", max_rooms);

    return 0;
}

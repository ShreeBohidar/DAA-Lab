#include <stdio.h>
#include <stdlib.h>

// Node for Singly Linked List
typedef struct SinglyNode {
    int data;
    struct SinglyNode* next;
} SinglyNode;

// Node for Doubly Linked List
typedef struct DoublyNode {
    int data;
    struct DoublyNode* prev;
    struct DoublyNode* next;
} DoublyNode;

// Helper print functions
void print_array(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void print_singly(SinglyNode* head) {
    printf("[ ");
    SinglyNode* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

void print_doubly(DoublyNode* head) {
    printf("[ ");
    DoublyNode* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

void display_all(int unsorted_arr[], int size_u, int sorted_arr[], int size_s,
                 SinglyNode* s_un, SinglyNode* s_so, DoublyNode* d_un, DoublyNode* d_so) {
    printf("\n--- CURRENT DATA STRUCTURE STATES ---\n");
    printf("1. Unsorted Array:        "); print_array(unsorted_arr, size_u);
    printf("2. Sorted Array:          "); print_array(sorted_arr, size_s);
    printf("3. Singly List Unsorted:  "); print_singly(s_un);
    printf("4. Singly List Sorted:    "); print_singly(s_so);
    printf("5. Doubly List Unsorted:  "); print_doubly(d_un);
    printf("6. Doubly List Sorted:    "); print_doubly(d_so);
    printf("-------------------------------------\n");
}

// 1. UNSORTED ARRAY OPERATIONS

int search_unsorted_array(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

void insert_unsorted_array(int arr[], int* size, int val) {
    arr[*size] = val;
    (*size)++;
}

void delete_unsorted_array(int arr[], int* size, int val) {
    int idx = search_unsorted_array(arr, *size, val);
    if (idx != -1) {
        arr[idx] = arr[*size - 1]; // Swap with last element
        (*size)--;
        printf("Deleted from Unsorted Array.\n");
    } else {
        printf("Not found in Unsorted Array.\n");
    }
}

// ---------------------------------------------------------
// 2. SORTED ARRAY OPERATIONS
// ---------------------------------------------------------
int search_sorted_array(int arr[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void insert_sorted_array(int arr[], int* size, int val) {
    int i = *size - 1;
    while (i >= 0 && arr[i] > val) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = val;
    (*size)++;
}

void delete_sorted_array(int arr[], int* size, int val) {
    int idx = search_sorted_array(arr, *size, val);
    if (idx != -1) {
        for (int i = idx; i < *size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*size)--;
        printf("Deleted from Sorted Array.\n");
    } else {
        printf("Not found in Sorted Array.\n");
    }
}

// 3. SINGLY LINKED LIST (UNSORTED) OPERATIONS

void insert_singly_unsorted(SinglyNode** head, int val) {
    SinglyNode* new_node = (SinglyNode*)malloc(sizeof(SinglyNode));
    new_node->data = val;
    new_node->next = *head;
    *head = new_node;
}

SinglyNode* search_singly(SinglyNode* head, int key) {
    SinglyNode* curr = head;
    while (curr != NULL) {
        if (curr->data == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

void delete_singly(SinglyNode** head, int val) {
    if (*head == NULL) return;
    if ((*head)->data == val) {
        SinglyNode* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Deleted from Singly Unsorted List.\n");
        return;
    }
    SinglyNode* curr = *head;
    while (curr->next != NULL && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next != NULL) {
        SinglyNode* temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        printf("Deleted from Singly Unsorted List.\n");
    } else {
        printf("Not found in Singly Unsorted List.\n");
    }
}

// 4. SINGLY LINKED LIST (SORTED) OPERATIONS

void insert_singly_sorted(SinglyNode** head, int val) {
    SinglyNode* new_node = (SinglyNode*)malloc(sizeof(SinglyNode));
    new_node->data = val;
    new_node->next = NULL;

    if (*head == NULL || (*head)->data >= val) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    SinglyNode* curr = *head;
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
}


// 5. DOUBLY LINKED LIST (UNSORTED) OPERATIONS

void insert_doubly_unsorted(DoublyNode** head, int val) {
    DoublyNode* new_node = (DoublyNode*)malloc(sizeof(DoublyNode));
    new_node->data = val;
    new_node->prev = NULL;
    new_node->next = *head;

    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

DoublyNode* search_doubly(DoublyNode* head, int key) {
    DoublyNode* curr = head;
    while (curr != NULL) {
        if (curr->data == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

void delete_doubly(DoublyNode** head, int val) {
    DoublyNode* target = search_doubly(*head, val);
    if (target == NULL) {
        printf("Not found in Doubly Unsorted List.\n");
        return;
    }
    if (*head == target) {
        *head = target->next;
    }
    if (target->next != NULL) {
        target->next->prev = target->prev;
    }
    if (target->prev != NULL) {
        target->prev->next = target->next;
    }
    free(target);
    printf("Deleted from Doubly Unsorted List.\n");
}

// 6. DOUBLY LINKED LIST (SORTED) OPERATIONS

void insert_doubly_sorted(DoublyNode** head, int val) {
    DoublyNode* new_node = (DoublyNode*)malloc(sizeof(DoublyNode));
    new_node->data = val;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }
    if ((*head)->data >= val) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
        return;
    }

    DoublyNode* curr = *head;
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    new_node->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = new_node;
    }
    curr->next = new_node;
}

// MAIN PROGRAM

int main() {
    int n, choice, val, k;

    printf("Enter initial size of dictionary (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    int* unsorted_arr = (int*)malloc((n + 100) * sizeof(int));
    int* sorted_arr = (int*)malloc((n + 100) * sizeof(int));
    int size_unsorted = n;
    int size_sorted = 0;

    SinglyNode* singly_unsorted = NULL;
    SinglyNode* singly_sorted = NULL;
    DoublyNode* doubly_unsorted = NULL;
    DoublyNode* doubly_sorted = NULL;

    printf("Enter %d space-separated elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        unsorted_arr[i] = val;

        insert_sorted_array(sorted_arr, &size_sorted, val);
        insert_singly_unsorted(&singly_unsorted, val);
        insert_singly_sorted(&singly_sorted, val);
        insert_doubly_unsorted(&doubly_unsorted, val);
        insert_doubly_sorted(&doubly_sorted, val);
    }

    // Display initial state of all 6 data structures
    display_all(unsorted_arr, size_unsorted, sorted_arr, size_sorted,
                singly_unsorted, singly_sorted, doubly_unsorted, doubly_sorted);

    while (1) {
        printf("\n------------------------------------------------\n");
        printf("DICTIONARY OPERATIONS MENU:\n");
        printf("1. Search Key (k)\n");
        printf("2. Insert Item (x)\n");
        printf("3. Delete Item (x)\n");
        printf("4. Find Min & Max\n");
        printf("5. Find Predecessor & Successor\n");
        printf("6. Exit\n");
        printf("Enter choice (1-6): ");
        scanf("%d", &choice);

        if (choice == 6) break;

        switch (choice) {
            case 1:
                printf("Enter search key k: ");
                scanf("%d", &k);

                printf("1. Unsorted Array Search:    Index %d\n", search_unsorted_array(unsorted_arr, size_unsorted, k));
                printf("2. Sorted Array Search:      Index %d\n", search_sorted_array(sorted_arr, size_sorted, k));
                printf("3. Singly Unsorted Search:   %s\n", search_singly(singly_unsorted, k) ? "Found" : "Not Found");
                printf("4. Singly Sorted Search:     %s\n", search_singly(singly_sorted, k) ? "Found" : "Not Found");
                printf("5. Doubly Unsorted Search:   %s\n", search_doubly(doubly_unsorted, k) ? "Found" : "Not Found");
                printf("6. Doubly Sorted Search:     %s\n", search_doubly(doubly_sorted, k) ? "Found" : "Not Found");
                break;

            case 2:
                printf("Enter element x to insert: ");
                scanf("%d", &val);

                insert_unsorted_array(unsorted_arr, &size_unsorted, val);
                insert_sorted_array(sorted_arr, &size_sorted, val);
                insert_singly_unsorted(&singly_unsorted, val);
                insert_singly_sorted(&singly_sorted, val);
                insert_doubly_unsorted(&doubly_unsorted, val);
                insert_doubly_sorted(&doubly_sorted, val);

                printf("Inserted %d into all 6 data structures.\n", val);
                display_all(unsorted_arr, size_unsorted, sorted_arr, size_sorted,
                            singly_unsorted, singly_sorted, doubly_unsorted, doubly_sorted);
                break;

            case 3:
                printf("Enter element x to delete: ");
                scanf("%d", &val);

                delete_unsorted_array(unsorted_arr, &size_unsorted, val);
                delete_sorted_array(sorted_arr, &size_sorted, val);
                delete_singly(&singly_unsorted, val);
                delete_singly(&singly_sorted, val);
                delete_doubly(&doubly_unsorted, val);
                delete_doubly(&doubly_sorted, val);

                display_all(unsorted_arr, size_unsorted, sorted_arr, size_sorted,
                            singly_unsorted, singly_sorted, doubly_unsorted, doubly_sorted);
                break;

            case 4:
                if (size_sorted == 0) {
                    printf("Dictionary is empty.\n");
                    break;
                }
                printf("\n--- MIN & MAX VALUES ---\n");
                printf("Minimum Value: %d\n", sorted_arr[0]);
                printf("Maximum Value: %d\n", sorted_arr[size_sorted - 1]);
                break;

            case 5:
                printf("Enter element x to find Predecessor/Successor: ");
                scanf("%d", &val);

                DoublyNode* ptr = search_doubly(doubly_sorted, val);
                if (ptr == NULL) {
                    printf("Element %d not found in dictionary.\n", val);
                } else {
                    if (ptr->prev != NULL) printf("Predecessor: %d\n", ptr->prev->data);
                    else printf("Predecessor: None (Smallest element)\n");

                    if (ptr->next != NULL) printf("Successor: %d\n", ptr->next->data);
                    else printf("Successor: None (Largest element)\n");
                }
                break;

            default:
                printf("Invalid choice! Enter 1-6.\n");
        }
    }

    free(unsorted_arr);
    free(sorted_arr);
    printf("Program finished.\n");
    return 0;
}
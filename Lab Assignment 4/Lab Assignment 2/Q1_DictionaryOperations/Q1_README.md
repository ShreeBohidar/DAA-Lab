# DAA Lab Assignment 2 - Question 1

## Overview
This project implements and analyzes a Dictionary Abstract Data Type (ADT) across six concrete data structures:
- Unsorted Array
- Sorted Array
- Singly Linked List (Unsorted)
- Singly Linked List (Sorted)
- Doubly Linked List (Unsorted)
- Doubly Linked List (Sorted)

The seven primary dictionary operations supported are Search, Insert, Delete, Minimum, Maximum, Predecessor, and Successor. All inputs ($N$, element array, search keys, insertion/deletion values) are provided manually by the user at runtime.



## Time Complexity Analysis

### 1. Unsorted Array
- **Search(D, k):** In the worst case, key $k$ is at index $N-1$ or not present. Checking every element sequentially requires $N$ comparisons, giving $O(N)$ time.
- **Insert(D, x):** Elements are unordered, so $x$ is placed directly at index $N$ in constant time $O(1)$.
- **Delete(D, x):** The target element is swapped with the last element at index $N-1$ and size is decremented by 1. This avoids element shifting and runs in $O(1)$ time.
- **Min / Max:** Finding the smallest or largest item requires scanning all $N$ elements, giving $O(N)$ time.
- **Predecessor / Successor:** Finding the adjacent element in sorted order requires checking all $N$ values, taking $O(N)$ time.

### 2. Sorted Array
- **Search(D, k):** Binary search cuts the search space in half at each comparison ($\frac{N}{2^k} = 1 \implies k = \log_2 N$), resulting in $O(\log N)$ time.
- **Insert(D, x):** Binary search locates the position in $O(\log N)$, but shifting remaining elements right to maintain sorted order takes up to $N$ operations, yielding $O(N)$ total time.
- **Delete(D, x):** Locating the item takes $O(\log N)$, but shifting elements left to close the gap requires $O(N)$ steps, giving $O(N)$ overall time.
- **Min / Max:** Minimum is at index $0$ and Maximum is at index $N-1$. Direct indexing takes $O(1)$ time.
- **Predecessor / Successor:** Given an index $i$, predecessor is at $i-1$ and successor is at $i+1$, taking $O(1)$ time.

### 3. Singly Linked List (Unsorted)
- **Search(D, k):** Must traverse sequentially from head to `NULL` checking each node, taking $O(N)$ worst-case time.
- **Insert(D, x):** Inserting at the head (`new_node->next = head`) updates pointers in $O(1)$ constant time.
- **Delete(D, x):** Requires traversing from head to locate the preceding node to update pointers, taking $O(N)$ time.
- **Min / Max:** Requires iterating through all $N$ nodes, taking $O(N)$ time.
- **Predecessor / Successor:** Requires full traversal of the list, taking $O(N)$ time.

### 4. Singly Linked List (Sorted)
- **Search(D, k):** Binary search cannot be used without random access indexing; linear traversal takes $O(N)$ time.
- **Insert(D, x):** Traversing to find the sorted insertion position takes $O(N)$ time, plus $O(1)$ pointer assignment, giving $O(N)$ total time.
- **Delete(D, x):** Finding the node takes $O(N)$ time, yielding $O(N)$ overall time.
- **Min / Max:** Minimum is at the head node in $O(1)$ time. Maximum is at the last node ($O(1)$ if tail pointer exists, $O(N)$ otherwise).
- **Predecessor / Successor:** Successor is `node->next` in $O(1)$ time. Predecessor requires searching from head to find the previous node in $O(N)$ time.

### 5. Doubly Linked List (Unsorted)
- **Search(D, k):** Linear traversal from head takes $O(N)$ time.
- **Insert(D, x):** Inserting at head updates `head`, `next`, and `prev` pointers in $O(1)$ time.
- **Delete(D, x):** Given a pointer to node $x$, updating `x->prev->next` and `x->next->prev` takes $O(1)$ constant time.
- **Min / Max:** Scanning all $N$ nodes takes $O(N)$ time.
- **Predecessor / Successor:** Full traversal required, taking $O(N)$ time.

### 6. Doubly Linked List (Sorted)
- **Search(D, k):** Sequential search takes $O(N)$ time.
- **Insert(D, x):** Finding the insertion point takes $O(N)$ time, plus $O(1)$ pointer linkage, giving $O(N)$ overall time.
- **Delete(D, x):** Pointer updates take $O(1)$ constant time.
- **Min / Max:** Minimum is at head ($O(1)$) and Maximum is at tail ($O(1)$).
- **Predecessor / Successor:** Predecessor is `node->prev` ($O(1)$) and Successor is `node->next` ($O(1)$).



## Worst-Case Complexity Table

| Operation | Unsorted Array | Sorted Array | Singly Unsorted | Singly Sorted | Doubly Unsorted | Doubly Sorted |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Search(D, k)** | $O(N)$ | $O(\log N)$ | $O(N)$ | $O(N)$ | $O(N)$ | $O(N)$ |
| **Insert(D, x)** | $O(1)$ | $O(N)$ | $O(1)$ | $O(N)$ | $O(1)$ | $O(N)$ |
| **Delete(D, x)** | $O(1)$ | $O(N)$ | $O(N)$ | $O(N)$ | $O(1)$ | $O(1)$ |
| **Max / Min** | $O(N)$ | $O(1)$ | $O(N)$ | $O(1)$ | $O(N)$ | $O(1)$ |
| **Predecessor** | $O(N)$ | $O(1)$ | $O(N)$ | $O(N)$ | $O(N)$ | $O(1)$ |
| **Successor** | $O(N)$ | $O(1)$ | $O(N)$ | $O(1)$ | $O(N)$ | $O(1)$ |



## Compilation and Execution

To compile the C program:
```bash
gcc dictionary_ops.c -o dictionary_ops.exe
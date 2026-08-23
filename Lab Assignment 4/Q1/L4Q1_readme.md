# DAA LAB ASSIGNMENT 4 - QUESTION 1
## COLOR SORT

---

### 1. Problem Statement
Assume that we are given n pairs of items as input, where the first item is a number and the second item is one of three colours (red, blue, or yellow). Further assume that the items are sorted by number. Give an O(n) algorithm to sort the items by colour (all reds before all blues before all yellows) such that the numbers for identical colours stay sorted[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read n elements, storing numbers in an integer array `num` and color strings in a 2D character array `col`.
2. Order Verification: Perform a linear scan from index `0` to `n-2` to verify that the array is already sorted numerically (num[i] <= num[i+1]).
3. Stable Partitioning:
   - Traverse the array from left to right and display all items with color "red".
   - Traverse the array from left to right and display all items with color "blue".
   - Traverse the array from left to right and display all items with color "yellow".
4. Because the original sequence is already sorted by numbers, printing each matching color from start to finish naturally preserves stability and sorted numerical order within each color block.

---

### 3. Pseudocode
```
Algorithm ColorSort(num, col, n):
    // 1. Validation Step
    for i = 0 to n - 2 do:
        if num[i] > num[i + 1] then:
            Print "Error: Input is not sorted by number."
            Return
        end if
    end for

    // 2. Multi-Pass Output
    // Pass 1: Red
    for i = 0 to n - 1 do:
        if col[i] == "red" then:
            Print (num[i], col[i])
        end if
    end for

    // Pass 2: Blue
    for i = 0 to n - 1 do:
        if col[i] == "blue" then:
            Print (num[i], col[i])
        end if
    end for

    // Pass 3: Yellow
    for i = 0 to n - 1 do:
        if col[i] == "yellow" then:
            Print (num[i], col[i])
        end if
    end for
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation:**
  The algorithm executes sequentially without divide-and-conquer recursion:
  $$T(n) = T_{validate}(n) + 3 \times T_{scan}(n) + c$$
  $$T(n) = (n - 1) + 3n + c = 4n + c' = \Theta(n)$$

* **Complexity Breakdown:**
  * **Best Case Time Complexity:** O(n)
  * **Average Case Time Complexity:** O(n)
  * **Worst Case Time Complexity:** O(n)
  
---


### 5. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o color_sort color_sort.c
```

**Execution Command:**
```bash
./color_sort
```

**Sample Output:**
```text
Enter number of items: 5
Enter 5 items as (number color):
10 blue
20 red
30 yellow
40 red
50 blue

Sorted output:
(20, red)
(40, red)
(10, blue)
(50, blue)
(30, yellow)
```
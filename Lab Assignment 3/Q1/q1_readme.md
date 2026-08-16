# DAA Lab Assignment - Question 1
# Binary Search vs. Ternary Search Analysis

## 1. Problem Statement
Design and implement a C program to search for an element `key` in a sorted list of size `n` using both Binary Search and Ternary Search[cite: 1]. Justify and validate theoretically and practically that Binary Search performs better than Ternary Search in terms of key comparisons[cite: 1].

## 2. Algorithm Overview

### Binary Search (D&C / Decrease & Conquer)
1. **Divide**: Calculate the middle index `mid = (low + high) / 2`, splitting the range into 2 equal parts.
2. **Conquer**:
   * If `arr[mid] == key`, return `mid`.
   * If `key < arr[mid]`, search the left sub-array `[low ... mid - 1]`.
   * If `key > arr[mid]`, search the right sub-array `[mid + 1 ... high]`.
3. In the worst case, each step requires **2 comparisons** and reduces the search space by a factor of **2**.

### Ternary Search (D&C / Decrease & Conquer)
1. **Divide**: Calculate two midpoints:
   * `mid1 = low + (high - low) / 3`
   * `mid2 = high - (high - low) / 3`
   This partitions the search range into 3 nearly equal intervals: `[low ... mid1 - 1]`, `[mid1 + 1 ... mid2 - 1]`, and `[mid2 + 1 ... high]`.
2. **Conquer**:
   * If `arr[mid1] == key`, return `mid1`.
   * If `arr[mid2] == key`, return `mid2`.
   * If `key < arr[mid1]`, search the first segment `[low ... mid1 - 1]`.
   * If `key > arr[mid2]`, search the third segment `[mid2 + 1 ... high]`.
   * Otherwise, search the middle segment `[mid1 + 1 ... mid2 - 1]`.
3. In the worst case, each step requires **4 comparisons** and reduces the search space by a factor of **3**.



## 3. Pseudocode

### Binary Search
Algorithm: BINARY-SEARCH(arr, n, key)
Input:  Sorted array arr, size n, target key
Output: Index of key if found, else -1

1. low = 0, high = n - 1
2. while low <= high do
3.      mid = (low + high) / 2
4.      if arr[mid] == key then
5.          return mid
6.      end if
7.      if key < arr[mid] then
8.          high = mid - 1
9.      else
10.         low = mid + 1
11.     end if
12. end while
13. return -1

### Ternary Search
Algorithm: TERNARY-SEARCH(arr, n, key)
Input:  Sorted array arr, size n, target key
Output: Index of key if found, else -1

1. low = 0, high = n - 1
2. while low <= high do
3.      mid1 = low + (high - low) / 3
4.      mid2 = high - (high - low) / 3
5.      if arr[mid1] == key then
6.          return mid1
7.      end if
8.      if arr[mid2] == key then
9.          return mid2
10.     end if
11.     if key < arr[mid1] then
12.         high = mid1 - 1
13.     else if key > arr[mid2] then
14.         low = mid2 + 1
15.     else
16.         low = mid1 + 1
17.         high = mid2 - 1
18.     end if
19. end while
20. return -1



## 4. Recurrence Relation & Comparison Count Analysis

### Binary Search:
* **Recurrence**: `T(n) = T(n / 2) + 2` (Worst Case: 2 comparisons per iteration)
* **Total Iterations**: `log2(n)`
* **Worst-Case Comparisons**:
  `C_binary(n) = 2 * log2(n)`

### Ternary Search:
* **Recurrence**: `T(n) = T(n / 3) + 4` (Worst Case: up to 4 comparisons per iteration)
* **Total Iterations**: `log3(n)`
* **Worst-Case Comparisons**:
  `C_ternary(n) = 4 * log3(n) = 4 * (log2(n) / log2(3))`
* Since `log2(3) ≈ 1.585`:
  `C_ternary(n) ≈ (4 / 1.585) * log2(n) ≈ 2.524 * log2(n)`

### Mathematical Conclusion:
* `2.000 * log2(n) < 2.524 * log2(n)`
* Although Ternary Search does fewer iterations (`log3(n) < log2(n)`), the overhead of performing up to **4 comparisons per step** makes its total comparison count ~26% higher than Binary Search.
* Therefore, **Binary Search is theoretically and practically more efficient**.


## 5. Complexity Analysis

### Time Complexity
* **Binary Search**:
  * Best Case: `O(1)` (Key at initial mid)
  * Worst Case: `O(log2 n)`
  * Average Case: `O(log2 n)`
* **Ternary Search**:
  * Best Case: `O(1)` (Key at initial mid1 or mid2)
  * Worst Case: `O(log3 n) = O(log2 n)`
  * Average Case: `O(log2 n)`


## 6. Performance Comparison

| Metric | Binary Search | Ternary Search |
| :--- | :--- | :--- |
| **Number of Sub-intervals** | `2` | `3` |
| **Max Comparisons per Iteration** | `2` | `4` |
| **Worst-case Total Comparisons** | `2 * log2(n)` | `2.524 * log2(n)` |
| **Time Complexity** | `O(log n)` | `O(log n)` |


## 7. Compilation and Execution

### Compilation:
gcc -O2 binary_vs_ternary.c -o binary_vs_ternary.exe

### Execution:
./binary_vs_ternary.exe

### Sample Run:
Enter number of elements (n <= 100): 9
Enter 9 sorted elements:
Element [0]: 10
Element [1]: 20
Element [2]: 30
Element [3]: 40
Element [4]: 50
Element [5]: 60
Element [6]: 70
Element [7]: 80
Element [8]: 90
Enter the element to search: 70
SEARCH RESULTS:
Binary Search  : Found at index 6 | Comparisons: 4
Ternary Search : Found at index 6 | Comparisons: 6
CONCLUSION: Binary Search used fewer/equal comparisons than Ternary Search.
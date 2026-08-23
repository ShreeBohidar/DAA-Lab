# DAA Lab Assignment 3 - Question 3
# Finding Maximum and Minimum using Divide and Conquer

## 1. Problem Statement
Given an array `A` of size `n`, find the maximum and minimum elements using the Divide and Conquer approach such that the total number of comparisons is bounded by `3n / 2`.



## 2. Algorithm Overview
The standard iterative scan checks elements one by one, requiring `2n - 2` comparisons. The Divide and Conquer approach reduces this to `(3n / 2) - 2` comparisons by dividing the problem into equal halves and solving small sub-problems directly:

1. **Divide**:
   * Calculate the middle index: `mid = (low + high) / 2`.
   * Split the array into two halves: `A[low ... mid]` and `A[mid + 1 ... high]`.

2. **Conquer (Base Cases)**:
   * **Single Element (`n = 1`)**: If `low == high`, the single element is both the minimum and the maximum (`0` comparisons).
   * **Two Elements (`n = 2`)**: If `high == low + 1`, compare both elements directly (`1` comparison). Assign the larger to `max` and the smaller to `min`.

3. **Combine**:
   * Recursively get the `(min, max)` pairs from both the left and right halves.
   * Compare the maximum of the left half with the maximum of the right half (`1` comparison).
   * Compare the minimum of the left half with the minimum of the right half (`1` comparison).
   * Return the overall minimum and maximum.



## 3. Pseudocode

Algorithm: FIND-MAX-MIN(A, low, high)
Input:  Array A, starting index low, ending index high
Output: Structure containing min and max

1. if low == high then
2.      return (min = A[low], max = A[low])
3. end if

4. if high == low + 1 then
5.      if A[low] > A[high] then
6.          return (min = A[high], max = A[low])
7.      else
8.          return (min = A[low], max = A[high])
9.      end if
10. end if

11. mid = (low + high) / 2
12. left_result  = FIND-MAX-MIN(A, low, mid)
13. right_result = FIND-MAX-MIN(A, mid + 1, high)

14. overall_max = max(left_result.max, right_result.max)
15. overall_min = min(left_result.min, right_result.min)

16. return (min = overall_min, max = overall_max)



## 4. Recurrence Relation & Comparison Count Analysis

Let `C(n)` represent the total number of element comparisons for an array of size `n`:

C(n) = 0                     if n = 1
C(n) = 1                     if n = 2
C(n) = 2 * C(n / 2) + 2      if n > 2

### Derivation (for n = 2^k):
Using the substitution method:
* `C(n) = 2 * C(n / 2) + 2`
* `C(n) = 2 * [2 * C(n / 4) + 2] + 2 = 4 * C(n / 4) + 4 + 2`
* `C(n) = 8 * C(n / 8) + 8 + 4 + 2`

Expanding up to `k - 1` steps:
* `C(n) = 2^(k - 1) * C(2) + (2^(k - 1) + ... + 4 + 2)`

Since `C(2) = 1` and the sum of the geometric progression is `2^k - 2`:
* `C(n) = 2^(k - 1) * (1) + (2^k - 2)`

Since `n = 2^k` and `2^(k - 1) = n / 2`:
* `C(n) = (n / 2) + n - 2`
* `C(n) = (3n / 2) - 2`

For any general `n >= 2`:
* `C(n) = ceil(3n / 2) - 2 <= 3n / 2`



## 5. Complexity Analysis

### Time Complexity
The recurrence relation for the total running time `T(n)` is:
* `T(n) = 2 * T(n / 2) + O(1)`

Using Master's Theorem:
* `a = 2, b = 2, f(n) = O(1)`
* `n^(log_b a) = n^(log_2 2) = n^1 = n`
* Since `f(n) = O(n^(1 - e))` where `e = 1`, Case 1 applies:
* **Time Complexity = O(n)**


## 6. Performance Comparison

| Metric | Standard Iterative Approach (Linear Scan) | Divide and Conquer Approach |
| :--- | :--- | :--- |
| **Best-case Comparisons** | `n - 1` | `(3n / 2) - 2` |
| **Worst-case Comparisons** | `2n - 2` | `(3n / 2) - 2` |
| **Average Comparisons** | `1.5n - 1.5` | `(3n / 2) - 2` |
| **Time Complexity** | `O(n)` | `O(n)` |



## 7. Compilation and Execution

### Compilation:
gcc -O2 max_min.c -o max_min.exe

### Execution:
./max_min.exe

### Sample Run:
Enter number of elements (n <= 100): 6
Enter 6 integers:
Element [0]: 34
Element [1]: 12
Element [2]: 89
Element [3]: 5
Element [4]: 70
Element [5]: 22


RESULTS:
Minimum Element          : 5
Maximum Element          : 89
Actual Comparisons Used  : 7
Theoretical Bound (3n/2): 9

VALIDATION SUCCESSFUL: Actual comparisons <= 3n/2
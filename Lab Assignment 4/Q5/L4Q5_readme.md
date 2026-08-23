# DAA LAB ASSIGNMENT 4 - QUESTION 5
## MERGED INTERVALS

---

### 1. Problem Statement
Given a list I of n intervals, specified as (x_i, y_i) pairs, return a list where the overlapping intervals are merged. For I = {(1, 3), (2, 6), (8, 10), (7, 18)} the output should be {(1, 6), (7, 18)}. Your algorithm should run in worst-case O(n log n) time complexity[cite: 1]. By choosing a suitable input and output representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read the number of intervals n and their start/end endpoints into parallel integer arrays `start` and `end`.
2. Sorting Phase: Apply Merge Sort on both arrays simultaneously using the starting endpoints `start[i]` as the primary sorting key in O(n log n) time.
3. Linear Merging Scan:
   - Initialize the first merged interval with the earliest interval: `res_start[0] = start[0]`, `res_end[0] = end[0]`.
   - Iterate through the remaining intervals from index 1 to n - 1.
   - If current interval's start point is less than or equal to the active merged interval's end point (`start[i] <= res_end[m]`), an overlap exists: update `res_end[m] = max(res_end[m], end[i])`.
   - If no overlap exists (`start[i] > res_end[m]`), advance the merged list index and insert the new interval.
4. Overall Complexity: Sorting takes O(n log n) and the linear scan takes O(n), giving an overall worst-case runtime of O(n log n).

---

### 3. Pseudocode
```text
Algorithm MergeSortIntervals(start, end, left, right):
    if left < right then:
        mid = left + (right - left) / 2
        MergeSortIntervals(start, end, left, mid)
        MergeSortIntervals(start, end, mid + 1, right)
        Merge(start, end, left, mid, right)
    end if

Algorithm MergeIntervals(start, end, n):
    // Step 1: Sort intervals by starting points
    MergeSortIntervals(start, end, 0, n - 1)

    // Step 2: Merge overlapping intervals
    m = 0
    res_start[0] = start[0]
    res_end[0] = end[0]

    for i = 1 to n - 1 do:
        if start[i] <= res_end[m] then:
            if end[i] > res_end[m] then:
                res_end[m] = end[i]
            end if
        else:
            m = m + 1
            res_start[m] = start[i]
            res_end[m] = end[i]
        end if
    end for

    // Step 3: Print result
    for i = 0 to m do:
        Print (res_start[i], res_end[i])
    end for
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation for Merge Sort:**
  $$T_{\text{sort}}(n) = 2T(n/2) + \Theta(n) \implies T_{\text{sort}}(n) = \Theta(n \log n)$$

* **Linear Merge Scan Complexity:**
  Traversing the sorted list of $n$ intervals involves exactly $(n - 1)$ constant-time comparisons:
  $$T_{\text{scan}}(n) = O(n)$$

* **Total Time Complexity:**
  $$T(n) = T_{\text{sort}}(n) + T_{\text{scan}}(n) = O(n \log n) + O(n) = O(n \log n)$$
  * **Best Case Time Complexity:** $O(n \log n)$
  * **Average Case Time Complexity:** $O(n \log n)$
  * **Worst Case Time Complexity:** $O(n \log n)$

---


### 5. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o merged_intervals merged_intervals.c
```

**Execution Command:**
```bash
./merged_intervals
```

**Sample Output:**
```text
Enter number of intervals (n): 4
Enter 4 intervals as (x_i y_i):
1 3
2 6
8 10
7 18

Merged Intervals:
(1, 6) (7, 18) 
```
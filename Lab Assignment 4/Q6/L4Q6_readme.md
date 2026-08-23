# DAA LAB ASSIGNMENT 4 - QUESTION 6
## MAX OVERLAP POINT

---

### 1. Problem Statement
You are given a set S of n intervals on a line, with the i-th interval described by its left and right endpoints (l_i, r_i). Give an O(n log n) algorithm to identify a point p on the line that is in the largest number of intervals. As an example, for S = {(10, 40), (20, 60), (50, 90), (15, 70)} no point exists in all four intervals, but p = 50 is an example of a point in three intervals[cite: 1]. You can assume an endpoint counts as being in its interval. By choosing a suitable input and output representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read n intervals. For each interval (l_i, r_i), generate two distinct events:
   - Start event at l_i with weight +1.
   - End event at r_i with weight -1.
   This produces an event array of size 2n.
2. Sorting Phase: Apply Merge Sort on the 2n events in O(n log n) time. In case of ties where a start point and end point share the exact same coordinate value, place the start event (+1) before the end event (-1) because endpoints are inclusive.
3. Sweep-Line Technique:
   - Traverse the sorted event list from index 0 to 2n - 1 while maintaining a running counter `current_overlap`.
   - Add the event weight to `current_overlap`.
   - Update `max_overlap` and record `best_point` whenever `current_overlap` reaches a new maximum.
4. Total Complexity: Sorting 2n events takes O(2n log(2n)) = O(n log n), and sweeping across the events takes O(n), producing an overall runtime of O(n log n).

---

### 3. Pseudocode
```text
Algorithm MergeSortEvents(val, type, left, right):
    if left < right then:
        mid = left + (right - left) / 2
        MergeSortEvents(val, type, left, mid)
        MergeSortEvents(val, type, mid + 1, right)
        MergeEvents(val, type, left, mid, right)
    end if

Algorithm FindMaxOverlapPoint(intervals, n):
    // Step 1: Create 2n event points
    for i = 0 to n - 1 do:
        val[2 * i] = intervals[i].left
        type[2 * i] = +1
        val[2 * i + 1] = intervals[i].right
        type[2 * i + 1] = -1
    end for

    // Step 2: Sort events by coordinate (tie-breaker: +1 before -1)
    MergeSortEvents(val, type, 0, 2 * n - 1)

    // Step 3: Sweep-line scan
    current_overlap = 0
    max_overlap = 0
    best_point = val[0]

    for i = 0 to 2 * n - 1 do:
        current_overlap = current_overlap + type[i]
        if current_overlap > max_overlap then:
            max_overlap = current_overlap
            best_point = val[i]
        end if
    end for

    Print best_point, max_overlap
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation for Merge Sort on $2n$ events:**
  $$T_{\text{sort}}(2n) = 2T(n) + \Theta(2n) \implies T_{\text{sort}}(2n) = \Theta(2n \log(2n)) = \Theta(n \log n)$$

* **Sweep-Line Scan Complexity:**
  Traversing the $2n$ sorted event endpoints involves $2n$ constant-time operations:
  $$T_{\text{scan}}(n) = O(2n) = O(n)$$

* **Total Time Complexity:**
  $$T(n) = T_{\text{sort}}(2n) + T_{\text{scan}}(n) = O(n \log n) + O(n) = O(n \log n)$$
  * **Best Case Time Complexity:** $O(n \log n)$
  * **Average Case Time Complexity:** $O(n \log n)$
  * **Worst Case Time Complexity:** $O(n \log n)$

---


### 5. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o max_overlap_point max_overlap_point.c
```

**Execution Command:**
```bash
./max_overlap_point
```

**Sample Output:**
```text
Enter number of intervals (n): 4
Enter 4 intervals as (l_i r_i):
10 40
20 60
50 90
15 70

Point in the largest number of intervals: 20
Number of intervals overlapping at this point: 3
```
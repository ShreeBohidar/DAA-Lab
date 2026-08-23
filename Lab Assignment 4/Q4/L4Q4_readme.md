# DAA LAB ASSIGNMENT 4 - QUESTION 4
## ENTRY EXIT (PEAK PARTY OCCUPANCY)

---

### 1. Problem Statement
A camera at the door tracks the entry time $a_i$ and exit time $b_i$ (assume $b_i > a_i$) for each of the $n$ persons $p_i$ attending a party. Give an $O(n \log n)$ algorithm that analyses this data to determine the time when the most people were simultaneously present at the party. Assume that all entry and exit times are distinct (no ties). By choosing the proper input representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read the number of persons $n$ and their respective entry times $a_i$ and exit times $b_i$ into two separate integer arrays `entry` and `exit_time`.
2. Sorting Phase:
   - Sort the `entry` array in ascending order using Merge Sort in $O(n \log n)$ time.
   - Sort the `exit_time` array in ascending order using Merge Sort in $O(n \log n)$ time.
3. Two-Pointer Sweep-Line Technique:
   - Maintain two pointers `i` (for `entry`) and `j` (for `exit_time`), along with counters `current_people` and `max_people`.
   - If `entry[i] < exit_time[j]`, a person arrives: increment `current_people`, update `max_people` and `peak_time` if a new maximum is reached, and advance `i`.
   - Else, a person leaves: decrement `current_people` and advance `j`.
4. Overall Complexity: Sorting takes $2 \times O(n \log n) = O(n \log n)$ and the two-pointer scan takes $O(n)$, giving an overall time complexity of $O(n \log n)$.

---

### 3. Pseudocode
```
Algorithm MergeSort(arr, left, right):
    if left < right then:
        mid = left + (right - left) / 2
        MergeSort(arr, left, mid)
        MergeSort(arr, mid + 1, right)
        Merge(arr, left, mid, right)
    end if

Algorithm FindPeakOccupancy(entry, exit_time, n):
    // Step 1: Sort both arrays
    MergeSort(entry, 0, n - 1)
    MergeSort(exit_time, 0, n - 1)

    // Step 2: Sweep-line scan
    i = 0, j = 0
    current_people = 0
    max_people = 0
    peak_time = entry[0]

    while i < n and j < n do:
        if entry[i] < exit_time[j] then:
            current_people = current_people + 1
            if current_people > max_people then:
                max_people = current_people
                peak_time = entry[i]
            end if
            i = i + 1
        else:
            current_people = current_people - 1
            j = j + 1
        end if
    end while

    Print max_people, peak_time
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation for Merge Sort:**
  $$T_{\text{sort}}(n) = 2T(n/2) + \Theta(n) \implies T_{\text{sort}}(n) = \Theta(n \log n)$$

* **Two-Pointer Scan Complexity:**
  Traversing both sorted lists advances pointer `i` at most $n$ times and pointer `j` at most $n$ times:
  $$T_{\text{scan}}(n) = O(2n) = O(n)$$

* **Total Time Complexity:**
  $$T(n) = 2 \times T_{\text{sort}}(n) + T_{\text{scan}}(n) = 2 \times O(n \log n) + O(n) = O(n \log n)$$
  * **Best Case Time Complexity:** $O(n \log n)$
  * **Average Case Time Complexity:** $O(n \log n)$
  * **Worst Case Time Complexity:** $O(n \log n)$

---

### 5. Performance Comparison Table

| Approach | Time Complexity | Strategy |
| :--- | :--- | :--- |
| **Brute Force (Interval Overlap Checks)** | $O(n^2)$ | Count active guests at every entry timestamp |
| **Sorted Two-Pointer Sweep (Our Method)** | $\mathbf{O(n \log n)}$ | Sort entry & exit events separately and scan in linear time |

---

### 6. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o entry_exit entry_exit.c
```

**Execution Command:**
```bash
./entry_exit
```

**Sample Output:**
```
Enter number of persons (n): 5
Enter entry (a_i) and exit (b_i) times for 5 persons:
1 4
2 5
10 12
5 9
3 8

Maximum people present simultaneously: 3
Time when peak occurred: 3
```
# DAA LAB ASSIGNMENT 4 - QUESTION 2
## PAIR SUM

---

### 1. Problem Statement
Given two sets S1 and S2 (each of size n), and a number x, describe an O(n log n) algorithm for finding whether there exists a pair of elements, one from S1 and one from S2, that add up to x. By choosing the proper input representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read the integer size n, the elements of sets S1 and S2 into static integer arrays, and the target sum x.
2. Sorting Phase: Apply Merge Sort on array S2 to arrange its elements in non-decreasing order in O(n log n) time.
3. Searching Phase (Binary Search):
   - For every element S1[i], calculate the needed complement: `complement = x - S1[i]`.
   - Perform a Binary Search for `complement` within the sorted array S2 in O(log n) time.
   - If found, record/print the matching pair (S1[i], complement).
4. Overall Complexity: Sorting takes O(n log n) and n individual binary searches take n * O(log n) = O(n log n), yielding a total time of O(n log n).

---

### 3. Pseudocode
```text
Algorithm MergeSort(arr, left, right):
    if left < right then:
        mid = left + (right - left) / 2
        MergeSort(arr, left, mid)
        MergeSort(arr, mid + 1, right)
        Merge(arr, left, mid, right)
    end if

Algorithm BinarySearch(arr, n, target):
    low = 0, high = n - 1
    while low <= high do:
        mid = low + (high - low) / 2
        if arr[mid] == target then:
            return true
        else if arr[mid] < target then:
            low = mid + 1
        else:
            high = mid - 1
        end if
    end while
    return false

Algorithm PairSum(S1, S2, n, x):
    // Step 1: Sort S2
    MergeSort(S2, 0, n - 1)

    // Step 2: Binary search complement for each element in S1
    count = 0
    for i = 0 to n - 1 do:
        complement = x - S1[i]
        if BinarySearch(S2, n, complement) == true then:
            Print S1[i], complement
            count = count + 1
        end if
    end for

    if count == 0 then:
        Print "No pair found"
    end if
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation for Merge Sort:**
  $$T_{\text{sort}}(n) = 2T(n/2) + \Theta(n)$$
  By Master Theorem (Case 2), $T_{\text{sort}}(n) = \Theta(n \log n)$.

* **Total Time Complexity:**
  $$T(n) = T_{\text{sort}}(n) + T_{\text{search}}(n) = O(n \log n) + O(n \log n) = O(n \log n)$$
  * **Best Case Time Complexity:** $O(n \log n)$
  * **Average Case Time Complexity:** $O(n \log n)$
  * **Worst Case Time Complexity:** $O(n \log n)$


---

### 5. Performance Comparison Table

| Approach | Time Complexity | Strategy |
| :--- | :--- | :--- |
| **Brute Force (Nested Loops)** | $O(n^2)$ | Check all pairs $(S_1[i], S_2[j])$ |
| **Merge Sort + Binary Search (Our Method)** | $\mathbf{O(n \log n)}$ | Deterministic sorting + binary search |

---

### 6. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o pair_sum pair_sum.c
```

**Execution Command:**
```bash
./pair_sum
```

**Sample Output:**
```text
Enter size n: 4
Enter 4 elements for S1: 1 4 5 7
Enter 4 elements for S2: 3 6 8 2
Enter target sum x: 9

Matching pairs:
1 (from S1) + 8 (from S2) = 9
7 (from S1) + 2 (from S2) = 9
Total pairs found: 2
```
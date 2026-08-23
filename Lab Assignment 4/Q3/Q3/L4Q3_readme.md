# DAA LAB ASSIGNMENT 4 - QUESTION 3
## K INTEGERS SUM UP TO GET TARGET T

---

### 1. Problem Statement
Given a set S of n integers and an integer T, give an O(n^(k-1) log n) algorithm to test whether k of the integers in S add up to T. By choosing the proper input representation, write a program in C to validate your algorithm.

---

### 2. Algorithm Overview
1. Input & Representation: Read n integers into an array S, along with parameters k and target integer T.
2. Sorting Step: Apply Merge Sort on array S to sort all elements in non-decreasing order in O(n log n) time.
3. Recursive Search & Binary Search:
   - Recursively select (k - 1) distinct elements from array S across (k - 1) nested decision levels.
   - For every combination of (k - 1) numbers chosen with sum `current_sum`, compute the required k-th complement: `complement = T - current_sum`.
   - Perform Binary Search in O(log n) over the remaining unsought section of the sorted array to verify whether `complement` exists.
4. Total Complexity: Generating all combinations of (k - 1) elements yields O(n^(k-1)) subsets, and each subset performs one binary search of O(log n), producing an overall runtime of O(n^(k-1) log n).

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

Algorithm BinarySearch(arr, low, high, target):
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

Algorithm FindKSum(S, n, k, current_k, start_idx, current_sum, T, chosen):
    // Base Case: (k - 1) elements selected
    if current_k == k - 1 then:
        complement = T - current_sum
        if BinarySearch(S, start_idx, n - 1, complement) == true then:
            Print chosen + complement
        end if
        return
    end if

    // Recursive Step: Select remaining elements
    for i = start_idx to n - (k - current_k) do:
        chosen[current_k] = S[i]
        FindKSum(S, n, k, current_k + 1, i + 1, current_sum + S[i], T, chosen)
    end for

Algorithm KSum(S, n, k, T):
    MergeSort(S, 0, n - 1)
    FindKSum(S, n, k, 0, 0, 0, T, empty_array)
```

---

### 4. Recurrence Relation & Time Complexity Analysis
* **Recurrence Relation for Merge Sort:**
  $$T_{\text{sort}}(n) = 2T(n/2) + \Theta(n) \implies T_{\text{sort}}(n) = \Theta(n \log n)$$

* **Recurrence Relation for Recursive Combination Generator:**
  Selecting $(k - 1)$ elements across recursive tree branches of depth $(k - 1)$:
  $$T(n, k - 1) = \sum_{i=1}^{n} T(n - i, k - 2)$$
  The total number of leaves (subsets of size $k-1$) is:
  $$\binom{n}{k-1} = \frac{n(n-1)\cdots(n-k+2)}{(k-1)!} = O(n^{k-1})$$

* **Search Step at Each Leaf:**
  Each leaf conducts one binary search on an array slice of size at most $n$:
  $$T_{\text{leaf}} = O(\log n)$$

* **Total Time Complexity:**
  $$T(n) = T_{\text{sort}}(n) + \left[ \binom{n}{k-1} \times O(\log n) \right]$$
  $$T(n) = O(n \log n) + O(n^{k-1} \log n) = O(n^{k-1} \log n)$$
  * **Best Case Time Complexity:** $O(n^{k-1} \log n)$
  * **Average Case Time Complexity:** $O(n^{k-1} \log n)$
  * **Worst Case Time Complexity:** $O(n^{k-1} \log n)$

---

### 5. Performance Comparison Table

| Approach | Time Complexity | Strategy |
| :--- | :--- | :--- |
| **Brute Force (All subsets of size $k$)** | $O(n^k)$ | Check all $\binom{n}{k}$ combinations with $k$ nested loops |
| **Recursive Sort + Binary Search (Our Method)** | $\mathbf{O(n^{k-1} \log n)}$ | Sort $S$, fix $(k-1)$ elements recursively, binary search last element |

---

### 6. Compilation, Execution & Sample Output

**Compilation Command:**
```bash
gcc -o k_sum_up_to_t k_sum_up_to_t.c
```

**Execution Command:**
```bash
./k_sum_up_to_t
```

**Sample Output:**
```text
Enter size of set S (n): 6
Enter 6 integers for S: 12 3 4 1 6 9
Enter value of k: 3
Enter target sum T: 24

Results:
Subset found: 3 + 9 + 12 = 24
Total matching subsets found: 1
```
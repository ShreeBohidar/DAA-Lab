# DAA Lab Assignment 3 - Question 6
# Use of Loop Invariants in Sorting (Selection Sort)

## 1. Problem Statement
Consider sorting $n$ numbers stored in an array $A[1 \dots n]$ by:
1. Finding the smallest element of $A[1 \dots n]$ and exchanging it with the element in $A[1]$.
2. Finding the smallest element of $A[2 \dots n]$ and exchanging it with $A[2]$.
3. Continuing in this manner for the first $(n - 1)$ elements of $A$.


## 2. Pseudocode
> **Question:** Write a pseudocode for this algorithm.

**Answer:**
```text
Algorithm: SELECTION-SORT(A, n)
Input:  Array A of n elements (0-indexed: A[0 ... n - 1])
Output: Array A sorted in non-decreasing order

1. for i = 0 to n - 2 do
2.      min_idx = i
3.      for j = i + 1 to n - 1 do
4.          if A[j] < A[min_idx] then
5.              min_idx = j
6.          end if
7.      end for
8.      if min_idx != i then
9.          temp = A[i]
10.         A[i] = A[min_idx]
11.         A[min_idx] = temp
12.     end if
13. end for
14. return A
```


## 3. Loop Invariant and Correctness Proof
> **Question:** What loop invariant does this algorithm maintain? Validate the proof by showing three things: Initialization, Maintenance, and Termination.

**Answer:**

### Formulation of the Loop Invariant:
At the start of each iteration `i` of the outer `for` loop (where `i = 0, 1, ..., n - 2`):
1. The sub-array `A[0 ... i - 1]` contains the `i` smallest elements of the original array in fully sorted order.
2. Every element in `A[0 ... i - 1]` is less than or equal to every element in the remaining sub-array `A[i ... n - 1]`.



### Proof of Correctness:

#### 1. Initialization (Prior to the First Iteration)
* Before the loop starts, `i = 0`.
* The sub-array `A[0 ... i - 1]` corresponds to `A[0 ... -1]`, which is empty ($0$ elements).
* An empty sub-array is vacuously sorted and trivially contains the $0$ smallest elements of the array.
* Hence, the loop invariant holds true prior to the first iteration.

#### 2. Maintenance (From One Iteration to the Next)
* Assume the invariant holds true at the beginning of iteration `i`.
* `A[0 ... i - 1]` contains the `i` smallest elements of the array in sorted order, and all elements in `A[i ... n - 1]` are greater than or equal to `A[i - 1]`.
* During iteration `i`, the inner loop scans `A[i ... n - 1]` from `j = i + 1` to `n - 1` and identifies the index `min_idx` of the minimum element in `A[i ... n - 1]`.
* The algorithm then swaps `A[i]` with `A[min_idx]`.
* Now, `A[i]` holds the smallest element among all elements in `A[i ... n - 1]`.
* Since all elements in `A[i ... n - 1]` were already $\ge$ all elements in `A[0 ... i - 1]`, placing this minimum at `A[i]` ensures:
  * `A[i - 1] <= A[i]`
  * `A[i] <= A[k]` for all $k \in [i + 1, n - 1]$
* Thus, the sub-array `A[0 ... i]` now contains the $(i + 1)$ smallest elements in sorted order.
* Incrementing `i` for the next iteration re-establishes the loop invariant.

#### 3. Termination (When the Loop Terminates)
* The loop terminates when the loop counter reaches `i = n - 1`.
* Applying `i = n - 1` to the invariant:
  * The sub-array `A[0 ... n - 2]` contains the $(n - 1)$ smallest elements of the entire array in sorted order.
  * Every element in `A[0 ... n - 2]` is $\le$ the single remaining element in `A[n - 1]`.
* By deduction, the remaining element `A[n - 1]` must be the largest element in the original array and is already in its correct final position.
* Therefore, the entire array `A[0 ... n - 1]` is completely sorted.



## 4. Reason for Running (n - 1) Elements Only
> **Question:** Why does it need to run for only the first $(n - 1)$ elements, rather than for all $n$ elements?

**Answer:**
1. After $(n - 1)$ iterations, the $(n - 1)$ smallest elements have already been selected and placed in positions `A[0 ... n - 2]` in sorted order.
2. By the Law of Total Elements, only $1$ element remains at index `n - 1`.
3. Because all other $(n - 1)$ elements in the array are less than or equal to `A[n - 1]`, this remaining element is guaranteed to be the maximum element and is already in its correct sorted position.
4. If an $n$-th iteration were executed (`i = n - 1`), the inner loop would look for elements from `j = n` to `n - 1` (an empty range), perform $0$ comparisons, and swap `A[n - 1]` with itself.
5. Therefore, running for $(n - 1)$ iterations is both mathematically sufficient and avoids redundant operations.



## 5. Worst-Case Running Time Analysis
> **Question:** Give the worst-case running time of the above sorting algorithm in $\Theta$-notation.

**Answer:**
In each pass `i`, the inner loop compares `A[min_idx]` against every element from `j = i + 1` to `n - 1`, performing exactly $(n - 1 - i)$ comparisons.

The total number of comparisons $C(n)$ across all iterations is:
$$C(n) = \sum_{i=0}^{n-2} (n - 1 - i) = (n - 1) + (n - 2) + \dots + 2 + 1$$
$$C(n) = \frac{n(n - 1)}{2} = \frac{n^2}{2} - \frac{n}{2}$$

* **Comparisons:** Always exactly $\frac{n(n - 1)}{2} = \Theta(n^2)$.
* **Swaps:** At most $(n - 1)$ swaps $= \Theta(n)$.
* **Total Running Time:** $T(n) = c_1 \cdot \frac{n(n - 1)}{2} + c_2 \cdot (n - 1) = \Theta(n^2)$.

**Worst-Case Running Time = $\Theta(n^2)$**



## 6. Best-Case Running Time Analysis
> **Question:** Is the best-case running time any better?

**Answer:**
**No, the best-case running time is not any better.**

* Even if the input array is already completely sorted (e.g., `[10, 20, 30, 40, 50]`), Selection Sort has no early-termination condition.
* To prove that `A[i]` is the minimum element in the remaining unsorted sub-array `A[i ... n - 1]`, the inner loop must still compare `A[i]` with every subsequent element `A[j]` for all $j \in [i + 1, n - 1]$.
* The number of key comparisons remains strictly identical:
$$C_{\text{best}}(n) = \frac{n(n - 1)}{2} = \Theta(n^2)$$
* The only difference in the best case is that the number of swaps is $0$ instead of $(n - 1)$. Since comparisons dominate the running time, the asymptotic time complexity remains unchanged.

**Best-Case Running Time = $\Theta(n^2)$**



## 7. Performance Summary Table

| Metric | Best Case | Average Case | Worst Case |
| :--- | :--- | :--- | :--- |
| **Comparisons** | $\frac{n(n - 1)}{2}$ | $\frac{n(n - 1)}{2}$ | $\frac{n(n - 1)}{2}$ |
| **Swaps** | $0$ | $O(n)$ | $n - 1$ |
| **Time Complexity** | $\Theta(n^2)$ | $\Theta(n^2)$ | $\Theta(n^2)$ |



## 8. Compilation, Execution, and Validation Trace

### Compilation:
```bash
gcc -O2 selection_sort.c -o selection_sort.exe
```

### Execution:
```bash
./selection_sort.exe
```

### Sample Terminal Output:
```text
Enter number of elements (n <= 100): 5
Enter 5 integers:
Element [0]: 64
Element [1]: 25
Element [2]: 12
Element [3]: 22
Element [4]: 11
After iteration 1 (Placing smallest at index 0): 11 25 12 22 64 
After iteration 2 (Placing smallest at index 1): 11 12 25 22 64 
After iteration 3 (Placing smallest at index 2): 11 12 22 25 64 
After iteration 4 (Placing smallest at index 3): 11 12 22 25 64 
SORTING RESULTS:
Sorted Array                       : 11 12 22 25 64 
Actual Comparisons Used            : 10
Theoretical Comparisons [n(n-1)/2] : 10
Total Swaps Performed              : 3
```
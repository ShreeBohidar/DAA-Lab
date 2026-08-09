# DAA Lab Assignment 2 - Question 3

## Overview
This code implements and compares two fundamental strategies for merging $k$ sorted arrays, each containing $n$ elements, into a single sorted array of size $k \cdot n$:
1. **Sequential Merge:** Successively merges arrays one by one into an accumulating result array.
2. **Pairwise Merge (Divide and Conquer):** Pairs up arrays and merges them in logarithmic stages using a tree structure.

All array parameters ($k$, $n$, and array elements) are provided via manual input or auto-generated.


## Fundamental Subroutine Analysis: Merging Two Sorted Arrays

Both merging strategies rely on the standard two-pointer merging technique, `merge_two(A, B)`, which combines two sorted arrays of sizes $L_1$ and $L_2$ into a sorted array of size $L_1 + L_2$.

- **Comparisons:** In the worst-case scenario (where elements from $A$ and $B$ alternate), the number of key comparisons required is:
  $$\text{Comparisons}_{\text{worst}} = L_1 + L_2 - 1$$
- **Element Moves:** Regardless of element distribution, every single element from both input arrays must be copied into the target array:
  $$\text{Element Moves} = L_1 + L_2$$

Since memory transfers and element moves dominate running time, the execution time for merging two sorted arrays of lengths $L_1$ and $L_2$ is strictly proportional to $L_1 + L_2$, yielding a worst-case time complexity of $\Theta(L_1 + L_2)$.



## Detailed Mathematical Time Complexity Analysis

Let $k$ be the number of arrays and $n$ be the size of each array. The total number of elements across all arrays is $N_{\text{total}} = k \cdot n$.

### 1. Sequential Merge Analysis

In Sequential Merge, we start with the first array of size $n$ and sequentially merge each subsequent array into our accumulating result array across $k-1$ iterations.

- **Iteration 1:** Merge Array 1 (size $n$) and Array 2 (size $n$).
  $$\text{Cost}_1 = n + n = 2n$$
- **Iteration 2:** Merge Intermediate Result (size $2n$) and Array 3 (size $n$).
  $$\text{Cost}_2 = 2n + n = 3n$$
- **Iteration 3:** Merge Intermediate Result (size $3n$) and Array 4 (size $n$).
  $$\text{Cost}_3 = 3n + n = 4n$$
- **Iteration $i$ (for $i = 1, 2, \dots, k-1$):** Merge Intermediate Result (size $i \cdot n$) and Array $i+1$ (size $n$).
  $$\text{Cost}_i = (i \cdot n) + n = (i + 1)n$$

To find the total operations $T(k, n)$ required across all $k-1$ iterations, we sum the costs:

$$T(k, n) = \sum_{i=1}^{k-1} (i + 1)n = n \sum_{i=1}^{k-1} (i + 1)$$

Changing the summation variable by letting $j = i + 1$:

$$T(k, n) = n \sum_{j=2}^{k} j$$

Using the standard summation identity $\sum_{j=1}^{k} j = \frac{k(k+1)}{2}$:

$$\sum_{j=2}^{k} j = \frac{k(k+1)}{2} - 1 = \frac{k^2 + k - 2}{2}$$

Substituting this back into $T(k, n)$ yields the exact total operation polynomial:

$$T(k, n) = n \left( \frac{k^2 + k - 2}{2} \right) = \frac{1}{2} n k^2 + \frac{1}{2} n k - n$$

#### Asymptotic Worst-Case Complexity
Focusing on the highest-order term as $k \to \infty$:

$$\text{Time Complexity} = O(k^2 \cdot n)$$

*Reason for efficiency loss:* Elements from the earliest arrays are repeatedly scanned and re-copied $k-1$ times, causing quadratic growth with respect to $k$.



### 2. Pairwise Merge Analysis (Divide & Conquer)

In Pairwise Merge, arrays are paired up and merged simultaneously in parallel rounds, forming a balanced binary tree of merge operations.

- **Tree Height / Total Rounds:** Since the number of arrays is halved at each level ($k \rightarrow k/2 \rightarrow k/4 \dots \rightarrow 1$), the total number of merge levels is:
  $$\text{Levels} = \lceil \log_2 k \rceil$$

- **Work Per Level:**
  - **Level 1:** Merge $\frac{k}{2}$ pairs of arrays (each of size $n$).
    $$\text{Work}_1 = \left( \frac{k}{2} \right) \times (n + n) = k \cdot n$$
  - **Level 2:** Merge $\frac{k}{4}$ pairs of arrays (each of size $2n$).
    $$\text{Work}_2 = \left( \frac{k}{4} \right) \times (2n + 2n) = k \cdot n$$
  - **Level $L$:** Merge $\frac{k}{2^L}$ pairs of arrays (each of size $2^{L-1}n$).
    $$\text{Work}_L = \left( \frac{k}{2^L} \right) \times \left( 2^{L-1}n + 2^{L-1}n \right) = k \cdot n$$

The work done at **every level** of the tree is constant and equals the total number of elements ($k \cdot n$).

Summing the work across all $\log_2 k$ levels:

$$T(k, n) = \sum_{L=1}^{\lceil \log_2 k \rceil} (k \cdot n) = (k \cdot n) \times \lceil \log_2 k \rceil$$

#### Asymptotic Worst-Case Complexity
$$T(k, n) = O(k \cdot n \log k)$$

*Reason for efficiency gain:* No single element is moved or copied more than $\log_2 k$ times (once per tree level), distributing the merge workload evenly.



## Direct Mathematical Comparison & Numerical Example

Expressed in terms of total elements $N_{\text{total}} = k \cdot n$:
- **Sequential Merge:** $T(k, n) = O(k \cdot N_{\text{total}})$
- **Pairwise Merge:** $T(k, n) = O(N_{\text{total}} \log k)$

### Concrete Case ($k = 100$ arrays, $n = 100$ elements each $\implies N_{\text{total}} = 10,000$):
1. **Sequential Merge:**
   $$T(100, 100) = \frac{100 \times (100^2 + 100 - 2)}{2} = 504,900 \text{ operations}$$
2. **Pairwise Merge:**
   $$T(100, 100) \approx 100 \times 100 \times \log_2(100) \approx 10,000 \times 6.64 = 66,438 \text{ operations}$$

Pairwise Merge performs approximately **7.6 times fewer operations** on this input size alone, and this gap expands quadratically as $k$ increases.



## Complexity Summary Matrix

| Method | Time Complexity | Space Complexity | Practical Impact |
| :--- | :---: | :---: | :--- |
| **Sequential Merge** | $O(k^2 \cdot n)$ | $O(k \cdot n)$ | Highly inefficient for large $k$ due to repeated re-copying of early elements. |
| **Pairwise Merge** | $O(k \cdot n \log k)$ | $O(k \cdot n)$ | Optimal divide-and-conquer strategy, maintaining scalable execution time. |



## Compilation and Execution

To compile the C program:
```bash
gcc merge_k_arrays.c -o merge_k_arrays.exe
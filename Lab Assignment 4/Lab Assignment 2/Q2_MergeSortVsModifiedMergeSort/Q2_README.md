# DAA Lab Assignment 2 - Question 2

## Overview
This code implements and analyzes two variations of the Divide and Conquer Merge Sort algorithm:
1. **Binary Merge Sort:** Standard approach that recursively divides an array into **2 equal halves**, sorts them, and merges them using 2-way comparison.
2. **Ternary Merge Sort:** Modified approach that recursively divides an array into **3 equal subparts**, sorts them, and merges them using 3-way comparison.

Both methods are implemented in C, handling both manual input and auto-generated data, followed by theoretical order-of-growth verification.

---

## Detailed Mathematical Time Complexity Analysis

Let $n$ be the total number of elements in the array to be sorted.

---

### 1. Binary Merge Sort Analysis

#### Recurrence Relation
In Binary Merge Sort, an array of size $n$ is split into 2 subarrays of size $n/2$. Merging two sorted subarrays of total size $n$ requires at most $n - 1$ comparisons in the worst case.

$$T(n) = 2 T\left(\frac{n}{2}\right) + \Theta(n)$$

#### Solving via the Master Theorem
For $T(n) = a T(n/b) + f(n)$:
- $a = 2$ (number of subproblems)
- $b = 2$ (division factor)
- $f(n) = \Theta(n) = \Theta(n^{\log_b a})$ where $\log_2 2 = 1$

By Case 2 of the Master Theorem:

$$T(n) = \Theta(n^{\log_2 2} \log n) = \Theta(n \log_2 n)$$

#### Exact Operations & Tree Depth
- **Recursion Tree Height:** $\log_2 n$
- **Work Per Level:** At most $n$ comparisons and $n$ element copies.
- **Total Worst-Case Comparisons:** 

$$C_{\text{binary}}(n) \approx n \log_2 n$$

---

### 2. Ternary Merge Sort Analysis

#### Recurrence Relation
In Ternary Merge Sort, an array of size $n$ is split into 3 subarrays of size $n/3$. Merging three sorted subarrays requires finding the minimum among 3 elements at each step, taking at most **2 comparisons per output element** in the worst case.

$$T(n) = 3 T\left(\frac{n}{3}\right) + \Theta(n)$$

#### Solving via the Master Theorem
For $T(n) = a T(n/b) + f(n)$:
- $a = 3$ (number of subproblems)
- $b = 3$ (division factor)
- $f(n) = \Theta(n) = \Theta(n^{\log_b a})$ where $\log_3 3 = 1$

By Case 2 of the Master Theorem:

$$T(n) = \Theta(n^{\log_3 3} \log n) = \Theta(n \log_3 n)$$

#### Exact Operations & Tree Depth
- **Recursion Tree Height:** $\log_3 n$
- **Comparisons Per Element during Merge:** To select the smallest element among 3 pointers, up to 2 comparisons are performed per element. Thus, merging 3 subarrays of total length $n$ requires up to $2n - 2$ comparisons.
- **Total Worst-Case Comparisons:**

$$C_{\text{ternary}}(n) \approx 2n \log_3 n$$

---

### 3. Theoretical Trade-off Comparison

We can express $\log_3 n$ in terms of $\log_2 n$ using the change-of-base formula:

$$\log_3 n = \frac{\log_2 n}{\log_2 3} \approx \frac{\log_2 n}{1.585} \approx 0.631 \log_2 n$$

Comparing the worst-case comparison counts:

$$C_{\text{binary}}(n) \approx 1.000 \cdot n \log_2 n$$

$$C_{\text{ternary}}(n) \approx 2 \cdot (0.631 \cdot n \log_2 n) \approx 1.262 \cdot n \log_2 n$$

#### Key Takeaways:
1. **Tree Depth:** Ternary Merge Sort reduces the recursion tree height by roughly **37%** ($\log_3 n$ vs $\log_2 n$), leading to fewer recursive function call frames.
2. **Comparison Overhead:** Ternary Merge Sort requires up to **26% more key comparisons** overall because each element merge requires comparing up to 3 values instead of 2.
3. **Asymptotic Complexity:** Both algorithms share the same asymptotic growth class of **$\Theta(n \log n)$**.

---

## Complexity Summary Matrix

| Metric | Binary Merge Sort | Ternary Merge Sort | Impact |
| :--- | :---: | :---: | :--- |
| **Recurrence Relation** | $2T(n/2) + \Theta(n)$ | $3T(n/3) + \Theta(n)$ | Subproblem division ratio |
| **Recursion Depth** | $\log_2 n$ | $\log_3 n$ | Ternary tree is ~37% shallower |
| **Max Comparisons / Step** | 1 comparison | 2 comparisons | Ternary has higher local overhead |
| **Worst-Case Operations** | $\approx n \log_2 n$ | $\approx 2n \log_3 n$ | Ternary performs ~26% more comparisons |
| **Overall Complexity** | $\Theta(n \log n)$ | $\Theta(n \log n)$ | Asymptotically equivalent |
| **Auxiliary Space** | $O(n)$ | $O(n)$ | Equal linear memory usage |

---

## Plot Analysis Explanation

The generated order-of-growth plot (`order_of_growth.png`) illustrates two key perspectives:
1. **Recursion Tree Depth:** Confirms that Ternary Merge Sort ($\log_3 n$) grows slower than Binary Merge Sort ($\log_2 n$) in terms of call stack levels.
2. **Total Worst-Case Comparisons:** Demonstrates that despite the shallower depth, Ternary Merge Sort requires slightly more total comparisons due to the 3-way merge logic.

---

## Compilation and Execution

To compile the C program:
```bash
gcc modified_merge_sort.c -o modified_merge_sort.exe
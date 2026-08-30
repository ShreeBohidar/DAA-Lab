# DAA Lab 5 - Question 1: Median Without Sorting

## Problem Statement
Find the median of a list of $N$ numbers without sorting the list, and perform the complexity analysis of the algorithm.


## Approach & Algorithm: QuickSelect
Instead of sorting the entire array in $\mathcal{O}(N \log N)$ time, the **QuickSelect** (Hoare's Selection) algorithm is used to find the target median element in expected linear time.

1. **Partitioning**: 
   - A pivot element is selected (the last element `arr[high]`).
   - The array is rearranged so that elements smaller than or equal to the pivot move to the left, and elements greater move to the right.
   - The pivot is placed at its final sorted position index `pi`.
2. **Selection**:
   - If `pi == k`, the element at `pi` is the $k$-th smallest element.
   - If `pi > k`, recurse only on the left partition: `low` to `pi - 1`.
   - If `pi < k`, recurse only on the right partition: `pi + 1` to `high`.
3. **Median Computation**:
   - **Odd $N$**: Find the element at index $k = \lfloor N / 2 \rfloor$.
   - **Even $N$**: Find elements at indices $(N/2) - 1$ and $N/2$, then calculate their average.



## Complexity Analysis

### Time Complexity
- **Best Case**: $\mathcal{O}(N)$ — Occurs when the pivot splits the array into balanced halves ($N + N/2 + N/4 + \dots \approx 2N$).
- **Average Case**: $\mathcal{O}(N)$ — Expected linear performance over random permutations.
- **Worst Case**: $\mathcal{O}(N^2)$ — Occurs when the pivot is consistently the maximum or minimum element (e.g., sorted array with last element as pivot).



## Sample Input & Output

### Case 1: Odd Number of Elements
```text
Enter number of elements: 5
Enter 5 elements: 12 3 5 7 19
Median: 7
```

### Case 2: Even Number of Elements
```text
Enter number of elements: 6
Enter 6 elements: 12 3 5 7 19 1
Median: 6.00
```


## Conclusion
The QuickSelect algorithm successfully avoids the overhead of complete array sorting ($\mathcal{O}(N \log N)$) by only partitioning the subarray containing the median index. This reduces the average time complexity to $\mathcal{O}(N)$, making it an optimal selection approach for finding order statistics in unsorted lists.

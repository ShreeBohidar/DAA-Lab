# DAA Lab 5 - Question 2: K-th Smallest Element Without Sorting

## Problem Statement
Find the $K$-th smallest element in a given list of $N$ numbers without sorting the list, and perform the complexity analysis of the algorithm.

## Approach & Algorithm: QuickSelect
Instead of sorting the entire array in $\mathcal{O}(N \log N)$ time using standard comparison sorts, the **QuickSelect** algorithm is used to find the $K$-th smallest element in expected linear time by locating the element at 0-based index `target_idx = K - 1`.

1. **Partitioning (Lomuto Partition Scheme)**:
   - Choose the last element `arr[high]` as the pivot.
   - Rearrange the array such that all elements $\le$ pivot are placed before it, and all elements $>$ pivot are placed after it.
   - Return the final sorted index `pi` of the pivot element.
2. **Selection**:
   - If `pi == target_idx`, the element at index `pi` is the $K$-th smallest element.
   - If `pi > target_idx`, the target lies in the left subarray; recurse on `low` to `pi - 1`.
   - If `pi < target_idx`, the target lies in the right subarray; recurse on `pi + 1` to `high`.


## Complexity Analysis

### Time Complexity
- **Best Case**: $\mathcal{O}(N)$ — Occurs when the pivot consistently divides the search space evenly ($N + N/2 + N/4 + \dots \approx 2N$).
- **Average Case**: $\mathcal{O}(N)$ — Expected linear running time over arbitrary permutations.
- **Worst Case**: $\mathcal{O}(N^2)$ — Occurs when the chosen pivot is always an extreme element (smallest or largest), reducing the problem size by only 1 element per recursive call.



## Sample Input & Output

### Example 1
```text
Enter number of elements: 6
Enter 6 elements: 7 10 4 3 20 15
Enter K (1 to 6): 3
The 3-th smallest element is: 7
```

### Example 2
```text
Enter number of elements: 5
Enter 5 elements: 12 3 5 7 19
Enter K (1 to 5): 1
The 1-th smallest element is: 3
```


## Conclusion
The QuickSelect algorithm efficiently determines the $K$-th order statistic without incurring the full $\mathcal{O}(N \log N)$ computational cost of sorting the entire dataset. By pruning one-half of the search space at each partitioning step, it achieves an optimal average time complexity of $\mathcal{O}(N)$.
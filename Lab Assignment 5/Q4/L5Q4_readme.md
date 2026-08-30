# DAA Lab 5 - Question 4: Heap Sort with File Operations

## Problem Statement
Implement Heap Sort to sort $N$ randomly generated elements stored in a file (`input.txt`), store the sorted elements into an output file (`sorted.txt`), and perform the complexity analysis of the algorithm.


## Approach & Algorithm: Heap Sort
Heap Sort is an in-place comparison-based sorting algorithm based on a **Binary Heap** data structure.

1. **Max-Heap Construction**:
   - The array representation of a binary tree is transformed into a Max-Heap where each parent node satisfies $\text{Parent} \ge \text{Children}$.
   - Max-heap building starts bottom-up from index $\lfloor N/2 \rfloor - 1$ down to $0$ using the `heapify` function.
2. **Extraction & Sorting**:
   - The maximum element (root `arr[0]`) is swapped with the last element of the unsorted heap `arr[i]`.
   - The heap size is reduced by 1, and `heapify(arr, i, 0)` is invoked on the new root to restore the Max-Heap property.
   - Repeating this process sorts the entire array in ascending order.
3. **File I/O**:
   - Random values are initially stored into `input.txt`.
   - The values are read into an array, sorted via Heap Sort, and the resulting ordered sequence is written to `sorted.txt`.


## Complexity Analysis

### Time Complexity
- **Building Max-Heap**: $\mathcal{O}(N)$ — Mathematically bounded by $\sum_{h=0}^{\lfloor \log N \rfloor} \frac{N}{2^{h+1}} \mathcal{O}(h) = \mathcal{O}(N)$.
- **Heapify per extraction**: $\mathcal{O}(\log N)$.
- **Best Case**: $\mathcal{O}(N \log N)$
- **Average Case**: $\mathcal{O}(N \log N)$
- **Worst Case**: $\mathcal{O}(N \log N)$ (Unlike QuickSort, Heap Sort guarantees $\mathcal{O}(N \log N)$ in all scenarios).


## Sample Input & Output

### Terminal Output
```text
Enter number of random elements (N): 6
Generated 6 random numbers into 'input.txt'.

Sorted Elements:
145 289 421 532 870 912 

Sorted data successfully saved to 'sorted.txt'.
```

### File Contents
* **input.txt**: `532 145 912 289 870 421`
* **sorted.txt**: `145 289 421 532 870 912`

---

## Conclusion
Heap Sort offers guaranteed $\mathcal{O}(N \log N)$ time complexity in all cases (best, average, and worst) while operating in-place with $\mathcal{O}(1)$ auxiliary memory. Using file input and output streams allows handling arbitrary randomized inputs efficiently and persisting the sorted results directly to storage.
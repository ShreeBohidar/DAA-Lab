# DAA Lab 5 - Question 3: Quick Sort with File Operations

## Problem Statement
Implement Quick Sort to sort $N$ randomly generated numbers stored in a file (`input.txt`), and save the sorted output into another file (`sorted.txt`).


## Approach & Algorithm
The program performs in-place sorting using the Divide-and-Conquer **Quick Sort** algorithm with file input/output redirection.

1. **Data Generation**: 
   - Generates $N$ pseudo-random numbers using a Linear Congruential formula.
   - Stores these numbers sequentially into `input.txt`.
2. **File Reading**:
   - Reads the generated numbers from `input.txt` into an array.
3. **Quick Sort Sorting**:
   - **Partitioning (Lomuto Scheme)**: Chooses the last element as the pivot, rearranges the array so elements $\le$ pivot are to the left and elements $>$ pivot are to the right, placing the pivot at index `pi`.
   - **Recursion**: Recursively applies Quick Sort to subarrays `[low ... pi-1]` and `[pi+1 ... high]`.
4. **File Writing**:
   - Outputs the sorted sequence directly into `sorted.txt` and displays it in the terminal.


## Complexity Analysis

### Time Complexity
- **Best Case**: $\mathcal{O}(N \log N)$ — Occurs when the pivot consistently divides the list into two equal halves.
- **Average Case**: $\mathcal{O}(N \log N)$ — Standard expected behavior over random inputs.
- **Worst Case**: $\mathcal{O}(N^2)$ — Occurs when the input is already sorted or reverse sorted and the extreme element is consistently chosen as pivot.



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
Quick Sort provides efficient $\mathcal{O}(N \log N)$ average-case sorting with minimal memory overhead by sorting in-place. By utilizing file input/output streams, large randomized datasets can be systematically processed, sorted, and persisted across disk files without requiring manual data entry.
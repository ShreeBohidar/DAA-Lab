# DAA Lab Assignment 09 - Question 2

## Problem Statement
[Huffman Coding] Given symbol frequencies, construct a prefix-free binary code of minimum expected length, and output the canonical Huffman codebook (where codes are ordered lexicographically by length). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
Standard Huffman coding produces optimal prefix-free codes, but the code assignments are not unique and can vary based on tree structure. Canonical Huffman coding standardizes the representation so that codebooks can be reconstructed solely using symbol lengths and lexicographical ordering.

1. Array-Based Huffman Tree:
   - We avoid complex pointer-based trees by maintaining indexed flat arrays: `freq[]`, `parent[]`, `left[]`, and `right[]`.
   - Initial n leaf nodes are created. At each step, two root nodes (nodes with `parent == -1`) having the minimum frequencies are greedily merged into a new internal node.
   - Merging repeats n - 1 times until a single tree structure is formed with 2n - 1 total nodes.
2. Bit Length Extraction:
   - For each original symbol from index 0 to n - 1, its optimal code length is computed by traversing up the `parent[]` pointers until reaching the root (`parent == -1`).
3. Canonical Ordering:
   - Sort the symbols using two priority levels:
     - Primary Key: Ascending order of bit length.
     - Secondary Key: Ascending lexicographical (alphabetical) order of symbols.
4. Canonical Code Generation:
   - The first symbol in the sorted list is assigned an all-zero bit sequence of its specific length.
   - For every subsequent symbol i:
     - Increment the integer value of the previous code by 1: `(code + 1)`.
     - Left-shift the value by the difference in lengths to match the current bit length: `(code + 1) << (len[i] - len[i - 1])`.
   - Convert each numeric code to its binary string representation.

---

## Algorithm
1. Read the number of symbols (n).
2. Read each symbol character and its associated frequency.
3. Initialize array-based tree nodes:
   - Set `parent[i] = -1`, `left[i] = -1`, `right[i] = -1` for all leaves 0 <= i < n.
4. Perform n - 1 greedy merge steps:
   - Scan all available nodes without parents (`parent == -1`) to find the two nodes `min1` and `min2` with the lowest frequencies.
   - Create a new parent node with frequency `freq[min1] + freq[min2]`.
   - Set `parent[min1] = new_node`, `parent[min2] = new_node`, `left[new_node] = min1`, and `right[new_node] = min2`.
5. For each symbol i from 0 to n - 1:
   - Trace `parent` links upward to count the depth, which equals the optimal bit length `len[i]`.
6. Sort symbols and lengths primarily by bit length ascending, and break ties by symbol character ascending.
7. Generate canonical binary codes:
   - Set initial integer code value to 0.
   - For each symbol i from 0 to n - 1:
     - If i > 0, compute `code = (code + 1) << (len[i] - len[i - 1])`.
     - Format and display the binary string of length `len[i]`.

---

## Pseudocode
Algorithm CanonicalHuffmanCoding(symbol[], freq[], n):
    Input: Array of characters symbol[], frequency array freq[], total symbols n
    Output: Canonical Huffman codebook ordered by length and lexicographically

    Initialize parent[0..2n-1] with -1
    total_nodes <- n

    For step <- 0 to n - 2 do
        Find min1, min2 among 0 to total_nodes - 1 such that parent == -1 and freq is minimum
        new_node <- total_nodes
        freq[new_node] <- freq[min1] + freq[min2]
        parent[min1] <- new_node
        parent[min2] <- new_node
        left[new_node] <- min1
        right[new_node] <- min2
        total_nodes <- total_nodes + 1
    End For

    For i <- 0 to n - 1 do
        curr <- i
        count <- 0
        While parent[curr] != -1 do
            count <- count + 1
            curr <- parent[curr]
        End While
        len[i] <- count
    End For

    Sort symbol[] and len[] primarily by len ascending, secondarily by symbol ascending

    code <- 0
    For i <- 0 to n - 1 do
        If i > 0 then
            code <- (code + 1) << (len[i] - len[i - 1])
        End If
        binary_str <- ConvertToBinary(code, len[i])
        Print symbol[i], len[i], binary_str
    End For
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by tree construction, depth computation, sorting, and code generation:
1. Greedy Tree Construction:
   - There are (n - 1) merge iterations.
   - In iteration k, finding the two minimum frequencies among the active nodes takes O(n + k) = O(n) time.
   - Summing over all steps: Sum over k from 1 to n - 1 of O(n) = O(n^2).
2. Bit Length Computation:
   - For each of the n symbols, tracing back to the root takes time proportional to the tree depth, bounded by O(n) per symbol.
   - Total length extraction time: O(n^2) worst-case.
3. Sorting Symbols:
   - Bubble sort performs n * (n - 1) / 2 comparisons across lengths and characters, taking Θ(n^2) time.
4. Canonical Code Construction:
   - A single linear loop of n iterations with bit-shift and formatting operations takes O(n) time.

Total Time Complexity:
T(n) = O(n^2) + O(n^2) + Θ(n^2) + O(n) = Θ(n^2) (or O(n log n) when using a priority queue/min-heap and merge sort).

---

## Sample Output
Enter number of symbols (n): 5
Enter symbol (char) and frequency for each:
A 5
B 9
C 12
D 13
E 16

--- Canonical Huffman Codebook ---
Symbol   Bit Length   Canonical Code  
----------------------------------------
E        2            00              
C        2            01              
D        2            10              
A        3            110             
B        3            111             

---

## Conclusion
Canonical Huffman coding uniquely standardizes prefix-free binary encodings by sorting codewords by length and lexicographical order. This array-based implementation avoids pointer complexity and dynamic memory overhead, determining optimal tree depths and assigning standardized binary codes in Θ(n^2) time.
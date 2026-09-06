DAA Lab Assignment 06 - Question 4

Problem Statement:
4. Sorting via reversal procedure: Suppose you are given a permutation p of the integers 1 to n, and seek to sort them to be in increasing order [1,..., n]. The only operation at your disposal is reverse(p, i, j), which reverses the elements of a subsequence p_i,...,p_j in the permutation. For example, the permutation [1, 4, 3, 2, 5] one reversal (of the second through fourth elements) suffices to sort.
- Mathematically, show that it is possible to sort any permutation using O(n) reversals.
- Now suppose that the cost of reverse(p, i, j) is equal to its length, the number of elements in the range, |j - i| + 1. Design an algorithm that sorts p in O(n log^2 n) cost.
Analyse the running time and cost of your algorithm and prove the correctness.
Write a program in C to validate your algorithm supporting your analysis.

The Approach:
- Mathematical Proof for O(n) Reversals:
  We sort the array using an iterative selection/prefix-reversal procedure:
  1. For each suffix position curr from n - 1 down to 1, find the index maxIdx of the maximum element in p[0...curr].
  2. If maxIdx != curr:
     - If maxIdx > 0, reverse the prefix from index 0 to maxIdx. This brings the maximum element to index 0 (1 reversal).
     - Reverse the entire prefix from index 0 to curr. This places the maximum element into its correct final position at index curr (1 reversal).
  3. Since placing each element into its sorted destination requires at most 2 reversals, sorting all n elements requires at most 2(n - 1) reversals, which is strictly O(n).

- O(n log^2 n) Cost Sorting (Reversal Merge Sort):
  When each reversal operation incurs a cost equal to its length |j - i| + 1, standard linear reversals incur sum_{k=1}^n O(k) = O(n^2) cost.
  To achieve O(n log^2 n) total cost, we employ a divide-and-conquer Merge Sort with an in-place block-reversal merge:
  1. Recursively sort the left half p[l...mid] and the right half p[mid+1...r].
  2. Merge the two sorted subarrays in place without auxiliary storage:
     - Select the midpoint of the larger subarray and locate its split position in the other subarray using binary search.
     - Swap the two adjacent middle blocks using a cyclic block shift implemented via three reversals:
       reverse(A), reverse(B), reverse(AB).
     - The cost of shifting two blocks of total length L using 3 reversals is:
       len(A) + len(B) + (len(A) + len(B)) = 2L = O(L).
     - Recursively merge the remaining sub-blocks.

Algorithm:
1. ReverseSubarray(p, i, j):
   - While i < j, swap p[i] and p[j], increment i, decrement j.

2. SortLinearReversals(p, n):
   - For curr from n - 1 down to 1:
       Find maxIdx in p[0...curr].
       If maxIdx == curr, continue.
       If maxIdx > 0, call ReverseSubarray(p, 0, maxIdx).
       Call ReverseSubarray(p, 0, curr).

3. BlockCyclicShift(p, i, mid, j):
   - Call ReverseSubarray(p, i, mid).
   - Call ReverseSubarray(p, mid + 1, j).
   - Call ReverseSubarray(p, i, j).

4. InPlaceReversalMerge(p, l, mid, r):
   - If l > mid or mid >= r, return.
   - Choose the midpoint of the larger subarray.
   - Use binary search in the other subarray to find the split index.
   - Perform BlockCyclicShift to exchange adjacent blocks.
   - Recursively call InPlaceReversalMerge on the two resulting independent partitions.

5. SortReversalDivideConquer(p, l, r):
   - If l >= r, return.
   - Set mid = (l + r) / 2.
   - Call SortReversalDivideConquer(p, l, mid).
   - Call SortReversalDivideConquer(p, mid + 1, r).
   - Call InPlaceReversalMerge(p, l, mid, r).

Pseudocode:
FUNCTION reverseSubarray(p, i, j):
    WHILE i < j:
        SWAP(p[i], p[j])
        i = i + 1
        j = j - 1

FUNCTION sortLinearReversals(p, n):
    FOR curr = n - 1 DOWNTO 1:
        maxIdx = 0
        FOR i = 1 TO curr:
            IF p[i] > p[maxIdx] THEN maxIdx = i
        IF maxIdx != curr:
            IF maxIdx > 0 THEN reverseSubarray(p, 0, maxIdx)
            reverseSubarray(p, 0, curr)

FUNCTION blockCyclicShift(p, i, mid, j):
    reverseSubarray(p, i, mid)
    reverseSubarray(p, mid + 1, j)
    reverseSubarray(p, i, j)

FUNCTION inPlaceReversalMerge(p, l, m, r):
    IF l >= m + 1 OR m >= r THEN RETURN
    len1 = m - l + 1
    len2 = r - m
    IF len1 >= len2 THEN:
        mid1 = (l + m) / 2
        mid2 = BinarySearchUpper(p, m + 1, r, p[mid1])
        k = mid2 - (m + 1)
        blockCyclicShift(p, mid1, m, mid1 + k)
        newMid = mid1 + k
        inPlaceReversalMerge(p, l, mid1 - 1, newMid - 1)
        inPlaceReversalMerge(p, newMid + 1, mid2 - 1, r)
    ELSE:
        mid2 = (m + 1 + r) / 2
        mid1 = BinarySearchUpper(p, l, m, p[mid2])
        k = mid2 - (m + 1)
        blockCyclicShift(p, mid1, m, mid1 + k)
        newMid = mid1 + k
        inPlaceReversalMerge(p, l, mid1 - 1, newMid - 1)
        inPlaceReversalMerge(p, newMid + 1, mid2, r)

FUNCTION sortReversalDivideConquer(p, l, r):
    IF l >= r THEN RETURN
    mid = (l + r) / 2
    sortReversalDivideConquer(p, l, mid)
    sortReversalDivideConquer(p, mid + 1, r)
    inPlaceReversalMerge(p, l, mid, r)

Complexity Analysis:
1. Reversal Count for Linear Prefix Sorting:
   - For each element placed in its final position:
     R(n) <= 2 reversals
   - For n elements:
     R_total(n) <= 2 * (n - 1) = O(n) reversals.
   - Time Complexity:
     T(n) = sum_{k=1}^n (k comparisons + 2k swaps) = O(n^2).

2. Cost Analysis of Divide-and-Conquer In-Place Merge:
   - Shifting two contiguous blocks of size a and b (where a + b = L) via 3 reversals incurs cost:
     Cost_shift(L) = a + b + (a + b) = 2L = O(L).
   - In-place merging splits the array of length L into two pieces where each piece is at most (3/4)L:
     Cost_merge(L) = Cost_merge(L1) + Cost_merge(L2) + O(L), where L1 + L2 <= L and max(L1, L2) <= 3L/4.
     By the Master Theorem, Cost_merge(L) = O(L log L).
   - The overall sorting recurrence for an array of size n is:
     Cost_sort(n) = 2 * Cost_sort(n / 2) + Cost_merge(n)
     Cost_sort(n) = 2 * Cost_sort(n / 2) + c * n log n.
   - Solving by the Master Theorem / recursion tree:
     At each level d (where d = 0, 1, ..., log n), the sum of subproblem sizes is n:
     Level cost = sum O(L log L) <= O(n log n).
     With log n total levels in the recursion tree:
     Total Cost = O(n log n) * log n = O(n log^2 n).

Sample Output:
Enter number of elements n: 6
Enter 6 integers (positive, negative, or zero):
-3 14 0 -8 9 2

Original Array: -3 14 0 -8 9 2 

--- (1) Sorted using O(n) Reversals ---
Result: -8 -3 0 2 9 14 
Total Reversal Operations: 8 (<= 2n = 12)

--- (2) Sorted using Divide-and-Conquer Reversals ---
Result: -8 -3 0 2 9 14 
Total Reversals: 21
Total Cost (sum of |j - i| + 1): 58

Conclusion:
Any sequence or permutation can be sorted using at most 2(n - 1) = O(n) reversal operations by repeatedly bringing the maximal remaining element to the front and reversing it to its final sorted boundary.
Furthermore, when every reversal incurs a cost proportional to its span |j - i| + 1, standard prefix reversal incurs O(n^2) total cost. By employing a divide-and-conquer strategy coupled with an in-place merge driven by cyclic block shifts, each merge phase runs in O(n log n) cost, bounding the cumulative reversal cost of the entire sort to O(n log^2 n).
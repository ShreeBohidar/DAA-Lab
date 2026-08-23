# DAA Lab Assignment 3 - Question 2
# Finding the Defective (Lighter) Coin using Divide and Conquer

## 1. Problem Statement
Working as a quality-control engineer, inspect a batch of `n` coins where at most one coin is lighter (defective) due to excessive shaping, or possibly none is defective (all coins have identical genuine weight). Using a two-pan balance scale, design and implement a Divide and Conquer algorithm to locate the lighter coin or report that all are perfect within `log2(n) + c` weighings for a positive constant `c`.


## 2. Algorithm Overview
The algorithm uses a two-pan balance scale to discard half of the candidate coins per step:

1. **Divide**:
   * For the current coin range of length `len`, split it into two equal subsets of size `half = floor(len / 2)`:
     * Left pan: `arr[low ... low + half - 1]`
     * Right pan: `arr[low + half ... low + 2 * half - 1]`

2. **Conquer & Combine**:
   * **Left Pan Lighter**: Defective coin is in the left half. Recursively search the left half (the right half provides a known genuine coin reference).
   * **Right Pan Lighter**: Defective coin is in the right half. Recursively search the right half (the left half provides a known genuine coin reference).
   * **Both Pans Balance**:
     * If `len` is **even**: All tested coins in this subset are identical.
     * If `len` is **odd**: Test the single unweighed remainder coin `arr[high]` against a known genuine coin `arr[low]`. If it is lighter, it is defective; otherwise, no defective coin exists.
   * **Base Case (`low == high`)**: Weigh the single candidate against a known genuine coin to verify if it is strictly lighter.


## 3. Pseudocode

Algorithm: FIND-DEFECTIVE(arr, low, high, genuine_idx)
Input:  Array arr, search boundaries [low ... high], index of a known genuine coin
Output: Index of defective coin, or -1 if all are genuine

1. if low == high then
2.      res = WEIGH(arr[low], arr[genuine_idx])
3.      if res < 0 then
4.          return low
5.      end if
6.      return -1
7. end if

8.  len = high - low + 1
9.  half = floor(len / 2)
10. l1 = low, r1 = low + half - 1
11. l2 = low + half, r2 = low + 2 * half - 1

12. res = WEIGH(arr[l1 ... r1], arr[l2 ... r2])

13. if res < 0 then
14.     return FIND-DEFECTIVE(arr, l1, r1, l2)
15. else if res > 0 then
16.     return FIND-DEFECTIVE(arr, l2, r2, l1)
17. else
18.     if len % 2 != 0 then
19.         rem_res = WEIGH(arr[high], arr[low])
20.         if rem_res < 0 then
21.             return high
22.         end if
23.     end if
24.     return -1
25. end if


## 4. Recurrence Relation & Weighing Count Analysis

Let `W(n)` represent the maximum number of weighings on the balance scale for `n` coins:

```text
W(n) <= W(n / 2) + 1       if n > 1
W(1) = 1                   (1 verification weighing)

### Derivation:
* At each recursive step, the search range `n` is halved: `n -> n/2 -> n/4 -> ... -> 1`.
* Total recursive levels = `ceil(log2 n)`.
* When an odd group balances, exactly `1` extra weighing verifies the odd coin.
* When reaching the single-coin base case, exactly `1` verification weighing confirms if it is lighter.

Therefore, the total number of balance weighings is bounded by:
* `W(n) <= ceil(log2 n) + 1`
* `W(n) <= log2(n) + c` (where `c = 2`)


## 5. Complexity Analysis

### Time Complexity
* Each balance weighing splits the input size in half with `O(1)` state updates: `T(n) = T(n / 2) + O(1)`.
* By Master's Theorem:
* **Time Complexity = O(log n)**


## 6. Performance Comparison

| Metric | Linear Scan (Weighing Coins 1 by 1) | Divide and Conquer (Balance Scale) |
| :--- | :--- | :--- |
| **Worst-case Weighings** | `n - 1` | `log2(n) + c` |
| **Best-case Weighings** | `1` | `1` |
| **Average Weighings** | `n / 2` | `log2(n)` |
| **Time Complexity** | `O(n)` | `O(log n)` |


## 7. Compilation and Execution

### Compilation:
gcc -O2 defective_coin.c -o defective_coin.exe

### Execution:
./defective_coin.exe

### Sample Run 1 (Defective Coin Present):
Enter total number of coins (n <= 100): 8
Enter weights of 8 coins:
Coin [0] weight: 10
Coin [1] weight: 10
Coin [2] weight: 10
Coin [3] weight: 7
Coin [4] weight: 10
Coin [5] weight: 10
Coin [6] weight: 10
Coin [7] weight: 10

Status: Defective (Lighter) Coin Found at Index 3
Defective Coin Weight: 7
Total Balance Scale Weighings Used: 3

### Sample Run 2 (All Coins Genuine):
Enter total number of coins (n <= 100): 6
Enter weights of 6 coins:
Coin [0] weight: 5
Coin [1] weight: 5
Coin [2] weight: 5
Coin [3] weight: 5
Coin [4] weight: 5
Coin [5] weight: 5

Status: All coins are PERFECT (No defective coin found)
Total Balance Scale Weighings Used: 1
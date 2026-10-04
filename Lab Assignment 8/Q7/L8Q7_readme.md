# DAA Lab Assignment 08 - Question 7

## Problem Statement
[Rod Cutting with Reconstruction] Given a rod of length n inches and an array of prices P = [p1, p2, ..., pn], where pi denotes the market price of a rod piece of length i inches, determine:
(i) The maximum revenue obtainable by cutting up the rod and selling the pieces.
(ii) The exact lengths of the pieces that constitute the optimal decomposition (reconstruction).
Cuts are integral and can be made in any combination (including leaving the rod uncut), and the sum of the piece lengths must equal n. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
The rod-cutting problem can be framed as making an initial cut of length i and recursively solving the remaining subproblem of length j - i:
1. Dynamic Programming Formulation:
   - Let `dp[j]` denote the maximum obtainable revenue for a rod of length `j`.
   - Base Case: `dp[0] = 0` (a rod of length 0 generates 0 revenue).
2. Auxiliary Table for Reconstruction:
   - Maintain an auxiliary array `firstCut[j]` to store the optimal length of the first piece cut from a rod of length `j`.
3. Recurrence Relation:
   - For rod length `j` from 1 to n:
     `dp[j] = max { price[i] + dp[j - i] }` for all `1 <= i <= j`.
   - The value of `i` that maximizes this equation is saved in `firstCut[j]`.
4. Reconstruction:
   - Start with rod of length `temp = n`.
   - Repeatedly output `firstCut[temp]` and set `temp = temp - firstCut[temp]` until `temp == 0`.

---

## Algorithm
1. Read the length of the rod (n).
2. Read the price array `price` of size n + 1 (1-indexed).
3. Initialize arrays `dp` and `firstCut` of size n + 1.
4. Set `dp[0] = 0` and `firstCut[0] = 0`.
5. For `j` from 1 to n:
   - Set `maxVal = -1` and `bestCut = 0`.
   - For `i` from 1 to j:
     - `currentVal = price[i] + dp[j - i]`.
     - If `currentVal > maxVal`:
       - `maxVal = currentVal`.
       - `bestCut = i`.
   - Store `dp[j] = maxVal` and `firstCut[j] = bestCut`.
6. Print maximum revenue `dp[n]`.
7. Reconstruct piece lengths using `firstCut` starting from n until remaining length reaches 0.

---

## Pseudocode
Algorithm CutRod(price[], n):
    Input: Array price where price[i] is value of piece length i, total length n
    Output: Maximum revenue and piece decomposition

    Declare dp[n + 1], firstCut[n + 1]
    dp[0] <- 0
    firstCut[0] <- 0

    For j <- 1 to n do
        maxVal <- -1
        bestCut <- 0
        For i <- 1 to j do
            currentVal <- price[i] + dp[j - i]
            If currentVal > maxVal then
                maxVal <- currentVal
                bestCut <- i
            End If
        End For
        dp[j] <- maxVal
        firstCut[j] <- bestCut
    End For

    Print "Maximum revenue: ", dp[n]
    Print "Optimal piece lengths: "

    temp <- n
    While temp > 0 do
        Print firstCut[temp]
        temp <- temp - firstCut[temp]
    End While
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the nested loop structure:
1. Base cases initialization takes O(1) time.
2. The outer loop runs for rod lengths j from 1 to n: n iterations.
3. The inner loop evaluates every candidate cut i from 1 to j: j iterations.
4. Total loop operations:
   Sum over j from 1 to n of [ j ] = (n * (n + 1)) / 2 = (n^2 + n) / 2
5. Reconstructing the cuts uses a while loop that performs at most n cuts: O(n).

Total Time Complexity:
T(n) = (n^2 + n) / 2 + O(n) = O(n^2)

---

## Sample Output
Enter the length of the rod (n): 8
Enter the prices for lengths 1 to 8: 1 5 8 9 10 17 17 20
Maximum obtainable revenue: 22
Optimal piece lengths: 2 6 

---

## Conclusion
The dynamic programming formulation solves the rod cutting problem by computing optimal revenues from smallest to largest lengths. Storing the optimal initial cut length in an auxiliary array enables immediate O(n) recovery of the cutting pieces, reducing an exponential cut permutation space to O(n^2) time complexity.
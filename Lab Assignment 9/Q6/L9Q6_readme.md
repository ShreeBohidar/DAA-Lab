# DAA Lab Assignment 09 - Question 6

## Problem Statement
[Reorganise String with K-Distance Apart] Given a string S and an integer K, rearrange S such that the same characters are at least distance K apart. If impossible, return an empty string. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
To guarantee that identical characters are positioned at least K places apart, we apply a greedy frequency-based selection strategy.

1. Frequency Counting and Cooldown Window:
   - Identical characters require a cooldown gap of at least K positions between successive placements (i.e., `curr_pos - last_pos[c] >= K`).
   - The characters with the highest remaining frequencies impose the tightest placement constraints because they require the most intervals to fit without overlap.
2. Greedy Choice Property:
   - For each output index from 0 to n - 1, we inspect all candidate characters that are currently eligible (those whose last placement occurred at least K indices prior).
   - Among all eligible characters, we greedily pick the one with the maximum remaining frequency.
   - Placing high-frequency characters as early as their cooldown permits minimizes the risk of running out of valid filler positions in subsequent steps.
3. Impossibility Detection:
   - If at any index no valid character satisfies the distance constraint, it is mathematically impossible to arrange the remaining characters without violating the distance K rule, and the algorithm reports an empty string.
4. Input Representation:
   - A standard frequency array `freq[256]` tracks remaining character counts, and an array `last_pos[256]` stores the most recent index where each character was placed, initialized to a sufficiently large negative value.

---

## Algorithm
1. Read the input string S and the integer K.
2. Compute the length of the string n = strlen(S).
3. If K <= 1, output the string directly as no spacing constraint is violated.
4. Count character frequencies into `freq[256]` and initialize `last_pos[c] = -100000` for all characters c from 0 to 255.
5. Create a result character array `result` of size n + 1.
6. For each position `pos` from 0 to n - 1:
   - Initialize `best_char = -1` and `max_freq = 0`.
   - Scan all characters c from 0 to 255:
     - If `freq[c] > 0` and `(pos - last_pos[c]) >= K`:
       - If `freq[c] > max_freq`, update `max_freq = freq[c]` and `best_char = c`.
   - If `best_char == -1`:
     - Return an empty string / report rearrangement impossible, and exit.
   - Assign `result[pos] = best_char`.
   - Decrement `freq[best_char]` by 1.
   - Update `last_pos[best_char] = pos`.
7. Terminate the string with `result[n] = '\0'` and print the reorganized string.

---

## Pseudocode
Algorithm ReorganizeKDistance(S, K):
    Input: String S of length n, spacing constraint K
    Output: Reorganized string or empty string if impossible

    If K <= 1 then
        Return S
    End If

    Initialize freq[0..255] to 0
    Initialize last_pos[0..255] to -100000

    For i <- 0 to n - 1 do
        freq[(unsigned char)S[i]] <- freq[(unsigned char)S[i]] + 1
    End For

    Declare result[n + 1]

    For pos <- 0 to n - 1 do
        best_char <- -1
        max_freq <- 0

        For c <- 0 to 255 do
            If freq[c] > 0 and (pos - last_pos[c]) >= K then
                If freq[c] > max_freq then
                    max_freq <- freq[c]
                    best_char <- c
                End If
            End If
        End For

        If best_char == -1 then
            Print "Rearrangement impossible: \"\""
            Return ""
        End If

        result[pos] <- best_char
        freq[best_char] <- freq[best_char] - 1
        last_pos[best_char] <- pos
    End For

    result[n] <- '\0'
    Print "Reorganized String: ", result
    Return result
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by string parsing and the position-by-position greedy selection:
1. Frequency counting and initialization take O(n + Σ) time, where Σ is the alphabet size (Σ = 256 for ASCII).
2. Construction Loop:
   - The outer loop runs for all n character slots of the output string.
   - For each slot, the inner loop searches across all Σ = 256 possible character entries to find the eligible character with highest frequency.
   - Total operations in placement: n * Σ = 256 * n = O(n).
3. String finalization and display take O(n) time.

Total Time Complexity:
T(n) = O(n + Σ) + O(Σ * n) + O(n) = O(n) (since alphabet size Σ is a fixed constant, or O(n log Σ) if using a max-priority queue).

---

## Sample Output
Enter the string: aabbcc
Enter distance K: 3

Reorganized String (K = 3 apart): abcabc

---

## Conclusion
The greedy rearrangement strategy systematically prioritizes highest-frequency characters subject to a sliding cooldown window of size K. By iteratively picking the most restrictive character that satisfies the distance separation, the algorithm either constructs a valid collision-free permutation or detects structural impossibility in optimal linear O(n) time.
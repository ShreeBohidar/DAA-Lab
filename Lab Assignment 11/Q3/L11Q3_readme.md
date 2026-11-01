# DAA Lab Assignment 11 - Question 03

## Problem Statement
[Bidirectional BFS for Shortest Transformation Sequence in a Word Graph] You are given:
- A dictionary D containing N unique words, where every word has the exact same length L.
- A starting word A and a target word B, both of length L.

A valid mutation step consists of changing exactly one character of a word such that the resulting word exists in dictionary D. A transformation sequence from A to B is an ordered sequence of words:
W0, W1, W2, ..., Wk
such that:
1. W0 = A and Wk = B.
2. Every intermediate word Wi is in D for all 1 <= i <= k. (Note: B must always be in D).
3. For every adjacent pair (W_{i-1}, Wi), the two words differ by exactly one character (their Hamming distance is 1).

Objective: Compute the minimum number of mutations k required to transform A into B. If A cannot be transformed into B through valid intermediate words in D, return -1 (or report that no valid path exists).

Constraints:
- N < 10^5 (number of dictionary words)
- L <= 10 (length of each word)
- All words consist solely of lowercase English letters ('a' to 'z').

By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
1. Word Graph Formulation:
   - Each unique word represents a vertex in an unweighted, undirected graph.
   - An edge exists between word u and word v if and only if their Hamming distance is exactly 1 (they differ by exactly one character across length L).
2. Bidirectional Search Paradigm:
   - Standard unidirectional BFS expands outward from source word A across depth d with branching factor b, exploring O(b^d) states.
   - Bidirectional BFS simultaneously runs two concurrent searches:
     - A forward BFS starting from source word A.
     - A backward BFS starting from target word B.
   - The search space is reduced to O(b^(d/2) + b^(d/2)) = O(b^(d/2)), cutting down exponential expansion.
3. Dynamic Frontier Balancing:
   - At each iteration, the algorithm compares the number of active words in the forward queue versus the backward queue.
   - By always expanding the smaller frontier level-by-level, memory footprint and exploration overhead remain minimal.
4. Intersection and Path Completion:
   - When a word v being explored by one search frontier has already been visited by the opposite search direction, a complete path between A and B is established.
   - The total minimum mutation steps k is computed directly:
     k = dist_fwd[v] + dist_bwd[v] (or dist_from_one_side + 1 + dist_from_other_side).
5. Input Boundary Conditions:
   - If A equals B, the transformation distance is 0.
   - If target word B is absent from dictionary D, no valid path can terminate at B, returning -1.
   - If source word A is absent from D, it is included as the entry node without violating dictionary requirements on intermediate words.

---

## Algorithm
1. Read the number of dictionary words N and length L.
2. Read start word A and target word B.
3. If A == B, output 0 and terminate.
4. Read the N dictionary words into a 2D character array `words[][]`.
5. Check if B exists in the dictionary. If absent, output -1 and terminate.
6. Check if A exists in the dictionary; if not, append A to the list at index N and increment total word count.
7. Initialize two distance arrays `dist_fwd[]` and `dist_bwd[]` with -1.
8. Initialize two queues `q_fwd[]` and `q_bwd[]`:
   - Set `dist_fwd[start_idx] = 0` and enqueue start index into `q_fwd`.
   - Set `dist_bwd[target_idx] = 0` and enqueue target index into `q_bwd`.
9. While both `q_fwd` and `q_bwd` are non-empty:
   - Determine which queue has fewer elements.
   - For all elements currently at that frontier level:
     - Dequeue node u.
     - For every word v in the word set:
       - If Hamming distance between words[u] and words[v] is 1:
         - If v is already visited by the opposite direction's search:
           - Record minimum mutations = current_dist + 1 + opposite_dist.
           - Jump to result reporting.
         - If v is unvisited in the current direction:
           - Record dist[v] = dist[u] + 1.
           - Enqueue v into the current direction's queue.
10. If the queues empty without an intersection, report -1 (unreachable).

---

## Pseudocode
Algorithm BidirectionalWordLadder(D, N, L, A, B):
    Input: Dictionary D with N words of length L, Start word A, Target word B
    Output: Minimum mutations k to transform A to B, or -1 if unreachable

    If A == B then
        Return 0
    End If

    If B not in D then
        Return -1
    End If

    If A not in D then
        Append A to D
    End If

    Initialize dist_fwd[0..|D|-1] <- -1
    Initialize dist_bwd[0..|D|-1] <- -1
    Initialize Queue Q_fwd, Q_bwd

    dist_fwd[index(A)] <- 0
    Enqueue(Q_fwd, index(A))

    dist_bwd[index(B)] <- 0
    Enqueue(Q_bwd, index(B))

    While Q_fwd is not empty and Q_bwd is not empty do
        If Size(Q_fwd) <= Size(Q_bwd) then
            ActiveQ <- Q_fwd
            curr_dist <- dist_fwd
            opp_dist <- dist_bwd
        Else
            ActiveQ <- Q_bwd
            curr_dist <- dist_bwd
            opp_dist <- dist_fwd
        End If

        level_size <- Size(ActiveQ)
        For s <- 1 to level_size do
            u <- Dequeue(ActiveQ)

            For each word v in D do
                If HammingDistance(D[u], D[v]) == 1 then
                    If opp_dist[v] != -1 then
                        Return curr_dist[u] + 1 + opp_dist[v]
                    End If

                    If curr_dist[v] == -1 then
                        curr_dist[v] <- curr_dist[u] + 1
                        Enqueue(ActiveQ, v)
                    End If
                End If
            End For
        End For
    End While

    Return -1
End Algorithm

---

## Complexity Analysis
1. Neighbor Validation:
   - Comparing two words of length L to check if their Hamming distance equals 1 takes O(L) time.
2. Search State Space:
   - Let b be the average branching factor (number of valid 1-letter mutation neighbors per word) and d be the shortest transformation path length.
   - A standard BFS visits O(b^d) vertices.
   - Bidirectional BFS meets in the middle at depth d/2 from both ends, traversing only O(b^(d/2) + b^(d/2)) = O(b^(d/2)) states.
3. Level-by-Level Neighbor Exploration:
   - For each word popped from the active frontier, scanning candidate words against the set of size N requires checking pairs in O(N * L) time.
   - With at most V_explored <= N nodes visited across both frontiers:
     Total Time Complexity: O(V_explored * N * L), bounded by O(N^2 * L) in the worst case, but practically constrained to O(b^(d/2) * N * L).

---

## Sample Output
Enter number of dictionary words (N) and word length (L): 6 3
Enter starting word A: hit
Enter target word B: cog
Enter 6 dictionary words:
hot
dot
dog
lot
log
cog

--- Result ---
Shortest transformation sequence length (mutations k): 4

---

## Conclusion
The shortest transformation sequence in a word mutation graph is an unweighted shortest path problem. Employing Bidirectional Breadth-First Search significantly optimizes search efficiency compared to standard BFS by expanding forward and backward frontiers concurrently and meeting at intermediate words. Dynamically choosing the smaller frontier at each stage guarantees minimal branching, providing optimal transformation sequence lengths while deterministically detecting disconnected target words.
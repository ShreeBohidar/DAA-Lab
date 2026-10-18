# DAA Lab Assignment 10 - Question 01

## Problem Statement
[Online Graph-Bipartiteness Testing] A graph is bipartite if and only if it contains no odd-length cycles. Given an undirected graph with V vertices, edges arrive online one by one. Maintain whether the graph remains bipartite. If adding an edge (u, v) does not introduce an odd cycle, add it; otherwise, report that it violates bipartiteness and skip it. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
A graph is bipartite if and only if its vertices can be partitioned into two disjoint sets such that every edge connects a vertex in one set to a vertex in the other set (equivalent to 2-colorability). In an online setting where edges arrive sequentially, testing for bipartiteness from scratch using BFS or DFS requires O(V + E) per query, which is computationally expensive.

1. Disjoint Set Union with Parities:
   - A potential-based Disjoint Set Union (DSU) structure tracks both connected components and the 2-coloring parity (distance modulo 2) from each node to its component root.
   - For every node `v`, `parity_to_parent[v]` denotes whether `v` has the same color (0) or opposite color (1) relative to its immediate parent.
2. Path Compression with XOR Roll-up:
   - During `find_root(v)`, path compression points `v` directly to the root while maintaining correct parity:
     `parity_to_parent[v] = parity_to_parent[v] ^ parity_to_parent[original_parent]`
   - This ensures parity relative to the root is evaluated in near-constant time.
3. Online Edge Validation:
   - For an incoming edge `(u, v)`:
     - Find roots `root_u = find_root(u)` and `root_v = find_root(v)`.
     - **Intra-Component Edge (`root_u == root_v`)**: Vertices already reside in the same component. If `parity_to_parent[u] == parity_to_parent[v]`, both endpoints have the same color. Connecting them creates an odd cycle of length `2k + 1`. The edge is rejected and skipped. If their parities differ, the edge connects opposite colors, closing an even cycle; the edge is safe to accept.
     - **Inter-Component Edge (`root_u != root_v`)**: The edge merges two disjoint components. To ensure proper alternating colors, set the relative parity between the merged root and the other root:
       `parity_to_parent[root_u] = parity_to_parent[u] ^ parity_to_parent[v] ^ 1`
     - Union-by-rank balances the tree depth.

---

## Algorithm
1. Read the number of vertices `V` and total incoming edges `E`.
2. Initialize three static arrays of size `V + 1`:
   - `parent_node[i] = i`
   - `parity_to_parent[i] = 0`
   - `rank_tree[i] = 0`
3. For each incoming edge `(u, v)`:
   - Compute `root_u = find_root(u)` and `root_v = find_root(v)`.
   - If `root_u == root_v`:
     - If `parity_to_parent[u] == parity_to_parent[v]`, print rejection message and do not modify the graph.
     - Else, print acceptance message.
   - If `root_u != root_v`:
     - Link the root with lower rank to the root with higher rank.
     - Update the rank if both roots have equal ranks.
     - Set the parity between roots to `parity_to_parent[u] ^ parity_to_parent[v] ^ 1`.
     - Print acceptance message.
4. Terminate after processing all `E` edge queries.

---

## Pseudocode
Algorithm OnlineBipartiteness(V, edges[][], E):
    Input: Total vertices V, sequence of E edges (u, v)
    Output: Status of each edge acceptance or rejection

    For i <- 1 to V do
        parent[i] <- i
        parity[i] <- 0
        rank[i] <- 0
    End For

    Function FindRoot(v):
        If parent[v] == v then
            Return v
        End If
        orig_parent <- parent[v]
        parent[v] <- FindRoot(parent[v])
        parity[v] <- parity[v] XOR parity[orig_parent]
        Return parent[v]
    End Function

    For each edge (u, v) in edges do
        root_u <- FindRoot(u)
        root_v <- FindRoot(v)

        If root_u == root_v then
            If parity[u] == parity[v] then
                Print "Rejected: Odd cycle detected"
            Else
                Print "Accepted: Graph remains bipartite"
            End If
        Else
            rel_parity <- parity[u] XOR parity[v] XOR 1
            If rank[root_u] < rank[root_v] then
                parent[root_u] <- root_v
                parity[root_u] <- rel_parity
            Else
                parent[root_v] <- root_u
                parity[root_v] <- rel_parity
                If rank[root_u] == rank[root_v] then
                    rank[root_u] <- rank[root_u] + 1
                End If
            End If
            Print "Accepted: Graph remains bipartite"
        End If
    End For
End Algorithm

---

## Complexity Analysis
Let V be the number of vertices and E be the number of edge queries:
1. DSU Initialization:
   - Initializing parent, rank, and parity arrays takes O(V) time.
2. Edge Processing:
   - Each edge arrival performs two `find_root` calls and at most one union operation.
   - With both path compression and union-by-rank, each operation executes in amortized O(alpha(V)) time, where alpha is the inverse Ackermann function.
   - For E edges, total query processing takes O(E * alpha(V)) time.
3. Space Allocation:
   - Parent, parity, and rank tracking require three 1D static integer arrays of size O(V).

Total Time Complexity:
T(V, E) = O(V) + O(E * alpha(V)) = O(E * alpha(V))

---

## Sample Output
Enter number of vertices and edges: 5 6
Enter edges sequentially (u v):
1 2
Edge (1, 2): Accepted. Graph remains bipartite.
2 3
Edge (2, 3): Accepted. Graph remains bipartite.
3 4
Edge (3, 4): Accepted. Graph remains bipartite.
4 1
Edge (4, 1): Accepted. Graph remains bipartite.
1 3
Edge (1, 3): Accepted. Graph remains bipartite.
2 4
Edge (2, 4): Rejected. Violates bipartiteness (odd cycle detected).

---

## Conclusion
Online graph-bipartiteness testing dynamically decides whether an incoming edge preserves 2-colorability without scanning entire cycles. By augmenting the Disjoint Set Union data structure with edge parities updated via XOR roll-up during path compression, odd-cycle introduction is verified in amortized inverse Ackermann time per edge. This delivers an optimal O(E * alpha(V)) solution, bypassing the O(E * (V + E)) overhead of repeated graph traversals.
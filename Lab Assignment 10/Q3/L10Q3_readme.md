# DAA Lab Assignment 10 - Question 03

## Problem Statement
[Maximum Weight Component with Size Constraints] Given a graph where each vertex v has weight w_v, edges are added sequentially with weights. At any point, compute the maximum total vertex weight of any connected component whose size does not exceed a threshold K. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.[cite: 1]

---

## Approach
As edges arrive sequentially, vertices merge into larger connected components. Maintaining and tracking component metrics from scratch via BFS or DFS after every edge addition would take O(m * (n + m)) time. Using an augmented Disjoint Set Union (DSU) structure allows real-time maintenance of both vertex weight sums and component sizes.

1. Augmented Disjoint Set Union:
   - For every disjoint component root, maintain three pieces of metadata:
     - `parent_node[v]`: Parent pointer compressed along the path to the set root.
     - `comp_size[v]`: Total number of vertices present in the component.
     - `comp_weight[v]`: Cumulative sum of vertex weights belonging to the component.
2. Union-by-Size and Aggregation:
   - When an incoming edge connects vertex `u` and vertex `v`:
     - Determine their respective representatives `root_u = find_root(u)` and `root_v = find_root(v)`.
     - If `root_u != root_v`, attach the smaller component under the root of the larger component.
     - Add the size of the smaller component to the larger root: `comp_size[root_u] += comp_size[root_v]`.
     - Add the total vertex weight of the smaller component to the larger root: `comp_weight[root_u] += comp_weight[root_v]`.
3. Threshold-Bounded Query Evaluation:
   - After each sequential edge union, scan all valid component roots (`parent_node[i] == i`).
   - For every root satisfying `comp_size[i] <= K`, compare `comp_weight[i]` against the tracked maximum.
   - Return the highest valid vertex weight, or report that no component satisfies the size threshold.

---

## Algorithm
1. Read the number of vertices `n`, total edges `m`, and the size threshold `K`.
2. Read the initial weight values for all vertices into an array `weights[]`.
3. Initialize the DSU:
   - For each vertex `i` from 1 to `n`:
     - `parent_node[i] = i`
     - `comp_size[i] = 1`
     - `comp_weight[i] = weights[i]`
4. Evaluate and display the initial maximum component weight among components with size <= `K`.
5. For each incoming edge `(u, v)` from 1 to `m`:
   - Compute `root_u = find_root(u)` and `root_v = find_root(v)`.
   - If `root_u != root_v`:
     - Merge the root of the smaller tree into the root of the larger tree.
     - Accumulate both size and vertex weight into the chosen representative root.
   - Iterate through all vertices `i` from 1 to `n`:
     - If `parent_node[i] == i` and `comp_size[i] <= K`:
       - Update `max_weight = max(max_weight, comp_weight[i])`.
   - Output the maximum component weight after the current edge insertion.
6. Terminate after processing all `m` edges.

---

## Pseudocode
Algorithm MaxWeightComponentUnderK(n, m, K, weights[], edges[][]):
    Input: Vertex count n, edge count m, threshold K, vertex weights, list of m edges
    Output: Maximum component weight with size <= K after each edge insertion

    For i <- 1 to n do
        parent[i] <- i
        comp_size[i] <- 1
        comp_weight[i] <- weights[i]
    End For

    Function FindRoot(v):
        If parent[v] == v then
            Return v
        End If
        parent[v] <- FindRoot(parent[v])
        Return parent[v]
    End Function

    Function UnionSets(u, v):
        root_u <- FindRoot(u)
        root_v <- FindRoot(v)
        If root_u != root_v then
            If comp_size[root_u] < comp_size[root_v] then
                Swap(root_u, root_v)
            End If
            parent[root_v] <- root_u
            comp_size[root_u] <- comp_size[root_u] + comp_size[root_v]
            comp_weight[root_u] <- comp_weight[root_u] + comp_weight[root_v]
        End If
    End Function

    Function GetMaxWeight():
        max_val <- -1
        For i <- 1 to n do
            If parent[i] == i and comp_size[i] <= K then
                If max_val == -1 or comp_weight[i] > max_val then
                    max_val <- comp_weight[i]
                End If
            End If
        End For
        Return max_val
    End Function

    Print "Initial: ", GetMaxWeight()

    For step <- 0 to m - 1 do
        u <- edges[step][0]
        v <- edges[step][1]
        UnionSets(u, v)
        Print "Step ", step + 1, ": ", GetMaxWeight()
    End For
End Algorithm

---

## Complexity Analysis
Let n be the total number of vertices and m be the number of sequential edge additions:
1. DSU Initialization:
   - Initializing parent, size, and weight arrays takes O(n) time.
2. Edge Union Operations:
   - For each edge addition, path compression combined with union-by-size executes in amortized O(alpha(n)) time, where alpha is the inverse Ackermann function.
   - For m edges, total union overhead is O(m * alpha(n)).
3. Component Evaluation per Step:
   - After each edge addition, scanning all unique component roots to identify the maximum weight with size <= K takes O(n) time.
   - Over m edge operations, the total scanning time is O(m * n).

Total Time Complexity:
T(n, m) = O(n) + O(m * alpha(n)) + O(m * n) = O(m * n)

---

## Sample Output
Enter number of vertices (n), edges (m), and size threshold (K): 5 4 3
Enter weights of 5 vertices:
10 25 15 30 20
Initial maximum component weight (size <= 3): 30
Enter 4 edges sequentially (u v):
1 2
After adding edge 1-2: Maximum component weight (size <= 3) = 35
2 3
After adding edge 2-3: Maximum component weight (size <= 3) = 50
4 5
After adding edge 4-5: Maximum component weight (size <= 3) = 50
3 4
After adding edge 3-4: No component satisfies size <= 3

---

## Conclusion
Tracking property-constrained components during dynamic edge insertions is efficiently solved by augmenting Disjoint Set Union nodes with cumulative metrics. Maintaining component sizes and total vertex weights alongside root pointers enables immediate aggregation during union operations. Filtering valid components against size threshold K after each edge event provides an exact and robust solution in O(m * n) time without requiring repeated full graph traversals.
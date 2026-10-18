# DAA Lab Assignment 10 - Question 04

## Problem Statement
[Reverse Time-Step DSU Application] Given a vertex-weighted undirected graph, vertices are sequentially deleted one by one in an order P = [p1, p2, ..., pV]. After each vertex deletion, compute the maximum sum of vertex values among all remaining connected components. Note that deleting a vertex in a graph means removing that specific vertex and all edges connected (incident) to it from the graph structure. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.[cite: 1]

---

## Approach
Directly deleting vertices and their incident edges dynamically fractures connected components into smaller disconnected subgraphs. Standard graph traversal (BFS or DFS) would require O(V * (V + E)) total time, which becomes prohibitively slow. However, standard Disjoint Set Union (DSU) operations excel at incremental merges rather than deletions.

1. Reverse Time-Step Technique (Offline Processing):
   - Vertex deletions in forward order P = [p1, p2, ..., pV] are algebraically symmetric to vertex additions in reverse order P_rev = [pV, pV-1, ..., p1].
   - When the final vertex pV is removed, the graph is completely empty (maximum component sum is 0).
   - Reversing the deletion sequence transforms component destruction into incremental component additions and merges.
2. Static Adjacency Representation:
   - Graph edges are stored using head, to_node, and next_edge arrays (forward-star representation).
   - This pointer-free representation avoids dynamic memory allocation while allowing direct traversal of incident neighbors.
3. Component Weight Tracking via DSU:
   - Maintain an `is_active[]` array to track whether a vertex has been introduced in the reverse timeline.
   - For every component root, maintain `comp_weight[root]` storing the cumulative sum of vertex weights in that component.
   - When activating vertex `u`:
     - Mark `is_active[u] = 1`.
     - Initialize `comp_weight[u] = weight[u]`.
     - Update `current_max = max(current_max, comp_weight[u])`.
     - For each incident neighbor `v` that is already active (`is_active[v] == 1`):
       - If `find_root(u) != find_root(v)`, merge the sets using union-by-rank.
       - Sum the component weights into the surviving root:
         `comp_weight[new_root] = comp_weight[root_u] + comp_weight[root_v]`
       - Update `current_max = max(current_max, comp_weight[new_root])`.
4. Answer Mapping:
   - The value of `current_max` after inserting `p_step` in reverse order corresponds directly to the maximum component sum after vertex `p_{step - 1}` is removed in the forward timeline.

---

## Algorithm
1. Read the number of vertices `V` and total edges `E`.
2. Read the initial weight values for all vertices 1 to `V`.
3. Read all `E` undirected edges and store them using head, to_node, and next_edge arrays.
4. Read the deletion sequence `P = [p1, p2, ..., pV]`.
5. Initialize the DSU:
   - For each vertex `i` from 1 to `V`:
     - `parent[i] = i`, `rank[i] = 0`, `is_active[i] = 0`.
   - Set `current_max = 0` and `ans[V] = 0`.
6. Traverse the deletion sequence in reverse from `step = V` down to `1`:
   - Let `u = P[step]`.
   - Mark `is_active[u] = 1`.
   - Update `current_max = max(current_max, comp_weight[u])`.
   - For each neighbor `v` of `u` in the graph:
     - If `is_active[v] == 1`:
       - Find `root_u = find_root(u)` and `root_v = find_root(v)`.
       - If `root_u != root_v`:
         - Merge `root_u` and `root_v` using union-by-rank.
         - Accumulate component weight into the new root.
         - Update `current_max = max(current_max, comp_weight[new_root])`.
   - If `step > 1`, set `ans[step - 1] = current_max`.
7. Display the stored answers `ans[1]` through `ans[V]` representing maximum component sums after each deletion.

---

## Pseudocode
Algorithm ReverseTimeStepDSU(V, E, weights[], edges[][], P[]):
    Input: Total vertices V, edges E, vertex weights, deletion sequence P
    Output: Maximum component weight after each deletion

    For i <- 1 to V do
        parent[i] <- i
        rank[i] <- 0
        comp_weight[i] <- weights[i]
        is_active[i] <- False
    End For

    BuildAdjacency(edges, E)

    current_max <- 0
    ans[V] <- 0

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
            If rank[root_u] < rank[root_v] then
                parent[root_u] <- root_v
                comp_weight[root_v] <- comp_weight[root_v] + comp_weight[root_u]
            Else
                parent[root_v] <- root_u
                comp_weight[root_u] <- comp_weight[root_u] + comp_weight[root_v]
                If rank[root_u] == rank[root_v] then
                    rank[root_u] <- rank[root_u] + 1
                End If
            End If
        End If
    End Function

    For step <- V down to 1 do
        node <- P[step]
        is_active[node] <- True

        If comp_weight[node] > current_max then
            current_max <- comp_weight[node]
        End If

        For each neighbor of node in Graph do
            If is_active[neighbor] == True then
                root_node <- FindRoot(node)
                root_neighbor <- FindRoot(neighbor)
                If root_node != root_neighbor then
                    UnionSets(node, neighbor)
                    new_root <- FindRoot(node)
                    If comp_weight[new_root] > current_max then
                        current_max <- comp_weight[new_root]
                    End If
                End If
            End If
        End For

        If step > 1 then
            ans[step - 1] <- current_max
        End If
    End For

    For i <- 1 to V do
        Print "After deleting vertex ", P[i], ": ", ans[i]
    End For
End Algorithm

---

## Complexity Analysis
Let V be the number of vertices and E be the number of edges:
1. Graph Construction:
   - Initializing head array and inserting 2 * E directed half-edges takes O(V + E) time.
2. DSU Initialization:
   - Initializing parent, rank, weight, and status arrays takes O(V) time.
3. Reverse Processing:
   - Each vertex is activated exactly once across all steps.
   - Each undirected edge (u, v) is checked at most twice (once from u and once from v).
   - Union and find operations with path compression and union-by-rank take O(alpha(V)) amortized time.
   - Processing all reverse additions and edge merges takes O(V + E * alpha(V)) time.
4. Output Display:
   - Printing the precomputed results takes O(V) time.

Total Time Complexity:
T(V, E) = O(V + E) + O(V + E * alpha(V)) + O(V) = O(V + E * alpha(V))

---

## Sample Output
Enter number of vertices and edges: 4 4
Enter weights of 4 vertices:
10 20 30 40
Enter 4 edges (u v):
1 2
2 3
3 4
4 1
Enter the sequence of 4 vertex deletions:
2 4 1 3

Maximum component sum after each deletion:
After deleting vertex 2: Maximum component sum = 70
After deleting vertex 4: Maximum component sum = 30
After deleting vertex 1: Maximum component sum = 30
After deleting vertex 3: Maximum component sum = 0

---

## Conclusion
Simulating vertex and edge deletions in forward order causes continuous component fragmentation that is computationally prohibitive to track. Inverting time converts destruction queries into incremental graph construction. Leveraging an augmented Disjoint Set Union over the reversed query sequence resolves all dynamic component sum queries in near-linear O(V + E * alpha(V)) time.
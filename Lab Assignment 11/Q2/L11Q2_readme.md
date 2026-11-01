# DAA Lab Assignment 11 - Question 02

## Problem Statement
[Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning] You are given:
- An unweighted, undirected graph G = (V, E).
- A set of K designated hub vertices H = {h1, h2, ..., hK} subset of V, indexed from 1 to K.
- An integer radius threshold R > 0.

Let dist(u, v) denote the shortest path distance (minimum number of edges) between vertices u and v in G.
For every vertex v in V, assign an ownership label owner[v] in {1, 2, ..., K} U {-1} according to the following rules:
1. Distance Metric: Find the distance from v to each service hub: di = dist(v, hi) for all i in {1, ..., K}. Let dmin(v) = min di over 1 <= i <= K.
2. Reachability Threshold (R): If dmin(v) > R, vertex v lies outside the service coverage area. Set owner[v] = -1.
3. Closest Hub Assignment: If dmin(v) <= R, assign v to the hub hi that minimizes di.
4. Deterministic Tie-Breaking: If multiple hubs achieve the exact same minimum distance dmin(v), choose the hub with the smallest numerical index i.

Objective: Output the array owner[1...|V|] containing the assigned hub index (or -1 if unassigned) and the corresponding shortest distance to that hub for every vertex. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
1. Multi-Source BFS Paradigm:
   - Instead of initiating K independent Breadth-First Searches (which would incur redundant graph traversals), all K hubs are treated as simultaneous wavefront sources.
   - All hubs {h1, h2, ..., hK} are initialized with a distance of 0 and pushed into the BFS FIFO queue.
2. Deterministic Tie-Breaking Mechanism:
   - Hubs are enqueued strictly in ascending order of their designated indices (i = 1 to K).
   - Because standard BFS visits vertices in non-decreasing order of distance, earlier enqueued hubs naturally expand first.
   - For an edge (u, v), if v is encountered at dist[u] + 1 == dist[v], the owner label is updated to min(owner[v], owner[u]) to guarantee that the hub with the smallest numerical index wins ties deterministically.
3. Radius Pruning:
   - If dist[u] >= R, its outgoing edges need not be expanded further since any adjacent neighbor reached via u would have a distance of at least R + 1 > R.
   - Vertices that remain unreached or have a minimum distance exceeding R are assigned an owner value of -1.
4. Simplified Data Structures:
   - Variable Length Arrays (VLAs) are used to dynamically adapt array allocations to graph dimensions without fixed buffer limits or explicit pointer manipulation.

---

## Algorithm
1. Read the number of vertices N and edges M.
2. Read the number of hubs K and the radius threshold R.
3. Read the K hub vertices and store them in array `hubs[1...K]`.
4. Initialize the adjacency matrix `adj[][]` of size (N + 1) x (N + 1) to 0.
5. Read all M undirected edges (u, v) and set `adj[u][v] = 1` and `adj[v][u] = 1`.
6. Initialize `dist[1...N]` to infinity (INF) and `owner[1...N]` to -1.
7. Initialize a queue of size N + 1. For each hub index i from 1 to K:
   - Let h = hubs[i].
   - If dist[h] == INF, set dist[h] = 0, owner[h] = i, and push h to the queue.
   - If dist[h] == 0 and i < owner[h], update owner[h] = i.
8. While the queue is not empty:
   - Pop u from the front of the queue.
   - If dist[u] >= R, continue to the next queue item.
   - For each vertex v from 1 to N such that adj[u][v] == 1:
     - If dist[u] + 1 < dist[v]:
       - Update dist[v] = dist[u] + 1.
       - Update owner[v] = owner[u].
       - Push v into the queue.
     - Else if dist[u] + 1 == dist[v]:
       - If owner[u] < owner[v], update owner[v] = owner[u].
9. For each vertex v from 1 to N:
   - If dist[v] <= R and owner[v] != -1, report owner[v] and dist[v].
   - Otherwise, report owner[v] = -1.

---

## Pseudocode
Algorithm MultiSourceVoronoiPartition(V, E, H, K, R):
    Input: Vertices V, Edges E, Hub array H[1..K], Hub count K, Radius R
    Output: Array owner[1..V] and distance to assigned hub

    For v <- 1 to V do
        dist[v] <- INF
        owner[v] <- -1
    End For

    Initialize empty FIFO Queue Q

    For i <- 1 to K do
        h <- H[i]
        If dist[h] == INF then
            dist[h] <- 0
            owner[h] <- i
            Enqueue(Q, h)
        Else If dist[h] == 0 and i < owner[h] then
            owner[h] <- i
        End If
    End For

    While Q is not empty do
        u <- Dequeue(Q)

        If dist[u] >= R then
            Continue
        End If

        For each neighbor v of u do
            If dist[u] + 1 < dist[v] then
                dist[v] <- dist[u] + 1
                owner[v] <- owner[u]
                Enqueue(Q, v)
            Else If dist[u] + 1 == dist[v] then
                If owner[u] < owner[v] then
                    owner[v] <- owner[u]
                End If
            End If
        End For
    End While

    For v <- 1 to V do
        If dist[v] <= R and owner[v] != -1 then
            Print "Vertex", v, "assigned to Hub", owner[v], "at distance", dist[v]
        Else
            owner[v] <- -1
            Print "Vertex", v, "Unassigned (owner = -1)"
        End If
    End For
End Algorithm

---

## Complexity Analysis
1. Multi-Source BFS Traversal:
   - Initializing the K sources takes O(K) time.
   - Each vertex v enters the BFS queue at most once.
   - When a vertex u is dequeued, all its adjacent neighbors are checked via the adjacency structure.
   - For an adjacency matrix representation, inspecting neighbors across all visited vertices requires O(|V|^2) total checks. (Under an adjacency list representation, this phase takes O(|V| + |E|) time).
2. Radius Pruning:
   - Nodes at or beyond distance R do not expand their edges, pruning further edge checks.
3. Final Ownership Formatting:
   - A single linear scan over all vertices to format the output takes O(|V|) time.

Total Time Complexity: O(|V|^2) with adjacency matrix (or O(|V| + |E|) with adjacency list).

---

## Sample Output
Enter number of vertices and edges: 6 6
Enter number of hubs (K) and radius threshold (R): 2 2
Enter the 2 hub vertices (1 to 6):
1 6
Enter 6 undirected edges (u v):
1 2
2 3
3 4
4 5
5 6
2 5

--- Voronoi Cell Partitioning (Radius R = 2) ---
Vertex	Owner Hub Index	Hub Vertex	Distance
1	1		1		0
2	1		1		1
3	1		1		2
4	2		6		2
5	2		6		1
6	2		6		0

---

## Conclusion
Multi-source Breadth-First Search efficiently partitions a graph into discrete Voronoi cells relative to designated hubs without requiring independent single-source traversals. By enqueueing hubs in index sequence and applying an explicit comparison during equal-distance relaxations, deterministic tie-breaking is maintained. The radius cutoff parameter R ensures that nodes exceeding the service threshold are properly designated as unassigned.
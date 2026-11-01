# DAA Lab Assignment 11 - Question 01

## Problem Statement
[Shortest Path on Parity-Constrained Graphs via 0-1 BFS] You are given a directed graph G = (V, E), a designated source vertex S in V, and an extra penalty cost C >= 0. Every directed edge (u, v) in E has a weight w(u, v) in {0, 1}.
For any path P from S to a vertex v:
1. Let W(P) denote the sum of all edge weights along P.
2. Let k1(P) denote the total count of weight-1 edges traversed in P.
3. The effective cost of path P is defined as:
   Cost(P) = W(P) + (0 if k1(P) is even, C if k1(P) is odd)

Objective: For every vertex v in V, compute the minimum possible Cost(P) among all valid paths from S to v. If a node v cannot be reached from S, report that it is unreachable. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
1. Mathematical Property of Weights:
   - Every edge in G has weight 0 or 1.
   - Consequently, the sum of weights along path P, W(P), is strictly identical to the count of weight-1 edges traversed: W(P) = k1(P).
   - Hence, the parity condition depends directly on whether W(P) mod 2 is 0 (even) or 1 (odd).
2. State-Space Expansion:
   - A single distance scalar per vertex is insufficient because a path with a slightly larger edge weight but even parity might yield a lower total cost than a shorter odd-weight path penalized by +C.
   - Each vertex u is split into two states:
     - (u, 0): Shortest weight to reach vertex u with an even number of weight-1 edges.
     - (u, 1): Shortest weight to reach vertex u with an odd number of weight-1 edges.
3. State Transitions:
   - For an edge u -> v with weight w in {0, 1}:
     - Transition: (u, p) -> (v, (p + w) mod 2) with edge cost w.
4. 0-1 BFS with Double-Ended Queue (Deque):
   - All transition weights in the expanded state graph belong strictly to {0, 1}.
   - Instead of using a priority queue (Dijkstra's O((V + E) log V)), a double-ended queue (deque) allows optimal O(V + E) traversal:
     - When an edge with weight 0 relaxes a distance, push the next state to the front of the deque.
     - When an edge with weight 1 relaxes a distance, push the next state to the back of the deque.
5. Final Cost Evaluation:
   - For every vertex v, the optimal path cost is:
     min(dist[v][0], dist[v][1] + C)
   - If both states remain infinity, vertex v is reported as unreachable.

---

## Algorithm
1. Represent the directed graph using array-based adjacency lists (Forward Star representation: head[], to[], weight[], and next_edge[]) to eliminate dynamic pointer overhead.
2. Read the number of vertices N, edges M, source vertex S, and penalty C.
3. Initialize distance array dist[1..N][0..1] with infinity (INF). Set dist[S][0] = 0.
4. Initialize a double-ended queue centered in an array and push (S, 0).
5. While the deque is not empty:
   - Pop (curr_u, curr_p) from the front of the deque.
   - For every outgoing edge (curr_u, v) with weight w:
     - Compute next parity next_p = (curr_p + w) % 2.
     - If dist[curr_u][curr_p] + w < dist[v][next_p]:
       - dist[v][next_p] = dist[curr_u][curr_p] + w.
       - If w == 0, push (v, next_p) to the front of the deque.
       - If w == 1, push (v, next_p) to the back of the deque.
6. For each vertex v in {1, ..., N}:
   - Compute cost_even = dist[v][0].
   - Compute cost_odd = dist[v][1] + C.
   - Select min(cost_even, cost_odd). If both are INF, mark as unreachable.
7. Print the computed minimum effective costs.

---

## Pseudocode
Algorithm ParityConstrained01BFS(V, E, S, C):
    Input: Number of vertices V, edges E, source S, penalty cost C
    Output: Minimum effective cost from S to every vertex v

    For v <- 1 to V do
        dist[v][0] <- INF
        dist[v][1] <- INF
    End For

    dist[S][0] <- 0
    Initialize empty deque Q
    PushBack(Q, (S, 0))

    While Q is not empty do
        (u, p) <- PopFront(Q)

        For each directed edge (u, v) with weight w in E do
            next_p <- (p + w) mod 2
            If dist[u][p] + w < dist[v][next_p] then
                dist[v][next_p] <- dist[u][p] + w
                If w == 0 then
                    PushFront(Q, (v, next_p))
                Else
                    PushBack(Q, (v, next_p))
                End If
            End If
        End horror/End For
    End While

    For v <- 1 to V do
        cost_even <- dist[v][0]
        cost_odd <- (dist[v][1] == INF) ? INF : dist[v][1] + C
        best_cost <- min(cost_even, cost_odd)

        If best_cost == INF then
            Print "Vertex", v, ": Unreachable"
        Else
            Print "Vertex", v, ":", best_cost
        End If
    End For
End Algorithm

---

## Complexity Analysis
1. State-Space Graph Dimensions:
   - Number of states: |V'| = 2 * |V|.
   - Number of transitions: |E'| = 2 * |E|.
2. Time Complexity:
   - Each state (u, p) enters and leaves the 0-1 BFS deque at most once when relaxed.
   - Pushing to the front (w = 0) and pushing to the back (w = 1) both take O(1) constant time.
   - Scanning outgoing edges per state takes time proportional to the degree of each node.
   - Total Time Complexity: O(|V'| + |E'|) = O(|V| + |E|).
---

## Sample Output
Enter number of vertices and edges: 4 4
Enter source vertex (1 to 4) and penalty C: 1 5
Enter 4 directed edges (u v weight) where weight is 0 or 1:
1 2 1
2 3 1
1 3 1
3 4 0

--- Minimum Effective Cost from Source 1 (Penalty C = 5) ---
Vertex	Min Cost	Details
1	0		(Even path weight = 0, penalty = 0)
2	6		(Odd path weight = 1 + penalty 5)
3	2		(Even path weight = 2, penalty = 0)
4	2		(Even path weight = 2, penalty = 0)

---

## Conclusion
By expanding the graph state into parity layers (v, parity) and recognizing that edge weights are restricted to {0, 1}, the parity-constrained shortest path problem is resolved without invoking higher-overhead priority queues. The implemented 0-1 BFS double-ended queue guarantees optimal O(|V| + |E|) time complexity while avoiding dynamic memory overhead.
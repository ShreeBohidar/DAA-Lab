# DAA Lab Assignment 10 - Question 02

## Problem Statement
[Dynamic Connected Components in a Grid] Given an R x C grid initially completely filled with water, land cells are added one by one at positions (r1, c1), (r2, c2), ..., (rk, ck). After each operation, output the current number of 4-directionally connected land components (islands). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.
[Hint: This is the Dynamic Connected Components in a Grid (commonly known as Number of Islands II), which can be solved using a Disjoint Set Union (DSU / Union-Find) data structure with coordinate flattening.]

---

## Approach
Re-evaluating connected land components after each dynamic land addition using standard graph traversal (BFS or DFS) would require O(k * R * C) time, which quickly becomes inefficient for large grids or repeated updates. Instead, an online Disjoint Set Union (DSU) maintains connected components dynamically.

1. 2D-to-1D Coordinate Flattening:
   - To treat the R x C matrix as a graph of disjoint vertices without pointer allocations, each grid cell `(r, c)` is mapped to a unique 1D index using row-major ordering:
     `flat_index = r * C + c`
2. Dynamic Component Counting:
   - The grid begins entirely as water (all zeros) with `island_count = 0`.
   - When a new land position `(r, c)` is converted to 1:
     - If it is already marked land, skip merging and retain the current component count.
     - Otherwise, tentatively treat it as a new isolated island and increment `island_count` by 1.
3. 4-Directional Neighbor Merging:
   - Examine the 4 orthogonal neighbors: North `(r - 1, c)`, South `(r + 1, c)`, West `(r, c - 1)`, and East `(r, c + 1)`.
   - For every adjacent cell within valid grid bounds that is already land:
     - Map the neighbor to its flattened index.
     - Call `union_sets(current_flat, neighbor_flat)`.
     - If the two cells belonged to different connected components, merge them and decrement `island_count` by 1.
   - Output the updated `island_count` at each step.

---

## Algorithm
1. Read the dimensions `R`, `C`, and the number of land additions `k`.
2. Initialize parent and rank arrays for all `R * C` flattened cells where `parent[i] = i` and `rank[i] = 0`.
3. Initialize the 2D grid matrix of size `R x C` to 0 (all water) and set `island_count = 0`.
4. For each land addition query `(r, c)` from 1 to `k`:
   - If `grid[r][c] == 1`, land is already present; print the unchanged `island_count`.
   - Mark `grid[r][c] = 1` and increment `island_count` by 1.
   - Compute `current_flat = r * C + c`.
   - For each orthogonal direction `(dr, dc)` in `{(-1, 0), (1, 0), (0, -1), (0, 1)}`:
     - Calculate neighbor coordinates `nr = r + dr` and `nc = c + dc`.
     - Check if `nr` is in `[0, R - 1]`, `nc` is in `[0, C - 1]`, and `grid[nr][nc] == 1`.
     - If valid, compute `neighbor_flat = nr * C + nc`.
     - Call `union_sets(current_flat, neighbor_flat)`.
     - If a union occurs between two previously separate sets, decrement `island_count` by 1.
   - Output the current `island_count`.
5. Terminate after processing all `k` additions.

---

## Pseudocode
Algorithm DynamicIslands(R, C, positions[][], k):
    Input: Grid rows R, columns C, sequence of k land cells positions
    Output: Island count after each land addition

    total_cells <- R * C
    For i <- 0 to total_cells - 1 do
        parent[i] <- i
        rank[i] <- 0
    End For

    For r <- 0 to R - 1 do
        For c <- 0 to C - 1 do
            grid[r][c] <- 0
        End For
    End For

    island_count <- 0
    dr <- [-1, 1, 0, 0]
    dc <- [0, 0, -1, 1]

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
        If root_u == root_v then
            Return False
        End If
        If rank[root_u] < rank[root_v] then
            parent[root_u] <- root_v
        Else
            parent[root_v] <- root_u
            If rank[root_u] == rank[root_v] then
                rank[root_u] <- rank[root_u] + 1
            End If
        End If
        Return True
    End Function

    For step <- 0 to k - 1 do
        r <- positions[step][0]
        c <- positions[step][1]

        If grid[r][c] == 1 then
            Print island_count
            Continue
        End If

        grid[r][c] <- 1
        island_count <- island_count + 1
        curr_flat <- r * C + c

        For d <- 0 to 3 do
            nr <- r + dr[d]
            nc <- c + dc[d]
            If nr >= 0 and nr < R and nc >= 0 and nc < C then
                If grid[nr][nc] == 1 then
                    neighbor_flat <- nr * C + nc
                    If UnionSets(curr_flat, neighbor_flat) == True then
                        island_count <- island_count - 1
                    End If
                End If
            End If
        End For

        Print island_count
    End For
End Algorithm

---

## Complexity Analysis
Let R and C be the dimensions of the grid, and k be the number of land addition operations:
1. DSU and Grid Initialization:
   - Initializing the parent and rank arrays across all R * C cells takes O(R * C) time.
   - Initializing the grid matrix to zero takes O(R * C) time.
2. Dynamic Query Processing:
   - For each land addition, exactly 4 adjacent cells are checked.
   - For each valid adjacent land cell, `FindRoot` and `UnionSets` are invoked.
   - Path compression together with union-by-rank guarantees an amortized time complexity of O(alpha(R * C)) per operation, where alpha is the inverse Ackermann function.
   - Processing all k additions takes O(k * alpha(R * C)) time.

Total Time Complexity:
T(R, C, k) = O(R * C) + O(k * alpha(R * C)) = O(R * C + k * alpha(R * C))

---

## Sample Output
Enter grid dimensions R and C: 3 3
Enter number of land additions (k): 5
Enter land coordinates sequentially (r c):
0 0
Operation 1 at (0, 0): Island count = 1
0 1
Operation 2 at (0, 1): Island count = 1
1 2
Operation 3 at (1, 2): Island count = 2
2 1
Operation 4 at (2, 1): Island count = 3
1 1
Operation 5 at (1, 1): Island count = 1

---

## Conclusion
The dynamic connected components problem in a 2D grid maps naturally to an incremental graph connectivity problem. Flattening 2D matrix coordinates into 1D scalar identifiers allows standard Disjoint Set Union primitives to maintain land island counts in real time. Rather than traversing the entire grid repeatedly, each addition runs in near-constant amortized time, providing an efficient O(R * C + k * alpha(R * C)) solution.
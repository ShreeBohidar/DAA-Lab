# DAA Lab Assignment 10 - Question 05

## Problem Statement
[Lexicographically Smallest Connected Component Permutation] Given a permutation A of numbers 1...n, and a list of allowable pairwise swaps (u, v) forming edges in an undirected graph, find the lexicographically smallest permutation achievable through any number of valid swaps. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.[cite: 1]

---

## Approach
Allowable pairwise swaps can be modeled as undirected edges between permutation index positions. The ability to perform an arbitrary number of swaps between adjacent indices implies that any positions belonging to the same connected component can be freely rearranged into any arbitrary permutation.

1. Equivalence Relation and Transitivity:
   - If position a can be swapped with b, and b can be swapped with c, then any pair among {a, b, c} can be transposed through intermediate steps without disturbing other elements.
   - Hence, swap accessibility forms an equivalence relation partitioning the indices 1...n into connected components.
2. Disjoint Set Union Partitioning:
   - A Disjoint Set Union (DSU) data structure with path compression and union-by-rank groups connected position indices together.
   - For every allowable swap query (u, v), `union_sets(u, v)` merges the components containing index u and index v.
3. Component-Wise Greedy Sorting:
   - To make the entire permutation lexicographically smallest, the smallest available values must occupy the lowest available index positions.
   - For each connected component:
     - Collect all indices belonging to the component in sorted order.
     - Collect all values residing at those indices in sorted order.
     - Assign the sorted values back into the sorted positions one by one.
   - Sorting within disjoint components independently produces the globally optimal lexicographically minimal configuration.

---

## Algorithm
1. Read the permutation size `n` and the number of allowable swap pairs `m`.
2. Read the elements of the permutation into an array `arr[]` indexed from 1 to `n`.
3. Initialize the DSU:
   - Set `parent_node[i] = i` and `rank_tree[i] = 0` for all `i` from 1 to `n`.
4. For each allowable swap pair `(u, v)` from 1 to `m`:
   - Call `union_sets(u, v)` to link the component containing index `u` with index `v`.
5. Initialize a boolean array `visited[]` of size `n + 1` to 0.
6. For each index `i` from 1 to `n`:
   - If `visited[i] == 0`:
     - Determine `root = find_root(i)`.
     - Collect all unvisited indices `j` such that `find_root(j) == root` into `comp_indices[]` and their corresponding values `arr[j]` into `comp_values[]`.
     - Mark each collected index as visited.
     - Sort `comp_indices[]` in ascending order using merge sort.
     - Sort `comp_values[]` in ascending order using merge sort.
     - Place `comp_values[k]` at position `comp_indices[k]` in the result array for each element in the component.
7. Print the final permutation stored in `result[]`.

---

## Pseudocode
Algorithm SmallestPermutation(n, m, arr[], swaps[][]):
    Input: Permutation size n, swap count m, initial array arr[], swap pairs
    Output: Lexicographically smallest permutation

    For i <- 1 to n do
        parent[i] <- i
        rank[i] <- 0
        visited[i] <- False
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
            If rank[root_u] < rank[root_v] then
                parent[root_u] <- root_v
            Else
                parent[root_v] <- root_u
                If rank[root_u] == rank[root_v] then
                    rank[root_u] <- rank[root_u] + 1
                End If
            End If
        End If
    End Function

    For k <- 0 to m - 1 do
        UnionSets(swaps[k][0], swaps[k][1])
    End For

    For i <- 1 to n do
        If visited[i] == False then
            root <- FindRoot(i)
            count <- 0

            For j <- i to n do
                If visited[j] == False and FindRoot(j) == root then
                    comp_indices[count] <- j
                    comp_values[count] <- arr[j]
                    visited[j] <- True
                    count <- count + 1
                End If
            End For

            MergeSort(comp_indices, 0, count - 1)
            MergeSort(comp_values, 0, count - 1)

            For k <- 0 to count - 1 do
                result[comp_indices[k]] <- comp_values[k]
            End For
        End If
    End For

    Print result[1 ... n]
End Algorithm

---

## Complexity Analysis
Let n be the size of the permutation and m be the number of allowable swap pairs:
1. DSU Initialization and Union Operations:
   - Initializing parent and rank arrays takes O(n) time.
   - Performing m union operations with path compression and union-by-rank takes O(m * alpha(n)) time, where alpha is the inverse Ackermann function.
2. Component Gathering:
   - Scanning for unvisited nodes across all components takes O(n * C) where C is the number of connected components, bounded by O(n^2) worst case.
3. Component-Wise Sorting:
   - For a component of size S_i, sorting indices and values with merge sort takes O(S_i * log(S_i)) time.
   - Summed over all disjoint components where sum(S_i) = n:
     Sum of O(S_i * log(S_i)) <= O(n * log(n)) time.
4. Output Construction:
   - Placing and printing the final values takes O(n) time.

Total Time Complexity:
T(n, m) = O(m * alpha(n) + n^2 + n * log(n)) = O(m * alpha(n) + n^2)

---

## Sample Output
Enter size of permutation (n) and number of allowable swaps (m): 5 3
Enter permutation of 5 elements:
5 3 1 4 2
Enter 3 allowable swap pairs (u v):
1 3
2 5
3 5

Lexicographically smallest permutation:
1 2 3 4 5

---

## Conclusion
The problem of finding the lexicographically smallest permutation under pairwise swap constraints reduces to finding connected components of graph indices. Because allowable transpositions propagate transitively, elements within the same component can be permuted arbitrarily. Partitioning indices using a Disjoint Set Union data structure and independently sorting the values into the available positions yields the optimal permutation in polynomial time.
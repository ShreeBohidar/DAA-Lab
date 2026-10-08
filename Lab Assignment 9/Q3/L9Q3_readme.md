# DAA Lab Assignment 09 - Question 3

## Problem Statement
[Minimum Initial Fuel (Reverse Greedy)] A vehicle needs to reach the target D starting with fuel F. Along the way are stations (di, fi) (distance from origin and refuel amount). What is the minimum number of refuelling stops required to reach the target? By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
To reach target distance D with the minimum number of stops, the problem can be framed using a greedy horizon-expansion strategy (often termed reverse greedy / farthest-reach greedy).

1. Horizon Expansion:
   - Starting with initial fuel F, the vehicle can cover a distance of F units without stopping.
   - All fuel stations located at distances di <= current_fuel are within reach.
2. Greedy Choice Property:
   - When the vehicle cannot reach the destination D with the currently available fuel, it must refuel at one of the stations it has already passed or can reach.
   - To minimize the total count of stops, the optimal decision at each point of fuel exhaustion is to retroactively choose the station that provides the maximum possible fuel capacity among all visited, unselected stations.
   - This expands the vehicle's driving horizon by the largest possible margin per stop.
3. Sorting and Station Tracking:
   - Stations are initially sorted in ascending order of their distance from the origin.
   - A boolean or integer array `used[]` is maintained to record which stations have already contributed their fuel.
   - If at any point the destination has not been reached and no unused reachable stations remain, the target is unreachable.

---

## Algorithm
1. Read the target distance D and the initial fuel amount F.
2. Read the number of refueling stations n.
3. Read the distance di and fuel capacity fi for each of the n stations.
4. Sort all stations in ascending order of distance di.
5. Initialize `current_fuel = F`, `stops = 0`, and mark all stations as unused (`used[i] = 0`).
6. While `current_fuel < D`:
   - Iterate through all stations i from 0 to n - 1:
     - Check if `dist[i] <= current_fuel` and `used[i] == 0`.
     - Find the station index `best_station` that maximizes `fuel[i]`.
   - If no valid station is found (`best_station == -1`):
     - The target cannot be reached; terminate and report failure.
   - Otherwise:
     - Mark `used[best_station] = 1`.
     - Add `fuel[best_station]` to `current_fuel`.
     - Increment `stops` by 1.
7. Output the minimum number of refueling stops required.

---

## Pseudocode
Algorithm MinRefuelingStops(D, F, dist[], fuel[], n):
    Input: Target distance D, initial fuel F, station arrays dist[] and fuel[], station count n
    Output: Minimum stops to reach D or -1 if unreachable

    Sort stations by dist[] in ascending order

    current_fuel <- F
    stops <- 0
    Initialize used[0..n-1] to 0

    While current_fuel < D do
        best_station <- -1
        max_fuel <- -1

        For i <- 0 to n - 1 do
            If dist[i] <= current_fuel and used[i] == 0 then
                If fuel[i] > max_fuel then
                    max_fuel <- fuel[i]
                    best_station <- i
                End If
            End If
        End For

        If best_station == -1 then
            Print "Cannot reach target"
            Return -1
        End If

        used[best_station] <- 1
        current_fuel <- current_fuel + fuel[best_station]
        stops <- stops + 1
    End While

    Print "Minimum stops: ", stops
    Return stops
End Algorithm

---

## Complexity Analysis
The overall time complexity is determined by sorting and the greedy selection loop:
1. Sorting Stations:
   - Sorting n stations by distance using bubble sort requires n * (n - 1) / 2 comparisons in the worst case, running in Θ(n^2) time.
2. Greedy Selection Loop:
   - In the worst case, the vehicle may stop at all n stations, executing the while loop at most n times.
   - In each step, scanning all n stations to identify the unused station with maximum fuel takes O(n) operations.
   - Total time spent in selection: n * O(n) = O(n^2).
3. Condition checks and additions inside the loop run in O(1) time.

Total Time Complexity:
T(n) = Θ(n^2) + O(n^2) = Θ(n^2) (or O(n log n) if using a max-heap/priority queue and MergeSort).

---

## Sample Output
Enter target distance (D) and initial fuel (F): 100 10
Enter number of refueling stations (n): 4
Enter distance and fuel for each station:
10 60
20 30
30 30
60 40

--- Journey Simulation ---
Stop 1: Refueled at station 1 (dist: 10, +60 fuel) -> New reach: 70
Stop 2: Refueled at station 4 (dist: 60, +40 fuel) -> New reach: 110

Target 100 reached successfully!
Minimum number of refueling stops required: 2

---

## Conclusion
The reverse greedy strategy solves the minimum refueling stops problem by maintaining a dynamic reachable frontier. Whenever forward progress is stalled, selecting the maximum-capacity station from within the currently reached perimeter maximizes range expansion per stop. This eliminates exponential search across subset combinations, guaranteeing an optimal solution in Θ(n^2) time.
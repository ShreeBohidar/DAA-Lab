# DAA Lab Assignment 09 - Question 8

## Problem Statement
[Minimum Number of Meeting Rooms] Given an array of meeting time intervals consisting of start and end times [[s1, e1], [s2, e2], ...], find the minimum number of conference rooms required. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## Approach
The minimum number of conference rooms required at any point equals the maximum number of concurrent/overlapping meetings happening at the same moment across the continuous timeline.

1. Chronological Event-Sweep Strategy:
   - Instead of maintaining complex room assignments or intervals as whole paired objects, meeting start and end times can be treated as discrete chronological events:
     - A meeting start event indicates an increment in room demand (+1 room).
     - A meeting end event indicates a decrement in room demand (-1 room).
2. Separate Independent Sorting:
   - All start times are extracted into an array `start[]` and all end times into an array `end[]`.
   - Both arrays are sorted independently in ascending order.
   - Decoupling start and end times preserves interval overlap correctness because an ongoing meeting only needs to be vacated by the earliest finishing meeting, regardless of which specific meeting ends first.
3. Two-Pointer Timeline Traversal:
   - Pointer `s_ptr` tracks the next meeting start, and pointer `e_ptr` tracks the earliest ending meeting.
   - If `start[s_ptr] < end[e_ptr]`: A new meeting begins before the earliest ongoing meeting concludes; increment `current_rooms` by 1 and advance `s_ptr`.
   - Else: An existing meeting concludes, freeing a room; decrement `current_rooms` by 1 and advance `e_ptr`.
   - The global maximum of `current_rooms` observed during the traversal gives the exact minimum conference rooms required.

---

## Algorithm
1. Read the total number of meetings n.
2. Read the start and end times for all n meetings into arrays `start[]` and `end[]`.
3. Sort `start[]` in ascending order.
4. Sort `end[]` in ascending order.
5. Initialize pointers `s_ptr = 0`, `e_ptr = 0`, `current_rooms = 0`, and `max_rooms = 0`.
6. While `s_ptr < n`:
   - If `start[s_ptr] < end[e_ptr]`:
     - Increment `current_rooms` by 1.
     - Update `max_rooms = max(max_rooms, current_rooms)`.
     - Increment `s_ptr` by 1.
   - Else:
     - Decrement `current_rooms` by 1.
     - Increment `e_ptr` by 1.
7. Print the resulting `max_rooms`.

---

## Pseudocode
Algorithm MinMeetingRooms(start[], end[], n):
    Input: Array start[] of start times, array end[] of end times, count n
    Output: Minimum number of conference rooms required

    Sort start[] in ascending order
    Sort end[] in ascending order

    s_ptr <- 0
    e_ptr <- 0
    current_rooms <- 0
    max_rooms <- 0

    While s_ptr < n do
        If start[s_ptr] < end[e_ptr] then
            current_rooms <- current_rooms + 1
            If current_rooms > max_rooms then
                max_rooms <- current_rooms
            End If
            s_ptr <- s_ptr + 1
        Else
            current_rooms <- current_rooms - 1
            e_ptr <- e_ptr + 1
        End If
    End While

    Print "Minimum conference rooms required: ", max_rooms
    Return max_rooms
End Algorithm

---

## Complexity Analysis
The overall time complexity is governed by sorting the time intervals and executing the linear two-pointer sweep:
1. Sorting Start and End Times:
   - Sorting array `start[]` of size n using bubble sort performs n * (n - 1) / 2 comparisons, requiring Θ(n^2) time.
   - Sorting array `end[]` of size n takes another n * (n - 1) / 2 comparisons, requiring Θ(n^2) time.
   - (Note: Using an optimal sorting algorithm like MergeSort or QuickSort reduces this step to O(n log n)).
2. Two-Pointer Chronological Sweep:
   - In each step of the while loop, at least one of the two pointers (`s_ptr` or `e_ptr`) advances by 1.
   - Pointers advance at most n times each, executing at most 2n steps.
   - Constant-time scalar increments and comparisons take O(n) total time.

Total Time Complexity:
T(n) = Θ(n^2) + Θ(n^2) + O(n) = Θ(n^2) (or O(n log n) with standard optimal sorting).

---

## Sample Output
Enter number of meetings (n): 3
Enter start and end times for 3 meetings:
0 30
5 10
15 20

--- Timeline Simulation ---
Time 0: Meeting starts -> Active rooms: 1 (Max: 1)
Time 5: Meeting starts -> Active rooms: 2 (Max: 2)
Time 10: Meeting ends   -> Active rooms: 1
Time 15: Meeting starts -> Active rooms: 2 (Max: 2)
Time 20: Meeting ends   -> Active rooms: 1
Time 30: Meeting ends   -> Active rooms: 0

Minimum number of conference rooms required: 2

---

## Conclusion
By modeling meeting intervals as distinct chronological boundary events, the meeting room problem is solved via an event-sweep greedy approach. Sorting start and end points independently permits a simultaneous two-pointer scan that tracks concurrent resource demands in optimal Θ(n^2) (or O(n log n)) time, eliminating the overhead of tracking complex room assignment permutations.
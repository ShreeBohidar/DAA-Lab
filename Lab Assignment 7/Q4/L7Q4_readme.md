# DAA Lab Assignment 07 - Question 4

## Problem Statement
[Security switches] There is a row of n security switches protecting a military installation entrance. The switches can be manipulated as follows:
(i) The rightmost switch may be turned on or off at will.
(ii) Any other switch may be turned on or off only if the switch to its immediate right is on and all the other switches to its right, if any, are off.
(iii) Only one switch may be toggled at a time.
Devise an algorithm to turn off all the switches, which are initially all on, in the minimum number of moves. (Toggling one switch is considered one move.)

By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## Approach
This puzzle is isomorphic to the classic Baguenaudier (Chinese Rings) problem and Gray Code sequence transitions.

Let the switches be numbered 1 to n from right to left (Switch 1 is the rightmost, Switch n is the leftmost).
According to the rules:
- Switch 1 can toggle freely at any time.
- Switch k (where k > 1) can only toggle if switch (k - 1) is ON and all switches from 1 to (k - 2) are OFF.

To turn off switches 1 through k when all are currently ON:
1. Turn off switches 1 through (k - 2). This leaves switch (k - 1) ON and all switches to the right of (k - 1) OFF.
2. Toggle switch k from ON to OFF.
3. Turn on switches 1 through (k - 2) so that we have the configuration required to systematically turn off switch (k - 1).
4. Turn off switches 1 through (k - 1).

To turn on switches 1 through k when all are currently OFF:
1. Turn on switches 1 through (k - 1).
2. Turn off switches 1 through (k - 2) so only switch (k - 1) remains ON.
3. Toggle switch k from OFF to ON.
4. Turn on switches 1 through (k - 2).

This mutual recursion ensures every move strictly adheres to the physical switch constraints while minimizing the total toggles.

---

## Algorithm
1. Read the total number of switches (n).
2. Validate that n is a positive integer.
3. Define recursive procedure `set_off(k)`:
   - If k <= 0, return.
   - If k == 1, toggle switch 1 and return.
   - Call `set_off(k - 2)`.
   - Toggle switch k.
   - Call `set_on(k - 2)`.
   - Call `set_off(k - 1)`.
4. Define recursive procedure `set_on(k)`:
   - If k <= 0, return.
   - If k == 1, toggle switch 1 and return.
   - Call `set_on(k - 1)`.
   - Call `set_off(k - 2)`.
   - Toggle switch k.
   - Call `set_on(k - 2)`.
5. Execute `set_off(n)` to transition all n switches from ON to OFF.
6. Print the total count of toggle operations performed.

---

## Pseudocode
Algorithm SecuritySwitches(n):
    Input: Positive integer n (number of switches, initially all ON)
    Output: Sequence of switch toggles to turn all switches OFF

    moves <- 0

    Procedure SetOff(k):
        If k <= 0 then
            Return
        End If
        If k = 1 then
            moves <- moves + 1
            Print "Move ", moves, ": Toggle switch 1"
            Return
        End If

        SetOff(k - 2)
        moves <- moves + 1
        Print "Move ", moves, ": Toggle switch ", k
        SetOn(k - 2)
        SetOff(k - 1)
    End Procedure

    Procedure SetOn(k):
        If k <= 0 then
            Return
        End If
        If k = 1 then
            moves <- moves + 1
            Print "Move ", moves, ": Toggle switch 1"
            Return
        End If

        SetOn(k - 1)
        SetOff(k - 2)
        moves <- moves + 1
        Print "Move ", moves, ": Toggle switch ", k
        SetOn(k - 2)
    End Procedure

    SetOff(n)
    Print "Total moves: ", moves
End Algorithm

---

## Complexity Analysis
Let F(k) be the number of moves to turn off k switches, and G(k) be the number of moves to turn on k switches.
By the structure of the recursive procedures:
- F(k) = F(k - 2) + 1 + G(k - 2) + F(k - 1)
- G(k) = G(k - 1) + F(k - 2) + 1 + G(k - 2)

By symmetry between turning switches on and off:
F(k) = G(k)

Substituting this into the recurrence:
F(k) = F(k - 1) + 2 * F(k - 2) + 1

The characteristic equation for the homogeneous part is:
r^2 - r - 2 = 0
(r - 2)(r + 1) = 0
giving roots r = 2 and r = -1.

Solving with initial conditions F(1) = 1 and F(2) = 2 yields the closed form:
- For even n: F(n) = (2^(n + 1) - 2) / 3
- For odd n:  F(n) = (2^(n + 1) - 1) / 3

Therefore, the total number of operations is proportional to 2^n.
Total Time Complexity:
T(n) = O(2^n)

---

## Sample Output
Enter number of switches (n): 4

Solution moves:
Move 1: Toggle switch 2
Move 2: Toggle switch 1
Move 3: Toggle switch 4
Move 4: Toggle switch 1
Move 5: Toggle switch 2
Move 6: Toggle switch 1
Move 7: Toggle switch 3
Move 8: Toggle switch 1
Move 9: Toggle switch 2
Move 10: Toggle switch 1

Total moves: 10

---

## Conclusion
To turn off all n switches initially in the ON state, the minimum number of moves is (2^(n + 1) - 2) / 3 for even n and (2^(n + 1) - 1) / 3 for odd n. For n = 4, the exact minimum sequence requires 10 moves. The mutual recursion ensures full compliance with the adjacent-switch dependency while achieving exponential O(2^n) optimality.
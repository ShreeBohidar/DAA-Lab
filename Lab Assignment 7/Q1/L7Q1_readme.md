# DAA Lab Assignment 07 - Question 1

## Problem Statement
[Invert the coin-triangle] Consider an equilateral triangle formed by closely packed pennies or other identical coins like the one shown in Figure 1. (The centers of the coins are assumed to be at the points of the equilateral triangular lattice.) Design an algorithm to flip the triangle upside down in the minimum number of moves if on each move you can slide one coin at a time to its new position. Give a compact formula for the number of minimum moves.

Figure 1: Coin-triangle that needs to be inverted

By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## Approach
An equilateral coin triangle with side length n contains T(n) = n * (n + 1) / 2 coins arranged in rows of 1, 2, ..., n coins.

To invert the triangle (turn it upside down) with the minimum number of moves, we must find the maximum number of coins that can remain stationary. The stationary coins form a smaller upright sub-structure or hexagon-like overlap within the inverted boundary.

By analyzing the overlap of the original upright triangle of side n and an inverted triangle of side n:
- The maximum number of coins that can remain unmoved leaves a remainder of coins to be relocated equal to floor(n * (n + 1) / 6).
- Thus, the minimum number of coin moves is derived using integer division:
  min_moves = (n * (n + 1)) / 6

---

## Algorithm
1. Read the number of rows (n) representing the side of the coin triangle.
2. Validate that n is a positive integer.
3. Compute the total number of coins using the triangular number formula:
   total_coins = (n * (n + 1)) / 2
4. Compute the minimum moves required to invert the triangle using integer arithmetic:
   min_moves = (n * (n + 1)) / 6
5. Display the calculated total coins and the minimum moves required.

---

## Pseudocode
Algorithm InvertCoinTriangle(n):
    Input: Positive integer n (number of rows in the coin triangle)
    Output: Minimum moves required to flip the triangle upside down

    If n <= 0 then
        Print "Number of rows must be positive."
        Return
    End If

    total_coins <- (n * (n + 1)) / 2
    min_moves <- (n * (n + 1)) / 6

    Print "Total number of coins: ", total_coins
    Print "Minimum moves required to invert the triangle: ", min_moves
End Algorithm

---

## Complexity Analysis
The time complexity is determined by the basic arithmetic operations executed:
1. Input reading takes O(1) time.
2. Arithmetic operations:
   - One addition: (n + 1)
   - One multiplication: n * (n + 1)
   - Two integer divisions: division by 2 and division by 6
3. Each of these basic operations is performed on fixed-width machine integers and runs in O(1) constant time.
4. Printing the output takes O(1) time.

Total Time Complexity:
T(n) = O(1) + O(1) + O(1) = O(1)

Therefore, the algorithm executes in strictly O(1) constant time.

---

## Sample Output
Enter the number of rows in the coin triangle (n): 4
Total number of coins: 10
Minimum moves required to invert the triangle: 3

---

## Conclusion
The compact formula for the minimum number of moves required to invert an n-row coin triangle is floor(n * (n + 1) / 6). For the 4-row (10-coin) triangle shown in the problem, sliding exactly 3 coins turns the triangle upside down. This mathematical relation eliminates the need for geometric simulation, providing an instant solution in constant time.
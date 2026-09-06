DAA Lab Assignment 06 - Question 1

Problem Statement:
1. 1D array operations and their complexities: Given an array with n unsorted integer elements, what is the worst-case complexity of the following problems in terms of n:
(i) Finding the maximum element.
(ii) Finding the first and second largest elements.
(iii) Finding the mean.
(iv) Finding the median.
(v) Finding the standard deviation.
(vi) Finding the mode.
(vii) Removing all duplicates.
(viii) Reversing the elements of the array.
(ix) Partitioning the array with respect to a given random pivot element so that all elements less than the pivot appear after all the elements greater than or equal to the pivot.
By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.

The Approach:
- Input Representation: A 1D integer array along with an integer n specifying the total number of elements.
- (i) Maximum: Traverse the array linearly from index 1 to n-1 while updating a running maximum variable.
- (ii) First and Second Largest: Perform a single linear scan maintaining two variables (first and second), updating them appropriately when larger elements are found.
- (iii) Mean: Traverse the array once to calculate the sum of all elements, then divide by n.
- (iv) Median: Create a copy of the array, sort it using standard Bubble Sort, and pick the middle element if n is odd, or the average of the two middle elements if n is even.
- (v) Standard Deviation: Compute the mean first, make a second pass to sum the squared differences from the mean, divide by n, and compute the square root.
- (vi) Mode: Use two nested loops to count the frequency of each element across the array, tracking the value with the highest frequency.
- (vii) Removing Duplicates: Scan each element of the array and insert it into a unique list only if it is not already present in the list.
- (viii) Reversing: Use two indices (left starting at 0, right starting at n-1) and swap elements moving towards the center.
- (ix) Partitioning: First copy all elements greater than or equal to the pivot into a temporary array, then copy all elements strictly less than the pivot, and finally copy them back.

Algorithm:
1. FindMax(A, n):
   - Set max = A[0].
   - For i from 1 to n - 1: if A[i] > max, set max = A[i].
   - Return max.

2. FindFirstAndSecond(A, n):
   - Set first = A[0], second = -1000000.
   - For i from 1 to n - 1:
       if A[i] > first: set second = first, first = A[i].
       else if A[i] > second and A[i] != first: set second = A[i].
   - Return first, second.

3. FindMean(A, n):
   - Set sum = 0.
   - For i from 0 to n - 1: sum = sum + A[i].
   - Return sum / n.

4. FindMedian(A, n):
   - Copy array A to temp.
   - Sort temp using Bubble Sort.
   - If n % 2 != 0: return temp[n / 2].
   - Else: return (temp[(n / 2) - 1] + temp[n / 2]) / 2.0.

5. FindStandardDeviation(A, n):
   - Calculate mean = FindMean(A, n).
   - Set sumSq = 0.
   - For i from 0 to n - 1: sumSq = sumSq + (A[i] - mean)^2.
   - Return sqrt(sumSq / n).

6. FindMode(A, n):
   - Set maxCount = 0, modeVal = A[0].
   - For i from 0 to n - 1:
       Set count = 0.
       For j from 0 to n - 1:
           if A[j] == A[i]: count = count + 1.
       If count > maxCount: maxCount = count, modeVal = A[i].
   - Return modeVal.

7. RemoveDuplicates(A, n):
   - Set uniqueCount = 0.
   - For i from 0 to n - 1:
       Check if A[i] exists in unique array.
       If not found: unique[uniqueCount] = A[i], uniqueCount = uniqueCount + 1.
   - Copy unique array back to A and return uniqueCount.

8. ReverseArray(A, n):
   - Set start = 0, end = n - 1.
   - While start < end:
       Swap A[start] and A[end].
       Increment start, decrement end.

9. PartitionArray(A, n, pivot):
   - Set index = 0.
   - For i from 0 to n - 1: if A[i] >= pivot, temp[index++] = A[i].
   - For i from 0 to n - 1: if A[i] < pivot, temp[index++] = A[i].
   - Copy temp back to A.

Pseudocode:
FUNCTION findMaximum(A, n):
    maxVal = A[0]
    FOR i = 1 TO n - 1:
        IF A[i] > maxVal THEN maxVal = A[i]
    RETURN maxVal

FUNCTION findFirstAndSecondLargest(A, n):
    first = A[0], second = -1000000
    FOR i = 1 TO n - 1:
        IF A[i] > first:
            second = first
            first = A[i]
        ELSE IF A[i] > second AND A[i] != first:
            second = A[i]
    PRINT first, second

FUNCTION findMean(A, n):
    sum = 0
    FOR i = 0 TO n - 1:
        sum = sum + A[i]
    RETURN sum / n

FUNCTION findMedian(A, n):
    Copy A to temp
    FOR i = 0 TO n - 2:
        FOR j = 0 TO n - i - 2:
            IF temp[j] > temp[j + 1] THEN SWAP(temp[j], temp[j + 1])
    IF n % 2 != 0:
        RETURN temp[n / 2]
    ELSE:
        RETURN (temp[(n / 2) - 1] + temp[n / 2]) / 2.0

FUNCTION findStandardDeviation(A, n):
    mean = findMean(A, n)
    sumSq = 0
    FOR i = 0 TO n - 1:
        sumSq = sumSq + (A[i] - mean) * (A[i] - mean)
    RETURN sqrt(sumSq / n)

FUNCTION findMode(A, n):
    maxCount = 0, modeVal = A[0]
    FOR i = 0 TO n - 1:
        count = 0
        FOR j = 0 TO n - 1:
            IF A[j] == A[i] THEN count = count + 1
        IF count > maxCount:
            maxCount = count
            modeVal = A[i]
    RETURN modeVal

FUNCTION removeDuplicates(A, n):
    uniqueCount = 0
    FOR i = 0 TO n - 1:
        isDuplicate = 0
        FOR j = 0 TO uniqueCount - 1:
            IF A[i] == unique[j]:
                isDuplicate = 1
                BREAK
        IF isDuplicate == 0:
            unique[uniqueCount] = A[i]
            uniqueCount = uniqueCount + 1
    FOR i = 0 TO uniqueCount - 1:
        A[i] = unique[i]
    RETURN uniqueCount

FUNCTION reverseArray(A, n):
    start = 0, end = n - 1
    WHILE start < end:
        SWAP(A[start], A[end])
        start = start + 1
        end = end - 1

FUNCTION partitionArray(A, n, pivot):
    index = 0
    FOR i = 0 TO n - 1:
        IF A[i] >= pivot:
            temp[index] = A[i]
            index = index + 1
    FOR i = 0 TO n - 1:
        IF A[i] < pivot:
            temp[index] = A[i]
            index = index + 1
    FOR i = 0 TO n - 1:
        A[i] = temp[i]

Complexity Analysis:
(i) Finding maximum element:
    T(n) = c * (n - 1)
    T(n) = O(n)
    Derivation: One loop runs exactly (n - 1) times with constant work per iteration.

(ii) Finding first and second largest elements:
    T(n) <= 2 * c * (n - 1)
    T(n) = O(n)
    Derivation: In the worst case, each element is compared up to 2 times in a single linear traversal of length (n - 1).

(iii) Finding mean:
    T(n) = c * n + c_div
    T(n) = O(n)
    Derivation: One loop runs n times to sum elements, followed by 1 division.

(iv) Finding median:
    T(n) = c * (n * (n - 1)) / 2
    T(n) = O(n^2)
    Derivation: Sorting an unsorted array using Bubble Sort executes (n - 1) passes, resulting in n*(n - 1)/2 total comparisons in the worst case.

(v) Finding standard deviation:
    T(n) = T_mean(n) + c * n + c_sqrt
    T(n) = O(n) + O(n) = O(n)
    Derivation: Computing the mean requires O(n) time, and computing the sum of squared differences requires a second loop of n steps.

(vi) Finding mode:
    T(n) = c * n * n
    T(n) = O(n^2)
    Derivation: For each of the n elements, an inner loop runs n times to count its occurrences.

(vii) Removing all duplicates:
    T(n) = c * (0 + 1 + 2 + ... + (n - 1))
    T(n) = c * (n * (n - 1)) / 2
    T(n) = O(n^2)
    Derivation: In the worst case where all elements are distinct, the inner check executes 0 + 1 + 2 + ... + (n - 1) comparisons.

(viii) Reversing the elements:
    T(n) = c * (n / 2)
    T(n) = O(n)
    Derivation: The two-pointer loop executes exactly floor(n / 2) iterations, swapping two elements per step.

(ix) Partitioning the array:
    T(n) = c1 * n + c2 * n + c3 * n
    T(n) = (c1 + c2 + c3) * n
    T(n) = O(n)
    Derivation: There are three linear scans of length n: one for elements >= pivot, one for elements < pivot, and one copy-back pass.

Sample Output:
Enter number of elements: 6
Enter 6 integers:
12 5 8 12 3 9

--- Array Operations ---
(i) Maximum Element: 12
(ii) First Largest: 12
Second Largest: 9
(iii) Mean: 8.17
(iv) Median: 8.50
(v) Standard Deviation: 3.48
(vi) Mode: 12
(vii) Array after removing duplicates: 12 5 8 3 9 
(viii) Reversed Array: 9 3 12 8 5 12 
Enter pivot element for partitioning: 8
(ix) Partitioned Array (elements >= 8 first, then < 8): 12 8 12 9 5 3 

Conclusion:
The worst-case computational time complexities for the given unsorted 1D array operations are:
- (i) Maximum element: O(n)
- (ii) First and second largest elements: O(n)
- (iii) Mean: O(n)
- (iv) Median: O(n^2)
- (v) Standard deviation: O(n)
- (vi) Mode: O(n^2)
- (vii) Removing duplicates: O(n^2)
- (viii) Reversing elements: O(n)
- (ix) Partitioning array: O(n)
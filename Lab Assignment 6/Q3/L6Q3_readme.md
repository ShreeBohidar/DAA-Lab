DAA Lab Assignment 06 - Question 3

Problem Statement:
3. Convolution operation on vectors of size n: The convolution of two vectors A and B is a new vector C such that
C[k] = sum_{j=0}^{m-1} A[j] * B[k-j]
Assuming the lengths of A and B are of length m and n, respectively, and the indexing of the vectors starts from 0, find an O(n log n) divide and conquer algorithm for this operation. Consider, n >= m for your implementation and analysis.
By choosing the proper input representation, write a program in C to validate your algorithm.

The Approach:
- Direct polynomial multiplication (convolution) requires O(m * n) = O(n^2) operations. To achieve the required O(n log n) time complexity, the convolution theorem is utilized via Fast Fourier Transform (FFT).
- The total length of the resulting convolution vector C is totalLen = m + n - 1.
- Both input vectors are zero-padded to the smallest power of 2, denoted by N, such that N >= totalLen.
- The Cooley-Tukey Radix-2 Divide and Conquer algorithm is applied to compute the Discrete Fourier Transform (DFT) of both vectors in O(N log N) time by recursively splitting the sequence into even-indexed and odd-indexed terms.
- Pointwise multiplication of the transformed sequences is computed in O(N) time.
- The Inverse Fast Fourier Transform (IFFT) is performed on the pointwise product in O(N log N) time to retrieve the convolved sequence in the time domain, which is then truncated to the original length totalLen.
- Input validation is enforced to guarantee that n >= m before performing any computation.

Algorithm:
1. FFT(a, n, invert):
   - If n <= 1, return.
   - Separate array a into even-indexed elements a0 and odd-indexed elements a1 of size n / 2.
   - Recursively call FFT(a0, n / 2, invert) and FFT(a1, n / 2, invert).
   - Set angle = 2 * PI / n * (-1 if invert else 1).
   - Initialize twiddle factor w = 1 + 0i and step wn = cos(angle) + i * sin(angle).
   - For i from 0 to n / 2 - 1:
       prod = Mul(w, a1[i])
       a[i] = Add(a0[i], prod)
       a[i + n / 2] = Sub(a0[i], prod)
       If invert is true:
           a[i].real = a[i].real / 2, a[i].imag = a[i].imag / 2
           a[i + n / 2].real = a[i + n / 2].real / 2, a[i + n / 2].imag = a[i + n / 2].imag / 2
       w = Mul(w, wn)

2. ConvolveFFT(A, m, B, n, C, totalLen):
   - Find smallest power of 2, N >= totalLen.
   - Construct complex array fa of size N filled with A[0...m-1] and padded with zeros.
   - Construct complex array fb of size N filled with B[0...n-1] and padded with zeros.
   - Call FFT(fa, N, 0) and FFT(fb, N, 0).
   - For i from 0 to N - 1: fa[i] = Mul(fa[i], fb[i]).
   - Call FFT(fa, N, 1) (Inverse FFT).
   - Copy real parts fa[0...totalLen-1] into array C.

Pseudocode:
FUNCTION fft(a, n, invert):
    IF n <= 1 THEN RETURN
    FOR i = 0 TO (n / 2) - 1:
        a0[i] = a[2 * i]
        a1[i] = a[2 * i + 1]
    fft(a0, n / 2, invert)
    fft(a1, n / 2, invert)
    ang = 2 * PI / n * (invert ? -1 : 1)
    w = 1.0 + 0.0i
    wn = cos(ang) + sin(ang)i
    FOR i = 0 TO (n / 2) - 1:
        prod = Mul(w, a1[i])
        a[i] = Add(a0[i], prod)
        a[i + n / 2] = Sub(a0[i], prod)
        IF invert == TRUE THEN:
            a[i].real = a[i].real / 2.0
            a[i].imag = a[i].imag / 2.0
            a[i + n / 2].real = a[i + n / 2].real / 2.0
            a[i + n / 2].imag = a[i + n / 2].imag / 2.0
        w = Mul(w, wn)

FUNCTION convolveFFT(A, m, B, n, C, totalLen):
    N = 1
    WHILE N < totalLen:
        N = N * 2
    FOR i = 0 TO N - 1:
        fa[i].real = (i < m) ? A[i] : 0
        fa[i].imag = 0
        fb[i].real = (i < n) ? B[i] : 0
        fb[i].imag = 0
    fft(fa, N, 0)
    fft(fb, N, 0)
    FOR i = 0 TO N - 1:
        fa[i] = Mul(fa[i], fb[i])
    fft(fa, N, 1)
    FOR i = 0 TO totalLen - 1:
        C[i] = fa[i].real

Complexity Analysis:
- Power of Two Zero-Padding:
  Since n >= m, the length of the result is totalLen = m + n - 1 <= 2n.
  The smallest power of two N >= totalLen satisfies N < 2 * (2n) = 4n.
  Hence, N = Theta(n).

- Divide-and-Conquer Recurrence Relation:
  At each recursion level, an array of size N is divided into two halves of size N / 2, and the combination step (butterfly operations) executes in linear time c * N:
  T(N) = 2 * T(N / 2) + c * N

- Solving Recurrence via Master Theorem:
  Comparing with T(N) = a * T(N / b) + f(N):
  a = 2, b = 2, f(N) = c * N
  N^(log_b a) = N^(log_2 2) = N^1
  Since f(N) = Theta(N^1), it satisfies Case 2 of the Master Theorem:
  T(N) = Theta(N * log N).

- Overall Time Complexity:
  T_total(n) = T_FFT(fa) + T_FFT(fb) + T_PointwiseMul + T_IFFT(fa)
  T_total(n) = O(N log N) + O(N log N) + O(N) + O(N log N)
  T_total(n) = O(N log N)
  Substituting N = Theta(n):
  T_total(n) = O(n log n).

Sample Output:
Enter size of vector A (m): 3
Enter size of vector B (n, such that n >= m): 4
Enter 3 elements of vector A:
1 2 3
Enter 4 elements of vector B:
4 5 6 7

 Convolution Vector C (size 6) 
C[0] = 4.00
C[1] = 13.00
C[2] = 28.00
C[3] = 34.00
C[4] = 32.00
C[5] = 21.00

Conclusion:
The convolution of two vectors of sizes m and n (where n >= m) is successfully implemented using the divide-and-conquer Fast Fourier Transform (Cooley-Tukey algorithm).
The direct discrete convolution method requires O(m * n) = O(n^2) operations. By transforming the sequences into their frequency-domain point-value representation, performing pointwise multiplication in linear time, and inverting back via IFFT, the overall worst-case computational time complexity is reduced to O(n log n).
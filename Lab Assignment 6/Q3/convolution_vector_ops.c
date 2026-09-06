#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double real;
    double imag;
} Complex;

Complex Add(Complex a, Complex b) {
    Complex res;
    res.real = a.real + b.real;
    res.imag = a.imag + b.imag;
    return res;
}

Complex Sub(Complex a, Complex b) {
    Complex res;
    res.real = a.real - b.real;
    res.imag = a.imag - b.imag;
    return res;
}

Complex Mul(Complex a, Complex b) {
    Complex res;
    res.real = (a.real * b.real) - (a.imag * b.imag);
    res.imag = (a.real * b.imag) + (a.imag * b.real);
    return res;
}

void fft(Complex a[], int n, int invert) {
    int i;
    if (n <= 1) {
        return;
    }

    Complex a0[256];
    Complex a1[256];

    for (i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    double ang = 2.0 * PI / n * (invert ? -1 : 1);
    Complex w;
    w.real = 1.0;
    w.imag = 0.0;

    Complex wn;
    wn.real = cos(ang);
    wn.imag = sin(ang);

    for (i = 0; 2 * i < n; i++) {
        Complex prod = Mul(w, a1[i]);
        a[i] = Add(a0[i], prod);
        a[i + n / 2] = Sub(a0[i], prod);

        if (invert) {
            a[i].real = a[i].real / 2.0;
            a[i].imag = a[i].imag / 2.0;
            a[i + n / 2].real = a[i + n / 2].real / 2.0;
            a[i + n / 2].imag = a[i + n / 2].imag / 2.0;
        }

        w = Mul(w, wn);
    }
}

void convolveFFT(double A[], int m, double B[], int n, double C[], int totalLen) {
    int N = 1;
    while (N < totalLen) {
        N = N * 2;
    }

    Complex fa[512];
    Complex fb[512];
    int i;

    for (i = 0; i < N; i++) {
        if (i < m) {
            fa[i].real = A[i];
        } else {
            fa[i].real = 0.0;
        }
        fa[i].imag = 0.0;

        if (i < n) {
            fb[i].real = B[i];
        } else {
            fb[i].real = 0.0;
        }
        fb[i].imag = 0.0;
    }

    fft(fa, N, 0);
    fft(fb, N, 0);

    for (i = 0; i < N; i++) {
        fa[i] = Mul(fa[i], fb[i]);
    }

    fft(fa, N, 1);

    for (i = 0; i < totalLen; i++) {
        C[i] = fa[i].real;
    }
}

int main() {
    int m, n, i;
    double A[100];
    double B[100];
    double C[200];

    printf("Enter size of vector A (m): ");
    scanf("%d", &m);

    printf("Enter size of vector B (n, such that n >= m): ");
    scanf("%d", &n);

    while (n < m) {
        printf("Invalid input! Condition requires n >= m. Please re-enter n: ");
        scanf("%d", &n);
    }

    printf("Enter %d elements of vector A:\n", m);
    for (i = 0; i < m; i++) {
        scanf("%lf", &A[i]);
    }

    printf("Enter %d elements of vector B:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    int totalLen = n + m - 1;

    convolveFFT(A, m, B, n, C, totalLen);

    printf("\n Convolution Vector C (size %d) \n", totalLen);
    for (i = 0; i < totalLen; i++) {
        printf("C[%d] = %.2f\n", i, C[i]);
    }

    return 0;
}

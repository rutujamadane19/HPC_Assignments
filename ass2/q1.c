#include <stdio.h>
#include <omp.h>

void vector_scalar_addition(int *vector, int scalar, int n) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int n = 100000;  // Size of the vector
    int scalar = 5;  // Scalar to be added
    int vector[n];

    // Initialize vector
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    // Perform vector-scalar addition
    vector_scalar_addition(vector, scalar, n);

    // Print first 10 elements to verify
    for (int i = 0; i < 10; i++) {
        printf("%d ", vector[i]);
    }

    return 0;
}

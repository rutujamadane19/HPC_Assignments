#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void vector_scalar_addition(int *vector, int scalar, int n) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int n = 100000000;  // Large size of the vector
    int scalar = 5;

    // Allocate memory for the vector dynamically
    int *vector = (int *)malloc(n * sizeof(int));
    if (vector == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize vector
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    double start_time, end_time;

    for (int threads = 1; threads <= 8; threads *= 2) {
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        vector_scalar_addition(vector, scalar, n);
        
        end_time = omp_get_wtime();
        printf("Time with %d threads: %f seconds\n", threads, end_time - start_time);
    }

    // Free allocated memory
    free(vector);

    return 0;
}


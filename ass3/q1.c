#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compare two integers for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to compute the minimum scalar product using OpenMP
int min_scalar_product(int *a, int *b, int n) {
    // Sort vector a in ascending order
    qsort(a, n, sizeof(int), compare);
    
    // Sort vector b in descending order
    qsort(b, n, sizeof(int), compare);
    for (int i = 0; i < n / 2; i++) {
        int temp = b[i];
        b[i] = b[n - 1 - i];
        b[n - 1 - i] = temp;
    }

    int min_product = 0;

    #pragma omp parallel for reduction(+:min_product) schedule(static)
    for (int i = 0; i < n; i++) {
        min_product += a[i] * b[i];
    }

    return min_product;
}

int main() {
    int n = 1000000; // Size of vectors
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    // Initialize vectors with random values
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    double start_time, end_time;

    // Measure the execution time
    start_time = omp_get_wtime();
    int result = min_scalar_product(a, b, n);
    end_time = omp_get_wtime();

    printf("Minimum Scalar Product: %d\n", result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    // Clean up
    free(a);
    free(b);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int **a, int **b, int **c, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};  // Different matrix sizes
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        
        // Allocate memory for matrices
        int **a = (int **)malloc(n * sizeof(int *));
        int **b = (int **)malloc(n * sizeof(int *));
        int **c = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            a[i] = (int *)malloc(n * sizeof(int));
            b[i] = (int *)malloc(n * sizeof(int));
            c[i] = (int *)malloc(n * sizeof(int));
        }
        
        // Initialize matrices with random values
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand() % 100;
                b[i][j] = rand() % 100;
                c[i][j] = 0;
            }
        }

        printf("Matrix size: %dx%d\n", n, n);

        for (int threads = 1; threads <= 8; threads *= 2) {
            omp_set_num_threads(threads);
            
            double start_time = omp_get_wtime();
            matrix_addition(a, b, c, n);
            double end_time = omp_get_wtime();

            double time_taken = end_time - start_time;
            printf("Threads: %d, Time taken: %f seconds\n", threads, time_taken);
        }

        // Free memory
        for (int i = 0; i < n; i++) {
            free(a[i]);
            free(b[i]);
            free(c[i]);
        }
        free(a);
        free(b);
        free(c);
    }

    return 0;
}

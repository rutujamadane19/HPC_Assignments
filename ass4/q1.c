#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int x, y;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                x = fibonacci(n-1);
            }
            #pragma omp section
            {
                y = fibonacci(n-2);
            }
        }
        
        return x + y;
    }
}

int main() {
    int n = 20; // Fibonacci number to compute
    int result;

    double start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    double end_time = omp_get_wtime();

    printf("Fibonacci of %d is %d\n", n, result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}

#include <omp.h>
#include <stdio.h>

int main() {
    int num_threads;

    // Ask the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Print 'Hello, World' sequentially
    printf("Sequential Execution:\n");
    for(int i = 0; i < num_threads; i++) {
        printf("Hello, World\n");
    }

    // Print 'Hello, World' in parallel
    printf("\nParallel Execution:\n");
    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }

    return 0;
}

#include <stdio.h>
#include <omp.h>

double calculate_pi(int num_steps) {
    double step = 1.0 / (double) num_steps;
    double sum = 0.0;
    int i;

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

int main() {
    int num_steps = 1000000000;  // Large number of steps
    double start_time, end_time;

    for (int threads = 1; threads <= 8; threads *= 2) {
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        double pi = calculate_pi(num_steps);
        
        end_time = omp_get_wtime();
        printf("Time with %d threads: %f seconds, Pi: %f\n", threads, end_time - start_time, pi);
    }

    return 0;
}

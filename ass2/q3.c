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
    int num_steps = 1000000;
    double pi = calculate_pi(num_steps);
    printf("Calculated value of Pi: %f\n", pi);
    return 0;
}

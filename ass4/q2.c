#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer
int in = 0;     // Points to the next free position in the buffer
int out = 0;    // Points to the next item to be consumed

omp_lock_t lock;  // Lock to protect buffer access

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        omp_set_lock(&lock);  // Acquire lock
        
        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            omp_unset_lock(&lock);  // Release lock
            // Wait a bit to avoid busy waiting
            // Optionally: sleep(1) or usleep(1000);
            omp_set_lock(&lock);  // Reacquire lock
        }

        // Add item to the buffer
        buffer[in] = i;
        printf("Producer %d produced %d at position %d\n", id, i, in);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        omp_unset_lock(&lock);  // Release lock
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        omp_set_lock(&lock);  // Acquire lock
        
        // Wait if the buffer is empty
        while (count == 0) {
            omp_unset_lock(&lock);  // Release lock
            // Wait a bit to avoid busy waiting
            // Optionally: sleep(1) or usleep(1000);
            omp_set_lock(&lock);  // Reacquire lock
        }

        // Consume item from the buffer
        int item = buffer[out];
        printf("Consumer %d consumed %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        omp_unset_lock(&lock);  // Release lock
    }
}

int main() {
    omp_init_lock(&lock);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer(1);
        }
        #pragma omp section
        {
            consumer(1);
        }
    }

    omp_destroy_lock(&lock);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex, resource;
int readers_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    
    while (1) {
        // Entering critical section
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&resource); // Block writers if it's the first reader
        }
        sem_post(&mutex);

        // Reading from the resource
        printf("Reader %d is reading\n", id);

        // Exiting critical section
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&resource); // Unblock writers if no readers
        }
        sem_post(&mutex);

        // Simulate reading time
        usleep(rand() % 1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    
    while (1) {
        // Entering critical section
        sem_wait(&resource); // Wait for exclusive access
        // Writing to the resource
        printf("Writer %d is writing\n", id);
        // Exiting critical section
        sem_post(&resource); // Release resource

        // Simulate writing time
        usleep(rand() % 1000000);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&resource, 0, 1);
    
    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&resource);
    
    return 0;
}


// gcc rw.c -o rw -lpthread -lrt

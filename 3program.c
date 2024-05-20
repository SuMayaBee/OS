#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // For memset in some environments

// Global flag to control thread execution
volatile sig_atomic_t run_thread = 1;

// Function to be executed by the thread
void* thread_function(void* arg) {
    while (run_thread) {
        printf("Thread is running...\n");
        sleep(1);  // Simulate work by sleeping for 1 second
    }
    printf("Thread is exiting...\n");
    pthread_exit(NULL);
}

// Signal handler
void handle_sigint(int sig) {
    printf("SIGINT received, stopping the program...\n");
    run_thread = 0;  // Set the flag to stop the thread
}

int main() {
    pthread_t thread_id;
    struct sigaction sa;

    // Ensure the sigaction struct is zeroed out
    memset(&sa, 0, sizeof(sa));

    // Set up the structure to handle SIGINT
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register the signal handler
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("Failed to set signal handler");
        return EXIT_FAILURE;
    }

    // Create the thread
    if (pthread_create(&thread_id, NULL, thread_function, NULL) != 0) {
        perror("Failed to create the thread");
        return EXIT_FAILURE;
    }

    // Wait for the thread to finish
    pthread_join(thread_id, NULL);
    printf("Main program is exiting...\n");

    return EXIT_SUCCESS;
}


// gcc program.c -o program -pthread

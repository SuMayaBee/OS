// Include necessary libraries
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

// Declare global variables
int philNum, chopNum; // Number of philosophers and chopsticks
sem_t chopsticks[2]; // Array of semaphores representing chopsticks

// Function prototype for the eat function
void *eat(void *arg);

int main(){
    srand(time(NULL)); // Seed the random number generator
    printf("Enter number of philosophers: ");
    scanf("%d", &philNum); // Get the number of philosophers from the user
    printf("\n");
    chopNum = philNum; // The number of chopsticks is equal to the number of philosophers
    chopsticks[philNum]; // Initialize the chopsticks array
    pthread_t philosopers[philNum]; // Array of threads representing philosophers
    int philID[philNum]; // Array of philosopher IDs
    for(int i = 0; i < philNum; i++){
        philID[i] = i + 1; // Assign IDs to philosophers
    }
    for(int i = 0; i < chopNum; i++){
        sem_init(&chopsticks[i], 0, 1); // Initialize chopstick semaphores
    }
    for(int i = 0; i < philNum; i++){
        pthread_create(&philosopers[i], NULL, eat, &philID[i]); // Create philosopher threads
    }
    for(int i = 0; i < philNum; i++){
        pthread_join(philosopers[i], NULL); // Wait for philosopher threads to finish
    }
    return 0;
}

void *eat(void *arg){
    int num = *(int *)arg; // Philosopher ID
    while(1){ // Infinite loop
        int left = num; // Left chopstick
        int right = ( num  == philNum ) ? (num + 1) % philNum : num + 1; // Right chopstick
        printf("Philosopher %d is thinking.....\n\n", num); // Philosopher is thinking
        sleep((rand() % 3) + 1); // Sleep for a random amount of time
        printf("Philosopher %d is hungry\n\n", num); // Philosopher is hungry
        if(num == philNum){ // If philosopher is the last one
            sem_wait(&chopsticks[num % philNum]); // Wait for the right chopstick
            sem_wait(&chopsticks[num - 1]); // Wait for the left chopstick
        }
        else{ // If philosopher is not the last one
            sem_wait(&chopsticks[num - 1]); // Wait for the left chopstick
            sem_wait(&chopsticks[num % philNum]); // Wait for the right chopstick
        }
        printf("Philosopher %d has taken chopsticks %d and %d\n\n", num, left, right); // Philosopher has taken chopsticks
        printf("Philosopher %d is eating.....\n\n", num); // Philosopher is eating
        sleep((rand() % 2) + 1); // Sleep for a random amount of time
        printf("Philosopher %d has finihed eating\n\n", num); // Philosopher has finished eating
        sem_post(&chopsticks[num - 1]); // Release the left chopstick
        sem_post(&chopsticks[num % philNum]); // Release the right chopstick
    }
}
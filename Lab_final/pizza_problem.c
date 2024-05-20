#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<semaphore.h>
#include<pthread.h>

#define true 1
#define false 0

int num_student; // Number of students
int num_slices = 0; // Number of pizza slices available
int S; // Number of slices in each pizza
sem_t pizza; // Semaphore to signal when a pizza slice is available
sem_t deliver; // Semaphore to signal when a pizza delivery can be made
sem_t mutex; // Semaphore to ensure mutual exclusion when updating num_slices and deliveryProcess
int deliveryProcess = true; // Flag to indicate whether a pizza delivery can be made

void *student(void *arg);
void *delivery(void *arg);
void init_sem();
void destroy_sem();

int main(){
    srand(time(NULL));
    
    init_sem(); // Initialize semaphores
    
    printf("Enter number of stuents: ");
    scanf("%d", &num_student);
    printf("Enter number of slices: ");
    scanf("%d", &S);
    printf("\n");

    pthread_t students[num_student]; // Array of student threads
    pthread_t pizza_delivery; // Pizza delivery thread
    int studentID[num_student]; // Array of student IDs
    
    for(int i = 0; i < num_student; i++){
        studentID[i] = i + 1; // Assign IDs to students
    }
    
    for(int i = 0; i < num_student; i++){
        pthread_create(&students[i], NULL, student, &studentID[i]); // Create student threads
    }
    
    pthread_create(&pizza_delivery, NULL, delivery, NULL); // Create pizza delivery thread
    
    for(int i = 0; i < num_student; i++){
        pthread_join(students[i], NULL); // Wait for student threads to finish
    }
    
    pthread_join(pizza_delivery, NULL); // Wait for pizza delivery thread to finish
    
    destroy_sem(); // Destroy semaphores
}

void init_sem(){
    sem_init(&pizza, 0, 0); // Initialize pizza semaphore with 0
    sem_init(&deliver, 0, 1); // Initialize deliver semaphore with 1
    sem_init(&mutex, 0, 1); // Initialize mutex semaphore with 1
}

void destroy_sem(){
    sem_destroy(&pizza); // Destroy pizza semaphore
    sem_destroy(&deliver); // Destroy deliver semaphore
    sem_destroy(&mutex); // Destroy mutex semaphore
}

void *student(void *arg){
    int id = *(int *)arg; // Student ID
    int flag;
    while(1){ // Infinite loop
        flag = true;
        while(num_slices == 0){ // If no pizza slices are available
            if(flag){
                printf("Student %d is sleeping\n\n", id); // Student sleeps
                flag = false;
            }
        }
        sem_wait(&mutex); // Acquire mutex lock
        if(num_slices > 0){ // If pizza slices are available
            num_slices--; // Eat a slice
            sem_wait(&pizza); // Wait for a slice to be available
            printf("Student %d is eating and studying. Remaining slices: %d\n\n", id, num_slices); // Student eats and studies
        } 
        if(num_slices == 0){ // If no more slices are left
            if(!deliveryProcess){ // If a pizza delivery can be made
                deliveryProcess = true; // Set flag to true
                sem_post(&deliver); // Signal that a pizza delivery can be made
            }
        }
        sem_post(&mutex); // Release mutex lock
        sleep((rand() % 3) + 1); // Sleep for a random amount of time
    }
}

void *delivery(void *arg){
    while(1){ // Infinite loop
        sem_wait(&deliver); // Wait until a pizza delivery can be made

        printf("Pizza is being prepared.....\n\n"); // Prepare pizza
        sleep(5); // Simulate pizza preparation time
        printf("Pizza is delivered\n\n"); // Deliver pizza
        sem_wait(&mutex); // Acquire mutex lock
        num_slices += S; // Add slices to the pizza
        sem_post(&mutex); // Release mutex lock
        for(int i = 0; i < S; i++){
            sem_post(&pizza); // Signal that a slice is available
        }
        deliveryProcess = false; // Set flag to false
    }
}


// gcc pizza_problem.c -o pizza -lpthread
// ./pizza

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 3

int main() {
    double matrixA[N][N] = {
        {1, 2, 4},
        {3, 2, 4},
        {9, 4, 7}
    };

    double matrixB[N][N] = {
        {1, 2, 4},
        {3, 2, 4},
        {9, 4, 7}
    };

    key_t key = ftok("matrix_multiplication", 65);
    int shmid = shmget(key, sizeof(double[N][N]), IPC_CREAT | 0666);

    double (*result)[N] = shmat(shmid, NULL, 0);

    for (int i = 0; i < N; i++) {
        int pid = fork();

        if (pid == 0) { // Child process
            for (int j = 0; j < N; j++) {
                result[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
            shmdt(result);
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    // Print the result matrix
    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lf\t", result[i][j]);
        }
        printf("\n");
    }

    // Detach shared memory
    shmdt(result);

    // Remove shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
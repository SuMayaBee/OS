#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadParams {
    int *array;
    int size;
};


void *average(void *args) {
    struct ThreadParams *params = (struct ThreadParams *)args;
    int *array = params->array;
    int size = params->size;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    double average = (double)sum / size;
    printf("Average: %.2lf\n", average);

    pthread_exit(NULL);
}


void *minn(void *args) {
    struct ThreadParams *params = (struct ThreadParams *)args;
    int *array = params->array;
    int size = params->size;

    int min = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }

    printf("Minimum: %d\n", min);

    pthread_exit(NULL);
}

void *maxx(void *args) {
    struct ThreadParams *params = (struct ThreadParams *)args;
    int *array = params->array;
    int size = params->size;

    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    printf("Maximum: %d\n", max);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }


    for (int i = 0; i < size; i++) 
        array[i] = atoi(argv[i + 1]);

    struct ThreadParams params = {array, size};


    pthread_t average_thread, min_thread, max_thread;
    pthread_attr_t attr;
    pthread_create(&average_thread, &attr, average, (void *)&params);
    pthread_create(&min_thread, &attr, minn, (void *)&params);
    pthread_create(&max_thread, &attr, maxx, (void *)&params);

    
    pthread_join(average_thread, NULL);
    pthread_join(min_thread, NULL);
    pthread_join(max_thread, NULL);

    free(array);

    return 0;
}

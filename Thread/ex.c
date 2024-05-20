#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 50
int sum; /* this data is shared by the thread(s) */
int array_size;
float average, max, min;
float arr[MAX];

void *runner1(void *param); /* the thread */
void *runner2(void *param); /* the thread */
void *runner3(void *param); /* the thread */


int main(int argc, char *argv[])
{
// pthread_t tid; /* the thread identifier */
// pthread_attr_t attr; /* set of attributes for the thread */


// if (argc != 3) {
// 	fprintf(stderr,"usage: a.out <thread size> <integer value>\n");
// 	/*exit(1);*/
// 	return -1;
// }

// if (atoi(argv[2]) < 0) {
// 	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[2]));
// 	/*exit(1);*/
// 	return -1;
// }

array_size = atoi(argv[1]);
pthread_t tid[3];
pthread_attr_t attr;
arr[array_size];

/* get the default attributes */
pthread_attr_init(&attr);

int i;

for(i = 0; i < array_size; ++i){
    arr[i] = atof(argv[i+2]); 
}

for(i = 0; i < array_size; ++i){
    printf("%.2f ", arr[i]); 
}

printf("\n");

/* create the thread */
//pthread_create(&tid,&attr,runner,argv[1]);


pthread_create(&tid[0], &attr, runner1, arr);
pthread_create(&tid[1], &attr, runner2, arr);
pthread_create(&tid[2], &attr, runner3, arr);
/* now wait for the thread to exit */
// pthread_join(tid,NULL);


for(i = 0; i < 3; ++i){
	pthread_join(tid[i], NULL);
}

// printf("In main thread, sum = %d\n",sum);
printf("Avearge = %.2f\n", average);
printf("Maximum value = %.2f\n", max);
printf("Minimum value = %.2f\n", min);
}

/**
 * The thread will begin control in this function
 */
void *runner1(void *param) 
{
    float *a = (float*) param; 
    float sum = 0.0;
    for(int i = 0; i < array_size; ++i){
        printf("%.2f ", a[i]);
        sum += a[i];
    }
    printf("\n");
    average = sum/array_size;

	pthread_exit(0);
}

void *runner2(void *param) 
{
    float *a = (float*) param; 
    max = -1000000.0;
    for(int i = 0; i < array_size; ++i){
        if(max < a[i]) {
            max = a[i];
        }
    }

	pthread_exit(0);
}

void *runner3(void *param) 
{
    float *a = (float*) param; 
    min = 1000000.0;
    for(int i = 0; i < array_size; ++i){
        if(min > a[i]) {
            min = a[i];
        }
    }

	pthread_exit(0);
}   

// gcc ex.c -o ex -lpthread
// ./ex 5 1.1 2.2 3.3 4.4 5.5
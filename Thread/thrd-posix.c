/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Figure 4.11
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */
int counter;

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
// pthread_t tid; /* the thread identifier */
// pthread_attr_t attr; /* set of attributes for the thread */



if (argc != 3) {
	fprintf(stderr,"usage: a.out <thread size> <integer value>\n");
	/*exit(1);*/
	return -1;
}

if (atoi(argv[2]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[2]));
	/*exit(1);*/
	return -1;
}

int thread_size = atoi(argv[1]);
//int num = atoi(argv[2]);
//int num = argv[2];
pthread_t tid[thread_size];
pthread_attr_t attr;

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
//pthread_create(&tid,&attr,runner,argv[1]);

int i;

for(i = 0; i < thread_size; ++i){
	pthread_create(&tid[i], &attr, runner, argv[2]);
}
/* now wait for the thread to exit */
// pthread_join(tid,NULL);

for(i = 0; i < thread_size; ++i){
	pthread_join(tid[i], NULL);
}

printf("In main thread, sum = %d\n",sum);
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
int i, upper = atoi(param);
sum = 0;
counter++;

	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	printf("thread % d calculates sum = %d\n",counter, sum);
	pthread_exit(0);
}

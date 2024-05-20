#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define thread_size 5
#define radius 1.0
#define points_per_thread 1000000

int total_points,points_in_circle;

void *runner(void *param);
double generate_point ();
double calculate_distance(double x,double y);

int main(int argc, char *argv[]){
    srand(time(NULL));
    pthread_t tid[thread_size];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    total_points=points_per_thread*thread_size;
    int i;
    for(i=0;i<thread_size;++i){
        pthread_create(&tid[i],&attr,runner,NULL);
    }
    for(i=0;i<thread_size;++i){
        pthread_join(tid[i],NULL);
    }
    double estimated_pi=4.0*((double)points_in_circle/total_points);
    printf("The estimated value of pi = %lf\n",estimated_pi);
}

void *runner(void *param) 
{
    double  x,y,distance;
    for(int i=0;i<points_per_thread;++i){
        x=generate_point();
        y=generate_point();
        distance=calculate_distance(x,y);
        if(distance<=radius){
            points_in_circle++;
        }
    }
    pthread_exit(0);
}

double generate_point (){
    double x;
    x=((double)rand()/RAND_MAX)*2-1;
    return x; 
}

double calculate_distance(double x,double y){
    return sqrt(x*x + y*y);
}

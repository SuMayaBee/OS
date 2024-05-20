#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define thread_size 1
#define radius 1.0
int total_points, points_in_circle;
// double x, y;

// void *runner(void *param); /* the thread */
// double generate_point ();
// double calculate_distance(double x,double y);

// int main(int argc, char *argv[])
// {
//     for(int i = 0; i < 10; ++i){
//         double x = generate_point();
//     double y = generate_point();
//     double distance = sqrt(x*x + y*y);
//     printf("%lf %lf\n", x, y);
//     }
// }

// /**
//  * The thread will begin control in this function
//  */
// void *runner(void *param) 
// {
//     // int i, upper = atoi(param);
//     double  x, y, distance;
//     for(int i = 0; i < 100; ++i){
//         srand(time(0));
//         x = generate_point();
//         y = generate_point();
//         distance = sqrt(x*x + y*y);
//         if(distance <= radius) {
//             points_in_circle++;
//         }
//     }
//     pthread_exit(0);
// }

// double generate_point (){
//     double x;
//     int is_positive = rand() % 2;
    
//     x = (rand() % 101) / 100.00;
//     if(is_positive == 0){
//         x = -1 * (x);
//     }
//     return x; 
// }


// double calculate_distance(double x,double y){
//     return sqrt(x*x + y*y);
// }

int main(){
    for(int i = 0; i < 10; ++i){
        printf("%'f\n",((double)rand()/RAND_MAX)*2-1);
    }
}
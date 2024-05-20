#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<math.h>
#define THREADNUM 10

struct params{
    double radius;
    double x;
    double y;
};

int totalCircle;
int totalThrown;

int isInCircle(double centerX, double centerY, double radius, double randX, double randY)
{
    double dis = sqrt(pow(centerX-randX, 2) + pow(centerY-randY, 2));
    printf("%lf\n", dis);
    if(dis<radius)
    return 1;
    else
    return 0;
}

void *runner(void *param)
{
    srand(time(NULL));
    struct params *circle = (struct params*)param;
    double left = circle->x-circle->radius;
    double right = circle->x+circle->radius;
    totalThrown = 10000;
    totalCircle=0;
    for(int i=0; i<totalThrown; i++)
    {
        double random1 = left+((double)rand()/RAND_MAX)*(right-left);
        double random2 = left+((double)rand()/RAND_MAX)*(right-left);
        printf("%lf %lf\n", random1, random2);
        if(isInCircle(circle->x, circle->y, circle->radius, random1, random2))
        totalCircle++;
    }
    pthread_exit(0);
}
int main()
{
    pthread_t tid[THREADNUM];
    srand(time(NULL));
    double centerX, centerY, radius;
    printf("Enter centerX, centerY, radius: \n");
    scanf("%lf %lf %lf", &centerX, &centerY, &radius);
    struct params circle = {radius, centerX, centerY};
    for(int i=0; i<10; i++)
    pthread_create(&tid[i], NULL, runner, (void *)&circle);
    for(int i=0; i<10; i++)
    pthread_join(tid[i], NULL);
    //totalThrown*=THREADNUM;
    double pi = 4*((double)totalCircle/totalThrown);
    printf("%lf\n", pi/THREADNUM);
    return 0;
}

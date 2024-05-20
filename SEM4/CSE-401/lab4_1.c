#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int n;
    scanf("%d", &n);

    int pid = fork();

    if(pid<0)
    {
        perror("fork");
        exit(1);
    }
    else if(pid==0)
    {
        int sum_odd=0;
        for(int i=1; i<=n; i+=2)
        sum_odd+=i;
        printf("Sum of odd is: %d\n", sum_odd);
    }
    else
    {
        int sum_even=0;
        for(int i=2; i<=n; i+=2)
        sum_even+=i;
        printf("Sum of even is: %d\n", sum_even);
    }
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    int n;
    printf("Enter number: ");
    scanf("%d",&n);
    int pid=fork();
    if(pid==0){
        int odd_sum=0,cnt=1;
        while(cnt<=n){
            odd_sum+=cnt;
            cnt+=2;
        }
        printf("Sum of odd numbers: %d\n",odd_sum);
        exit(0);
    }
    else{
        int even_sum=0,cnt=0;
        while(cnt<=n){
            even_sum+=cnt;
            cnt+=2;
        }
        wait(NULL);
        printf("Sum of even numbers: %d\n",even_sum);
    }
    return 0;
}
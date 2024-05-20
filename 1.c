#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    int n,even_sum=0,odd_sum=0,count;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    int pid=fork();
    if(pid==0){
        count=1;
        while(count<=n){
            odd_sum+=count;
            count+=2;
        }
        printf("Sum of the odd numbers: %d\n",odd_sum);
    }
    else{
        count=0;
        while(count<=n){
            even_sum+=count;
            count+=2;
        }
        printf("Sum of the even numbers: %d\n",even_sum);
    }
    return 0;
}
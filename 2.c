#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    freopen("input.txt","r",stdin);
    int r1,c1,r2,c2;
    // printf("Enter the dimension of the first matrix: ");
    scanf("%d %d",&r1,&c1);
    // printf("Enter the dimension of the second matrix: ");
    scanf("%d %d",&r2,&c2);
    int mat1[r1][c1],mat2[r2][c2],mat3[r1][c2];
    int i,j,k,pid,ppid=getppid();
    // printf("Enter the first matrix:\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            scanf("%d",&mat1[i][j]);
        }
    }
    // printf("Enter the second matrix:\n");
    for(i=0;i<r2;i++){
        for(j=0;j<c2;j++){
            scanf("%d",&mat2[i][j]);
        }
    }
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            mat3[i][j]=0;
        }
    }
    printf("Multiplied matrix:\n");
    i=0;
    while(i<r1){
        if(pid=fork()==0){
            printf("i: %d ppid: %d pid: %d\t",i,getppid(),getpid());
            j=0;
            while(j<c1){
                k=0;
                while(k<c2){
                    mat3[i][k]+=mat1[i][j]*mat2[j][k];
                    k++;
                }
                j++;
            }
            for(int x=0;x<c2;x++){
                printf("%5d",mat3[i][x]);
            }
            printf("\n");  
            exit(0);
        }
        i++;
    }
    for(i=0;i<r1;i++){
        wait(NULL);
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    freopen("input.txt","r",stdin);
    int r1,c1,r2,c2;
    scanf("%d %d",&r1,&c1); // Dimension of the first matrix
    scanf("%d %d",&r2,&c2); // Dimension of the second 
    int mat1[r1][c1],mat2[r2][c2];
    int i,j,k,pid;
    // Input of the first matrix
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++){
            scanf("%d",&mat1[i][j]);
        }
    }
    // Input of the second matrix
    for(i=0;i<r2;i++){
        for(j=0;j<c2;j++){
            scanf("%d",&mat2[i][j]);
        }
    }
    int row[c2]; // Each row of the multiplied matrix
    for(i=0;i<r1;i++){
        pid=fork();
        if(pid==0){
            for(j=0;j<c2;j++){
                row[j]=0;
            }
            for(j=0;j<c1;j++){
                for(k=0;k<c2;k++){
                    row[k]+=mat1[i][j]*mat2[j][k];
                }
            }
            for(j=0;j<c2;j++){
                printf("%6d",row[j]);
            }
            printf("\n");
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
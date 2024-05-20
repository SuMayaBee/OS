#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    int row1, col1, row2, col2;
    scanf("%d %d %d %d", &row1, &col1, &row2, &col2);

    int matrix1[row1][col1], matrix2[row2][col2];


    for(int i = 0; i < row1; i++) 
    {
        for(int j = 0; j < col1; j++)
        scanf("%d", &matrix1[i][j]);
    }


    for(int i = 0; i < row2; i++)
    {
        for(int j = 0; j < col2; j++)
        scanf("%d", &matrix2[i][j]);
    }


    int res[row1][col2];

    printf("Result is \n");
    for(int i = 0; i < row1; i++) 
    {
        int pid = fork();
        if(pid < 0) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) 
        {
            for(int j = 0; j < col2; j++) 
            {
                res[i][j]=0;
                for(int k = 0; k < col1; k++)
                res[i][j] += matrix1[i][k]*matrix2[k][j];
            }
            for(int p=0; p<col2; p++)
            printf("%d ", res[i][p]);
            printf("\n");
            exit(EXIT_SUCCESS);
        }
    }

    for(int i = 0; i < row1; i++)
        wait(NULL);

    // for(int i = 0; i < row1; i++) {
    //     for(int j = 0; j < col2; j++)
    //         printf("%d ", res[i][j]);
    //     printf("\n");
    // }
    // printf("\n");
    return 0;
}

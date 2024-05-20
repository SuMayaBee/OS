#include<stdio.h>

int arr[2];

int main(){
    int num = 5;
    arr[num];
    for(int i = 0; i < num; i++){
        arr[i] = i + 1;
    }
    for(int i = 0; i < num; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
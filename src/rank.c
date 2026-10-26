#include "main.h"

void DivideANDConquer(Rank *arr, Rank *temp, int left, int right){
    if(left >= right){
        return;
    }

    int mid = (left+right)/ 2;
    DivideANDConquer(arr, temp, left, mid);
    DivideANDConquer(arr, temp, mid+1,right);
    merge(arr, temp, left, mid, right);
}

void merge(Rank *arr, Rank *temp, int left, int mid, int right){
    int i= left;
    int j = mid+1;
    int k = left;

    while(i<=mid && j<=right){
        if(arr[i].friendCount > arr[j].friendCount){
            temp[k] = arr[i];
            i++;
        }
        else if(arr[i].friendCount < arr[j].friendCount){
            temp[k] = arr[j];
            j++;
        }
        else if(arr[i].userId < arr[j].userId){
            temp[k] = arr[i];
            i++;
        }
        else{
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    while(i<=mid){
        temp[k]=arr[i];
        i++;
        k++;
    }
    while(j<=right){
        temp[k]=arr[j];
        j++;
        k++;
    }
    for(int n=left;n<=right;n++){
        arr[n]=temp[n];
    }
}
void printRank(Graph *g){
    int i;
    int count = g->n;
    Rank *arr = (Rank*)malloc(sizeof(Rank)*count);
    Rank *temp = (Rank*)malloc(sizeof(Rank)*count);
    
    for(i=0;i<count;i++){
        arr[i].userId = i;
        arr[i].friendCount = friendCount(g,i);
    }
    DivideANDConquer(arr, temp, 0, count-1);
    printf("\n ========= RANKING ========= \n\n");

    int limit = 50;
    if(count<50){
        limit = count;
    }
    for(i=0;i<limit;i++){
        printf("사용자 번호: %d | 친구 수: %d | %d위\n", arr[i].userId, arr[i].friendCount,i+1);
    }
    free(arr);
    free(temp);
}
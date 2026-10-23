#include "main.h"

heap *create_heap(int size, bool isMin){
    if(size <= 0){
        return 0;
    }
    heap *h = (heap*)malloc(sizeof(heap));
    h->Id = (int*)malloc(sizeof(int) * (size + 1));
    h->priority = (int*)malloc(sizeof(int) * (size + 1));
    h->capacity = size;
    h->size = 0;
    h->isMin = isMin;
    return h;
}
void swap(heap *h, int i, int j){
    int tmp = h->Id[i];
    h->Id[i] = h->Id[j];
    h->Id[j] = tmp;

    tmp = h->priority[i];
    h->priority[i] = h->priority[j];
    h->priority[j] = tmp;
}

int MinORMax(heap *h, int i, int j){ //최소 힙, 최대 힙 구분
    if(h->isMin){
        return h->priority[i] < h->priority[j];
    }
    else{
        return h->priority[i] > h->priority[j];
    }
}

void heapify(heap *h, int i){ // bottom-up
    int child;
    while(i*2<=h->size){
        child=i*2;
        if(child+1 <= h->size && MinORMax(h, child+1, child)){
            child++;
        }
        if(MinORMax(h, child, i)==0){
            break;
        }
        swap(h,i,child);
        i = child;
    }
}

void build_heap(heap *h){
    for(int i=h->size/2;i>=1;i--){
        heapify(h,i);
    }
}

int add_heap(heap *h, int v, int p){
    h->size++;
    int i = h->size;
    int parent = i/2;
    h->Id[i] = v;
    h->priority[i] = p;
    while(i>1){
        if(h->priority[parent] <= h->priority[i]){
            break;
        }
        swap(h, i, parent);
        i = parent;
        parent = i/2;
    }
    return 1;
}

int remove_heap(heap *h, int *v, int *p){

    if(h->size == 0){
        return 0;
    }
    *v = h->Id[1];
    *p = h->priority[1];
    h->Id[1] = h->Id[h->size];
    h->priority[1] = h->priority[h->size];
    h->size--;
    heapify(h,1);
    
    return 1;
}

void free_heap(heap *h){
    if(h != NULL){
        free(h->Id);
        free(h->priority);
        free(h);
    }
}
#include "main.h"

void rehash(Table *ht){
    int n = ht->tablesize*2;
    if(ht->isP){
        p_node **new = (p_node**)malloc(sizeof(p_node*)*n);
        if(new==0){
            return;
        }
        for(int i=0;i<n;i++){
            new[i]=0;
        }
        for(int i=0;i<ht->tablesize;i++){
            p_node *current = ht->profile[i];
            while(current!=0){
                p_node *next = current->next;
                int i = hash(current->data.userId, n);
                current->next = new[i];
                new[i] = current;
                current = next;
            }
        }
        free(ht->profile);
        ht->profile = new;
    }
    else{
        h_node **new = (h_node**)malloc(sizeof(h_node*)*n);
        if(new==0){
            return;
        }
        for(int i=0;i<n;i++){
            new[i]=0;
        }
        for(int i=0;i<ht->tablesize;i++){
            h_node *current = ht->hashtag[i];
            while(current!=0){
                h_node *next = current->next;
                int i = djb2(current->key, n);
                current->next = new[i];
                new[i] = current;
                current = next;
            }
        }
        free(ht->hashtag);
        ht->hashtag = new;
    }
    ht->tablesize = n;
}
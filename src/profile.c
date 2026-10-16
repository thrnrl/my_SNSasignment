#include "main.h"

int user(int userId){
    return userId % TABLE_SIZE;
}

void init_table(p_table *t){
    for(int i=0;i<TABLE_SIZE;i++){
        t->table[i] = 0;
    }
}

void insert_profile(p_table *h, Profile p){
    int i = user(p.userId);
    p_node *n = (p_node*)malloc(sizeof(p_node));

    if(n==0){
        printf("Memory Misallcation ");
        return;
    }
    n->data = p;
    n->next = h->table[i];
    h->table[i] = n;
}

void generate_profile(p_table *t, Graph *g, int count){

    char *favorite[] = {"workout","running","cook","laundry","bakery"}; 
    for(int i=0;i<count;i++){
        Profile p;
        p.userId = i;
        strcpy(p.favorite, favorite[i%5]);
        p.friendCount = friendCount(g, i);
        insert_profile(t, p);
    }
}

Profile *search_profile(p_table *t, int userId){
    int i = user(userId);
    p_node *p = t->table[i];

    while(p!=0){
        if(p->data.userId == userId){
            return &(p->data);
        }
        p = p->next;
    }

    return 0;
}

void print_profile(Profile *p){
    if(p==0){
        printf("profile Not found\n");
    }
    printf("ID: %d\n", p->userId);
    // printf("name: %s\n", p->nickname);
    printf("favorite: %s\n", p->favorite);
    printf("friends: %d\n",p->friendCount);
}

void free_table(p_table *t){
    for(int i=0;i<MAX_SIZE;i++){
        p_node *n = t->table[i];
        while(n!=0){
            p_node *temp = n;
            n = n->next;
            free(temp);
        }
        t->table[i] = 0;
    }
}
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

void generate_profile(p_table *pt, Graph *g, int count){

    char *favorite[] = {"workout","running","cook","laundry","bakery","game","travel","drawing"};
    char *nickname[] = {"철수","영희","민수","지수","현우","수지","민호","하영"}; 
    for(int i=0;i<count;i++){
        Profile p;
        p.userId = i;
        strcpy(p.nickname, nickname[RANDOM(8)]);
        strcpy(p.favorite, favorite[RANDOM(8)]); 
        p.friendCount = friendCount(g, i);
        insert_profile(pt, p);
    }
}

Profile *search_profile(p_table *pt, int userId){
    int i = user(userId);
    p_node *p = pt->table[i];

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
        return;
    }
    printf(" ========= %s님의 프로필 ========= \n", p->nickname);
    printf("ID: %d\n", p->userId);
    printf("name: %s\n", p->nickname);
    printf("favorite: %s\n", p->favorite);
    printf("friends: %d\n",p->friendCount);
}

void free_table(p_table *pt){
    for(int i=0;i<TABLE_SIZE;i++){
        p_node *n = pt->table[i];
        while(n!=0){
            p_node *temp = n;
            n = n->next;
            free(temp);
        }
        pt->table[i] = 0;
    }
}
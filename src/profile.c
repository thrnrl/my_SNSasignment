#include "main.h"

int hash(int userId, int tablesize){
    return userId % tablesize;
}

void init_table(p_table *pt){
    pt->tablesize = BUCKET;
    pt->count = 0;
    pt->table = (p_node**)calloc(pt->tablesize, sizeof(p_node *));
    for(int i=0;i<BUCKET;i++){
        pt->table[i] = 0;
    }
}

void insert_profile(p_table *pt, Profile p){
    int i = hash(p.userId, pt->tablesize);
    p_node *n = (p_node*)malloc(sizeof(p_node));
    if(n==0){
        printf("Memory Misallcation");
        return;
    }
    n->data = p;
    n->next = pt->table[i];
    pt->table[i] = n;
    pt->count++;
    if(Usage(pt->count, pt->tablesize)){
        PTrehash(pt);
    }
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
    int i = hash(userId, pt->tablesize);
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

int PTrehash(p_table *pt){
    int new = pt->tablesize*2 +1;
    p_node **newTable = (p_node**)calloc(new, sizeof(p_node*));
    for(int i=0;i<pt->tablesize;i++){
        p_node *current = pt->table[i];
        while(current!=0){
            p_node *next = current->next;
            int i = hash(current->data.userId, new);
            current->next = newTable[i];
            newTable[i] = current;
            current = next;
        }
    }
    free(pt->table);
    pt->table = newTable;
    pt->tablesize = new;
    printf("Rehash: %d\n", new);

    return 1;
}

void free_table(p_table *pt){
    for(int i=0;i<BUCKET;i++){
        p_node *n = pt->table[i];
        while(n!=0){
            p_node *temp = n;
            n = n->next;
            free(temp);
        }
    }
    free(pt->table);
    pt->table = 0;
    pt->count = 0;
}
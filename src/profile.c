#include "main.h"

int hash(int userId, int tablesize){
    return userId % tablesize;
}

void init_profile(Table *pt){
    
    pt->tablesize = BUCKET;
    pt->count = 0;
    pt->isP = true;
    pt->hashtag = 0;
    pt->profile = (p_node**)malloc(sizeof(p_node *)*pt->tablesize);

    if(pt->profile==0){
        return;
    }
    for(int i=0;i<pt->tablesize;i++){
        pt->profile[i] = 0;
    }
}

void insert_profile(Table *pt, Profile p){
    int i = hash(p.userId, pt->tablesize);
    p_node *n = (p_node*)malloc(sizeof(p_node));
    if(n==0){
        return;
    }
    n->data = p;
    n->next = pt->profile[i];
    pt->profile[i] = n;
    pt->count++;
    if(Usage(pt->count, pt->tablesize)){
        rehash(pt);
    }
}

void generate_profile(Table *pt, Graph *g, int count){

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

Profile *search_profile(Table *pt, int userId){

    if(userId>=USERS){
        return 0;
    }
    int i = hash(userId, pt->tablesize);
    p_node *p = pt->profile[i];
    
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

void free_table(Table *pt){
    for(int i=0;i<pt->tablesize;i++){
        p_node *n = pt->profile[i];
        while(n!=0){
            p_node *temp = n;
            n = n->next;
            free(temp);
        }
    }
    free(pt->profile);
    pt->profile = 0;
    pt->count = 0;
}
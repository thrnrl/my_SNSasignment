#include "main.h"

void generate_post(Post *p, Table *ht, int count, int userCount){
    int tagId;
    if(p==NULL){
        return;
    }
    for(int i=0;i<count;i++){
        p[i].postId = i;
        p[i].userId = RANDOM(userCount);
        p[i].likes = RANDOM(500);
        p[i].uploadTime = RANDOM(43200); // 분 단위 경과시간
        if(i<50000){
            tagId = i;
        }
        else{
            tagId=RANDOM(50000);
        }
        sprintf(p[i].hashtag, "#tag%d", tagId);
        insert_hashtag(ht, p[i].hashtag, p[i].postId);
    }
}

int calculate_trendFeedScore(Post *p){
    int score = p->likes / (p->uploadTime+1);
    return score*500 + p->likes;
}

void printTrendFeed(Post *p, int count){
    int i, Id=0, score=0;
    heap *h = create_heap(count, MAX_HEAP);
    for(i=0;i<count;i++){
        h->Id[i+1] = i;
        h->priority[i+1] = calculate_trendFeedScore(&p[i]);
    }
    h->size = count;
    build_heap(h);

    printf(" ========= TREND FEED ========= \n");
    for(i=0;i<10&&i<count;i++){
        if(remove_heap(h,&Id, &score)==0){
            break;
        }
        printf("%d | 게시물번호: %d | 좋아요 수: %d | 점수 :%d | %s\n", i+1, p[Id].postId, p[Id].likes, score ,p[Id].hashtag);
    }
    free_heap(h);
}

int djb2(char *tag, int tablesize){
    unsigned long hash = 5381;
    int i;
    while((i=(unsigned char)*tag++)!=0){
        hash = hash * 33 + i;
    }
    return hash % tablesize;
}

void init_hashtag(Table *ht){
    ht->tablesize = BUCKET;
    ht->count=0;
    ht->profile = 0;
    ht->hashtag = (h_node**)malloc(sizeof(h_node*)*ht->tablesize);
    ht->isP = false;
    if(ht->hashtag==0){
        return;
    }
    for(int i=0;i<ht->tablesize;i++){
        ht->hashtag[i]=0;
    }
}

void insert_hashtag(Table *ht, char *tag, int postId){
    int i = djb2(tag, ht->tablesize);
    h_node *n = (h_node*)malloc(sizeof(h_node));
    if(n == 0){
        return;
    }
    n->key = tag;
    n->postId = postId;
    n->next = ht->hashtag[i];
    ht->hashtag[i] = n;
    ht->count++;
    if(Usage(ht->count, ht->tablesize)){
        rehash(ht);
    }
}

void search_hashtag(Table *ht, Post *p, char *tag){
    int i = djb2(tag, ht->tablesize);
    h_node *current = ht->hashtag[i];
    int count = 0;

    printf(" ========= %s 게시물 목록 ========= \n", tag);
    while(current!=0){
        if(strcmp(current->key, tag)==0){
            int postId = current->postId;
            printf("게시물: %d\n",p[postId].postId);
            count++;
        }
        current = current->next;
    }
    if(count==0){
        printf("Not Found!\n");
    }
    else{
        printf("%d개 게시물이 존재합니다.\n",count);
    }
}

void free_hashtag(Table *ht){
    for(int i=0;i<ht->tablesize;i++){
        h_node *current = ht->hashtag[i];
        while(current!=0){
            h_node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(ht->hashtag);
    ht->hashtag=0;
    ht->tablesize=0;
    ht->count=0;
}
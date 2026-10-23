#include "main.h"

void generate_post(Post *p, h_table *ht, int count, int userCount){
    int tagId;
    if(p==NULL){
        return;
    }
    for(int i=0;i<count;i++){
        p[i].postId = i;
        p[i].userId = RANDOM(userCount);
        p[i].likes = RANDOM(500);
        // 분 단위 경과시간
        p[i].uploadTime = RANDOM(43200); 
        
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
    return p->likes / (p->uploadTime+1);
}

void printTrendFeed(Post *p, int count){

    int i, Id, score;
    heap *h = create_heap(count, MAX_HEAP);
    if (p==NULL){
        return;
    }
    for(i=0;i<count;i++){
        h->Id[i+1] = i;
        h->priority[i+1] = calculate_trendFeedScore(&p[i]);
    }
    h->size = count;
    build_heap(h);

    printf(" ========= TREND FEED ========= \n");
    for(i=0;i<10&&i<count;i++){
        if(remove_heap(h, &Id, &score)==0){
            break;
        }
        printf("%d | 게시물번호: %d | 좋아요 수: %d | 점수 :%d | %s\n", i+1, p[Id].postId,p[Id].likes, score,p[Id].hashtag);
    }
    free_heap(h);
}

int hashtag(char *tag){
    unsigned long hash = 5381;
    int i;
    while((i=(unsigned char)*tag++)!=0){
        hash = hash * 33 + i;
    }
    return hash % TABLE_SIZE;
}

void init_hashtag(h_table *ht){
    for (int i=0;i<TABLE_SIZE;i++){
        ht->table[i]=0;
    }
}

void insert_hashtag(h_table *ht, char *tag, int postId){
    int index = hashtag(tag);
    h_node *new = malloc(sizeof(h_node));

    if(new == 0){
        printf("Memory Misallcation");
        return;
    }

    strcpy(new->key, tag);
    new->postId = postId;
    new->next = ht->table[index];
    ht->table[index] = new;
}

void search_hashtag(h_table *ht, Post *p, char *tag){
    int index = hashtag(tag);
    h_node *current = ht->table[index];
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

void free_hashtag(h_table *ht){
    for(int i=0;i<TABLE_SIZE;i++){
        h_node *current = ht->table[i];
        while(current!=0){
            h_node *next = current->next;
            free(current);
            current = next;
        }
        ht->table[i]=0;
    }
}
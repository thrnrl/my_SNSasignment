#include "main.h"

void generate_post(Post *p, int count, int userCount){
    if(p==NULL){
        return;
    }
    char *hashtag[] = {"#운동", "#일상", "#음식", "#여행","#게임","#공부" };
    for(int i=0;i<count;i++){
        p[i].postId = i;
        p[i].userId = RANDOM(userCount);
        p[i].likes = RANDOM(500);
        // 분 단위 경과시간
        p[i].uploadTime = RANDOM(43200); 
        strcpy(p[i].hashtag, hashtag[RANDOM(6)]);
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
        printf("%d | 게시물번호: %d | 좋아요 수: %d | 점수 :%d | %s\n", i+1, p[Id].postId,p[Id].likes, score,p[i].hashtag);
    }
    free_heap(h);
}
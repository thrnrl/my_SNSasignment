#include "include/main.h"



void clear(){
    while((getchar())!='\n');
}

int try(int *n){
    int i;
    while(1){
        i = scanf("%d", n);
        if(i==EOF){
            return EOF;
        }else if(i==0){
            clear();
            printf("[access denied]:: not exist num ..\n");
        }else if(*n<0){
            printf("[your input < 0]\n");
        }else if(*n>=USERS){
            printf("[over 0-99999 range]\n");
        }else{
            return 1;
        }
        printf("try again:: ");
    }
}

int main(){
    int myId, menu, userId;
    char tag[32];

    printf("0 -- 99999\n기준 번호 입력: ");
    if(try(&myId)==EOF){
        return 0;
    }
    srand(time(0));

    Graph *g = (Graph*)malloc(sizeof(Graph));
    init_graph(g);
    generate_user(g, 100000);
    generate_edge(g, 500000);
    Table *pt = (Table*)malloc(sizeof(Table));
    init_profile(pt);
    generate_profile(pt, g, 100000);
    
    Post *p = malloc(sizeof(Post)*POSTS);
    Table *ht = (Table*)malloc(sizeof(Table));
    init_hashtag(ht);
    generate_post(p, ht, POSTS, USERS);

    while(1){
        printf("\n ========= MENU ========= \n\n");
        printf("1. 사용자와의 거리 재기\n");
        printf("2. 추천 친구\n");
        printf("3. 프로필 검색\n");
        printf("4. 실시간 피드\n");
        printf("5: 해시태그로 게시물 검색\n");
        printf("6. 유저 간 랭킹\n");
        printf("0. 종료\n");
        printf(":: ");
        if(try(&menu)==EOF){
            break;
        }
        if(menu==1){
            printf("\n친구 ID 입력: ");
            if(try(&userId)==EOF){
                break;
            }
            printf("\n");
            dijkstra(g, myId, userId);
        }
        else if(menu==2){
            mutual(g, myId);
        }
        else if(menu==3){
            printf("\n상대방 ID 입력: ");
            if(try(&userId)==EOF){
                break;
            }
            printf("\n");
            Profile *res = search_profile(pt, userId);
            print_profile(res);
        }
        else if(menu==4){
            printTrendFeed(p, POSTS);
        }
        else if(menu==5){
            printf("\n[#tag0~49999]\n해시태그 양식에 맞춰서 입력: ");
            if(scanf("%31s", tag)!=1){
                printf("access dinied, check md.");
                break;
            }
            search_hashtag(ht, p, tag);
        }
        else if(menu==6){
            printRank(g);
        }
        else if(menu==0){
            break;
        }
        else{
            printf("your input not exist. follow menu num.");
        }
    }
    free(p);
    free_graph(g);
    free(g);
    free_table(pt);
    free(pt);
    free_hashtag(ht);
    free(ht);

    return 0;
}
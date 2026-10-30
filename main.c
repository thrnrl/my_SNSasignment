#include "include/main.h"

void clear(){
    while((getchar())!='\n');
}



int main(){
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

    int myId, menu, userId;
    char tag[32];
    
    while(1){
        printf("계정을 생성합니다.\n사용하실 ID를 입력해주세요[범위: 0~99999]:");
        if(scanf("%d", &myId)!=1 || myId < 0 || myId>=USERS){
            printf("Access Dinied!\n");
            continue;
        }
    }

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
        if(scanf("%d", &menu)==EOF){
            break;
        }
        else if(menu!=1){
            printf("access Denied, plz check your num.\n");
            clear();
            continue;
        }
        if(menu==1){
            printf("\n친구 ID 입력: ");
            if(scanf("%d", &userId)!=1 || userId<0 || userId >= USERS){
                printf("존재하지 않는 ID");
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
            scanf("%d", &userId);
            printf("\n");
            Profile *res = search_profile(pt, userId);
            print_profile(res);
        }
        else if(menu==4){
            printTrendFeed(p, POSTS);
        }
        else if(menu==5){
            printf("\n검색할 해시태그 입력.\n[#tag0~49999]: ");
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
            printf("your input is not exist. follow to borad number!");
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
#include "include/main.h"

int main(){
    srand(time(0));

    Graph *g = malloc(sizeof(Graph));
    init_graph(g);
    generate_user(g, 100000);
    generate_edge(g, 500000);

    p_table *t = malloc(sizeof(p_table));
    init_table(t);
    generate_profile(t, g, 100000);

    Post *p = malloc(sizeof(Post)*POST_SIZE);
    generate_post(p, POST_SIZE, MAX_SIZE);


    int myId, menu,userId;

    printf("계정을 생성합니다.\n\n사용하실 ID를 입력해주세요: ");
    scanf("%d", &myId);

    while(1){
        printf("\n ========= MENU ========= \n\n");
        printf("1. 사용자와의 거리 재기\n");
        printf("2. 추천 친구\n");
        printf("3. 프로필 검색\n");
        printf("4. 실시간 피드\n");
        printf("5. 유저 간 랭킹\n");
        printf("0. 종료\n");
        printf(":: ");
        scanf("%d", &menu);

        if(menu == 1){
            printf("\n친구 ID 입력: ");
            scanf("%d", &userId);
            printf("\n");
            dijkstra(g, myId, userId);
        }
        else if(menu == 2){
            mutual(g, myId);
        }
        else if(menu == 3){
            printf("\n상대방 ID 입력: ");
            scanf("%d", &userId);
            printf("\n");
            Profile *res = search_profile(t, userId);
            print_profile(res);
        }
        else if(menu == 4){
            printTrendFeed(p, POST_SIZE);
        }
        else if(menu == 0){
            break;
        }
    }

    
    free(p);
    free_graph(g);
    free(g);
    free_table(t);
    free(t);

    return 0;
}
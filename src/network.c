#include "main.h"

void init_graph(Graph *g){
    g->n = 0;
    for(int i=0;i<USERS;i++){
        g->adj_list[i]=0;
    }
}

void add_vertex(Graph *g){
    if(g->n >= USERS){
        printf("OVERFLOW!!!\n");
        return;
    }
    g->n++;
}

void add_edge(Graph *g, int v1, int v2){
    Node *node;

    if(v1 >= g->n || v2 >= g->n){
        printf("vertex not inserting\n");
        return;
    }

    node = (Node*)malloc(sizeof(*node));

    if(node == 0){
        printf("memory dealocation\n");
        return;
    }
    node->vertex = v2;
    node->next = g->adj_list[v1];
    g->adj_list[v1]=node;

    node = (Node*)malloc(sizeof(*node));

    node->vertex = v1;
    node->next = g->adj_list[v2];
    g->adj_list[v2]=node;
}

int isExist(Graph *g, int v1, int v2){
    Node *node = g->adj_list[v1];
    while(node!=0){
        if(node->vertex == v2){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void generate_user(Graph *g, int count){
    for(int i=0;i<count;i++){
        add_vertex(g);
    }
}

void generate_edge(Graph *g, int count){
    int edge_count = 0;
    int v1, v2;

    while(edge_count < count){
        v1 = RANDOM(g->n);
        v2 = RANDOM(g->n);

        if(v1==v2){
            continue;
        }
        if(isExist(g, v1, v2)){
            continue;
        }
        add_edge(g, v1, v2);
        edge_count++;
    }
}

void mutual(Graph *g, int me){
    int visited[USERS] = {0};
    Node *friend;
    Node *mutual;

    visited[me] = 1;
    friend = g->adj_list[me];
    while(friend!=0){
        visited[friend->vertex] = 1;
        friend = friend->next;
    }
    friend = g->adj_list[me];
    printf("%d 다리건너친구: ", me);
    while(friend!=0){
        mutual=g->adj_list[friend->vertex];
        while(mutual!=0){
            if(visited[mutual->vertex]==0){
                printf("%d, ",mutual->vertex);
                visited[mutual->vertex] = 1;
            }
            mutual = mutual->next;
        }
        friend= friend->next;
    }
    printf("\n");
}

void dijkstra(Graph *g, int s, int e){
    int *distance = (int*)malloc(sizeof(int) * g->n);
    int *visited = (int*)malloc(sizeof(int)*g->n);
    int *prev = (int*)malloc(sizeof(int)*g->n);
    int *path = (int*)malloc(sizeof(int)*g->n);
    int count = 0;
    heap *h = create_heap(g->n, true);
    for(int i=0;i<g->n;i++){    
        distance[i] = INIT;
        visited[i] = 0;
        prev[i] = -1;
    }
    distance[s] = 0;
    add_heap(h, s, 0);
    int v;
    int priority;
    while(h->size > 0){
        remove_heap(h, &v, &priority);
        if(visited[v]){
            continue;
        }
        visited[v] = 1;
        if(v==e){
            break;
        }
        Node *n = g->adj_list[v];
        while(n!=0){
            int next = n->vertex;
            if(distance[next] > distance[v] + 1){
                distance[next] = distance[v] + 1;
                prev[next] = v;

                add_heap(h, next, distance[next]);
            }
            n=n->next;
        }
    }
    if(distance[e]==INIT){
        printf("%d -> %d 경로 X\n", s,e);
    }else{
        int current = e;
        while(current != -1){
            path[count++] = current;
            current = prev[current];
        }
        for(int i=count-1;i>=0;i--){        // 배열 역추적
            printf("%d", path[i]);
            if(i!=0){
                printf(" -> ");
            }
        }
        printf("\n\n");
        printf("%d ==================> %d 촌수: %d\n", s,e,distance[e]);
    }
    free(distance);
    free(visited);
    free(prev);
    free(path);
    free_heap(h);
    
}

int friendCount(Graph *g, int userId){
    int count = 0;
    Node *n = g->adj_list[userId];
    while(n!=0){
        count++;
        n = n->next;
    }
    return count;
}

void free_graph(Graph *g){
    for(int i=0;i<g->n;i++){
        Node *node = g->adj_list[i];
        while(node!=0){
            Node *temp = node;
            node = node->next;
            free(temp);
        }
        g->adj_list[i] = 0;
    }
    g->n = 0;
}
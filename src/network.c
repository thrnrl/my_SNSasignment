#include "main.h"

void init_graph(Graph *g){
    g->n = 0;
    for(int i=0;i<MAX_SIZE;i++){
        g->adj_list[i]=0;
    }
}

void add_vertex(Graph *g){
    if(g->n >= MAX_SIZE){
        printf("overflow\n");
        return;
    }
    g->n++;
}

void add_edge(Graph *g, int v1, int v2, int weight){
    Node *node;

    if(v1 >= g->n || v2 >= g->n){
        printf("vertex addting problem\n");
        return;
    }

    node = (Node*)malloc(sizeof(*node));

    if(node == 0){
        printf("memory dealocation\n");
        return;
    }
    node->vertex = v2;
    node->weight = weight;
    node->next = g->adj_list[v1];
    g->adj_list[v1]=node;

    node = (Node*)malloc(sizeof(*node));

    node->vertex = v1;
    node->weight = weight;
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
    int weight;

    while(edge_count < count){
        v1 = RANDOM(g->n);
        v2 = RANDOM(g->n);

        if(v1==v2){
            continue;
        }
        if(isExist(g, v1, v2)){
            continue;
        }
        weight = rand()%5+1;
        add_edge(g, v1, v2, weight);
        edge_count++;
    }
}

void graph_print(Graph *g){
    for(int i=0;i<g->n;i++){
        printf("%d의 이웃: ", i);
        Node *node = g->adj_list[i];

        while(node!=0){
            printf("%d(%d) ",node->vertex, node->weight);
            node = node->next;
        }
        printf("\n");
    }
}

void mutual(Graph *g, int me){
    int visited[MAX_SIZE] = {0};
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
                printf("%d ",mutual->vertex);
                visited[mutual->vertex] = 1;
            }
            mutual = mutual->next;
        }
        friend= friend->next;
    }
    printf("\n");
}

heap *create_heap(int size){
    if(size <= 0){
        return 0;
    }
    heap *h = (heap*)malloc(sizeof(heap));
    h->vertex = (int*)malloc(sizeof(int) * (size + 1));
    h->priority = (int*)malloc(sizeof(int) * (size + 1));
    h->capacity = size;
    h->size = 0;
    return h;
}
void swap(heap *h, int i, int j){
    int tmp = h->vertex[i];
    h->vertex[i] = h->vertex[j];
    h->vertex[j] = tmp;

    tmp = h->priority[i];
    h->priority[i] = h->priority[j];
    h->priority[j] = tmp;
}

int add_heap(heap *h, int v, int p){
    h->size++;
    int i = h->size;
    int parent = i/2;
    h->vertex[i] = v;
    h->priority[i] = p;
    while(i>1){
        if(h->priority[parent] <= h->priority[i]){
            break;
        }
        swap(h, i, parent);
        i = parent;
        parent = i/2;
    }
    return 1;
}

int remove_heap(heap *h, int *v, int *p){

    if(h->size == 0){
        return 0;
    }
    *v = h->vertex[1];
    *p = h->priority[1];
    h->vertex[1] = h->vertex[h->size];
    h->priority[1] = h->priority[h->size];
    h->size--;
    int i = 1;
    int child = i*2;
    while(i*2 <= h->size){
        if(child+1 <= h->size && h->priority[child+1] < h->priority[child]){
            child++;
        }
        if(h->priority[i] <= h->priority[child]){
            break;
        }
        swap(h, i, child);
        i = child;
        child = i*2;
    }
    return 1;
}

void free_heap(heap *h){
    if(h != NULL){
        free(h->vertex);
        free(h->priority);
        free(h);
    }
}

void dijkstra(Graph *g, int s, int e){
    int distance[MAX_SIZE];
    int visited[MAX_SIZE];
    int prev[MAX_SIZE];
    int path[MAX_SIZE];
    int count = 0;
    heap *h = create_heap(g->n);
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
            if(distance[next] > distance[v] + n->weight){
                distance[next] = distance[v] + n->weight;
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
        // 배열 역추적
        for(int i=count-1;i>=0;i--){
            printf("%d", path[i]);
            if(i!=0){
                printf(" -> ");
            }
        }
        printf("\n");
        printf("%d ==================> %d 최단거리: %d\n", s,e,distance[e]);
    }
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
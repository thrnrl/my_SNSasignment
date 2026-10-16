#ifndef SNS_H
#define SNS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100000
#define INIT 99999999
#define TABLE_SIZE 50000

  // =========================== //
 //            Graph            //
// =========================== //
typedef struct Node{
    int vertex; // 정점
    int weight; // 가중치
    struct Node *next; // 리스트 다음 노드
}Node;

typedef struct Graph{
    int n; // 정점 개수
    Node *adj_list[MAX_SIZE]; // 인접리스트
}Graph;

typedef struct Heap{
    int *vertex;
    int *priority;
    int capacity;
    int size;
}heap;

  // ============================= //
 //            Profile           //
// =========================== //
typedef struct Profile{
    int userId;
    char nickname[16];
    char favorite[20];
    int friendCount;
}Profile;

typedef struct profileNode{
    Profile data;
    struct profileNode *next;
}p_node;

typedef struct profileTable{
    p_node *table[TABLE_SIZE];
}p_table;

int RANDOM(int n);

/**
 *      NETWORK.C
 * 
 */

void init_graph(Graph *g);
/**
 * 그래프 초기화
 */
void add_vertex(Graph *g);

void add_edge(Graph *g, int v1, int v2, int weight);

int isExist(Graph *g,int v1, int v2);

void generate_user(Graph *g, int count);

void generate_edge(Graph *g, int count);

void graph_print(Graph *g);

void mutual(Graph *g, int user);

heap *create_heap(int size);

void swap(heap *h, int a, int b);

int add_heap(heap *h, int v, int p);

int remove_heap(heap *h, int *v, int *priority);

void dijkstra(Graph *g, int s, int e);

int friendCount(Graph *g, int userId);

void free_graph(Graph *g);

void free_heap(heap *h);

/**
 *      PROFILE.C
 * 
 */
int user(int userId);

void init_table(p_table *t);

void insert_profile(p_table *h, Profile p);

void generate_profile(p_table *t, Graph *g, int count);

Profile *search_profile(p_table *t, int userId);

void print_profile(Profile *p);

void free_table(p_table *t);

#endif

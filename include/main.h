#ifndef SNS_H
#define SNS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define USERS 100000
#define INIT 99999999
#define BUCKET 50021 //P
#define MIN_HEAP 1
#define MAX_HEAP 0
#define POSTS 200000

  // =========================== //
 //            Graph            //
// =========================== //
typedef struct Node{
    int vertex; // 정점
    struct Node *next; // 리스트 다음 노드
}Node;

typedef struct Graph{
    int n; // 정점 개수
    Node *adj_list[USERS]; // 인접리스트
}Graph;

typedef struct Heap{
    int *Id;
    int *priority;
    int capacity;
    int size;
    bool isMin; // min or max
}heap;

  // ============================= //
 //            Profile           //
// =========================== //

typedef struct Profile{
    int userId;
    char nickname[32];
    char favorite[20];
    int friendCount;
}Profile;

typedef struct profileNode{
    Profile data;
    struct profileNode *next;
}p_node;

typedef struct profileTable{
    p_node **table;
    int tablesize;
    int count;
}p_table;

  // =========================== //
 //            Post             //
// =========================== //

typedef struct Post{
    int postId;
    int userId;
    int likes;
    int uploadTime;
    char hashtag[32];
}Post;

typedef struct hashtagNode{
    char key[32];
    int postId;
    struct hashtagNode *next;
}h_node;

typedef struct hashtagTable{
    int tablesize;
    int count;
    h_node **table;
}h_table;

  // =========================== //
 //           Ranking           //
// =========================== //

typedef struct Rank{
    int userId;
    int friendCount;
}Rank;

/*      utils       */

/** 
 *      RANDOM.C 
 */

int RANDOM(int n);

/**
 *      HEAP.C
 */

heap *create_heap(int size, bool isMin);

void swap(heap *h, int a, int b);

int MinORMax(heap *h, int i, int j);

void heapify(heap *h, int i);

void build_heap(heap *h);

int add_heap(heap *h, int v, int p);

int remove_heap(heap *h, int *v, int *priority);

void free_heap(heap *h);

/**
 *      USAGE.C
 */

int Usage(int count, int tablesize);

/**
 *      NETWORK.C
 * 
 */

void init_graph(Graph *g);

void add_vertex(Graph *g);

void add_edge(Graph *g, int v1, int v2);

int isExist(Graph *g,int v1, int v2);

void generate_user(Graph *g, int count);

void generate_edge(Graph *g, int count);

void mutual(Graph *g, int user);

void dijkstra(Graph *g, int s, int e);

int friendCount(Graph *g, int userId);

void free_graph(Graph *g);


/**
 *      PROFILE.C
 * 
 */

int hash(int userId, int tablesize);

void init_table(p_table *t);

void insert_profile(p_table *h, Profile p);

void generate_profile(p_table *pt, Graph *g, int count);

Profile *search_profile(p_table *pt, int userId);

int PTrehash(p_table *pt);

void print_profile(Profile *p);

void free_table(p_table *pt);

/**
 *      FEED.C
 * 
 */

 void generate_post(Post *p, h_table *ht, int count, int userCount);

 int calculate_trendFeedScore(Post *p);

 void printTrendFeed(Post *p, int count);

 int djb2(char *hashtag, int tablesize);

 void init_hashtag(h_table *ht);

 void insert_hashtag(h_table *ht, char *tag, int postId);

 void search_hashtag(h_table *ht, Post *p, char *hashtag);

int HTrehash(h_table *ht);

 void free_hashtag(h_table *ht);


/**
 *      RANK.C
 * 
 */

void DivideANDConquer(Rank *arr, Rank *temp, int left, int right);

void merge(Rank *arr, Rank *temp, int left, int mid, int right);

void printRank(Graph *g);

#endif

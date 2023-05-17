#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define MAX_NODES 100

typedef struct Node {
    int id;
    int cost;
    int heuristic;
    struct Node* parent;
} Node;

typedef struct Edge {
    int from;
    int to;
    int cost;
} Edge;

int num_nodes = 0;
Node* nodes[MAX_NODES];
int num_edges = 0;
Edge edges[MAX_NODES * MAX_NODES];



void addnode(int id, int heuristic) {
    Node* node = malloc(sizeof(Node));
    node->id = id;
    node->heuristic = heuristic;
    node->parent = NULL;
    nodes[num_nodes++] = node;
}

void addedge(int from, int to, int cost) {
    edges[num_edges++] = (Edge){ from, to, cost };
}

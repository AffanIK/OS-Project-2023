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

void* search(void* arg) {
    int start = *(int*)arg;

    Node* open_set[MAX_NODES];
    int num_open = 0;
    Node* closed_set[MAX_NODES];
    int num_closed = 0;

    open_set[num_open++] = nodes[start];

    while (num_open > 0) {
        // Find the node with the lowest cost + heuristic in the open set
        Node* current = open_set[0];
        int index = 0;
        for (int i = 1; i < num_open; i++) {
            if (open_set[i]->cost + open_set[i]->heuristic < current->cost + current->heuristic) {
                current = open_set[i];
                index = i;
            }
        }

       
        for (int i = index; i < num_open - 1; i++) {
            open_set[i] = open_set[i + 1];
        }
        num_open--;

        closed_set[num_closed++] = current;

        // If the goal has been reached, return the path
        if (current->id == num_nodes - 1) {
            pthread_mutex_lock(&mutex);
            Node* node = current;
            while (node != NULL) {
                printf("%d ", node->id);
                node = node->parent;
            }
            printf("\n");
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        // Expand the current node
        for (int i = 0; i < num_edges; i++) {
            Edge edge = edges[i];
            if (edge.from == current->id) {
                Node* neighbor = nodes[edge.to];
                int new_cost = current->cost + edge.cost;
                if (neighbor->parent == NULL || new_cost < neighbor->cost) {
                    neighbor->cost = new_cost;
                    neighbor->parent = current;
                    int found = 0;
                    for (int j = 0; j < num_open; j++) {
                        if(open_set[j]->id == neighbor->id) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    open_set[num_open++] = neighbor;
                }
            }
        }
    }
}

return NULL;
}

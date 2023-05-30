#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 6

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} List;

int dijkstra(List* graph, int source, int target);
void printPath(int* prev, int target);

int main() {
    int cost[N][N], i, j, w, source, target, co;
    List graph[N];
    printf("\t The Shortest Path Algorithm (DIJKSTRA'S ALGORITHM in C using linked list)\n\n");
    for(i = 1; i < N; i++) {
        for(j = 1; j < N; j++) {
            cost[i][j] = INT_MAX;
        }
    }
    for(i = 1; i < N; i++) {
        for(j = i + 1; j < N; j++) {
            printf("Enter the weight of the path between nodes %d and %d: ", i, j);
            scanf("%d", &w);
            cost[i][j] = cost[j][i] = w;
        }
        printf("\n");
    }
    for(i = 1; i < N; i++) {
        graph[i].head = NULL;
        for(j = 1; j < N; j++) {
            if(cost[i][j] != INT_MAX) {
                Node* newNode = (Node*) malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->weight = cost[i][j];
                newNode->next = graph[i].head;
                graph[i].head = newNode;
            }
        }
    }
    printf("\nEnter the source: ");
    scanf("%d", &source);
    printf("\nEnter the target: ");
    scanf("%d", &target);
    co = dijkstra(graph, source, target);
    printf("\nThe Shortest Path: %d", co);
    return 0;
}

int dijkstra(List* graph, int source, int target) {
    int dist[N], prev[N], selected[N] = {0}, i, u, v, w;
    for(i = 1; i < N; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[source] = 0;
    for(i = 1; i < N; i++) {
        u = -1;
        for(v = 1; v < N; v++) {
            if(!selected[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        if(dist[u] == INT_MAX) {
            break;
        }
        selected[u] = 1;
        Node* curr = graph[u].head;
        while(curr != NULL) {
            w = curr->weight;
            v = curr->vertex;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
            curr = curr->next;
        }
    }
    printPath(prev, target);
    return dist[target];
}

void printPath(int* prev, int target) {
    if(prev[target] != -1) {
        printPath(prev, prev[target]);
    }
    printf("%c", target + 'A');
}

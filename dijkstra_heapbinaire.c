#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define IN 99
#define N 6
//oui
typedef struct {
    int vertex;
    int dist;
} Vertex;

typedef struct {
    Vertex* arr;
    int size;
    int count;
} Heap;

int dijkstra(int cost[][N], int source, int target);
void printPath(int* prev, int target);
void heapify(Heap* heap, int currentIndex);
void insert(Heap* heap, Vertex newVertex);
Vertex extractMin(Heap* heap);
int isEmpty(Heap* heap);

int main() {
    int cost[N][N], i, j, w, source, target, co;
    printf("\t The Shortest Path Algorithm (DIJKSTRA'S ALGORITHM in C  using priority queue based on a binary heap)\n\n");
    for(i = 1; i < N; i++) {
        for(j = 1; j < N; j++) {
            cost[i][j] = IN;
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
    printf("\nEnter the source: ");
    scanf("%d", &source);
    printf("\nEnter the target: ");
    scanf("%d", &target);
    co = dijkstra(cost, source, target);
    printf("\nThe Shortest Path: %d", co);
    return 0;
}

int dijkstra(int cost[][N], int source, int target) {
    int dist[N], prev[N], i, u, v, w;
    bool visited[N] = {false};
    for(i = 1; i < N; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[source] = 0;
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->arr = (Vertex*) malloc(sizeof(Vertex) * N);
    heap->size = N;
    heap->count = 0;
    Vertex newVertex;
    newVertex.vertex = source;
    newVertex.dist = 0;
    insert(heap, newVertex);
    while(!isEmpty(heap)) {
        Vertex minVertex = extractMin(heap);
        visited[minVertex.vertex] = true;
        for(v = 1; v < N; v++) {
            if(cost[minVertex.vertex][v] != IN && !visited[v]) {
                w = cost[minVertex.vertex][v];
                if(dist[minVertex.vertex] + w < dist[v]) {
                    dist[v] = dist[minVertex.vertex] + w;
                    prev[v] = minVertex.vertex;
                    newVertex.vertex = v;
                    newVertex.dist = dist[v];
                    insert(heap, newVertex);
                }
            }
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

void heapify(Heap* heap, int currentIndex) {
    int leftChild = 2 * currentIndex;
    int rightChild = 2 * currentIndex + 1;
    int smallest = currentIndex;
    if(leftChild <= heap->count && heap->arr[leftChild].dist < heap->arr[smallest].dist) {
        smallest = leftChild;
    }
    if(rightChild <= heap->count && heap->arr[rightChild].dist < heap->arr[smallest].dist) {
        smallest = rightChild;
    }
    if(smallest != currentIndex) {
        Vertex temp = heap->arr[smallest];
        heap->arr[smallest] = heap->arr[currentIndex];
        heap->arr[currentIndex] = temp;
        heapify(heap, smallest);
    }
}

void insert(Heap* heap, Vertex newVertex) {
    heap->count++;
    int currentIndex = heap->count;
    while(currentIndex > 1 && newVertex.dist < heap->arr[currentIndex / 2].dist) {
        heap->arr[currentIndex] = heap->arr[currentIndex / 2];
        currentIndex /= 2;
    }
    heap->arr[currentIndex] = newVertex;
}

Vertex extractMin(Heap* heap) {
    Vertex minVertex = heap->arr[1];
    heap->arr[1] = heap->arr[heap->count];
    heap->count--;
    heapify(heap, 1);
    return minVertex;
}

int isEmpty(Heap* heap) {
    return heap->count == 0;
}

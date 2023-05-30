#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define IN 99
#define N 6

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} List;

typedef struct {
    int vertex;
    int dist;
} Vertex;

typedef struct {
    Vertex* arr;
    int size;
} Heap;

typedef struct {
    List* arr;
    int count;
    int size;
} HashTable;

int hash(int key);
HashTable* createHashTable(int size);
void insert(HashTable* ht, int vertex, int adjVertex, int weight);ccc
void printPath(int* prev, int target);
int dijkstra(HashTable* ht, int source, int target);

int main() {
    int cost[N][N], i, j, w, source, target, co;
    HashTable* ht = createHashTable(N);
    printf("\t The Shortest Path Algorithm (DIJKSTRA'S ALGORITHM in C using hash table)\n\n");
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
    for(i = 1; i < N; i++) {
        for(j = 1; j < N; j++) {
            if(cost[i][j] != IN) {
                insert(ht, i, j, cost[i][j]);
            }
        }
    }
    printf("\nEnter the source: ");
    scanf("%d", &source);
    printf("\nEnter the target: ");
    scanf("%d", &target);
    co = dijkstra(ht, source, target);
    printf("\nThe Shortest Path: %d", co);
    return 0;
}

int hash(int key) {
    return key % N;
}

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*) malloc(sizeof(HashTable));
    ht->arr = (List*) malloc(sizeof(List) * size);
    ht->count = 0;
    ht->size = size;
    int i;
    for(i = 0; i < size; i++) {
        ht->arr[i].head = NULL;
    }
    return ht;
}

void insert(HashTable* ht, int vertex, int adjVertex, int weight) {
    int index = hash(vertex);
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = adjVertex;
    newNode->weight = weight;
    newNode->next = ht->arr[index].head;
    ht->arr[index].head = newNode;
    ht->count++;
}

void printPath(int* prev, int target) {
    if(prev[target] != -1) {
        printPath(prev, prev[target]);
    }
    printf("%c", target + 'A');
}

int dijkstra(HashTable* ht, int source, int target) {
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
    heap->arr[0].vertex = -1;
    heap->arr[0].dist = INT_MIN;
    int heapSize = 0;
    Vertex newVertex;
    newVertex.vertex = source;
    newVertex.dist = 0;
    heap->arr[++heapSize] = newVertex;
    while(heapSize != 0) {
        Vertex minVertex = heap->arr[1];
        heap->arr[1] = heap->arr[heapSize];
        heapSize--;
        int currentIndex = 1;
        while(true) {
            int leftChild = currentIndex * 2;
            int rightChild = currentIndex * 2 + 1;
            if(leftChild > heapSize) {
                break;
            }
            int smallerChild = leftChild;
            if(rightChild <= heapSize && heap->arr[rightChild].dist < heap->arr[leftChild].dist) {
                smallerChild = rightChild;
            }
            if(heap->arr[smallerChild].dist < heap->arr[currentIndex].dist) {
                Vertex temp = heap->arr[smallerChild];
                heap->arr[smallerChild] = heap->arr[currentIndex];
                heap->arr[currentIndex] = temp;
                currentIndex = smallerChild;
            } else {
                break;
            }
        }
        visited[minVertex.vertex] = true;
        Node* curr = ht->arr[minVertex.vertex].head;
        while(curr != NULL) {
            if(!visited[curr->vertex]) {
                w = curr->weight;
                v = curr->vertex;
                if(dist[minVertex.vertex] + w < dist[v]) {
                    dist[v] = dist[minVertex.vertex] + w;
                    prev[v] = minVertex.vertex;
                    newVertex.vertex = v;
                    newVertex.dist = dist[v];
                    int index = ++heapSize;
                    while(index != 1 && newVertex.dist < heap->arr[index / 2].dist) {
                        heap->arr[index] = heap->arr[index / 2];
                        index /= 2;
                    }
                    heap->arr[index] = newVertex;
                }
            }
            curr = curr->next;
        }
    }
    printPath(prev, target);
    return dist[target];
}

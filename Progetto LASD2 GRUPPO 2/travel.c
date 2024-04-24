#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "travel.h"

struct AdjListNode* newAdjListNode(
        int dest, int weight, int weight2,char name[20])
{
    struct AdjListNode* newNode =
            (struct AdjListNode*)
                    malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    strcpy(newNode->name,name);
    newNode->weight2 = weight2;
    newNode->next = NULL;
    return newNode;
}

struct Graph* Create_Graph(int V,char* name)
{
    struct Graph* graph = (struct Graph*)
            malloc(sizeof(struct Graph));
    graph->V = V;
    graph->name = name;

    graph->array = (struct AdjList*)
            malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src,
             int dest, int weight,int weight2,char name[20],char name2[20])
{
    struct AdjListNode* newNode =
            newAdjListNode(dest, weight,weight2,name);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
/*
    newNode = newAdjListNode(src, weight,weight2,name2);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;*/
}

struct MinHeapNode* newMinHeapNode(int v,
                                   int dist)
{
    struct MinHeapNode* minHeapNode =
            (struct MinHeapNode*)
                    malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
            (struct MinHeap*)
                    malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
            (struct MinHeapNode**)
                    malloc(capacity *
                           sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap,
                int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
        minHeap->array[smallest]->dist )
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
        minHeap->array[smallest]->dist )
        smallest = right;

    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode =
                minHeap->array[smallest];
        struct MinHeapNode *idxNode =
                minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}


struct MinHeapNode* extractMin(struct MinHeap*
minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root =
            minHeap->array[0];

    struct MinHeapNode* lastNode =
            minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap* minHeap,
                 int v, int dist)
{
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist <
                minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] =
                (i-1)/2;
        minHeap->pos[minHeap->array[
                (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],
                        &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}


void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void printPath(int parent[], int j,char *names[])
{
    if (parent[j]==-1)
        return;

    printPath(parent, parent[j],names);

    printf("%s->", names[j]);
}

int printSolution(int dist[], int n, int parent[],char *names[],int dest,char* srcs)
{
        if(dist[dest] == INT_MAX){
            printf("Meta non raggiungibile da %s, l'amministratore e' stato avvisato,riprova con un altra meta",srcs);
            //add_queue();
            return 0;
        }
    printf("\n\nPercorso che verra effettuato per questo viaggio:\n");
        printf("\n%s->",srcs);
        printPath(parent, dest,names);
        printf("Arrivato!\n\n");
    return 1;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %s\n head ", graph->array[v].Node_Name);
        while (pCrawl) {
            printf("-> %s", pCrawl->name);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int dijkstra(struct Graph* graph, char* name,char* dest,int check)
{

    int V = graph->V;
    int src = 0;
    int des = 0;



    int *parent = malloc(V*sizeof(int));
    for (int i = 0; i < V; ++i) {
        parent[i] = -1;
    }

    int dist[V];
    char *str_array[V*V];
    char array_i[30];


        for (src = 0; src < graph->V; ++src) {
            if(strcmp(graph->array[src].Node_Name,name) == 0){
                break;
            }
        }


    for (des = 0; des <graph->V ; ++des) {
        if(strcmp(graph->array[des].Node_Name,dest) == 0){
            break;
        }

    }


    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                           dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] =
            newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {

        struct MinHeapNode* minHeapNode =
                extractMin(minHeap);
        int k = 0;
        int u = minHeapNode->v;

        struct AdjListNode* pCrawl =
                graph->array[u].head;
        struct AdjListNode* ptest;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            if (check) {
                if (isInMinHeap(minHeap, v) &&
                    dist[u] != INT_MAX &&
                    pCrawl->weight + dist[u] < dist[v]) {
                    dist[v] = dist[u] + pCrawl->weight;
                    str_array[v]= (char*)malloc(strlen(array_i)*sizeof(char));
                    strcpy(str_array[v],pCrawl->name);
                    parent[v] = u;

                    decreaseKey(minHeap, v, dist[v]);
                }
                pCrawl = pCrawl->next;
            }else{
                if (isInMinHeap(minHeap, v) &&
                    dist[u] != INT_MAX &&
                    pCrawl->weight2 + dist[u] < dist[v]) {
                    dist[v] = dist[u] + pCrawl->weight2;
                    str_array[v]= (char*)malloc(strlen(array_i)*sizeof(char));
                    strcpy(str_array[v],pCrawl->name);
                    parent[v] = u;

                    decreaseKey(minHeap, v, dist[v]);
                }
                pCrawl = pCrawl->next;
            }
        }

    }
    //printArr(dist, V);
    int i = printSolution(dist,V,parent,str_array,des,name);
    return i;
}




struct Hotel_List* create_hnode(char* name,int id_node,char * desc,int stars){

    struct Hotel_List* tmp = NULL;

    tmp = (struct Hotel_List*) malloc(sizeof(struct Hotel_List));
    strcpy(tmp->name,name);
    strcpy(tmp->desc,desc);
    tmp->id_node = id_node;
    tmp->stars = stars;
    tmp->next = NULL;

    return tmp;
};

void print_HList(struct Hotel_List* L){

    while (L) {
        printf("\n%8s %15s %8d", L->name,L->desc,L->stars);
        L = L->next;
    }
}



#ifndef PROGETTO2LASD_TRAVEL_H
#define PROGETTO2LASD_TRAVEL_H

#endif //PROGETTO2LASD_TRAVEL_H

struct AdjListNode
{
    int dest;
    char name[20];
    int weight;
    int weight2;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
    char Node_Name[20];
};

struct Graph
{
    int V;
    char* name;
    struct AdjList* array;
};

struct MinHeap
{

    int size;
    int capacity;

    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode
{
    int  v;
    int dist;
};

struct Hotel_List{

    int id_node;
    char name[20];
    char desc[30];
    int stars;
    struct Hotel_List *next;
};

struct Graph* Create_Graph(int V,char* name);
void addEdge(struct Graph* graph, int src, int dest, int weight,int weight2,char name[20],char name2[20]);
int dijkstra(struct Graph* graph, char* name,char* des,int check);
void printArr(int dist[], int n);
void printGraph(struct Graph* graph);
struct Hotel_List* create_hnode(char* name,int id_node,char * desc, int stars);
void print_HList(struct Hotel_List* L);
#ifndef PROGETTO2LASD_DATABASE_H
#define PROGETTO2LASD_DATABASE_H

#endif //PROGETTO2LASD_DATABASE_H

#include "users.h"
#include "travel.h"




int Connection_DB();

int get_Users(User *root);
int save_users(char* name,char* password);
int Count_Nodes(char *type);
void Popolate_Graph(struct Graph* graph,char* type,int size);
void Get_Nodes_Name(char *type);
void Set_Nodes_Name(struct Graph* graph,char *type);
void print_dest(char *name);
int save_dest(char* name,char* src,char* dest,char* hotel);
struct Hotel_List* create_hlist(char* name);
void remove_node(char * graph,int node);
int check_queue();
void remove_Queue(int src,int dest);
int name_to_number(char * name,char* graph);
void add_edge_db(char* graph,int src,int dest,int weight,int weight2);
void add_queue(int src,int dest,char * name);
int get_min(char * name);
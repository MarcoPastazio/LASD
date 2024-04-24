#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"


struct User* newNode_User(char* name, char* password)
{
    User* temp = (User *)malloc(sizeof( User ) );
    strcpy(temp->name,name);
    strcpy(temp->password,password);

    temp->left = temp->right = NULL;

    return temp;
}

struct User * Create_Balanced_Tree(char* arr[], int start, int end)
{
    char *password;
    if (start > end)
        return NULL;

    int mid = (start + end)/2;
    struct User *root = newNode_User(arr[mid],password);

    root->left =  Create_Balanced_Tree(arr, start, mid-1);

    root->right = Create_Balanced_Tree(arr, mid+1, end);

    return root;
}

void Insert_User(User ** radice, const char* name, const char* password){
    if((*radice)==NULL){
        (*radice)= newNode_User(name,password);
    }else{
        if(strcmp(name, (*radice)->name) > 0){
            Insert_User(&((*radice)->right), name, password);
        }else{
            Insert_User(&((*radice)->left), name, password);
        }
    }
}

User* search_user(struct User* root, char* name)
{
    if (root == NULL || strcmp(name, root->name) == 0)
        return root;

    if (strcmp(name, root->name) > 0)
        return search_user(root->right, name);

    return search_user(root->left, name);
}



#ifndef PROGETTO2LASD_STRUCTURES_H
#define PROGETTO2LASD_STRUCTURES_H

#endif //PROGETTO2LASD_STRUCTURES_H


typedef struct User
{
    char name[20];
    char password[20];
    struct User *left, *right;
} User;



void Insert_User(User ** radice, const char* name, const char* password);
User* search_user(struct User* root, char* name);
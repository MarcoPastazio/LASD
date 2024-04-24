#include "sqlite3/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "users.h"
#include "travel.h"


int Connection_DB() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(0);
    }

    char *sql = "CREATE TABLE IF NOT EXISTS Users(U_Name TEXT NOT NULL,Password TEXT NOT NULL, PRIMARY KEY(U_Name,Password));"
                "CREATE TABLE IF NOT EXISTS Graph(idGraph TEXT NOT NULL,PRIMARY KEY(idGraph));"
                "CREATE TABLE IF NOT EXISTS Nodes(idGraph TEXT NOT NULL,Name TEXT NOT NULL,PRIMARY KEY(idGraph,Name),FOREIGN KEY(idGraph) REFERENCES Graph(idGraph) ON UPDATE CASCADE ON DELETE CASCADE);"
                "CREATE TABLE IF NOT EXISTS Edge(idGraph TEXT NOT NULL,L_Name Text NOT NULL,R_Name TEXT NOT NULL,Cost FLOAT,DISTANCE INTEGER NOT NULL,PRIMARY KEY(idGraph,L_Name,R_Name),FOREIGN KEY(idGraph) REFERENCES Graph(idGraph) ON UPDATE CASCADE ON DELETE CASCADE,FOREIGN KEY(L_Name) REFERENCES Nodes(Name) ON UPDATE CASCADE ON DELETE CASCADE,FOREIGN KEY(R_Name) REFERENCES Nodes(Name) ON UPDATE CASCADE ON DELETE CASCADE);"
                "CREATE TABLE IF NOT EXISTS Hotel(H_Name TEXT NOT NULL,Description TEXT,Cost_FN INTEGER NOT NULL,Stars FLOAT NOT NULL,PRIMARY KEY(H_Name),FOREIGN KEY(H_Name) REFERENCES Nodes(Name));"
                "CREATE TABLE IF NOT EXISTS Travel(U_Name TEXT NOT NULL,Origin TEXT NOT NULL,Dest TEXT NOT NULL,H_Name TEXT NOT NULL,PRIMARY KEY(U_Name),FOREIGN KEY(U_Name) REFERENCES User(U_Name),FOREIGN KEY(H_Name) REFERENCES Hotel(H_Name));";


    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);
    return 0;
}


int save_users(char* name,char* password){

    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(0);
    }

    char *sql = "INSERT INTO USERS VALUES (?,?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, name, -1,NULL);
        sqlite3_bind_text(res, 2, password, -1,NULL);
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);

    sqlite3_close(db);

    return 0;
}

int get_Users(User *root) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    rc = sqlite3_prepare_v2(
            db, "SELECT * From Users",
            -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    while (1) {
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return 1;
        }
        Insert_User(&root, sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void Set_Nodes_Name(struct Graph* graph,char *type){
    sqlite3 *db;
    int rc,i = 0;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "SELECT Name FROM Nodes WHERE idGraph = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, type, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }

        strcpy(graph->array[i].Node_Name, (char *) sqlite3_column_text(res, 0));
        i++;
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

}


int check_queue(){
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    sqlite3_stmt *stmt2 = NULL;
    int rc = 0;
    int res;
    int i = 0,k;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    sqlite3_prepare_v2(
            db, "SELECT Q.L_Name,Q.R_name,N.Name,N2.Name,U_NAME From Queue AS Q,Nodes AS N,Nodes AS N2  where Q.L_name = N.idNodes and Q.R_name = N2.idNodes",
            -1, &stmt, NULL);

    while (1) {
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return 1;
        }

        printf("\nAVVISO! L'utente %s voleva prenotare un viaggio da %s a %s ma non e' raggiungibile (per rimuovere questa notifica rendere raggiungibile o rimuovere la meta)\n",sqlite3_column_text(stmt,4),sqlite3_column_text(stmt,2),sqlite3_column_text(stmt,3));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return i;

}

void Popolate_Graph(struct Graph* graph,char* type,int size){
    sqlite3 *db;
    int rc,tag=0,min;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "SELECT L_NAME,R_NAME,COST,DISTANCE,N.Name,N2.Name FROM EDGE AS E,Nodes AS N,Nodes AS N2 WHERE E.idGraph = ? AND R_NAME = N.idNodes AND L_NAME = N2.idNodes";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, type, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }

        if(tag == 0){
            min = sqlite3_column_int(res,0);
            tag = 1;
        }
            addEdge(graph,sqlite3_column_int(res,0) - min,sqlite3_column_int(res,1) - min,sqlite3_column_int(res,2),sqlite3_column_int(res,3),(char *) sqlite3_column_text(res,4),(char *) sqlite3_column_text(res,5));
    }
    Set_Nodes_Name(graph,type);
    sqlite3_finalize(res);
    sqlite3_close(db);

}

int Count_Nodes(char *type){
    sqlite3 *db;
    int rc,i;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    char *sql = "SELECT COUNT(*) AS COUNT FROM NODES WHERE idGraph = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, type, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    i = sqlite3_column_int(res,0);

    sqlite3_finalize(res);
    sqlite3_close(db);

    return i;
}

void Get_Nodes_Name(char *type){
    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "SELECT Name FROM Nodes WHERE idGraph = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, type, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }
        printf("%s\n",sqlite3_column_text(res, 0));
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

}

void print_dest(char *name){
    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "SELECT * FROM Travel WHERE U_Name = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, name, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }
        printf("%-15s %-15s %-15s\n",sqlite3_column_text(res, 1),sqlite3_column_text(res, 2),sqlite3_column_text(res, 3));
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

}

void remove_edge(char * graph,int node){
    sqlite3 *db;
    int rc = 0;
    sqlite3_stmt *res;


    rc = sqlite3_open("test.db", &db);
    char sql[80] = "Delete From Edge where idGraph = ? and (L_Name= ? OR R_Name = ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, graph,-1,NULL);
        sqlite3_bind_int(res, 2, node);
        sqlite3_bind_int(res, 3, node);
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void remove_node(char * graph,int node){
    sqlite3 *db;
    int rc = 0;
    sqlite3_stmt *res;


    rc = sqlite3_open("test.db", &db);
    char sql[60] = "Delete From Nodes where idGraph = ? and idNodes= ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, graph,-1,NULL);
        sqlite3_bind_int(res, 2, node);
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    remove_edge(graph,node);
    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}



int save_dest(char* name,char* src,char* dest,char* hotel){

    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(0);
    }

    char *sql = "INSERT INTO Travel VALUES (?,?,?,?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, name, -1,NULL);
        sqlite3_bind_text(res, 2, src, -1,NULL);
        sqlite3_bind_text(res, 3, dest, -1,NULL);
        sqlite3_bind_text(res, 4, hotel, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);

    sqlite3_close(db);

    return 0;
}


struct Hotel_List* create_hlist(char* name){

    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;
    struct Hotel_List* L = NULL,*tmp = NULL;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    char *sql = "SELECT H_Name,idNodes,Description,Stars FROM Hotel,Nodes WHERE idGraph = ? AND H_Name = Name";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, name, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }
        tmp = create_hnode((char *) sqlite3_column_text(res, 0),sqlite3_column_int(res, 1),(char *) sqlite3_column_text(res, 2),sqlite3_column_int(res, 3));

        if (!L){
            L = tmp;
        }else{
            tmp->next = L;
            L = tmp;
        }
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

    return L;
}

void add_edge_db(char* graph,int src,int dest,int weight,int weight2){
    sqlite3 *db;
    int rc = 0;
    sqlite3_stmt *res;


    rc = sqlite3_open("test.db", &db);
    char sql[60] = "INSERT INTO EDGE VALUES(?,?,?,?,?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, graph, -1,NULL);
        sqlite3_bind_int(res, 2, src);
        sqlite3_bind_int(res, 3, dest);
        sqlite3_bind_int(res, 4, weight);
        sqlite3_bind_int(res, 5, weight2);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void remove_Queue(int src,int dest){
    sqlite3 *db;
    int rc = 0;
    sqlite3_stmt *res;


    rc = sqlite3_open("test.db", &db);
    char sql[60] = "Delete From queue where L_NAME = ? and R_name = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, src);
        sqlite3_bind_int(res, 2, dest);
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void add_queue(int src,int dest,char * name){
    sqlite3 *db;
    int rc = 0;
    sqlite3_stmt *res;


    rc = sqlite3_open("test.db", &db);
    char sql[60] = "INSERT INTO Queue VALUES(?,?,?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


    if (rc == SQLITE_OK) {

        sqlite3_bind_int(res, 1, src);
        sqlite3_bind_int(res, 2, dest);
        sqlite3_bind_text(res, 3, name, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(res);
    sqlite3_finalize(res);
    sqlite3_close(db);
}

int name_to_number(char * name,char * graph){

    sqlite3 *db;
    int rc,src;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    char *sql = "SELECT idNodes FROM Nodes WHERE Name = ? AND idGraph = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, name, -1,NULL);
        sqlite3_bind_text(res, 2, graph, -1,NULL);
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }
        src = sqlite3_column_int(res, 0);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

    return src;
}

int get_min(char * name){

    sqlite3 *db;
    int rc,src;
    sqlite3_stmt *res;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    char *sql = "SELECT idNodes FROM Nodes WHERE idGraph = ? LIMIT 1";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_text(res, 1, name, -1,NULL);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (1) {
        rc = sqlite3_step(res);
        if (rc == SQLITE_DONE) {
            break;
        } else if (rc != SQLITE_ROW) {
            fprintf(stderr, "Problem: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(res);
        }
        src = sqlite3_column_int(res, 0);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);

    return src;
}
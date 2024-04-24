#include <stdio.h>
#include "database.h"
#include <unistd.h>


int main() {
    char name[20], password[16], *name_saved,keys[20],keys2[20],keys3[20],keys4[20],keys5[20],keys6[20],keys7[20];
    User *root = NULL;
    int key, admin = 0;
    static int login = 0;
    int type,i,m = 0,type2,weight,weight2;
    struct Graph* graph_aereo = NULL;
    struct Graph* graph = NULL;
    struct Graph* graph_treno = NULL;
    struct Graph* graph_city = NULL;
    struct Hotel_List * h_list = NULL;

    Connection_DB();
    Insert_User(&root, "admin", "admin");
    get_Users(root);
    i = Count_Nodes("aeroporti");
    graph_aereo = Create_Graph(i,"aeroporti");
    Popolate_Graph(graph_aereo,"aeroporti",graph_aereo->V);
    i = Count_Nodes("treni");
    graph_treno = Create_Graph(i,"treni");
    Popolate_Graph(graph_treno,"treni",graph_treno->V);

    while (1) {
        if (!login) {
            printf("Inserisci il nome:");
            scanf("%s", name);
            printf("Inserisci la password:");
            scanf("%s", password);
            User *nodo = search_user(root, name);
            if (nodo && strcmp(nodo->password, password) == 0) {
                login = 1;
                if (strcmp(nodo->name, "admin") == 0){
                    admin = 1;
                }

            } else if (nodo && strcmp(nodo->password, password) != 0) {
                printf("password sbagliata\n");
                continue;
            } else {
                Insert_User(&root, name, password);
                save_users(name, password);
                login = 1;
            }
        }

        User *nodo = search_user(root, name);
        printf("            ______\n"
               "            _\\ _~-\\___\n"
               "    =  = ==(____AA____D                                                               @@@\"\"\"\"\"\"\"\"\"\"\"\"\"*\n"
               "                \\_____\\___________________,-~~~~~~~`-.._                            @\" ___ ___________\n"
               "                /     o O o o o o O O o o o o o o O o  |\\_                           II__[w] | [i] [z] |\n"
               "                `~-.__        ___..----..                  )                         {======|_|~~~~~~~~~|\n"
               "                      `---~~\\___________/------------`````                         /oO--000'\"`-OO---OO-'\n"
               "                      =  ===(_________D                               **************************************\n"
               "By Carmine Mascia, Alessandro Mauriello e Marco Pastore\n\n"
               );
        if(admin)
            check_queue();

        printf("\nBenvenuto, per continuare inserisci una delle seguenti lettere:\n\n");
        printf("q. Uscita del programma\n");
        printf("a. Prenota viaggio\n");
        printf("b. Visualizza le tue prenotazioni\n");
        if (admin) {
            printf("c. Rendi Raggiungibile meta\n");
            printf("d. Elimina meta\n");
        }
        printf("\n\n");
        scanf(" %s",&key);


        switch (key) {
            case 'q':
                printf("Arrivederci e buona giornata.");
                exit(0);
            case 'a':
                printf("Viaggio con treno o aereo?");
                scanf("%s",keys3);
                if(strcmp("aereo",keys3)== 0){
                    graph = graph_aereo;
                    type2 = 0;
                    strcpy(keys3,"aeroporti");
                }else if(strcmp("treno",keys3) == 0){
                    graph = graph_treno;
                    type2 = 1;
                    strcpy(keys3,"treni");
                }

                printf("\nLista di mete:\n ");
                Get_Nodes_Name(keys3);
                printf("\n\nInserisci il nome della citta' di partenza: ");
                scanf("%s",keys);
                printf("\n\n Inserisci il nome della citta' di destinazione: ");
                scanf("%s",keys2);
                printf("Inserire 1 per viaggio piu' economico o 0 per il viaggio piu' veloce: ");
                int l;
                scanf("%d",&l);
                if(!dijkstra(graph,keys,keys2,l)) {
                    printf("%s %s",keys,graph->name);
                    add_queue(name_to_number(keys,graph->name),name_to_number(keys2,graph->name),name);
                    break;
                }
                i = Count_Nodes(keys2);
                graph_city = Create_Graph(i,keys2);
                Popolate_Graph(graph_city,keys2,graph_city->V);
                h_list = create_hlist(keys2);
                printf("Ecco a voi una lista di hotel presenti in questa meta: ");
                printf("\n\n%8s %15s %10s", "Nome","Descrizione","Stelle");
                print_HList(h_list);
                printf("\n\n Inserisca il nome dell'hotel in cui desidera prenotare: ");
                fflush(stdin);
                scanf("%[^\n]%*c", keys4);
                char t[20];
                if(!type2){
                    strcpy(t, keys2);
                    strcat(t," A.");
                }else if(type2){
                    strcpy(t, keys2);
                    strcat(t," T.");
                }
                if(!dijkstra(graph_city,t,keys4,l)) {
                    break;
                }
                save_dest(name,keys,keys2,keys4);
                printf("\nPrenotato!\n\n");
                break;
            case 'b':
                printf("Ecco la lista delle tue prenotazioni:\n\n");
                printf("%-15s %-15s %-15s\n", "Origine", "Destinazione","Nome Albergo");
                print_dest(name);
                system("PAUSE");
                system("cls");
                break;
            case 'c':
                if(admin){
                    printf("\n\nInserisci il nome della citta' da rendere raggiungibile: ");
                    scanf("%s",keys5);
                    printf("\n\nInserisci il nome della citta' da cui sará raggiungibile: ");
                    scanf("%s",keys6);
                    printf("\n\nInserisci il mezzo di trasporto aereo o treno: ");
                    scanf("%s",keys7);
                    printf("\n\nInserisci il costo e la il tempo del volo/treno");\
                    scanf("%d %d",&weight,&weight2);

                    if(strcmp("aereo",keys7)== 0)
                        graph = graph_aereo;
                    else if(strcmp("treno",keys7) == 0)
                        graph = graph_treno;
                    int kl = name_to_number(keys5,graph->name);
                    int kl2 = name_to_number(keys6,graph->name);
                    int min = get_min(graph->name);
                    addEdge(graph, kl - min,kl2 - min,weight,weight2,keys5,keys6);
                    add_edge_db(graph->name,kl,kl2,weight,weight2);
                    remove_Queue(kl, kl2);
                }
                break;
            case 'd':
                if(admin){
                    printf("\n\nInserisci il nome della meta da eliminare: ");
                    scanf("%s",keys5);
                    printf("\n\nInserisci il mezzo di trasporto aereo o treno: ");
                    scanf("%s",keys7);

                    if(strcmp("aereo",keys7)== 0)
                        graph = graph_aereo;
                    else if(strcmp("treno",keys7) == 0)
                        graph = graph_treno;
                    int kl = name_to_number(keys5,graph->name);
                    remove_node(graph->name,kl);
                }
                break;
        }
    }
}
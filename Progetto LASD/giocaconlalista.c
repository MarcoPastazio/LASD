#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

lista *giocaconlalista(lista *head){
	
	char r, r1;
	lista *nodo = NULL;
	char abbigliamento[400];
	char marca[400];
	char taglia[400];
	int quantita;
	float prezzo;
	
	//siccome l'amministratore fa solo poche cose, gliele faccio fare in maniera sequenziale all'interno di una stessa funzione.
	
	do{
		printf("Vuoi aggiungere un nuovo prodotto(Y per si e N per no)? ");
		fflush(stdin);
		scanf("%c", &r);
	}while(r != 'Y' && r != 'N');
	
	if(r == 'Y'){
		printf("\nQuale capo d'abbigliamento vuoi? ");
		scanf("%s", abbigliamento);
		fflush(stdin);
		printf("\nDi che marca lo vuoi? ");
		scanf("%s", marca);
		fflush(stdin);
		printf("\nDi che taglia? ");
		fflush(stdin);
		scanf("%s", taglia);
		do{
			printf("\nQuanti ne vuoi? ");
			fflush(stdin);
			scanf("%d", &quantita);
		}while (quantita <= 0);
		printf("\nA quanto lo vuoi vendere? ");
		fflush(stdin);
		scanf("%f", &prezzo);
		
		
		nodo = (lista *) malloc (sizeof(lista));
		nodo = nuovonodo(abbigliamento, marca, taglia, quantita, prezzo);
		if(nodo == NULL)
		{
			printf("sono uscito");
		}
		
		head = inserisci(nodo, head);		
	}else{
		do{
			printf("Vuoi aggiornare un prodotto in magazzino(Y per si e N per no)? ");
			fflush(stdin);
			scanf("%c", &r1);
		}while(r1 != 'Y' && r1 != 'N');
		
		if(r1 == 'Y'){
			printf("\nQuale capo d'abbigliamento vuoi? ");
			scanf("%s", abbigliamento);
			fflush(stdin);
			printf("\nDi che marca lo vuoi? ");
			scanf("%s", marca);
			fflush(stdin);
			printf("\nDi che taglia? ");
			fflush(stdin);
			scanf("%s", taglia);
			do{
				printf("\nQuanti ne vuoi? ");
				fflush(stdin);
				scanf("%d", &quantita);
			}while (quantita <= 0);
			printf("\nA quanto lo vuoi vendere? ");
			fflush(stdin);
			scanf("%f", &prezzo);
			
			nodo = ricercanodo(head, abbigliamento, marca, taglia, quantita);
			nodo->quantita = quantita;
			nodo->prezzo = prezzo;
		}
	}
	
	return head;
}

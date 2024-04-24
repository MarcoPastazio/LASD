#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

lista *caricacarrello(lista *carrello, lista *head){

	lista *nodo = NULL;
	FILE *desideri;
	float prezzo;
	char abbigliamento[400];
	char marca[400];
	char taglia[400];
	int quantita;
	
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
			
	nodo = ricercanodo(head, abbigliamento, marca, taglia, quantita);
	
	if(nodo == NULL){
		desideri = fopen("Attesa.txt", "w");
		if(desideri == NULL) 
		{
			printf("\nsono qui\n");
		}
		scrivifiledattesa(desideri, abbigliamento, marca, taglia, quantita);
		fclose(desideri);
		printf("\nQuesto elemento e' stato caricato in un file d'attesa");
	}else{	
		if(quantita > nodo->quantita){
			printf("Questo elemento non e' stato caricato nel carrello perchè ne ha ordinati troppi");
		}else{
			nodo = nuovonodo(abbigliamento, marca, taglia, quantita, quantita*nodo->prezzo);
			carrello = inserisci(nodo, carrello);
		}
	}
	
	return carrello;
}

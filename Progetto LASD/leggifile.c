#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"


lista *leggifile(FILE *fp, lista *head){
	
	char abbigliamento[400];
	char marca[400];
	char taglia[400];
	int quantita;
	float prezzo;
	
	lista *nodo = NULL;
	if(fscanf(fp," %s%s%s%d%f", abbigliamento, marca, taglia, &quantita, &prezzo)==5)
	{
		nodo = (lista *) malloc (sizeof(lista));
		nodo = nuovonodo(abbigliamento, marca, taglia, quantita, prezzo);
		if(nodo == NULL)
		{
			printf("sono uscito");
		}
		
		head = inserisci(nodo, head);
		head->next = leggifile(fp, head->next);
	}
	return head;
}

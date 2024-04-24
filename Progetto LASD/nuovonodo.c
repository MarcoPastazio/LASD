#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"


lista *nuovonodo(char *abbigliamento, char *marca, char *taglia, int quantita, float prezzo)
{	
	lista *nodo = (lista *) malloc (sizeof(lista));
	if (nodo ==NULL)
	{
		printf("generato un errore");
		return NULL;
	}
	nodo->marca=(char *)malloc (sizeof(char)*strlen(marca));
	nodo->abbigliamento=(char *)malloc (sizeof(char)*strlen(abbigliamento));
	nodo->taglia=(char *)malloc (sizeof(char)*strlen(taglia));
	
	strcpy(nodo->abbigliamento, abbigliamento);
	strcpy(nodo->marca, marca);
	strcpy(nodo->taglia, taglia);
	nodo->quantita = quantita;
	nodo->prezzo = prezzo;
	nodo->next = NULL;
	
	return nodo;
}

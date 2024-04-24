#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

lista *ricercanodo(lista *head, char *abbigliamento, char *marca, char *taglia, int quantita){
	
	lista *nodo = NULL;
	
	if(head != NULL)
	{
		if(strcmp(head->abbigliamento,abbigliamento) == 0 && strcmp(head->marca, marca) == 0 && strcmp(head->taglia, taglia) == 0){
			return head;
		}else{
			return ricercanodo(head->next, abbigliamento, marca, taglia, quantita);
		}
	}
	
	return head;
}

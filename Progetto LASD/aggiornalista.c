#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

lista *aggiornalista(lista *head, lista *carrello){
	
	lista *nodo = NULL;
	if(carrello == NULL){
		return head;
	}else{
		head = aggiornalista(head, carrello->next);
		nodo = ricercanodo(head, carrello->abbigliamento, carrello->marca, carrello->taglia, carrello->quantita);
		nodo->quantita = nodo->quantita - carrello->quantita;
	}
	return head;
}

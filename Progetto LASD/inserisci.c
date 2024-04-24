#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"


lista *inserisci(lista *nodo, lista *head){
	if(head == NULL){
		head = nodo;
	}else{
		head->next = inserisci(nodo, head->next);
	}
}

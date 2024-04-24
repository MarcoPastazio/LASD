#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

lista *svuotalista(lista *head){
	
	if ( head != NULL ){
		head->next = svuotalista(head->next);
		free(head);
	} 
	return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

float contasaldo(lista *carrello){
	
	float newsaldo;
	
	if(carrello->next == NULL){
		return carrello->prezzo;
	}else{
		newsaldo = carrello->prezzo + contasaldo(carrello->next);
	}
	
	return newsaldo;
}

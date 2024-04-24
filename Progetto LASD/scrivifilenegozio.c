#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

void scrivifilenegozio(FILE *fp, lista *head){
	
	if(head != NULL){
		
		scrivifilenegozio(fp, head->next);
		fprintf(fp, "%s %s %s %d %.2f\n", head->abbigliamento, head->marca, head->taglia, head->quantita, head->prezzo);
	}
}

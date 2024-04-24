#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"


void print(lista *head, int count){
	if(head != NULL){
		printf("|%s %s %s %d %.2f| ", head->abbigliamento, head->marca, head->taglia, head->quantita, head->prezzo);
		if(head->next != NULL){
			printf("->");
		}
		if(count%3==0){
			printf("\n");
		}
		count++;
		print(head->next, count);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

void inseriscimailepassword(char *mailrec, char *passwordrec){
	
	int count = 0;//mi serve solo a mandare il messaggio di errore
	char mailins[100];
	char passwordins[100];

	do{

		if(count>0){
			printf("O la mail o la password sono errate\n");
		}
		printf("Metti la mail: ");
		scanf("%s", mailins);
		
		printf("Adesso metti la password: ");
		scanf("%s", passwordins);
		
		count++;
		
		
	}while (strcmp(mailrec, mailins) != 0 || strcmp(passwordrec, passwordins) != 0);
}

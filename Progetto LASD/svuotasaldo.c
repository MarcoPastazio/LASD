#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"


float svuotasaldo(float saldo){
	
	char risposta;
	
	do{
		printf("\nVuoi svuotare la carta(Y per svuotare e N per bloccare l'operazione)? ");
		fflush(stdin);
		scanf("%c", &risposta);
	}while(risposta != 'Y' && risposta != 'N');
	//ulteriore check per confermare assolutamente questa operazione
	if(risposta == 'Y'){
		saldo = 0;
		printf("\nMi dispiace assai\n");
	}
	return saldo;
}


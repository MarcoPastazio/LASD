#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

int acquistocarrello(lista *carrello, float saldo){
	
	int ok = 0;//check per vedere se posso effettivamente svuotare il carrello o meno
	char r;
	float saldoacquisti = 0;

	printf("\nVuoi procedere con l'acquisto del tuo carrello(Y per procedere e qualsiasi altro tasto per negare l'operazione)? ");
	fflush(stdin);
	scanf("%c", &r);
	
	saldoacquisti = contasaldo(carrello);//check per vedere se si può fare l'acquisto
	
	if(r == 'Y'){
		if(saldo < saldoacquisti){
			printf("\nNon puoi effettuare l'acquisto, devi prima fare una ricarica\n");
			ok = 0;
		}else{
			ok = 1;
		}	
	}
	
	return ok;
}

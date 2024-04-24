#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

float aggiornasaldo(float saldo, float tmpsaldo, lista *carrello){
	
	if(carrello == NULL){
		saldo = saldo - tmpsaldo;
	}
	
	return saldo;
}

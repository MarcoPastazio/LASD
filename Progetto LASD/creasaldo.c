#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

float creasaldo(float saldo){
	printf("Quando vuoi caricare sulla tua carta? ");
	scanf("%f", &saldo);
	return saldo;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

void scrivifiledattesa(FILE *fp, char *abbigliamento, char *marca, char *taglia, int quantita){
		
	fprintf(fp, "%s %s %s %d\n", abbigliamento, marca, taglia, quantita);
}

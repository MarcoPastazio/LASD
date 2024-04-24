#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

void scrivifile(FILE *fp, char *mailrec, char *passwordrec, float saldo){
	
	fprintf(fp, "\n%s %s %.2f", mailrec, passwordrec, saldo);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

void aggiornautente(FILE *fp, char *mailrec, char *passwordrec, float saldo, FILE *fpUt){
	
	char mailver[400];
	char passwordver[400];
	float saldover;
	
	if(fscanf(fp, " %s%s%f", mailver, passwordver, &saldover)==3){
		if(strcmp(mailver, mailrec) == 0 && strcmp(passwordver, passwordrec) == 0){
			aggiornautente(fp, mailrec, passwordrec, saldo, fpUt);//non fa nulla e vai avanti
		}else{//altrimnti scrivo
			aggiornautente(fp, mailrec, passwordrec, saldo, fpUt);
			fprintf(fpUt, "%s %s %.2f\n", mailver, passwordver, saldover);
		}	
	}
}

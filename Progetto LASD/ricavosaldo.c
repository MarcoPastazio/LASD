#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

float ricavosaldo(FILE *fp, char *mailrec, char *passwordrec, float saldo){
	
	float newsaldo;
	char mailver[400];
	char passwordver[400];
	
	if(fscanf(fp, " %s%s%f", mailver, passwordver, &saldo)==3){
		
		if(strcmp(mailver, mailrec) == 0 && strcmp(passwordver, passwordrec) == 0){
			newsaldo = saldo;
		}else{
			newsaldo = ricavosaldo(fp, mailrec, passwordrec, saldo);
		}
	}
	
	return newsaldo;
}

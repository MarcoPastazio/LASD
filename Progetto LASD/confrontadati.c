#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

int confrontadati(FILE *fp, char *mailrec, char *passwordrec, float saldo){
	
	int ok = 0;
	char mailver[400];
	char passwordver[400];
	
	
	if(fscanf(fp, " %s%s%f", mailver, passwordver, &saldo)==3){
		
		if(strcmp(mailver, mailrec) == 0 && strcmp(passwordver, passwordrec) == 0){
			ok = 1;
		}else{
			ok = confrontadati(fp, mailrec, passwordrec, saldo);
		}
	}

	return ok;
}


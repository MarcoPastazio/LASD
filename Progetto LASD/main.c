#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"

int main(){
	char mailrec[30];//mail con cui si registra
	char passwordrec[25];//password con cui vuole accedere al suo account
	char c;//per fare il check se e' un cliente o un amministratore
	char r;//per vedere se sei registrato o meno
	FILE *fpIn;//file dove stanno i prodotti del negozio
	FILE *fpIn2;//file dove sta la lista degli utenti registrati
	FILE *fpUt;//file temporaneo per l'aggiornamento del saldo utente
	lista *head = NULL;//lista dei prodotti a disposizione del cliente
	lista *carrello = NULL;//prodotti desiderati dal cliente
	int count = 1;//per fare una stampa più carina
	int count1 = 0;//check per vedere se è sbagliata la password
	float saldo;//il saldo del cliente
	int ok;//flag che mi serve successivamente per vedere se i dati d'accesso che mette il cliente sono uguali ai dati che stanno nel file utente
	float tmpsaldo;//mi serve a salvarmi la somma dei prezzi che stanno nel carrello e mi serve anche per aggiornare il saldo
	int check;//check mi serve per verificare se posso svuotare il carrello e aggiornare la lista oppure no
	int x;//per gestire i vari casi
		
	printf("Benvenuto a Trapswag, se compri sarai un po' piu' swag.\n");
	
	do{
		printf("Sei cliente o amministratore(c per cliente e a per amministratore)? ");
		fflush(stdin);
		scanf("%c", &c);
	}while(c != 'c' && c != 'a');
	
	
	if(c == 'c'){
		printf("Prima di cominciare i tuoi acquisti, devi essere necessariamente registrato.\n");
		do{
			printf("Sei registrato?(Y se sei gia' registrato sulla piattaforma e N per registrarti sulla piattaforma) ");
			fflush(stdin);
			scanf("%c", &r);
		}while(r != 'Y' && r != 'N');
		
		if(r == 'N'){
			//l'utente che si registra parte con 0!
			printf("Per registrarti ci serve solamente la tua mail.\nQual e' la tua mail? ");
			scanf("%s", mailrec);
			printf("\nPerfetto. Adesso puoi anche decidere la password: ");
			scanf("%s", passwordrec);
			fpIn2 = fopen("Utente.txt", "a");
			if(fpIn2 == NULL) 
			{
				printf("\nsono qui\n");
			}
			scrivifile(fpIn2, mailrec, passwordrec, saldo);
			fclose(fpIn2);
			inseriscimailepassword(mailrec, passwordrec);//funzione che mi serve ad accettarmi che il cliente metta i dati correttamente
		}else{
			do{
				if(count1 > 0){
					printf("O la mail o la password sono errate\n");
				}
				printf("Qual e' la tua mail? ");
				scanf("%s", mailrec);
				printf("\nPerfetto. Qual e' la password? ");
				scanf("%s", passwordrec);
				fpIn2 = fopen("Utente.txt", "r");
				ok = confrontadati(fpIn2, mailrec, passwordrec, saldo);//confronto i dati per verificare la validità dell'accesso
				fclose(fpIn2);
				fpIn2 = fopen("Utente.txt", "r");//riapro il file perchè altrimenti la riga del file raggiunta precedentemente non viene riletta
				saldo = ricavosaldo(fpIn2, mailrec, passwordrec, saldo);//ricavo il saldo e me lo salvo
				fclose(fpIn2);
				count1++;//mi serve solo per mandare il messaggio di errore, originariamente volevo fare che se il count fosse arrivato a 3,
				//il sistema bloccava l'account
			}while(ok == 0);
		}
		do{
			system("cls");
			printf("Saldo attuale = %.2f\n\n", saldo);
			printf("\n1) Caricare soldi XD\n");
			printf("2) Svuotare il conto :(\n");
			printf("3) Riempire il carrello ;)\n");
			printf("4) Acquistare il carrello\n");
			printf("5) Svuotare il carrello\n");
			printf("6) Effettuare il logout\n");
			printf("Scegli con il numero citato l'operazione che vuoi fare: ");
			fflush(stdin);
			scanf("%d", &x);
			
			switch(x){
				case 1:
					saldo += creasaldo(saldo);
					break;
				case 2:
					saldo = svuotasaldo(saldo);
					break;
				case 3:
					if(head == NULL){
						fpIn = fopen("Negozio.txt", "r");
						if(fpIn == NULL) 
						{
							printf("\nsono qui\n");
						}
	
						head = leggifile(fpIn, head);
						fclose(fpIn);
					}
					
					printf("\nQuesti sono i prodotti disponibili:\n");
					printf("Se inserisci un prodotto non presente, verra' caricato su una lista d'attesa.\n");
					print(head, count);
	
					carrello = caricacarrello(carrello, head);//creo il mio carrello per gli acquisti, ma nel caso in cui non ci sta
					//l'articolo, lo metto in un file chiamato Attesa.txt
					break;
				case 4:
					if(carrello == NULL){
						printf("\nNon ci sta nulla!\n");
					}else{
						print(carrello, count);
						tmpsaldo = contasaldo(carrello);
						check = acquistocarrello(carrello, saldo);
						if(check == 1){
							head = aggiornalista(head, carrello);
							carrello = svuotalista(carrello);
							fpIn = fopen("Negozio.txt", "w");
							if(fpIn == NULL) 
							{
								printf("\nsono qui\n");
							}
							scrivifilenegozio(fpIn, head);
							fclose(fpIn);
						}else{
							tmpsaldo = 0;
						}
						saldo = aggiornasaldo(saldo, tmpsaldo, carrello);
					}
					break;
				case 5:
					if(carrello == NULL){
						printf("Nel carrello non ci sta nulla");
					}else{
						carrello = svuotalista(carrello);
					}
				case 6:
						fpIn2 = fopen("Utente.txt", "r");
						if(fpIn2 == NULL) 
						{
							printf("\nsono qui\n");
						}
						fpUt = fopen("Utentetmp.txt", "w");
						if(fpUt == NULL) 
						{
							printf("\nsono qui\n");
						}
						aggiornautente(fpIn2, mailrec, passwordrec, saldo, fpUt);
						scrivifile(fpUt, mailrec, passwordrec, saldo);
						fclose(fpIn2);
						fclose(fpUt);
						//il file temporaneo lo cancello e cambio il nome
						if (remove("Utente.txt")!=0){
							printf("ERRORE nella remove!");
							return 0;
						}
						if (rename("Utentetmp.txt","Utente.txt")!=0) {
							printf("ERRORE nella rename!");
							return 0;
						}
						break;
				default:
					printf("Numero non compreso");
			}
		}while(x>0 && x<=5 || x>6);
	}else{
		printf("Accedi al tuo account inserendo mail e password.\nInserisci prima la mail: ");
		scanf("%s", mailrec);
		printf("Inserisci la password: ");
		scanf("%s", passwordrec);
		//è un check dei dati molto fittizio, potevo fare lo stesso check che facevo ai clienti, però sono solo funzioni ripetitive
		system ("cls");
		fpIn = fopen("Negozio.txt", "r");
		if(fpIn == NULL) 
		{
			printf("\nsono qui\n");
		}
	
		head = leggifile(fpIn, head);
		head = giocaconlalista(head);//significa che l'amministratore o aggiunge cose alla lista oppure la modifica
		fclose(fpIn);
		fpIn = fopen("Negozio.txt", "w");
		if(fpIn == NULL) 
		{
			printf("\nsono qui\n");
		}
		scrivifilenegozio(fpIn, head);//mi riscrivo il file negozio aggiornato
		fclose(fpIn);
	}
	return 0;
}

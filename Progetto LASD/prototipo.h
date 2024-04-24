#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
	char *abbigliamento;
	char *marca;
	char *taglia;
	int quantita;
	float prezzo;
	struct lista *next;
}lista;

//parte della gestione dei clienti
void inseriscimailepassword(char *mailrec, char *passwordrec);
void scrivifile(FILE *fp, char *mailrec, char *passwordrec, float saldo);
int confrontadati(FILE *fp, char *mailrec, char *passwordrec, float saldo);
float ricavosaldo(FILE *fp, char *mailrec, char *passwordrec, float saldo);
void aggiornautente(FILE *fp, char *mailrec, char *passwordrec, float saldo, FILE *fpUt);

//parte della gestione della lista di prodotti
lista *inserisci(lista *nodo, lista *head);
lista *nuovonodo(char *abbigliamento, char *marca, char *taglia, int quantita, float prezzo);
lista *leggifile(FILE *fp, lista *head);
void print(lista *head, int count);
lista *aggiornalista(lista *head, lista *carrello);

//parte della gestione del carrello
lista *caricacarrello(lista *carrello, lista *head);
lista *ricercanodo(lista *head, char *abbigliamento, char *marca, char *taglia, int quantita);
int acquistocarrello(lista *carrello, float saldo);
lista *svuotalista(lista *head);//in caso in cui l'acquisto viene effettuato

//parte della gestione della lista d'attesa
void scrivifiledattesa(FILE *fp, char *abbigliamento, char *marca, char *taglia, int quantita);

//parte della gestione del saldo
float creasaldo(float saldo);
float svuotasaldo(float saldo);
float contasaldo(lista *carrello);
float aggiornasaldo(float saldo, float tmpsaldo, lista *carrello);

//parte amministrativa
lista *giocaconlalista(lista *head);//in questa funzione si chiede di aggiungere prodotti e di modificare qualcosa nella lista
//di partenza in modo sequenziale
void scrivifilenegozio(FILE *fp, lista *head);







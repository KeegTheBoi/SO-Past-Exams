/* file:  stanza1.c */

/*
4 persone cercano di entrare in una stanza CHE PUO' CONTENERE
AL MASSIMO 2 PERSONE. Le prime due persone che arrivano entrano,
le altre aspettano che la stanza si svuoti e poi entrano.
Quando nella stanza ci sono due persone, entrambe escono.
Dopo che sono uscite le persone cercano di rientrare
subito e cosi' via all'infinito.

Pero', quando una persona capisce che sono in due e che puo' uscire,
aspetta un tempo casuale compreso tra 1 e 5 secondi e poi esce.
Durante questo intervallo di tempo,
la persona stampa ogni secondo il suo indice ed un puntino.
Attenzione, il primo che capisce che puo' uscire
non è detto che sia il primo che effettivamente esce.
Dipende dal tempo casuale generato in cui si stampano i puntini.

Quando una persona esce dalla stanza, stampa a video un messaggio
per dire se e' l'ultimo a uscire oppure no.

La variabile NumDentro indica quante persone ci sono dentro la stanza.
La variabile Entrare indica se si puo' entrare o se bisogna aspettare
che la stanza si svuoti.
Una condition variable condEntrare serve a far aspettare chi vuole entrare.
Una condition variable condUscire serve a far aspettare chi e' dentro e
sta aspettando che arrivi la seconda persona.

La funzione attendi(secmin, secmax) serve ad attendere qualche secondo,
è una specie di sleep.

I sorgenti del modulo DBGpthread.c e gli header files DBGpthread.h e
printerror.h sono contenuti nella sottodirectory ./modules
Il Makefile e' nella directory principale assieme al file tre.c
Il Makefile non e' completo, qualcosa va aggiunto per compilare
correttamente.

*/


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 
#include "modules/DBGpthread.h"
#include "modules/printerror.h"

#define NUMPERSONE 4
#define MINATTESA 1
#define MAXATTESA 5

/* dati da proteggere */
pthread_mutex_t  mutex;
int NumDentro=0; /* inizio stanza vuota */
int Entrare=1; /* inizio stanza vuota, si puo' entrare */
pthread_cond_t condEntrare;
pthread_cond_t condUscire;

void attendi( int secmin, int secmax) {
	int secrandom=0;
	static int inizializzato=0;
	if( inizializzato==0 ) {
		srandom( time(NULL) );
		inizializzato=1;
	}
	if( secmin > secmax ) {
		printf("attendi: parametri errati: secmin %i secmax %i"
			" - TERMINO PROCESSO\n", secmin, secmax ),
		exit(1);
	}
	else if ( secmin == secmax )
		secrandom = secmin;
	else
		secrandom = secmin + ( random()%(secmax-secmin+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 )
		{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
return;
}

void *Persona (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"P%" PRIiPTR "",indice);

	while(1) {
		int i, numsecondi;


		DBGpthread_mutex_lock(&mutex,Plabel);

		/* se non c'e' posto devo aspettare */

		/* cerco di entrare */ 
		while(	Entrare==0 ) {
			/* aspetto */
			DBGpthread_cond_wait(&condEntrare,&mutex,Plabel);
		}
		printf("%s entra \n", Plabel );
		fflush(stdout);

		/* se sono il primo ad entrare aspetto il secondo che mi fara' uscire */
		/* se sono il secondo ad entrare sveglio il primo per farlo uscire*/

                NumDentro++;
                if ( NumDentro==2 ) {
                        Entrare=0;
                        DBGpthread_cond_signal(&condUscire,Plabel);
                } else {
                        DBGpthread_cond_wait(&condUscire,&mutex,Plabel);
                }

		/* VIC: PRIMA PARTE DA AGGIUNGERE */

		DBGpthread_mutex_unlock(&mutex,Plabel);

		/* VIC: FINE PRIMA PARTE DA AGGIUNGERE */


		/* CAPISCO DI POTER USCIRE, MA PRIMA STAMPO UN PUNTINO OGNI SECONDO */
		numsecondi=MINATTESA+(random()%(MAXATTESA-MINATTESA));
		printf("%s attende %i secondi \n", Plabel, numsecondi );
		fflush(stdout);


		for ( i=0; i<numsecondi; i++ ) {
			printf("%s . \n", Plabel );
			fflush(stdout);
			attendi(1,1);
		}

		/* ORA ESCO VERAMENTE DALLA STANZA */

		/* VIC: SECONDA PARTE DA AGGIUNGERE */

		DBGpthread_mutex_lock(&mutex,Plabel);

		/* VIC: FINE SECONDA PARTE DA AGGIUNGERE */

		NumDentro--;
		if ( NumDentro==0 ) {
			printf("%s sono l\'ultimo a uscire\n", Plabel );
			fflush(stdout);
			/* consento agli altri di entrare */
			Entrare=1;
			/* abilito TUTTI gli altri a tentare di entrare */
			DBGpthread_cond_broadcast(&condEntrare,Plabel);
		} else {
			printf("%s esco MA NON sono l\'ultimo\n", Plabel );
			fflush(stdout);
		}
		DBGpthread_mutex_unlock(&mutex,Plabel);

		/* faccio un giretto prima di provare a rientrare. */
		attendi(1,1);
	}
	pthread_exit(NULL); 
} 


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	intptr_t i;
	char Mlabel[128]="main";

	DBGpthread_mutex_init(&mutex, NULL, Mlabel); 
	DBGpthread_cond_init(&condEntrare, NULL, Mlabel);
	DBGpthread_cond_init(&condUscire, NULL, Mlabel);

	for(i=0;i<NUMPERSONE;i++) {
		rc=pthread_create(&th,NULL,Persona,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL);
	return(0); 
} 
  

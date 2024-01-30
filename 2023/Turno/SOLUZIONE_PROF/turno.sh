#!/bin/bash

# L'esercizio realizza una sorta di staffetta tra processi
# figli, ciascuno caratterizzato da un indice intero positivo,
# che si passano il turno per mezzo dell'esistenza di un file
# il cui nome e' il valore dell'indice.
# Il processo padre crea i figli e da' il turno al processo
# figlio di indice 0.
#
# Dettagli:
# Un processo padre denominato turno.sh crea un file di nome 0
# poi crea 3 processi figlio.sh passando loro come
# argomento un indice intero univoco da 0 a 2, e li fa eseguire
# in background,
# poi aspetta la terminazione di tutti i figli.
# Ciascun processo figlio ogni secondo verifica se esiste
# nella directory corrente un file che si chiama come il
# proprio indice. Se non lo trova riprova dopo un secondo.
# Se lo trova allora:
# - cancella quel file che si chiama come il proprio indice.
# - crea il file che si chiama come l'indice del figlio successivo
#   cioe' (il proprio indice piu 1) modulo 3.
# - stampa a video il proprio indice.
# In tal modo i figli si scambiano una specie di turno,
# stampando uno dopo l'altro il proprio indice.
# Dopo avere stampato a video 3 volte il proprio indice
# allora ciascun processo figlio termina.

NUMFIGLI=3
# elimino gli eventuali file presenti 
for (( i=0; $i<${NUMFIGLI}; i=$i+1 )) ; do 
	if [[ -e ${i} ]] ; then rm -f ${1} ; fi
done

# AGGIUNGERE CODICE DA QUI'

touch 0
for (( i=0; $i<3; i=$i+1 )) ; do 
	./figlio.sh $i &
done

wait

#AGGIUNGERE CODICE FINO A QUI'
echo padre finisce


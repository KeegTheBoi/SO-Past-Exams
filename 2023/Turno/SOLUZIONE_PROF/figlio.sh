#!/bin/bash

indice=$1
echo inizia figlio indice ${indice}
#AGGIUNGERE CODICE DA QUI



MAXNUMSTAMPE=3
counter=0
while true ; do
	sleep 1
	if [[ -e ${indice} ]] ; then
		(( counter=${counter}+1 ))
		rm ${indice}
		touch $(( (${indice}+1)%3 ))

		echo ${indice}
		if (( counter == ${MAXNUMSTAMPE} )) ; then
			break
		fi
	fi
done

# FINE AGGIUNTA CODICE
echo figlio indice ${indice} finisce


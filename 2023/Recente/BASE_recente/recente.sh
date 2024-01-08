#!/bin/bash

# Scrivere uno script bash recente.sh che deve
# cercare la directory che verifica le tre seguenti proprieta':
# - sta nell'albero che parte da /usr/include/
# - contiene almeno una 'a' nel proprio nome
# - e' quella modificata piu' di recente tra tutte quelle che
#   verificano le due precedenti proprieta'.
#
# Suggerimento: per verificare se il vostro script funziona 
# creare una directory di nome aggiunta che corrisponda
# alle prime due caratteristiche:
# essendo la directory creata piu' di recente, dovrebbe essere quella
# che viene individuata come risultato dal vostro scric



recenteDir=$(find /usr/include/ -type d -name "*a*" | head -n 1)
for dire in $(find /usr/include/ -type d -name "*a*")
do 
    echo "[[ $dire -nt $recenteDir ]]"
        if [[ $dire -nt $recenteDir ]] 
        then 
            recenteDir=$dire
        fi
    
done    
echo $recenteDir

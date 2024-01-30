#!/bin/bash
parola='cacc'
echo parola da indovinare: $parola
while true
do
    tenta=$(./parola.sh)
    echo Tentativo: $tenta
    if [[ $tenta = $parola ]]
    then 
        echo Indovinato
        break
    fi
done
#!/bin/bash
INDEX=$1

if [[ $# -ne 1 ]]; then echo argomenti non corretti; fi

for (( i=0; i<3;i++)) 
do
    NOTFOUND=1;
    while (( NOTFOUND == 1))
    do
        sleep 1
        if [ -e $INDEX ]
        then 
            NOTFOUND=0
        fi
    done
    rm -f $INDEX
    NEXTFILE=$(((INDEX+1)%3))
    touch $NEXTFILE
    ls
    echo Created file: $NEXTFILE
    
done
exit 0
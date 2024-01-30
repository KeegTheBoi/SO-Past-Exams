#!/bin/bash

(( NUMERO=${RANDOM}%2 ))
if (( $NUMERO == 0 )) ; then echo -n a 
else echo -n  c
fi


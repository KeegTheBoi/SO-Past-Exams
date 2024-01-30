#!/bin/bash

PAROLA=""
for (( i=0; $i < 4; i=$i + 1 )) ; do
	PAROLA=${PAROLA}$(./lettera.sh)
done
echo ${PAROLA}


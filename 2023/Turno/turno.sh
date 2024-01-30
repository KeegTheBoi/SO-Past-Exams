#!/bin/bash                           
for (( i=0;i<3;i++))
do
    ./figlio.sh $i &
done
wait
echo Terminated
exit 0
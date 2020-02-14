#!/bin/bash

> ~/input.txt

while read
do
    if [[ ! "$REPLY" -ge 0 ]]
    then
        echo $REPLY >> input.txt
        break;
    else
        echo $REPLY >> input.txt
    fi
done

count=$(( `wc -l < input.txt` - 1 ))
condition=true
for i in $(seq 2 $count)
do
    current=`sed -n "$i"p input.txt` 
    prev=`sed -n "$(( i - 1 ))"p input.txt` 
    if [[ ! $(( current - prev )) -eq 1 ]]
    then
        condition=false
        break;
    fi
done

if [[ "$condition" == "true" ]]
then
    echo YES
else
    echo NO
fi
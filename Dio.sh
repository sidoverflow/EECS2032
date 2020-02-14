#!/bin/bash
#File:Dio.sh

check=0
diophantine() {
    x=$(($1**3))
    y=$(($2**3))
    z=$(($3**3))
    w=$(($4**3))
    a=$(($x+$y))
    b=$(($z+$w))
    if [ "$a" -eq "$b" ]
    then
        check=1
        echo "x= $1, y= $2, z= $3, w= $4"
    fi
}

for ((i = 1; i <= "$1"; i++))
do 
    for ((j = 1; j <= "$2"; j++))
    do 
        for ((k = 1; k <= "$3"; k++))
        do 
            for ((l = 1; l <= "$4"; l++))
            do 
                diophantine "$i" "$j" "$k" "$l"
            done 
        done 
    done 
done
if [ "$check" -eq "0" ]
then
    echo "No solution"
fi



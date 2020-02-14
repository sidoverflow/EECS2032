#!/bin/bash
#File:sh1.sh

if [ ! "$#" -eq "2" ]
then
    echo "usage: script_name dir file"
    exit
else
    if [ -e $2 ] 
    then   
        if [ ! -f $2 ]
        then   
            echo "$2 is not a regular file"
            exit         
        fi
    fi
    if [ ! -d $1 ]
    then
        echo "$1 is not a directory"
        exit
    fi
    if [ -e "$1"/"$2" ] 
    then
        echo "$2 is in $1"
        exit
    else 
        echo "$2 is not in $1"
        exit
    fi
fi





    
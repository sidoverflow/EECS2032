#!/bin/bash

names=./$pwd/names.txt
courses=./$pwd/courses.txt
IFS=$'\t'

if [[ -f $names && -f $courses ]] 
then
    if [[ $1 == "-count" ]]
    then
        echo $(( $(wc -l < $names)))
    elif [[ $1 == "-f" ]]
    then
        if grep -w -q "^$2" "$names" 
        then
            while read -r nline
            do
                nArray=($nline)
                if [[ ${nArray[0]} == "$2" ]]
                then
                    while read -r cline
                    do
                        cArray=($cline)
                        if [[ ${cArray[0]} == ${nArray[1]} ]]
                        then
                            if [[ ${cArray[2]} == "" ]]
                            then
                                echo -e ${cArray[1]} '\t' "in progress"
                                
                            else
                                echo -e ${cArray[1]} '\t' "${cArray[2]}"
                                
                            fi
                        fi
                    done < $courses
                    exit
                fi
            done < $names
        else 
            echo "No such student: $2"
            exit
        fi
    elif [[ $1 == "-g" ]] 
    then
        while read -r nline
            do
                nArray=($nline)
                if [[ ${nArray[0]} == "$2" ]]
                then
                    while read -r cline
                    do
                        cArray=($cline)
                        if [[ ${cArray[0]} == ${nArray[1]} ]]
                        then
                            if [[ ! ${cArray[2]} == "" ]]
                            then
                                echo ${cArray[1]}
                            fi
                        fi
                    done < $courses
                    exit
                fi
            done < $names
    elif [[ $1 == "-c" ]]
    then
        ctr=0
        while read -r cline
        do
            cArray=($cline)
            if [[ ${cArray[1]} == $2 ]]
            then
                ((ctr++))
            fi
        done < $courses
        echo $ctr
    elif [[ $1 == "-list" ]]
    then 
        ctr=0
        while read -r cline
        do
            cArray=($cline)
            if [ ${cArray[1]} == $2 ] && [ ${cArray[2]} == $3 ]
            then
                ((ctr++))
            fi
        done < $courses
        echo $ctr
    fi
else
    echo "One or both files do not existing"
    exit
fi


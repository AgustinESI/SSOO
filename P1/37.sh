#!/bin/bash
#echo "El nombre del script es $0"
#echo "El número de argumentos suministrados es $#"
#echo "Los argumentos son: $@"

if [ $# -eq 0 ]
then 
    echo "Debe introducir argumentos"
    exit 1
fi

for nodo in "$@"
do
    if [ -e $nodo ] 
    then
        echo "El nodo $nodo existe"
    else
        echo "El nodo $nodo no existe"
    fi
done
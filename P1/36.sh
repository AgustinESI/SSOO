#!/bin/bash
#echo "El nombre del script es $0"
#echo "El número de argumentos suministrados es $#"
#echo "Los argumentos son: $@"


if [ $# -eq 0 ]
then 
    echo "Mete parametros"
    exit 1
fi

for argumento in "$@"
do
    if [ -e $argumento ]
    then 
        echo "El nodo no existe"
    else
        echo "El nodo existe"
    fi
done

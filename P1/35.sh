#!/bin/bash
#echo "El nombre del script es $0"
#echo "El número de argumentos suministrados es $#"
#echo "Los argumentos son: $@"


if [ $# -ne 1 ]
then 
    echo "Error: nombre del archivo $0 <nombrearchivo>, faltan parametros"
    exit 1
fi

if [ ! -f "$1" ] 
then 
    echo "No es un archivo, puto calvo"
    exit 1
fi





ls -la $1


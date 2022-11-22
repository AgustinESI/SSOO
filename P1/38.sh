#!/bin/bash
#echo "El nombre del script es $0"
#echo "El número de argumentos suministrados es $#"
#echo "Los argumentos son: $@"

#Comprobamos el numero de argumentos
if [ $# -ne 2 ]
then
    echo "Debe introducir dos argumentos"
    exit 1
fi

#Comprobamos que sean archivos
for nodo in "$@"
do 
    if [ ! -f $nodo ]
    then 
        echo "El argumento $nodo no es un archivo valido"
        exit 1
    fi
done


#Cambiamos el nombre al archivo
echo "$1"
echo "$2"

cp $1 "/tmp/$1"
cp $2 "/tmp/$2"

mv $1 $2
mv "/tmp/$2" "/tmp/$1"

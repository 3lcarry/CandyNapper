#!/bin/bash

CARPETA_BUILD=build
CARPETA_SOURCE=.

if [ ! -d $CARPETA_BUILD ]
then
    mkdir $CARPETA_BUILD
fi

cd $CARPETA_BUILD

if [ $1 == "cmake" ]
then
    $@ ../$CARPETA_SOURCE
elif [ $1 == "make" ]
then
    if [ ! -e Makefile ]
    then
        cmake $@ ../$CARPETA_SOURCE
    fi
    $@
elif [ $1 == "help" ]
then
    echo "Uso: make.sh [make | cmake]"
    echo "Con cmake se ejecuta el cmake con parametros"
    echo "Con make se ejecuta el makefile"
else
	echo "make.sh [make | cmake]"
fi

cd ..

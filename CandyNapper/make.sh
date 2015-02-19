#!/bin/bash

#USO DEL SCRIPT:
# Para no llenar de mierda las carpetas, usaremos este script al compilar. Lo que hacemos es:
#	Si no existe la carpeta CARPETA_BUILD, la creamos. Aqu’ es donde va todo lo de la compilaci—n
#
#	Si el primer parametro es "cmake", genera los makefiles segun el CMakeLists.txt que haya en 
#	la carpeta CARPETA_SRC (donde esta el codigo, que no se ensucia).
#
#	Si el primer parametro es "make" ejecuta el make autogenerado, con el resto de parametros que le pasemos
#
#	Ejemplo: queremos generar los makefiles, pues ./make.sh cmake.
#			queremos hacer la documentacion, pues ./make.sh make doc.
#
#NOTA: Es aconsejable que lo useis en los motores y en los submodulos (aunque luego, para el proyecto final,
#		no se usen. 

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
    echo "make.sh [make | cmake]"
    echo "Con cmake se ejecuta cmake y los parametros que le pasemos"
    echo "Con make se ejecuta el make autogenerado y los parametros que le pasemos"
else
	echo "make.sh [make | cmake]"
fi

cd ..

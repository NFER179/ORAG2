#!/bin/bash

#$1     #img01
#$2     #img02
#$3     #mascara
#$4     #ancho
#$5     #alto

processFolder="procesado" #Carpeta en la que se dejaran los archivos que se pasen a .bmp
mkdir $processFolder
mkdir "${processFolder}/enmascarados/"

if test "${1##*.}" = "bmp"
then
    cp $1 "${processFolder}/"
else
    gm convert $1 -resize $4"x"$5 "${1%.*}.bmp"
    mv "${1%.*}.bmp" "${processFolder}/"
fi
#### img02
if test "${2##*.}" = "bmp"
then
    cp $2 "${processFolder}/"
else
    gm convert $2 -resize $4"x"$5 "${2%.*}.bmp"
    mv "${2%.*}.bmp" "${processFolder}/"
fi
####
if test "${3##*.}" = "bmp"
then
    cp $3 "${processFolder}/"
else
    #gm convert -monochrome $3 -resize $4"x"$5 "${3%.*}.bmp"
    gm convert $3 -resize $4"x"$5 "${3%.*}.bmp"
    mv "${3%.*}.bmp" "${processFolder}/"
    #chmod 777 "${processFolder}/mascara.bmp"
fi

gcc -m32 -o executable main.c
./executable 
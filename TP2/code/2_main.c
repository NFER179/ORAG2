#include <stdio.h>
#include <dirent.h>//Para el manejo de directorios.
#include <string.h>//Para la comparacion de strings
#include "2_structs.h" // Archivo con todas las structuras.

int countFileToCompareInFolder(char* folder);

/*
*argc: Identifica la cantidad de parametros que se pasan.
*argv: Es un array que contiene los parametros que se pasan desde la ejecucion, siendo el argv[0] el "./{objetoC}"
*/
int main(int argc, char** argv){

    /*
    * Obtengo la cantidad total de archivos.
    * Obtengo la cantidad de mascaras
    *   En base a ambos resultados me armo un listado de imagenes y un listado de mascaras.
    * Luego recorro los archivos preguntando si tienen las mismas dimensiones pero diferente nombre.
    * Cuando encuentro que tienen las mismas dimensiones entonces busco la mascara que tiene las mismas dimensiones y armo un struct para cada oincidencia.
    */

    int counter = 0;

    DIR* folder;
    DIR* folder02;
    struct dirent* in_file;
    struct dirent* image2;
    struct dirent* mask;

    printf("Folder: %s\n", argv[1]);

    int cantidadArchivos = countFileToCompareInFolder( "prueba" );
    printf( "Cantidad de archivos: %d\n", cantidadArchivos );

    folder = opendir( "prueba" );

    while( ( in_file = readdir( folder ) ) ){
        if( !strcmp( in_file -> d_name, "." ) ) {
            continue;
        }
        
        if( !strcmp( in_file -> d_name, ".." ) ){
            continue;
        }

        char* fileName = in_file -> d_name;

        folder02 = opendir( "prueba" );

        while( ( image2 = readdir( folder02 ) ) ){
            if( !strcmp( image2 -> d_name, "." ) ){
                continue;
            }
            if( !strcmp( image2 -> d_name, ".." ) ) {
                continue;
            }
            if( !strcmp( image2 -> d_name, fileName ) ){
                continue;
            }

            char* fileName02 = image2 -> d_name;
//            printf( "%d: File merge: %s & %s\n", counter, fileName, fileName02 );

            counter = counter + 1;
        }

        closedir( folder02 );

    }

    closedir( folder );

    return 0;
}

/* Cantidad de archivos a compara */
int countFileToCompareInFolder( char* folder ) {

    int folderCount = 0;

    DIR* dir;
    struct dirent* stDir;

    dir = opendir( folder );

    while( ( stDir = readdir( dir ) ) ) {
        folderCount++;
    }

    closedir( dir );

    return folderCount;

}
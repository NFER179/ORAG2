#include <stdio.h>

typedef struct {
	unsigned short type;   			//2 char
	unsigned char size[4];              //4 char
	unsigned short reserved01;       //2 char
    unsigned short reserved02;       //2 char
//	unsigned char a[10];
//	unsigned char dataOffset[4];        //4 char
	unsigned int dataOffset;
	unsigned int size02;
	int width, height;
	unsigned short planes;
	unsigned short bitPerPixel;
	unsigned char rest[24];
} __attribute((packed)) _HEADERINFO_ ;

typedef struct {
	unsigned char r; //red
	unsigned char g; //green
	unsigned char b; //blue
} _PIXEL_ ;

int main() {

    _HEADERINFO_ headInfo;
	_PIXEL_ pixel;

    char fileName[] = "hexagonos_600_600.bmp";
    FILE * file = fopen( fileName , "rb" );

    fread( &headInfo, sizeof(_HEADERINFO_), 1, file );

/*	int doff = 0;
	int i;
	for ( i = 0; i < 4 ; i++ ) {
		printf( "dataOffset: %c\n", headInfo.dataOffset[i] );
		doff = doff + (int) headInfo.dataOffset[i];
	}
*/
	printf( "%u\n", headInfo.dataOffset );
//	printf( "%u\n", doff );

	fseek( file, headInfo.dataOffset, SEEK_SET );
	fread( &pixel, sizeof(pixel), 1, file );

	printf( "red: %u,green: %u,blue: %u\n", (int)pixel.r, (int)pixel.g, (int)pixel.b );

    return 0;
}
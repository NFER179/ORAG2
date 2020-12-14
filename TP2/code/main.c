#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned short type;
	unsigned char size[4];
	unsigned char reserved[4];
	unsigned char dataOffset[4];
} HEADER;

typedef struct {
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitPerPixel;
	unsigned char rest[24];
} INFOHEADER;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} COLORTABLE;

typedef struct {
	unsigned char padding;
} PADDING;
/*
typedef struct {
	
};

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *c, int cantidad);
*/
int main(){

	int column;
	HEADER bmpHeader, bmp01Header, bmp02Header;
	INFOHEADER bmpInfoHeader, bmp01InfoHeader, bmp02InfoHeader;

	//char file01[] = "procesado/img01.bmp";
	char file01[] = "procesado/meditacion_680_400.bmp";
	FILE * img01 = fopen(file01, "rb");

	//char file02[] = "procesado/img02.bmp";
	char file02[] = "procesado/balon_680_400.bmp";
	FILE * img02 = fopen(file02, "rb");

	//char maskFile[] = "procesado/mascara_v02.bmp";
	char maskFile[] = "procesado/mascara_ovalo_680_400.bmp";
	FILE * mask = fopen(maskFile, "rwb");

	FILE *out = fopen("procesado/enmascarados/out.bmp", "wb");
/*
	if( img01 == NULL && img02 == NULL && mask == NULL ){
		printf("Archivo no encontrado\n");
	} else {
		printf("A trabajar\n");
	}
*/	

	/* Start -> Read file 1 and 2 */
	fseek(img01, 0x0, SEEK_SET);
	fseek(img02, 0x0, SEEK_SET);
	fseek(mask, 0x0, SEEK_SET);
	fseek(out, 0x0, SEEK_SET);

	/* Leo la cabecera del archivo. */
	fread(&bmp01Header, sizeof(HEADER), 1, img01);
	fread(&bmp02Header, sizeof(HEADER), 1, img02);
	fread(&bmpHeader, sizeof(HEADER), 1, mask);
	fwrite(&bmp02Header, sizeof(HEADER), 1, out);

	/* Ahora leo la informacion de la cabecera del archivo. */
	fread(&bmp01InfoHeader, sizeof( INFOHEADER ), 1, img01);
	fread(&bmp02InfoHeader, sizeof( INFOHEADER ), 1, img02);
	fread(&bmpInfoHeader, sizeof(INFOHEADER), 1, mask);
	fwrite(&bmp02InfoHeader, sizeof(INFOHEADER), 1, out);

	printf("El ancho es de: %d\nEl alto es de: %d\n", bmpInfoHeader.width, bmpInfoHeader.height);

	int maskPadding = bmpInfoHeader.width % 4;

	/*int pixelWidth01 = ( int )bmp01InfoHeader.width;
	int pixelWidth02 = ( int )bmp02InfoHeader.width;
	int pixelWidthMask = ( int )bmpInfoHeader.width;

	COLORTABLE bmp01ColorTable[ pixelWidth01 ];
	COLORTABLE bmp02ColorTable[ pixelWidth02 ];
	COLORTABLE bmpColorTable[ pixelWidthMask ];
	COLORTABLE bmpOutColorTable[ pixelWidthMask ];
*/
	int rowPixels = ( int )bmpInfoHeader.height;
	int columnPixels = ( int )bmpInfoHeader.width;
	int row;

	COLORTABLE bmp01ColorTable;
	COLORTABLE bmp02ColorTable;
	COLORTABLE bmpColorTable;
	COLORTABLE bmpOutColorTable;

	//for( row = 0; i < ( int )bmpInfoHeader.height; row++ ) {
	for( row = 0; row < rowPixels; row++ ) {
//		fread( bmp01ColorTable, sizeof( COLORTABLE ), pixelWidth01, img01 );
//		fread( bmp02ColorTable, sizeof( COLORTABLE ), pixelWidth02, img02 );
//		fread( bmpColorTable, sizeof( COLORTABLE ), pixelWidthMask, mask );

//		fread( &bmp01ColorTable, sizeof( COLORTABLE ), 1, img01 );
//		fread( &bmp02ColorTable, sizeof( COLORTABLE ), 1, img02 );
//		fread( &bmpColorTable, sizeof( COLORTABLE ), 1, mask );
		for( column = 0; column < columnPixels; column++){

			fread( &bmp01ColorTable, sizeof( COLORTABLE ), 1, img01 );
			fread( &bmp02ColorTable, sizeof( COLORTABLE ), 1, img02 );
			fread( &bmpColorTable, sizeof( COLORTABLE ), 1, mask );
			//negro
			//printf("[%dx%d](%c,%c,%c) ", row, column, bmpColorTable.r, bmpColorTable.g, bmpColorTable.b);
			if( bmpColorTable.r <= 0xf0) {
				bmpOutColorTable.r = bmp01ColorTable.r;
				bmpOutColorTable.g = bmp01ColorTable.g;
				bmpOutColorTable.b = bmp01ColorTable.b;
				//printf("negro: %cu%cu%cu", bmpColorTable.r, bmpColorTable.g, bmpColorTable.b);
				//bmpOutColorTable = bmp02ColorTable;
			} else {
				bmpOutColorTable.r = bmp02ColorTable.r;
				bmpOutColorTable.g = bmp02ColorTable.g;
				bmpOutColorTable.b = bmp02ColorTable.b;
				//printf("blanco");
				//bmpColorTable = bmp01ColorTable;
			}

			fwrite( &bmpOutColorTable, sizeof(COLORTABLE), 1, out);
		}

		if( maskPadding != 0 ){
			PADDING bmp01Padding[maskPadding];
			fread( &bmp01Padding, sizeof( PADDING ), maskPadding, img01 );
			fread( &bmp01Padding, sizeof( PADDING ), maskPadding, img02 );
			fread( &bmp01Padding, sizeof( PADDING ), maskPadding, mask );
		}
		//printf("\n");
	}
/*
	fseek( img01, ( int )bmp01Header.dataOffset, SEEK_SET );
	fseek( img02, ( int )bmp02Header.dataOffset, SEEK_SET );
	fseek( mask, ( int )bmpHeader.dataOffset, SEEK_SET );

	fread( bmp01ColorTable, sizeof( COLORTABLE ), totalBits01, img01 );
	fread( bmp02ColorTable, sizeof( COLORTABLE ), totalBits02, img02 );
	fread( bmpColorTable, sizeof( COLORTABLE ), totalBits, mask );
*/
	/* End <- Read file 1 and 2 */

//	fseek(mask, (int)bmpHeader.dataOffset, SEEK_SET);

//	fwrite(bmpColorTable, sizeof(COLORTABLE), 1, mask);
/*
	FILE *out = fopen("procesado/enmascarados/out.bmp", "wb");

	fseek(out, 0x0, SEEK_SET);
	fwrite(&bmpHeader, sizeof(HEADER), 1, out);
	fwrite(&bmpInfoHeader, sizeof(INFOHEADER), 1, out);
	fwrite(bmpColorTable, sizeof(COLORTABLE), pixelWidthMask, out);
*/

	fclose(out);
	fclose(img01);
	fclose(img02);
	fclose(mask);

	return 0;
}

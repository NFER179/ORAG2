#include <time.h>//Tiempo en clocks

struct CSV_LINE {
    char line[140];
};

typedef struct {
    char* name;
    int weight;
    int height;
} FILE_INFORMATION ;

typedef struct {
    char id[10];
    char pathIn[100];
    char pathOut[100];
    char image_name_01[50];
    char image_name_02[50];
    char mask_name[50];
    double sPthreadClock;
    double cPthreadClock;
    double asmClock;
} FILE_MERGE ;

typedef struct {
	unsigned short type01;          //2 char
	unsigned int size;              //4 char
	unsigned short reserved01;      //2 char
    unsigned short reserved02;      //2 char
	unsigned int dataOffset;        //4 char
} __attribute((packed)) HEADER ;

typedef struct {
	unsigned int size;
	int width, height;
	unsigned short planes;
	unsigned short bitPerPixel;
	unsigned char rest[24];
} __attribute((packed)) HEADERINFO ;

typedef struct {
    unsigned char r;// red
    unsigned char g;// green
    unsigned char b;// blue
} __attribute((packed)) PIXELCOLOR ;

typedef struct {
    unsigned char paddingByte;
} __attribute((packed)) PADDING ;

typedef struct {
    char filename[30];
    long withOutThread;
    long withThread;
    long sasm;
} CSV_EACH_FILE ;
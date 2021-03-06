#ifndef HDCHS_H
#define HDCHS_H

typedef struct // 20 bits
{
	unsigned char s; // 6 bits
	unsigned char h; // 4 bits
	unsigned short int c; // 10 bits
} tCHS;

typedef struct // 32 bits 
{
	unsigned int size;
} tLBA;

typedef struct // 24 bits
{
	unsigned char s; // 6 bits
	unsigned char h; // 8 bits
	unsigned short int c; // 10 bits
} tLARGE;

typedef struct // 28 bites
{
	unsigned char s; // 8 bits
	unsigned char h; //  4 bits
	unsigned short int c; // 16 bits
} tIDECHS;

int g_lba2chs 	   (tLBA, tCHS *);
int g_lba2large    (tLBA, tLARGE *);
int g_lba2idechs   (tLBA, tIDECHS *);
int g_chs2large	   (tCHS, tLARGE *);
int g_chs2lba	   (tCHS, tLBA *);
int g_chs2idechs   (tCHS, tIDECHS *);
int g_large2chs	   (tLARGE, tCHS *);
int g_large2idechs (tLARGE, tIDECHS *);
int g_large2lba    (tLARGE, tLBA *);
int g_idechs2chs   (tIDECHS, tCHS *);
int g_idechs2large (tIDECHS, tLARGE *);
int g_idechs2lba   (tIDECHS, tLBA *);

int a_lba2chs	   (tCHS geometry, tLBA, tCHS *);
int a_lba2large    (tLARGE geometry, tLBA, tLARGE *);
int a_lba2idechs   (tIDECHS geometry, tLBA, tIDECHS *);
int a_chs2lba 	   (tCHS geometry, tCHS, tLBA *);
int a_large2lba    (tLARGE geometry, tLARGE, tLBA *);
int a_idechs2lba   (tIDECHS geometry, tIDECHS, tLBA *);
int a_large2chs    (tLARGE geometry1, tCHS geometry2, tLARGE, tCHS *);
int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE, tIDECHS *);
int a_chs2large    (tCHS geometry1, tLARGE geometry2, tCHS, tLARGE *);
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS, tLARGE *);
int a_chs2idechs   (tCHS geometry1, tIDECHS geometry2, tCHS, tIDECHS *);
int a_idechs2chs   (tIDECHS geometry1, tCHS geometry2, tIDECHS, tCHS *);

#endif //HDCHS_H

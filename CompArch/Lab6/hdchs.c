#include "hdchs.h"

int g_lba2chs (tLBA input, tCHS *output)
{
	int CH = input.size / 63;
	int H = CH / 1023;
	int k;
	while (H > k){ 
 		if (k == 16) break;
		k *= 2;
	} 
	if (k == 16) 
		k = 15;
	if (H / k < 1024) {
		output->c = CH / k;
		output->h = k;
		output->s = 63;
	} else
		return 1;
	return 0;
};
int g_lba2large (tLBA input, tLARGE *output)
{
	int CH,H,k = 2;
	CH = input.size/63;
	H = CH/1024;
	while ((H/k) > 0){
		if (k == 256) break;
		k *= 2;
	}
	if (k == 256) 
		k = 255;
	if (H/k < 1024){
		output->c = CH / k;
		output->h = k;
		output->s = 63;
	} else return 1;
	return 0;
};
int g_lba2idechs (tLBA input, tIDECHS *output)
{
	int CH,H,k = 2;
	CH = input.size/255;
	H = CH/65535;
	while ((H/k) > 0){
		if (k == 256) break;
		k *= 2;
	}
	if (k == 256) 
		k = 255;
	if (H/k < 65536){
		output->c = CH / k;
		output->h = k;
		output->s = 255;
	} else return 1;
	return 0;
};
int g_chs2large (tCHS input, tLARGE *output)
{
	int C,H;
	C=input.c;
	H=input.h;
	do {
	  C /= 2;
	  H *= 2;
	} while ((C/2 > 0) && (H*2 < 256));
	output->c=C;
	output->h=H;
	output->s=input.s;
	return 0;
};
int g_chs2lba (tCHS input, tLBA *output)
{
	output->size = input.c * input.h * input.s;
	return 0;
};
int g_chs2idechs (tCHS input, tIDECHS *output)
{
	int C,H;
	C=input.c;
	H=input.h;
	do {
	  C *= 2;
	  H /= 2;
	} while ((C*2 < 65536) && (H/2 > 0));
	output->c=C;
	output->h=H;
	output->s=input.s;
	return 0;
};

int g_large2chs (tLARGE input, tCHS *output)
{
	int C,H;
	C=input.c;
	H=input.h;
	do {
	  C *= 2;
	  H /= 2;
	} while ((C*2 < 1024) && (H/2 > 0));
	if (C > 1023 || H > 15) return 1;
	output->c=C;
	output->h=H;
	output->s=input.s;
	return 0;
};
int g_large2idechs (tLARGE input, tIDECHS *output)
{
	int C,H;
	C=input.c;
	H=input.h;
	do {
	  C *= 2;
	  H /= 2;
	} while ((C*2 < 1024) && (H/2 > 0));
	if (C > 65535 || H > 15) return 1;
	output->c=C;
	output->h=H;
	output->s=input.s;
	return 0;
};
int g_large2lba (tLARGE input, tLBA *output)
{
	output->size = input.c  * input.h * input.s;
	return 0;
};
int g_idechs2chs (tIDECHS input, tCHS *output)
{
	tLBA buf;
	g_idechs2lba(input,&buf);
	if (g_lba2chs(buf, output) == 1) return 1;
	return 0;
};
int g_idechs2large (tIDECHS input, tLARGE *output)
{
	tLBA buf;
	g_idechs2lba(input,&buf);
	if (g_lba2large(buf, output) == 1) return 1;
	return 0;
	};
int g_idechs2lba (tIDECHS input, tLBA *output)
{
	output->size = input.c * input.h * input.s;
	return 0;
};

//Address

int a_lba2chs (tCHS geometry, tLBA input, tCHS *output)
{
	if ((geometry.c * geometry.h * geometry.s) < input.size) return 1;
	output->c = input.size / (geometry.h * geometry.s);
	output->h = (input.size / geometry.s) % geometry.h;
	output->s = input.size % geometry.s;
	return 0;
};
int a_lba2large (tLARGE geometry, tLBA input, tLARGE *output)
{
	if ((geometry.c * geometry.h * geometry.s) < input.size) return 1;
	output->c = input.size / (geometry.h * geometry.s);
	output->h = (input.size / geometry.s) % geometry.h;
	output->s = input.size % geometry.s;
	return 0;
};
int a_lba2idechs (tIDECHS geometry, tLBA input, tIDECHS *output)
{
	if ((geometry.c * geometry.h * geometry.s) < input.size) return 1;
	output->c = input.size / (geometry.h * geometry.s);
	output->h = (input.size / geometry.s) % geometry.h;
	output->s = input.size % geometry.s;
	return 0;
};
int a_chs2lba (tCHS geometry, tCHS input, tLBA *output)
{
	if ((geometry.c < input.c) || (geometry.h < input.h) || (geometry.s < input.s)) return 1;
		output->size = input.c * (geometry.h * geometry.s) + input.s * geometry.s + input.s;
	return 0;
};

int a_large2lba (tLARGE geometry, tLARGE input, tLBA *output)
{
	if ((geometry.c < input.c) || (geometry.h < input.h) || (geometry.s < input.s)) return 1;
		output->size = input.c * (geometry.h * geometry.s) + input.s * geometry.s + input.s;
	return 0;
};

int a_idechs2lba (tIDECHS geometry, tIDECHS input, tLBA *output)
{
	if ((geometry.c < input.c) || (geometry.h < input.h) || (geometry.s < input.s)) return 1;
		output->size = input.c * (geometry.h * geometry.s) + input.s * geometry.s + input.s;
	return 0;
};

int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE input, tCHS *output)
{
	int C, H, k = 1;
	if (geometry1.c >= geometry2.c || geometry1.h <= geometry2.h) return 1;
	C=geometry1.c;
	H=geometry1.h;
	do{
		C *= 2;
		H /= 2;
		k *= 2;
	} while ((C < geometry2.c)  && (H > geometry2.h));
	output->c=geometry1.c * (input.h % k) + input.c;
	output->h=input.h % k;
	output->s=input.s;
	return 0;
};

int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE input, tIDECHS *output)
{
	int C, H, k = 1;
	if (geometry1.c >= geometry2.c || geometry1.h <= geometry2.h) return 1;
	C=geometry1.c;
	H=geometry1.h;
	do{
		C *= 2;
		H /= 2;
		k *= 2;
	} while ((C < geometry2.c)  && (H > geometry2.h));
	output->c=geometry1.c * (input.h % k) + input.c;
	output->h=input.h % k;
	output->s=input.s;
	return 0;
};
int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS input, tLARGE *output)
{
	int C, H, k=1;
	if (geometry1.c <= geometry2.c || geometry1.h >= geometry2.h) return 1;
	C = geometry1.c;
	H = geometry1.h;
	do{
		C /= 2;
		H *= 2;
		k *= 2;
	} while ((C > geometry2.c) && (H < geometry2.h));
	output->c = input.c % geometry2.c;
	output->h = (geometry2.h / k) * (input.c % k) + input.h;
	output->s = input.s;
	return 0;
};
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS input, tLARGE *output)
{
	tLBA buf;
	a_idechs2lba(geometry1,input,&buf);
	if (a_lba2large(geometry2,buf,output) == 1) return 1;
	return 0;
};
int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS input, tIDECHS *output)
{
	int C, H, k = 1;
	if (geometry1.c >= geometry2.c || geometry1.h <= geometry2.h) return 1;
	C=geometry1.c;
	H=geometry1.h;
	do{
		C *= 2;
		H /= 2;
		k *= 2;
	} while ((C < geometry2.c)  && (H > geometry2.h));
	output->c=geometry1.c * (input.h % k) + input.c;
	output->h=input.h % k;
	output->s=input.s;
	return 0;
};
int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS input, tCHS *output)
{
	tLBA buf;
	a_idechs2lba(geometry1,input,&buf);
	if (a_lba2chs(geometry2,buf,output) == 1) return 1;
	return 0;
};

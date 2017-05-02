#include "hdchs.h"

int g_lba2chs (tLBA input, tCHS *output)
{
	int cyl = (input.size / 63) / 16;
	output->cylinder = cyl % 1024;
	output->head = (input.size / 63) % 16;
	output->sector = (input.size % 63) + 1;
	return 0;
};
int g_lba2large (tLBA input, tLARGE *output)
{
	int cyl = (input.size / 63) / 256;
	output->cylinder = cyl % 1024;
	output->head = (input.size / 63) % 256;
	output->sector = (input.size % 63) + 1;
	return 0;
};
int g_lba2idechs (tLBA input, tIDECHS *output)
{
	int cyl = (input.size / 256) / 16;
	output->cylinder = cyl % 65536;
	output->head = (input.size / 256) % 16;
	output->sector = (input.size % 256) + 1;
	return 0;
};
int g_chs2large (tCHS input, tLARGE *output)
{
	
};
int g_chs2lba (tCHS input, tLBA *output)
{
	output->size = input.cylinder * input.head * input.sector;
	return 0;
};
int g_chs2idechs (tCHS input, tIDECHS *output)
{
	return 0;
};

//int g_large2chs (tCHS input, tIDECHS output*);
//int g_large2idechs (tLARGE input, tIDECHS *output);
int g_large2lba (tLARGE input, tLBA *output)
{
	output->size = input.cylinder  * input.head * input.sector;
	return 0;
};
//int g_idechs2chs (tIDECHS, tCHS *);
//int g_idechs2large (tIDECHS, tLARGE *);
int g_idechs2lba (tIDECHS input, tLBA *output)
{
	output->size = input.cylinder * input.head * input.sector;
	return 0;
};

int a_lba2chs (tCHS geometry, tLBA input, tCHS *output)
{
	output->cylinder = input.size / geometry.sector / geometry.head;
	output->head = (input.size / geometry.sector) % geometry.head;
	output->sector = input.size % geometry.head + 1;
	return 0;
};
//int a_lba2large (tLARGE geometry, tLBA, tLARGE *);
//int a_lba2idechs (tIDECHS geometry, tLBA, tIDECHS *);
int a_chs2lba (tCHS geometry, tCHS input, tLBA *output)
{
	output->size = (input.cylinder * geometry.head + input.head) * geometry.sector + input.sector - 1;
	return 0;
};
int a_large2lba (tLARGE geometry, tLARGE input, tLBA *output)
{
	output->size = (input.cylinder * geometry.head + input.head)*geometry.sector + input.sector - 1;
	return 0;
};
int a_idechs2lba (tIDECHS geometry, tIDECHS input, tLBA *output)
{
	output->size = (input.cylinder * geometry.head + input.head)*geometry.sector + input.sector - 1;
	return 0;
};
/*int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE, tCHS *);
int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE, tIDECHS *);
int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS, tLARGE *);
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS, tLARGE *);
int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS, tIDECHS *);
int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS, tCHS *);*/

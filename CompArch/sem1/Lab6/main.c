#include "hdchs.h"
#include <stdlib.h>
#include <stdio.h>	

typedef struct
{
	unsigned char active;   
	tLARGE CHSbegin;        
	unsigned char oc;     
	tLARGE CHSend;           
	tLBA LBAbegin;         
	unsigned int size; 
} part;

struct part_tables {
	part table[4];
	struct part_tables *next;
} *head,*temp,*tail;

int main(){
	int t, b = 1,free_size,type_oc,flag;
	char c;
	tLARGE geom;
	tLBA adres;
	adres.size = 1; // 0 - this table
	geom.c = 1023;
	geom.h = 255;
	geom.s = 63;
	head = malloc(sizeof(struct part_tables));
	tail = head;
 
	printf("Введите IDECHS геометрию диска\n");
	tIDECHS source;
	
	do {
		printf("C:"); 
		scanf("%d",&t);
		if(t > 16384)
			printf("Error\n");
		else break;
	} while (1);
	source.c=t;
	
	do {
		printf("H:");
		scanf("%d",&t);
		if(t > 16)
			printf("Error\n");
		else break;
	} while (1);
	source.h=t;
	
	do {
		printf("S:");
		scanf("%d",&t);
		if(t > 255)
			printf("Error\n");
		else break;
	} while (1);
	source.s=t;
	
	tLBA disk;
	tLARGE adr;
	part buf;
	g_idechs2lba(source, &disk);
	printf("Размер диска %.2f Gb\n",(double) disk.size / (2048 * 1024)); // * 512 / 1024^3
	free_size=disk.size / 2; // * 512 / 1024 
	int k = 0;
	do{
		do{
			printf("Свободного места: %d Кб\n",free_size);
			printf("Размер раздела (Кб):"); 
			scanf("%d",&t);
		} while (t > free_size);
		if(t == 0) break;
		free_size -= t;
		buf.LBAbegin.size = adres.size;
		buf.size = t * 2;
		adres.size += buf.size;
		if(a_lba2large(geom,buf.LBAbegin,&adr) == 0)
			buf.CHSbegin = adr;
		else
		{
			buf.CHSbegin = geom;
			buf.CHSbegin.s -= 1;
		} 
		if (a_lba2large(geom,adres,&adr) == 0)
			buf.CHSend = adr;
		else
		{
			buf.CHSend = geom;
			buf.CHSend.s -= 1;
		}
		flag = 1;
		while (flag){
			flag = 0;
			printf("Тип ОС:\n");
			printf("1 - Empty\n");
			printf("2 - FAT12\n");
			printf("3 - FAT16 < 32M\n");
			printf("4 - Расширенный\n");
			printf("5 - MS-DOS FAT16\n");
			printf("6 - HPFS/NTFS\n");
			printf("7 - Win95 FAT32 (LBA)\n");
			printf("8 - Win95 FAT16\n");
			printf("9 - Linux swap\n");
			printf("0 - Linux\n");
			scanf("%d",&type_oc);
			switch (type_oc){
				case 1:
					 buf.oc = 0x00;
				break;
				case 2:
					 buf.oc = 0x01;
				break;
				case 3:
					 buf.oc = 0x04;
				break;
				case 4:
					 buf.oc = 0x05;
				break;
				case 5:
					 buf.oc = 0x06;
				break;
				case 6:
					 buf.oc = 0x07;
				break;
				case 7:
					 buf.oc = 0x0c;
				break;
				case 8:
					 buf.oc = 0x0e;
				break;
				case 9:
					 buf.oc = 0x82;
				break;
				case 0:
					 buf.oc = 0x83;
				break;
				default:
					 flag = 1;
			}
		}
		buf.active = 0;
		if(b){
			printf("Установить раздел активным (y/n)\n"); 
			do{
				scanf("%c",&c);
			} while((c != 'n') && (c != 'y'));
			if ((c == 'y')){
				buf.active = 0x80;
				b = 0;
			}
		}
		if (((buf.CHSbegin.c == geom.c) && (buf.CHSbegin.h == geom.h) && (buf.CHSbegin.s == geom.s)) || (k == 3))
		{
			tail->table[k] = buf;
			tail->table[k].oc = 0x00;
			if (k != 3)
				tail->table[k+1].LBAbegin.size = 0;
			temp = malloc(sizeof(struct part_tables));
			tail->next = temp;
			tail = temp;
			tail->table[0] = buf;
			tail->table[1].LBAbegin.size = 0;
			k = 1;
		} else {
			tail->table[k] = buf;
			tail->table[++k].LBAbegin.size = 0;
		}
	} while (free_size != 0);
	printf("Ак#   CHS нач   # ОС #    CHS кон  #   LBA нач  #     Размер \n");
	temp = head;
 	while (temp != NULL){
		int i;
		for (i = 0; i < 4; i++)
		{ 
			if (temp->table[i].LBAbegin.size == 0) break;
			printf("%2x", temp->table[i].active);
			printf("%7d", temp->table[i].CHSbegin.c);
			printf("%4d", temp->table[i].CHSbegin.h);
			printf("%3d", temp->table[i].CHSbegin.s + 1);
			printf("%5x", temp->table[i].oc);
			printf("%7d", temp->table[i].CHSend.c);
			printf("%4d", temp->table[i].CHSend.h);
			printf("%3d", temp->table[i].CHSend.s + 1);
			printf("%13d", temp->table[i].LBAbegin.size);
			printf("%13d\n", temp->table[i].size);
		}
		temp = temp->next;
		printf("\n");
	}
	return 0;
}

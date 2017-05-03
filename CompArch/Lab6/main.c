#include "hdchs.h"
#include <stdlib.h>
#include <stdio.h>	

typedef struct
{
	unsigned char active;   
	tLARGE CHSbegin;        
	unsigned char type;     
	tLARGE CHSend;           
	tLBA LBAbegin;         
	unsigned int size; 
} part;

struct part_tables {
	part table[4];
	struct part_tables *next;
} *head,*temp,*tail;

	part tm;
	tIDECHS source;
	tLARGE geom, adr;
	tLBA disk, adres;

int main(){
	int t,k = 0,b = 1,free_size,type_oc,flag;
	char c;
	adres.size = 1; // 0 - this table
	geom.c = 1023;
	geom.h = 255;
	geom.s = 63;
	head = malloc(sizeof(struct part_tables));
	tail = head;
 
	printf("Введите IDECHS геометрию диска\n");
	
	do {
		printf("C:"); 
		scanf("%d",&t);
		if(t > geom.c)
			printf("Error\n");
		else break;
	} while (1);
	source.c=t;
	
	do {
		printf("H:");
		scanf("%d",&t);
		if(t > 15)
			printf("Error\n");
		else break;
	} while (1);
	source.h=t;
	
	do {
		printf("S:");
		scanf("%d",&t);
		if(t > geom.s)
			printf("Error\n");
		else break;
	} while (1);
	source.s=t;

	g_idechs2lba(source, &disk);
	printf("Размер диска %.2f Gb\n",(double) disk.size / (2048 * 1024)); // * 512 / 1024^3
	free_size=disk.size / 2; // * 512 / 1024 
	do{
		do{
			printf("Свободного места: %d Кб\n",free_size);
			printf("Размер раздела (Кб):"); 
			scanf("%d",&t);
		} while (t > free_size);
		if(t == 0) break;
		free_size -= t;
		tm.LBAbegin.size = adres.size;
		tm.size = t * 2;
		adres.size += tm.size;
		if(a_lba2large(geom,tm.LBAbegin,&adr) == 0)
			tm.CHSbegin = adr;
		else
			tm.CHSbegin = geom; 
		if (a_lba2large(geom,adres,&adr) == 0)
			tm.CHSend = adr;
		else
			tm.CHSend = geom;
		flag = 1;
		while (flag){
			flag = 0;
			printf("Тип ОС:\n");
			printf("1 - FAT16\n");
			printf("2 - FAT32\n");
			printf("3 - Linux swap\n");
			printf("4 - Linux\n");
			printf("5 - HPFS/NTFS\n");
			scanf("%d",&type_oc);
			switch (type_oc){
				case 1:
					 tm.type = 0x04;
				break;
				case 2:
					 tm.type = 0x0c;
				break;
				case 3:
					 tm.type = 0x82;
				break;
				case 4:
					 tm.type = 0x83;
				break;
				case 5:
					 tm.type = 0x07;
				break;
				default:
					 flag = 1;
			}
		}
		tm.active = 0;
		if(b){
			printf("Установить раздел активным (y/n)\n"); 
			do{
				scanf("%c",&c);
			} while((c != 'n') && (c != 'y'));
			if ((c == 'y')){
				tm.active = 0x80;
				b = 0;
			}
		}
		if (((tm.CHSbegin.c == geom.c) && (tm.CHSbegin.h == geom.h) && (tm.CHSbegin.s == geom.s)) || (k == 3))
		{
			tail->table[k] = tm;
			tail->table[k].type = 0x05;
			if (k != 3)
				tail->table[k+1].LBAbegin.size = 0;
			temp = malloc(sizeof(struct part_tables));
			tail->next = temp;
			tail = temp;
			tail->table[0] = tm;
			tail->table[1].LBAbegin.size = 0;
			k = 1;
		} else {
			tail->table[k] = tm;
			tail->table[++k].LBAbegin.size = 0;
		}
	} while (free_size != 0);
	printf("Ак#   CHS нач   # ОС #    CHS кон  #   LBA нач  #     Размер \n");
	temp = head;
 	while (temp != NULL){
		int i;
		//printf("Адрес сектора где расположена таблица %d\n",temp->table[0].LBAbegin);
		for (i = 0; i < 4; i++)
		{ 
			if (temp->table[i].LBAbegin.size == 0) break;
			printf("%2x", temp->table[i].active);
			printf("%7d", temp->table[i].CHSbegin.c);
			printf("%4d", temp->table[i].CHSbegin.h);
			printf("%3d", temp->table[i].CHSbegin.s + 1);
			printf("%5x", temp->table[i].type);
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

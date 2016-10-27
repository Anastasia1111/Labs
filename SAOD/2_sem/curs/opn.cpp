// Вариант №41 B2 C2 S1 D2

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <conio.h>

#define DBSize 4000

using namespace std;

struct record
{
	char fio[30];
	short int dept;
	char post[22];
	char dob[10];
};

record* database;
int* index;

void readDB()
{
	FILE *pF;
	pF = fopen("testBase2.dat","rb");
	database = new record [DBSize];
	int count = fread((record*)database, sizeof(record), DBSize, pF);
	cout<<count<<endl;
	if (count != DBSize) {
		puts("\nERROR! Something unexpected caused a problem! Database wastn't readed!\n");
		system("PAUSE");
		exit(1);
	}
	
	index = new int [DBSize];
	for (int i=0; i<DBSize; i++)
		index[i] = i;
	fclose(pF);
}

void printDB()
{
	char ch;
	int i;
	int first = 0;
	int last = 20;
	while (1)
	{
		system("CLS");
		for (i=first; i<last; i++) {
			printf("%04d) %30s  %03d  %22s  %10s\n",i+1,database[index[i]].fio,
														database[index[i]].dept,
														database[index[i]].post,
														database[index[i]].dob);
		}
		puts("\nNEXT 20: RIGHT\nPREVIOUS 20: LEFT\nEXIT: Esc");
		ch = getch();
		switch(ch)
		{
			case 77:
				{
					if ((last+20)<=DBSize)
					{
						first += 20;
						last += 20;
					}
					break;
				}
			case 75:
				{
					if ((first-20)>=0)
					{
						first -= 20;
						last -= 20;
					}
					break;
				}
			case 27:
				{
					system("CLS");
					return;
				}
		}
	}
	puts("\nERROR! Something unexpected caused a problem!\n");
	system("PAUSE");
	exit(1);
}

int compare_strings(char* str1, char* str2, int size)
{
	for (int i=0; i<size; i++) {
		if (str1[i]<str2[i]) {
			return -1;
		} else {
			if (str1[i]>str2[i]) {
				return 1;
			} else {
				i++;
			}
		}
	}
	return 0;
}

int compare_records(int num1, int num2)
{
	int flag = compare_strings(database[num1].dob, database[num2].dob, 2);
	if (!flag) {
		flag = compare_strings(database[num1].fio, database[num2].fio, 30);
	}
	return flag;
}

void Heap(int l, int r)
{
	int x = index[l], i = l, j;
	while (1) {
		j = 2*i;
		if (j>r) 
			break;
		if ((j<r)&&(compare_records(index[j+1],index[j])>-1)) 
			j++;
		if (compare_records(x,index[j])>-1)
			break;
		index[i] = index[j];
		i = j;
	}
	index[i] = x;
}

void HeapSort()
{
	int l = DBSize/2;
	while (l>=0) {
		Heap(l, DBSize-1);
		l--;
	}
	int r = DBSize;
	while (r>0) {
		int buf = index[0];
		index[0] = index[r-1];
		index[r-1] = buf;
		r--;
		Heap(0, r-1);
	}
}

int main()
{
	readDB();
	printDB();
	
	HeapSort();
	printDB();
	
	return 0;
}

// Variant #41 B2 C2 S1 D2 E3

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

struct qEl
{
	qEl* next;
	record rcrd;
};

struct queue
{
	qEl* head;
	qEl* tail;
};

struct vertex
{
	record* rcrd;
	vertex* left;
	vertex* right;
};

record* database;
int* index;
queue* srch_res;

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
	if (database[num1].dob[0]<database[num2].dob[0]) 
	{
		return -1;
	} else {
		if (database[num1].dob[0]>database[num2].dob[0])
		{
			return 1;
		} else {
			if (database[num1].dob[1]<database[num2].dob[1]) 
			{
				return -1;
			} else {
				if (database[num1].dob[1]>database[num2].dob[1]) 
				{
					return 1;
				} else {
					if (compare_strings(database[num1].fio,database[num2].fio,30)==-1) 
					{
						return -1;
					} else {
						return 1;
					}
				}
			}
		}
	}
}

void Heap(int l, int r)
{
	int j = 2*l, t, buf;
	while (j+1 < r) {
		t = j+1;
		if ((t+1)<r && (compare_records(index[t+1],index[t])>-1))
		{
			t++;
		}
		if (compare_records(index[l],index[t])==-1)
		{
			buf = index[l];
			index[l] = index[t];
			index[t] = buf;
			l = t;
			j = 2*l;
		} 
		else break;
	}
}

void HeapSort()
{
	for (int l = DBSize/2; l>=0; l--)
    {
        Heap(l, DBSize);
    }
	int r = DBSize, buf;
	while (r>0) {
		buf = index[0];
		index[0] = index[r-1];
		index[r-1] = buf;
		r--;
		Heap(0, r);
	}
}

void initQueue()
{
	srch_res = new queue;
	srch_res->tail = (qEl*)&srch_res->head;
}

void addToQueue(record data)
{
	qEl *new_el = new qEl;
	new_el->rcrd = data;
	srch_res->tail->next = new_el;
	srch_res->tail = new_el;
}

void printQueue()
{
	qEl* cur_el = srch_res->head;
	while (cur_el!=srch_res->tail)
	{
		printf("%30s  %03d  %22s  %10s\n",	cur_el->rcrd.fio,
											cur_el->rcrd.dept,
											cur_el->rcrd.post,
											cur_el->rcrd.dob);
		cur_el = cur_el->next;
	}	
}	

int main()
{
	readDB();
	printDB();
	
	HeapSort();
	printDB();
	
	// Queue making
	initQueue();
	for (int i=0; i<10; i++) {
		addToQueue(database[index[i]]);
	}
	printQueue();
	system("PAUSE");
	
	// Tree making
	
	return 0;
}

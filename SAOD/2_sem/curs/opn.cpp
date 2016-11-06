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
	char fullname[30];
	short int dept;
	char post[22];
	char dob[10];
};

struct qEl
{
	qEl* next;
	record* rcrd;
};

struct queue
{
	qEl* head;
	qEl* tail;
};

struct vertex
{
	char bal;
	record* rcrd;
	vertex* left;
	vertex* right;
};

record* database;
record** index;
queue* srch_res;
vertex* tree;

void readDB()
{
	FILE *pF;
	pF = fopen("testBase2.dat","rb");
	database = new record [DBSize];
	int count = fread((record*)database, sizeof(record), DBSize, pF);
	if (count != DBSize) {
		puts("\nERROR! Something unexpected caused a problem! Database wastn't readed!\n");
		system("PAUSE");
		exit(1);
	}
	
	index = new record* [DBSize];
	for (int i=0; i<DBSize; i++)
		index[i] = &database[i];
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
			printf("%04d) %30s  %03d  %22s  %10s\n",i+1,index[i]->fullname,
														index[i]->dept,
														index[i]->post,
														index[i]->dob);
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

int compare_dob(char* dob1, char* dob2)
{
	if (dob1[0]<dob2[0]) 
	{
		return -1;
	} else {
		if (dob1[0]>dob2[0])
		{
			return 1;
		} else {
			if (dob1[1]<dob2[1]) 
			{
				return -1;
			} else {
				if (dob1[1]>dob2[1]) 
				{
					return 1;
				} else {
					return 0;
				}
			}
		}
	}
}

int compare_fullname(char* fn1, char* fn2)
{
	for (int i=0; i<30; i++) {
		if (fn1[i]<fn2[i]) {
			return -1;
		} else {
			if (fn1[i]>fn2[i]) {
				return 1;
			}
		}
		i++;
	}
	return 0;
}

int compare_records(record* rcrd1, record* rcrd2)
{
	int flag = compare_dob(rcrd1->dob, rcrd2->dob);
	if (flag==0) {
		if (compare_fullname(rcrd1->fullname, rcrd2->fullname)==-1) 
		{
			return -1;
		} else {
			return 1;
		}
	}
	return flag;
}

void Heap(int l, int r)
{
	int j = 2*l, t;
	record* buf;
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
	int r = DBSize;
	record* buf;
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

void addToQueue(record* data)
{
	qEl *new_el = new qEl;
	new_el->rcrd = data;
	srch_res->tail->next = new_el;
	srch_res->tail = new_el;
}

void printQueue()
{
	char ch;
	int i;
	int first = 0;
	int last = 20;
	qEl* cur_el = srch_res->head;
	while (1)
	{
		system("CLS");
		for (i=first; (i<last)&&(cur_el!=srch_res->tail); i++) {
			printf("%04d) %30s  %03d  %22s  %10s\n",i+1,cur_el->rcrd->fullname,
														cur_el->rcrd->dept,
														cur_el->rcrd->post,
														cur_el->rcrd->dob);
			cur_el = cur_el->next;
		}
		puts("\nNEXT 20: ANY KEY\nEXIT: Esc");
		ch = getch();
		switch(ch)
		{
			default:
				{
					if (cur_el!=srch_res->tail) {
						first += 20;
						last += 20;
						break;
					}
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

int binSearch(char* key)
{
	int l = 0;
	int r = DBSize-1;
	int m;
	while (l<r) {
		m = (l+r)/2;
		if (compare_dob(index[m]->dob,key)==-1) {
			l = m+1; 
		} else {
			r = m;
		}
	}
	if (compare_dob(index[r]->dob, key)==0) return r;
	return -1;
}

void makeQueue()
{
	char key[11];
	puts("WARNING! Key of search is ONLY day of birth! WARNING!\n");
	puts("Type the search key: ");
	gets(key);
	if (key[3]=='\0') {
		int id = binSearch(key);
		if (id>=0) {
			while (compare_dob(index[id]->dob,key)==0) {
				addToQueue(index[id]);
				id++;
			}
		} else {
			puts("Requested value isn't found!\n");
			system("PAUSE");
			exit(1);
		}
	} else {
		puts("\nERROR! Recived value too big!\n");
		system("PAUSE");
		exit(1);
	}
}

void freeQueue(){
     qEl* tmp;
     qEl* head = srch_res->head;
     while (head!=srch_res->tail){
           tmp = head;
           head = head->next;
           delete tmp;
     }
     srch_res->tail = srch_res->head = head = NULL;
}

vertex* TreeSearch (vertex* root, short int key)
{
	if ( !root ) return NULL;
	if (key == root->rcrd->dept) {
		return root;
	} else {
		if (key < root->rcrd->dept) {
			return TreeSearch (root->left,key);
		} else {
			return TreeSearch (root->right,key);
		}
	}
}

void searchInTree()
{
	short int key;
	system("CLS");
	puts("WARNING! Key of search is ONLY number of departament! WARNING!\n");
	puts("Type the search key: ");
	scanf("%d",&key);
	vertex* res = TreeSearch(tree, key);
	if (res!=NULL) {
		printf("Result:\n%30s  %03d  %22s  %10s\n",	res->rcrd->fullname,
													res->rcrd->dept,
													res->rcrd->post,
													res->rcrd->dob);
		system("PAUSE");
		return;
	} else {
		puts("Requested value isn't found!\n");
		system("PAUSE");
		return;
	} 
	puts("\nERROR! Something unexpected caused a problem!\n");
	system("PAUSE");
	exit(1);
}

void addToBBT(record* data, vertex* &root, bool &HG, bool &VG)
{
	vertex* neighbor;
	if (root == NULL){   
		root = new vertex;
		root->rcrd = data;
		root->left = root->right = NULL;
		root->bal = 0;
		VG = true;
	} else {
		if (root->rcrd->dept > data->dept) {
			addToBBT(data, root->left, HG, VG);
			if (VG) {
				if (root->bal == 0) {
					neighbor = root->left;
					root->left = neighbor->right;
					neighbor->right = root;
					root = neighbor;
					neighbor->bal = 1;
					VG = false;
					HG = true;
				} else {
					root->bal = 0;
					VG = true;
					HG = false;
				}
			} else {
				HG = false;
			}
		} else {
			if (root->rcrd->dept <= data->dept) {
				addToBBT(data, root->right, HG, VG);
				if (VG) {
					root->bal = 1;
					VG = false;
					HG = true;
				} else {
					if (HG) {
						if (root->bal == 1) {
							neighbor = root->right;
							root->bal = 0;
							neighbor->bal = 0;
							root->right = neighbor->left;
							neighbor->left = root;
							root = neighbor;
							VG = true;
							HG = false;
						} else {
							HG = false;
						}
					}
				}
			}
		}
	}
}

void makeTree()
{
	qEl* curr_el = srch_res->head;
	bool HG = true;
	bool VG = true;
	while(curr_el != srch_res->tail){
        addToBBT(curr_el->rcrd, tree, HG, VG);
        curr_el = curr_el->next;
    }
}

void printTree(vertex* root){	
	if ( !root ) return;
	printTree (root->left);
	printf("%30s  %03d  %22s  %10s\n",	root->rcrd->fullname,
										root->rcrd->dept,
										root->rcrd->post,
										root->rcrd->dob);
	printTree (root->right);
}

int main()
{
	readDB();
	printDB();
	
	HeapSort();
	printDB();
	
	// Queue making
	initQueue();
	makeQueue();
	printQueue();
	
	// Tree making
	
	makeTree();
	printTree(tree);
	system("PAUSE");
	searchInTree();
	freeQueue();
	
	return 0;
}

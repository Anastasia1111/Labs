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

record* database = NULL;
record** index = NULL;
queue* srch_res = NULL;
vertex* tree = NULL;

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

void freeDB()
{
	if (database!=NULL){
		delete[] database;
		delete[] index;
		database = NULL;
		index = NULL;
	}
}

void printDB()
{
	if (database==NULL){
		system("CLS");
		puts("Database hasn't readed yet!\n");
		system("PAUSE");
		return;
	}
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

void heap(int l, int r)
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

void heapSort()
{
	if (database==NULL){
		system("CLS");
		puts("Database hasn't readed yet!\n");
		system("PAUSE");
		return;
	}
	for (int l = DBSize/2; l>=0; l--)
    {
        heap(l, DBSize);
    }
	int r = DBSize;
	record* buf;
	while (r>0) {
		buf = index[0];
		index[0] = index[r-1];
		index[r-1] = buf;
		r--;
		heap(0, r);
	}
}

void freeQueue(){
	if (srch_res!=NULL){
	    qEl* tmp;
	    qEl* head = srch_res->head;
	    while (head!=srch_res->tail){
	        tmp = head;
	        head = head->next;
	        delete tmp;
	    }
	    delete head;
	    srch_res->tail = srch_res->head = NULL;
	    srch_res = NULL;
	}
}

void initQueue()
{
	if (srch_res==NULL) {
		srch_res = new queue;
		srch_res->tail = (qEl*)&srch_res->head;
	} else {
		freeQueue();
		initQueue();
	}
}

void addToQueue(record* data)
{
	qEl* new_el = new qEl;
	new_el->rcrd = data;
	srch_res->tail->next = new_el;
	srch_res->tail = new_el;
}

int searchInDB()
{
	if (database==NULL){
		system("CLS");
		puts("Database hasn't readed yet!\n");
		system("PAUSE");
		return 0;
	}
	char key[3];
	system("CLS");
	puts("WARNING! Key of search is ONLY day of birth! WARNING!\n");
	puts("Type the search key: ");
	scanf("%s",&key);
	int id = binSearch(key);
	if (id>=0) {
		initQueue();
		while (compare_dob(index[id]->dob,key)==0) {
			addToQueue(index[id]);
			id++;
		}
		return 1;
	} else {
		puts("Requested value isn't found!\n");
		system("PAUSE");
		return 0;
	}
	puts("\nERROR! Something unexpected caused a problem!\n");
	system("PAUSE");
	exit(1);
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
		for (i=first; (i<last)&&(cur_el!=srch_res->tail->next); i++) {
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
					if (cur_el!=srch_res->tail->next) {
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

vertex* TreeSearch (vertex* root, short int key)
{
	if ( !root ) return NULL;
	if (key == root->rcrd->dept) {
		TreeSearch (root->left,key);
		addToQueue(root->rcrd);
		TreeSearch (root->right,key);
		return root;
	} else {
		if (key < root->rcrd->dept) {
			return TreeSearch (root->left,key);
		} else {
			return TreeSearch (root->right,key);
		}
	}
}

int searchInTree()
{
	if (tree==NULL){
		system("CLS");
		puts("Tree hasn't created yet!\n");
		system("PAUSE");
		return 0;
	}
	short int key;
	system("CLS");
	puts("WARNING! Key of search is ONLY number of departament! WARNING!\n");
	puts("Type the search key: ");
	scanf("%d",&key);
	initQueue();
	vertex* res = TreeSearch(tree, key);
	if (res!=NULL) {
		return 1;
	} else {
		puts("Requested value isn't found!\n");
		system("PAUSE");
		return 0;
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
	if (srch_res!=NULL){
		qEl* curr_el = srch_res->head;
		bool HG = true;
		bool VG = true;
		while(curr_el != srch_res->tail->next){
	        addToBBT(curr_el->rcrd, tree, HG, VG);
	        curr_el = curr_el->next;
	    }
	} else {
		system("CLS");
		puts("Queue hasn't created yet!\n");
		system("PAUSE");
		return;
	} 
}

void addFromTreeToQueue(vertex* root){	
	if ( !root ) return;
	addFromTreeToQueue(root->left);
	addToQueue(root->rcrd);
	addFromTreeToQueue(root->right);
}

int printTree()
{
	if (tree!=NULL) {
		initQueue();
		addFromTreeToQueue(tree);
		return 1;
	} else {
		system("CLS");
		puts("Tree hasn't created yet!\n");
		system("PAUSE");
		return 0;
	} 
	puts("\nERROR! Something unexpected caused a problem!\n");
	system("PAUSE");
	exit(1);
}

void freeTree(vertex* root){
	if (root->left) {
        freeTree (root->left);
	}
    if (root->right) {
        freeTree (root->right);
	}
    delete root;
}

int main()
{
	char selector;
	while(1){
		system("CLS");
		puts("MENU:\n\
1. Load database\n\
2. Print database\n\
3. Sort database\n\
4. Make queue (Find a key)\n\
5. Make tree\n\
6. Print tree\n\
7. Search in tree\n\
8. Free all the memory (ONLY FOR EXPERIENCED USERS)\n\
ESC. Exit\n");
		selector = getch();
		switch(selector)
		{
			case '1':
				{
					freeDB();
					readDB();
					break;
				}
			case '2':
				{
					printDB();
					break;
				}
			case '3':
				{
					heapSort();
					break;
				}
			case '4':
				{
					if(searchInDB()){
						printQueue();
					}
					break;
				}
			case '5':
				{
					if(tree!=NULL){
						freeTree(tree);
					}
					makeTree();
					break;
				}
			case '6':
				{
					if(printTree()){
						printQueue();
					}
					break;
				}
			case '7':
				{
					if(searchInTree()){
						printQueue();
					}
					break;
				}
			case '8':
				{
					if(tree!=NULL){
						freeTree(tree);
					}
					freeQueue();
					freeDB();
					break;
				}
			case 27:
				{
					system("CLS");
					return 0;
				}
			default:
				{
					puts("\nWRONG KEY\n");
				}
		}
	}
}

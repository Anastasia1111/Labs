// Variant #41 B2 C2 S1 D2 E3
#pragma pack(push, 1)

#include <algorithm>
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

struct chr
{
	int prob;
	unsigned char ch;
};

record* database = NULL;
record** index = NULL;
queue* srch_res = NULL;
vertex* tree = NULL;
chr* alphabet = NULL;
string* CodeWord = NULL;

void freeDB();
void readDB();
void printDB();
int searchInDB();
void heapSort();
void heap(int l, int r);
void freeQueue();
void initQueue();
void addToQueue(record* data);
void printQueue();
int binSearch(char* key);
void freeTree(vertex* root);
void addToBBT(record* data, vertex* &root, bool &HG, bool &VG);
int makeTree();
int printTree();
int searchInTree();
void addFromTreeToQueue(vertex* root);
vertex* TreeSearch (vertex* root, short int key);
int compare_dob(char* dob1, char* dob2);
int compare_fullname(char* fn1, char* fn2);
int compare_records(record* rcrd1, record* rcrd2);
void encode();
int find_probability();
bool comparator(chr a, chr b);
void freeCode();
void codeFano(char l, char r);
char med(char l, char r);
void menu();

int main()
{
	menu();
	return 0;
}

void menu()
{
	char selector;
	while(1){
		system("CLS");
		puts("MENU:\n\
1. Load database\n\
2. Print database\n\
3. Sort database\n\
4. Make queue (Find a key)\n\
5. Print queue\n\
6. Make tree\n\
7. Print tree\n\
8. Search in tree\n\
9. Free all the memory (ONLY FOR EXPERIENCED USERS)\n\
C. Encode database (ONLY FOR EXPERIENCED USERS)\n\
ESC. Exit\n");
		selector = getch();
		switch(selector)
		{
			case '1':
				{
					readDB();
				}
			case '2':
				{
					printDB();
					break;
				}
			case '3':
				{
					heapSort();
					printDB();
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
					printQueue();
					break;
				}
			case '6':
				{
					if(!makeTree()){
						break;
					}
				}
			case '7':
				{
					if(printTree()){
						printQueue();
					}
					break;
				}
			case '8':
				{
					if(searchInTree()){
						printQueue();
					}
					break;
				}
			case '9':
				{
					freeCode();
					if(tree!=NULL){
						freeTree(tree);
					}
					freeQueue();
					freeDB();
					break;
				}
			case 'Ñ':
			case 'ñ':
			case 'C':
			case 'c':
				{
					encode();
					break;
				}
			case 27:
				{
					system("CLS");
					return;
				}
			default:
				{
					puts("\nWRONG KEY\n");
				}
		}
	}
}

void readDB()
{
	freeDB();
	
	FILE *pF;
	pF = fopen("testBase2.dat","rb");
	database = new record [DBSize];
	int count = fread((record*)database, sizeof(record), DBSize, pF);
	if (count != DBSize)
	{
		puts("\nERROR! Something unexpected caused a problem! Database wastn't readed!\n");
		system("PAUSE");
		exit(1);
	}
	
	index = new record* [DBSize];
	for (int i=0; i<DBSize; i++)
		index[i] = &database[i];
	fclose(pF);
}

void initQueue()
{
	if (srch_res!=NULL){
		freeQueue();
	}
	srch_res = new queue;
	srch_res->tail = (qEl*)&srch_res->head;
}

void addToQueue(record* data)
{
	qEl* new_el = new qEl;
	new_el->rcrd = data;
	srch_res->tail->next = new_el;
	srch_res->tail = new_el;
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

int makeTree()
{
	if (srch_res==NULL){
		system("CLS");
		puts("Queue hasn't created yet!\n");
		system("PAUSE");
		return 0;
	}
	if (tree!=NULL){
		freeTree(tree);
	}
	qEl* curr_el = srch_res->head;
	bool HG = true;
	bool VG = true;
	while(curr_el != srch_res->tail->next){
        addToBBT(curr_el->rcrd, tree, HG, VG);
        curr_el = curr_el->next;
    }
    return 1;
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

void freeDB()
{
	if (database!=NULL){
		delete[] database;
		delete[] index;
		database = NULL;
		index = NULL;
	}
}

void freeQueue()
{
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

void freeTree(vertex* root)
{
	if (root->left) {
        freeTree (root->left);
	}
    if (root->right) {
        freeTree (root->right);
	}
    delete root;
}

void freeCode()
{
	if (alphabet!=NULL || CodeWord!=NULL){
		delete[] alphabet;
		delete[] CodeWord;
		alphabet = NULL;
		CodeWord = NULL;
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

void printQueue()
{
	if (srch_res==NULL){
		system("CLS");
		puts("Queue hasn't created yet!\n");
		system("PAUSE");
		return;
	}
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

void addFromTreeToQueue(vertex* root){	
	if ( !root ) return;
	addFromTreeToQueue(root->left);
	addToQueue(root->rcrd);
	addFromTreeToQueue(root->right);
}

int printTree()
{
	if (tree==NULL){
		system("CLS");
		puts("Tree hasn't created yet!\n");
		system("PAUSE");
		return 0;
	}
	initQueue();
	addFromTreeToQueue(tree);
	return 1;
}

void encode()
{
	if (database==NULL){
		system("CLS");
		puts("Database hasn't readed yet!\n");
		system("PAUSE");
		return;
	}
	FILE *pF;
	pF = fopen("encoding_results.dat","wb");
	
	if (pF != NULL)
	{
		freeCode();
		alphabet = new chr[256];
		
		for (int i=0; i<256; i++){
			alphabet[i].prob = 0;
			alphabet[i].ch = i;
		}
		
		char CWNum = find_probability();
		
		CodeWord = new string[CWNum];
		
		for (int i=0; i<CWNum; i++){
			CodeWord[i] = "";
		}
		
		codeFano(0,CWNum);
		
		char* DB = (char *)database;
		int size = sizeof(record)*DBSize;
		char buf = 0;
		char bit_count = 0;
		int CWSize = 0;
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<CWNum; j++){
				if (DB[i]==alphabet[j].ch)
				{
					CWSize = CodeWord[j].size();
					for (int k=0; k<CWSize; k++){
						if (bit_count==8)
						{
							fputc((int)buf, pF);
							/*cout<<buf;
							getch();*/
							buf = 0;
							bit_count = 0;
						}
						if(CodeWord[j][k]=='1')
						{
							buf++;
						}
						buf <<= 1;
						bit_count++;
					}
				}
			}
		}
		if(bit_count!=0)
		{
			for(int j=bit_count; j<8; j++)
				buf<<=1;
			fputc((int)buf, pF);
			buf = 0;
			bit_count = 0;
		}
	} else {
		puts("\nERROR! Something unexpected caused a problem! Encoding results wastn't created!\n");
		system("PAUSE");
		exit(1);
	}
	
	system("PAUSE");
	fseek(pF, 0, SEEK_END);
	long size = ftell(pF);
	
	cout << "Size of encoding_results.dat: " << size << " bytes\n";

	fclose(pF);
}

bool comparator(chr a, chr b)
{
	return a.prob<b.prob;
}

int find_probability()
{
	unsigned char* DB = (unsigned char *)database;
	int size = sizeof(record)*DBSize;
	for (int i=0; i<size; i++){
		/*cout<<DB[i]<<(int)DB[i]<<"="<<alphabet[DB[i]].ch<<(int)alphabet[DB[i]].ch<<endl;
		system("PAUSE");*/
		alphabet[DB[i]].prob++;
	}
	std::sort(alphabet, alphabet+256, comparator);
	std::reverse(alphabet, alphabet+256);
	
	int real_num = 0;
	int prob = 0;
	while(alphabet[real_num].prob){
		/*cout<<alphabet[real_num].ch<<"("<<(int)alphabet[real_num].ch<<")"<<"("<<alphabet[real_num].prob<<")"<<endl;
		system("PAUSE");*/
		prob += alphabet[real_num].prob;
		real_num++;
	}
	/*int flag = 0;
	if(size==prob) flag = 1;
	cout<<real_num<<" "<<flag<<endl;*/
	return real_num;
}

char med(char l, char r)
{
	int sumL = 0;
	for(int i=l; i<r-1; i++){
		sumL += alphabet[i].prob;
	}
	int sumR = alphabet[r-1].prob;
	char m = r-1;
	while(sumL>=sumR)
	{
		m--;
		sumL -= alphabet[m].prob;
		sumR += alphabet[m].prob;
	}
	return m;
}

void codeFano(char l, char r)
{
	if (l<r)
	{
		char m = med(l,r);
		for (char i=l; i<r; i++){
			if (i<=m)
			{
				CodeWord[i] += '0';
			} else {
				CodeWord[i] += '1';
			}
		}
		codeFano(l, m);
		codeFano(m+1, r);
	}
}

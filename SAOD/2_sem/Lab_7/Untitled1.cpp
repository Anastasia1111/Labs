#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

int N = 100; // size of tree
int H; // fact height
int CHH; // height of local branch
int CS; // control summ
int S; // size (number of elem)
int MIDH; // middle height
int BR; // number of branches
int** AW; 
int** AP; 
int** AR; 

struct tree{
       int wes;
       int data;
       tree *l;
       tree *r;
};
    
void print_struct (tree *m){	
	if ( !m ) return;
	print_struct (m->l);
	printf("%4d",m->data);
	CS += m->data;
	print_struct (m->r);
}

void RandTrMaking (int data, int wes, tree *&head){
   if (head == NULL){    
        head = new tree;
        head->data = data;
        head->wes = wes;
        head->l = head->r = NULL;  
        S++;
    }
    if (data > head->data) {
		RandTrMaking (data, wes, head->r);
	} else {
		if (data < head->data) {
			RandTrMaking (data, wes, head->l);
		} else {
			if (data == head->data) {
            	return;
            }
		}
	}
}

void matrixAW(int** AW, int* W){
	for (int i=0; i<=N; i++){
		for (int j=i+1; j<=N; j++){
			AW[i][j] = AW[i][j-1] + W[j];
		}
	}
}

void matrixAPAR(int** AP, int** AR, int** AW){
	int i,j,h,k,m,min;
	for (i=0; i<N; i++) {
		j = i+1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (h=2; h<=N; h++){
		for (i=0; i<=N-h; i++){
			j = i+h;
			m = AR[i][j-1];
			min = AP[i][m-1] + AP[m][j];
			for (k=m+1; k<=AR[i+1][j]; k++){
				int x = AP[i][k-1] + AP[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void CreateTree(int L, int R, int* A, int* W, tree *&head){
	if (L < R){
		int k = AR[L][R];
		RandTrMaking (A[k], W[k], head);
		CreateTree(L, k-1, A, W, head);
		CreateTree(k, R, A, W, head);
	}
}

void middleHeight (tree *m){
    MIDH += m->wes*CHH;
    if ( m->l ) {
        CHH++;
        middleHeight (m->l);
    }
    if ( m->r ) {
        CHH++;
        middleHeight (m->r);
    }
    if ((!m->l) && (!m->r)){
        BR++;
        if (H < CHH)
           H = CHH;
    }
    CHH--;
    return;
}
       
tree *t_search (tree *m, int key)
{
	if ( !m ) return NULL;
	if (key == m->data)
		return m;
	if (key < m->data)
		return t_search (m->l,key);
	else return t_search (m->r,key);
	
}
       
void ClearTree(tree *S){
	if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    delete S;
}

int shir(int n){
    if (n <= 1) return 1;
    if (n == 2) return 5;
    return shir(n-1) * 2 + 1;
}

void graphtree(tree *head, int xhead, int yhead, int level){
   // bar(xhead, yhead, xhead + 20, yhead + 20);
    int x,y,k;
    k = shir(H - level) / 4; 
    settextstyle (10,0,1);
    bgiout << head->data << "(" << head->wes << ")" ;
    outstreamxy(xhead + 2, yhead + 2);
    if (head->l){
        x = xhead;
        y = yhead + 20;
        line(x, y, x - 20 * k, y + 20);
        graphtree(head->l, x - 20 * k - 20, y + 20, level + 1);
    }
    if (head->r){
        x = xhead + 20;
        y = yhead + 20;
		line(x, y, x + 20 * k, y + 20);
		graphtree(head->r, x + 20 * k, y + 20, level + 1);
    }
}

void graph(tree *head){
	if (!head) return;
	
    int graphx = 3 + shir(H);
    int graphy = 5 + 2 * H - 1;
    initwindow(graphx * 20, graphy * 20);
    int actx,acty;
    actx = (graphx * 20) / 2;
    acty = 10;
    while (1) {
         cleardevice(); 
         graphtree (head, actx, acty, 0);
         char ch = getch();
         fflush(stdin);
         if (ch == 'a') actx+=20;
         if (ch == 'd') actx-=20;
         if (ch == 'w') acty+=20;
         if (ch == 's') acty-=20;
         if (ch == 27) break;
    }
    cleardevice();
    closegraph();
}

void InsertSort (int *a, int n){
	int i,j,key;
	for (j=2;j<=n;j++){
		key=a[j];
		i=j-1;
		while(i>=1 && a[i]>key){
			a[i+1]=a[i];
			i--;
	    }
	 	a[i+1]=key;
	}
} 

main(){
	srand (time(NULL));
    int key;
    int *A = new int [N+1];
    int *W = new int [N+1];
    int Wes = 0;
    tree *h = NULL;
    tree *see = NULL;
    int i,j;
    
    AW = new int* [N+1];
    for (i=0; i<N+1; i++){
		AW[i] = new int [N+1];
	}
    AP = new int* [N+1];
    for (i=0; i<N+1; i++){
		AP[i] = new int [N+1];
	}
    AR = new int* [N+1];
    for (i=0; i<N+1; i++){
		AR[i] = new int [N+1];
	}
    
    puts("\n\n**********************  LAB 7  ***************************");
    
    puts("\n");
    printf("\nInput array: \n");
    for (i=1; i<=N; i++){
		A[i] = rand() % (N*2) + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        if (j < i) {CS -= A[i]; i--;}
        else printf("%6d",A[i]);
    }
	InsertSort (A, N+1);
	printf(" \nSorted array: \n");
	for (i=1;i<=N;i++){
		W[i] = rand() % 50;
		Wes += W[i];
        printf("%4d (%d)",A[i], W[i]);
    }
	printf("\nCS - %d", CS);
	
    for (i=0; i<=N; i++) {
		for (j=0; j<=N; j++) {
			AW[i][j] = AR[i][j] = AP[i][j] = 0;
		}
	}
    matrixAW(AW, W);
    matrixAPAR(AP, AR, AW);
    /*printf("\nAW:\n");
    for (i=0; i<=N; i++) {
		for (j=0; j<=N; j++) {
			printf("%5d",AW[i][j]);
		}
		printf("\n");
	}
    printf("\nAP:\n");
    for (i=0; i<=N; i++) {
		for (j=0; j<=N; j++) {
			printf("%5d",AP[i][j]);
		}
		printf("\n");
	}
    printf("\nAR:\n");
    for (i=0; i<=N; i++) {
		for (j=0; j<=N; j++) {
			printf("%5d",AR[i][j]);
		}
		printf("\n");
	}*/
    
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    
    CreateTree(0, N, A, W, h);
    middleHeight (h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, ", CS);
    printf("HEIGHT - %d, ", H);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)MIDH/Wes));
    graph(h);
        
    printf("\nEnter the key:");
    scanf ( "%d", &key );
    see = t_search(h,key);
    if (see) {
    	printf("\nElement was found! %d", see->data);
    } else {
    	printf("\nElement wasn't found!");
    }
    
    //ClearTree (h);
    h = NULL;
    delete A;
    system ("PAUSE");
}

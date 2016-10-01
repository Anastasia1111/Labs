#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

int H; // fact height
int CHH; // height of local branch
int CS; // control summ
int S; // size (number of elem)
int MIDH; // middle height
int BR; // number of branches
bool VR; // VerticalRost
bool HR; // HorizontalRost

struct tree{
       int bal;
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

void B2INSERT (int data, tree *&p){
	tree *q;
	if (p == NULL){   
		p = new tree;
		p->data = data;
		p->l = p->r = NULL;
		p->bal = 0;
		VR = true;
		S++;
	} else {
        if (p->data > data) {
            B2INSERT (data, p->l);
            if (VR) {
                if (p->bal == 0) {
					q = p->l;
					p->l = q->r;
					q->r = p;
					p = q;
                 	q->bal = 1;
                 	VR = false;
                 	HR = true;
              	} else {
                 	p->bal = 0;
                 	VR = true;
                 	HR = false;
              	}
           	} else {
				HR = false;
			}
    	} else {
	        if (p->data < data) {
	            B2INSERT (data, p->r);
	            if (VR) {
                 	p->bal = 1;
                 	VR = false;
                 	HR = true;
	            } else {
					if (p->bal == 1) {
						q = p->r;
						p->bal = 0;
						q->bal = 0;
						p->r = q->l;
						q->l = p;
						p = q;
	                 	VR = true;
	                 	HR = false;
	              	} else {
	                 	HR = false;
	              	}
              	}
	    	}
        }
	}
}

void middleHeight (tree *m){
    MIDH+=CHH;
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
    bgiout << head->data;
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

main(){
	srand (time(NULL));
    int n = 20;
    int key;
    int *A = new int [n];
    tree *h = NULL;
    tree *see = NULL;
    int i,j;
    
    puts("\n\n**********************  LAB 6  ***************************");
    
    puts("\n");
    printf("\nInput array: \n");
    for (i=0;i<n;i++){
		A[i] = rand()%(n*2) + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        if (j < i) {CS -= A[i]; i--;}
        else printf("%6d",A[i]);
    }
	printf("\nCS - %d", CS);
	
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    VR = HR = true;
    for(i = 0; i < n; i++){
        B2INSERT (A[i], h);
    }
    middleHeight (h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, ", CS);
    printf("HEIGHT - %d, ", H);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)MIDH/S));
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
    system ("pause");
}

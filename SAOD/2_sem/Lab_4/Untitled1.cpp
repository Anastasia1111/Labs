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
int TC;
bool R;

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

void LLTurn (tree *&p){
     TC++;
     tree* q = p->l;
     p->bal = 0;
     q->bal = 0;
     p->l = q->r;
     q->r = p;
     p = q;
}

void RRTurn (tree *&p){
     TC++;
     tree* q = p->r;
     p->bal = 0;
     q->bal = 0;
     p->r = q->l;
     q->l = p;
     p = q;
}

void LRTurn (tree *&p){
     TC++;
     tree* q = p->l;
     tree* r = q->r;
     if (r->bal < 0)
        p->bal = 1;
     else
        p->bal = 0;
     if (r->bal > 0)
        q->bal = -1;
     else
        q->bal = 0;
     r->bal = 0;
     q->r = r->l;
     p->l = r->r;
     r->l = q;
     r->r = p;
     p = r;
}

void RLTurn (tree *&p){
     TC++;
     tree* q = p->r;
     tree* r = q->l;
     if (r->bal > 0)
        p->bal = -1;
     else
        p->bal = 0;
     if (r->bal < 0)
        q->bal = 1;
     else
        q->bal = 0;
     r->bal = 0;
     p->r = r->l;
     q->l = r->r;
     r->l = p;
     r->r = q;
     p = r;
}

void AVLTrMaking (int data, tree *&p){
       R = true;
       if (p == NULL){   
            p = new tree;
            p->data = data;
            p->l = p->r = NULL;
            p->bal = 0;
            R = true;
            S++;
        }
        else {
            if (p->data > data) {
               AVLTrMaking (data, p->l);
               if (R) {
                  if (p->bal > 0) {
                     p->bal = 0;
                     R = false;
                  } else {
                     if (p->bal == 0) {
                        p->bal=-1;
                        R = true;
                     } else {
                        if (p->l->bal < 0) {
                           LLTurn(p);
                           R = false;
                        } else {
                           LRTurn(p);
                           R = false;
                        }
                     }
                  }
               }
            } else {
                if(p->data < data) {
                   AVLTrMaking (data, p->r);
                   if (R) {
                      if (p->bal < 0) {
                         p->bal = 0;
                         R = false;
                      } else {
                         if (p->bal == 0) {
                            p->bal = 1;
                            R = true;
                         } else {
                            if (p->r->bal > 0) {
                               RRTurn(p);
                               R = false;
                            } else {
                               RLTurn(p);
                               R = false;
                            }
                         }
                      }
                   }
                } else {
                  if (p->data == data) {
                     return;
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
        //MIDH += CHH;
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
    free (S);
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

/*void delete_vertex(tree *&head, int data){
     tree* q, *r, *s;
     tree** p = &head;
     while (*p != NULL) {
           if (data < (*p)->data) p = &((*p)->l);
           else if (data > (*p)->data) p = &((*p)->r);
                else break;
     }
     if (*p != NULL) {
            q = *p;
            if (q->l == NULL) *p = q->r;
            else
                 if (q->r == NULL) *p = q->l;
                 else {
                          r = q->l;
                          s = q;
                          if (r->r == NULL) {
                                   r->r = q->r;
                                   *p = r;
                          } else {
                                 while (r->r != NULL) {
                                       s = r;
                                       r = r->r;
                                 }
                                 s->r = r->l;
                                 r->l = q->l;
                                 r->r = q->r;
                                 *p = r;
                          }
                 }
            delete q;
            q = NULL;
     }
}*/

bool define_tree(tree* head){
     tree* p = head;
     bool dp = true;
     if (p != NULL && (
             (p->l != NULL && 
                   (p->data <= p->l->data || 
                            !define_tree(p->l)   )) 
     ||      (p->r != NULL && 
                   (p->data >= p->r->data || 
                            !define_tree(p->r)   ))
     )){ dp = false;
     }
     return dp;
}

main(){
	srand (time(NULL));
    int n = 1000;
    int key;
    int *A = new int [n];
    tree *h = NULL;
    tree *see = NULL;
    int i,j;
    
    puts("\n\n**********************  LAB 4  ***************************");
    
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
	
    TC = CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    for(i = 0; i < n; i++){
        AVLTrMaking (A[i], h);
    }
    middleHeight (h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, ", CS);
    printf("HEIGHT - %d, ", H);
    printf("SIZE - %d, ", S);
    printf("MIDDLEH - %2.2f, ", ((double)MIDH/S));
    printf("TURN COUNT - %2.2f", ((double)TC/S));
    //graph(h);
    
    bool check = define_tree(h);
    if (check)
        printf("\n It's a search tree!");
    else
        printf("\n It's not a search tree!");
        
    printf("\nEnter the key:");
    scanf ( "%d", &key );
    see = t_search(h,key);
    if (see) {
    	printf("\nElement was found! %d", see->data);
    } else {
    	printf("\nElement wasn't found!");
    }
    /*while (h) {
        printf("\nEnter the key:");
        scanf ( "%d", &key );
        delete_vertex(h,key);
        print_struct (h);
        graph(h);
    }*/
    
    ClearTree (h);
    h = NULL;
    free (A);  
    system ("pause");
}

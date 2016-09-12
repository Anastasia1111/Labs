#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

int H;
int CHH;
int CS;
int MIDH;
bool Rost;

struct tree{
       int bal;
       int data;
       tree *l;
       tree *r;
};
    
void print_struct (tree *m){	
	if ( !m ) return;
	print_struct (m->l);
	printf("%3d ",m->data);
	CS += m->data;
	print_struct (m->r);
}

void AVLTrMaking (int data, tree *&p){
       Rost = true;
       if (p == NULL){    
            p = new tree;
            p->data = data;
            p->l = p->r = NULL;
            p->bal = 0;
            Rost = true;
            MIDH += CHH;
            if (CHH > H)
                H = CHH;
            CHH = 1;
        }
        else {
            if (p->data > data) {
               AVLTrMaking (data, p->l);
               if (Rost) {
                  if (p->bal > 0) {
                     p->bal = 0;
                     Rost = false;
                  } else {
                     if (p->bal == 0) {
                        p->bal=-1;
                        Rost = true;
                     } else {
                        if (p->l->bal < 0) {
                           LLTurn(p);
                           Rost = false;
                        } else {
                           LRTurn(p);
                           Rost = false;
                        }
                     }
                  }
               }
            } else {
                if(p->data < data) {
                   AVLTrMaking (data, p->r);
                   if (Rost) {
                      if (p->bal < 0) {
                         p->bal = 0;
                         Rost = false;
                      } else {
                         if (p->bal == 0) {
                            p->bal = 1;
                            Rost = true;
                         } else {
                            if (p->r->bal > 0) {
                               RRTurn(p);
                               Rost = false;
                            } else {
                               RLTurn(p);
                               Rost = false;
                            }
                         }
                      }
                   }
                }
            }
        }
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

void delete_vertex(tree *&head, int data){
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
}

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
    int n = 10;
    int key;
    int *A = new int [n];
    tree *h;
    tree *see = NULL;
    int i,j;
    
    puts("\n\n**********************  LAB 2  ***************************");
    
    puts("\n");
    printf("\nInput array: \n");
    for (i=0;i<n;i++){
		A[i] = rand()%200 + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        if (j < i) {CS -= A[i]; i--;}
        else printf("%4d",A[i]);
    }
	printf("\nCS - %d", CS);
    CS = H = MIDH = 0; 
    CHH = 1;
    for(i = 0; i < n; i++){
        RandTrMakingTwice (A[i], h);
    }
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, HEIGHT - %d, SIZE - %d, MIDDLEH - %d", CS, H, S, (MIDH/BR)+2);
    graph(h);
    bool check = define_tree(h);
    if (check)
        printf("\n It's a search tree!");
    else
        printf("\n It's not a search tree!");
    ClearTree (h);
    h = NULL;
    
    puts("\n\n*************************************************");
    
    puts("\n");
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    for(i = 0; i < n; i++){
        RandTrMaking (A[i], h);
    }
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, HEIGHT - %d, SIZE - %d, MIDDLEH - %d", CS, H, S, (MIDH/BR)+2);
    graph(h);
    /*see = t_search(h,key);
    if (see) {
    	printf("\nElement was found! %d", see->data);
    } else {
    	printf("\nElement wasn't found!");
    }*/
    while (h) {
          printf("\nEnter the key:");
          scanf ( "%d", &key );
        delete_vertex(h,key);
        print_struct (h);
        graph(h);
    }
    ClearTree (h);
    h = NULL;
    free (A);  
    system ("pause");
}

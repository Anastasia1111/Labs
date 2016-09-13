#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

struct stack{
    int data;
    stack *next;
};

void printStack (stack *p) {
	if ( !p ) return;
	printf("%4d", p->data);
	printStack (p->next);
}

void addToStack (int data, stack *&head) {
     stack* p = new stack;
     p->data = data;
     p->next = head;
     head = p;
}

void deleteFromStack (stack *&head) {
     if (head) {
        stack* p = head;
        head = p->next;
        delete p;
     }
}

void addAfterK (int data, stack *&head, int k) { // A
     stack* p = head;
     if (p) {
         for (int i=0; i<k+1; i++) {
             if (p->next) {
                p = p->next;
             } else break;
         }
     }
     addToStack(data, p);
}

void deleteAfterK (stack *&head, int k) { // B
     stack* p = head;
     if (p) {
         for (int i=0; i<k-1; i++) {
             if (p->next) {
                p = p->next;
             } else break;
         }
     }
     deleteFromStack(p);
}

int measureStack (stack *p) { // C
	if ( !p ) return 0;
	return 1 + measureStack(p->next);
}

void transferFromPToK (stack *&head, int p, int k) { // D
     stack* q = head;
     if (q) {
         for (int i=0; i<k+1; i++) {
             if (q->next) {
                q = q->next;
             } else break;
         }
     } // Repeat from deleteAfterK
     addAfterK (q->data, head, k);
     deleteFromStack(q);
}

bool deleteIfKey (stack *&p, int key) {
     if (p->data == key) {
        stack* q = p;
        p = q->next;
        delete q;
        return true;
     } else return false;
}

main(){
	srand (time(NULL));
    int n = 25;
    char *A = new char [n];
    stack *h = NULL;
    
    printf("\nInput array: \n");
    for (int i = 0; i < n; i++) {
		A[i] = rand()%16;
		printf("%4d",A[i]);
	}
    
    printf("\n\nMiddle-work list: \n");
    int lsize = 0;
    for(int i = 0; i < n; i++) {
        addToStack (A[i]*A[i], h);
    }
    printStack (h);
    printf("\nStack size: %d\n", measureStack(h));
    
    printf("\nOutput list: \n");
    stack* p = h;
    stack *q, *pr_q;
    int data;
    while (p) {
          pr_q = p;
          q = p->next;
          data = p->data;
          //printStack (h);
          //printf("\n");
          while (q) {
                if (q->data == data) {
                    //printf("Ya ydalay %d potomu chto on takoy ge kak %d(%d). Na ego mesto vstanet %d\n",q->data,data,p->data,q->next->data);
                    pr_q->next = q->next;
                    delete q;
                    q = pr_q->next;
                } else {
                    //printf("Ne udalyau\n");
                    pr_q = q;
                    q = q->next;
                }
          }
          p = p->next;
    }
    printStack (h);
    printf("\nStack size: %d\n", measureStack(h));
    
    system ("pause");
}

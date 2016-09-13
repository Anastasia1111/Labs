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
	printf("%d ", p->data);
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

main(){
	srand (time(NULL));
    int n;
    stack *h = NULL;
    
    system ("pause");
}

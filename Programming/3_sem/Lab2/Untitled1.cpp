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

void printList (stack *p) {
	if ( !p ) return;
	printf("%4d", p->data);
	printList (p->next);
}

int measureStack (stack *p) { // Size of stack
	if ( !p ) return 0;
	return 1 + measureStack(p->next);
}

void addToStack (int data, stack *&head) { // Add element to head
     stack* p = new stack;
     p->data = data;
     p->next = head;
     head = p;
}

void addToQueue (int data, stack *&head) { // Add element to tail
     stack* p = head;
     if (p) {
         while (p->next) {
               p = p->next;
         }
         stack* q = new stack;
         q->data = data;
         q->next = NULL;
         p->next = q;
     } else {
         head = new stack;
         head->data = data;
         head->next = NULL;
     }
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

void deleteFromK (stack *&head, int k) { // B
     stack* p = head;
     stack* p_pr = (stack *)&head;
     if (p) {
         for (int i=0; i<k-1; i++) {
             if (p->next) {
                p_pr = p;
                p = p->next;
             } else break;
         }
     }
     p_pr->next = p->next;
     delete p;
}

void transferFromPToK (stack *&head, int p, int k) { // D
     stack* q = head;
     stack* q_pr = (stack *)&head;
     if (q) {
         for (int i=0; i<p-1; i++) {
             if (q->next) {
                q_pr = q;
                q = q->next;
             } else break;
         }
     } // Repeat from deleteAfterK
     addAfterK (q->data, head, k);
     q_pr->next = q->next;
     delete q;
}

main(){
	srand (time(NULL));
    int n = 10;
    char *A = new char [n];
    stack *h = NULL;
    
    printf("\nSECOND LAB\n");
    printf("\nFIRST TASK\n");
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
    printList (h);
    printf("\nStack size: %d\n", measureStack(h));
    
    printf("\nOutput list: \n");
    stack* p = h;
    stack *q, *pr_q;
    int data;
    while (p) {
          pr_q = p;
          q = p->next;
          data = p->data;
          while (q) {
                if (q->data == data) {
                    pr_q->next = q->next;
                    delete q;
                    q = pr_q->next;
                } else {
                    pr_q = q;
                    q = q->next;
                }
          }
          p = p->next;
    }
    printList (h);
    printf("\nStack size: %d\n", measureStack(h));
    system ("pause");
    
    stack* h1 = NULL;
    stack* h2 = NULL;
    for(int i = 0; i < n; i++) {
        system("cls");
        printf("\nSECOND TASK\n");
        addToStack (A[i], h1);
        addToQueue (A[i], h2);
        printf("Stack: "); printList (h1); printf("\n");
        printf("Queue: "); printList (h2); printf("\n");
        system ("pause");
    }    
    system ("pause");
}

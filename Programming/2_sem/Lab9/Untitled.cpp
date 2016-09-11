#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

const short N=4; //���������� ������

typedef struct st { char fam[20]; short mark[N]; struct st *next;} spis;

spis* create(void); //������� �������� ������
void list(spis *head); // ������� ��������� ������
void free_spis(spis *head); //������� ������������ ������

main(){
       spis *head; // ����� ������ ������
       system ("CLS");
       head=create();
       list(head);
       free_spis(head);
       getch(); 
} 

spis* create(){
      spis *p; //��������� �� ������� ���������
      spis *t; //��������� �� "�������" ���������
      spis *pred; //��������� �� ���������� ���������
      spis *h; //��������� �� ������ ���������
      h=pred=t=new spis; //��������� ������ ��� ������ ���������
      printf("Type the last name and marks of student:\n"); 
      scanf("%s", pred->fam);
      for (int i=0; i<N; i++) scanf("%d", pred->mark+i);
      do { 
           p=new spis;
           printf("Type the last name and marks of student:\n");
           scanf("%s", p->fam);
           for (int i=0; i<N; i++) scanf("%d", p->mark+i);
           //������� �����
           while (1) { //��������� ��������� ������ �� ������ �� �������, ����� �������� ������ ���������� ������ ��������
                 t=t->next;
                 if (t==t->next) { break; }
                 if (strcmp(t->fam,p->fam)<0) { pred=t; printf("check");}
           }
           p->next=t; //������ �� ������� ��������� �� �����������
           pred->next=p; //������ �� ���������� ��������� �� �������
           t=h; //���������� "��������" ��������� � ������ ������
           //������� �����
           printf("Continue? y/n "); 
      } while (getch()=='y');
      p->next=NULL; 
      return h; //������� ������ ������
}

void list(spis *head){  
     spis *p;
     p=head;
     printf("\nList of students:");
     while (p!=NULL) { // ���� �� ����� ������
        printf("\n%s",p->fam);
        for (int i=0; i<N; i++) printf("%d", p->mark[i]);
        p=p->next; // ����������� �� ������ 
     }
} 
  
void free_spis(spis *head){ 
     spis *p,*q;
     q=p=head;
     while (p!=NULL) {
           p=q->next;
           delete q; 
           q=p;
     }   
     head=NULL;
}

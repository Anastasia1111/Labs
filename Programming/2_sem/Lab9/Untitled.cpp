#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

const short N=4; //Количество оценок

typedef struct st { char fam[20]; short mark[N]; struct st *next;} spis;

spis* create(void); //функция создания списка
void list(spis *head); // функция просмотра списка
void free_spis(spis *head); //функция освобождения памяти

main(){
       spis *head; // адрес головы списка
       system ("CLS");
       head=create();
       list(head);
       free_spis(head);
       getch(); 
} 

spis* create(){
      spis *p; //Указатель на текущую структуру
      spis *t; //Указатель на "рабочую" структуру
      spis *pred; //Указатель на предыдущую структуру
      spis *h; //Указатель на первую структуру
      h=pred=t=new spis; //выделение памяти для первой структуры
      printf("Type the last name and marks of student:\n"); 
      scanf("%s", pred->fam);
      for (int i=0; i<N; i++) scanf("%d", pred->mark+i);
      do { 
           p=new spis;
           printf("Type the last name and marks of student:\n");
           scanf("%s", p->fam);
           for (int i=0; i<N; i++) scanf("%d", p->mark+i);
           //Пробный кусок
           while (1) { //Сравнение элементов списка от начала до момента, когда элементы списка становятся больше текущего
                 t=t->next;
                 if (t==t->next) { break; }
                 if (strcmp(t->fam,p->fam)<0) { pred=t; printf("check");}
           }
           p->next=t; //Ссылка из текущей структуры на последующую
           pred->next=p; //Ссылка из предыдущей структуры на текущую
           t=h; //Приведение "рабочего" указателя к началу списка
           //Пробный кусок
           printf("Continue? y/n "); 
      } while (getch()=='y');
      p->next=NULL; 
      return h; //Возврат головы списка
}

void list(spis *head){  
     spis *p;
     p=head;
     printf("\nList of students:");
     while (p!=NULL) { // пока не конец списка
        printf("\n%s",p->fam);
        for (int i=0; i<N; i++) printf("%d", p->mark[i]);
        p=p->next; // продвижение по списку 
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

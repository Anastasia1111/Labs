#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef struct st
     { char data[20];
       struct st *next;} spis;
spis * create(void); //функция создания списка
void list(spis *head); // функция просмотра списка
void free_spis(spis *head); //функция освобождения памяти
main()
{ system ("CLS");
  spis *head; // адрес головы списка
  head= create();
   list (head);
   free_spis (head);
   getch(); 
} 
 spis * create(void)
{  spis *p, *pred, *h; 
   // pred - указатель на предыдущую структуру
  // h- указатель на первую структуру
   h=pred=new spis; //выделение памяти для первой структуры
   printf("  fam: "); scanf("%s", pred->data);
   do { p=new spis;
        printf("\n  fam: "); scanf("%s", p->data);
        pred->next=p; //ссылка из предыдущей на текущую
        pred=p; // сохранение адреса текущей 
        printf(" закончить? y/n  ");
       } while (getch()=='y');
   p->next=NULL; 
   return h;
}
void list(spis *head)
{  spis *p;
   p=head;
   while (p!=NULL) // пока не конец списка
   {  printf("\n  fio: %s",p->data);
      p=p->next; // продвижение по списку 
   }
}   
 void free_spis(spis *head)
 { spis *p,*q;
   q=p=head;
   while (p!=NULL)
   {
     p=q->next;
     delete q; 
     q=p;
   }   
  head=NULL;
 }

#include "bible9.cpp"

const int N=640; // ширина
const int M=360; // высота
const int OX=50;
const int OY=M-50;

void StackToQueue (tLE *&List, Queue *Q) 
{
     Q->tail->next=List;
     Q->tail=List;
     List=List->next;
}

int Split(tLE *s, tLE *&a, tLE *&b)
{
     a=s; b=s->next; int n=0;
     tLE *k=s; tLE *p=s->next;
     while (p) {
           n++;
           k->next=p->next;
           k=p;
           p=p->next;
     }
     return n;
}

void Merge(tLE *&a, int q, tLE *&b, int r, Queue *c) {
     while (q&&r) {
           if (a->data<=b->data) {                
              StackToQueue (a,c);
              q--;
           } else {
              StackToQueue (b,c);
              r--;
           }
     } 
     while (q) {
           StackToQueue (a,c);
           q--;
     }
     while (r) {
           StackToQueue (b,c);
           r--;
     }
}

void MergeMC(tLE *&a, int q, tLE *&b, int r, Queue *c, int &T) {
     while (q&&r) {
           if (a->data<=b->data) {
              T+=2;                
              StackToQueue (a,c);
              q--;
           } else {
              T+=2;
              StackToQueue (b,c);
              r--;
           }
     } 
     while (q) {
           T++;
           StackToQueue (a,c);
           q--;
     }
     while (r) {
           T++;
           StackToQueue (b,c);
           r--;
     }
}

void MergeSort(tLE *&s, int n) 
{
     tLE *a,*b;  // Рабочие списки
     Queue *c[2];  // Массив из 2-х очередей
     int p=1;  // Предполагаемый размер серии
     int q,r;  // Фактический размер серии в списках а и b
     int m;  // Текущее количество элементов в списках а и b
     int i;  // Номер активной очереди
     int T=n;  // Трудоемкость (при разделении ниже получится именно такое значение трудоемкости)
     Split(s,a,b);
     c[0]=new Queue;
     c[1]=new Queue;
     if (c[0]==NULL||c[1]==NULL){
        printf(" ERROR ");
     }
     while (p<n) {
           c[0]->head=c[1]->head=NULL;
           c[0]->tail=(tLE*)&c[0]->head;
           c[1]->tail=(tLE*)&c[1]->head;
           i=0; m=n;
           while (m>0) {
                 if (m>=p) q=p;
                 else q=m;
                 m=m-q;
                 if (m>=p) r=p;
                 else r=m;
                 m=m-r;
                 //Merge(a,q,b,r,c[i]);
                 MergeMC(a,q,b,r,c[i],T);
                 i=1-i;
           }
           a=c[0]->head; b=c[1]->head; 
           p*=2;
     }
     c[0]->tail->next=NULL;
     s=c[0]->head;
     printf("\nPractical M + C:\nT=%d",T);
}

void Graph() {
     int i,y;
   initwindow(N,M); 
   moveto(0,OY);       
   lineto(N,OY);       
   moveto(OX,0);
   lineto(OX,M);
   moveto(OX,OY); 
   outtextxy (OX+25, OY+10, "25" );
   outtextxy (OX+50, OY+10, "50" );
   outtextxy (OX+100, OY+10, "100" );
   outtextxy (OX+200, OY+10, "200" );
   outtextxy (OX+300, OY+10, "300" );
   outtextxy (OX+400, OY+10, "400" );
   outtextxy (OX+500, OY+10, "500" );
   outtextxy (OX+600, OY+10, "600" );
   outtextxy (OX-40, OY-200, "8000" );
   outtextxy (OX-40, OY-150, "6000" );
   outtextxy (OX-40, OY-100, "4000" );
   outtextxy (OX-40, OY-50, "2000" );
   outtextxy (N-10, OY+10, "n" );
   outtextxy (OX-30, 10, "C(n)" );
   moveto(OX,OY);
   setcolor(3); //бирюзовый
   for (i=OX; i<N; i++) { //Цикл для метода прямого слияния
       y=(int)(2*(i-OX)*log(i-OX)/log(2)+(i-OX));
       lineto(i,(OY-y/40));
   }
   moveto(OX,OY);
   setcolor(5); //фиолетовый
   for (i=OX; i<N; i++) { //Цикл для метода Хоара
       y=(int)((i-OX+1)*log(i-OX+1)/log(2)-(i-OX+1)+(3/2)*(i-OX+1)*log(i-OX+1)/log(2)-(i-OX+1));
       lineto(i,(OY-y/40));
   }
   moveto(OX,OY);
   setcolor(1); //синий
   for (i=OX; i<N; i++) { //Цикл для "кучи"
       y=(int)(3*(i-OX)*log(i-OX)/log(2)+7.5*(i-OX)-2); 
       lineto(i,(OY-y/40));
   }
   system("Pause");
   closegraph();
}

main() {
       int n, i;
       printf("Razmer spiska: ");
       scanf("%d",&n);
       tLE *stack=new tLE;
       if (stack==NULL){
           printf(" ERROR ");
           return 1;
       }
       stack->next=NULL;
       //StackFillInc(stack,n);
       //StackFillDec(stack,n);
       StackFillRand(stack,n);
       OutputList(stack,n);
       MergeSort(stack,n);
       OutputList(stack,n);
       Graph();
       delete stack;
       system("Pause");
       return 0;
}

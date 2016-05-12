#include "bible6.cpp"

short N=256; // –азмер базы
struct tel {char surname[15]; char name[15]; char phone[12]; char adress[30]; bool flag;} t1; // ќбъ€вление "рабочей" структуры

void input(FILE *, tel *); // создание справочника
void print(tel *); // просмотр справочника
void addfile(FILE *, tel *); // добавление записи в файл
void addbase(FILE *, tel *); // добавление записи в справочник
void search(tel *, short *, short *, short *, short *); // поиск в справочнике
void index(tel *, short *, short *, short *, short *); // обща€ функци€ дл€ создани€ индексов и работы с ними
void indexsort(tel *, short *, short *, short *, short *); // сортировка индексов
void dataprint(tel *, short *, short *, short *, short *); // вывод отсортированного справочника
void delentry(tel *, short *); // "удаление" лишних записей из справочника

main(){ 
        char c,flagMAKE=1,flagINDEX=0,flagADEL=0;
        short iSUR[N],iNAM[N],iTEL[N],iADR[N];
        FILE *tf;
        tel base[N];
        while (1){ 
              system("CLS");
              puts("  1 - MAKE DATABASE  "); //ѕересоздание базы с нул€
              puts("  2 - PRINT DATABASE (UNSORTED)  "); //¬ывод базы (неотсортированной)
              puts("  3 - MAKE INDEX  "); //—оздание индексов дл€ сортировки
              puts("  4 - PRINT DATABASE (SORTED)  "); //¬ывод базы из оперативной пам€ти (отсортированной по индексу)
              puts("  5 - FIND ENTRY  "); //ѕоиск записей по введенному ключу
              puts("  6 - ADD ENTRY  "); //ƒобавление записей в базу (в 2 этапа)
              puts("  7 - DELETE ENTRY (FOR EXPERIENCED USERS)  "); //—окрытие ("удаление") записей из базы
              puts("  0 - EXIT  ");
              if (flagMAKE) puts("WARNING!!! \nFor correct working of programm you need make database and index \nWARNING!!!\n");
              if (flagINDEX) puts("WARNING!!! \nFor correct working of programm you need make an index \nWARNING!!!\n");
              if (flagADEL) puts("WARNING!!! \nFor correct working of programm you need remake an index \nWARNING!!!\n");
              c=getch();
              switch(c){ 
                         case '1': input(tf,base); flagMAKE=0; flagINDEX=1; break;
                         case '2': print(base); break;
                         case '3': index(base,iSUR,iNAM,iTEL,iADR); indexsort(base,iSUR,iNAM,iTEL,iADR); flagINDEX=0; flagADEL=0; break;
                         case '4': dataprint(base,iSUR,iNAM,iTEL,iADR); break;
                         case '5': search(base,iSUR,iNAM,iTEL,iADR); break;
                         case '6': addfile(tf,base); flagADEL=1; break;
                         case '7': delentry(base,iSUR); flagADEL=1; break; //¬ силу того, что в задании дано написание процедуры, а не функции, флаг будет подниматьс€, даже если ни одной записи удалено не было
                         case '0': return 0;
                         default : puts("WRONG CASE");
              }
        }
}

void input(FILE *tf, tel *base)
{ 
     int i;
     system("CLS");
     tf=fopen("database.dat","rb"); // открытие бинарного файла дл€ чтени€
     i=0;
     fread(&t1,sizeof(t1),1,tf); // чтение из файла одной структуры t1
     while (!feof(tf)) { 
           strcpy(base[i].surname, t1.surname);
           strcpy(base[i].name, t1.name);
           strcpy(base[i].phone, t1.phone);
           strcpy(base[i].adress, t1.adress);
           base[i].flag=1;
           fread(&t1,sizeof(t1),1,tf);
           i++;
     }
     for(i=i; i<N; i++) base[i].flag=0;
}

void print(tel *base) 
{
     int i,j;
     system("CLS");
     int k=0;
     for (i=0; i<N; i++) 
         if(base[i].flag) {
             printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",k,base[i].surname,base[i].name,base[i].phone,base[i].adress);
             k++;
         }
     getch();
}

void dataprint(tel *base, short *indxS, short *indxN, short *indxT, short *indxA)
{
     char c;
     int i,j;
     while (1) {
           system("CLS");
           puts("  CHOOSE YOUR INDEX:  ");
           puts("  1 - Surname  ");
           puts("  2 - Name  ");
           puts("  3 - Phone number  ");
           puts("  4 - Adress  "); 
           puts("  0 - EXIT  ");
           c=getch();
           int k=0;
           switch(c){ 
                      case '1': 
                           for (i=0; i<N; i++) 
                               if(base[indxS[i]].flag) {
                                   printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",k,base[indxS[i]].surname,base[indxS[i]].name,base[indxS[i]].phone,base[indxS[i]].adress);
                                   k++;
                               }
                           getch();
                           break;
                      case '2': 
                           for (i=0; i<N; i++) 
                               if(base[indxN[i]].flag) {
                                   printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",k,base[indxN[i]].surname,base[indxN[i]].name,base[indxN[i]].phone,base[indxN[i]].adress);
                                   k++;
                               }
                           getch();
                           break;
                      case '3': 
                           for (i=0; i<N; i++) 
                               if(base[indxT[i]].flag) {
                                   printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",k,base[indxT[i]].surname,base[indxT[i]].name,base[indxT[i]].phone,base[indxT[i]].adress);
                                   k++;
                               }
                           getch();
                           break;
                      case '4': 
                           for (i=0; i<N; i++) 
                               if(base[indxA[i]].flag) {
                                   printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",k,base[indxA[i]].surname,base[indxA[i]].name,base[indxA[i]].phone,base[indxA[i]].adress);
                                   k++;
                               }
                           getch();
                           break;
                      case '0': return;
                      default : puts("WRONG CASE");
           }
     }
}

void addbase(FILE *tf, tel *base) 
{ 
     int i;
     system("CLS");
     tf=fopen("database.dat","rb"); // открытие бинарного файла дл€ чтени€
     i=0;
     fread(&t1,sizeof(t1),1,tf); // чтение из файла одной структуры t1
     while (!feof(tf)) { 
           if (!base[i].flag) { //“ак как в задании ничего не сказано о восстановлении данных, то новые записи встанут на место отсутствующих/удаленных
               strcpy(base[i].surname, t1.surname);
               strcpy(base[i].name, t1.name);
               strcpy(base[i].phone, t1.phone);
               strcpy(base[i].adress, t1.adress);
               base[i].flag=1;
           }
           fread(&t1,sizeof(t1),1,tf);
           i++;
     }
}

void addfile(FILE *tf, tel *base)
{ 
     char ch;
     tf=fopen("database.dat","ab"); // открытие бинарного файла дл€ добавлени€
     system("CLS");
     printf("\n SCANING DATA: \n");
     do { 
          printf("\n Surname: "); scanf("%s",&t1.surname);
          printf(" Name: "); scanf("%s",&t1.name);
          printf(" Phone number: "); scanf("%s",&t1.phone);
          printf(" Adress: "); scanf("%s",&t1.adress);
          fwrite(&t1,sizeof(t1),1,tf); // запись в файл одной структуры t1
          printf("\n END?  y/n  ");
          ch=getch();
     } while (ch != 'y');
     fclose(tf);
     addbase(tf,base);
}

void search(tel *base, short *indxS, short *indxN, short *indxT, short *indxA)
{
     int m,i,k,R,L=0;
     char c,key[30];
     R=0;
     while (base[indxS[R]].flag) R++; //ѕробный пробег по циклу дл€ определени€ количества активных элементов
     system("CLS");
     puts("TYPE A KEY:");
     gets(key);
     puts("  This is...  ");
     puts("  1 - ...a surname  ");
     puts("  2 - ...a name  ");
     puts("  3 - ...a phone number  ");
     puts("  4 - ...an adress  "); 
     puts("  0 - EXIT  ");
     c=getch();
     switch(c){ 
                case '1': 
                     while (L<R) {
                           m=(L+R)/2;
                           if (strcmp(base[indxS[m]].surname,key)<0) L=m+1;
                           else R=m;
                     }
                     if (strcmp(base[indxS[m]].surname,key)==0) k=1;
                           else k=0;
                     i=R;
                     while (strcmp(base[indxS[i]].surname,key)==0) {
                           printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",i,base[indxS[i]].surname,base[indxS[i]].name,base[indxS[i]].phone,base[indxS[i]].adress); 
                           i++; 
                     }
                     break;
                case '2': 
                     while (L<R) {
                           m=(L+R)/2;
                           if (strcmp(base[indxN[m]].name,key)<0) L=m+1;
                           else R=m;
                     }
                     if (strcmp(base[indxN[m]].name,key)==0) k=1;
                           else k=0;
                     i=R;
                     while (strcmp(base[indxN[i]].name,key)==0) {
                           printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",i,base[indxN[i]].surname,base[indxN[i]].name,base[indxS[i]].phone,base[indxN[i]].adress); 
                           i++; 
                     }
                     break;
                case '3': 
                     while (L<R) {
                           m=(L+R)/2;
                           if (strcmp(base[indxT[m]].phone,key)<0) L=m+1;
                           else R=m;
                     }
                     if (strcmp(base[indxT[m]].phone,key)==0) k=1;
                           else k=0;
                     i=R;
                     while (strcmp(base[indxT[i]].phone,key)==0) {
                           printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",i,base[indxT[i]].surname,base[indxT[i]].name,base[indxT[i]].phone,base[indxT[i]].adress); 
                           i++; 
                     }
                     break;
                case '4': 
                     while (L<R) {
                           m=(L+R)/2;
                           if (strcmp(base[indxA[m]].adress,key)<0) L=m+1;
                           else R=m;
                     }
                     if (strcmp(base[indxA[m]].adress,key)==0) k=1;
                           else k=0;
                     i=R;
                     while (strcmp(base[indxA[i]].adress,key)==0) {
                           printf("\n%2d)Full name: %s %s \n   Phone number: %s \n   Adress: %s",i,base[indxA[i]].surname,base[indxA[i]].name,base[indxA[i]].phone,base[indxA[i]].adress); 
                           i++; 
                     }
                     break;
                case '0': return;
                default : puts("WRONG CASE");
     }
     if (!k) printf("Element, that you are looking for, doesn't exist!!!\n");
     getch();
}

void index(tel *base, short *indxS, short *indxN, short *indxT, short *indxA) {
     int i;
     for (i=0; i<N; i++) {
         indxS[i]=i;
         indxN[i]=i;
         indxT[i]=i;
         indxA[i]=i;
     }
}

void indexsort(tel *base, short *indxS, short *indxN, short *indxT, short *indxA){
     // —ортировка происходит методом выбора
      int i,j,k,t;
      for (i=0; i<N-1; i++) {
          k=i;
          for (j=i+1; j<N; j++) {
              if (base[indxS[j]].flag) {
                 if (strcmp(base[indxS[j]].surname,base[indxS[k]].surname)<0) k=j;
              }
          }
          if (i<k) { t=indxS[k]; indxS[k]=indxS[i]; indxS[i]=t; }
      }
      for (i=0; i<N-1; i++) {
          k=i;
          for (j=i+1; j<N; j++) {
              if (base[indxN[j]].flag) {
                 if (strcmp(base[indxN[j]].name,base[indxN[k]].name)<0) k=j;
              }
          }
          if (i<k) { t=indxN[k]; indxN[k]=indxN[i]; indxN[i]=t; }
      }
      for (i=0; i<N-1; i++) {
          k=i;
          for (j=i+1; j<N; j++) {
              if (base[indxT[j]].flag) {
                 if (strcmp(base[indxT[j]].phone,base[indxT[k]].phone)<0) k=j;
              }
          }
          if (i<k) { t=indxT[k]; indxT[k]=indxT[i]; indxT[i]=t; }
      }
      for (i=0; i<N-1; i++) {
          k=i;
          for (j=i+1; j<N; j++) {
              if (base[indxA[j]].flag) {
                 if (strcmp(base[indxA[j]].adress,base[indxA[k]].adress)<0) k=j;
              }
          }
          if (i<k) { t=indxA[k]; indxA[k]=indxA[i]; indxA[i]=t; }
      }
}

void delentry(tel *base, short *indxS) 
{
     int m,i,k,R,L=0;
     char surname[15], name[15], phone[12], adress[30];
     R=0;
     while (base[indxS[R]].flag) R++; //ѕробный пробег по циклу дл€ определени€ количества активных элементов
     system("CLS");
     printf("\n DATA FOR DELETION: \n"); //„тобы случайно не удалить лишнего, запрашиваем все пол€
     printf("\n Surname: "); gets(surname);
     printf(" Name: "); gets(name);
     printf(" Phone number: "); gets(phone);
     printf(" Adress: "); gets(adress);
     while (L<R) { //ѕутем двоичного поиска находим по одному из полей что-то похожее
           m=(L+R)/2;
           if (strcmp(base[indxS[m]].surname,surname)<0) L=m+1;
           else R=m;
     }
     k=0;
     i=R;
     while (strcmp(base[indxS[i]].surname,surname)==0) {
           if ((strcmp(base[indxS[i]].name,name)==0)&&(strcmp(base[indxS[i]].phone,phone)==0)&&(strcmp(base[indxS[i]].adress,adress)==0)) { base[indxS[i]].flag=0; k=1; }
           i++; 
     }
     if (!k) printf("Element, that you are looking for, doesn't exist!!!\n");
     getch();
}

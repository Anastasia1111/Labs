#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 80; // количество элементов в строке
const int CS = 24; //  оличество строк в исходном массиве
typedef char rown[N]; //rown - новый тип: массив (строка) из n целых чисел

struct tLE {
	tLE *next;
	char data[80];
};

struct queue {
	tLE *head;
	tLE *tail;
	bool filled;
};

int Hash(char* str, int m) {
	int len = strlen(str);
	int h = 0;
	for (int i = 0; i <= len; i++)
		h = (h*256 + str[i]) % m;
	return h;
}

bool Hash_Insert(char* str, rown* T, int m) {
	int i = 0, d = 1;
	while (i <= m) {
		int j = Hash(str, m) + i;
		if (T[j][0] == '\0') {
			strcpy(T[j], str);
			return false;
		}
		i += d;
		/*d += 2;*/
	}
	return true;
}

int Hash_Search(char* str, rown* T, int m) {
	int i = 0, d = 1;
	while (i <= m) {
		int j = Hash(str, m) + i;
		if (T[j][0] == '\0') 
            break;
		if (strcmp(T[j],str) == 0) {
			return j;
		}
		i += d;
		/*d += 2;*/
	}
	return m+1;
}

void AddToList(char* str, queue* Q, int m)
{
	tLE *p;
	p = new tLE;
	strcpy(p->data, str);
	p->next = NULL;
	int h = Hash(str, m);
    if (!Q[h].filled) {
        Q[h].head=Q[h].tail=p;
        Q[h].filled=true;
    } else {
        Q[h].tail->next=p;
        Q[h].tail=p;
    }
}

int Hash_list_Search(char* str, queue* Q, int m)
{
	tLE *p;
	int i;
	int h = Hash(str, m);
	p = Q[h].head;
	while (p) {
		if (strcmp(p->data,str) == 0) return h;
		if (p->next) p = p->next;
		else break;
	}
	return m+1;
}

void Output_tables(queue* table1, rown* table2, int m) {
	int i;
	tLE *p;
	printf("\nMetod pryamogo svyazivaniya:\n");
	for (i = 0; i < m; i++) {
		p = table1[i].head;
		printf("%d:",i);
		while (p) {
			printf(" [%s]", p->data);
			if (p->next) p = p->next;
			else break;
		}
		printf("\n");
	}
	printf("\nMetod otkritoy adresatzii [Original'noe znachenie hash]:\n");
	for (i = 0; i < m; i++) {
        int h = Hash(table2[i],m);
		printf("%d: %s [%d]\n", i, table2[i], h);
    }
}

main() {
       int m, i, h;
	   queue *Hashtable1;
	   rown *Hashtable2;
	   char *str[CS] = { 
		   "Rzhavye kol'tsa",
		   "na uzkoy ruke.",
		   "CHernaya ptitsa",
		   "krichit vdaleke.",
		   "CHto - to zabyto,",
		   "kto - to propal.",
		   "V temnom uglu",
		   "svoyu dushu iskal.",
		   "Mednye puty",
		   "na gryaznoy kisti.",
		   "Alaya tsaplya",
		   "sbilas' s puti.",
		   "Mrachnye mysli",
		   "terzali ego.",
		   "V gryaznom kreste",
		   "net nikogo.",
		   "Ryzhie tsepi",
		   "na uzkom zapyast'e.",
		   "Belaya ptaha -",
		   "predvestnik nenast'ya.",
		   "Mrak prilaskal",
		   "povesiv petlyu.",
		   "Bol'she net Very",
		   "ni k tebe, ni k komu."
	   }; // ¬ качестве строк выбраны случайные стихи из интернета
	   char key[N];
	   
       printf("\nRazmer hash-tablitzi: ");
       scanf("%d",&m);

       Hashtable1 = new queue [m];
       if (Hashtable1==NULL){
           printf(" ERROR ");
           return 1;
       }
       for (i = 0; i < m; i++) {
           Hashtable1[i].head = NULL;
           Hashtable1[i].filled=false;
       }

	   Hashtable2 = new rown[m];
	   for (i = 0; i < m; i++)
		   strcpy(Hashtable2[i],"\0");

	   for (i = 0; i < CS; i++) {
		   AddToList(str[i], Hashtable1, m);
		   bool flag = Hash_Insert(str[i], Hashtable2, m);
		   if (flag) {
			   printf("\nTablitza perepolnena! Vibirete drugoe znachenie M!\n");
			   system("Pause");
			   return 0;
		   }
	   }

	   Output_tables(Hashtable1, Hashtable2, m);

       printf("\nVvedite kluch: ");
       getchar(); // —читывет перевод строки при вводе m
       gets(key);
       
       printf("V pervoy tablitze: ");
       int loc = Hash_list_Search(key, Hashtable1, m);
       if (loc<m)
          printf("%d spisok\n",loc);
       else 
          printf("ne nayden\n");
       
       printf("Vo vtoroy tablitze: ");
       loc = Hash_Search(key, Hashtable2, m);
       if (loc<m)
          printf("%d element\n",loc);
       else 
          printf("ne nayden\n");

       delete Hashtable1;
	   delete Hashtable2;
       Hashtable1 = NULL;
	   Hashtable2 = NULL;
       system("Pause");
       return 0;
}

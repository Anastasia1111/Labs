//#include "bible4.cpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 80; // количество элементов в строке
const int CS = 24; // Количество строк в исходном массиве
typedef char rown[N]; //rown - новый тип: массив (строка) из n целых чисел

struct tLE {
	tLE *next;
	char data[80];
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
		i++;
		/*i += d;
		d += 2;*/
	}
	return true;
}

void AddToList(char* str, tLE *head)
{
	tLE *p;
	p = new tLE;
	strcpy(p->data, str);
	p->next = head;
	head = p;
}

void Output_tables(tLE* table1, rown* table2, int m) {
	int i;
	tLE *p;
	printf("\nMetod pryamogo svyazivaniya:\n");
	for (i = 0; i < m; i++) {
		p = table1+i;
		printf("%d: ",i);
		while (p) {
			printf("%s ", p->data);
			p = p->next;
		}
		printf("\n");
	}
	printf("\nMetod otkritoy adresatzii:\n");
	for (i = 0; i < m; i++)
		printf("%d: %s \n", i, table2[i]);
}

main() {
       int m, i, h, key;
	   tLE *Hashtable1;
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
	   }; // В качестве строк выбраны случайные стихи из интернета

       printf("\nRazmer hash-tablitzi: ");
       scanf("%d",&m);

       Hashtable1 = new tLE [m];
       if (Hashtable1==NULL){
           printf(" ERROR ");
           return 1;
       }
	   for (i = 0; i < m; i++)
		   Hashtable1[i].next = NULL;

	   Hashtable2 = new rown[m];
	   for (i = 0; i < m; i++)
		   strcpy(Hashtable2[i],"\0");

	   for (i = 0; i < CS; i++) {
           h = Hash(str[i], m);
		   AddToList(str[i], Hashtable1+h);
		   bool flag = Hash_Insert(str[i], Hashtable2, m);
		   if (flag) {
			   printf("\nTablitza perepolnena! Vibirete drugoe znachenie M!\n");
			   system("Pause");
			   return 0;
		   }
	   }

	   Output_tables(Hashtable1, Hashtable2, m);

       printf("\nType the key: ");
       scanf("%d",&key);

       delete Hashtable1;
	   delete Hashtable2;
       Hashtable1 = NULL;
	   Hashtable2 = NULL;
       system("Pause");
       return 0;
}

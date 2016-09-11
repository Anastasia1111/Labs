#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=80; // Величина строки

main (){
    char wrd[N], out[N], *p;
    int i;
    puts ("Vvedite slova cherez probel:");
	gets (wrd);
	char * tmp = strtok (wrd," ");
	while (tmp != NULL) {
        for (i=48; i<=57; i++) {
		    p=strchr(tmp,i);
		    if (p!=NULL) break;
		}
		if (p==NULL) {strcat(out,tmp); strcat(out," ");}
        tmp = strtok (NULL, " ");
    }
    puts ("Obrabotannaya stroka:");
    puts (out); 
	getch();
}

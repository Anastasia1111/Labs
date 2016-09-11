#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=80; // Величина строки
const int NP=10; // Величина приставки

main (){
    char wrd[N], prfx[NP], out[N], *pp, *ppp;
    int flag=1, n;
    puts ("Vvedite slova cherez probel:");
	gets (wrd);
	puts ("Vvedite pristavku:");
	gets (prfx);
	n=strlen(prfx);
	char * tmp = strtok (wrd," ");
	while (tmp != NULL) {
        if (strncmp(tmp,prfx,n)==0) {strcat(out,tmp); strcat(out," ");}
        tmp = strtok (NULL, " ");
    }
//	pp=wrd-1;
//	while(flag) {
//		ppp=pp+1;
//    	pp=strchr(pp+1, ' ');
//    	if (pp!=NULL) {
//    		if (strncmp(ppp,prfx,n)==0) strncat(out,ppp,pp-wrd);
//        }   
//        else {
//            if (strncmp(ppp,prfx,n)==0) strncat(out,ppp,pp-wrd);
//            flag=0;
//        }
//    }
    puts ("Iskomie slova:");
    puts (out); 
	getch();
}
        

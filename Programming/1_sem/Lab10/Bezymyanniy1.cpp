#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=20;

main (){
    char wrd[80], prfx[10], out[80], *pp, *ps;
    int i, j, flag=1;
    puts ("Vvedite slova cherez probel:");
	gets (wrd);
	puts ("Vvedite pristavku:");
	gets (prfx);
	while(flag) {
    	pp=strchr(wrd, ' ');
    	if (pp!=NULL) {
             ps=strstr(wrd, prfx);
             if (ps==wrd) strncat(out,wrd,pp-wrd);
             for (i=0; i<=pp-wrd; i++)
                 for (j=0; i<80; j++) wrd[j]=wrd[j+1];
        }
        else {
             ps=strstr(wrd, prfx);
             if (ps!=NULL) {
                 strcat (out,wrd); 
             }
                 flag=0;
        }
    }
    puts ("Iskomie slova:");
    puts (out); 
	getch();
}
        

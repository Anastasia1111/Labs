#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=80; // Величина строки

main (){
    char wrd[N], slv[N][N/2-1], out[N]="";
    int i=0, j, n, k, flag;
    puts ("Vvedite slova cherez probel:");
	gets (wrd);
	char * tmp = strtok (wrd," ");
	while (tmp != NULL) {
        n=strlen(tmp);
        for (j=0; j<n; j++) slv[i][j]=tmp[j];
        slv[i][j]=0;
        i++;
        tmp = strtok (NULL, " ");
    }
    k=i;
    for (i=0; i<k; i++) {
    	flag=0;
        for (j=i+1; j<k; j++) {
        	if (strcmp(slv[i],slv[j])==0) { slv[j][0]=0; flag=1; }
		}
		if (flag) { strcat(out,slv[i]); strcat(out," "); }
	}	
    puts ("Povtotyaushiesya slova:");
    puts (out); 
	getch();
}

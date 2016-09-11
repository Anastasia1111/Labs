#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=80; // Величина строки

main (){
    char fam[N], sps[N][N/2+1], out[N];
    int i=0, j, n, k, tmp, min;
    puts ("Vvedite familii cherez zapyatuiy:");
	gets (fam);
	char * tok = strtok (fam,",");
	while (tok != NULL) {
        n=strlen(tok);
        for (j=0; j<n; j++) sps[i][j]=tok[j];
        sps[i][j]=0;
        k++; i++;
        tok = strtok (NULL, ",");
    }
    for (i=0; i<k; i++) {
    	puts(sps[i]);
	}
    for (i=0; i<k-1; i++) {
	    min=i;
        for (j=i+1; j<k; j++)
        	if (strcmp(sps[min],sps[j])>0) min=j;
        for (j=0,n=0; j<N; j++) {
        	tmp=sps[i][j]; sps[i][j]=sps[min][j]; sps[min][j]=tmp;
        	if (sps[i][j]==0 || sps[min][j]==0) n++;
        	if (n==2) break;
		}
	}	
    puts ("Otsortirovanniy spisok:");
    for (i=0; i<k; i++) {
    	puts(sps[i]);
	}
	getch();
}

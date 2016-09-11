#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
const int N=80; // Величина строки

main (){
    char in[N], out[2*N];
    int i, j;
    puts ("Ishodnaya stroka:");
	gets (in);
	for (i=j=0; in[i]; i++) {
		out[j++]=in[i];
		if (in[i]==','|| in[i]=='.' || in[i]=='!' || in[i]==':' || in[i]==';' || in[i]=='?') out[j++]=' ';
	}
	out[j]=0;
    puts ("Obrabotannaya stroka:");
    puts (out); 
	getch();
}
        

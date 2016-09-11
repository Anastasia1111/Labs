#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

char* prog = " \n\
#include <stdlib.h> \n\
#include <stdio.h> \n\
#include <conio.h> \n\
#include <math.h> \n\
#include <string.h> \n\
const int N=80; // Величина строки \n\
 \n\
main (){ \n\
    char wrd[N], slv[N][N/2-1], out[N]=; \n\
    int i=0, j, n, k, flag; \n\
    puts (); \n\
	gets (wrd);  \n\
	char * tmp = strtok (wrd,); \n\
	while (tmp != NULL) { \n\
        n=strlen(tmp); \n\
        for (j=0; j<n; j++) slv[i][j]=tmp[j]; \n\
        slv[i][j]=0; \n\
        i++; \n\
        tmp = strtok (NULL, ); \n\
    } \n\
    k=i; \n\
    for (i=0; i<k; i++) { \n\
    	flag=0; \n\
        for (j=i+1; j<k; j++) { \n\
        	if (strcmp(slv[i],slv[j])==0) { slv[j][0]=0; flag=1; } \n\
		} \n\
		if (flag) { strcat(out,slv[i]); strcat(out,); } \n\
	} \n\
    puts (); \n\
    puts (out);  \n\
	getch(); \n\
}";

char include[]="#include";
char ch[]="char";
char fr[]="for";
char iif[]="if";
char intr[]="int";
char cnst[]="const";
char whil[]="while";
char get[]="gets";
char put[]="puts";

struct tree{
       int count;
    char data[20];
    tree *l;
    tree *r;
};

void print_struct (tree *m){	
	if ( !m ) return;
	print_struct (m->l);
	printf("%s ",m->data);
	print_struct (m->r);
}

void ClearTree(tree *S){
    if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    free (S);
}

void WordTrMaking (char* data, tree *&head){
   if (head == NULL){    
        head = new tree;
        strcpy(head->data,data);
        head->count = 1;
        head->l = head->r = NULL;
    }
    if (strcmp(data,head->data)>0) {WordTrMaking (data, head->r);}
    else if (strcmp(data,head->data)<0) {WordTrMaking (data, head->l);}
        else if (strcmp(data,head->data)==0) {
             head->count++;
             return;
             }
}

main(){
	srand (time(NULL));
    int n;
    tree *h;
    char slv[20];
    char * tmp = strtok (prog," ");
    printf("CHECK1");
	while (tmp != NULL) {
          printf("CHECK2");
        n=strlen(tmp);
        for (int j=0; j<n; j++) slv[j]=tmp[j];
        if (strcmp(slv,include)==0||
            strcmp(slv,ch)==0||
            strcmp(slv,fr)==0||
            strcmp(slv,iif)==0||
            strcmp(slv,cnst)==0||
            strcmp(slv,get)==0||
            strcmp(slv,put)==0||
            strcmp(slv,whil)==0||
            strcmp(slv,intr)==0  )
                                 WordTrMaking (slv, h);
        printf("CHECK3");
        strcpy(slv,"");
        tmp = strtok (NULL, " ");
    }
    printf("\nTree was maden! \n");
    print_struct (h);
    
    h = NULL; 
    system ("pause");
}

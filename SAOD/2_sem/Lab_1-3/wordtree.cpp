#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

char prog[] = " \n\
 #include <stdlib.h> \n\
 #include <stdio.h> \n\
 #include <conio.h> \n\
 #include <math.h> \n\
 #include <string.h> \n\
 const int N=80; \n\
 \n\
 main (){ \n\
 char wrd[N], slv[N][N/2-1], out[N]=; \n\
 int i=0, j, n, k, flag; \n\
 puts (); \n\
 gets (wrd);  \n\
 char * tmp = strtok (wrd,); \n\
 while (tmp != NULL) { \n\
 n = strlen(tmp); \n\
 for (j=0; j<n; j++) slv[i][j]=tmp[j]; \n\
 slv[i][j]=0; \n\
 i++; \n\
 tmp = strtok (NULL, ); \n\
 } \n\
 k=i; \n\
 for (i=0; i<k; i++) { \n\
 flag=0; \n\
 for (j=i+1; j<k; j++) { \n\
 if (strcmp (slv[i],slv[j])==0) { slv[j][0]=0; flag=1; } \n\
 } \n\
 if (flag) { strcat (out,slv[i]); strcat (out,); } \n\
 } \n\
 puts (); \n\
 puts (out);  \n\
 getch (); \n\
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
	printf("%s[%d]\n", m->data, m->count);
	print_struct (m->r);
}

void WordTrMaking (char* data, tree *&head){
   if (head == NULL){   
        head = new tree;
        strcpy(head->data,data);
        head->count = 0;
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
    tree *h = NULL;
    char slv[20];
    char * tmp = strtok (prog," ,.-;:()");
	while (tmp != NULL) {
        if (strcmp(tmp,include)==0||
            strcmp(tmp,ch)==0||
            strcmp(tmp,fr)==0||
            strcmp(tmp,iif)==0||
            strcmp(tmp,cnst)==0||
            strcmp(tmp,get)==0||
            strcmp(tmp,put)==0||
            strcmp(tmp,whil)==0||
            strcmp(tmp,intr)==0  )
                                 WordTrMaking (tmp, h);
        strcpy(slv,"");
        tmp = strtok (NULL, " ");
    }
    printf("Tree was maden! \n");
    print_struct (h);
    
    h = NULL; 
    system ("pause");
}

#include <cstdio>
#include <cstdlib>
#include <cstring>

const short N=5; //Количество комнат

main() {
       struct data {short num; short plosh; char fac[10]; short lnum;} kom[N];
       short i, j, plosh=0, knum=0, snum=0, n=0, flag=1;
       char facult[N][10];
       facult[0][0]='/0';
       printf("Type the information about rooms:\n");
       for (i=0; i<N; i++) {
           printf("%d)Number of room, size of room, faculty of students, number of students:\n",i);
           scanf("%d %d %s %d",&kom[i].num,&kom[i].plosh,&kom[i].fac,&kom[i].lnum);
           for (j=0; j<=n; j++) {
               if (!strcmp(facult[j],kom[i].fac)) { flag=0; /*printf("%YES! (%s)\n",facult[j]);*/ break; }
               //printf("NO! (%s)\n", facult[j]);
           }
           if (flag) { strcpy(facult[n],kom[i].fac); n++; }
           flag=1;
       }
       //for (i=0; i<n; i++) printf("%s\n",facult[i]);
       for (i=0; i<n; i++) {
           for (j=0; j<N; j++) {
               if (!strcmp(facult[i],kom[j].fac)) {
                   knum+=kom[j].num;
                   snum+=kom[j].lnum;
                   plosh+=kom[j].plosh;
               }
           }
           printf("%d)%s:\nNumber of room: %d\nNumber of students: %d\nAverage area per student: %5.3f\n",i,facult[i],knum,snum,(float)plosh/snum);
           plosh=knum=snum=0;
       }
       system("Pause");
}

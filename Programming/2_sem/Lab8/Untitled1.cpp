#include <cstdio>
#include <cstdlib>

const short N=5;

main() {
       struct data {short num; short vipnum; short vuznum;} scl[N];
       short index[N], i, j, tmp, min;
       float dol;
       printf("Type the information about schools:\n");
       for (i=0; i<N; i++) {
           index[i]=i;
           printf("%d)Number of school, number of graduates, number of students:\n",index[i]);
           scanf("%d %d %d",&scl[i].num,&scl[i].vipnum,&scl[i].vuznum);
       }
       for (i=0; i<N-1; i++) {
           min=i;
           for (j=i+1; j<N; j++)
               if (scl[index[min]].vuznum>scl[index[j]].vuznum) min=j;
           tmp=index[i]; index[i]=index[min]; index[min]=tmp;
       }
       printf("List of the schools:\n");
       for (i=0; i<N; i++) {
           dol=(float)(scl[index[i]].vuznum)/scl[index[i]].vipnum;
           printf("School ¹%d: %d graduates, %d students (%3.2f of graduates)\n",scl[index[i]].num, scl[index[i]].vipnum, scl[index[i]].vuznum, dol);
       }
       system("Pause");
}

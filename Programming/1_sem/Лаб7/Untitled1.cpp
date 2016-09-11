#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
const int N = 59;

main()
{
  int i=0, j;
  float t, A[N], a=2.14, b=-4.21, c=3.25, xn=-4.5, xk=-33.5, h=0.5; 
  printf("\n Ishodniy massiv:\n");
  while (xn>=xk) {
      A[i]=a*xn*xn+b*xn+c;
      printf("%5.1f\n",A[i]);
      xn=xn-h;
      i++;
  } 
  for (i=0; i<N-1; i++)
      for (j=N-2; j>=i; j--)
      if (A[j]>A[j+1]) {     
           t=A[j]; 
           A[j]=A[j+1];
           A[j+1]=t;
      }
  printf("\n Otsortirivanniy massiv:\n");
  for (i=0; i<N; i++)
      printf("%5.1f\n", A[i]);
  getch();
}

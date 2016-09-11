#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
typedef int *pint;

int Sum(int *a[], int n, int m) {
    int i, sum=0;
    // Для суммы элементов строки, исключая нулевой (длину строки), нумерацию надо начинать с 1
    for (i=0; i<m; i++)
        sum+=a[n][i];
    return sum;
}

main() {
    int i,j,m,n;
    pint *B;
    printf("Kolichestvo strok: ");
    scanf("%d",&n);
    B=new pint[n];
    srand(time(0));
    printf("Kolichestvo stolbcov (vkluchaya nulevoy simvol):\n");
    for (i=0; i<n; i++) { scanf("%d",&m); B[i]= new int[m]; B[i][0]=m; }
    printf("Matrix | Summa stroki:\n");
    for (i=0; i<n; i++) {
        printf("%4d",B[i][0]);
        for (j=1; j<B[i][0]; j++) { 
            B[i][j]=rand()%20;
            printf("%4d",B[i][j]); 
        }
        printf(" |%4d",Sum(B,i,B[i][0]));
        printf("\n");
    }
    for (i=0; i<n; i++)  delete B[i];
    delete B;
    B=NULL;
    system("Pause");
    
}

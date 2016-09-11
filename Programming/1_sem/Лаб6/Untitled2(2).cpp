#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
	int i, j, n, iv, nv, inv;
	printf("Vvedite N: ");
	scanf("%d",&n);
	int C[n];
	for (nv=1, i=1; i<=n; i++) {   
        nv*=i;
    }
    for (iv=1,i=1; i<=n; i++) {
        iv*=i;
        for (j=1, inv=1; j<=n-i; j++) {
            inv*=j;
        }
        C[i]=nv/(iv*inv);
    }
    printf("Vivod elementov massiva:\n");
    for (i=1; i<=n; i++){
        printf(" %d ",C[i]);
    }
	getch();
}
        

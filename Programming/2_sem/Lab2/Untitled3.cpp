#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>

void convert(unsigned short int dec)
{
    if (dec) {
        convert(dec/2);
        printf("%d",dec%2);
    }
}

main() {
    unsigned short int dec;
	printf("Vvedite chislo (dec): \n");
	scanf("%d",&dec);
	printf("Bin: ");
	convert(dec);
    getch(); 
}

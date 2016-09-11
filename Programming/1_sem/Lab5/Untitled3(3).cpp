#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 

main() 
{ 
float s,y,n,x,e,sum; 
int i; 
i=1; 
y=1; 
e=0.001; 
printf("Vvedite x \n"); scanf("%f",&x); 
sum=-x; 
while (fabs(sum)>=e) 
{ 
s=s+sum; 
i=i+1; 
y=y*i; 
sum=pow(-1,i)*pow(x,i)/y; 
}; 
printf("S=%7.3f \n",s); 
system("PAUSE"); 
return 0; 
}

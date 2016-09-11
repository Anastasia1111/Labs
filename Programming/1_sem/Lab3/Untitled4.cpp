#include <stdio.h>
#include <conio.h>

main (){
 int t,m,d;
 printf("Vvedite den': \n");
 scanf("%d", &t);
 switch(t<32)
 {
          case 1:
               d=t;
               printf(" M=1\n D=%d", d); break;
 }   
  switch((t>31)*(t<60))
 {
          case 1:
               d=t-31;
               printf(" M=2\n D=%d", d); break;
 }     
  switch((t>59)*(t<91))
 {
          case 1:
               d=t-59;
               printf(" M=3\n D=%d", d); break;
 }     
  switch((t>90)*(t<121))
 {
          case 1:
               d=t-90;
               printf(" M=4\n D=%d", d); break;
 }     
  switch((t>120)*(t<152))
 {
          case 1:
               d=t-120;
               printf(" M=5\n D=%d", d); break;
 }     
  switch((t>151)*(t<182))
 {
          case 1:
               d=t-151;
               printf(" M=6\n D=%d", d); break;
 }     
  switch((t>181)*(t<212))
 {
          case 1:
               d=t-181;
               printf(" M=7\n D=%d", d); break;
 }     
  switch((t>211)*(t<243))
 {
          case 1:
               d=t-211;
               printf(" M=8\n D=%d", d); break;
 }     
  switch((t>242)*(t<274))
 {
          case 1:
               d=t-242;
               printf(" M=9\n D=%d", d); break;
 }     
  switch((t>273)*(t<304))
 {
          case 1:
               d=t-273;
               printf(" M=10\n D=%d", d); break;
 }     
  switch((t>303)*(t<335))
 {
          case 1:
               d=t-303;
               printf(" M=11\n D=%d", d); break;
 }     
  switch((t>334)*(t<366))
 {
          case 1:
               d=t-334;
               printf(" M=12\n D=%d", d); break;
 }            
 getch();  
}
     

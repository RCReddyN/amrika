#include <stdio.h>
int main(void){
float n;
float f;
if(0 == scanf("%f", &n)) {
n = 0;
scanf("%*s");
}
f = 1;
while(n>0){
f = f*n;
n = n-1;
}
printf("%.7f\n", (float)(f));
return 0;
}

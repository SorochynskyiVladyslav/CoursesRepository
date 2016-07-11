#include <stdio.h>
#include <stdlib.h>

int main()
{ int h, m, code;
float t, s;
scanf("%i %i %i", &h, &m, &code);
if ((code>=10)&&(code<=999))
switch (code) {
case 44:
t=0.77;
break;
case 62:
t=0.8;
break;
case 32:
t=0.95;
break;
case 692:
t=1.5;
break;
case 697:
t=1.5;
break;
default:
printf("error, code is wrong");
break;}
else printf ("error, code is wrong");

s=h*60*t+m*t;
printf("%f", s);

    return 0;
}

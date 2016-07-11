#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double x, double y, double z) {
   double a;
   if ((x<=y)||(x<=0)||(sin(x)==0)||(z==0))
    return NAN;
    else
    a0=pow(x, y+1)/pow(x-y, 1/z);
    a1=6*y+z/x;
    a2=pow(fabs(cos(y)/sin(x)+1), 1/2);
    a=a0+a1+a2;
   return a;
}

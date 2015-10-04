#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double x, double y, double z) {
   double a;
   if ((x==y)||(x==0)||(sin(x)==0)||(z==0))
    return NAN;
    else
   a=(pow(x, y+1))/(pow(x-y,1/z))+6*y+z/x+pow(abs(cos(y)/sin(x)+1), 1/2);
   return a;
}

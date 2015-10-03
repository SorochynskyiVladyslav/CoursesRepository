#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double, double, double);

int main() {
    double xval = 0, yval = 0, zval = 0;
    double result;

    result = calc(xval, yval, zval);

    printf("%.12f", result);
    return 0;
}

// copy the code below to the answers files and add #include <math.h> at the beginning

double calc(double x, double y, double z) {
   double a;
   if ((x==y)||(x==0)||(sin(x)==0))
    return NAN;
    else
   a=(pow(x, y+1))/(pow(x-y,1/z))+6*y+z/x+pow(abs(cos(y)/sin(x)+1), 1/2);
   return a;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double long2double (long long);
int main () {
    long long number;
    printf ("Enter the number ");
    scanf ("%lli", &number);
    printf ("%.325llf",long2double(number));
}
double long2double (long long num){
double e = 0, f = 0, result;
short sign,i,j;
sign=(num>>63)&1;
for (i=52;i<63;i++){             //calculating exponent(e)
    e = e + (((num>>i)&1)*pow(2,i-52));
}
for (j=51;j>=0;--j){             //calculating fraction(f)
    f = f + (((num>>j)&1)*pow(2,j-52));
}
if ((e == 2047) && (f!=0)) {     //if num is NAN
    return NAN;
}
if ((e == 2047) && (f==0) && (sign==0)) {  //if num is infinity
    return INFINITY;
}
if ((e == 2047) && (f==0) && (sign==1)) {  //if num is -infinity
    return -INFINITY;
}
if ((e>0) && (e<2047)) {            //normalized
        result = pow(-1, sign)*pow(2, e-1023)*(f+1);
    return result;
}
if ((e==0) && (f!=0)){              //denormalized
        result = pow(-1,sign) * pow(2,-1022)*f;
    return result;
}
if ((e==0) && (f==0) && (sign==1)) { //if num is -0
    return -0;
}
if ((e==0) && (f==0) && (sign==0)) { //if num is +0
    return 0;
}


}


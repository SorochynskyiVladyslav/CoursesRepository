#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int exec(int, int, int);

int mymin(int a, int b){
if (a>b) return b;
else return a;
}
int mymax(int a, int b){
if (a>b) return a;
else return b;
}

int main() {
    int opval = 0, aval = 0, bval = 0;
    int resultVal;

    resultVal = exec(opval, aval, bval);

    printf("%i", resultVal);
    return 0;
}
// copy the code below to the answers files and add #include <math.h> at the beginning
int exec(int op, int a, int b) {
   int result, c, datatype;
if (op<0)
{c=a;
a=b;
b=c;
op=op*(-1);}
else a=a;
b=b;
   switch(op){
   case 0:
       result=a*(-1);
       break;
   case 1:
       result=a+b;
       break;
   case 2:
       result=a-b;
       break;
   case 3:
       result=a*b;
       break;
   case 4:
       result=a/b;
       break;
   case 5:
       result=abs(a);
       break;
   case 6:
       result=pow(a, b);
       break;
   case 7:
   case 13:
   case 77:
       result=a%b;
       break;
   case 8:
       result=mymax(a, b);
       break;
   case 9:
       result=mymin(a, b);
       break;
   case 10:
       datatype=abs(b)%8;
       switch(datatype){
       case 0:
           datatype=sizeof(char);
           break;
       case 1:
           datatype=sizeof(signed char);
           break;
       case 2:
           datatype=sizeof(short);
           break;
       case 3:
           datatype=sizeof(unsigned int);
           break;
       case 4:
           datatype=sizeof(long);
           break;
       case 5:
           datatype=sizeof(unsigned long long);
           break;
       case 6:
           datatype=sizeof(float);
           break;
       case 7:
           datatype=sizeof(double);
           break;
       default:
           printf("error");
           break;
           }
       result=abs(a)*datatype;
       break;
   case 11:
       if (b==6) result=0;
       else {if ((a==1/2)||(a==3/2))
            result=0;
       else result=tan(a*M_PI)/((6-b)*7);}
       break;
   default:
       if (op<100)
       result=(op%abs(a+1))+(op%abs(b+1));
       else result=-1;
       break;
   }
   return result;
}

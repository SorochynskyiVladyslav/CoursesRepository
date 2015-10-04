#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mymin(int a, int b){    //виявив, що min та max не працюють
if (a>b) return b;          //тому написав функціі, що за дією ідентичні до min та max
else return a;
}
int mymax(int a, int b){
if (a>b) return a;
else return b;
}

int satisfies(int a, int b, int c) {
   int result, modmin1, modmin2, modmin, modmax1, modmax2, modmax, sum2;

   if ((a<0)&&(b<0)&&(c<0))
   {modmin1=mymin(a, b);
   modmin2=mymin(b, c);
   modmin=mymin(modmin1, modmin2);
     if (modmin==a) sum2=b+c;
     else if (modmin==b) sum2=a+c;
          else sum2=a+b;
     if ((sum2<-256)&&(modmin<256)&&(modmin%2==0))
        result=1;
     else if (((abs(sum2)-modmin)<16)||(abs(sum2)<16))
        result=1;
        else result=0;}
   else if ((a>=0)&&(b>=0)&&(c>=0))
        {modmax1=mymax(a, b);
        modmax2=mymax(b, c);
        modmax=mymax(modmax1, modmax2);
        modmin1=mymin(a, b);
        modmin2=mymin(b, c);
        modmin=mymin(modmin1, modmin2);
          if ((modmax+modmin)<256)
            result=1;
            else result=0;}
        else if ((a<0)||(b<0)||(c<0))
             {modmin1=mymin(a, b);
             modmin2=mymin(b, c);
             modmin=mymin(modmin1, modmin2);
               if (modmin>-256) result=1;
                else result=0;}
             else if ((a<b)&&(b<c))
                    {sum2=(a+b)*7;
                    if (sum2>-256) result=1;
                    else result=0;}
                  else if ((a<b)&&(c<b))
                         {sum2=(a+c)*7;
                         if (sum2>-256) result=1;
                           else result=0;}
                         else sum2=(b+c)*7;
                            if (sum2>-256) result=1;
                            else result=0;
   return result;
}

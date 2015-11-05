#include <stdio.h>
#include <stdlib.h>

double calc(int n, int m);

int main()
{
    int n, m;
    double res;
    puts("==please, enter an amount of iterations n==");
    scanf("%i", &n);
    puts("==please, enter an amount of iterations m==");
    scanf("%i", &m);
    res = calc(n, m);
    printf("Result = %lf", res);
    return 0;
}

double calc(int n, int m){
    double sum1=0, sum2=0, sum=0, i, j;
    for (i=1; i<=(n+1); i++){
        for (j=1; j<(m+1); j++){
            sum2 = i*i + (11/j);
            sum1 = sum1+sum2;
        }
        sum = sum + sum1;
    }
    return sum;
}

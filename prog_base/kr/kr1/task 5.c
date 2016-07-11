#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, sum;
    int n=4;
    int m1[n], m2[n];
    puts ("==enter the first massive, please==");
    for (i=0; i<n; i++){
        scanf ("%i", &m1[i]);
    }
    puts("==enter the second massive, please==");
    for (i=0; i<n; i++){
        scanf ("%i", &m2[i]);
    }
    puts("==here you have negative sums==");
    for (i=0; i<n; i++){
        sum=m1[i]+m2[i];
        if (sum<0)
            printf ("%i\n", sum);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int sumLoop(int num){
    int s = num;
    while (--num> 0 ){
        s += num;
    }
    return s;
}

int sum(int num){
    if (num == 0){
        return 0;
    } else {
        return num + sum(num - 1);
    }
}

int main()
{
    int n = 5, s;
    s = sum(n);
    printf("%i", s);
    return 0;
}














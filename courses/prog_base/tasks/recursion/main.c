#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkStr(char* str, char* p, int num);

int main()
{
    char ch[100];
    char* str;
    int num = 11;
    puts("enter a string");
    str = gets(ch);
    char* p = str + strlen(str) - 1;
    num = checkStr(str, p, num);
    printf("%i", num);
    return 0;
}

int checkStr(char* str, char* p, int num){
    if (*p >= 48 && *p <= 57 ) num = (int) *p - 48;
    else num = 11;
    if (p + 1 == str || num != 11){
        if (p + 1 == str && num == 11){
        num = 0;
        }
        return num;
    }
    else {
        return checkStr(str, p - 1, num);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[100];
    char * p;
    char tok = " ";
    int l, i;
    gets(str);
    p = strtok(str, tok);
    while(p != NULL){
        if (strlen(p)>5){
            l=strlen(p)-2;
            printf("%c", p[0]);
            printf("%i", l);
            printf("%c", p[strlen(p)-1]);
            }
        else {
            for (i=(strlen(p)-1); i=0; i--){
                printf("%c", p[i]);
                }
                puts ("==next word==");
        }
        p = strtok(NULL, tok);
        }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int todec(int* p);

int main()
{
    char * str = NULL;
    int* f = NULL;
    int* l = NULL;
    int* m = NULL;
    str = malloc(sizeof(char) * 100);
    f = malloc(sizeof(int));
    l = malloc(sizeof(int));
    m = malloc(sizeof(int));

    if (NULL == str || NULL == f || NULL == l || NULL == m){
    printf ("error, memory was not reserved");
    return 1;
    }

    puts("enter a string");
    gets(str);
    char* p = str;

    while (p != NULL){
        if (*p >= 48 && *p <= 57 ){
            *f = (int) *p;
            todec(f);
            break;
        }
        p++;
    }
    p = str;
    p = p + strlen(str);
    while (p != NULL){
        if (*p >= 48 && *p <= 57 ){
            *l = (int) *p;
            todec(l);
            break;
        }
        p--;
    }
    *m = *f * *l;
    printf("%i", *m);
    free(str);
    free(p);
    free(f);
    free(l);
    free(m);
    return 0;
}

int todec(int* p){
    switch (*p){
    case 48:
        *p = 0;
        break;
    case 49:
        *p = 1;
        break;
    case 50:
        *p = 2;
        break;
    case 51:
        *p = 3;
        break;
    case 52:
        *p = 4;
        break;
    case 53:
        *p = 5;
        break;
    case 54:
        *p = 6;
        break;
    case 55:
        *p = 7;
        break;
    case 56:
        *p = 8;
        break;
    case 57:
        *p = 9;
        break;
    default:
        printf("error");
        return 1;
    }
    return 0;
}

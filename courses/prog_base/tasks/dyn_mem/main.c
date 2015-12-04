#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            *f = (int) *p - 48;
            break;
        }
        p++;
    }
    p = str;
    p = p + strlen(str);
    while (p != NULL){
        if (*p >= 48 && *p <= 57 ){
            *l = (int) *p - 48;
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

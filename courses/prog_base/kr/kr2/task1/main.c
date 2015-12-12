#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wordCount(char* str);

int main(int argc, char **argv)
{
    char str[100];
    int i, j = 0;
    FILE * fp = NULL;
    FILE * fr = NULL;
    fp = fopen("fread.txt", "r");
    fr = fopen("fwrite.txt", "w");
    if (fp == NULL || fr == NULL){
        printf("error opening file");
    }
    while (!feof(fp)){
    fgets(str, 100, fp);
    printf("number of words in string '%i' = %i\n", j, wordCount(str));
    fprintf(fr, "number of words in string '%i' = %i\n", j, wordCount(str));
    j++;
    }
    fclose(fp);
    fclose(fr);
    return 0;
}

int wordCount(char* str){
    int amount = 0, i;
    char* p = str;
    for (i = 0; i < strlen(str) + 1; i++){
        if (((isdigit(*p) != 0 || *p == 32) && ((*(p + 1) <= 90 && *(p + 1) >= 65) || (*(p + 1) <= 122 && *(p + 1) >= 97))) || (*p == 0))
            amount++;
        p++;
    }
    return amount;
}

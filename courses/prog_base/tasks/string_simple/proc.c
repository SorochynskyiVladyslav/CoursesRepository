#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check (char * str);
char * extra(const char * extraStr);

char * process(char * resultStr, const char * textLines[],
               int linesNum, const char * extraStr) {
    int i;
    int status=0;
    char * line;
    int index;
    char * extr;
    for(i = 0; i < linesNum; i++) {
        line = textLines[i];
        status = check (line);
        if (status==1){
               index = i;
               break;
        }
        else index = -1;
    }
    extr = extra(extraStr);
    sprintf(resultStr, "%i ", index);
    strcat(resultStr, extr);
    return resultStr;
}

char * extra(const char * extraStr){
char * p;
char * extr1;
char * extr2;
char * h[] = {"a",
"e",
"i",
"o",
"u",
"y"};
const char * sfind=" ";
int flag, i;
extr1=extraStr;
p = strtok(extr1, sfind);
    while(p != NULL){
        for (i=0; i<6; i++){
                if ((p[0]==h[i])&&(p[strlen(p)-1]!=h[i])){
                    flag=1;
                }
                else flag=0;
            }
            if(flag == 1){
                extr2=p;
                break;}
            p = strtok(NULL, sfind);
        }
        if (flag == 0){
            extr2=NULL;
        }
        return extr2;
}

int check (char * str){
char * p;
char * h[] = {"a",
 "e",
 "i",
 "o",
 "u",
 "y"};
char sfind=" ";
int status = 0;
int i;
    p = strtok(str, sfind);
    while(p != NULL){
        for (i=0; i<6; i++){
                if ((p[0]==h[i])&&(p[strlen(p)-1]!=h[i])){
                    status=1;}
        else {
            status=0;
            break;}
            }
            if(status == 0) break;
            p = strtok(NULL, sfind);
        }
    return status;
}


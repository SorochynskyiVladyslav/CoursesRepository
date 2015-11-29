#include <stdio.h>

void fprocess(const char * pread, const char * pwrite){
    int i, x1, x2, y1, y2;
    FILE * fp = NULL;
    fp = fopen("pread.txt", "r");
    if (fp == NULL){
        printf("error opening file");
    }
    for(i = 0; i < 15; i++){
        while (i != -1){
            if (fgetc(fp) == 10)
            break;
        }
    }
    fscanf(fp, "%i%i%i%i", &x1, &y1, &x2, &y2);
    fclose(fp);
    fp = fopen("pwrite.txt", "w");
    if (fp == NULL){
        printf("error opening file");
    }
    if (sqrt(x1*x1 + y1*y1) <= sqrt(x2*x2 + y2*y2)){
        fprintf(fp, "(%i, %i)", x1, y1);
    }
    else {
        fprintf(fp, "(%i, %i)", x2, y2);
    }
    fclose(fp);
}

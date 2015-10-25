#include <stdio.h>
#include <stdlib.h>

void printMatrix(int mat[4][4]);
void copyMatrix(int mat [4][4], int copymat[4][4]);
void fillRand(int mat[4][4]);
void rotateCW90(int mat[4][4]);
void flipV(int mat[4][4]);
void transposMain(int mat[4][4]);
/*
int main()
{   int mat[4][4];
    srand(time(NULL));
    fillRand(mat);
    printMatrix(mat);
    puts (" ");
    transposMain(mat);
    printMatrix(mat);

    return 0;
}
*/
void copyMatrix(int mat[4][4], int copymat[4][4]) {
int i, j;
for (i=0; i<4; i++){
    for(j=0; j<4; j++){
        copymat[i][j]=mat[i][j];
    }
}
}

void printMatrix(int mat[4][4]) {
    int i, j;
    int n = 4;
    printf("{ ");
    for (i = 0; i < n; i++) {
        printf("{");
        for (j = 0; j < n; j++) {
            printf("%5i, ", mat[i][j]);
        }
        printf("}");
        if ( i < n - 1)
            printf("\n  ");
    }
    printf(" };\n");
}

void fillRand(int mat[4][4]){
        int i, j;
        for (i=0; i<4; i++) {
                for (j=0; j<4; j++){
                    mat[i][j]=rand() % 1998 - 999;
        }
        }
        }

void rotateCW90(int mat[4][4]){
 int copymat[4][4];
 int i, j;
 copyMatrix(mat, copymat);
 for (j=0; j<4; j++){
    for (i=0; i<4; i++){
        mat[i][j]=copymat[3-j][i];
    }
 }
}

void flipV(int mat[4][4]){
 int copymat[4][4];
 int i, j;
 copyMatrix(mat, copymat);
 for (i=0; i<4; i++){
    for (j=0; j<4; j++){
        mat[i][j]=copymat[3-i][j];
    }
 }
}

void transposMain(int mat[4][4]){
 int copymat[4][4];
 int i, j;
 copyMatrix(mat, copymat);
 for (i=0; i<4; i++){
    for (j=0; j<4; j++){
        mat[i][j]=copymat[j][i];
    }
 }
}

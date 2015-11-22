#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

void callhelp(int size){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD head, text;
    int fst = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
        fhelp = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

    head.X = 10;
    head.Y = size + 11;
    text.X = 23;
    text.Y = size + 11;

    SetConsoleTextAttribute(hConsole, fhelp);
    SetConsoleCursorPosition(hConsole, head);
    printf("clear");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("random");
    head.Y++;
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("change");
    head.Y++;
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("display");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("transpose");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("rotate");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("sum");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("colsum");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("diogsum");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("swingfirst");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("swinglast");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("swingcols");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("help");
    head.Y++;
    SetConsoleCursorPosition(hConsole, head);
    printf("end");

    SetConsoleTextAttribute(hConsole, fst);
    SetConsoleCursorPosition(hConsole, text);
    printf("set all elements to zero");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("set all elemets to random numbers in a range you enter");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("use only ranges that belong to [0 ... 10)");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("set element on (row, col) position to number you enter");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("use only numbers that belong to [0 ... 10)");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("display matrix horizontally");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("side diagonal transposal");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("rotate matrix clockwise for 90 degrees");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("calculate sum of all matrix elements");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("calculate sum of elements in a col you enter");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("calculate sum of elements on and under main diagonal");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("swing first min and first max elemets of matrix");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("swing last min and last max elemets of matrix");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("swing cols with max and min sums");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("display help");
    text.Y++;
    SetConsoleCursorPosition(hConsole, text);
    printf("exit program");
}

void drawinterface(int size){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD in;
    int x = 0, y = 0, fmt, fc, f;
    fmt = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fc = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    f = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, fmt);
    for (y = 0; y < (size + 6); y++){
    for (x = 0; x < 80; x++){
        in.X = x;
        in.Y = y;
        SetConsoleCursorPosition(hConsole, in);
        if (y == 0 || y == (size + 5) || x == 0 || x == 79)
            printf("*");
        else printf(" ");
    }
    }
    in.X = 3;
    in.Y = size + 6;
    SetConsoleTextAttribute(hConsole, f);
    printf("\n enter your command\n");
    printf(" >> ");
    in.X =  5;
    in.Y = size + 8;
    SetConsoleTextAttribute(hConsole, fc);
    SetConsoleCursorPosition(hConsole, in);
    in.X = 0;
    for (y = 0; y < 30; y++){
    in.Y += y;
    if (y == 0) in.X = 5;
    else in.X = 0;
    SetConsoleCursorPosition(hConsole, in);
    printf("                                                                                                                 ");
    in.Y = size + 8;
    }
    in.X = 0;
    in.Y = 0;
    SetConsoleCursorPosition(hConsole, in);
        }

void copymat(double* p, double* v, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
        *(v + size*i + j) = *(p + size*i + j);
    }
    }
}

void printmat (double* p, int size){
    int i, j, fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work;
    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, fmt);
        for (j = 0; j < size; j++){
            printf ("%.3lf ", *(p + size*i + j));
        }
        printf("\n");
    }
}

void printmatd (double* p, double* v, int size){
    int i, j, fs, fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work, in;

    fs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    in.X =  5;
    in.Y = size + 8;
    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        for (j = 0; j < size; j++){
            if (*(p + size*i + j) != *(v + size*i + j))
            SetConsoleTextAttribute(hConsole, fs);
            else SetConsoleTextAttribute(hConsole, fmt);
            printf ("%.3lf ", *(p + size*i + j));
        }
        printf("\n");
    }
    SetConsoleCursorPosition(hConsole, in);
}

void printmatcol (double* p, int size, int col){
    int i, j, fs, fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work, in;

    fs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    in.X =  5;
    in.Y = size + 8;
    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        for (j = 0; j < size; j++){
            if (j == col)
            SetConsoleTextAttribute(hConsole, fs);
            else SetConsoleTextAttribute(hConsole, fmt);
            printf ("%.3lf ", *(p + size*i + j));
        }
        printf("\n");
    }
    SetConsoleCursorPosition(hConsole, in);
}

void printmatdg (double* p, int size){
    int i, j, fs, fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work, in;

    fs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    in.X =  5;
    in.Y = size + 8;
    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        for (j = 0; j < size; j++){
            if ((double) (i+1) / (j+1) >= 1)
            SetConsoleTextAttribute(hConsole, fs);
            else SetConsoleTextAttribute(hConsole, fmt);
            printf ("%.3lf ", *(p + size*i + j));
        }
        printf("\n");
    }
    SetConsoleCursorPosition(hConsole, in);
}

void printbrotate (double* p, int size){
    int i, j, f, fs, fmt;
    const long SLEEP_MILLISECONDS = 1000;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work;

    f = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
    fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        for (j = 0; j < size; j++){
            if (i == 0 || j == 0){
                SetConsoleTextAttribute(hConsole, fs);
            }
            else {
                SetConsoleTextAttribute(hConsole, f);
            }
            printf ("%.3lf", *(p + size*i + j));
            SetConsoleTextAttribute(hConsole, fmt);
            printf (" ");
        }
        printf("\n");
    }
    Sleep(SLEEP_MILLISECONDS);
}

void printarotate (double* p, int size){
    int i, j, f, fs, fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD work;

    f = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    fs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
    fmt = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    work.X = 33 - size* 5/2;
    for (i = 0; i < size; i++){
        work.Y = i + 2;
        SetConsoleCursorPosition(hConsole, work);
        for (j = 0; j < size; j++){
            if (i == 0 || j == (size - 1)){
                SetConsoleTextAttribute(hConsole, fs);
            }
            else {
                SetConsoleTextAttribute(hConsole, f);
            }
            printf ("%.3lf", *(p + size*i + j));
            SetConsoleTextAttribute(hConsole, fmt);
            printf (" ");
        }
        printf("\n");
    }
}

void settonull (double* p, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            *(p + size*i + j) = 0;
        }
}
}

void random (double* p, int size, double arand, double brand){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            *(p + size*i + j) = (double) rand() / RAND_MAX * (brand - arand) + arand;
        }
}
}

void change (double* p, int size, int rownum, int colnum, double newelem){
    *(p + size*rownum + colnum) = newelem;
}

void mirH (double* p, int size){
    int i, j;
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            *(p + size*i + j) = *(v + size*i + (size - 1 - j));
        }
    }
}

void transposeSide (double* p, int size){
    int i, j;
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            *(p + size*i + j) = *(v + size*(size - 1 - j) + (size - 1 - i));
        }
    }
}

void rotateCW90 (double* p, int size){
    int i, j;
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            *(p + size*i + j) = *(v + size*(size - 1 - j) + i);
        }
    }
}

double summat (double* p, int size){
    int i, j;
    double sum = 0;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            sum += *(p + size*i + j);
        }
    }
    return sum;
}

double sumcol (double* p, int size, int col){
    int i;
    double sum = 0;
    for (i = 0; i < size; i++){
            sum += *(p + size*i + col);
    }
    return sum;
}

double undsum (double* p, int size){
    int i, j;
    double sum = 0;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if ((double) (i+1) / (j+1) >= 1){
            sum += *(p + size*i + j);
        }
        }
        }
    return sum;
}

void swfminmax (double* p, int size){
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    int i, j, mini, minj, maxi, maxj;
    double min = 0, max = 0;
    mini = 0;
    minj = 0;
    maxi = 0;
    maxj = 0;
    min = *(p);
    max = *(p);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (*(p + size*i + j) < min){
                mini = i;
                minj = j;
                min = *(p + size*i + j);
            }
            if (*(p + size*i + j) > max){
                maxi = i;
                maxj = j;
                max = *(p + size*i + j);
            }
        }
    }
    *(p + size*mini + minj) = *(v + size*maxi + maxj);
    *(p + size*maxi + maxj) = *(v + size*mini + minj);
}

void swlminmax (double* p, int size){
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    int i, j, mini, minj, maxi, maxj;
    double min = 0, max = 0;
    mini = 0;
    minj = 0;
    maxi = 0;
    maxj = 0;
    min = *(p);
    max = *(p);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (*(p + size*i + j) <= min){
                mini = i;
                minj = j;
                min = *(p + size*i + j);
            }
            if (*(p + size*i + j) >= max){
                maxi = i;
                maxj = j;
                max = *(p + size*i + j);
            }
        }
    }
    *(p + size*mini + minj) = *(v + size*maxi + maxj);
    *(p + size*maxi + maxj) = *(v + size*mini + minj);
}

void swcol (double* p, int size){
    double cop[size][size];
    double* v = &cop;
    copymat(p, v, size);
    double summax, summin;
    int j, i, jmax = 0, jmin = 0;
    summin = sumcol(p, size, 0);
    summax = sumcol(p, size, 0);
    for (j = 0; j < size; j++){
        if (sumcol(p, size, j) > summax){
            summax = sumcol(p, size, j);
            jmax = j;
        }
        if (sumcol(p, size, j) < summin){
            summin = sumcol(p, size, j);
            jmin = j;
        }
    }
    for (i = 0; i < size; i++){
    *(p + size*i + jmin) = *(v + size*i + jmax);
    *(p + size*i + jmax) = *(v + size*i + jmin);
    }
}

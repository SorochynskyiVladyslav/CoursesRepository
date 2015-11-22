#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

double sumcol (double* p, int size, int col);
double summat (double* p, int size);
double undsum (double* p, int size);

int main()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cmd, scan, scf;
    scan.X = 20;
    scan.Y = 2;
    char com[100];
    char* command;
    int fcmd = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        fst = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
        fer = FOREGROUND_RED | FOREGROUND_INTENSITY,
        fhelp = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        fini = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;

    int size = -1, status = 0, row = -1, col = -1;
    double newel, a, b, sum, colsum, dgsum, check1 = 1, check2 = 1, check3 = 1;

    SetConsoleCursorPosition(hConsole, scan);
    SetConsoleTextAttribute(hConsole, fst);
    printf ("enter size of matrix in a range [1 ... 13] ");
    while (size < 1 || size > 13){
        scan.Y = 4;
        SetConsoleCursorPosition(hConsole, scan);
        printf("                                                                                              \n");
        printf("                                                                                               \n");
        printf("                                                                                               \n");
        printf("                                                                                               \n");
        printf("                                                                                               \n");
        SetConsoleCursorPosition(hConsole, scan);
        scanf("%i", &size);
        fflush(stdin);
        if (size >= 1 && size <= 13)
            break;
        scan.Y = 3;
        SetConsoleCursorPosition(hConsole, scan);
        SetConsoleTextAttribute(hConsole, fer);
        printf ("invalid input, try again or enter 0 to exit program ");
        if (size == 0)
            return 0;
        fflush(stdin);
        SetConsoleTextAttribute(hConsole, fst);
    }

    scf.X = 5;
    scf.Y = size + 9;
    cmd.X = 5;
    cmd.Y = size + 8;
    double arr[size][size];
    double* p = &arr;
    double cop[size][size];
    double* v = &cop;;

    drawinterface(size);
    settonull(p, size);
    printmat(p, size);

    while (status != 2){
        SetConsoleTextAttribute(hConsole, fcmd);
        SetConsoleCursorPosition(hConsole, cmd);
        command = gets(com);
        SetConsoleCursorPosition(hConsole, scf);
        printf ("                                                                             ");

        fflush(stdin);
        status = 0;
        if (strcmp(command, "end") == 0){
            status = 2;
        }
        if (strcmp(command, "clear") == 0){
            drawinterface(size);
            settonull(p, size);
            printmat(p, size);
        }
        if (strcmp(command, "random") == 0){
            copymat(p, v, size);
            do {
            SetConsoleTextAttribute(hConsole, fst);
            SetConsoleCursorPosition(hConsole, scf);
            check1 = scanf("%lf", &a);
            fflush(stdin);
            scf.Y++;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            scf.Y--;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            if (a < 0 || a >= 10 || check1 == 0){
                SetConsoleTextAttribute(hConsole, fer);
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("invalid range start input, try again");
                scf.Y--;
                SetConsoleTextAttribute(hConsole, fst);
                SetConsoleCursorPosition(hConsole, scf);
            }
            else status = 1;
            } while (status != 1);
            status = 0;
            do {
            SetConsoleTextAttribute(hConsole, fst);
            SetConsoleCursorPosition(hConsole, scf);
            check2 = scanf("%lf", &b);
            fflush(stdin);
            scf.Y++;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            scf.Y--;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            if (b < 0 || b >= 10 || check2 == 0){
                SetConsoleTextAttribute(hConsole, fer);
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("invalid range finish input, try again");
                scf.Y--;
                SetConsoleTextAttribute(hConsole, fst);
                SetConsoleCursorPosition(hConsole, scf);
            }
            else status = 1;
            } while (status != 1);
            status = 0;
            scf.X = 5;
            scf.Y = size + 9;
            status = 0;
            if (a > b) random(p, size, b, a);
            else random (p, size, a, b);
            drawinterface(size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "change") == 0){
            copymat(p, v, size);
            do {
            SetConsoleTextAttribute(hConsole, fst);
            SetConsoleCursorPosition(hConsole, scf);
            check1 = scanf("%i", &row);
            fflush(stdin);
            scf.Y++;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            scf.Y--;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                  ");
            if (row < 0 || row >= size || check1 == 0){
                SetConsoleTextAttribute(hConsole, fer);
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("invalid row input, try again");
                scf.Y--;
                SetConsoleTextAttribute(hConsole, fst);
                SetConsoleCursorPosition(hConsole, scf);
            }
            else status = 1;
            } while (status != 1);
            status = 0;
            do {
            SetConsoleTextAttribute(hConsole, fst);
            SetConsoleCursorPosition(hConsole, scf);
            check2 = scanf("%i", &col);
            fflush(stdin);
            scf.Y++;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                ");
            scf.Y--;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                ");
            if (col < 0 || col >= size || check2 == 0){
                SetConsoleTextAttribute(hConsole, fer);
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("invalid col input, try again");
                scf.Y--;
                SetConsoleTextAttribute(hConsole, fst);
                SetConsoleCursorPosition(hConsole, scf);
            }
            else status = 1;
            } while (status != 1);
            status = 0;
            do {
            SetConsoleTextAttribute(hConsole, fst);
            SetConsoleCursorPosition(hConsole, scf);
            check3 = scanf("%lf", &newel);
            fflush(stdin);
            scf.Y++;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                                ");
            scf.Y--;
            SetConsoleCursorPosition(hConsole, scf);
            printf("                                                                                ");
            if (newel < 0 || newel >= 10 || check3 == 0){
                SetConsoleTextAttribute(hConsole, fer);
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("invalid new element input, try again, use only numbers in range [0 ... 10)");
                scf.Y--;
                SetConsoleTextAttribute(hConsole, fst);
                SetConsoleCursorPosition(hConsole, scf);
            }
            else status = 1;
            } while (status != 1);
            status = 0;

        scf.X = 5;
        scf.Y = size + 9;
        change(p, size, row, col, newel);
        drawinterface(size);
        printmatd(p, v, size);
        row = -1;
        col = - 1;
        }
        if (strcmp(command, "display") == 0){
            copymat(p, v, size);
            drawinterface(size);
            mirH(p, size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "transpose") == 0){
            copymat(p, v, size);
            drawinterface(size);
            transposeSide(p, size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "rotate") == 0){
            copymat(p, v, size);
            drawinterface(size);
            printbrotate(p, size);
            rotateCW90(p, size);
            printarotate(p, size);
        }
        if (strcmp(command, "sum") == 0){
            scf.X = 27;
            scf.Y = size + 3;
            sum = summat(p, size);
            drawinterface(size);
            printmat(p, size);
            SetConsoleCursorPosition(hConsole, scf);
            SetConsoleTextAttribute(hConsole, fini);
            printf ("matrix sum = %lf", sum);
            sum = 0;
            scf.X = 5;
            scf.Y = size + 9;
        }
        if (strcmp(command, "colsum") == 0){
            while (status != 1){
                SetConsoleCursorPosition(hConsole, scf);
                SetConsoleTextAttribute(hConsole, fst);
                check1 = scanf("%i", &col);
                fflush(stdin);
                SetConsoleCursorPosition(hConsole, scf);
                printf ("                                                                ");
                scf.Y++;
                SetConsoleCursorPosition(hConsole, scf);
                printf("                                                  ");
                scf.Y--;
                if (col < 0 || col >= size || check1 == 0){
                    scf.Y++;
                    SetConsoleCursorPosition(hConsole, scf);
                    SetConsoleTextAttribute(hConsole, fer);
                    printf("invalid col input, try again");
                    scf.Y--;
                }
                else status = 1;
            }
            status = 0;
            scf.X = 27;
            scf.Y = size + 3;
            colsum = sumcol(p, size, col);
            drawinterface(size);
            printmatcol(p, size, col);
            SetConsoleCursorPosition(hConsole, scf);
            SetConsoleTextAttribute(hConsole, fini);
            printf ("colsum = %lf", colsum);
            colsum = 0;
            scf.X = 5;
            scf.Y = size + 9;
        }
        if (strcmp(command, "diogsum") == 0){
            scf.X = 20;
            scf.Y = size + 3;
            dgsum = undsum(p, size);
            drawinterface(size);
            printmatdg(p, size);
            SetConsoleCursorPosition(hConsole, scf);
            SetConsoleTextAttribute(hConsole, fini);
            printf ("sum under main diagonal = %lf", dgsum);
            dgsum = 0;
            scf.X = 5;
            scf.Y = size + 9;
        }
        if (strcmp(command, "swingfirst") == 0){
            copymat(p, v, size);
            swfminmax(p, size);
            drawinterface(size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "swinglast") == 0){
            copymat(p, v, size);
            swlminmax(p, size);
            drawinterface(size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "swingcols") == 0){
            copymat(p, v, size);
            swcol(p, size);
            drawinterface(size);
            printmatd(p, v, size);
        }
        if (strcmp(command, "help") == 0) {
            printmat(p, size);
            callhelp(size);
            SetConsoleCursorPosition(hConsole, cmd);
            printf("    ");
        }
        if (strcmp(command, "end") != 0 && strcmp(command, "clear") != 0 && strcmp(command, "random") != 0 && strcmp(command, "display") != 0 && strcmp(command, "transpose") != 0 && strcmp(command, "rotate") != 0 && strcmp(command, "sum") != 0 &&
        strcmp(command, "colsum") != 0 && strcmp(command, "diogsum") != 0 && strcmp(command, "swingfirst") != 0 && strcmp(command, "swinglast") != 0 && strcmp(command, "swingcols") != 0 && strcmp(command, "help") != 0){
            SetConsoleCursorPosition(hConsole, cmd);
            SetConsoleTextAttribute(hConsole, fer);
            printf ("                                                               ");
            SetConsoleCursorPosition(hConsole, scf);
            printf ("error, no command such as this");
            SetConsoleTextAttribute(hConsole, fcmd);
            printf(" -> ");
            SetConsoleTextAttribute(hConsole, fhelp);
            printf ("use help if you don`t know any commands");
        }
    }
    return 0;
}

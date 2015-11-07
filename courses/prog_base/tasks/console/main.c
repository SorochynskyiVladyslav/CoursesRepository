#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void color(HANDLE hConsole, int y);
void print(HANDLE hConsole, COORD pos, int x, int y);

int main()
{
    int x, y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    x = 79;
    y = 24;
    pos.X = x;
    pos.Y = y;
    while ((x != 0)||(y != 0)){
    /*last point*/
        if (y == 24 && x == 79){
        print(hConsole, pos, x, y);
        x--;
        }
    /*right diagonal starts*/
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    while (((y + 1) != 0) && (x != 80)){
    print(hConsole, pos, x, y);
    if ((y + 1) != 0)
    x++;
    if (x != 80)
    y--;
    }
    if ((y + 1) == 0){
        y++;
        x-=2;
    }
    if (x == 80){
        x--;
        y--;
    }
    /*left diagonale starts*/
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    while (((x + 1) != 0) && (y != 25)){
    print(hConsole, pos, x, y);
    if ((x + 1) != 0)
        y++;
    if (y != 25)
        x--;
    }
    if ((x + 1) == 0){
        x++;
        y-=2;
    }
    if (y == 25){
        y--;
        x--;
    }
    }
    /*first point*/
    if ((x == 0) && (y == 0))
    print(hConsole, pos, x, y);
    pos.X = 0;
    pos.Y = 25;
    SetConsoleCursorPosition(hConsole, pos);
    return EXIT_SUCCESS;
}

void color(HANDLE hConsole, int y){
    int fmt = 0;
    switch(y){
        case 0 ... 4:
            fmt = BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
            break;
        case 5 ... 9:
            fmt = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
            break;
        case 10 ... 14:
            fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
            break;
        case 15 ... 19:
            fmt = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
            break;
        case 20 ... 24:
            fmt = BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
            break;
        default:
            puts ("error, you`re out of console");
    }
    SetConsoleTextAttribute(hConsole, fmt);
}

void print(HANDLE hConsole, COORD pos, int x, int y){
    const long SLEEP_MILLISECONDS = 5;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    color(hConsole, y);
    Sleep(SLEEP_MILLISECONDS);
    printf("*");
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

void bg (void);
void drawAxes(COORD cent);
void drawGraph(COORD cent, int k, int g);
void connection (COORD cent, int x, int y, int lx, int ly);
void writefunc (int g);

int main()
{
    int g = 1, c = 0, k = 20;
    bg();
    COORD cent;
    cent.X = 40;
    cent.Y = 12;
    drawAxes(cent);
    drawGraph(cent, k, g);

    while (c != 27){
        c = _getch();
        switch (c){
    case 'w':
        cent.Y--;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case 's':
        cent.Y++;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case 'a':
        cent.X--;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case 'd':
        cent.X++;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case '=':
        if (g == 2)
        k--;
        if (g == 1)
        k++;
        if (k == 0)
            k = 1;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case '-':
        if (g == 2)
        k++;
        if (g == 1)
        k--;
        if (k == 0)
            k = 1;
        bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    case 32:
        g = (g == 1) ? 2 : 1;
		bg();
        drawAxes (cent);
        drawGraph (cent, k, g);
        writefunc (g);
        break;
    }
    }
    return 0;
}

void bg (void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int f;
    f = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |  BACKGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, f);
    for (pos.Y = 0; pos.Y < 30; pos.Y++){
    for (pos.X = 0; pos.X < 80; pos.X++){
        SetConsoleCursorPosition(hConsole, pos);
        printf(" ");
    }
    }
    }

void drawAxes(COORD cent){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int f = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    COORD draw;
    SetConsoleTextAttribute(hConsole, f);

    draw.X = cent.X;
    for(draw.Y = 0; draw.Y < 25; draw.Y++){
        SetConsoleCursorPosition(hConsole, draw);
        if (draw.Y % 2 == 0)
            printf("+");
        else printf("|");
    }
    draw.Y = cent.Y;
    for (draw.X = 0; draw.X < 80; draw.X++){
        SetConsoleCursorPosition(hConsole, draw);
        if (draw.X % 2 == 0)
        printf ("+");
        else printf ("-");
    }
}

void print(COORD cent, int x, int y){
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int f = BACKGROUND_BLUE | BACKGROUND_GREEN;
    SetConsoleTextAttribute(hConsole, f);
    pos.X = cent.X + x;
    pos.Y = cent.Y - y;
    if (pos.X >= 0 && pos.X <= 79 && pos.Y >= 0 && pos.Y <= 25){
    SetConsoleCursorPosition(hConsole, pos);
    printf(" ");
    }
}

void drawGraph (COORD cent, int k, int g){
    int x, y, lx, ly;
    lx = -40;
    for (x = -40; x < 40; x++){
        if (g == 1){
        y = (3.5 * cos(1.5 * x * k/20 - 2) + 3) * k/20;
        ly = (3.5 * cos(1.5 * lx * k/20 - 2) + 3) * k/20;
        }
        if (g == 2){
        y = (pow(x * k/20, 2) - 5) * k/20;
        ly = (pow(lx * k/20, 2) - 5) * k/20;
        }
        if (abs(y) <= 30){
        print (cent, x, y);
        connection (cent, x, y, lx, ly);
        }
        lx = x;
    }
}

void connection (COORD cent, int x, int y, int lx, int ly){
	if (ly < y){
		while (ly < y){
			print(cent, lx, ly);
			ly++;
		}
	}
	if (ly > y){
		while (y < ly){
			print(cent, x, y);
			y++;
		}
	}
}

void writefunc (int g){
    int f;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 5;
	pos.Y = 23;
	SetConsoleCursorPosition(hConsole, pos);
	f = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, f);
	if (g == 1) printf("f(x) =  3.5 * cos(1.5 * x - 2) + 3");
	else printf("f(x) = x^2 - 5");
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct dot {
    int x;
    int y;
};

void dotrandom (struct dot dotarr[], int size){
    int i;
    for (i = 0; i < size; i++){
        dotarr[i].x = rand() % 101 - 50;
        dotarr[i].y = rand() % 101 - 50;
    }
}

void printdots (struct dot dotarr[], int size){
    int i;
    for (i = 0; i < size; i++){
        printf("point%i (%i, %i);\n", i + 1, dotarr[i].x, dotarr[i].y);
    }
}

void square (struct dot dotarr[], int size){
    int i;
    struct dot d[4] = {{-55, -55}, {55, 55}, {-55, 55}, {55, -55}};
    for (i = 0; i < size; i++){
        if (dotarr[i].x >= d[0].x)
            d[0].x = dotarr[i].x;
        if (dotarr[i].y >= d[0].y)
            d[0].y = dotarr[i].y;

        if (dotarr[i].x <= d[1].x)
            d[1].x = dotarr[i].x;
        if (dotarr[i].y <= d[1].y)
            d[1].y = dotarr[i].y;

        if (dotarr[i].x >= d[2].x)
            d[2].x = dotarr[i].x;
        if (dotarr[i].y <= d[2].y)
            d[2].y = dotarr[i].y;

        if (dotarr[i].x <= d[3].x)
            d[3].x = dotarr[i].x;
        if (dotarr[i].y >= d[3].y)
            d[3].y = dotarr[i].y;
    }
        if (d[0].x <= d[3].x)
            d[3].x = d[0].x;
        else d[0].x = d[3].x;
        if (d[0].y <= d[2].y)
            d[2].y = d[0].y;
        else d[0].y = d[2].y;
        if (d[2].x >= d[1].x)
            d[1].x = d[2].x;
        else d[2].x = d[1].x;
        if (d[3].y <= d[1].y)
            d[3].y = d[1].y;
        else d[1].y = d[3].y;

        printdots(d, 4);

}

int main()
{
    int size;
    printf ("please, enter amount of points ");
    scanf("%i", &size);
    srand(time(NULL));

    if (size <= 0 || size >= 100){
        printf ("wrong size input\n");
        return 1;
    }

    struct dot dotarr[size];

    dotrandom(dotarr, size);
    printdots(dotarr, size);
    puts ("square coordinates");
    square(dotarr, size);

    return 0;
}


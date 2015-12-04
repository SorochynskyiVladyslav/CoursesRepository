#include <stdio.h>
#include <stdlib.h>

struct music {
    char* song;
    char* artist;
    float lenght;
    int year;
};

void printst(int size, struct music songs[size]);
int count(int size, struct music songs[size]);
void change(struct music * pVar, const char * newValue);
void print(struct music* pVar);

int main()
{
    char ch[100];
    struct music songs[7]={{"Walking with a ghost", "Kadebostany", 2.30, 2013}, {"Burn", "Ellie Goulding", 2.48, 2013}, {"Oblivion", "30 seconds to Mars", 1.59, 2002}, {"Stronger", "Kanye West", 4.46, 2007}, {"Eagle", "Kadebostany", 1.46, 2013}, {"It`s my life", "Bon Jovi", 2.50, 2000}, {"Skyfall", "Adele", 4.46, 2012}};
    const char* newsong;
    int i, amount;
    size_t size = sizeof(songs)/sizeof(struct music);
    printst(size, songs);

    printf("Enter number of song [1 ... %i], you want to change ", size);
    scanf("%i", &i);
    fflush(stdin);
    printf("Enter a new name of song\n");
    newsong = gets(ch);
    puts("");
    struct music* p = &songs[i-1];
    change(p, newsong);

    amount = count(size, songs);
    printf("amount = %i\n\n", amount);

    print(p);

    return 0;
}

void printst(int size, struct music songs[size]){
    int i;
    for (i = 0; i < size; i++){
        printf("%i) %s\n   Artist: %s, lenght: %.2lf, year %i\n", i+1, songs[i].song, songs[i].artist, songs[i].lenght, songs[i].year);
    }
    puts("");
}

int count(int size, struct music songs[size]){
    int i, amount = 0;
    for (i = 0; i < size; i++){
        if (songs[i].lenght >= 2){
            amount++;
        }
    }
    return amount;
}

void change(struct music * pVar, const char * newValue){
    (*pVar).song = newValue;
}

void print(struct music* pVar){
    printf(" %s\n Artist: %s, lenght: %.2lf, year %i\n", (*pVar).song, (*pVar).artist, (*pVar).lenght, (*pVar).year);
}

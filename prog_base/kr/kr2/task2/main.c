#include <stdio.h>
#include <stdlib.h>

struct mayor {
    char* name;
    int age;
};

struct city {
    char* name;
    struct mayor* ag;
    int age;
};

int main()
{
    struct mayor mrs[5]={{"Klichko Vitaly", 40}, {"Filatov Boris", 29}, {"Kyratin Victor", 43}, {"Sadovyy Andriy", 47}};
    struct city cities[5]={{"Kiev", &mrs[0], 1500}, {"Dnipropetrovsk", &mrs[1], 500},
                            {"Makeevka", &mrs[2], 49}, {"Lvyv", &mrs[3], 1200}};

    return 0;
}

void fillDefault1(struct mayor* pM){
    (*pM).name = "Surname Name"
    (*pM).age = 0;
}

void fillDefault2(struct city* pC){
    (*pC).name = "CityName";
    (*pC).age = 0;
}

void fillCertain1(struct mayor* pM, char* newname, int age){
    (*pM).name = newname;
    (*pM).age = age;
}

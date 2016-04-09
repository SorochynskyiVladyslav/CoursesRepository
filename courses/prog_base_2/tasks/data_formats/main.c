#include "head.h"
#include <locale.h>
#include <time.h>


void printStudent (xmlNode * xSt) {
    printf("\t%s\n", xSt->name);
    for (xmlNode * xI = xSt->children; xI; xI = xI->next) {
        if (XML_ELEMENT_NODE != xI->type) {
            continue;
        }
        if (xmlStrcmp(xI->name, "group") == 0){
            const char* groupName = xmlGetProp(xI, "name");
            printf("\t\t%10s (name = %s) : \n", "group", groupName);
            continue;
        }
        const char* contents = xmlNodeGetContent(xI);
        printf("\t\t%10s : %s\n", xI->name, contents);
    }
}

int main(void)
{
    char line[LINE_MAX_SIZE];
    char text[TEXT_MAX_SIZE] = "";
    const char* fileName = "teachers.xml";
    FILE * fr = fopen(fileName, "r");
    int amount = 0;
    while (fgets(line, LINE_MAX_SIZE, fr)) {
        strcat(text, line);
        amount++;
    }

    amount = (amount - 3)/10;

    teacher_t teachers[amount];
    for (int i = 0; i < amount; i++) {
        teachers[i] = teacher_new();
    }
    ReadXml (teachers, amount, text);
    for (int i = 0; i < amount; i++){
    teacher_print(teachers[i]);
    }













    fclose(fr);

    return 0;
}

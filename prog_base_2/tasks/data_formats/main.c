#include "head.h"


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

    for (int i = 0; i < amount; i++) {
        free(teachers[i]);
    }
    fclose(fr);

    return 0;
}
